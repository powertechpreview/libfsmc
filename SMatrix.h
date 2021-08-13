#ifndef IBM_SMATRIX_H
#define IBM_SMATRIX_H

#include <iostream>
#include <stdio.h>
#include <altivec.h>
#include "Smul.h"

enum EStorageOrder : int { RowMajor, ColMajor };

template<typename Scalar, int rows, int cols, int StorageOrder = RowMajor>
class SMatrix
{
public:
    const int m_rows, m_cols, storage_order;
    Scalar m_data[rows*cols];

    SMatrix() : m_rows(rows), m_cols(cols), storage_order(StorageOrder) {}

    explicit SMatrix(const Scalar& x0) : m_rows(rows), m_cols(cols), storage_order(StorageOrder)
    {
        setVal<rows, cols>(x0);
    }

    template<int r, int c>
    void setVal(const Scalar& v)
    {
        for(int i = 0; i < r; i++)
        {
            for(int j = 0; j < c; j++)
            {
                m_data[StorageOrder == RowMajor ? i*cols + j : j*rows + i] = v;
            }
        }
    }

    inline Scalar& operator()(int i, int j) const
    {
        return m_data[StorageOrder == RowMajor ? i*cols + j : j*rows + i];
    }

    // Template declaration - multiplication of matrices  // ONE MUST DEFINE THE TEMPLATE FUNCTION OUTSIDE THE CLASS TO ALLOW SPECIALIZATION (but must declare it inside the class)
    //====================================================================================================
    template<int mRHS_cols>
    SMatrix<Scalar, rows, mRHS_cols> mul(const SMatrix<Scalar, cols, mRHS_cols>& rhs);

    //====================================================================================================
    friend std::ostream& operator<<(std::ostream& out, const SMatrix& m)
    {
        for(int i = 0; i < rows;i++)
        {
            for(int j = 0; j < cols; j++)
            {
                out << m.m_data[StorageOrder == RowMajor ? i*cols + j : j*rows + i] << " ";
            }
            out << std::endl;
        }
        return out;
    }
};

// Template definition - multiplication of matrices
//====================================================================================================
template<typename Scalar, int rows, int cols, int StorageOrder>
template<int mRHS_cols>
SMatrix<Scalar, rows, mRHS_cols> SMatrix<Scalar, rows, cols, StorageOrder>::mul(const SMatrix<Scalar, cols, mRHS_cols>& rhs)
{
    SMatrix<Scalar, rows, mRHS_cols> res;    //if RowMajor: lhs(this): #rows = rows, #columns = cols
    for(int i = 0; i < rows; i++)            //             rhs:       #rows = cols, #columns = mRHS_cols
    {                                        //             res:       #rows = rows, #columns = mRHS_cols
        for(int j = 0; j < mRHS_cols; j++)
        {
            for(int k = 0; k < cols; k++)
            {
                res.m_data[res.StorageOrder == RowMajor ? i*mRHS_cols + j : j*rows + i] += this->m_data[this->StorageOrder == RowMajor ? i*cols + k : k*rows + i]*rhs.m_data[rhs.StorageOrder == RowMajor ? k*mRHS_cols + j : j*cols + k];
            }
        }
    }
    return res;
}

//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
// Template specialization - multiplication of 4 by 4 double matrices
//====================================================================================================
//  SOLVING ERRORS: ONE CAN NOT SPECIALIZE A MEMBER FUNCTION WITHOUT ALSO SPECIALIZING THE CLASS
template<>
template<>
SMatrix<double, 4, 4> SMatrix<double, 4, 4, RowMajor>::mul<4>(const SMatrix<double, 4, 4>& rhs)  // lhs(this) is RowMajor and rhs is RowMajor
{
    SMatrix<double, 4, 4> res;
    mul4x4RowMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
    return res;
}
//====================================================================================================
template<>
template<>
SMatrix<double, 4, 4> SMatrix<double, 4, 4, ColMajor>::mul<4>(const SMatrix<double, 4, 4>& rhs)  // lhs(this) is ColMajor and rhs is RowMajor
{
    SMatrix<double, 4, 4> res;
    mul4x4ColMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
    return res;
}

//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//


