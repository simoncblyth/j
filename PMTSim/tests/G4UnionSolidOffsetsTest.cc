/**
By observation (with clang anyhow) memory layout is opposite to inheritance order
with the base-est class members first.::

    G4VSolid

    G4BooleanSolid
        fPtrSolidA
        fPtrSolidB

    G4UnionSolid
        fPMin
        fPMax


Uses naughty defines in order for offsetof to work with private and protected members.

**/

#define private public
#define protected public

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#elif defined(_MSC_VER)
#pragma warning(push)
#endif

void test_offsetof_G4UnionSolid()
{
    printf("sizeof(G4UnionSolid)                 %lu \n",sizeof(G4UnionSolid)); 
    printf("sizeof(G4SubtractionSolid)           %lu \n",sizeof(G4SubtractionSolid)); 
    printf("sizeof(G4IntersectionSolid)          %lu \n",sizeof(G4IntersectionSolid)); 
    printf("sizeof(G4BooleanSolid)               %lu \n",sizeof(G4BooleanSolid)); 
    printf("sizeof(G4VSolid)                     %lu \n",sizeof(G4VSolid)); 
    printf("sizeof(G4VSolid*)                    %lu \n",sizeof(G4VSolid*)); 
    printf("sizeof(G4ThreeVector)                %lu \n", sizeof(G4ThreeVector)); 
    printf("sizeof(G4ThreeVector)*2              %lu \n", sizeof(G4ThreeVector)*2); 
    printf("sizeof(G4int)                        %lu \n", sizeof(G4int)); 

    int nb = 0 ; 
    int sz = 0 ; 
    int pd = 0 ; 
    int of = 0 ; 

    sz = sizeof(G4UnionSolid)  ;
     
    printf("sizeof(G4UnionSolid)                    %d %d %d  \n", sz, nb, pd ); 

    sz = sizeof(G4VSolid*) ; 
    nb += sz + pd ; printf("    sizeof(G4VSolid*)  fPtrSolidA          %d  %d  %d\n",  sz, nb, pd); 
    nb += sz + pd ; printf("    sizeof(G4VSolid*)  fPtrSolidB          %d  %d  %d\n",  sz, nb, pd); 
    sz = sizeof(G4int) ; 
    pd = 4 ; 
    nb += sz + pd  ; printf("    sizeof(G4int)      fStatistics         %d  %d  %d\n",  sz, nb, pd );
    pd = 0 ; 
    sz = sizeof(G4double) ; 
    nb += sz + pd ; printf("    sizeof(G4double)   fCubVolEpsilon      %d %d  %d\n",   sz, nb, pd ); 
    nb += sz + pd ; printf("    sizeof(G4double)   fAreaAccuracy       %d %d  %d\n",   sz, nb, pd ); 
    nb += sz + pd ; printf("    sizeof(G4double)   fCubicVolume        %d %d  %d\n",   sz, nb, pd ); 
    nb += sz + pd ; printf("    sizeof(G4double)   fSurfaceArea        %d %d  %d\n",   sz, nb, pd ); 
    sz = sizeof(G4bool) ; 
    pd = 7 ; 
    nb += sz + pd ; printf("    sizeof(G4bool)     fRebuildPolyhedron  %d %d  %d\n",   sz, nb, pd ); 
    pd = 0 ; 
    sz = sizeof(G4Polyhedron*) ; 
    nb += sz + pd ; printf("    sizeof(G4Polyhedron*)  fpPolyhedron     %d %d %d\n",  sz, nb, pd ); 
    sz = sizeof(std::vector<std::pair<G4VSolid *,G4Transform3D>>) ; 
    nb += sz + pd ; printf("    sizeof(std::vector<std::pair<G4VSolid *,G4Transform3D>>)  fPrimitives     %d %d \n",  sz, nb ); 
    sz = sizeof(G4double) ; 
    nb += sz + pd ; printf("    sizeof(G4double)   fPrimitivesSurfaceArea  %d %d %d\n",   sz, nb, pd ); 
    sz = sizeof(G4bool) ; 
    pd = 7 ; 
    nb += sz + pd ; printf("    sizeof(G4bool)     createdDisplacedSolid  %d %d %d \n",   sz, nb, pd ); 
    pd = 0 ; 

    sz = sizeof(G4ThreeVector) ; 
    nb += sz + pd ; printf("    sizeof(G4ThreeVector)  fPMin           %d  %d  %d\n",  sz, nb, pd); 
    nb += sz + pd ; printf("    sizeof(G4ThreeVector)  fPMax           %d  %d  %d\n",  sz, nb, pd); 

    sz = sizeof( G4double) ; 
    of = offsetof( G4UnionSolid, kCarTolerance ); 
    printf( " offsetof( G4UnionSolid, kCarTolerance)  %d %d %d   (G4VSolid)\n", of, sz, of+sz ); 

    sz = sizeof(G4String); 
    of = offsetof( G4UnionSolid, fshapeName ); 
    printf( " offsetof( G4UnionSolid, fshapeName)     %d %d %d   (G4VSolid)\n", of, sz, of+sz );

    sz = sizeof(G4VSolid*) ; 
    of = offsetof( G4UnionSolid, fPtrSolidA  ); 
    printf( " offsetof( G4UnionSolid, fPtrSolidA)     %d %d %d   (G4BooleanSolid)\n", of, sz, of+sz );
    of = offsetof( G4UnionSolid, fPtrSolidB  ); 
    printf( " offsetof( G4UnionSolid, fPtrSolidB)     %d %d %d   (G4BooleanSolid)\n", of, sz, of+sz );

    of = offsetof( G4UnionSolid, fpPolyhedron ); 
    printf( " offsetof( G4UnionSolid, fpPolyhedron )   %d %d %d   (G4BooleanSolid)\n", of, sz, of+sz );

    sz = sizeof(G4bool) ; 
    of = offsetof( G4UnionSolid, createdDisplacedSolid ); 
    printf( " offsetof( G4UnionSolid, createdDisplacedSolid) %d %d %d   (G4BooleanSolid)\n", of, sz, of+sz );    

    sz = sizeof( G4ThreeVector) ; 
    of = offsetof( G4UnionSolid, fPMin) ; 
    printf( " offsetof( G4UnionSolid, fPMin)          %d %d %d   (G4UnionSolid) \n", of, sz, of+sz ); 

    of = offsetof( G4UnionSolid, fPMax) ; 
    printf( " offsetof( G4UnionSolid, fPMax)          %d %d %d   (G4UnionSolid) \n", of, sz, of+sz ); 

    sz = sizeof(G4VSolid) ; 
    nb += sz + pd ; printf("     sizeof(G4VSolid)                         %d %d %d \n",  sz, nb, pd ); 
    sz = sizeof(G4double) ; 
    printf("    sizeof(G4double) kCarTolerance   %d\n",  sz );
    sz = sizeof(G4String) ;  
    printf("    sizeof(G4String) fshapename      %d\n",  sz ); 
}

#ifdef __clang__
#pragma clang diagnostic pop
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif

int main(int argc, char** argv)
{
    test_offsetof_G4UnionSolid(); 
    return 0 ; 
}

