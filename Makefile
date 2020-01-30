main: geometry.c vmath.c metropolis.c init_config.c
	gcc main.c -lm -lgsl geometry.c vmath.c metropolis.c init_config.c -o "main.exe"
	./main.exe
