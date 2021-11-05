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


G4VSolid* ZSolid::MakeZCut( const G4VSolid* original, double zcut ) // static
{
    ZSolid* zs = new ZSolid(original); 
    zs->cutTree( zcut );  
    return zs->root ; 
}

ZSolid::ZSolid(const G4VSolid* original_ ) 
    :
    original(original_),
    root(DeepClone(original_)),
    parentmap(MakeParentMap(root)),
    zclsmap(new std::map<const G4VSolid*, int>)
{
    init(); 
}

void ZSolid::init()
{
    dumpTree("ZSolid::init.dumpTree"); 
    dumpUp("ZSolid::init.dumpUp"); 
}

/**
ZSolid::EntityTypeName
-----------------------

Unexpectedly G4 returns EntityType by value rather than by reference
so have to strdup to avoid corruption when the G4String goes out of scope. 

**/

const char* ZSolid::EntityTypeName(const G4VSolid* solid)   // static
{
    G4GeometryType type = solid->GetEntityType();  // G4GeometryType typedef for G4String
    return strdup(type.c_str()); 
}

int ZSolid::EntityType(const G4VSolid* solid)   // static 
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

bool ZSolid::IsBooleanSolid(const G4VSolid* solid) // static
{
    return dynamic_cast<const G4BooleanSolid*>(solid) != nullptr ; 
}
bool ZSolid::IsDisplacedSolid(const G4VSolid* solid) // static
{
    return dynamic_cast<const G4DisplacedSolid*>(solid) != nullptr ; 
}

const G4VSolid* ZSolid::Left(const G4VSolid* solid ) // static
{
    return IsBooleanSolid(solid) ? solid->GetConstituentSolid(0) : nullptr ; 
}

const G4VSolid* ZSolid::Right(const G4VSolid* solid ) // static
{
    return IsBooleanSolid(solid) ? solid->GetConstituentSolid(1) : nullptr ; 
}

G4VSolid* ZSolid::Left_(G4VSolid* solid ) // static
{
    return IsBooleanSolid(solid) ? solid->GetConstituentSolid(0) : nullptr ; 
}
G4VSolid* ZSolid::Right_(G4VSolid* solid ) // static
{
    return IsBooleanSolid(solid) ? solid->GetConstituentSolid(1) : nullptr ; 
}




/**
ZSolid::Moved
---------------

When node isa G4DisplacedSolid sets the rotation and translation and returns the constituentMovedSolid
otherwise returns the input node.

**/
const G4VSolid* ZSolid::Moved( G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* node )  // static
{
    const G4DisplacedSolid* disp = dynamic_cast<const G4DisplacedSolid*>(node) ; 
    if(disp)
    {
        if(rot) *rot = disp->GetFrameRotation();
        if(tla) *tla = disp->GetObjectTranslation();  
    }
    return disp ? disp->GetConstituentMovedSolid() : node  ;
}


G4VSolid* ZSolid::Moved_( G4RotationMatrix* rot, G4ThreeVector* tla, G4VSolid* node )  // static
{
    G4DisplacedSolid* disp = dynamic_cast<G4DisplacedSolid*>(node) ; 
    if(disp)
    {
        if(rot) *rot = disp->GetFrameRotation();
        if(tla) *tla = disp->GetObjectTranslation();  
    }
    return disp ? disp->GetConstituentMovedSolid() : node  ;
}



/**
ZSolid::dumpTree
------------------
 
Postorder traversal of CSG tree
**/
void ZSolid::dumpTree(const char* msg ) const 
{
    std::cout << msg << std::endl ; 
    dumpTree_r(root, 0 ); 
}

