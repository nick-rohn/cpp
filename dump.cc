#include <iostream>

#include "Event.h"

void dump( const Event& ev ){

    // write event data
    std::cout << ev.EventNumber() << ' '
              << ev.XDecay() << ' ' << ev.YDecay() << ' ' << ev.ZDecay() << ' ' 
              << ev.NParticles();
    
    // write particles
    for ( int i = 0; i < ev.NParticles(); ++i ){
        Event::part_ptr p = ev.GetParticle(i);
        std::cout << ' '
                  << p->charge << ' '
                  << p->p_x << ' ' << p->p_y << ' ' << p->p_z;
    }

    std::cout << std::endl;

    return;

}