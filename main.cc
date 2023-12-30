#include <string>
#include <sstream>
#include <vector>

#include "AnalysisInfo.h"
#include "SourceFactory.h"
#include "Event.h"
#include "EventSource.h"
#include "AnalysisSteering.h"
#include "EventDump.h"
#include "ParticleMass.h"

using namespace std;

int main( int argc, char *argv[] ){

    // store command line parameters
    AnalysisInfo* info = new AnalysisInfo( argc, argv );

    // create data source
    EventSource* es = SourceFactory::create( info );

    // list of analyzers
    vector<AnalysisSteering*> an_list;
    // event dumping object
    an_list.push_back( new EventDump );
    // particle identifier
    an_list.push_back( new ParticleMass );

    // initialize analyzers
    for( auto as: an_list ) as->BeginJob();

    // loop over events
    const Event* ev;
    while( (ev = es->get()) != nullptr ){
        for( auto as: an_list ) as->Process( *ev );
        delete ev;
    }

    // finalize all analyzers
    for( auto as: an_list ) as->EndJob();

    // clear allocated space
    delete es;
    for( auto as: an_list ) delete as;
    
    return 0;
    
}