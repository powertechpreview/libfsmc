#include <iostream>
#include <stdio.h>
#include <altivec.h>
#include "SMatrixWithMul4x4.h"


int main()
{
  SMatrix<double, 4, 4, RowMajor> sm1(10), sm2(20);
  std::cout << sm1 << std::endl;
  std::cout << sm2 << std::endl;
  std::cout << sm1.mul<4>(sm2) << std::endl;

  SMatrix<double, 4, 4, ColMajor> sm3(30);
  SMatrix<double, 4, 4, RowMajor> sm4(40);
  std::cout << sm3 << std::endl;
  std::cout << sm4 << std::endl;
  std::cout << sm3.mul<4>(sm4) << std::endl;

  return 0;
}

