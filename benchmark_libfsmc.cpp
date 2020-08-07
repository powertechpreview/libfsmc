#include <benchmark/benchmark.h>
#include "Matrix.h"

template <typename T> void BM_GEMM(benchmark::State& state) {
  // Perform setup here
  Matrix<T> A(state.range(0), state.range(0), 0);
  Matrix<T> B(state.range(0), state.range(0), 0);

  for(int i = 0; i < state.range(0); i++)
  {
      for(int j = 0; j < state.range(0); j++)
      {
          A(i,j) = ((T)rand()/(T)(RAND_MAX)) * 3;
          B(i,j) = ((T)rand()/(T)(RAND_MAX)) * 7;
      }
  }


  for (auto _ : state) {
    // This code gets timed
    Matrix<T> C = A*B;
    benchmark::DoNotOptimize(C);
  }
}

int main(int argc, char** argv) {

  //Small size benchmarks (8 -> 256)
  benchmark::RegisterBenchmark("GEMM_double", BM_GEMM<double>)
	->RangeMultiplier(2)->Range(8, 256);

  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
