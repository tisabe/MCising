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

  long int C = 50000; //50000

  params.L = ipow(params.N,params.D);

  char *s = malloc(params.L * sizeof(char));
  double *hamiltonian_vec = malloc(C * sizeof(double));
  double *magnetization_vec = malloc(C * sizeof(double));

  FILE *config_file;

  config_file = fopen("config_output.txt","w");

  //init_config_alternate(s, params);
  init_config_rng(s, 42, params);

  long int prog = 0;

  for(long int i = 0; i < C; i++){
    if(i % 1000 == 0){
      for(long int j = 0; j < params.L; j++){
        fprintf(config_file, "%d\t", s[j]);
      }
      fprintf(config_file, "\n");
      if(i%1000 == 0){printf("Saving Montecarlo step no. %ld\n",prog); prog += 1000;}
    }
      step_mc(s, 42, params);
      hamiltonian_vec[i]=hamiltonian(s, params);
      magnetization_vec[i]=magnetization(s, params);
  }

  FILE *obs_file;
  obs_file = fopen("obs_output.txt","w");
  for(long int i = 0; i < C; i++){
      fprintf(obs_file, "%ld\t%e\t%e\n", i, hamiltonian_vec[i], magnetization_vec[i]);
  }
  fclose(obs_file);
  fclose(config_file);

  free(s);
  free(hamiltonian_vec);
  free(magnetization_vec);

  printf("finished\n");

  return 0;
}
