
#include <cstdio>
#include <cassert>

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "X4SolidTree.hh"

G4VSolid* make_tubs( const char* name, double rmax, double hz )
{
    double rmin = 0. ; 
    double pSPhi = 0. ;
    double pDPhi = 2.*CLHEP::pi ;
    G4VSolid* tubs = new G4Tubs(name, rmin, rmax, hz, pSPhi, pDPhi); 
    return tubs ; 
}

G4VSolid* make_orb( const char* name, double rmax )
{
    return new G4Orb(name, rmax); 
}

G4VSolid* make_union()
{
    G4VSolid* l = make_tubs("l", 100., 10.); 
    G4VSolid* r = make_tubs("r", 200., 10.); 
    G4ThreeVector tla(0,0,-10.) ; 
    G4VSolid* lr = new G4UnionSolid( "lr", l, r, 0, tla); 
    return lr ; 
}

void test_PlacementNewDupe()
{
    G4VSolid* lr = make_union(); 

    char* bytes0 = nullptr ; 
    int num_bytes0 ; 
    X4SolidTree::GetBooleanBytes( &bytes0, num_bytes0, lr );   
    printf("num_bytes0 %d \n", num_bytes0); 

    G4cout << *lr ; 

    X4SolidTree::PlacementNewDupe( lr ); 

    printf("after X4SolidTree::PlacementNewDupe \n"); 

    G4cout << *lr ; 

    char* bytes1 = nullptr ; 
    int num_bytes1 ; 
    X4SolidTree::GetBooleanBytes( &bytes1, num_bytes1, lr );   
    printf("num_bytes1 %d \n", num_bytes1); 
    assert( num_bytes0 == num_bytes1 ); 
    int mismatch = X4SolidTree::CompareBytes( bytes0, bytes1, num_bytes0 ); 
    printf("mismatch %d (expect a few different bytes from new G4DisplacedSolid inside ctor \n", mismatch); 
}

void test_SetRight()
{
    G4VSolid* lr = make_union(); 
    G4VSolid* o  = make_orb("o", 100.); 
    //G4cout << *lr ; 
    X4SolidTree::SetRight( lr, o ); 
    G4cout << *lr ; 
}

void test_SetRight_translate()
{
    G4VSolid* lr = make_union(); 
    G4VSolid* o  = make_orb("o", 100.); 
    //G4cout << *lr ; 
    G4ThreeVector rtla(0.,0.,-1000.); 
    X4SolidTree::SetRight( lr, o, nullptr, &rtla ); 
    G4cout << *lr ; 
}

void test_SetLeft()
{
    G4VSolid* lr = make_union(); 
    G4VSolid* o  = make_orb("o", 100.); 
    X4SolidTree::SetLeft( lr, o ); 
    G4cout << *lr ; 
}

int main(int argc, char** argv)
{
    //test_PlacementNewDupe();   
    //test_SetRight(); 
    test_SetRight_translate(); 
    //test_SetLeft(); 

    return 0 ; 
}



