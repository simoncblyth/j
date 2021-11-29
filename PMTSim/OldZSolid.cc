
#include <cassert>
#include <sstream>
#include <iomanip>

#include "OldZSolid.hh"
#include "ZSolid.hh"

#include "G4Ellipsoid.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4UnionSolid.hh"

#include "NP.hh"



std::string OldZSolid::desc() const   
{
    std::stringstream ss ; 
    ss 
       << " EntityTypeName " << std::setw(15) << ZSolid::EntityTypeName(solid) 
       << " EntityType " << std::setw(3) << ZSolid::EntityType(solid) 
       << " label " << std::setw(10) << label 
       << " zdelta " << std::setw(10) << std::fixed << std::setprecision(3) << zdelta 
       << " z1 " << std::setw(10) << std::fixed << std::setprecision(3) << z1()
       << " z0 " << std::setw(10) << std::fixed << std::setprecision(3) << z0()
       ;
    std::string s = ss.str(); 
    return s ; 
}

double OldZSolid::z0() const 
{
    double _z0, _z1 ; 
    ZSolid::ZRange(_z0, _z1, solid ); 
    return _z0 ; 

}
double OldZSolid::z1() const 
{
    double _z0, _z1 ; 
    ZSolid::ZRange(_z0, _z1, solid ); 
    return _z1 ; 
}

int OldZSolid::classifyZCut( double zcut ) const 
{
    double az0 = zdelta + z0() ; 
    double az1 = zdelta + z1() ; 
    return ZSolid::ClassifyZCut( az0, az1, zcut ); 
}  

void OldZSolid::applyZCut( double zcut )
{
    double az1 = zdelta + z1() ; 
    double az0 = zdelta + z0() ; 
    assert( zcut < az1 && zcut > az0 );  

    double local_zcut = zcut - zdelta ;     

    ZSolid::ApplyZCut( solid, local_zcut, true ); 
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void OldZSolidList::dump(const char* msg) const
{
    std::cout << msg << std::endl ; 
    for(unsigned i=0 ; i < solids.size() ; i++)
    {
        const OldZSolid& zsi = solids[i] ; 
        double az0 = zsi.zdelta + zsi.z0() ; 
        double az1 = zsi.zdelta + zsi.z1() ; 
        std::cout 
            << std::setw(3) << i << " " << zsi.desc() 
            << " az1 " << std::setw(10) << std::fixed << std::setprecision(3) << az1
            << " az0 " << std::setw(10) << std::fixed << std::setprecision(3) << az0
            << std::endl 
            ; 
    }
}

void OldZSolidList::save(const char* path) const 
{
    std::vector<double> tmp ; 
    unsigned num = solids.size() ; 
    for(unsigned i=0 ; i < num ; i++)
    {
        const OldZSolid& zsi = solids[i] ; 
        tmp.push_back(zsi.z0()); 
        tmp.push_back(zsi.z1());
        tmp.push_back(zsi.zdelta); 
        tmp.push_back(0.); 

        double az0 = zsi.zdelta + zsi.z0() ; 
        double az1 = zsi.zdelta + zsi.z1() ; 
        tmp.push_back(az0);
        tmp.push_back(az1);
        tmp.push_back(0.); 
        tmp.push_back(0.); 
    }
    NP* a = NP::Make<double>( num, 2, 4 ); 
    a->read(tmp.data()); 
    a->save(path); 
}


G4VSolid* OldZSolidList::makeUnionSolid(const std::string& solidname) const 
{
    dump("OldZSolidList::makeUnionSolid"); 
    G4VSolid* solid = solids[0].solid ;
    for(unsigned i=1 ; i < solids.size() ; i++)
    {
        const OldZSolid& zsi = solids[i] ; 
        solid = new G4UnionSolid(
				 solidname+zsi.label,
				 solid,     
				 zsi.solid, 
				 0,
				 G4ThreeVector(0,0,zsi.zdelta)
				 );  
    }
 
    save("/tmp/ZSolids.npy"); 

    return solid ; 
}



unsigned OldZSolidList::classifyZCutCount( double zcut, int q_cls )
{
    unsigned count(0); 
    for(unsigned idx=0 ; idx < solids.size() ; idx++ )
    {
        OldZSolid& zsi = solids[idx] ;  
        if( zsi.classifyZCut(zcut) == q_cls ) count += 1 ; 
    }
    return count ; 
}


/**
OldZSolids::makeUnionSolidZCut
---------------------------------

Hmm how to do this with a tree of solids instead of the artifically 
collected vector ?

**/

G4VSolid* OldZSolidList::makeUnionSolidZCut(const std::string& solidname, double zcut) 
{
    unsigned num_undefined = classifyZCutCount(zcut, ZSolid::UNDEFINED ); 
    unsigned num_include   = classifyZCutCount(zcut, ZSolid::INCLUDE ); 
    unsigned num_straddle  = classifyZCutCount(zcut, ZSolid::STRADDLE ); 
    unsigned num_exclude   = classifyZCutCount(zcut, ZSolid::EXCLUDE ); 
    unsigned num_solid     = num_include + num_straddle ; 
 
    std::cout 
         << "OldZSolids::makeUnionSolidZCut"
         << " num_undefined " << num_undefined
         << " num_include " << num_include
         << " num_straddle " << num_straddle
         << " num_exclude " << num_exclude
         << " num_solid " << num_solid
         << std::endl 
         ;

    assert( num_undefined == 0 );  
    assert( num_solid > 0 );  

    OldZSolid& zsi0 = solids[0] ;  
    G4VSolid* solid = zsi0.solid ;
    int cls = zsi0.classifyZCut(zcut ); 

    assert( cls == ZSolid::INCLUDE || cls == ZSolid::STRADDLE ); // first solid must be at z top and at least partially included 
    if( cls == ZSolid::STRADDLE ) zsi0.applyZCut( zcut ); 
    if( num_solid == 1 ) return solid ; 

    for(unsigned idx=1 ; idx < solids.size() ; idx++)
    {
        OldZSolid& zsi = solids[idx] ;  
        cls = zsi.classifyZCut( zcut ); 

        if( cls == ZSolid::STRADDLE ) zsi.applyZCut( zcut ); 
        if( cls == ZSolid::INCLUDE || cls == ZSolid::STRADDLE )
        {
            solid = new G4UnionSolid(
                     solidname+zsi.label,
                     solid,     
                     zsi.solid, 
                     0,
                     G4ThreeVector(0,0,zsi.zdelta)
                     );  
        }
    }
    return solid ;
}

