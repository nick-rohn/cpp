#include <iostream>
#include <fstream>

struct Event;

const Event* read( std::ifstream& file );
void dump( const Event& ev );
void clear ( const Event* ev );


int main( int argc, char *argv[] ){
    //open input file
    const char* name = argv[1];
    std::ifstream file( name );
    
    //event
    const Event* ev;

    //loop over events
    while( (ev = read( file )) != nullptr ){
        dump( *ev );
        clear( ev );
    }

    return 0;
    
}