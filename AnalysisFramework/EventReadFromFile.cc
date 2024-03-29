#include "AnalysisFramework/EventReadFromFile.h"

#include <fstream>
#include <string>

#include "AnalysisFramework/Event.h"

using namespace std;


// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) {
    file = new ifstream( name.c_str() );
}


EventReadFromFile::~EventReadFromFile() {
    delete file;
}


// get an event
const Event* EventReadFromFile::get() {
    return ReadFile();
}


// read an event
const Event* EventReadFromFile::ReadFile() {

    // event pointer and identifier
    Event* ev;
    Event::u_int id;

    // try to read input file
    // on failure return null pointer
    if( !(*file >> id) ) return nullptr;

    double x, y, z;
    *file >> x >> y >> z;
    ev = new Event( id, x, y, z );

    // read number of particles (could have used in the constructor)
    Event::u_int n;
    *file >> n;
    
    //read and store particles
    int charge;
    double p_x, p_y, p_z;
    for( Event::u_int i = 0; i < n; ++i ){
        *file >> charge >> p_x >> p_y >> p_z;
        ev->Add( charge, p_x, p_y, p_z );
    }

    return ev;

}

