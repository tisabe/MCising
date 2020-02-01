#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"

double rand_f() {
   	// returns a random double in the interval [0,1)
	// directly put this into the main code for optimization purposes

	gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
	double r_max = gsl_rng_max(r);
	double random_number = gsl_rng_get (r)/r_max;
	gsl_rng_free(r);

   	return random_number;
}

void step_mc(char *s, double B, double beta, long int N, unsigned int D) {
    static long int *neighbours = NULL;
    static long int prev_N, prev_D, L;

    //Check if geometry parameters have changed. If yes, free, reallocate and recalculate the next neighbours the array again
    if((neighbours == NULL) || (prev_N != N) || (prev_D != D)){
        if(neighbours != NULL){free(neighbours);}
        L = ipow(N, D);
        neighbours = malloc(2*D*L*sizeof(long int));
        nneighbour_init(neighbours, N, D);
        prev_N = N;
        prev_D = D;
    }

    //Loop over all points i in the lattice
    for(long int i=0; i<L; i++){

        double diff_H = 0;

        // loop over all dimensions, for there are 2 next neighbours of point i in each dimension
        for(int d=0; d<D; d++){
            diff_H += s[i]*(s[neighbours[2*(i*D+d)]]+s[neighbours[2*(i*D+d)+1]]);
        }
        diff_H = 2*(diff_H + B*s[i]);

        // now calculate p as exponential
        double p = exp(-1*beta*diff_H);

        // if p is greater than one, the energy is smaller with flipped spin,
        // so the spin is flipped
        if (p >= 1) {
            s[i] *= -1;
        } else if (rand_f() < p) { // if p is smaller than 1, flip spin with probability p
            s[i] *= -1;
        }
    }
    // after iterating over all lattice points, the MC step is completed
}

double auto_corr(double *s, long int N, long int k, double mu) {

	double res = 0.;
	for(long int i=0; i<(N-k); i++) {
		res += (s[i]-mu) * (s[i+k]-mu);
	}

	return res/(N-k);
}
