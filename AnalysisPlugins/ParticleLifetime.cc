#include "AnalysisPlugins/ParticleLifetime.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "TH1F.h"
#include "TFile.h"

#include "AnalysisFramework/Event.h"
#include "AnalysisFramework/AnalysisSteering.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisFramework/AnalysisFactory.h"
#include "AnalysisObjects/LifetimeFit.h"
#include "AnalysisObjects/ProperTime.h"
#include "util/include/ActiveObserver.h"
#include "util/include/TFileProxy.h"

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
    ifstream file( aInfo->value( "fit" ).c_str() );
    string name;
    double mass_min, mass_max;
    double time_min, time_max;
    double scan_min,  scan_max;
    double scan_step;
    while ( file >> name >> mass_min >> mass_max >> time_min >> time_max
                         >> scan_min >> scan_max >> scan_step )
        PCreate(    name,   mass_min,   mass_max,   time_min,   time_max,
                            scan_min,   scan_max, scan_step );

    return;

}


// function to be called at execution end
void ParticleLifetime::EndJob() {

    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFileProxy* file = new TFileProxy( aInfo->value( "time" ).c_str(), "RECREATE" );

    cout << endl;
    // loop over elements
    for( Particle* particle: p_list ) {

        // compute results
        LifetimeFit* data = particle->data;
        data->compute();
        // print results
        cout << particle->name        << '\t'
             << data->LifetimeMean()  << ' '
             << data->LifetimeError() << '\t'
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
                                double mass_min, double mass_max,
                                double time_min, double time_max,
                                double scan_min, double scan_max,
                                double scan_step ){
    
    std::string title = "time_" + name;
    // convert string for histogram title
    const char* hist_name = title.c_str();

    // create particle struct and set contents
    Particle* part = new Particle;
    part->name = name;
    part->data = new LifetimeFit( mass_min, mass_max, time_min, time_max,
                                  scan_min, scan_max, scan_step );
    part->hist = new TH1F( hist_name, hist_name, 100, time_min, time_max );

    p_list.push_back( part );

    return;

}