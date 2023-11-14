#include <iostream>
#include <fstream>
#include <cmath>

#include "MassMean.h"

struct Event;

const Event* read( std::ifstream& file );
void dump( const Event& ev );


int main( int argc, char *argv[] ){
    // open input file
    const char* name = argv[1];
    std::ifstream file( name );
    
    // event
    const Event* ev;

    // K0 and Lambda0 objects
    MassMean kay0( 0.495, 0.500 );
    MassMean lam0( 1.115, 1.116 );

    // loop over events
    while( (ev = read( file )) != nullptr ){
        dump( *ev );
        kay0.add( *ev );
        lam0.add( *ev );
        delete ev;
    }

    // compute results
    kay0.compute();
    lam0.compute();

    // print results
    std::cout << std::endl;
    std::cout << "K0:\t\t" << kay0.MassAvg() << ' '
                           << kay0.MassRms() << '\t'
                           << kay0.NEvents() << std::endl;
    
    std::cout << "Lambda0:\t" << lam0.MassAvg() << ' '
                              << lam0.MassRms() << '\t'
                              << lam0.NEvents() << std::endl;


    return 0;
    
}