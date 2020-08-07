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
  
