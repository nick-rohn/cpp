#include "Utilities.h"

#include <cmath>

// compute energy from momentum x,y,z components and invariant mass
double Utilities::Energy( double p_x, double p_y, double p_z, double inv_mass ){
    double p_sum_2 = pow( p_x, 2 ) + pow( p_y, 2 ) + pow( p_z, 2 );
    double energy = sqrt( p_sum_2 + pow( inv_mass, 2 ) );
    return energy;
}

// compute invariant mass from momentum x,y,z components and energy
double Utilities::InvariantMass( double p_x, double p_y, double p_z, double energy){
    double p_sum_2 = pow( p_x, 2 ) + pow( p_y, 2 ) + pow( p_z, 2 );
    double inv_mass = sqrt( pow( energy, 2 ) - p_sum_2 );
    return inv_mass;
}