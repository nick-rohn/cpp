#include "AnalysisPlugins/EventDump.h"

#include <iostream>

#include "AnalysisFramework/Event.h"
#include "AnalysisFramework/AnalysisFactory.h"
#include "AnalysisFramework/AnalysisSteering.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "util/include/ActiveObserver.h"

using namespace std;

// concrete factory to create an EventDump analyzer
class EventDumpFactory: public AnalysisFactory::AbsFactory{
    public:
        // assign name "dump" to analyzer and factory
        EventDumpFactory(): AnalysisFactory::AbsFactory( "dump" ){}
        // function to create an EventDump when builder is run
        AnalysisSteering* create( const AnalysisInfo* info ) override {
            return new EventDump( info );
        }
};
// create global EventDumpFactory to be registered in the AnalysisFactory map
// if called by arg, the AnalysisFactory::create will run the EventDumpFactory::create
// and an instance of EventDump will be added to the analysis log
static EventDumpFactory ed;




EventDump::EventDump( const AnalysisInfo* info ):
    AnalysisSteering( info ){
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::BeginJob() {
    return;
}


// function to be called at execution end
void EventDump::EndJob() {
    return;
}


// function to be called for each event
void EventDump::update( const Event& ev ) {

    // write event data
    cout << ev.EventNumber() << ' '
         << ev.XDecay() << ' ' << ev.YDecay() << ' ' << ev.ZDecay() << ' ' 
         << ev.NParticles();
    
    // write particles
    for ( Event::u_int i = 0; i < ev.NParticles(); ++i ){
        Event::part_ptr p = ev.GetParticle(i);
        cout << ' '
             << p->charge << ' '
             << p->p_x << ' ' << p->p_y << ' ' << p->p_z;
    }

    cout << endl;

    return;

}

