#ifndef LifetimeFit_h
#define LifetimeFit_h

class Event;

class LifetimeFit {

    public:

        // constructor
        LifetimeFit( double min, double max ); // mass range

        // destructor
        ~LifetimeFit();

        bool add( const Event& ev );      // add data from a new event
        void compute();                   // compute mean and rms

        unsigned int NEvents() const;     // return number of accepted events

    private:

        const double mass_min; // min mass
        const double mass_max; // max mass

        unsigned int n_events;  // number of accepted events

};

#endif

