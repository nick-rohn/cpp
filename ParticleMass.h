#ifndef ParticleMass_h
#define ParticleMass_h

#include <vector>

#include "AnalysisSteering.h"

class MassMean;

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

        // list of particles
        std::vector<MassMean*> p_list;

};

#endif