#include <cassert>
#include "MaterialSvc.hh"
#include "G4MaterialPropertyVector.hh"    // typedef 

int main(int argc, char** argv)
{
    const char* propPath = argc > 1 ? argv[1] : nullptr ; 
    if(!propPath) return 0 ; 

    bool dump = true ; 
    const char* path = MaterialSvc::GetPath(propPath); 

    G4MaterialPropertyVector* mpv = MaterialSvc::GetMPV(path,dump); 
    assert( mpv ); 

    return 0 ; 
}