void ZSolid::dumpTree_r( const G4VSolid* node_, int depth  ) const
{
    if(ZSolid::IsBooleanSolid(node_))
    {
        dumpTree_r(ZSolid::Left(node_) , depth+1) ; 
        dumpTree_r(ZSolid::Right(node_), depth+1) ; 
    }

    // postorder visit 

    G4RotationMatrix node_rot ;   // node (not tree) transforms
    G4ThreeVector    node_tla(0., 0., 0. ); 
    const G4VSolid*  node = Moved(&node_rot, &node_tla, node_ ); 
    assert( node ); 

    double zdelta_always_zero = getZ(node); 
    assert( zdelta_always_zero == 0. ); 
    // Hmm thats tricky, using node arg always gives zero.
    // Must use node_ which is the one that might be G4DisplacedSolid. 

    double zdelta = getZ(node_) ;  

    std::cout 
        << " type " << std::setw(20) << EntityTypeName(node) 
        << " name " << std::setw(20) << node->GetName() 
        << " depth " << depth 
        << " zdelta "
        << std::fixed << std::setw(7) << std::setprecision(2) << zdelta
        << " node_tla (" 
        << std::fixed << std::setw(7) << std::setprecision(2) << node_tla.x() << " " 
        << std::fixed << std::setw(7) << std::setprecision(2) << node_tla.y() << " "
        << std::fixed << std::setw(7) << std::setprecision(2) << node_tla.z() << ")"
        ;

    if(ZSolid::CanZ(node))
    {
        double z0, z1 ; 
        ZRange(z0, z1, node);  
        std::cout 
            << " z1 " << std::fixed << std::setw(7) << std::setprecision(2) << z1
            << " z0 " << std::fixed << std::setw(7) << std::setprecision(2) << z0 
            << " az1 " << std::fixed << std::setw(7) << std::setprecision(2) << ( z1 + zdelta )
            << " az0 " << std::fixed << std::setw(7) << std::setprecision(2) << ( z0 + zdelta )
            ;
    }
    std::cout 
        << std::endl
        ; 
}

void ZSolid::classifyTree(double zcut)  
{
    std::cout << "ZSolid::classifyTree against zcut " << zcut  << std::endl ; 
    classifyTree_r(root, 0, zcut); 
}

void ZSolid::classifyTree_r( const G4VSolid* node_, int depth, double zcut )
{
    if(ZSolid::IsBooleanSolid(node_))
    {
        classifyTree_r(ZSolid::Left(node_) , depth+1, zcut) ; 
        classifyTree_r(ZSolid::Right(node_), depth+1, zcut) ; 
    }
    else
    {
        double zd = getZ(node_) ;  
        const G4VSolid*  node = Moved(nullptr, nullptr, node_ ); 
        if(ZSolid::CanZ(node))
        {
            double z0, z1 ; 
            ZRange(z0, z1, node);  

            double az0 =  z0 + zd ; 
            double az1 =  z1 + zd ; 

            int zcls = ClassifyZCut( az0, az1, zcut ); 

            std::cout 
                << "ZSolid::classifyTree_r"
                << " zd " << std::fixed << std::setw(7) << std::setprecision(2) << zd
                << " z1 " << std::fixed << std::setw(7) << std::setprecision(2) << z1
                << " z0 " << std::fixed << std::setw(7) << std::setprecision(2) << z0 
                << " az1 " << std::fixed << std::setw(7) << std::setprecision(2) << az1
                << " az0 " << std::fixed << std::setw(7) << std::setprecision(2) << az0 
                << " zcls " << ClassifyName(zcls)
                << std::endl
                ;

            (*zclsmap)[node] = zcls ; 
        }
    }
}



int ZSolid::classifyMask(const G4VSolid* top) const 
{
    return classifyMask_r(top, 0); 
}
int ZSolid::classifyMask_r( const G4VSolid* node_, int depth ) const 
{
    int mask = 0 ; 
    if(ZSolid::IsBooleanSolid(node_))
    {
        mask |= classifyMask_r( ZSolid::Left(node_) , depth+1 ) ; 
        mask |= classifyMask_r( ZSolid::Right(node_), depth+1 ) ; 
    }
    else
    {
        const G4VSolid* node = Moved(nullptr, nullptr, node_ ); 
        mask |= (*zclsmap)[node] ; 
    }
    return mask ; 
}







