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

  long int C = 5000; //50000

  params.L = ipow(params.N,params.D);

  char *s = malloc(params.L * sizeof(char));
  double *hamiltonian_vec = malloc(params.L * sizeof(double));
  double *magnetization_vec = malloc(params.L * sizeof(double));
  long int *neighbour = malloc(2*params.D*params.L*sizeof(long int));

  nneighbour_init(neighbour, params.N, params.D);

  FILE *config_file;

  config_file = fopen("config_output.txt","w");

  //init_config_alternate(s, params);
  init_config_rng(s, 42, params);

  long int prog = 0;

  for(long int i = 0; i < C; i++){
    if(i % 100 == 0){
      for(long int j = 0; j < params.L; j++){
        fprintf(config_file, "%d\t", s[j]);
      }
      fprintf(config_file, "\n");
      if(i%100 == 0){printf("Saving config no. %ld\n",prog); prog += 100;}
    }
      step_mc(s, 42, params);
      hamiltonian(hamiltonian_vec, s, params, neighbour, i);
      magnetization(magnetization_vec, s, params, i);
  }

  FILE *obs_file;
  obs_file = fopen("obs_output.txt","w");
  for(long int i = 0; i < C; i++){
      fprintf(obs_file, "%ld\t%e\t%e\n", i, hamiltonian_vec[i], magnetization_vec[i]);
  }
  fclose(obs_file);

  printf("finished\n");

  free(s);
  printf("last energy: %e\n", hamiltonian_vec[C-1]);

  free(hamiltonian_vec);
  free(magnetization_vec);

  fclose(config_file);

  return 0;
}
