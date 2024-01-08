#include "AnalysisFramework/AnalysisSteering.h"

#include "AnalysisFramework/AnalysisInfo.h"
#include "util/include/ActiveObserver.h"

AnalysisSteering::AnalysisSteering( const AnalysisInfo* info ):
    aInfo( info ) {
}


AnalysisSteering::~AnalysisSteering() {
}


// function to be called at execution start / end
void AnalysisSteering::update( const AnalysisInfo::AnalysisStatus& status ) {
    switch ( status ) {
    case AnalysisInfo::begin:
        BeginJob();
        break;
    case AnalysisInfo::end:
        EndJob();
        break;
    }
    return;
}