#include <iostream>

#include "Event.h"

using namespace std;

void dump( const Event& ev ){

    // write event data
    cout << ev.EventNumber() << ' '
         << ev.XDecay() << ' ' << ev.YDecay() << ' ' << ev.ZDecay() << ' ' 
         << ev.NParticles();
    
    // write particles
    for ( Event::u_int i = 0; i < ev.NParticles(); ++i ){
        Event::part_ptr p = ev.GetParticle(i);
        cout << ' '
             << p->charge << ' '
             << p->p_x << ' ' << p->p_y << ' ' << p->p_z;
    }

    cout << endl;

    return;

}