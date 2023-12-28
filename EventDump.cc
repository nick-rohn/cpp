#include "EventDump.h"

#include <iostream>

#include "Event.h"

using namespace std;


EventDump::EventDump() {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::BeginJob() {
  return;
}


// function to be called at execution end
void EventDump::EndJob() {
  return;
}


// function to be called for each event
void EventDump::Process( const Event& ev ) {

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