/**
ZSolid::ClassifyZCut
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


const char* ZSolid::UNDEFINED_ = "UNDEFINED" ; 
const char* ZSolid::INCLUDE_   = "INCLUDE" ; 
const char* ZSolid::STRADDLE_  = "STRADDLE" ; 
const char* ZSolid::EXCLUDE_   = "EXCLUDE" ; 

const char* ZSolid::ClassifyName( int zcls ) // static 
{
    const char* s = nullptr ; 
    switch( zcls )
    {
        case UNDEFINED: s = UNDEFINED_ ; break ; 
        case INCLUDE  : s = INCLUDE_ ; break ; 
        case STRADDLE : s = STRADDLE_ ; break ; 
        case EXCLUDE  : s = EXCLUDE_ ; break ; 
    }
    return s ; 
}










/**
ZSolid::cutTree
------------------

NTreeAnalyse height 7 count 15::

                                                     [un]    

                                              un          cy  

                                      un          cy        

                              un          zs                

                      un          cy                        

              un          co                                

      un          zs                                        

  zs      cy                                                


With this tree structure cutting from the right is easy because can just change the root 

So the steps are:

1. classify the nodes of the tree against the zcut 
2. change STRADDLE node params and transforms according to the zcut
   and set classification to INCLUDE
3. edit the tree to remove the EXCLUDE nodes

**/
void ZSolid::cutTree(double zcut)
{
    std::cout << "ZSolid::cutTree " << zcut << std::endl ; 
    classifyTree(zcut);  
    cutTree_r(root, 0, zcut); 
}

void ZSolid::cutTree_r( G4VSolid* node_, int depth, double zcut )
{
    if(ZSolid::IsBooleanSolid(node_))
    {
        cutTree_r( ZSolid::Left_(node_) , depth+1, zcut ) ; 
        cutTree_r( ZSolid::Right_(node_), depth+1, zcut ) ; 
    }
    else
    {
        // get tree frame zcut into local frame of the node 
        double zdelta = getZ(node_) ; 
        double local_zcut = zcut - zdelta ; 

        G4VSolid* node = Moved_(nullptr, nullptr, node_ ); 
        int zcls = (*zclsmap)[node] ; 

        if( zcls == STRADDLE )
        {
            ApplyZCut( node_, local_zcut ); 
            (*zclsmap)[node] = INCLUDE  ; 
        } 
    }
}



void ZSolid::collectNodes( std::vector<const G4VSolid*>& nodes, const G4VSolid* top, int query_zcls  )
{
    collectNodes_r(nodes, top, 0, query_zcls);  
}

void ZSolid::collectNodes_r( std::vector<const G4VSolid*>& nodes, const G4VSolid* node_, int query_zcls, int depth  )
{
    if(ZSolid::IsBooleanSolid(node_))
    {
        collectNodes_r( nodes, ZSolid::Left(node_) , query_zcls, depth+1 ) ; 
        collectNodes_r( nodes, ZSolid::Right(node_), query_zcls, depth+1 ) ; 
    }
    else
    {
        const G4VSolid* node = Moved(nullptr, nullptr, node_ ); 
        int zcls = (*zclsmap)[node] ; 
        if( zcls == query_zcls )
        {
            nodes.push_back(node) ;  // node_ ?
        } 
    }
} 





void ZSolid::ApplyZCut( G4VSolid* node_, double local_zcut ) // static
{
    G4VSolid* node = Moved_(nullptr, nullptr, node_ ); 

    std::cout << "ZSolid::ApplyZCut " << ZSolid::EntityTypeName(node) << std::endl ; 

    switch(ZSolid::EntityType(node))
    {
        case _G4Ellipsoid: ApplyZCut_G4Ellipsoid( node  , local_zcut);  break ; 
        case _G4Tubs:      ApplyZCut_G4Tubs(      node_ , local_zcut);  break ;  // cutting tubs requires changing the transform, hence node_
        case _G4Polycone:  ApplyZCut_G4Polycone(  node  , local_zcut);  break ; 
        default: 
            { 
                std::cout 
                    << "ZSolid::ApplyZCut FATAL : not implemented for entityType " 
                    << ZSolid::EntityTypeName(node) 
                    << std::endl ; 
                assert(0) ; 
            } ;
    }
}

