#include <cassert>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "ssys.h"
#include "SPath.hh"
#include "PMTSim.hh"
#include "SVolume.h"

int main(int argc, char** argv)
{
    setenv("JUNO_PMT20INCH_POLYCONE_NECK","ENABLED",1); 
    setenv("JUNO_PMT20INCH_SIMPLIFY_CSG","ENABLED",1);
    setenv("JUNO_PMT20INCH_NOT_USE_REAL_SURFACE", "ENABLED", 1); 
    setenv("JUNO_PMT20INCH_PLUS_DYNODE", "ENABLED", 1); 

 
    //const char* geom_default = "nnvtBodyPhys" ; // THIS NOW NULL 
    //const char* geom_default = "nnvtInnerPhys" ; 
    const char* geom_default = "tub3BodyPhys" ; 
    const char* geom = ssys::getenvvar("GEOM", geom_default );


    typedef std::vector<double> VD ; 
    typedef std::vector<G4VSolid*> VS ; 

    VD* tr = new VD ; 
    VS* so = new VS ; 

    G4VPhysicalVolume* pv = PMTSim::GetPV(geom, tr, so );
    assert(pv); 

    SVolume::DumpTransforms(tr, so, "PMTSim::DumpTransforms"); 
 
    const char* path = SPath::Resolve("$TMP/PMTSim/GetPVTest/transforms.npy", FILEPATH ); 
    SVolume::SaveTransforms(tr, so, path  ); 

    return 0 ; 
}
