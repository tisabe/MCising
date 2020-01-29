#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"

double rand_f() {
    // returns a random double in the interval [0,1)
    return (double)rand()/RAND_MAX; // may need to be replaced by a better RNG
}

void step_mc(char *s, double B, double beta, long int N, unsigned int D) {
    static long int *neighbours = NULL;
    static long int prev_N, prev_D, L;

    //Check if geometry parameters have changed. If yes, free, reallocate and recalculate the next neighbours the array again
    if((neighbours == NULL) || (prev_N != N) || (prev_D != D)){
        free(neighbours);
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
        double p = exp(-1*diff_H);

        // if p is greater than one, the energy is smaller with flipped spin,
        // so the spin is flipped
        if (p >= 1) {
            s[i] *= -1;
        } else if (rand_f < p) { // if p is smaller than 1, flip spin with probability p
            s[i] *= -1;
        }
    }
    // after iterating over all lattice points, the MC step is completed
}
