#include "G4Version.hh"
#include "G4Orb.hh"
#include "G4ios.hh"

int main()
{
    G4cout << G4Version << G4Date << "\n" ; 

    G4Orb orb("orb", 100.); 
    G4cout << orb ; 

    return 0 ; 
}
