#include <iostream>
#include "Matrix.h"
#include "SMatrix.h"

int main(int argc, char* argv[])
{
    const int m = 4, k = 2, n = 8;
    Matrix<double> m1(m,k,0), m2(k,n,0);
    SMatrix<double, m, m> sm1(1), sm2(1);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < k; j++)
        {
            m1(i,j) = 1;
        }
    }

    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < n; j++)
        {
            m2(i,j) = 1;
        }
    }
    std::cout << "Res\n" << m1*m2 << "\n\n";
    std::cout << "SRes\n" << sm1.mul<m>(sm2) << "\n\n";
    return 0;
}
