#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"
#include "metropolis.h"
#include "init_config.h"
#include "observables.h"

int main(){

  parameters params;

  params.N = 100;
  params.D = 2;
  params.beta = 0.5;
  params.B = 0.01;

  long int C = 50; //50000

  params.L = ipow(params.N,params.D);

  char *s = malloc(params.L * sizeof(char));
  double hamiltonian_vec = malloc(params.L * sizeof(double));
  double magnetization_vec = malloc(params.L * sizeof(double));
  long int neighbour = malloc(2*D*L*sizeof(long int));

  nneighbour_init(neighbour, params.N, params.D)

  FILE *config_file;
  config_file = fopen("config_output.txt","w");

  init_config1(s, params);

  for(long int i = 0; i < C; i++){
    //if(i % 1000 == 0){
      for(long int j = 0; j < params.L; j++){
        fprintf(config_file, "%d\t", s[j]);
      }
      fprintf(config_file, "\n");
      printf("Configuration saved\n");
    //}
      step_mc(s, params.B, params.beta, params.N, params.D);  //params
      hamiltonian(hamiltonian_vec, s, neighbour, params.B, params.N, params.D, i);
      magnetization(magnetization_vec, s, params.N, params.D, i);
  }

  fclose(config_file);
  free(s);

  return 0;
}
