#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

    public:

        // constructor
        MassMean( double min, double max ); // mass range

        // destructor
        ~MassMean();

        bool add( const Event& ev );      // add data from a new event
        void compute();                   // compute mean and rms

        unsigned int NEvents() const;     // return number of accepted events
        double MassAvg() const;           // return mean mass
        double MassRms() const;           // return rms  mass

    private:

        const double mass_min; // min mass
        const double mass_max; // max mass

        unsigned int n_events;  // number of accepted events
        double mass_sum;        // sum of masses
        double mass_2_sum;      // sum of masses square

        double mass_avg; // mean mass
        double mass_rms; // rms  mass

};

#endif

