#include "LifetimeFit.h"

#include <cmath>

#include "Event.h"
#include "ParticleReco.h"

// constructor
LifetimeFit::LifetimeFit( double min, double max ):
    mass_min( min ), mass_max( max ),
    //set cumulative variables to 0
    n_events( 0 ) {
}


// destructor
LifetimeFit::~LifetimeFit() {
}


// add data from a new event
bool LifetimeFit::add( const Event& ev ) {

    // get ParticleReco instance to compute mass
    static ParticleReco* particle_reco = ParticleReco::instance();
    double mass = particle_reco->Mass();

    // check if mass is in range, and return true
    // increase counter and update sums
    if( (mass_min < mass) && (mass < mass_max) ){
        n_events++;
        return true;
    }
    // else return false
    else return false;

}


// compute mean and rms
void LifetimeFit::compute() {
    return;
}


// return number of selected events
unsigned int LifetimeFit::NEvents() const{
    return n_events;
};