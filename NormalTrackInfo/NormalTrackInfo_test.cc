
#include <iostream>

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Electron.hh"
#include "G4Track.hh"

#include "NormalTrackInfo.hh"

int main()
{
    G4double en = 1.*MeV ;
    G4ParticleMomentum momentum(0., 0., 1.);
    G4DynamicParticle* particle = new G4DynamicParticle(G4Electron::Definition(),momentum);
    particle->SetPolarization(0., 0., 1. );
    particle->SetKineticEnergy(en);

    G4ThreeVector position(0., 0., 0.);
    G4double time(0.);

    G4Track* track = new G4Track(particle,time,position);

    NormalTrackInfo* ti0 = new NormalTrackInfo(track);

    ti0->markTracedAncestors(1);
    ti0->markTracedAncestors(10);
    ti0->markTracedAncestors(100);

    track->SetUserInformation(ti0);

    NormalTrackInfo* ti1 = NormalTrackInfo::FromTrack(track);

    std::cout
        << " track " << ( track ? "YES" : "NO " )
        << " ti0 " << ti0
        << " ti1 " << ti1
        << "\n"
        ;

#ifdef NORMALTRACKINFO_DEBUG
     NormalTrackInfoDebug::final_check("NormalTrackInfo_test.main BEFORE delete track");
#endif

    delete track ;

#ifdef NORMALTRACKINFO_DEBUG
     NormalTrackInfoDebug::final_check("NormalTrackInfo_test.main AFTER delete track");
#endif



    return 0 ;
}
