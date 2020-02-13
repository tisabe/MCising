#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"
#include "metropolis.h"
#include "init_config.h"
#include "observables.h"

#define num_params 1
// here we basically do the same thing as in run_params and print out the consistency check (called condition)
unsigned long int float_to_uint(double f) {
    if (f<0) {
        f *= -1.0;
    }
    while (f != (int)f) {
        f *= 10.0;
    }
    return (unsigned long int)f;
}

int main() {
    printf("starting sets...\n");
    parameters params;

    params.N = 100;
    params.D = 2;
    params.L = ipow(params.N,params.D);

    long int steps = 5000;

    // we define the number of parameter sets that will be calculated and the parameters itself
    // int num_params = 1;
    double beta_arr[num_params] = {0.1};
    double B_arr[num_params] = {0.0};
    // NOTE: for seed 2 in init_config, 45 in step_mc, beta=0.7, B=0.0, intersting stuff happens

    char *s = malloc(params.L * sizeof(char));
    double *h_vec = malloc(steps * sizeof(double));
    double *m_vec = malloc(steps * sizeof(double));

    double diff_H_test = 0;
    double condition = 0;
    double condition_sum = 0;
    printf("starting loop\n");

    for(int ip=0; ip<num_params; ip++) { // loop over all parameter sets

        init_config_rng(s, 42, params); // every chain will be started from the same starting configuration
        params.beta = beta_arr[ip];
        params.B = B_arr[ip];
        gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
        gsl_rng_set(r, float_to_uint(params.beta)+float_to_uint(params.B));

        printf("starting mc with params beta=%e, B=%e\n", params.beta, params.B);
        for(long int i=0; i<steps; i++) { // loop over steps
            h_vec[i] = hamiltonian(s, params);
            //printf("1\n");
            m_vec[i] = magnetization(s, params);
            //printf("2\n");
            diff_H_test = calc_b(s, params);
            step_mc(s, r, params); // do the monte-carlo step with a different seed
            
            condition = (h_vec[i] + params.B/2. * m_vec[i])+ diff_H_test/2.; //calculate the condition (difference between right and left side of the eq.) which should be 0
            condition_sum += condition; //sum over all conditions
            printf("difference %e\n", condition); 
        }
    printf("condition_sum is %e\n", condition_sum);

        gsl_rng_free(r);

    }
    printf("finished calculations\n");

    return 0;
}
