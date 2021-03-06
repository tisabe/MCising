#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structs.h"
#include "geometry.h"
#include "vmath.h"
#include "init_config.h"
#include "observables.h"

/*This function tests the hamiltonian function using knowm analytical solutions*/
int main() {
    printf("starting test...\n");
    parameters params;

    params.N = 100;
    params.D = 3;
    params.B = 0.01;
    params.L = ipow(params.N,params.D);

    char *s = malloc(params.L * sizeof(char));

    init_config_up(s, params); // spin configuration with all spins up

    double Hamiltonian_function_up=hamiltonian(s, params);
    double Hamiltonian_analytical_up= -params.L * params.D - params.L * params.B; //analytical solution for all spin up as described in python notebook, but number of spins is L

    double abs_err_up=Hamiltonian_function_up-Hamiltonian_analytical_up; //absolute error of the all spin up configuration in comparison with analytical solution
    double rel_err_up=abs_err_up/Hamiltonian_analytical_up;//error relative to analytical solution

    init_config_down(s, params); // spin configuration with all spins down

    double Hamiltonian_function_down=hamiltonian(s, params);
    double Hamiltonian_analytical_down= -params.L * params.D + params.L * params.B; //analytical solution for all spin down as described in python notebook, but number of spins is L

    double abs_err_down= Hamiltonian_function_down - Hamiltonian_analytical_down; //absolute error of the all spin down configuration in comparison with analytical solution
    double rel_err_down=abs_err_down/Hamiltonian_analytical_down;//error relative to analytical solution

    init_config_alternate(s, params); // spin configuration with alternating spins

    double Hamiltonian_function_alternate=hamiltonian(s, params);
    double Hamiltonian_analytical_alternate= -params.L * (params.D-2); //analytical solution for alternating spins as described in python notebook, but number of spins is L

    double abs_err_alternate=Hamiltonian_function_alternate - Hamiltonian_analytical_alternate; //absolute error of alternating spin configuration in comparison with analytical solution
    double rel_err_alternate=abs_err_alternate/Hamiltonian_analytical_alternate;//error relative to analytical solution

    printf(" absolute error up configuration: %e \t relative error up configuration: %e \n absolute error down configuration: %e \t relative error down configuration: %e\n absolute error alternating configuration: %e \t relative error alternating configuration: %e\n",abs_err_up,rel_err_up,abs_err_down,rel_err_down,abs_err_alternate,rel_err_alternate);
    return 0;
}
