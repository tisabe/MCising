#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <omp.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"
#include "metropolis.h"
#include "init_config.h"
#include "observables.h"

#define num_params 5

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

    double N_arr[num_params] = {10,20,50,100,200};

    long int steps = 50000;

    // we define the number of parameter sets that will be calculated and the parameters itself
    //int num_params = 12;
    // NOTE: for seed 42 in init_config, 45 in step_mc, beta=0.7, B=0.0, intersting stuff happens

    double *h_vec = malloc(steps * sizeof(double));
    double *m_vec = malloc(steps * sizeof(double));

    printf("starting loop\n");

    double time_start = 0.0;
    double time_end;
    time_start = omp_get_wtime();

    for(int ip=0; ip<num_params; ip++) { // loop over all parameter sets
        params.N = N_arr[ip];
        params.D = 2;
        params.L = ipow(params.N,params.D);
        char *s = malloc(params.L * sizeof(char));

        init_config_rng(s, 42, params); // every chain will be started from the same starting configuration
        params.beta = 0.5;
        params.B = 0.01;
        gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
        gsl_rng_set(r, float_to_uint(params.beta)+float_to_uint(params.B));

        printf("starting mc with params steps=%ld, N=%ld beta=%e, B=%e\n", steps, params.N,params.beta, params.B);

        static double time_start;
        time_start = omp_get_wtime();

        for(long int i=0; i<steps; i++) { // loop over steps
            h_vec[i] = hamiltonian(s, params);
            //printf("1\n");
            m_vec[i] = magnetization(s, params);
            //printf("2\n");
            step_mc_omp(s, r, params); // do the monte-carlo step with a different seed
        }
        time_end = omp_get_wtime() - time_start;
        printf("Parallel time elapsed: %e s\n", time_end);

        time_start = omp_get_wtime();

        for(long int i=0; i<steps; i++) { // loop over steps
            h_vec[i] = hamiltonian(s, params);
            //printf("1\n");
            m_vec[i] = magnetization(s, params);
            //printf("2\n");
            step_mc(s, r, params); // do the monte-carlo step with a different seed
        }
        time_end = omp_get_wtime() - time_start;
        printf("Serial time elapsed: %e s\n", time_end);

        gsl_rng_free(r);

    }
    printf("finished calculations\n");

    return 0;
}
