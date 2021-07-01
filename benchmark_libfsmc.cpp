#include <benchmark/benchmark.h>
#include "SMatrix.h"
/*
 
Gera bug no gcc.

template<typename T>
void BM_GEMM(benchmark::State& s) {
  // Perform setup her


 	SMatrix<double,s.range(0), s.range(0) ,0> A(10); 
 	SMatrix<double,s.range(0) ,s.range(0) ,0> B(11.16);

	for(auto _ : s){
	benchmark::DoNotOptimize(A.template mul<s.range(0)>(B));	

 	 }


}

static void CustomArgs(benchmark::internal::Benchmark* b) {
	  for (int i = 2; i < 3; ++i) {
		b->Args({i*i});
	 }
}


BENCHMARK_TEMPLATE(BM_GEMM,double)->Apply(CustomArgs);
BENCHMARK_MAIN();

*/

template<typename T, int n>
static void BM_GEMM(benchmark::State& s){
	SMatrix<T,n,n,0> A(12), B(989);
	
	for(auto _ : s){
		benchmark::DoNotOptimize(A.template mul<n>(B));
	}
}


int main(int argc,char** argv){

	benchmark::RegisterBenchmark("GEMM_double 4",BM_GEMM<double,4>);
	benchmark::RegisterBenchmark("GEMM_double 9",BM_GEMM<double,9>);
	benchmark::RegisterBenchmark("GEMM_double 12",BM_GEMM<double,12>);
	benchmark::Initialize(&argc,argv);
	benchmark::RunSpecifiedBenchmarks();

}
