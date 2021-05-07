#include <iostream>
#include "SMatrix.h"
#include <benchmark/benchmark.h>

static void BM_CONQUER(benchmark:: State& state)
{
  	int N=256;

 	static double A[256*256];
	static double B[256*256];
	static double C[256*256]={0};

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			A[i*N+j]=i+j;
			if(i==j){
				B[i*N+j]=1;
			}

			else{
				B[i*N+j]=0;
			}
		
		}
	
	}
	
	for(auto _: state){

	conquer(A,B,C,N,N);

	}

}

BENCHMARK(BM_CONQUER)->Unit(benchmark::kSecond)->Iterations(100);

BENCHMARK_MAIN();


