benchmark:
	g++ -O3 benchmark_libfsmc.cpp -isystem $(GOOGLE_BENCHMARK_FOLDER)/include -L$(GOOGLE_BENCHMARK_FOLDER)/build/src -lbenchmark -lpthread -o benchmark
eigen_benchmark:
	g++ -O3 benchmark_eigen.cpp -I $(EIGEN_FOLDER) -isystem $(GOOGLE_BENCHMARK_FOLDER)/include -L$(GOOGLE_BENCHMARK_FOLDER)/build/src -lbenchmark -lpthread -o eigen_benchmark
compare_eigen: benchmark eigen_benchmark
	$(GOOGLE_BENCHMARK_FOLDER)/tools/compare.py benchmarks $(CURDIR)/benchmark $(CURDIR)/eigen_benchmark
