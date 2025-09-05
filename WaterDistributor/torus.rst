torus
======

::

    ok) A[blyth@localhost opticks]$ jgr G4Torus
    ./Doc/detsim/PMTconstruct.md:    #include "G4Torus.hh"
    ./Doc/detsim/examples/R12199_PMTSolid.cc:#include "G4Torus.hh"
    ./Doc/oum/source/detsim/PMTconstruct.md:    #include "G4Torus.hh"
    ./Doc/oum/source/detsim/examples/R12199_PMTSolid.cc:#include "G4Torus.hh"
    ./Examples/Tutorial/share/opticks_juno.sh:   export U4Mesh__NumberOfRotationSteps_entityType_G4Torus=480
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:class G4Torus;
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    std::vector<G4Torus*> solidSurftube = std::vector<G4Torus*>(GT_number,0);
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    std::vector<G4Torus*> solidvacSurftube = std::vector<G4Torus*>(GT_number,0);
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:        solidSurftube[i] = new G4Torus("sSurftube_"+std::to_string(i)+m_guidetube_option,
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:        solidvacSurftube[i] = new G4Torus("svacSurftube_"+std::to_string(i)+m_guidetube_option,

    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:#include "G4Torus.hh"

    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    G4Torus* torus1 = new G4Torus("torus1", 0, pipe_radius, torus_radius, 0*deg, 48*deg);
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    G4Torus* torus2 = new G4Torus("torus2", 0, pipe_radius, torus_radius, 180*deg, 48*deg);

    ./Simulation/DetSimV2/DAE/include/G4DAEParameterisation.hh:#include "G4Torus.hh"
    ./Simulation/DetSimV2/DAE/include/G4DAEParameterisation.hh:   void ComputeDimensions(G4Torus&,const G4int,const G4VPhysicalVolume*) const;
    ./Simulation/DetSimV2/DAE/include/G4DAEReadSolids.hh:#include "G4Torus.hh"
    ./Simulation/DetSimV2/DAE/include/G4DAEWriteParamvol.hh:   void Torus_dimensionsWrite(xercesc::DOMElement*, const G4Torus* const);
    ./Simulation/DetSimV2/DAE/include/G4DAEWriteSolids.hh:#include "G4Torus.hh"
    ./Simulation/DetSimV2/DAE/include/G4DAEWriteSolids.hh:   void TorusWrite(xercesc::DOMElement*, const G4Torus* const);
    ./Simulation/DetSimV2/DAE/src/G4DAEParameterisation.cc:ComputeDimensions(G4Torus& torus,const G4int index,const G4VPhysicalVolume*) const
    ./Simulation/DetSimV2/DAE/src/G4DAEReadSolids.cc:   new G4Torus(name,rmin,rmax,rtor,startphi,deltaphi);

    ./Simulation/DetSimV2/DAE/src/G4DAEWriteParamvol.cc:                      const G4Torus* const torus)
    ./Simulation/DetSimV2/DAE/src/G4DAEWriteParamvol.cc:   if (G4Torus* torus = dynamic_cast<G4Torus*>(solid))

    ./Simulation/DetSimV2/DAE/src/G4DAEWriteSolids.cc:TorusWrite(xercesc::DOMElement* solidsElement, const G4Torus* const torus)
    ./Simulation/DetSimV2/DAE/src/G4DAEWriteSolids.cc:   if (const G4Torus* const torusPtr
    ./Simulation/DetSimV2/DAE/src/G4DAEWriteSolids.cc:     = dynamic_cast<const G4Torus*>(solidPtr))

    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4Torus* torus1 = new G4Torus("torus1", 0, pipe_radius, torus_radius, 0*deg, 48*deg);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4Torus* torus2 = new G4Torus("torus2", 0, pipe_radius, torus_radius, 180*deg, 48*deg);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4Torus* torus1 = new G4Torus("torus1", 0, pipe_radius, torus_radius, 0*deg, 48*deg);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4Torus* torus2 = new G4Torus("torus2", 0, pipe_radius, torus_radius, 180*deg, 48*deg);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    auto torus1 = new G4Torus("torus1", 0, r_tube, r_main1, phi_start1, phi_delta1);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    auto torus2 = new G4Torus("torus2", 0, r_tube, r_main2, phi_start2, phi_delta2);

    ./Simulation/DetSimV2/PMTSim/include/dywTorusStack.hh:// class GLG4TorusStack

    ./Simulation/DetSimV2/PMTSim/src/ExplosionProofSolid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/ExplosionProofSolid.cc:  G4Torus* bottom_torus = new G4Torus(
    ./Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc:    G4VSolid* solid_IV_torus = new G4Torus(
    ./Simulation/DetSimV2/PMTSim/src/Hello_PMTSolid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/Hello_PMTSolid.cc:    G4Torus* pmttube_solid_torus = new G4Torus(
    ./Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc:    G4Torus* torus = new G4Torus(
    ./Simulation/DetSimV2/PMTSim/src/R12860OnlyFront_PMTSolid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/R12860_PMTSolid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/R12860_PMTSolid.cc:    G4Torus* pmttube_solid_torus = new G4Torus(
    ./Simulation/DetSimV2/PMTSim/src/R12860_TorusPMTSolid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/R12860_TorusPMTSolid.cc:    G4Torus* pmttube_solid_torus_2 = new G4Torus(
    ./Simulation/DetSimV2/PMTSim/src/R12860_TorusPMTSolid.cc:    G4Torus* pmttube_solid_torus_5 = new G4Torus(
    ./Simulation/DetSimV2/PMTSim/src/Tub3inchPMTSolid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV2Solid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:#include "G4Torus.hh"
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:const char* ZSolid::G4Torus_              = "Tor" ;
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:       case _G4Torus:             s = G4Torus_             ; break ; 
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:    if( strcmp(name, "G4Torus") == 0 )             type = _G4Torus ; 
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:    else if( type == _G4Torus )
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:        const G4Torus* torus = dynamic_cast<const G4Torus*>(solid) ; 
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:        clone = new G4Torus(*torus) ;  
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:    bool can = type == _G4Ellipsoid || type == _G4Tubs || type == _G4Polycone || type == _G4Torus ; 
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:        case _G4Torus:     GetZRange( dynamic_cast<const G4Torus*>(solid),     z0, z1 );  break ; 
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.cc:void ZSolid::GetZRange( const G4Torus* const torus, double& _z0, double& _z1 )  // static 
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.h:class G4Torus ; 
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.h:        _G4Torus, 
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.h:    static const char* G4Torus_     ;
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.h:    static void GetZRange( const G4Torus*     const torus,     double& z0, double& z1 ); 
    ./Simulation/DetSimV2/PMTSim/src/dywTorusStack.cc:// class GLG4TorusStack
    ./Simulation/DetSimV2/PMTSim/src/dywTorusStack.cc:// 1999/11/22 G.Horton-Smith First version of GLG4TorusStack
    ./Simulation/DetSimV2/PMTSim/src/dywTorusStack.cc:// (just like G4Torus as of Geant 4.0.1 -- fixme? ? ?)
    (ok) A[blyth@localhost junosw]$ 

