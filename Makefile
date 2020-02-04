main: geometry.c vmath.c metropolis.c init_config.c
	gcc main.c -lm geometry.c vmath.c metropolis.c init_config.c observables.c -L/usr/local/lib -lgsl -o main.exe
	./main.exe

run_params: geometry.c vmath.c metropolis.c init_config.c observables.c
	gcc run_params.c -lm geometry.c vmath.c metropolis.c init_config.c observables.c -L/usr/local/lib -lgsl -o run_params.exe
	./run_params.exe
