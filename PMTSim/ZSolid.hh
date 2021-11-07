#pragma once

class G4VSolid ; 
class G4Ellipsoid ; 
class G4Tubs ; 
class G4Polycone ; 
class G4DisplacedSolid ; 

#include "G4RotationMatrix.hh" 
#include "G4ThreeVector.hh" 

#include <string>
#include <map>
#include <vector>


#include "PMTSIM_API_EXPORT.hh"

/**
ZSolid : CSG tree manipulations  
=================================

**/

struct ZCanvas ; 

struct PMTSIM_API ZSolid   
{
    // primary API
    static G4VSolid* CreateZCutTree( const G4VSolid* original, double zcut ); 

    // members
    const G4VSolid* original ; 
    G4VSolid*       root ;     // DeepClone of original, which should be identical to original AND fully independent 

    const G4VSolid* candidate_root ; 

    std::map<const G4VSolid*, const G4VSolid*>* parent_map ; 
    std::map<const G4VSolid*, int>*             in_map ; 
    std::map<const G4VSolid*, int>*             rin_map ; 
    std::map<const G4VSolid*, int>*             pre_map ; 
    std::map<const G4VSolid*, int>*             rpre_map ; 
    std::map<const G4VSolid*, int>*             post_map ; 
    std::map<const G4VSolid*, int>*             rpost_map ; 
    std::map<const G4VSolid*, int>*             zcls_map ; 
    std::map<const G4VSolid*, int>*             depth_map ; 

    unsigned width ; 
    unsigned height ; 
    ZCanvas* canvas ; 

    std::vector<const G4VSolid*> inorder ; 
    std::vector<const G4VSolid*> rinorder ; 
    std::vector<const G4VSolid*> preorder ; 
    std::vector<const G4VSolid*> rpreorder ; 
    std::vector<const G4VSolid*> postorder ; 
    std::vector<const G4VSolid*> rpostorder ; 



    // object methods
    ZSolid(const G4VSolid* root ); 

    void init(); 
    void instrumentTree();
    void dump(const char* msg="ZSolid::dump") const ; 

    void parent_r(    const G4VSolid* node, int depth); 
    void depth_r(     const G4VSolid* node, int depth);
    void inorder_r(   const G4VSolid* node, int depth);
    void rinorder_r(  const G4VSolid* node, int depth);
    void preorder_r(  const G4VSolid* node, int depth);
    void rpreorder_r( const G4VSolid* node, int depth);
    void postorder_r( const G4VSolid* node, int depth);
    void rpostorder_r(const G4VSolid* node, int depth);

    const G4VSolid* parent( const G4VSolid* node_) const ;
    int depth( const G4VSolid* node_) const ;
    int in(    const G4VSolid* node_) const ;
    int rin(   const G4VSolid* node_) const ;
    int pre(   const G4VSolid* node_) const ;
    int rpre(  const G4VSolid* node_) const ;
    int post(  const G4VSolid* node_) const ;
    int rpost( const G4VSolid* node_) const ;
    int index( const G4VSolid* n, int mode ) const ; 

    enum { IN, RIN, PRE, RPRE, POST, RPOST } ; 

    static const char* IN_ ; 
    static const char* RIN_ ;
    static const char* PRE_ ; 
    static const char* RPRE_ ;
    static const char* POST_ ;
    static const char* RPOST_ ;
    static const char* OrderName(int mode);



    double getZ(const G4VSolid* node ) const ; 
    void   getTreeTransform( G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* node ) const ; 

    int classifyTree( double zcut ); 
    int classifyTree_r( const G4VSolid* node_, int depth, double zcut ); 

    int classifyMask(const G4VSolid* top) const ;
    int classifyMask_r( const G4VSolid* node_, int depth ) const ;

    void cutTree(double zcut);
    void cutTree_r( G4VSolid* node_, int depth, double zcut ); 

    void findCandidateRoot();
    void findCandidateRoot_r(const G4VSolid* n, int depth);

    void collectNodes( std::vector<const G4VSolid*>& nodes, const G4VSolid* top, int query_zcls  );
    void collectNodes_r( std::vector<const G4VSolid*>& nodes, const G4VSolid* node_, int query_zcls, int depth  );

