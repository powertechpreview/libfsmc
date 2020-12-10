#include <iostream>
#include <stdio.h>
#include "SMatrix.h"

int main()
{
  //4x4
  SMatrix<double, 4, 4, RowMajor> sm1(10), sm2(20);
  std::cout << sm1 << std::endl;
  std::cout << sm2 << std::endl;
  std::cout << sm1.mul<4>(sm2) << std::endl;

  SMatrix<double, 4, 4, ColMajor> sm3(30);
  SMatrix<double, 4, 4, RowMajor> sm4(40);
  std::cout << sm3 << std::endl;
  std::cout << sm4 << std::endl;
  std::cout << sm3.mul<4>(sm4) << std::endl;

  //9x9
  SMatrix<double, 9, 9, RowMajor> sm9(90), sm10(100);
  std::cout << sm9 << std::endl;
  std::cout << sm10 << std::endl;
  std::cout << sm9.mul<9>(sm10) << std::endl;

  SMatrix<double, 9, 9, ColMajor> sm11(110);
  SMatrix<double, 9, 9, RowMajor> sm12(120);
  std::cout << sm11 << std::endl;
  std::cout << sm12 << std::endl;
  std::cout << sm11.mul<9>(sm12) << std::endl;

  return 0;
}
