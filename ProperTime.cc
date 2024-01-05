#include "ProperTime.h"

#include <iostream>
#include <cmath>

#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include "ParticleReco.h"
#include "util/include/Singleton.h"
#include "util/include/LazyObserver.h"

using namespace std;


// constructor
ProperTime::ProperTime() {
}


// destructor
ProperTime::~ProperTime() {
}


// recompute tag informations for new event
void ProperTime::update( const Event& ev ) {

    // get ParticleReco instance
    static ParticleReco* part_reco = ParticleReco::instance();

    // get data about reconstructed particle
    double mass = part_reco->Mass();
    double e_tot = part_reco->Energy();
    double p_tot = sqrt( pow( e_tot,2 ) - pow( mass,2 ) );
    double dist = sqrt( pow( ev.XDecay(),2 ) + 
                        pow( ev.YDecay(),2 ) + 
                        pow( ev.ZDecay(),2 ) );

    // compute proper time
    time = dist * mass / ( p_tot * Constants::light_speed );

    return;
}


// return particle mass
double ProperTime::DecayTime(){
    // check for new event and return result
    check();
    return time;
}