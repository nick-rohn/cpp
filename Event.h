#ifndef Event_h
#define Event_h

class Event {

    public:

        // constructor
        Event( int n, double x, double y, double z );

        // deleted copy constructor and assignment to prevent unadvertent copy
        Event           ( const Event& x ) = delete;
        Event& operator=( const Event& x ) = delete;

        // destructor
        ~Event();

        // composite object Particle to hold all information for each particle
        struct Particle {
            int charge;
            double p_x, p_y, p_z;
        };
        typedef const Particle* part_ptr;

        // add a particle to the event
        void Add( int charge, double p_x, double p_y, double p_z );

        // get event id.
        int EventNumber() const;

        // get decay point coordinates
        double XDecay() const;
        double YDecay() const;
        double ZDecay() const;

        // get number of particles
        int NParticles() const;

        // get particle
        part_ptr GetParticle( unsigned int i ) const;

        static const unsigned int max_n_part = 10;

    private:

        // event-specific informations:
        const int ev_number;
        const double x_decay, y_decay, z_decay;

        // particles: number and array of pointers
        int n_particles = 0;
        Particle** particles;

};

#endif

