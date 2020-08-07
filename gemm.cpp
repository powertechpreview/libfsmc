#include <iostream>
#include "Matrix.h"

int main(int argc, char* argv[])
{
    int s = 4;
    Matrix<double> m1(s,s,0), m2(s,s,0);

    for(int i = 0; i < s; i++)
    {
        for(int j = 0; j < s; j++)
        {
            m1(i,j) = 1;
            m2(i,j) = 1;
        }
    }
    std::cout << "Res\n" << m1*m2 << "\n\n";
    return 0;
}