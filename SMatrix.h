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
    template<int mRHS_cols, int outOrder = RowMajor>
    SMatrix<Scalar, rows, mRHS_cols, outOrder> mul(const SMatrix<Scalar, cols, mRHS_cols>& rhs);

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
template<int mRHS_cols, int outOrder>
SMatrix<Scalar, rows, mRHS_cols, outOrder> SMatrix<Scalar, rows, cols, StorageOrder>::mul(const SMatrix<Scalar, cols, mRHS_cols>& rhs)
{
    SMatrix<Scalar, rows, mRHS_cols, outOrder> res;    //if RowMajor: lhs(this): #rows = rows, #columns = cols
    for(int i = 0; i < rows; i++)            //             rhs:       #rows = cols, #columns = mRHS_cols
    {                                        //             res:       #rows = rows, #columns = mRHS_cols
        for(int j = 0; j < mRHS_cols; j++)
        {
            for(int k = 0; k < cols; k++)
            {
                res.m_data[res.storage_order == RowMajor ? i*mRHS_cols + j : j*rows + i] += this->m_data[this->storage_order == RowMajor ? i*cols + k : k*rows + i]*rhs.m_data[rhs.storage_order == RowMajor ? k*mRHS_cols + j : j*cols + k];
            }
        }
    }
    return res;
}
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
//====================================================================================================//

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

#endif //IBM_SMATRIX_H
