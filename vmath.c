/* this file will contain all math functions for vector operations
required in the QPP problem*/

#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structs.h"

long int ipow(long int base, unsigned int exp) {
/*integer power function so math does not need to be included*/
/*peer reviewed by frohlofl*/
    int result = 1;
    for (unsigned int i=0; i<exp; i++){
      result *= base;
    }
    return result;
}

double complex dot_product(double complex *v, double complex *w, long int L) {
/*returns the complex dot product of two vectors v, w*/
  double complex sprod = 0.0;
  for(long int i=0; i<L; i++) {
    sprod+=(~(v[i]))*w[i];
  }
  return sprod;
}

void scalar_vec(double complex *out, double complex *vec, double complex s, long int L) {
/*returns the product of a scalar s and a vector vec*/
  for(long int i=0; i<L; i++) {
    out[i] = s*vec[i];
  }
}

void mul_compl_vec_real_scal(double complex *out, double complex *vec, double s, long int L) {
/*same as previous function but with real scalar*/
  for(long int i=0; i<L; i++){
    out[i] = s*vec[i];
  }
}

void mul_element(double complex *out, double complex *w, double complex *v, long int L) {
/*returns the elementwise multiplication of two complex vectors v, w*/
  for(long int i=0; i<L; i++) {
    out[i] = v[i]*w[i];
  }
}

void add_vec(double complex *out, double complex *w, double complex *v, long int L) {
/*returns the sum of two complex vectors v, w*/
  for(long int i=0; i<L; i++) {
    out[i] = v[i]+w[i];
  }
}

void sub_vec(double complex *out, double complex *v, double complex *w, long int L) {
/*returns the difference of two complex vectors v, w*/
  for(long int i=0; i<L; i++) {
    out[i] = v[i]-w[i];
  }
}

void assign_vec(double complex *out, double complex *in, long int L) {
/*copy the values of in to values of out*/
  for(long int i=0; i<L; i++) {
    out[i] = in[i];
  }
}

void set_zero(double complex *in, long int L) {
/*set all values of in to zero*/
  for(long int i=0; i<L; i++) {
    in[i] = 0.0;
  }
}

double abs_vec(double complex *in, long int L) {
  return sqrt(creal(dot_product(in, in, L)));
}

long int fact(int n){
    long int res = 1;
    for(int i=1; i<=n; i++){
        res *= i;
    }
    return res;
}

void mat_vec_mul(double complex *out, double complex *mat, double complex *vec, long int N){ //N is the length of the vector
    set_zero(out, N);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            out[i] += mat[N*i+j] * vec[j];
        }
    }
}

void hermtransp_quadr_matrix(double complex *out, double complex *in, long int N){ //N is the length of one size
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            out[i*N+j] = (~(in[j*N+i]));
        }
    }
}
