#include "ParticleMass.h"

#include <iostream>
#include <vector>
#include <string>

#include "TH1F.h"
#include "TFile.h"

#include "Event.h"
#include "MassMean.h"
#include "AnalysisSteering.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "util/include/ActiveObserver.h"
#include "ParticleReco.h"

using namespace std;


// concrete factory to create an ParticleMass analyzer
class ParticleMassFactory: public AnalysisFactory::AbsFactory{
    public:
        // assign name "plot" to analyzer and factory
        ParticleMassFactory(): AnalysisFactory::AbsFactory( "plot" ){}
        // function to create an ParticleMass when builder is run
        AnalysisSteering* create( const AnalysisInfo* info ) override {
            return new ParticleMass( info );
        }
};
// create global ParticleMassFactory to be registered in the AnalysisFactory map
// if called by arg, the AnalysisFactory::create will run the ParticleMassFactory::create
// and an instance of ParticleMass will be added to the analysis log
static ParticleMassFactory pm;



ParticleMass::ParticleMass( const AnalysisInfo* info ):
    AnalysisSteering( info ) {
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
    TFile* file = new TFile( aInfo->value( "plot" ).c_str(), "RECREATE" );

    cout << endl;
    // loop over elements
    for( Particle* particle: p_list ) {

        // compute results
        MassMean* data = particle->data;
        data->compute();
        // print results
        cout << particle->name  << '\t'
             << data->MassAvg() << ' '
             << data->MassRms() << '\t'
             << data->NEvents()
             << endl;

        // save histogram
        particle->hist->Write();
        
    }
    cout << endl;
    
    // close file
    file->Close();
    delete file;
    // restore working area
    currentDir->cd();

    return;

}


// function to be called for each event
void ParticleMass::update( const Event& ev ) {
    
    // get ParticleReco instance to compute mass
    static ParticleReco* particle_reco = ParticleReco::instance();

    // loop over particles and pass event to each of them
    // fill histogram with accepted events
    for( Particle* particle: p_list )
        if( particle->data->add( ev ) )
            particle->hist->Fill( particle_reco->Mass() );

    return;
}

// create particle structs
void ParticleMass::PCreate( const std::string& name, double min_mass, double max_mass ){
    
    std::string title = "mass_" + name;
    // convert string for histogram title
    const char* hist_name = title.c_str();

    // create particle struct and set contents
    Particle* part = new Particle;
    part->name = name;
    part->data = new MassMean( min_mass, max_mass );
    part->hist = new TH1F( hist_name, hist_name, 100, min_mass, max_mass );

    p_list.push_back( part );

    return;

}