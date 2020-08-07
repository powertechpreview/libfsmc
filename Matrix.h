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

/* Small matrix */
/**** FIXME operator() const problem *****/
template<typename Scalar, int rows, int cols, int StorageOrder = RowMajor>
class SMatrix
{
public:
    const int m_rows, m_cols;
    Scalar m_data[rows*cols];

    SMatrix() : m_rows(rows), m_cols(cols) {}

    SMatrix(const Scalar& x0) : m_rows(rows), m_cols(cols)
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

    template<int mdepth, int mcols>
    SMatrix<Scalar, rows, mdepth> mul(const SMatrix<Scalar, mdepth, mcols>& rhs)
    {
        SMatrix<Scalar, rows, mdepth> res;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < mcols; j++)
            {
                for(int k = 0; k < mdepth; k++)
                {
                    res.m_data[StorageOrder == RowMajor ? i*mdepth + j : j*rows + i] += m_data[StorageOrder == RowMajor ? i*mdepth + k : k*rows + i]*rhs.m_data[StorageOrder == RowMajor ? k*mcols + j : j*mdepth + k];
                }
            }
        }
        return res;
    }

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