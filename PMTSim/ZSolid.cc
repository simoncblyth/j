#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4Ellipsoid.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4RotationMatrix.hh"

#include "ZSolid.hh"
#include "NP.hh"




ZSolid::ZSolid(const G4VSolid* original_ ) 
    :
    original(original_),
    root(DeepClone(original_))
{
    init(); 
}

void ZSolid::init()
{
    FillParentMap(root, &parentmap); 
    DumpTree(root, "ZSolid::init.DumpTree"); 
}

/**
ZSolid::EntityTypeName
-----------------------

Unexpectedly G4 returns EntityType by value rather than by reference
so have to strdup to avoid corruption when the G4String goes out of scope. 

**/

const char* ZSolid::EntityTypeName(const G4VSolid* const solid)   // static
{
    G4GeometryType type = solid->GetEntityType();  // G4GeometryType typedef for G4String
    return strdup(type.c_str()); 
}

int ZSolid::EntityType(const G4VSolid* const solid)   // static 
{
    const char* name = EntityTypeName(solid); 
    int type = _G4Other ; 
    if( strcmp(name, "G4Ellipsoid") == 0 )         type = _G4Ellipsoid ; 
    if( strcmp(name, "G4Tubs") == 0 )              type = _G4Tubs ; 
    if( strcmp(name, "G4Polycone") == 0 )          type = _G4Polycone ; 
    if( strcmp(name, "G4UnionSolid") == 0 )        type = _G4UnionSolid ; 
    if( strcmp(name, "G4SubtractionSolid") == 0 )  type = _G4SubtractionSolid ; 
    if( strcmp(name, "G4IntersectionSolid") == 0 ) type = _G4IntersectionSolid ; 
    if( strcmp(name, "G4DisplacedSolid") == 0 )    type = _G4DisplacedSolid ; 
    return type ; 
}

bool ZSolid::IsBooleanSolid(const G4VSolid* const solid) // static
{
    return dynamic_cast<const G4BooleanSolid*>(solid) != nullptr ; 
}
bool ZSolid::IsDisplacedSolid(const G4VSolid* const solid) // static
{
    return dynamic_cast<const G4DisplacedSolid*>(solid) != nullptr ; 
}
const G4VSolid* ZSolid::GetLeft(const G4VSolid* const solid ) // static
{
    return IsBooleanSolid(solid) ? solid->GetConstituentSolid(0) : nullptr ; 
}
const G4VSolid* ZSolid::GetRight(const G4VSolid* const solid ) // static
{
    return IsBooleanSolid(solid) ? solid->GetConstituentSolid(1) : nullptr ; 
}



/**
ZSolid::DumpTree
------------------
 
Postorder traversal of CSG tree
**/
void ZSolid::DumpTree( const G4VSolid* solid, const char* msg )  // static
{
    std::cout << msg << std::endl ; 
    DumpTree_r(solid, 0 ); 
}

void ZSolid::DumpTree_r( const G4VSolid* solid_, int depth  )  // static
{
    const G4VSolid* left  = ZSolid::GetLeft( solid_ ); 
    const G4VSolid* right = ZSolid::GetRight(solid_ );

    if(left && right)
    {
        DumpTree_r(left,  depth+1) ; 
        DumpTree_r(right, depth+1) ; 
    }

    // postorder visit 
    G4RotationMatrix rot ; 
    G4ThreeVector tla(0., 0., 0. ); 

    const G4DisplacedSolid* disp = dynamic_cast<const G4DisplacedSolid*>(solid_) ; 
    const G4VSolid* solid = disp ? disp->GetConstituentMovedSolid() : solid_  ;
    assert( solid ); 

    GetDisplacedSolidTransform( &rot, &tla, disp ); 

    std::cout 
        << " type " << std::setw(20) << EntityTypeName(solid) 
        << " name " << std::setw(20) << solid->GetName() 
        << " depth " << depth 
        << " tla (" 
        << std::fixed << std::setw(7) << std::setprecision(2) << tla.x() << " " 
        << std::fixed << std::setw(7) << std::setprecision(2) << tla.y() << " "
        << std::fixed << std::setw(7) << std::setprecision(2) << tla.z() << ")"
        << std::endl
        ; 
}


/**
ZSolid::DumpUp
----------------

Ordinary postorder recursive traverse in order to get to all nodes. 
Then from each node follow the parentmap uplinks to iterate up the 
tree to the root from every primitive leaf node.  

This approach should allow to obtain combination transforms in
complex trees. 

**/

