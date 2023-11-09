#include <iostream>
#include <fstream>

#include "Particle.h"
#include "Event.h"

const Event* read( std::ifstream& file ){

    // event pointer and identifier
    Event* ev;
    int id;

    // try to read input file
    // on success create new event
    if ( file >> id) ev = new Event;
    // on failure return null pointer
    else return nullptr;

    // set event number
    ev->ev_number = id;

    // read and store decay coordinates
    double x, y, z;
    file >> x >> y >> z;
    ev->x_decay = x;
    ev->y_decay = y;
    ev->z_decay = z;

    // read and store number of particles
    int n;
    file >> n;
    ev->n_particles = n;
    
    // allocate array for particles
    ev->particles = new Particle*[n];

    //create particle pointer and store data
    int charge;
    double p_x, p_y, p_z;
    for( int i = 0; i < n; ++i ){
        Particle* p = new Particle;
        file >> charge >> p_x >> p_y >> p_z;
        p->charge = charge;
        p->p_x = p_x;
        p->p_y = p_y;
        p->p_z = p_z;
        ev->particles[i] = p;
    }

    return ev;
}