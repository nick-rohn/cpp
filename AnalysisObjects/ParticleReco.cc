#include "AnalysisObjects/ParticleReco.h"

#include <iostream>
#include <cmath>

#include "AnalysisFramework/Event.h"
#include "AnalysisUtilities/Utilities.h"
#include "AnalysisUtilities/Constants.h"
#include "util/include/Singleton.h"
#include "util/include/LazyObserver.h"

using namespace std;


// constructor
ParticleReco::ParticleReco() {
}


// destructor
ParticleReco::~ParticleReco() {
}


// recompute tag informations for new event
void ParticleReco::update( const Event& ev ) {

    // set default quantities
    type   = unknown;
    energy = -1.0;
    mass   = -1.0;


    // variables to loop over particles
    Event::u_int n = ev.NParticles();

    // positive / negative track counters
    int pos_particles, neg_particles;
    pos_particles = neg_particles = 0;

    // variables for momentum sums
    double px_sum, py_sum, pz_sum;
    px_sum = py_sum = pz_sum = 0.0;

    // variables for energy sums, for K0 and Lambda0
    double energy_sum_k, energy_sum_l;
    double mass_sum_k, mass_sum_l;
    energy_sum_k = energy_sum_l = mass_sum_k = mass_sum_l = 0.0;

    // loop over particles - momenta
    for( Event::u_int i = 0; i < n; ++i ){

        // get particle pointer
        Event::part_ptr particle = ev.GetParticle(i);
        const double p_x = particle->p_x;
        const double p_y = particle->p_y;
        const double p_z = particle->p_z;

        // update momentum sums
        px_sum += p_x;
        py_sum += p_y;
        pz_sum += p_z;

        // update energy sums, for K0 and Lambda0 hypotheses:

        // pion mass for K0,
        double pion_energy = Utilities::Energy( p_x, p_y, p_z, Constants::mass_pion );

        energy_sum_k += pion_energy;


        // proton or pion mass for Lambda0,
        // for positive or negative particles respectively 
//        energy_sum_l += Energy( p_x, p_y, p_z,
//                                      ( particle->charge == 1 ? mass_proton : mass_pion ));
        if( particle->charge == 1 ){
            energy_sum_l += Utilities::Energy( p_x, p_y, p_z, Constants::mass_proton);
            pos_particles += 1;
        }
        else if( particle->charge == -1 ){
            energy_sum_l += pion_energy;
            neg_particles +=1;
        }
        // update positive/negative track counters
        
        // exclude cases with particles with unexpected charge
        // charge is int, so no risk with '=='
        else return;

    }

    // check for exactly one positive and one negative track
    // otherwise leave unknown type
    if( !( (pos_particles == 1) && (neg_particles == 1) ) ) return;

    // invariant masses for different decay product mass hypotheses
    double mass_hyp_k = Utilities::InvariantMass( px_sum, py_sum, pz_sum, energy_sum_k );
    double mass_hyp_l = Utilities::InvariantMass( px_sum, py_sum, pz_sum, energy_sum_l );

    // compare invariant masses with known values and set final values
    // ( type, energy and mass )
    double delta_k = fabs( mass_hyp_k - Constants::mass_k0 );
    double delta_l = fabs( mass_hyp_l - Constants::mass_lambda0 );

    if( delta_k < delta_l ){
        type = K0;
        energy = energy_sum_k;
        mass = mass_hyp_k;
    }
    else{
        type = Lambda0;
        energy = energy_sum_l;
        mass = mass_hyp_l;
    }

    return;

}


// return particle type
ParticleReco::ParticleType ParticleReco::Type(){
    // check for new event and return result
    check();
    return type;
}


// return particle energy
double ParticleReco::Energy(){
    // check for new event and return result
    check();
    return energy;

}


// return particle mass
double ParticleReco::Mass(){
    // check for new event and return result
    check();
    return mass;
}