void ZSolid::DumpUp(const G4VSolid* solid, std::map<const G4VSolid*,const G4VSolid*>* parentmap  )  // static
{
    assert( parentmap ); 
    std::cout << "ZSolid::DumpUp" << std::endl ; 
    DumpUp_r(solid, 0, parentmap ); 
}

void ZSolid::DumpUp_r(const G4VSolid* solid, int depth, std::map<const G4VSolid*,const G4VSolid*>* parentmap )  // static
{
    const G4VSolid* left  = ZSolid::GetLeft( solid ); 
    const G4VSolid* right = ZSolid::GetRight(solid );

    if(left && right)
    {
        DumpUp_r(left,  depth+1, parentmap ); 
        DumpUp_r(right, depth+1, parentmap ); 
    }
    else
    {
        std::cout << "ZSolid::DumpUp_r from depth " << depth << std::endl ; 
        unsigned elevation = 0 ; 
        const G4VSolid* node = solid ; 
        while(node)
        {
            const G4DisplacedSolid* disp = dynamic_cast<const G4DisplacedSolid*>(node) ; 
            const G4VSolid* dnode = disp ? disp->GetConstituentMovedSolid()  : node ; 

            G4RotationMatrix rot ; 
            G4ThreeVector tla(0., 0., 0. ); 
            GetDisplacedSolidTransform( &rot, &tla, disp ); 

            std::cout 
                << " elevation " << std::setw(3) << elevation
                << " dnode " << std::setw(20) << dnode->GetName()
                << " type " << std::setw(20) << dnode->GetEntityType()
                << " tla (" 
                << std::fixed << std::setw(7) << std::setprecision(2) << tla.x() << " " 
                << std::fixed << std::setw(7) << std::setprecision(2) << tla.y() << " "
                << std::fixed << std::setw(7) << std::setprecision(2) << tla.z() << ")"
                << std::endl 
                ; 

            node = (*parentmap)[node] ; // parentmap lineage uses G4DisplacedSolid so do not use dnode here
            elevation += 1 ;  
        }     
    }
}


/**
ZSolid::RecursiveDisplacement
-------------------------------

Would normally use parent links to determine all transforms relevant to a node, 
but Geant4 boolean trees do not have parent links. 

**/

void ZSolid::RecursiveDisplacement( G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* node, std::map<const G4VSolid*,const G4VSolid*>* parentmap )
{
    if(!parentmap) return ;  
    std::cout << "ZSolid::RecursiveDisplacement" << std::endl ; 
}  


/**
ZSolid::GetDisplacedSolidTransform
------------------------------------

When solid ISA G4DisplacedSolid sets the rotation and translation 

**/

void ZSolid::GetDisplacedSolidTransform( G4RotationMatrix* rot, G4ThreeVector* tla, const G4DisplacedSolid* disp ) // static
{
    if(!disp) return ; 
    if(rot) *rot = disp->GetFrameRotation();
    if(rot) assert( rot->isIdentity() ); 
    if(tla) *tla = disp->GetObjectTranslation();  
}


/**
ZSolid::DeepClone
-------------------

Clones a CSG tree of solids, assuming that the tree is
composed only of the limited set of primitives that are supported. 

G4BooleanSolid copy ctor just steals constituent pointers so 
it does not make an independent copy.  
Unlike the primitive copy ctors (at least those looked at: G4Polycone, G4Tubs) 
which appear to make properly independent copies 

**/

G4VSolid* ZSolid::DeepClone( const  G4VSolid* solid )  // static 
{
    G4RotationMatrix rot ; 
    G4ThreeVector tla ; 
    int depth = 0 ; 
    return DeepClone_r(solid, depth, &rot, &tla );  
}

/**
ZSolid::DeepClone_r
--------------------

G4DisplacedSolid is a wrapper for the for the right hand side of boolean constituent 
of a boolean combination which serves the purpose of holding the transform. 
The G4DisplacedSolid is automatically created by the G4BooleanSolid ctor when there is
an associated transform.  

The below *rot* and *tla* look at first glance like they are not used. 
But look more closely, the recursive DeepClone_r calls within BooleanClone are using them 
across the generations. This structure is necessary for BooleanClone because the 
transform from the child is needed when cloning the parent.

**/

