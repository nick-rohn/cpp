#include "Event.h"

// static variables
const Event::u_int Event::max_n_part = 10;

// constructor
// could have read in the constructor the number of particles
// this way we could create already the array with the right size
Event::Event( u_int id, double x, double y, double z ):
    ev_number( id ), x_decay( x ), y_decay( y ), z_decay( z ){
    
    //set counter to 0
    n_particles = 0;

    // allocate a buffer for particle pointers
    particles = new Particle*[max_n_part];

}


// destructor
Event::~Event() {
    // delete all the particle pointers
    for( u_int i = 0; i < n_particles; ++i ) delete particles[i];
    // delete the pointers array
    delete[] particles;
}


void Event::Add( int charge, double p_x, double p_y, double p_z ) {

    // check for the number of particles, if maximum reached do nothing and return
    if( n_particles >= max_n_part) return;

    // create the new particle and fill with data
    Particle* p = new Particle;
    p->charge = charge;
    p->p_x = p_x;
    p->p_y = p_y;
    p->p_z = p_z;

    // store the new particle pointer in the array and increase counter
    particles[n_particles] = p;
    n_particles++;

    return;

}


// get event id.
Event::u_int Event::EventNumber() const {
    return ev_number;
}


// get decay point coordinates
double Event::XDecay() const {
    return x_decay;
}

double Event::YDecay() const {
    return y_decay;
}

double Event::ZDecay() const {
    return z_decay;
}

// get number of particles
Event::u_int Event::NParticles() const {
    return n_particles;
}


// get particle
const Event::Particle* Event::GetParticle( u_int i ) const {

    // check if index is within the number of particles
    if( i >= n_particles ) return nullptr;
    else return particles[i];

}

