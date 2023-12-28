#include "ParticleMass.h"

#include <iostream>
#include <vector>

#include "MassMean.h"

using namespace std;

ParticleMass::ParticleMass() {
}

ParticleMass::~ParticleMass() {
    for( MassMean* part: p_list ) delete part;
}


// function to be called at execution start
void ParticleMass::BeginJob() {

    // create list of particles
    p_list.reserve( 2 );
    // K0
    p_list.push_back( new MassMean( 0.495, 0.500 ) );
    // Lambda0
    p_list.push_back( new MassMean( 1.115, 1.116 ) );

    return;

}


// function to be called at execution end
void ParticleMass::EndJob() {

    // loop over elements
    for( MassMean* particle: p_list ) {
        // compute results
        particle->compute();
        // print results
        cout << endl;
        cout << particle->MassAvg() << ' '
             << particle->MassRms() << '\t'
             << particle->NEvents() << endl;
    }

    return;

}


// function to be called for each event
void ParticleMass::Process( const Event& ev ) {
  // loop over particles and pass event to each of them
  for( MassMean* particle: p_list ) particle->add( ev );

  return;

}