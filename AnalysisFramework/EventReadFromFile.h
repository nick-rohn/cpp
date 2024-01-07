#ifndef EventReadFromFile_h
#define EventReadFromFile_h

#include <fstream>
#include <string>

#include "AnalysisFramework/EventSource.h"

class Event;

class EventReadFromFile: public EventSource {

    public:

        // read data from file "name"
        EventReadFromFile( const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        EventReadFromFile           ( const EventReadFromFile& x ) = delete;
        EventReadFromFile& operator=( const EventReadFromFile& x ) = delete;

        ~EventReadFromFile() override;

    private:

        // get an event
        const Event* get() override;

        // input file
        std::ifstream* file;

        // read and event
        const Event* ReadFile();

};

#endif

