#ifndef AnalysisSteering_h
#define AnalysisSteering_h

class Event;

class AnalysisSteering {

    public:

        AnalysisSteering();
        // deleted copy constructor and assignment to prevent unadvertent copy
        AnalysisSteering           ( const AnalysisSteering& x ) = delete;
        AnalysisSteering& operator=( const AnalysisSteering& x ) = delete;

        virtual ~AnalysisSteering();

        // function to be called at execution start
        virtual void BeginJob() = 0;
        // function to be called at execution end
        virtual void   EndJob() = 0;
        // function to be called for each event
        virtual void Process( const Event& ev ) = 0;

};

#endif