/**
ZSolid::ApplyZCut_G4Ellipsoid
--------------------------------
     
::

    local                                             absolute 
    frame                                             frame    

    z1  +-----------------------------------------+    zd   
         \                                       /
           
            .                              .
    _________________________________________________ zcut 
                .                     .
                                 
    z0                 .      .   
                         
                                     
**/


void ZSolid::ApplyZCut_G4Ellipsoid( G4VSolid* node, double local_zcut)
{  
    G4Ellipsoid* ellipsoid =  dynamic_cast<G4Ellipsoid*>(node) ;  
    assert(ellipsoid); 

    double z0 = ellipsoid->GetZBottomCut() ; 
    double z1 = ellipsoid->GetZTopCut() ;
    
    double new_z0 = local_zcut ; 
    assert( new_z0 >= z0 && new_z0 < z1 ); 
    double new_z1 = z1 ; 

    ellipsoid->SetZCuts( new_z0, new_z1 ); 
}


/**
ZSolid::ApplyZCut_G4Polycone
------------------------------

Currently limited to only 2 Z-planes, 
to support more that 2 would need to delve 
into the r-z details which should be straightforward, 
just it is not yet implemented. 

**/

void ZSolid::ApplyZCut_G4Polycone( G4VSolid* node, double local_zcut)
{  
    G4Polycone* polycone = dynamic_cast<G4Polycone*>(node) ;  
    assert(polycone); 
    G4PolyconeHistorical* pars = polycone->GetOriginalParameters(); 

    unsigned num_z = pars->Num_z_planes ; 
    for(unsigned i=1 ; i < num_z ; i++)
    {
        double z0 = pars->Z_values[i-1] ; 
        double z1 = pars->Z_values[i] ; 
        assert( z1 > z0 );   
    }

    assert( num_z == 2 );    // simplifying assumption 
    pars->Z_values[0] = local_zcut ;   // get into polycone local frame

    polycone->SetOriginalParameters(pars); // not necessary, its a pointer 
}


/**
ZSolid::ApplyZCut_G4Tubs
----------------------------

Cutting G4Tubs::


     zd+hz  +---------+               +---------+     new_zd + new_hz
            |         |               |         |  
            |         |               |         |
            |         |               |         |
            |         |             __|_________|__   new_zd
            |         |               |         |
     zd   --|---------|--             |         |
            |         |               |         |
            |         |               |         |
         .  | . . . . | . .zcut . . . +---------+ . . new_zd - new_hz  . . . . . .
            |         | 
            |         |
    zd-hz   +---------+ 


     cut position

          zcut = new_zd - new_hz 
          new_zd = zcut + new_hz  


     original height:  2*hz                         
      
     cut height :     

          loc_zcut = zcut - zd 

          2*new_hz = 2*hz - (zcut-(zd-hz)) 

                   = 2*hz - ( zcut - zd + hz )

                   = 2*hz -  zcut + zd - hz 

                   = hz + zd - zcut 

                   = hz - (zcut - zd)             

                   = hz - loc_zcut 


                                    hz + zd - zcut
                        new_hz =  -----------------
                                         2

                                    hz - loc_zcut 
                        new_hz =  --------------------      new_hz( loc_zcut:-hz ) = hz     unchanged
                                          2                 new_hz( loc_zcut:0   ) = hz/2   halved
                                                            new_hz( loc_zcut:+hz ) =  0     made to disappear 


       +hz  +---------+               +---------+     zoff + new_hz
            |         |               |         |  
            |         |               |         |
            |         |               |         |
            |         |             __|_________|__   zoff 
            |         |               |         |
        0 --|---------|- . . . . . . . . . . . . . . . 0 
            |         |               |         |
            |         |               |         |
   loc_zcut | . . . . | . . . . .  .  +---------+ . . zoff - new_hz  . . . . . .
            |         | 
            |         |
      -hz   +---------+. . . . . . . . . . . . 


            loc_zcut = zoff - new_hz

                zoff = loc_zcut + new_hz 

                     = loc_zcut +  (hz - loc_zcut)/2

                     =  2*loc_zcut + (hz - loc_zcut)
                        ------------------------------
                                   2

               zoff  =  loc_zcut + hz                   zoff( loc_zcut:-hz ) = 0      unchanged
                        ---------------                 zoff( loc_zcut:0   ) = hz/2   
                              2                         zoff( loc_zcut:+hz ) = hz     makes sense, 
                                                                                      think about just before it disappears

**/


