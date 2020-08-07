#include <benchmark/benchmark.h>
#include <Eigen/Dense>

template <typename T> void BM_GEMM(benchmark::State& state) {
  // Perform setup here
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Random(state.range(0), state.range(0));
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> B = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Random(state.range(0), state.range(0));
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> C = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Random(state.range(0), state.range(0));
  for (auto _ : state) {
    // This code gets timed
    C = A*B;
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
