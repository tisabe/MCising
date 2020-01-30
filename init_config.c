#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>


#include "structs.h"
/*********************************************************************************
this file contains three different functions to create starting configuration of size L declared in params

init_config1: set entries using the rand() function from C
init_config2: set entries using the rng function gsl
init_config3: alternate the entries between 1 and -1

**********************************************************************************/
void init_config1(char *configuration, parameters params){
	long int L= params.L;
	char *configuration = malloc(params.L * sizeof(char));

    for (long int i=0; i<L; i++) {
        if((double) rand()/RAND_MAX<0.5){
            configuration[i]=1;
        }
        else if((double) rand()/RAND_MAX>0.5){
            configuration[i]=-1;
        }
    }
}

void init_config2(char *configuration, parameters params){
	long int L= params.L;
	gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
	long int r_max = gsl_rng_max(r)
	char *configuration = malloc(params.L * sizeof(char));

    for (long int i=0; i<L; i++) {
        if(unsigned long int gsl_rng_get(r)/r_max<0.5){
            configuration[i]=1;
        }
        else if(unsigned long int gsl_rng_get(r)/r_max>0.5){
            configuration[i]=-1;
        }
    }
}

void init_config3(char *configuration, parameters params){
	long int L= params.L;
	char *configuration = malloc(params.L * sizeof(char));

    for (long int i=0; i<L; i=i+2) {
        init_config[i]=1;
    }
    for (long int i=1; i<L; i=i+2) {
        configuration[i]=-1;
    }
}
