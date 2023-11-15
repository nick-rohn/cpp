#ifndef Event_h
#define Event_h

class Event {

    public:

        typedef unsigned int u_int;
        // constructor
        Event( u_int n, double x, double y, double z );

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
        u_int EventNumber() const;

        // get decay point coordinates
        double XDecay() const;
        double YDecay() const;
        double ZDecay() const;

        // get number of particles
        u_int NParticles() const;

        // get particle
        part_ptr GetParticle( u_int i ) const;

        static const u_int max_n_part;

    private:

        // event-specific informations:
        const u_int ev_number;
        const double x_decay, y_decay, z_decay;

        // particles: number and array of pointers
        u_int n_particles;
        Particle** particles;

};

#endif

