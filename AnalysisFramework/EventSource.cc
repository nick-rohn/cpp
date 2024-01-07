#include "AnalysisFramework/EventSource.h"

#include "AnalysisFramework/Event.h"
#include "util/include/Dispatcher.h"


EventSource::EventSource() {
}


EventSource::~EventSource() {
}

void EventSource::run() {
    
    // loop over events
    const Event* ev;
    while( (ev = get()) != nullptr ){
        Dispatcher<Event>::notify( *ev );
        delete ev;
    }

    return;
    
}