#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"

void hamiltonian(double *out, char *in, parameters params, long int *neighbour, long int iteration){
    double hamilton_config = 0;
    for (long int i=0; i<params.L; i++){
        hamilton_config += (-1)*params.B*in[i];
        for (int j=0; j<params.D; j++){
            hamilton_config += (-1)*in[i]*(in[neighbour[2*i*params.D+2*j]]+in[neighbour[2*i*params.D+2*j+1]]);
        }
    }
    out[iteration]=hamilton_config;
}

void magnetization(double *out, char *in, parameters params, long int iteration){
    double magnetization_config = 0;
    for (long int i=0; i<params.L; i++){
        magnetization_config += in[i];
    }
    out[iteration]=magnetization_config;
}
