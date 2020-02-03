#include "structs.h"

void hamiltonian(double *out, char *in, parameters params, long int *neighbour, long int iteration);
void magnetization(double *out, char *in, parameters params, long int iteration);
double auto_corr(double *obs, long int N, long int k, double mu);
