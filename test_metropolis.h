#ifndef TEST_METROPOLIS_H
#define TEST_METROPOLIS_H

#include "structs.h"
#include <gsl/gsl_rng.h>


void step_mc(char *s, double diff_H_test, gsl_rng * r, parameters params);

#endif
