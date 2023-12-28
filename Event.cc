#include "Event.h"

#include <vector>

// constructor
Event::Event( u_int id, double x, double y, double z ):
    ev_number( id ), x_decay( x ), y_decay( y ), z_decay( z ) {
    
    // allocate a buffer for particle pointers
    particles.reserve( 10 );

}


// destructor
Event::~Event() {

    // delete all the particle pointers
    for( u_int i = 0; i < particles.size(); ++i ) delete particles[i];

}


void Event::Add( int charge, double p_x, double p_y, double p_z ) {

    // don't need this anymore, vector can resize
//    if( n_particles >= max_n_part) return;

    // create the new particle and fill with data
    Particle* p = new Particle;
    p->charge = charge;
    p->p_x = p_x;
    p->p_y = p_y;
    p->p_z = p_z;

    // store the new particle pointer in the vector
    particles.push_back( p );

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
    return particles.size();
}


// get particle
const Event::Particle* Event::GetParticle( u_int i ) const {

    // check if index is within the number of particles
    if( i < particles.size() ) return particles[i];
    else return nullptr;

}

