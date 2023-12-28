#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Event.h"
#include "EventSource.h"
#include "EventReadFromFile.h"
#include "EventSim.h"
#include "AnalysisSteering.h"
#include "EventDump.h"
#include "ParticleMass.h"

using namespace std;

int main( int argc, char *argv[] ){

    // create data source
    EventSource* es;
    const string type = argv[1];
    if( type == "input" ){
        const string name = argv[2];
        es = new EventReadFromFile( name );
    }
    else
    if( type == "sim" ){
        const string nevt = argv[2];
        const string seed = ( argc > 3 ? argv[3] : "1" );
        stringstream sstr;
        unsigned int n;
        sstr.str( nevt );
        sstr >> n;
        sstr.clear();
        unsigned int s;
        sstr.str( seed );
        sstr >> s;
        es = new EventSim( n, s );
    }
    else{
        cout << "invalid keyword" << endl;
        return 0;
    }

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