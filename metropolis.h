#ifndef METROPOLIS_H
#define METROPOLIS_H

#include "structs.h"
#include <gsl/gsl_rng.h>


void step_mc(char *s, gsl_rng * r, parameters params);
double calc_b(char *s, parameters params);

#endif
