#include "ParticleMass.h"

#include <iostream>
#include <vector>

#include "TH1F.h"
#include "TFile.h"

#include "Event.h"
#include "MassMean.h"

double Mass( const Event& ev );

using namespace std;

ParticleMass::ParticleMass() {
}

ParticleMass::~ParticleMass() {
    for( Particle* particle: p_list ){
        delete particle->data;
        delete particle->hist;
        delete particle;
    }
}


// function to be called at execution start
void ParticleMass::BeginJob() {

    // create list of particles
    p_list.reserve( 2 );
    // K0
    PCreate( "K0"     , 0.495, 0.500 );
    // Lambda0
    PCreate( "Lambda0", 1.115, 1.116 );

    return;

}


// function to be called at execution end
void ParticleMass::EndJob() {

    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFile* file = new TFile( "particles_hist.root", "CREATE" );

    // loop over elements
    for( Particle* particle: p_list ) {

        // compute results
        MassMean* data = particle->data;
        data->compute();
        // print results
        cout << endl;
        cout << data->MassAvg() << ' '
             << data->MassRms() << '\t'
             << data->NEvents() << endl;

        // save histogram
        particle->hist->Write();
        
    }
    
    // close file
    file->Close();
    delete file;
    // restore working area
    currentDir->cd();

    return;

}


// function to be called for each event
void ParticleMass::Process( const Event& ev ) {

    // loop over particles and pass event to each of them
    // fill histogram with accepted events
    for( Particle* particle: p_list )
        if( particle->data->add( ev ) )
            particle->hist->Fill( Mass( ev ) );

    return;
}

// create particle structs
void ParticleMass::PCreate( const std::string& name, double min_mass, double max_mass ){

    // convert string for histogram title
    const char* hist_name = name.c_str();

    // create particle struct and set contents
    Particle* part = new Particle;
    part->name = name;
    part->data = new MassMean( min_mass, max_mass );
    part->hist = new TH1F( hist_name, hist_name, 100, min_mass, max_mass );

    p_list.push_back( part );

    return;

}