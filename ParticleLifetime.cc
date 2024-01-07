#include "ParticleLifetime.h"

#include <iostream>
#include <vector>
#include <string>

#include "TH1F.h"
#include "TFile.h"

#include "Event.h"
#include "LifetimeFit.h"
#include "AnalysisSteering.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "ProperTime.h"
#include "util/include/ActiveObserver.h"

using namespace std;


// concrete factory to create an ParticleLifetime analyzer
class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory{
    public:
        // assign name "plot" to analyzer and factory
        ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "time" ){}
        // function to create an ParticleLifetime when builder is run
        AnalysisSteering* create( const AnalysisInfo* info ) override {
            return new ParticleLifetime( info );
        }
};
// create global ParticleLifetimeFactory to be registered in the AnalysisFactory map
// if called by arg, the AnalysisFactory::create will run the ParticleLifetimeFactory::create
// and an instance of ParticleLifetime will be added to the analysis log
static ParticleLifetimeFactory pt;



ParticleLifetime::ParticleLifetime( const AnalysisInfo* info ):
    AnalysisSteering( info ) {
}

ParticleLifetime::~ParticleLifetime() {
    for( Particle* particle: p_list ){
        delete particle->data;
        delete particle->hist;
        delete particle;
    }
}


// function to be called at execution start
void ParticleLifetime::BeginJob() {

    // create list of particles
    p_list.reserve( 2 );
    // K0
    PCreate( "K0"     , 0.495, 0.500, 10.0,  500.0 );
    // Lambda0
    PCreate( "Lambda0", 1.115, 1.116, 10.0, 1000.0 );

    return;

}


// function to be called at execution end
void ParticleLifetime::EndJob() {

    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFile* file = new TFile( aInfo->value( "time" ).c_str(), "RECREATE" );

    cout << endl;
    // loop over elements
    for( Particle* particle: p_list ) {

        // compute results
        LifetimeFit* data = particle->data;
        data->compute();
        // print results
        cout << particle->name  << '\t'
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
void ParticleLifetime::update( const Event& ev ) {
    
    // get ProperTime instance to compute time
    static ProperTime* particle_reco = ProperTime::instance();

    // loop over particles and pass event to each of them
    // fill histogram with accepted events
    for( Particle* particle: p_list )
        if( particle->data->add( ev ) )
            particle->hist->Fill( particle_reco->DecayTime() );

    return;
}

// create particle structs
void ParticleLifetime::PCreate( const std::string& name,
                                double min_mass, double max_mass,
                                double min_time, double max_time ){
    
    std::string title = "time_" + name;
    // convert string for histogram title
    const char* hist_name = title.c_str();

    // create particle struct and set contents
    Particle* part = new Particle;
    part->name = name;
    part->data = new LifetimeFit( min_mass, max_mass );
    part->hist = new TH1F( hist_name, hist_name, 100, min_time, max_time );

    p_list.push_back( part );

    return;

}