#ifndef Event_h
#define Event_h

class Event {

    public:

        // constructor
        Event( int n, float x, float y, float z ); // create an event with number "n"
                                                // and coordinates x, y, z
        // destructor
        ~Event();

        // composite object Particle to hold all information for each particle
        // ( electric charge and x,y,z momentum components )
        struct Particle {
        ...
        };
        typedef const Particle* part_ptr;

        // add a particle to the event
        void add( int charge, float px, float py, float pz );

        // get event id.
        int eventNumber() const;
        // get decay point coordinates
        ...
        // get number of particles
        ...
        // get particle
        part_ptr particle( unsigned int i ) const;

    private:

        // event-specific informations:
        ... // event id
        ... // decay point

        // particles: number and array of pointers
        ...

};

#endif

