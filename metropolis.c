#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"


void step_mc(char *s, unsigned long int seed, parameters params) {
    static long int *neighbours = NULL;
    static long int prev_N, prev_D, L;

    gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
    double r_max = gsl_rng_max(r);

    /* We want to set a seed for the rng, but only when the seed has changed.
    We do not want to set the seed every function call, so that the sequence
    of random numbers is different for each step, but repeatable with the same seed.
    WARNING: When the seed is unchanged, a different sequence of numbers will be used.
    To achieve the same steps within one instance (lifetime of the static variable),
    reset the seed to another number and then back.
    This is likely not very well explained so for questions write at bechtelt@physik.hu-berlin.de */
    static unsigned long int prev_seed; // the previous seed needs to be saved persistently
    if (prev_seed != seed) { // check if the seed has changed from previous call
        gsl_rng_set(r, seed); // set the seed for the rng
        prev_seed = seed;
    }


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
