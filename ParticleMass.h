#ifndef ParticleMass_h
#define ParticleMass_h

#include <vector>
#include <string>

#include "AnalysisSteering.h"

class MassMean;
class TH1F;

class ParticleMass: public AnalysisSteering {

    public:

        ParticleMass();
        // deleted copy constructor and assignment to prevent unadvertent copy
        ParticleMass           ( const ParticleMass& x ) = delete;
        ParticleMass& operator=( const ParticleMass& x ) = delete;

        ~ParticleMass() override;

        // function to be called at execution start
        void BeginJob() override;
        // function to be called at execution end
        void   EndJob() override;
        // function to be called for each event
        void Process( const Event& ev ) override;

    private:

        struct Particle{
            std::string name;   // particle name
            MassMean*   data;   // stored data
            TH1F*       hist;   //graph
        };
        
        // list of particles
        std::vector<Particle*> p_list;

        // create particle structs
        void PCreate( const std::string& name, double min_mass, double max_mass );

};

#endif