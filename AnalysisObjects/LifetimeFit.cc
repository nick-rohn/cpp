#include "AnalysisObjects/LifetimeFit.h"

#include <cmath>
#include <vector>

#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/ParticleReco.h"
#include "AnalysisObjects/ProperTime.h"
#include "AnalysisUtilities/QuadraticFitter.h"

// constructor
LifetimeFit::LifetimeFit( double mass_min, double mass_max,
                          double time_min, double time_max,
                          double scan_min, double scan_max,
                          double scan_step ):
    mass_min( mass_min ), mass_max( mass_max ),
    time_min( time_min ), time_max( time_max ),
    scan_min( scan_min ), scan_max( scan_max ),
    scan_step( scan_step ) {
}


// destructor
LifetimeFit::~LifetimeFit() {
}


// add data from a new event
bool LifetimeFit::add( const Event& ev ) {

    // get ParticleReco instance to compute mass
    static ParticleReco* particle_reco = ParticleReco::instance();
    double mass = particle_reco->Mass();

    // get ProperTime instance to compute proper decay time
    static ProperTime* proper_time = ProperTime::instance();
    double time = proper_time->DecayTime();

    // check if mass is in range, and return true
    // increase counter and update sums
    if( (mass_min < mass) && (mass < mass_max) &&
        (time_min < time) && (time < time_max) ){
        decay_times.push_back(time);
        return true;
    }
    // else return false
    else return false;

}


// compute mean lifetime and error
void LifetimeFit::compute() {

    // quadratic-fitter instance
    QuadraticFitter* fit = new QuadraticFitter;

    // sum for likelyhood (always the same)
    double sum_ti = 0;
    int n = decay_times.size();
    for( int i = 0; i < n; i++ ) sum_ti += decay_times[i];

    // compute likelyhood in scan range and fill fit class with data
    for( double t_scan = scan_min; t_scan <= scan_max; t_scan += scan_step ){
        double likelyhood = ( sum_ti / t_scan ) + 
                            ( n * log( t_scan ) ) +
                            ( n * log( exp( -time_min / t_scan) - 
                                       exp( -time_max / t_scan )));
        fit->add( t_scan, likelyhood );
    }

    // compute mean lifetime and error from fit
    lt_mean = - fit->b() / ( 2 * fit->c() );
    lt_err  = 1 / sqrt( 2 * fit->c() );

    delete fit;

    return;

}


// return number of selected events
unsigned int LifetimeFit::NEvents() const{
    return decay_times.size();
};

// return the mean lifetime
double LifetimeFit::LifetimeMean() const {
    return lt_mean;
};

// return the lifetime error
double LifetimeFit::LifetimeError() const {
    return lt_err;
};