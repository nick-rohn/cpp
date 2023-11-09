#include <iostream>

#include "Particle.h"
#include "Event.h"

void dump( const Event& ev ){

    // write event data
    std::cout << ev.ev_number << ' '
            << ev.x_decay << ' ' << ev.y_decay << ' ' << ev.z_decay
            << ' ' << ev.n_particles;
    
    // write particles
    for ( int i = 0; i < ev.n_particles; ++i ){
        std::cout << ' '
                  << ev.particles[i]->charge << ' '
                  << ev.particles[i]->p_x << ' '
                  << ev.particles[i]->p_y << ' '
                  << ev.particles[i]->p_z;
    }

    std::cout << std::endl;

    return;

}