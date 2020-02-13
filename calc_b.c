#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"


double calc_b(char *s, parameters params) {
    static long int *neighbours = NULL;
    static long int prev_N, prev_D, L;

    //Check if geometry parameters have changed. If yes, free, reallocate and recalculate the next neighbours the array again
    if((neighbours == NULL) || (prev_N != params.N) || (prev_D != params.D)){
        if(neighbours != NULL){free(neighbours);}
        neighbours = malloc(2*params.D*params.L*sizeof(long int));
        nneighbour_init(neighbours, params.N, params.D);
        prev_N = params.N;
        prev_D = params.D;
    }
    diff_H_test = 0;
    //Loop over all points i in the lattice
    for(long int i=0; i<params.L; i++){

        double diff_H = 0;

        // loop over all dimensions, for there are 2 next neighbours of point i in each dimension
        for(int d=0; d<params.D; d++){
            diff_H += s[i]*(s[neighbours[2*(i*params.D+d)]]+s[neighbours[2*(i*params.D+d)+1]]);
        }
        
        diff_H_test += diff_H + params.B*s[i];
        
    }
    return diff_H_test;
}
