#pragma once
/**
F4.hh : Geant4 FastTrack Utilities Drawing on Opticks U4
===========================================================

Used from junoPMTOpticalModel.cc

**/

struct F4
{
    static constexpr const char* kOutside_ = "kOutside" ;
    static constexpr const char* kSurface_ = "kSurface" ;
    static constexpr const char* kInside_  = "kInside" ;

    static const char* EInside_( EInside in ); 
    static G4double Distance_(const G4VSolid* solid, const G4ThreeVector& pos, const G4ThreeVector& dir, EInside* in ); 
    static std::string DescDist(const G4FastTrack &fastTrack, const G4VSolid* solid_ ); 
    static std::string Desc(const G4FastTrack &fastTrack, const char* opt); 

    static int PhotonId(const G4FastTrack &fastTrack) ; 

};


inline const char* F4::EInside_( EInside in ) // static
{
    const char* s = nullptr ;
    switch(in)
    {
        case kOutside: s = kOutside_ ; break ; 
        case kSurface: s = kSurface_ ; break ; 
        case kInside:  s = kInside_  ; break ; 
    }                     
    return s ;
}   

inline G4double F4::Distance_(const G4VSolid* solid, const G4ThreeVector& pos, const G4ThreeVector& dir, EInside* in ) // static
{
    EInside inside = solid->Inside(pos) ;
    if(in) *in = inside ; 
    G4double t = kInfinity ; 
    switch(inside)
    {   
        case kInside:  t = solid->DistanceToOut( pos, dir ) ; break ; 
        case kSurface: t = solid->DistanceToOut( pos, dir ) ; break ; 
        case kOutside: t = solid->DistanceToIn(  pos, dir ) ; break ; 
        default:  assert(0) ; 
    }   
    return t ; 
}

inline std::string F4::DescDist(const G4FastTrack &fastTrack, const G4VSolid* solid_ ) // static
{
    const G4VSolid* solid = solid_ ? solid_ : fastTrack.GetEnvelopeSolid();
    G4ThreeVector lpos = fastTrack.GetPrimaryTrackLocalPosition();
    G4ThreeVector ldir = fastTrack.GetPrimaryTrackLocalDirection();

    EInside inside = kOutside ;
    G4double dist = Distance_(solid, lpos, ldir, &inside ); 
    G4String solidName = solid->GetName() ; // this return by value always surprises me 
   
    std::stringstream ss ; 
    ss << "DescDist" 
       << " " << std::setw(20) << solidName
       ; 

    if( dist == kInfinity ) 
    {
        ss << " " << std::setw(10) << " MISS " ; 
    }
    else   
    {
        G4ThreeVector dpos = lpos+dist*ldir ; 
        ss << " " << std::fixed << std::setprecision(4) << std::setw(10) << dist
           << " " << std::setw(15) << EInside_(inside) 
           << " dpos " << std::setw(20) << dpos 
           ;
    }
    std::string s = ss.str() ; 
    return s ; 
}

inline std::string F4::Desc(const G4FastTrack &fastTrack, const char* opt) // static
{
    const G4Track* primaryTrack = fastTrack.GetPrimaryTrack() ; 
    const G4VSolid* envelopeSolid = fastTrack.GetEnvelopeSolid();
    G4String envelopeSolidName = envelopeSolid->GetName() ; // this return by value always surprises me 
    const G4VPhysicalVolume* volume = primaryTrack->GetVolume() ; 
    const G4String& volumeName = volume->GetName() ; 

    G4ThreeVector lpos = fastTrack.GetPrimaryTrackLocalPosition();
    G4ThreeVector ldir = fastTrack.GetPrimaryTrackLocalDirection();
    G4ThreeVector lpol = fastTrack.GetPrimaryTrackLocalPolarization();

    int photon_id = PhotonId(fastTrack) ; 

    std::stringstream ss ; 
    ss << "F4::Desc" << std::endl ; 

    if( opt && strstr(opt, "Hdr" )) ss
        << " Hdr " 
        << " photon_id " << std::setw(6) << photon_id
        << " volumeName " << std::setw(20) << volumeName
        << " lpos " << std::setw(20) << lpos 
        << " ldir " << std::setw(20) << ldir 
        << std::endl
        ;

    if( opt && strstr(opt, "Dbg" )) ss
        << " Dbg " 
        << std::endl
        << " primaryTrack " << primaryTrack
        << " photon_id " << photon_id
        << " envelopeSolid " << envelopeSolid
        << " envelopeSolidName " << envelopeSolidName
        << " volume " << volume
        << " volumeName " << volumeName
        << std::endl
        ;

    if( opt && strstr(opt, "Vec" )) ss
        << " Vec " 
        << std::endl
        << " lpos " << lpos << std::endl 
        << " ldir " << ldir << std::endl 
        << " lpol " << lpol << std::endl 
        << std::endl 
        ;

    std::string s = ss.str(); 
    return s ; 
}

inline int F4::PhotonId(const G4FastTrack& fastTrack ) // static   0-based id 
{
     const G4Track* track = fastTrack.GetPrimaryTrack() ; 
     int photon_id = track ? track->GetTrackID() - 1 : -1   ; 
     return photon_id ;  
}



