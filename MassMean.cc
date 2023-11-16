#include "MassMean.h"
#include "Event.h"

#include <cmath>

double Mass( const Event& ev );


// constructor
MassMean::MassMean( double min, double max ):
    mass_min( min ), mass_max( max ),
    //set cumulative variables to 0
    n_events( 0 ), mass_sum( 0 ), mass_2_sum( 0 ) {
}


// destructor
MassMean::~MassMean() {
}


// add data from a new event
void MassMean::add( const Event& ev ) {

    double mass = -1;

    // compute mass only if there are exactly 2 particles
    // could check as well if product of charges is -1
    // would not require Mass() to check it again later
    if( ev.NParticles() == 2 ) mass = Mass( ev );

    // check if mass is in range
    // increase counter and update sums
    if( (mass_min < mass) && (mass < mass_max) ){
        n_events++;
        mass_sum += mass;
        mass_2_sum += pow( mass, 2 );
        return;
    }
    // else do nothing
    else return;

}


// compute mean and rms
void MassMean::compute() {

    mass_avg = mass_sum / n_events;
    double mass_rms_temp = ( mass_2_sum / n_events ) - pow( mass_avg, 2 );
    mass_rms = ( mass_rms_temp > 0 ? sqrt(mass_rms_temp) : 0.0 );

}


// return number of selected events
unsigned int MassMean::NEvents() const{
    return n_events;
};


// return mean and rms
double MassMean::MassAvg() const{
    return mass_avg;
};
double MassMean::MassRms() const{
    return mass_rms;
};