    void draw(const char* msg="ZSolid::draw"); 
    void draw_r( const G4VSolid* n, int mode); 

    int zcls( const G4VSolid* node_, bool move) const ;
    void set_zcls( const G4VSolid* node_, bool move, int zc ); 

    int maxdepth() const  ;
    static int Maxdepth_r( const G4VSolid* node_, int depth); 

    void dumpUp(const char* msg="ZSolid::dumpUp") const ; 
    void dumpUp_r(const G4VSolid* node, int depth) const ; 

    void dumpTree(const char* msg="ZSolid::dumpTree" ) const ; 
    void dumpTree_r( const G4VSolid* node, int depth ) const ; 

    // enumerations
    enum { 
        _G4Other, 
        _G4Ellipsoid, 
        _G4Tubs, 
        _G4Polycone, 
        _G4UnionSolid, 
        _G4SubtractionSolid, 
        _G4IntersectionSolid, 
        _G4DisplacedSolid 
     }; 

    enum { 
       UNDEFINED=0, 
         INCLUDE=1<<0, 
        STRADDLE=1<<1, 
         EXCLUDE=1<<2 
     }; 

    static const char* UNDEFINED_ ; 
    static const char* INCLUDE_; 
    static const char* STRADDLE_ ; 
    static const char* EXCLUDE_; 
    static const char* ClassifyName( int zcls ); 
    static const char* ClassifyMaskName( int zcls ); 

    // simple static convenience functions
    static int    ClassifyZCut( double az0, double az1, double zcut ); 

    // basic solid functions
    static int             EntityType(      const G4VSolid* solid) ; 
    static const char*     EntityTypeName(  const G4VSolid* solid) ; 
    static const char*     EntityTag(       const G4VSolid* solid, bool move ) ; // move:true sees thru G4DisplacedSolid 
    static bool            Boolean(         const G4VSolid* solid) ;
    static bool            Displaced(       const G4VSolid* solid) ;

    // navigation
    static const G4VSolid* Left(  const G4VSolid* node) ;
    static const G4VSolid* Right( const G4VSolid* node) ;
    static const G4VSolid* Moved( G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* node) ;

    static       G4VSolid* Left_(       G4VSolid* node) ;
    static       G4VSolid* Right_(      G4VSolid* node) ;
    static       G4VSolid* Moved_( G4RotationMatrix* rot, G4ThreeVector* tla,      G4VSolid* node) ;

    // local node frame access 
    static void ZRange( double& z0, double& z1,  const G4VSolid* solid ) ; 
    static bool CanZ(   const G4VSolid* solid ); 
    static void GetZRange( const G4Ellipsoid* const ellipsoid, double& z0, double& z1 );
    static void GetZRange( const G4Tubs*      const tubs     , double& z0, double& z1 ); 
    static void GetZRange( const G4Polycone*  const polycone , double& z0, double& z1 ); 

    // tree cloning methods
    static G4VSolid* DeepClone(    const G4VSolid* solid ); 
    static G4VSolid* DeepClone_r(  const G4VSolid* solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla ); 
    static G4VSolid* BooleanClone( const G4VSolid* solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla ); 


    static void GetBooleanBytes(char** bytes, int& num_bytes, const G4VSolid* solid );
    static int CompareBytes( char* bytes0, char* bytes1, int num_bytes ); 
    static void PlacementNewDupe( G4VSolid* solid); 
    static void PlacementNewSetRight(  G4VSolid* solid, G4VSolid* right, G4RotationMatrix* rrot, G4ThreeVector* rtla ); 


    static void      CheckBooleanClone( const G4VSolid* clone, const G4VSolid* left, const G4VSolid* right ); 
    static G4VSolid* PrimitiveClone( const  G4VSolid* solid ); 

    static void ApplyZCut(             G4VSolid* node, double local_zcut); 
    static void ApplyZCut_G4Ellipsoid( G4VSolid* node, double local_zcut);
    static void ApplyZCut_G4Tubs(      G4VSolid* node, double local_zcut);
    static void ApplyZCut_G4Polycone(  G4VSolid* node, double local_zcut);
}; 

