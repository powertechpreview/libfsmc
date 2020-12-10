#include <iostream>

enum EStorageOrder : int { RowMajor, ColMajor };

template<typename Scalar, typename Index = long int, int StorageOrder = RowMajor>
class Matrix {
public:
    Index m_rows, m_cols;
    Scalar *m_data;

    Matrix(Index rows, Index cols) : m_rows(rows), m_cols(cols)
    {
        m_data = new Scalar[rows*cols];
    }

    Matrix(Index rows, Index cols, const Scalar& x0) : m_rows(rows), m_cols(cols)
    {
        m_data = new Scalar[rows*cols];
        setVal(x0);
    }

    void setVal(const Scalar& v)
    {
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                operator()(i,j) = v;
            }
        }
    }

    ~Matrix()
    {
        delete[] m_data;
    }

    /* In order to use operator[] we would need to implement a 1D array class, to avoid that we use the Fortran-like matrix access */
    inline Scalar& operator()(Index i, Index j) const
    {
        return m_data[StorageOrder == RowMajor ? i*m_cols + j : j*m_rows + i];
    }

    Matrix<Scalar> operator*(Matrix& rhs)
    {
        Matrix<Scalar, Index, StorageOrder> res(m_rows, rhs.m_cols);
        for(Index i = 0; i < m_rows; i++)
        {
            for(Index j = 0; j < rhs.m_cols; j++)
            {
                for(Index k = 0; k < m_cols; k++)
                {
                    res(i,j) += operator()(i,k)*rhs(k,j);
                }
            }
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix& m)
    {
        for(Index i = 0; i < m.m_rows;i++)
        {
            for(Index j = 0; j < m.m_cols; j++)
            {
                out << m(i,j) << " ";
            }
            out << std::endl;
        }
        return out;
    }
};
