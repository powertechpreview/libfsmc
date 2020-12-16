#include <iostream>
#include <stdio.h>
#include "SMatrix.h"

int main()
{
  //2x2
  SMatrix<int, 2, 2, RowMajor> sm01(1), sm02(2);
  std::cout << sm01 << std::endl;
  std::cout << sm02 << std::endl;
  std::cout << sm01.mul<2>(sm02) << std::endl;

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

  //12x12
  SMatrix<double, 12, 12, RowMajor> sm13(90), sm14(100);
  std::cout << sm13 << std::endl;
  std::cout << sm14 << std::endl;
  std::cout << sm13.mul<12>(sm14) << std::endl;

  SMatrix<double, 12, 12, ColMajor> sm15(110);
  SMatrix<double, 12, 12, RowMajor> sm16(120);
  std::cout << sm15 << std::endl;
  std::cout << sm16 << std::endl;
  std::cout << sm15.mul<12>(sm16) << std::endl;
  return 0;
}
