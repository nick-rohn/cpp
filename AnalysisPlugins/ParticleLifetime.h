#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include <vector>
#include <string>

#include "AnalysisFramework/AnalysisSteering.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "util/include/ActiveObserver.h"

class LifetimeFit;
class TH1F;

class ParticleLifetime: public AnalysisSteering,
                    public ActiveObserver<Event> {

    public:

        ParticleLifetime( const AnalysisInfo* info );
        // deleted copy constructor and assignment to prevent unadvertent copy
        ParticleLifetime           ( const ParticleLifetime& x ) = delete;
        ParticleLifetime& operator=( const ParticleLifetime& x ) = delete;

        ~ParticleLifetime() override;

        // function to be called at execution start
        void BeginJob() override;
        // function to be called at execution end
        void   EndJob() override;
        // function to be called for each event
        void update( const Event& ev ) override;

    private:

        struct Particle{
            std::string  name;   // particle name
            LifetimeFit* data;   // stored data
            TH1F*        hist;   //graph
        };
        
        // list of particles
        std::vector<Particle*> p_list;

        // create particle structs
        void PCreate( const std::string& name,
                      double mass_min, double mass_max,
                      double time_min, double time_max,
                      double scan_min, double scan_max,
                      double scan_step );

};

#endif