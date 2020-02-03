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

  long int C = 100; //50000

  params.L = ipow(params.N,params.D);

  char *s = malloc(params.L * sizeof(char));
  double *hamiltonian_vec = malloc(params.L * sizeof(double));
  double *magnetization_vec = malloc(params.L * sizeof(double));
  long int *neighbour = malloc(2*params.D*params.L*sizeof(long int));

  nneighbour_init(neighbour, params.N, params.D);

  FILE *config_file;
  config_file = fopen("config_output.txt","w");

  init_config_rng(s, params);

  int prog = 0;

  for(long int i = 0; i < C; i++){
    //if(i % 1000 == 0){
      for(long int j = 0; j < params.L; j++){
        fprintf(config_file, "%d\t", s[j]);
      }
      fprintf(config_file, "\n");
      if(i%10 == 0){printf("%i proc. progress\n",prog); prog += 10;}
    //}
      step_mc(s, params.B, params.beta, params.N, params.D);  //params
      hamiltonian(hamiltonian_vec, s, params, neighbour, i);
      magnetization(magnetization_vec, s, params, i);
  }

  fclose(config_file);
  free(s);

  return 0;
}
