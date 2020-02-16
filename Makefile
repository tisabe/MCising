main: geometry.c vmath.c metropolis.c init_config.c
	gcc main.c -lm -fopenmp geometry.c vmath.c metropolis.c init_config.c observables.c -L/usr/local/lib -lgsl -o main.exe
	./main.exe

run_params: geometry.c vmath.c metropolis.c init_config.c observables.c
	gcc run_params.c -lm -fopenmp geometry.c vmath.c metropolis.c init_config.c observables.c -L/usr/local/lib -lgsl -o run_params.exe
	./run_params.exe

consistency_test: vmath.c geometry.c metropolis.c init_config.c observables.c
	gcc consistency_test.c -lm -fopenmp -lgsl structs.h vmath.c geometry.c metropolis.c init_config.c observables.c  -O3  -o consistency_test.exe
	./consistency_test.exe

mc_parallel_test: geometry.c vmath.c metropolis.c init_config.c observables.c
	gcc mc_parallel_test.c -lm -fopenmp geometry.c vmath.c metropolis.c init_config.c observables.c -L/usr/local/lib -lgsl -o mc_parallel_test.exe
	./mc_parallel_test.exe

test_analytical_solution: geometry.c vmath.c init_config.c observables.c
	gcc test_analytical_solution.c -lm -fopenmp geometry.c vmath.c init_config.c observables.c -L/usr/local/lib -lgsl -o test_analytical_solution.exe
	./test_analytical_solution.exe
