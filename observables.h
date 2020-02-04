#include "structs.h"

double hamiltonian(char *in, parameters params, long int *neighbour);
double magnetization(char *in, parameters params);
double auto_corr(double *obs, long int N, long int k, double mu);