// Template specialization - multiplication of 4 by 4 float matrices
//====================================================================================================
//  SOLVING ERRORS: ONE CAN NOT SPECIALIZE A MEMBER FUNCTION WITHOUT ALSO SPECIALIZING THE CLASS
template<>
template<>
SMatrix<float, 4, 4> SMatrix<float, 4, 4, RowMajor>::mul<4>(const SMatrix<float, 4, 4>& rhs)  // lhs(this) is RowMajor and rhs is RowMajor
{
    SMatrix<float, 4, 4> res;
    mul4x4RowMajorFloat((float*)this->m_data, (float*)rhs.m_data, (float*)res.m_data);
    return res;
}
//====================================================================================================
template<>
template<>
SMatrix<float, 4, 4> SMatrix<float, 4, 4, ColMajor>::mul<4>(const SMatrix<float, 4, 4>& rhs)  // lhs(this) is ColMajor and rhs is RowMajor
{
    SMatrix<float, 4, 4> res;
    mul4x4ColMajorFloat((float*)this->m_data, (float*)rhs.m_data, (float*)res.m_data);
    return res;

}

//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//

// Template specialization - multiplication of 9 by 9 double matrices
//====================================================================================================
template<>
template<>
SMatrix<double, 9, 9> SMatrix<double, 9, 9, RowMajor>::mul<9>(const SMatrix<double, 9, 9>& rhs)  // lhs(this) is RowMajor and rhs is RowMajor
{
    SMatrix<double, 9, 9> res;
    mul9x9RowMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
    return res;
}
//====================================================================================================
template<>
template<>
SMatrix<double, 9, 9> SMatrix<double, 9, 9, ColMajor>::mul<9>(const SMatrix<double, 9, 9>& rhs)  // lhs(this) is ColMajor and rhs is RowMajor
{
    SMatrix<double, 9, 9> res;
    mul9x9ColMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
    return res;
}

//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//

// Template specialization - multiplication of 9 by 9 float matrices
//====================================================================================================
template<>
template<>
SMatrix<float, 9, 9> SMatrix<float, 9, 9, RowMajor>::mul<9>(const SMatrix<float, 9, 9>& rhs)  // lhs(this) is RowMajor and rhs is RowMajor
{
    SMatrix<float, 9, 9> res;
    mul9x9RowMajorFloat((float*)this->m_data, (float*)rhs.m_data, (float*)res.m_data);
    return res;
}
//====================================================================================================
template<>
template<>
SMatrix<float, 9, 9> SMatrix<float, 9, 9, ColMajor>::mul<9>(const SMatrix<float, 9, 9>& rhs)  // lhs(this) is ColMajor and rhs is RowMajor
{
    SMatrix<float, 9, 9> res;
    mul9x9ColMajorFloat((float*)this->m_data, (float*)rhs.m_data, (float*)res.m_data);
    return res;

}


//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//

// Template specialization - multiplication of 12 by 12 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 12, 12> SMatrix<double, 12, 12, RowMajor>::mul<12>(const SMatrix<double, 12, 12>& rhs)
{
        SMatrix<double, 12, 12> res;
        mul12x12RowMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
        return res;
}

template<>
template<>
SMatrix<double, 12, 12> SMatrix<double, 12, 12, ColMajor>::mul<12>(const SMatrix<double, 12, 12>& rhs)
{
        SMatrix<double, 12, 12> res;
        mul12x12ColMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
        return res;
}

//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//


// Template specialization - multiplication of 12 by 12 float matrices
//====================================================================================================
template<>
template<>
SMatrix<float, 12, 12> SMatrix<float, 12, 12, RowMajor>::mul<12>(const SMatrix<float, 12, 12>& rhs)  // lhs(this) is RowMajor and rhs is RowMajor
{
    SMatrix<float, 12, 12> res;
    mul12x12RowMajorFloat((float*)this->m_data, (float*)rhs.m_data, (float*)res.m_data);
    return res;
}
//====================================================================================================
template<>
template<>
SMatrix<float, 12, 12> SMatrix<float, 12, 12, ColMajor>::mul<12>(const SMatrix<float, 12, 12>& rhs)  // lhs(this) is ColMajor and rhs is RowMajor
{
    SMatrix<float, 12, 12> res;
    mul12x12ColMajorFloat((float*)this->m_data, (float*)rhs.m_data, (float*)res.m_data);
    return res;

}



//====================================================================================================//
// Divide and Conquer - multiplication of 1024 by 1024 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 1024, 1024> SMatrix<double, 1024, 1024, RowMajor>::mul<1024>(const SMatrix<double, 1024, 1024>& rhs)
{
        SMatrix<double, 1024, 1024> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 1024, 1024);
        return res;
}

