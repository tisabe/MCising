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

#define num_params 18

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
    //int num_params = 12;
    double beta_arr[num_params] = {0.1,0.3,0.5,0.7,0.1,0.3,0.5,0.7,0.1,0.3,0.5,0.7,0.4,0.425,0.43,0.435,0.44,0.45};
    double B_arr[num_params] = {0.0,0.0,0.0,0.0,0.01,0.01,0.01,0.01,0.03,0.03,0.03,0.03,0.0,0.0,0.0,0.0,0.0,0.0};
    // NOTE: for seed 42 in init_config, 45 in step_mc, beta=0.7, B=0.0, intersting stuff happens

    char *s = malloc(params.L * sizeof(char));
    double *h_vec = malloc(steps * sizeof(double));
    double *m_vec = malloc(steps * sizeof(double));

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
            step_mc(s, r, params); // do the monte-carlo step with a different seed
        }
        // generate the file name
        FILE *obs_file;
        char str[80];
        //char str2[80];
        sprintf(str, "params_out/out%d.txt", ip);
        obs_file = fopen(str,"w");
        for(long int i = 0; i < steps; i++) {
            fprintf(obs_file, "%ld\t%e\t%e\n", i, h_vec[i], m_vec[i]);
        }

        fclose(obs_file);
        gsl_rng_free(r);

    }
    printf("finished calculations\n");

    return 0;
}
