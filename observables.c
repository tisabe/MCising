#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"

void hamiltonian(double *out, char *in, long int *neighbour, double B, long int N, unsigned int D, long int iteration){
    double hamilton_config = 0;
    long int L=ipow(N,D);
    for (long int i=0; i<L; i++){
        hamilton_config += (-1)*B*in[i];
        for (int j=0; j<D; j++){
            hamilton_config += (-1)*in[i]*(in[neighbour[2*i*D+2*j]]+in[neighbour[2*i*D+2*j+1]]);
        }
    }
    out[iteration]=hamilton_config;
}

void magnetization(double *out, char *in, long int N, unsigned int D, long int iteration){
    double magnetization_config = 0;
    long int L=ipow(N,D);
    for (long int i=0; i<L; i++){
        magnetization_config += in[i];
    }
    out[iteration]=magnetization_config;
}
