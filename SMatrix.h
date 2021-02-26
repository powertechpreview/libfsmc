#ifndef IBM_SMATRIX_H
#define IBM_SMATRIX_H

#include <iostream>
#include <stdio.h>
#include <altivec.h>
#include "Smul.h"
#include "EStorageOrder.h"

/*
 * class for small matrices. StorageOrder is defined in the EstorageOrder.h file.
 */
template<typename Scalar, int rows, int cols, int StorageOrder = RowMajor>
class SMatrix
{
public:
    const int m_rows, m_cols, storage_order;
    Scalar m_data[rows*cols];

    /*
     * Construct a SMatrix object where m_rows = rows, m_cols = cols, storage_order = StorageOrder
     * and m_data is empty.
     */
    SMatrix() : m_rows(rows), m_cols(cols), storage_order(StorageOrder) {}

    /*
     * Construct a SMatrix object where m_rows = rows, m_cols = cols, storage_order = StorageOrder
     * and all the m_data's elements are equal to x0.
     */
    explicit SMatrix(const Scalar& x0) : m_rows(rows), m_cols(cols), storage_order(StorageOrder)
    {
        setVal<rows, cols>(x0);
    }

    /*
     * Set the value of all the m_data elements equal to v.
     */
    template<int r, int c>
    void setVal(const Scalar& v)
    {
        for(int i = 0; i < r*c; i++)
		m_data[i] = v;
    }

    /*
     * () operator overloading: takes two ints i and j and return the element in the ith row
     * and jth column. i and j begin at 0.
     */
    inline Scalar& operator()(int i, int j) /*const*/
    {
        return m_data[StorageOrder == RowMajor ? i*cols + j : j*rows + i];
    }

    /*
     * = operator overloading: copies the m_data atribute of the matrix on the right
     * of the = operator to the m_data atribute of this matrix.
     */
    void operator=(const SMatrix& m)
    {
	for (int i = 0; i < m_rows*m_cols; i++)
		m_data[i] = m.m_data[i];
    }

    /*
     * + operator overloading: creates and returns an object (called res) of the SMatrix class where 
     * its atribute m_data is the sum of the m_data atribute of this matrix with the m_data atribute 
     * of the matrix on the right of the + operator.
     */
    inline SMatrix<Scalar, rows, cols> operator+(const SMatrix& m)
    {
	    SMatrix<Scalar, rows, cols> res;

	    for (int i = 0; i < rows*cols; i++)
		    res.m_data[i] = m_data[i] + m.m_data[i];

	    return res;
    }

    /*
     * - operator overloading: creates and returns an object (called res) of the SMatrix class where 
     * its atribute m_data is the subtraction of the m_data atribute of this matrix by the m_data atribute 
     * of the matrix on the right of the - operator.
     */
    inline SMatrix<Scalar, rows, cols> operator-(const SMatrix& m)
    {
	    SMatrix<Scalar, rows, cols> res;

	    for (int i = 0; i < rows*cols; i++)
		    res.m_data[i] = m_data[i] - m.m_data[i];

	    return res;
    }

    /*
     * Multiplies this matrix by the rhs matrix and returns it as another SMatrix object called res.
     * The returning matrix order (called outOrder) is RowMajor by default, but can be set as ColMajor.
     */
    template<int mRHS_cols, int outOrder = RowMajor>
    SMatrix<Scalar, rows, mRHS_cols, outOrder> mul(const SMatrix<Scalar, cols, mRHS_cols>& rhs);

    /*
     * << operator overloading: prints the matrix elements.
     */
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

/*
 * Multiplies two general matrices by outer product.
 */
template<typename Scalar, int rows, int cols, int StorageOrder>
template<int mRHS_cols, int outOrder>
SMatrix<Scalar, rows, mRHS_cols, outOrder> SMatrix<Scalar, rows, cols, StorageOrder>::mul(const SMatrix<Scalar, cols, mRHS_cols>& rhs)
{
    SMatrix<Scalar, rows, mRHS_cols, outOrder> res(0);
    for(int i = 0; i < rows; i++)
    {
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

/*
 * When this matrix and the rhs matrix are 4x4 double row-major matrices, call the function mul4x4RowMajor,
 * from the Smul.h file, to perform the multiplication.
 */
template<>
template<>
SMatrix<double, 4, 4> SMatrix<double, 4, 4, RowMajor>::mul<4>(const SMatrix<double, 4, 4>& rhs)
{
    SMatrix<double, 4, 4> res;
    mul4x4RowMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
    return res;
}

/*
 * When this matrix is a 4x4 double column-major matrix and the rhs is a 4x4 double row-major matrix, 
 * call the function mul4x4ColMajor, from the Smul.h file, to perform the multiplication.
 */
template<>
template<>
SMatrix<double, 4, 4> SMatrix<double, 4, 4, ColMajor>::mul<4>(const SMatrix<double, 4, 4>& rhs)
{
    SMatrix<double, 4, 4> res;
    mul4x4ColMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
    return res;
}

/*
 * When this matrix and the rhs matrix are 9x9 double row-major matrices, call the function mul9x9RowMajor,
 * from the Smul.h file, to perform the multiplication.
 */
template<>
template<>
SMatrix<double, 9, 9> SMatrix<double, 9, 9, RowMajor>::mul<9>(const SMatrix<double, 9, 9>& rhs)
{
    SMatrix<double, 9, 9> res;
    mul9x9RowMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
    return res;
}

/*
 * When this matrix is a 9x9 double column-major matrix and the rhs is a 9x9 double row-major matrix, 
 * call the function mul9x9ColMajor, from the Smul.h file, to perform the multiplication.
 */
template<>
template<>
SMatrix<double, 9, 9> SMatrix<double, 9, 9, ColMajor>::mul<9>(const SMatrix<double, 9, 9>& rhs)
{
    SMatrix<double, 9, 9> res;
    mul9x9ColMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
    return res;
}

/*
 * When this matrix and the rhs matrix are 12x12 double row-major matrices, call the function mul12x12RowMajor,
 * from the Smul.h file, to perform the multiplication.
 */
template<>
template<>
SMatrix<double, 12, 12> SMatrix<double, 12, 12, RowMajor>::mul<12>(const SMatrix<double, 12, 12>& rhs)
{
        SMatrix<double, 12, 12> res;
        mul12x12RowMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
        return res;
}

/*
 * When this matrix is a 12x12 double column-major matrix and the rhs is a 12x12 double row-major matrix, 
 * call the function mul12x12ColMajor, from the Smul.h file, to perform the multiplication.
 */
template<>
template<>
SMatrix<double, 12, 12> SMatrix<double, 12, 12, ColMajor>::mul<12>(const SMatrix<double, 12, 12>& rhs)
{
        SMatrix<double, 12, 12> res;
        mul12x12ColMajor((double*)this->m_data, (double*)rhs.m_data, (double*)res.m_data);
        return res;
}

#endif //IBM_SMATRIX_H
