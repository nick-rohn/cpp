#ifndef LifetimeFit_h
#define LifetimeFit_h

#include <vector>

class Event;

class LifetimeFit {

    public:

        // constructor
        LifetimeFit( double mass_min, double mass_max,
                     double time_min, double time_max,
                     double scan_min, double scan_max,
                     double scan_step );

        // destructor
        ~LifetimeFit();

        bool add( const Event& ev );      // add data from a new event
        void compute();                   // compute mean and rms

        unsigned int NEvents() const;     // return number of accepted events
        double LifetimeMean()  const;  // return the mean lifetime
        double LifetimeError() const;  // return the lifetime error

    private:

        const double mass_min; // min mass
        const double mass_max; // max mass

        const double time_min, time_max; // time range
        const double scan_min, scan_max; // scan range
        const double scan_step;

        std::vector<double> decay_times; // all accepted decay times

        double lt_mean; // mean lifetime
        double lt_err ; // lifetime error

};

#endif

