#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "G4UnionSolid.hh"
#include "ZSolids.hh"

/**


            un
      un         un  
    a    b     c     d


**/

std::string ZSolid::desc() const 
{
    std::stringstream ss ; 
    ss 
       << " label " << std::setw(10) << label 
       << " zdelta " << std::setw(10) << std::fixed << std::setprecision(3) << zdelta 
       << " z1 " << std::setw(10) << std::fixed << std::setprecision(3) << z1
       << " z0 " << std::setw(10) << std::fixed << std::setprecision(3) << z0
       ;
    std::string s = ss.str(); 
    return s ; 
}

double ZSolids::getAbsoluteZShift(unsigned idx) const
{
    double az = 0. ;
    assert( idx < solids.size() ); 
    for(unsigned i=0 ; i <= idx ; i++)
    {
        if( i < solids.size() )
        {
            const ZSolid& zsi = solids[i] ; 
            az += zsi.zdelta ; 
        }
    }
    return az ; 
}

void ZSolids::dump(const char* msg) const
{
    std::cout << msg << std::endl ; 
    for(unsigned i=0 ; i < solids.size() ; i++)
    {
        const ZSolid& zsi = solids[i] ; 
        double az = getAbsoluteZShift(i); 
        double az1 = zsi.z1 + az ; 
        double az0 = zsi.z0 + az ; 

        std::cout 
            << std::setw(3) << i << " " << zsi.desc() 
            << " az " << std::setw(10) << std::fixed << std::setprecision(3) << az
            << " az1 " << std::setw(10) << std::fixed << std::setprecision(3) << az1
            << " az0 " << std::setw(10) << std::fixed << std::setprecision(3) << az0
            << std::endl 
            ; 
    }
}

G4VSolid* ZSolids::makeUnionSolid(const std::string& solidname, double zcut ) const 
{
    dump("ZSolids::makeUnionSolid"); 

    G4VSolid* solid = solids[0].solid ;
    for(unsigned i=1 ; i < solids.size() ; i++)
    {
        const ZSolid& zsi = solids[i] ; 
        solid = new G4UnionSolid(
				 solidname+zsi.label,
				 solid,     
				 zsi.solid, 
				 0,
				 G4ThreeVector(0,0,zsi.zdelta)
				 );  
    }
    return solid ; 
}

 
