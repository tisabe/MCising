#ifndef STRUCTS_H
#define STRUCTS_H

#include <complex.h>

//typedef struct parameters_tag parameters;
struct parameters_tag;

typedef struct parameters_tag {
    long int N; // length of each axis, number of points along each axis
    unsigned int D; // number of dimensions
    long int L; // length of whole array
    double beta; // parameter of inverse temperature beta=1/(k_B*T)
    double B; // magnetic field variable
} parameters /*name to reference struct*/;

#endif
