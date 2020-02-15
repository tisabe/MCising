#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"

/*This function calculates the the hamiltonian of a given spin configuration:

    char *in: pointer to the given spin configuration
    parameter params: struct containing the information of the system

    returns: double containing the energy of the spin configuration
*/
double hamiltonian(char *in, parameters params){
  //initialisation of the next neighbour array and check for consistency with system parameters
  static long int *neighbour = NULL;
  static long int prev_N, prev_D, L;
  if((neighbour==NULL) || (prev_N != params.N) || (prev_D != params.D)){
    free(neighbour);
	   L = ipow(params.N, params.D);
  	neighbour = malloc(2*params.D*L*sizeof(long int));
  	nneighbour_init(neighbour, params.N, params.D);
  	prev_N = params.N;
  	prev_D = params.D;
  }
  //calculation of the energy by summation over every spin
  double hamilton_config = 0;
  for (long int i=0; i<params.L; i++){
      hamilton_config += (-1)*params.B*in[i];
      for (int j=0; j<params.D; j++){
          hamilton_config += (-1)*in[i]*in[neighbour[2*i*params.D+2*j+1]];
      }
  }
  return hamilton_config;
}

/*This function calculates the the magnetization of a given spin configuration:

    char *in: pointer to the given spin configuration
    parameter params: struct containing the information of the system

    returns: double containing the magnetization of the spin configuration
*/
double magnetization(char *in, parameters params){
    //calculation of the magnetization by summation of all spin values
    double magnetization_config = 0;
    for (long int i=0; i<params.L; i++){
        magnetization_config += in[i];
    }
    return magnetization_config;
}


double auto_corr(double *obs, long int N, long int k, double mu) {

	double res = 0.;
	for(long int i=0; i<(N-k); i++) {
		res += (obs[i]-mu) * (obs[i+k]-mu);
	}

	return res/(N-k);
}
