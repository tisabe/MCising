#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"


void step_mc(char *s, parameters params) {
    static long int *neighbours = NULL;
    static long int prev_N, prev_D, L;
    
    gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
    double r_max = gsl_rng_max(r);
    
    //Check if geometry parameters have changed. If yes, free, reallocate and recalculate the next neighbours the array again
    if((neighbours == NULL) || (prev_N != params.N) || (prev_D != params.D)){
        if(neighbours != NULL){free(neighbours);}
        neighbours = malloc(2*params.D*params.L*sizeof(long int));
        nneighbour_init(neighbours, params.N, params.D);
        prev_N = params.N;
        prev_D = params.D;
    }

    //Loop over all points i in the lattice
    for(long int i=0; i<params.L; i++){

        double diff_H = 0;

        // loop over all dimensions, for there are 2 next neighbours of point i in each dimension
        for(int d=0; d<params.D; d++){
            diff_H += s[i]*(s[neighbours[2*(i*params.D+d)]]+s[neighbours[2*(i*params.D+d)+1]]);
        }
        diff_H = 2*(diff_H + params.B*s[i]);

        // now calculate p as exponential
        double p = exp(-1*params.beta*diff_H);

        // if p is greater than one, the energy is smaller with flipped spin,
        // so the spin is flipped
        if (p >= 1) {
            s[i] *= -1;
        } else if (gsl_rng_get (r)/r_max < p) { // if p is smaller than 1, flip spin with probability p
            s[i] *= -1;
        }
    }
    // after iterating over all lattice points, the MC step is completed
    gsl_rng_free(r);
}

double auto_corr(double *s, long int N, long int k, double mu) {

	double res = 0.;
	for(long int i=0; i<(N-k); i++) {
		res += (s[i]-mu) * (s[i+k]-mu);
	}

	return res/(N-k);
}
