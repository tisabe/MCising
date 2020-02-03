#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>


#include "structs.h"
/*********************************************************************************
this file contains three different functions to create starting configuration of size L declared in params

init_config_rand: set entries using the rand() function from C
init_config_rng: set entries using the rng function from gsl	https://www.gnu.org/software/gsl/doc/html/rng.html
init_config_alternate: alternate the entries between 1 and -1
init_config_up: all entries are +1
init_config_down: all entries are -1
**********************************************************************************/
void init_config_rand(char *configuration, parameters params){
	long int L= params.L;

    for (int i=0; i<L; i++) {
        configuration[i] = 2*(rand() % 2) - 1;
    }
}

void init_config_rng(char *configuration, parameters params){
	long int L= params.L;
	gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
	//double r_max = gsl_rng_max(r);

    	for (int i=0; i<L; i++) {
		configuration[i] = 2*(gsl_rng_get(r) % 2) - 1;
    	}
    	gsl_rng_free(r);
}

void init_config_alternate(char *configuration, parameters params){
	long int L= params.L;

    for (int i=0; i<L; i=i+2) {
        configuration[i]=1;
    }
    for (long int i=1; i<L; i=i+2) {
        configuration[i]=-1;
    }
}

void init_config_up(char *configuration, parameters params){
	long int L= params.L;

    for (int i=0; i<L; i++) {
            configuration[i]=1;
    }
}

void init_config_down(char *configuration, parameters params){
	long int L= params.L;

    for (int i=0; i<L; i++) {
            configuration[i]=-1;
    }
}

/*void main(){
    long int L= 100;
	char *configuration = malloc(L * sizeof(char));
    gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
	double r_max = gsl_rng_max(r);

    for (int i=0; i<L; i++) {
		configuration[i] = 2*(gsl_rng_get(r) % 2) - 1;
        printf("%d \n",configuration[i]);
    	}


	gsl_rng_free(r);
    free(configuration);
}*/