G4VSolid* ZSolid::DeepClone_r( const G4VSolid* _solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla )  // static 
{
    const G4DisplacedSolid* disp = dynamic_cast<const G4DisplacedSolid*>(_solid) ; 
    const G4VSolid* solid = disp ? disp->GetConstituentMovedSolid() : _solid  ;
    assert(solid); 
    GetDisplacedSolidTransform( rot, tla, disp ); 

    G4String name = solid->GetName() ; 
    if(false) std::cout 
        << "ZSolid::DeepClone_r(preorder visit)"
        << " type " << std::setw(20) << EntityTypeName(solid)
        << " name " << std::setw(20) << name
        << " depth " << std::setw(2) << depth
        << " tla (" << tla->x() << " " << tla->y() << " " << tla->z() << ")" 
        << std::endl 
        ; 

    G4VSolid* clone = IsBooleanSolid(solid) ? BooleanClone(solid, depth, rot, tla ) : PrimitiveClone(solid) ; 
    assert(clone);
    clone->SetName(name+"_clone") ; 
    return clone ; 
}    

G4VSolid* ZSolid::BooleanClone( const  G4VSolid* solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla ) // static
{
    G4String name = solid->GetName() ; 
    G4RotationMatrix lrot, rrot ;  
    G4ThreeVector    ltra, rtra ; 

    const G4BooleanSolid* src_boolean = dynamic_cast<const G4BooleanSolid*>(solid) ; 
    G4VSolid* left  = DeepClone_r( src_boolean->GetConstituentSolid(0), depth+1, &lrot, &ltra ) ; 
    G4VSolid* right = DeepClone_r( src_boolean->GetConstituentSolid(1), depth+1, &rrot, &rtra ) ; 

    assert( dynamic_cast<const G4DisplacedSolid*>(left) == nullptr  ) ; // not expecting these to be displaced 
    assert( dynamic_cast<const G4DisplacedSolid*>(right) == nullptr ) ; 
    assert( lrot.isIdentity() );   // lrot is expected to always be identity, as G4 never has left transforms
    assert( ltra.x() == 0. && ltra.y() == 0. && ltra.z() == 0. );  // not expecting transforms on the left
    assert( rrot.isIdentity() );   // rrot identity is a simplifying assumption

    G4VSolid* clone = nullptr ; 
    switch(EntityType(solid))
    {
        case _G4UnionSolid        : clone = new G4UnionSolid(       name, left, right, &rrot, rtra ) ; break ; 
        case _G4SubtractionSolid  : clone = new G4SubtractionSolid( name, left, right, &rrot, rtra ) ; break ;
        case _G4IntersectionSolid : clone = new G4IntersectionSolid(name, left, right, &rrot, rtra ) ; break ; 
    } 
    CheckBooleanClone( clone, left, right ); 
    return clone ; 
}

void ZSolid::CheckBooleanClone( const G4VSolid* clone, const G4VSolid* left, const G4VSolid* right ) // static
{
    if(!clone) std::cout << "ZSolid::CheckBooleanClone FATAL " << std::endl ; 
    assert(clone); 
    const G4BooleanSolid* boolean = dynamic_cast<const G4BooleanSolid*>(clone) ; 

    // lhs is never wrapped in G4DisplacedSolid 
    const G4VSolid* lhs = boolean->GetConstituentSolid(0) ; 
    const G4DisplacedSolid* lhs_disp = dynamic_cast<const G4DisplacedSolid*>(lhs) ; 
    assert( lhs_disp == nullptr && lhs == left ) ;      

    // rhs will be wrapped in G4DisplacedSolid as above G4BooleanSolid ctor has transform rrot/rtla
    const G4VSolid* rhs = boolean->GetConstituentSolid(1) ; 
    const G4DisplacedSolid* rhs_disp = dynamic_cast<const G4DisplacedSolid*>(rhs) ; 
    assert( rhs_disp != nullptr && rhs != right);    
    const G4VSolid* right_check = rhs_disp->GetConstituentMovedSolid() ;
    assert( right_check == right );  
}


G4VSolid* ZSolid::PrimitiveClone( const  G4VSolid* solid )  // static 
{
    G4VSolid* clone = nullptr ; 
    int type = EntityType(solid); 
    if( type == _G4Ellipsoid )
    {
        const G4Ellipsoid* ellipsoid = dynamic_cast<const G4Ellipsoid*>(solid) ; 
        clone = new G4Ellipsoid(*ellipsoid) ;
    }
    else if( type == _G4Tubs )
    {
        const G4Tubs* tubs = dynamic_cast<const G4Tubs*>(solid) ; 
        clone = new G4Tubs(*tubs) ;  
    }
    else if( type == _G4Polycone )
    {
        const G4Polycone* polycone = dynamic_cast<const G4Polycone*>(solid) ; 
        clone = new G4Polycone(*polycone) ;  
    }
    else
    {
        std::cout 
            << "ZSolid::PrimitiveClone FATAL unimplemented prim type " << EntityTypeName(solid) 
            << std::endl 
            ;
        assert(0); 
    } 
    return clone ; 
}








