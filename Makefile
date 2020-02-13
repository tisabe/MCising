main: geometry.c vmath.c metropolis.c init_config.c
	gcc main.c -lm geometry.c vmath.c metropolis.c init_config.c observables.c -L/usr/local/lib -lgsl -o main.exe
	./main.exe

run_params: geometry.c vmath.c metropolis.c init_config.c observables.c
	gcc run_params.c -lm geometry.c vmath.c metropolis.c init_config.c observables.c -L/usr/local/lib -lgsl -o run_params.exe
	./run_params.exe

consistency_test: vmath.c geometry.c metropolis.c init_config.c observables.c
	gcc consistency_test.c -lm -lgsl structs.h vmath.c geometry.c metropolis.c init_config.c observables.c  -O3  -o cons_test.out
	./cons_test.out
