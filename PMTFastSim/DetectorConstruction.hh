#pragma once
/**
DetectorConstruction.hh
=========================

This is a consolidation JUNOSW DetSim Geant4 material setup
intended to give standalone access to JUNO materials. 

**/

#include <string>
#include "PMTSIM_API_EXPORT.hh"

class G4Material ; 
class G4OpticalSurface ; 
class IMCParamsSvc ;
class G4MaterialPropertiesTable ;

struct PMTSIM_API DetectorConstruction
{
     DetectorConstruction();

     void DefineMaterials(); 
     bool helper_mpt(G4MaterialPropertiesTable*, const std::string&, IMCParamsSvc*, const std::string&, double scale=1.0);


     G4Material* Galactic;          // Default material
     G4Material* Air;          // Default material
     G4Material* GdLS;           // Target material
     G4Material* LS;           // Target material
     G4Material* LAB;
     G4Material* ESR;         // Detector material
     G4Material* Tyvek;         // Detector material
     G4Material* Acrylic;         // Detector material
     G4Material* AcrylicMask;        //Detector material
     G4Material* DummyAcrylic;         // Detector material
     G4Material* Teflon;         // Detector material
     G4Material* ETFE;         // Detector material
     G4Material* FEP;         // Detector material
     G4Material* PE_PA;          // Default material PE/PA--Nylon
     G4Material* PA;          // Default material---Nylon
     G4Material* Photocathode_mat;
     G4Material* Steel;
     G4Material* LatticedShellSteel; // used for Latticed Shell
     G4Material* StainlessSteel;
     G4Material* CDReflectorSteel; // used for Mask tail and CD reflector
     G4Material* StrutSteel;
     G4Material* Mylar;
     G4Material* Vacuum;
     G4Material* VacuumT;

     G4Material* Pyrex;
     G4Material* Oil;
     G4Material* Water;
     G4Material* vetoWater;
     G4Material* Rock;
     G4Material* Copper;

     G4OpticalSurface* Photocathode_opsurf;
     G4OpticalSurface* Photocathode_opsurf_3inch;

   //for TT
     G4Material* Aluminium;
     G4Material* TiO2;
     G4Material* Scintillator;
     G4Material* Adhesive;
     G4Material* TiO2Coating;

     std::string m_pmt_optical_model;
     std::string m_LS_optical_model;
     bool        m_use_pmtsimsvc;

};
