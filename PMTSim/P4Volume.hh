#pragma once
/**
P4Volume.hh
=============

Developed within PMTSim but it is generally useful so needs
to be moved somewhere easier to reuse : X4? A lower level X4 ?

**/

#include <vector>
#include <string>
#include <array>

struct NP ; 
class G4VSolid ; 
class G4LogicalVolume ; 
class G4VPhysicalVolume ; 

#include "PMTSIM_API_EXPORT.hh"

struct PMTSIM_API P4Volume
{
    static void SaveTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* names, const char* path ); 
    static void SaveTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* names, const char* fold, const char* name ); 
    static NP* MakeArray( std::vector<double>* tr, std::vector<G4VSolid*>* solids ); 
    static void DumpTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* names, const char* msg ); 

    static void Traverse(const G4VPhysicalVolume* const pv, std::vector<double>* tr, std::vector<G4VSolid*>* names ); 
    static void Traverse_r(const G4VPhysicalVolume* const pv, int depth, std::vector<double>* tr, std::vector<G4VSolid*>* names); 
    static bool IsIdentityRotation(const std::array<double, 16>& a, double epsilon ) ; 
    static void GetObjectTransform(std::array<double, 16>& a, const G4VPhysicalVolume* const pv); 
    static void DumpSolids(); 

};


