#include <cmath>

#include "Event.h"

double Mass( const Event& ev );

bool add( const Event& ev,
          double mass_min, double mass_max,
          double& inv_mass_sum, double& mass_2_sum){
    
    double mass = -1;

    // compute mass only if there are exactly 2 particles
    // could check as well if product of charges is -1
    // would not require Mass() to check it again later
    if( ev.n_particles == 2 ) mass = Mass( ev );

    // check if mass is in range
    // update sums and return true
    if( (mass_min < mass) && (mass < mass_max) ){
        inv_mass_sum += mass;
        mass_2_sum += pow( mass, 2 );
        return true;
    }
    // else return false
    else return false;

}