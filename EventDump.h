#ifndef EventDump_h
#define EventDump_h

#include "AnalysisSteering.h"

class Event;
class AnalysisInfo;

class EventDump: public AnalysisSteering {

    public:

        EventDump( const AnalysisInfo* info );
        // deleted copy constructor and assignment to prevent unadvertent copy
        EventDump           ( const EventDump& x ) = delete;
        EventDump& operator=( const EventDump& x ) = delete;

        ~EventDump() override;

        // function to be called at execution start
        void BeginJob() override;
        // function to be called at execution end
        void   EndJob() override;
        // function to be called for each event
        void Process( const Event& ev ) override;

};

#endif

