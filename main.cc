#include <vector>

#include "AnalysisInfo.h"
#include "EventSource.h"
#include "SourceFactory.h"
#include "util/include/Dispatcher.h"
#include "AnalysisFactory.h"

using namespace std;

int main( int argc, char *argv[] ){

    // store command line parameters
    AnalysisInfo* info = new AnalysisInfo( argc, argv );

    // create data source
    EventSource* es = SourceFactory::create( info );

    // create a list of analyzers
    AnalysisFactory::create( info );

    // initialize all analyzers
    Dispatcher<AnalysisInfo::AnalysisStatus>::notify( AnalysisInfo::begin );

    // loop over events
    es->run();

    // finalize all analyzers
    Dispatcher<AnalysisInfo::AnalysisStatus>::notify( AnalysisInfo::end );

    delete es;

    return 0;

}