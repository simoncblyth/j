
#include <cstdio>
#include <cassert>

#define private public
#define protected public

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "ZSolid.hh"

G4VSolid* make_tubs( const char* name, double rmax, double hz )
{
    double rmin = 0. ; 
    double pSPhi = 0. ;
    double pDPhi = 2.*CLHEP::pi ;
    G4VSolid* tubs = new G4Tubs(name, rmin, rmax, hz, pSPhi, pDPhi); 
    return tubs ; 
}


/**

Because the G4BooleanSolid ctor allocates fPtrSolidB 



 95 G4BooleanSolid::G4BooleanSolid( const G4String& pName,
 96                                       G4VSolid* pSolidA ,
 97                                       G4VSolid* pSolidB ,
 98                                 const G4Transform3D& transform    ) :
 99   G4VSolid(pName), fStatistics(1000000), fCubVolEpsilon(0.001),
100   fAreaAccuracy(-1.), fCubicVolume(-1.), fSurfaceArea(-1.),
101   fRebuildPolyhedron(false), fpPolyhedron(0), fPrimitivesSurfaceArea(0.),
102   createdDisplacedSolid(true)
103 {
104   fPtrSolidA = pSolidA ;
105   fPtrSolidB = new G4DisplacedSolid("placedB",pSolidB,transform) ;
106 }

**/


void test_PlacementNewDupe()
{
    G4VSolid* l = make_tubs("l", 100., 10.); 
    G4VSolid* r = make_tubs("r", 200., 10.); 

    G4ThreeVector tla(0,0,-10.) ; 
    G4VSolid* lr = new G4UnionSolid( "lr", l, r, 0, tla); 
    //G4VSolid* lr = new G4UnionSolid( lr_name, l, r ); 


    char* bytes0 = nullptr ; 
    int num_bytes0 ; 
    ZSolid::GetBooleanBytes( &bytes0, num_bytes0, lr );   
    printf("num_bytes0 %d \n", num_bytes0); 

    G4cout << *lr ; 

    ZSolid::PlacementNewDupe( lr ); 

    printf("after ZSolid::PlacementNewDupe \n"); 

    G4cout << *lr ; 

    char* bytes1 = nullptr ; 
    int num_bytes1 ; 
    ZSolid::GetBooleanBytes( &bytes1, num_bytes1, lr );   
    printf("num_bytes1 %d \n", num_bytes1); 
    assert( num_bytes0 == num_bytes1 ); 
    int mismatch = ZSolid::CompareBytes( bytes0, bytes1, num_bytes0 ); 
    printf("mismatch %d\n", mismatch); 
}



int main(int argc, char** argv)
{
    //test_offsetof_G4UnionSolid(); 
    test_PlacementNewDupe();   
  
    return 0 ; 
}