/**
ZSolid::FillParentMap
-----------------------

Note that the parentmap uses the G4DisplacedSolid (not the G4Vsolid that it points to) 
in order to have treewise access to the transform up the lineage. 

**/

void ZSolid::FillParentMap( const G4VSolid* solid, std::map<const G4VSolid*,const G4VSolid*>* parentmap ) // static
{
    assert( parentmap ); 
    std::cout << "ZSolid::FillParentMap" << std::endl ; 
    (*parentmap)[solid] = nullptr ;  // root has no parent 

    FillParentMap_r( solid, parentmap );   
}

void ZSolid::FillParentMap_r( const G4VSolid* solid, std::map<const G4VSolid*,const G4VSolid*>* parentmap ) // static
{
    const G4VSolid* l = ZSolid::GetLeft(solid) ; 
    const G4VSolid* r = ZSolid::GetRight(solid) ; 
    if(l && r)
    {
        FillParentMap_r( l ,parentmap );  
        FillParentMap_r( r, parentmap );  
        // postorder visit 
        (*parentmap)[l] = solid ; 
        (*parentmap)[r] = solid ; 
    }
}




/**
ZSolid::classifyZCut
------------------------

Inclusion status of solid with regard to a particular zcut::

                       --- 
                        .
                        .   EXCLUDE  : zcut entirely above the solid
                        .
                        .
      +---zd+z1----+   --- 
      |            |    .   
      | . zd . . . |    .   STRADDLE : zcut within z range of solid
      |            |    .
      +---zd+z0 ---+   ---
                        .
                        .   INCLUDE  : zcut fully below the solid 
                        .
                        .
                       ---  

**/


int ZSolid::ClassifyZCut( double az0, double az1, double zcut ) // static
{
    assert( az1 > az0 ); 
    int cls = UNDEFINED ; 
    if(       zcut < az1 && zcut < az0 ) cls = INCLUDE ; 
    else if ( zcut < az1 && zcut > az0 ) cls = STRADDLE ; 
    else if ( zcut > az1 && zcut > az0 ) cls = EXCLUDE ; 
    return cls ; 
}




double ZSolid::GetZ( const G4VSolid* const solid, int idx) // static  
{
    double z0, z1 ; 
    switch(EntityType(solid))
    {
        case _G4Ellipsoid: GetZRange( dynamic_cast<const G4Ellipsoid*>(solid), z0, z1 );  break ; 
        case _G4Tubs:      GetZRange( dynamic_cast<const G4Tubs*>(solid)    ,  z0, z1 );  break ; 
        case _G4Polycone:  GetZRange( dynamic_cast<const G4Polycone*>(solid),  z0, z1 );  break ; 
        case _G4Other:    { std::cout << "ZSolid::GetZ FATAL : not implemented for entityType " << EntityTypeName(solid) << std::endl ; assert(0) ; } ; break ;  
    }
    return idx == 0 ? z0 : z1 ; 
}

void ZSolid::GetZRange( const G4Ellipsoid* const ellipsoid, double& _z0, double& _z1 )  // static 
{
    _z1 = ellipsoid->GetZTopCut() ; 
    _z0 = ellipsoid->GetZBottomCut() ;  
}
void ZSolid::GetZRange( const G4Tubs* const tubs, double& _z0, double& _z1 )  // static 
{
    _z1 = tubs->GetZHalfLength() ;  
    _z0 = -_z1 ;  
    assert( _z1 > 0. ); 
}
void ZSolid::GetZRange( const G4Polycone* const polycone, double& _z0, double& _z1 )  // static 
{
    G4PolyconeHistorical* pars = polycone->GetOriginalParameters(); 
    unsigned num_z = pars->Num_z_planes ; 
    for(unsigned i=1 ; i < num_z ; i++)
    {
        double z0 = pars->Z_values[i-1] ; 
        double z1 = pars->Z_values[i] ; 
        assert( z1 > z0 );   
    }
    _z1 = pars->Z_values[num_z-1] ; 
    _z0 = pars->Z_values[0] ;  
}