template<>
template<>
SMatrix<double, 1024, 1024> SMatrix<double, 1024, 1024, ColMajor>::mul<1024>(const SMatrix<double, 1024, 1024>& rhs)
{
        SMatrix<double, 1024, 1024> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 1024, 1024);
        return res;
}
// Divide and Conquer - multiplication of 512 by 512 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 512, 512> SMatrix<double, 512, 512, RowMajor>::mul<512>(const SMatrix<double, 512, 512>& rhs)
{
        SMatrix<double, 512, 512> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 512, 512);
        return res;
}

template<>
template<>
SMatrix<double, 512, 512> SMatrix<double, 512, 512, ColMajor>::mul<512>(const SMatrix<double, 512, 512>& rhs)
{
        SMatrix<double, 512, 512> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 512, 512);
        return res;
}

// Divide and Conquer - multiplication of 256 by 256 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 256, 256> SMatrix<double, 256, 256, RowMajor>::mul<256>(const SMatrix<double, 256, 256>& rhs)
{
        SMatrix<double, 256, 256> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 256, 256);
        return res;
}

template<>
template<>
SMatrix<double, 256, 256> SMatrix<double, 256, 256, ColMajor>::mul<256>(const SMatrix<double, 256, 256>& rhs)
{
        SMatrix<double, 256, 256> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 256, 256);
        return res;
}

// Divide and Conquer - multiplication of 128 by 128 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 128, 128> SMatrix<double, 128, 128, RowMajor>::mul<128>(const SMatrix<double, 128, 128>& rhs)
{
        SMatrix<double, 128, 128> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 128, 128);
        return res;
}

template<>
template<>
SMatrix<double, 128, 128> SMatrix<double, 128, 128, ColMajor>::mul<128>(const SMatrix<double, 128, 128>& rhs)
{
        SMatrix<double, 128, 128> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 128, 128);
        return res;
}

// Divide and Conquer - multiplication of 64 by 64 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 64, 64> SMatrix<double, 64, 64 , RowMajor>::mul<64>(const SMatrix<double, 64, 64>& rhs)
{
        SMatrix<double, 64, 64> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 64, 64);
        return res;
}

template<>
template<>
SMatrix<double, 64, 64> SMatrix<double, 64, 64, ColMajor>::mul<64>(const SMatrix<double, 64, 64>& rhs)
{
        SMatrix<double, 64, 64> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 64, 64);
        return res;
}


// Divide and Conquer - multiplication of 32 by 32 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 32, 32> SMatrix<double, 32, 32, RowMajor>::mul<32>(const SMatrix<double, 32, 32>& rhs)
{
        SMatrix<double, 32, 32> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 32, 32);
        return res;
}

template<>
template<>
SMatrix<double, 32, 32> SMatrix<double, 32, 32, ColMajor>::mul<32>(const SMatrix<double, 32, 32>& rhs)
{
        SMatrix<double, 32, 32> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 32, 32);
        return res;
}

// Divide and Conquer - multiplication of 16 by 16 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 16, 16> SMatrix<double, 16, 16, RowMajor>::mul<16>(const SMatrix<double, 16, 16>& rhs)
{
        SMatrix<double, 16, 16> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 16, 16);
        return res;
}

template<>
template<>
SMatrix<double, 16, 16> SMatrix<double, 16, 16, ColMajor>::mul<16>(const SMatrix<double, 16, 16>& rhs)
{
        SMatrix<double, 16, 16> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 16, 16);
        return res;
}


// Divide and Conquer - multiplication of 8 by 8 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 8, 8> SMatrix<double, 8, 8, RowMajor>::mul<8>(const SMatrix<double, 8, 8>& rhs)
{
        SMatrix<double, 8, 8> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 8, 8);
        return res;
}

template<>
template<>
SMatrix<double, 8, 8> SMatrix<double, 8, 8, ColMajor>::mul<8>(const SMatrix<double, 8, 8>& rhs)
{
        SMatrix<double, 8, 8> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 8, 8);
        return res;
}

// Divide and Conquer - multiplication of 2 by 2 double matrices
//====================================================================================================//
template<>
template<>
SMatrix<double, 2, 2> SMatrix<double, 2, 2, RowMajor>::mul<2>(const SMatrix<double, 2, 2>& rhs)
{
        SMatrix<double, 2, 2> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 2, 2);
        return res;
}

template<>
template<>
SMatrix<double, 2, 2> SMatrix<double, 2, 2, ColMajor>::mul<2>(const SMatrix<double, 2, 2>& rhs)
{
        SMatrix<double, 2, 2> res;
        conquer((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data, 2, 2);
        return res;
}
#endif //IBM_SMATRIX_H
