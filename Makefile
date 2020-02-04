main: geometry.c vmath.c metropolis.c init_config.c
	gcc main.c -lm geometry.c vmath.c metropolis.c init_config.c observables.c -L/usr/local/lib -lgsl -o main.exe
	./main.exe