void ZSolid::ApplyZCut_G4Tubs( G4VSolid* node_ , double local_zcut )
{ 
    G4VSolid* node = Moved_(nullptr, nullptr, node_ ); 
    G4Tubs* tubs = dynamic_cast<G4Tubs*>(node) ;  
    assert(tubs); 

    double hz = tubs->GetZHalfLength() ; 
    double new_hz = (hz - local_zcut)/2. ;  
    tubs->SetZHalfLength(new_hz);  

    double zoffset = (local_zcut + hz)/2. ; 

    G4DisplacedSolid* disp = dynamic_cast<G4DisplacedSolid*>(node_) ; 
    assert( disp ); // transform must be associated as must change offset to cut G4Tubs

    G4ThreeVector objTran = disp->GetObjectTranslation() ; 
    objTran.setZ( objTran.z() + zoffset ); 
    disp->SetObjectTranslation( objTran ); 
}


/**
ZSolid::dumpUp
----------------

Ordinary postorder recursive traverse in order to get to all nodes. 
This approach should allow to obtain combination transforms in
complex trees. 

**/

void ZSolid::dumpUp(const char* msg) const 
{
    assert( parentmap ); 
    std::cout << msg << std::endl ; 
    dumpUp_r(root, 0); 
}

void ZSolid::dumpUp_r(const G4VSolid* node, int depth) const  
{
    if(IsBooleanSolid(node))
    {
        dumpUp_r(ZSolid::Left(  node ), depth+1 ); 
        dumpUp_r(ZSolid::Right( node ), depth+1 ); 
    }
    else
    {
        G4RotationMatrix tree_rot ; 
        G4ThreeVector    tree_tla(0., 0., 0. ); 
        getTreeTransform(&tree_rot, &tree_tla, node ); 

        const G4VSolid* nd = Moved(nullptr, nullptr, node); 
        std::cout 
            << "ZSolid::dumpUp_r" 
            << " depth " << depth 
            << " type " << std::setw(20) << EntityTypeName(nd) 
            << " name " << std::setw(20) << nd->GetName() 
            << " tree_tla (" 
            << std::fixed << std::setw(7) << std::setprecision(2) << tree_tla.x() << " " 
            << std::fixed << std::setw(7) << std::setprecision(2) << tree_tla.y() << " "
            << std::fixed << std::setw(7) << std::setprecision(2) << tree_tla.z() 
            << ")"
            << std::endl
            ; 
   }
}


/**
ZSolid::getTreeTransform
-------------------------------

Would normally use parent links to determine all transforms relevant to a node, 
but Geant4 boolean trees do not have parent links. 
Hence use an external parentmap to provide uplinks enabling iteration 
up the tree from any node up to the root. 

**/

