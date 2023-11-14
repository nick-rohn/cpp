#include <iostream>
#include <fstream>

#include "Event.h"

const Event* read( std::ifstream& file ){

    // event pointer and identifier
    Event* ev;
    int id;

    // try to read input file
    // on failure return null pointer
    if( !(file >> id) ) return nullptr;

    double x, y, z;
    file >> x >> y >> z;
    ev = new Event( id, x, y, z );

    // read number of particles (could have used in the constructor)
    int n;
    file >> n;
    
    //read and store particles
    int charge;
    double p_x, p_y, p_z;
    for( int i = 0; i < n; ++i ){
        file >> charge >> p_x >> p_y >> p_z;
        ev->Add( charge, p_x, p_y, p_z );
    }

    return ev;
}