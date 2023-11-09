#include "Event.h"
#include "Particle.h"

void clear ( const Event* ev ){

    // delete particles
    for( int i = 0; i < ev->n_particles; ++i ) delete ev->particles[i];

    // delete array
    delete[] ev->particles;

    //delete evemt
    delete ev;

    return;

}