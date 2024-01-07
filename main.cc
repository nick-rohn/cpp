#include <vector>

#include "AnalysisInfo.h"
#include "EventSource.h"
#include "SourceFactory.h"
#include "AnalysisSteering.h"
#include "AnalysisFactory.h"

using namespace std;

int main( int argc, char *argv[] ){

    // store command line parameters
    AnalysisInfo* info = new AnalysisInfo( argc, argv );

    // create data source
    EventSource* es = SourceFactory::create( info );

    // list of analyzers
    vector<AnalysisSteering*> an_list = AnalysisFactory::create( info );

    // initialize analyzers
    for( auto as: an_list ) as->BeginJob();

    // loop over events
    es->run();

    // finalize all analyzers
    for( auto as: an_list ) as->EndJob();

    // clear allocated space
    for( auto as: an_list ) delete as;
    delete es;
    
    return 0;
    
}