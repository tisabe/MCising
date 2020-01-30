#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double average(double *in, long int N, long int n_th){
	double out = 0;
	for (long int i=n_th; i<N; i++){
		out += in[i];
	}
	out = out/(N-n_th);
	return out;
}
