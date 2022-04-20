#include <cassert>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "SPath.hh"
#include "PMTSim.hh"
#include "P4Volume.hh"

int main(int argc, char** argv)
{
    setenv("JUNO_PMT20INCH_POLYCONE_NECK","ENABLED",1); 
    setenv("JUNO_PMT20INCH_SIMPLIFY_CSG","ENABLED",1);
    setenv("JUNO_PMT20INCH_NOT_USE_REAL_SURFACE", "ENABLED", 1); 
    setenv("JUNO_PMT20INCH_PLUS_DYNODE", "ENABLED", 1); 

    const char* name = argc > 1 ? argv[1] : "body_phys" ;  

    typedef std::vector<double> VD ; 
    typedef std::vector<G4VSolid*> VS ; 

    VD* tr = new VD ; 
    VS* so = new VS ; 

    G4VPhysicalVolume* pv = PMTSim::GetPV(name, tr, so );
    assert(pv); 

    P4Volume::DumpTransforms(tr, so, "PMTSim::DumpTransforms"); 
 
    const char* path = SPath::Resolve("$TMP/PMTSim/GetPVTest/transforms.npy", FILEPATH ); 
    P4Volume::SaveTransforms(tr, so, path  ); 

    return 0 ; 
}
