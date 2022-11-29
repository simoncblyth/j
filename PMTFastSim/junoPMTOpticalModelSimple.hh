#pragma once

#include "plog/Severity.h"
#include "PMTFASTSIM_API_EXPORT.hh"
#include "G4VFastSimulationModel.hh"
struct JPMT ; 

class PMTFASTSIM_API junoPMTOpticalModelSimple : public G4VFastSimulationModel
{
    public:
        static const plog::Severity LEVEL ; 
    public:
        junoPMTOpticalModelSimple(G4String, G4VPhysicalVolume*, G4Region*); 

        virtual G4bool IsApplicable(const G4ParticleDefinition&);
        virtual G4bool ModelTrigger(const G4FastTrack&);
        virtual void DoIt(const G4FastTrack&, G4FastStep&);

    private:
        JPMT* jpmt ;   // actually only needs to be single instance of JPMT for entire geometry
        int ModelTrigger_count ; 
}; 



