# libfsmc
Library for Fast Small Matrix Computation

## Benchmarks

### Requirements

  You need to have Google benchmark compiled. Here are the instructions:
  
  ```bash
# Check out the library.
$ git clone https://github.com/google/benchmark.git
# Benchmark requires Google Test as a dependency. Add the source tree as a subdirectory.
$ git clone https://github.com/google/googletest.git benchmark/googletest
# Go to the library root directory
$ cd benchmark
# Make a build directory to place the build output.
$ mkdir build && cd build
# Generate a Makefile with cmake.
# Use cmake -G <generator> to generate a different file type.
$ cmake -DCMAKE_BUILD_TYPE=Release ../
# Build the library.
# Use make -j<number_of_parallel_jobs> to speed up the build process, e.g. make -j8 .
$ make
```

  It is also recommended to install `scipy` to compare results between two benchmarks. Don't forget to initialize or manually replace the `GOOGLE_BENCHMARK_FOLDER` variable below.
  
  ```bash
     pip3 install -r $(GOOGLE_BENCHMARK_FOLDER)/tools/requirements.txt
  ```

### Features

We support the following microbenchmarks:
 * GEMM ( `benchmark.cpp` )

Our benchmarks can compare results with the following libraries:
  * Eigen ( `eigen_benchmark.cpp` )
  
### Usage

* Generate `libfsmc` benchmarks: 
```bash
  make benchmark GOOGLE_BENCHMARK_FOLDER=<folder>
``` 
* Generate `Eigen` benchmarks: 
```bash
  make eigen_benchmark EIGEN_FOLDER=<folder> GOOGLE_BENCHMARK_FOLDER=<folder>
``` 
* Compare `libfsmc` with `Eigen`: 
```bash
  make compare_eigen EIGEN_FOLDER=<folder> GOOGLE_BENCHMARK_FOLDER=<folder>
``` 

## The SMatrix class

The `SMatrix.h` is currently the main header file of the library. In this file there is a [class](https://en.wikipedia.org/wiki/C%2B%2B_classes) called SMatrix that is used for working with small matrices. It has the atributes:
* `m_rows`, `m_cols`: the number of rows and cols of the matrix;
* `storage_order`: the order the elements of the matrix are stored. It is an [enumerated type](https://en.wikipedia.org/wiki/Enumerated_type) used to indicate if the matrix is stored at [row-major or column-major order](https://en.wikipedia.org/wiki/Row-_and_column-major_order);
* `m_data`: a 1D-array to store the matrix elements. It's type is chosen by using [typename](https://en.wikipedia.org/wiki/Typename).

The storage order The SMatrix class has some methods that allows the programmer to do some operations easily, some of then use [operator overloading](https://en.wikipedia.org/wiki/Operator_overloading). There is a matrix multiplication method, called `mul`, that multiplies two general matrices that have the same type of elements, no matter what are neither their storage order nor their sizes (since they follow the rule for matrix multiplication: mxn nxk). The matrix multiplication will follow the standard algorithm by using [outer product](https://en.wikipedia.org/wiki/Outer_product#Definition), but, in order to optimaze it, we use [C++ templates](https://en.wikipedia.org/wiki/Template_metaprogramming#Compile-time_code_optimization), that are used to generate code at compile-time.

### Special sizes

There are some matrix special sizes that are worth of having their own multiplication optimazed code, because theses multiplications are more commom. When multiplying two 4x4, 9x9 and 12x12 double matrices the `mul` method uses [partial template specialization](https://en.wikipedia.org/wiki/Partial_template_specialization) to call, for each case, a specific function from the `Smul.h` file that performs a optimized multiplication using some vector instructions for Power from the [AltiVec](https://en.wikipedia.org/wiki/AltiVec) library. In these cases the left-hand side matrix can be either row-major or column-major, but the right-hand side matrix must be row-major. The resulting matrix will be row-major as well.

## Code example

To use the library codes, one needs first to:

```bash
# clone the library
$ git clone https://github.com/powertechpreview/libfsmc.git
# change the current working directory
$ cd libfsmc
```

Supose one wants to perform a matrix multiplication between a 3x4 and a 4x5 double matrices and between two 4x4 double matrices. The following code does so:

```cpp
#include <iostream>
#include "SMatrix.h"	// include the header file for small matrices

int main () {
  // create a 3x4 double matrix filled with ones
  SMatrix<double, 3, 4> lhs(1);
  // create a 4x5 double matrix filled with twos
  SMatrix<double, 4, 5> rhs(2);
  // create an empty 3x5 double matrix
  SMatrix<double, 3, 5> res;

  // perform the multiplication between 'lhs' and 'rhs' and pass it to 'res'
  res = lhs.mul<5>(rhs); // the value inside <> must be the number of columns of the right hand side matrix

  // create two 4x4 double matrices and fill the first with ones and the second with twos
  SMatrix<double, 4, 4> a(1), b(2); 
  // create an empty 4x4 double matrix
  SMatrix<double, 4, 4> c;

  // multiply a and b and pass it to c
  // this multiplication is performed by using vector instructons 
  c = a.mul<4>(b);

  // if one want, it is possible to print a matrix
  std::cout << res << std::endl;
  std::cout << c << std::endl;

  return 0;
}
```
