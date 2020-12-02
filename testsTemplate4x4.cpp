#include <iostream>
#include <stdio.h>
//#include <altivec.h>
#include "SMatrixWithMul4x4.h"


int main()
{
  SMatrix<double, 4, 4, RowMajor> sm1(10), sm2(10);
  std::cout << sm1.mul<4,4>(sm2) << std::endl;

  return 0;
}
