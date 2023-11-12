#include <iostream>
#include <fstream>
#include <cmath>

struct Event;

const Event* read( std::ifstream& file );
void dump( const Event& ev );
void clear ( const Event* ev );
bool add( const Event& ev,
          double mass_min, double mass_max,
          double& inv_mass_sum, double& mass_2_sum);


int main( int argc, char *argv[] ){
    // open input file
    const char* name = argv[1];
    std::ifstream file( name );
    
    // event
    const Event* ev;

    // cumulative variables
    int n_events = 0;
    double inv_mass_sum, mass_2_sum;
    inv_mass_sum = mass_2_sum = 0;

    // loop over events
    while( (ev = read( file )) != nullptr ){
        dump( *ev );
        if( add( *ev, 0.490, 0.505, inv_mass_sum, mass_2_sum )) ++n_events;
        // could create global variables for min and max masses, and simplify add() input
        // but in future versions they will change depending on the event
        clear( ev );
    }

    // compute mean mass and rms
    double mean_mass = inv_mass_sum / n_events;
    double rms_mass = ( mass_2_sum / n_events ) - ( mean_mass * mean_mass );
    rms_mass = ( rms_mass > 0 ? sqrt(rms_mass) : 0.0 );
    // could have used function to keep main simple, but it's not recursive and will be changed in the future

    // print results
    std::cout << std::endl;
    std::cout << mean_mass << " " << rms_mass << std::endl;
    std::cout << n_events << std::endl;

    return 0;
    
}