void ZSolid::getTreeTransform( G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* node ) const 
{
    const G4VSolid* nd = node ; 

    unsigned count = 0 ; 
    while(nd)
    {
        G4RotationMatrix r ; 
        G4ThreeVector    t(0., 0., 0. ); 
        const G4VSolid* dn = Moved( &r, &t, nd ); 
        assert( r.isIdentity() );  // simplifying assumption 

        *tla += t ;    // add up the translations 

        if(false) std::cout
            << "ZSolid::getTreeTransform" 
            << " count " << std::setw(2) << count 
            << " dn.name " << std::setw(20) << dn->GetName()
            << " dn.type " << std::setw(20) << dn->GetEntityType()
            << " dn.t (" 
            << std::fixed << std::setw(7) << std::setprecision(2) << t.x() << " " 
            << std::fixed << std::setw(7) << std::setprecision(2) << t.y() << " "
            << std::fixed << std::setw(7) << std::setprecision(2) << t.z() 
            << ")"
            << " tla (" 
            << std::fixed << std::setw(7) << std::setprecision(2) << tla->x() << " " 
            << std::fixed << std::setw(7) << std::setprecision(2) << tla->y() << " "
            << std::fixed << std::setw(7) << std::setprecision(2) << tla->z() 
            << ")"
            << std::endl 
            ; 

        nd = (*parentmap)[nd] ; // parentmap lineage uses G4DisplacedSolid so not using *dn* here
        count += 1 ; 
    }     
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

G4VSolid* ZSolid::DeepClone_r( const G4VSolid* node_, int depth, G4RotationMatrix* rot, G4ThreeVector* tla )  // static 
{
    const G4VSolid* node = Moved( rot, tla, node_ ); 

    if(false) std::cout 
        << "ZSolid::DeepClone_r(preorder visit)"
        << " type " << std::setw(20) << EntityTypeName(node)
        << " name " << std::setw(20) << node->GetName()
        << " depth " << std::setw(2) << depth
        << " tla (" << tla->x() << " " << tla->y() << " " << tla->z() << ")" 
        << std::endl 
        ; 

    G4VSolid* clone = IsBooleanSolid(node) ? BooleanClone(node, depth, rot, tla ) : PrimitiveClone(node) ; 
    assert(clone);
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
ZSolid::MakeParentMap
-----------------------

Note that the parentmap uses the G4DisplacedSolid (not the G4VSolid that it points to) 
in order to have treewise access to the transform up the lineage. 

**/

std::map<const G4VSolid*, const G4VSolid*>* ZSolid::MakeParentMap( const G4VSolid* root ) // static
{
    std::map<const G4VSolid*, const G4VSolid*>* parentmap = new std::map<const G4VSolid*, const G4VSolid*> ; 
    (*parentmap)[root] = nullptr ;  // root has no parent by definition

    std::cout << "ZSolid::MakeParentMap" << std::endl ; 
    FillParentMap_r( root, parentmap );   
    return parentmap ; 
}

void ZSolid::FillParentMap_r( const G4VSolid* node, std::map<const G4VSolid*,const G4VSolid*>* parentmap ) // static
{
    if(ZSolid::IsBooleanSolid(node))
    {
        const G4VSolid* l = ZSolid::Left(node) ; 
        const G4VSolid* r = ZSolid::Right(node) ; 

        FillParentMap_r( l ,parentmap );  
        FillParentMap_r( r, parentmap );  

        // postorder visit 
        (*parentmap)[l] = node ; 
        (*parentmap)[r] = node ; 
    }
}

double ZSolid::getZ( const G4VSolid* node ) const
{
    G4RotationMatrix tree_rot ; 
    G4ThreeVector    tree_tla(0., 0., 0. ); 
    getTreeTransform(&tree_rot, &tree_tla, node ); 

    double zdelta = tree_tla.z() ; 
    return zdelta ; 
}

bool ZSolid::CanZ( const G4VSolid* solid ) // static
{
    int type = EntityType(solid) ; 
    return type == _G4Ellipsoid || type == _G4Tubs || type == _G4Polycone ; 
}
void ZSolid::ZRange( double& z0, double& z1, const G4VSolid* solid) // static  
{
    switch(EntityType(solid))
    {
        case _G4Ellipsoid: GetZRange( dynamic_cast<const G4Ellipsoid*>(solid), z0, z1 );  break ; 
        case _G4Tubs:      GetZRange( dynamic_cast<const G4Tubs*>(solid)    ,  z0, z1 );  break ; 
        case _G4Polycone:  GetZRange( dynamic_cast<const G4Polycone*>(solid),  z0, z1 );  break ; 
        case _G4Other:    { std::cout << "ZSolid::GetZ FATAL : not implemented for entityType " << EntityTypeName(solid) << std::endl ; assert(0) ; } ; break ;  
    }
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

