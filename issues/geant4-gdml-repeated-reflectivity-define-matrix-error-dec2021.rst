geant4-gdml-repeated-reflectivity-define-matrix-error-dec2021
===============================================================

Seems all GDML reading tests are failing
--------------------------------------------

* From :doc:`offline-opticks-test-fails-dec2021`


GDML is repeatedly defining the same REFLECTIVITY matrix with same pointer suffixed name::

    40     <matrix coldim="2" name="REFLECTIVITY0x570d1e0" values="1.55e-06 0.535 1.55e-05 0.535"/>
    41     <matrix coldim="2" name="ABSLENGTH0x570e460" values="1.55e-06 0.001 6.2e-06 0.001 1.033e-05 0.001 1.55e-05 0.001"/>
    42     <matrix coldim="2" name="REFLECTIVITY0x570d1e0" values="1.55e-06 0.535 1.55e-05 0.535"/>
    43     <matrix coldim="2" name="ABSLENGTH0x570e460" values="1.55e-06 0.001 6.2e-06 0.001 1.033e-05 0.001 1.55e-05 0.001"/>
    44     <matrix coldim="2" name="REFLECTIVITY0x570d1e0" values="1.55e-06 0.535 1.55e-05 0.535"/>
    45     <matrix coldim="2" name="ABSLENGTH0x570e460" values="1.55e-06 0.001 6.2e-06 0.001 1.033e-05 0.001 1.55e-05 0.001"/>



    40     <matrix coldim="2" name="REFLECTIVITY0x570d1e0" values="1.55e-06 0.535 1.55e-05 0.535"/>
    42     <matrix coldim="2" name="REFLECTIVITY0x570d1e0" values="1.55e-06 0.535 1.55e-05 0.535"/>
    44     <matrix coldim="2" name="REFLECTIVITY0x570d1e0" values="1.55e-06 0.535 1.55e-05 0.535"/>

    41     <matrix coldim="2" name="ABSLENGTH0x570e460" values="1.55e-06 0.001 6.2e-06 0.001 1.033e-05 0.001 1.55e-05 0.001"/>
    43     <matrix coldim="2" name="ABSLENGTH0x570e460" values="1.55e-06 0.001 6.2e-06 0.001 1.033e-05 0.001 1.55e-05 0.001"/>
    45     <matrix coldim="2" name="ABSLENGTH0x570e460" values="1.55e-06 0.001 6.2e-06 0.001 1.033e-05 0.001 1.55e-05 0.001"/>


Is the problem due to issue with the kludging ? NOPE
------------------------------------------------------ 

Nope current kludging only changes:

1. a few "constant" into "matrix" 
2. clean truncates overlong matrix values


::

    epsilon:opticks blyth$ opticks-cd
    epsilon:opticks blyth$ pwd
    /usr/local/opticks

    epsilon:opticks blyth$ scp P:/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml .
    epsilon:opticks blyth$ mv origin_CGDMLKludge.gdml origin_CGDMLKludge_11dec2021.gdml

    epsilon:opticks blyth$ scp P:/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin.gdml .
    epsilon:opticks blyth$ mv origin.gdml origin_11dec2021.gdml


Checking after adding CGDMLKludgeRead::pruneDuplicatedMatrix
--------------------------------------------------------------

::

    N
    jre
    o
    git pull 
    oo
    tds3

    opticks-t





Can a kludge fix be added to CGDMLKludge ? Have added CGDMLKludgeRead::checkDuplicatedMatrix CGDMLKludgeRead::pruneDuplicatedMatrix
--------------------------------------------------------------------------------------------------------------------------------------

::

    epsilon:cfg4 blyth$ l CGDMLKludge*
    16 -rw-r--r--  1 blyth  staff   4202 Oct  1 14:08 CGDMLKludgeWrite.cc
    24 -rw-r--r--  1 blyth  staff  10980 Oct  1 14:08 CGDMLKludgeRead.cc
     8 -rw-r--r--  1 blyth  staff   2589 Oct  1 14:08 CGDMLKludge.cc
     8 -rw-r--r--  1 blyth  staff   1000 Apr  9  2021 CGDMLKludge.hh
     8 -rw-r--r--  1 blyth  staff   1233 Apr  9  2021 CGDMLKludgeErrorHandler.hh
     8 -rw-r--r--  1 blyth  staff    962 Apr  9  2021 CGDMLKludgeWrite.hh
     8 -rw-r--r--  1 blyth  staff   1485 Apr  9  2021 CGDMLKludgeRead.hh
    epsilon:cfg4 blyth$ 



::

     922 GGeo* G4Opticks::translateGeometry( const G4VPhysicalVolume* top )
     923 {
     924     LOG(verbose) << "( key" ;
     925     const char* keyspec = X4PhysicalVolume::Key(top) ;
     926 
     927     bool parse_argv = false ;
     928     Opticks* ok = InitOpticks(keyspec, m_embedded_commandline_extra, parse_argv );
     929 
     930     const char* dbggdmlpath = ok->getDbgGDMLPath();
     931     if( dbggdmlpath != NULL )
     932     {
     933         LOG(info) << "( CGDML" ;
     934         CGDML::Export( dbggdmlpath, top );
     935         LOG(info) << ") CGDML" ;
     936     }
     937 
     938     const char* origin = Opticks::OriginGDMLPath();
     939     LOG(info) << "( CGDML " << origin  ;
     940     CGDML::Export( origin, top );
     941     LOG(info) << ") CGDML " ;
     942 
     943     if(ok->isGDMLKludge())
     944     {
     945         LOG(info) << "( CGDMLKludge " << origin << " --gdmlkludge"  ;
     946         const char* kludge_path = CGDMLKludge::Fix( origin );
     947         if(kludge_path) LOG(info) << "kludge_path " << kludge_path ;
     948         LOG(info) << ") CGDMLKludge " ;
     949     }
     950     else
     951     {
     952         LOG(info) << "CGDMLKludge not-applied as no option : --gdmlkludge  " ;
     953     }
     954 





Finding the source of the repeat
---------------------------------------


::

    epsilon:data blyth$ find . -name REFLECTIVITY -exec grep -H 0.535 {} \;
    ./Simulation/DetSim/Material/CDInnerReflector/REFLECTIVITY:1.55   *eV      0.535
    ./Simulation/DetSim/Material/CDInnerReflector/REFLECTIVITY:15.5   *eV      0.535
    ./Simulation/DetSim/Material/StrutSteel/REFLECTIVITY:1.55   *eV      0.535
    ./Simulation/DetSim/Material/StrutSteel/REFLECTIVITY:15.5   *eV      0.535

::

    jgr Material.StrutSteel.REFLECTIVITY
    jgr Material.CDInnerReflector.REFLECTIVITY

    epsilon:data blyth$ jgr Material.StrutSteel.REFLECTIVITY
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        helper_mpt(StrutSteelMPT, "REFLECTIVITY", mcgt.data(), "Material.StrutSteel.REFLECTIVITY");
    epsilon:offline blyth$ 


The REFLECTIVITY0x570d1e0 is defined three times and referenced three times::


  0527     <material name="StrutSteel0x570c590" state="solid">
   528       <property name="REFLECTIVITY" ref="REFLECTIVITY0x570d1e0"/>
   529       <property name="ABSLENGTH" ref="ABSLENGTH0x570e460"/>
   530       <T unit="K" value="293.15"/>
   531       <MEE unit="eV" value="280.330055108221"/>
   532       <D unit="g/cm3" value="8.1"/>
   533       <fraction n="0.70845" ref="Iron0x56d8640"/>
   534       <fraction n="0.0008" ref="Carbon0x56d6cc0"/>
   535       <fraction n="0.02" ref="Mn0x56dab90"/>
   536       <fraction n="0.00045" ref="Phosphorus0x56dae20"/>
   537       <fraction n="0.0003" ref="Sulfur0x56d9840"/>
   538       <fraction n="0.01" ref="Silicon0x56d8080"/>
   539       <fraction n="0.18" ref="Cr0x56da7f0"/>
   540       <fraction n="0.08" ref="Ni0x56da3f0"/>
   541     </material>

  1693     <tube aunit="deg" deltaphi="360" lunit="mm" name="sStrut0x57f6870" rmax="42.5" rmin="0" startphi="0" z="1552.05399021558"/>
  1694     <opticalsurface finish="3" model="1" name="opStrutAcrylic" type="0" value="0.2">
  1695       <property name="REFLECTIVITY" ref="REFLECTIVITY0x570d1e0"/>
  1696       <property name="ABSLENGTH" ref="ABSLENGTH0x570e460"/>
  1697     </opticalsurface>
  1698     <tube aunit="deg" deltaphi="360" lunit="mm" name="sStrut0x584c590" rmax="30" rmin="0" startphi="0" z="1552.07707472297"/>
  1699     <opticalsurface finish="3" model="1" name="opStrut2Acrylic" type="0" value="0.2">
  1700       <property name="REFLECTIVITY" ref="REFLECTIVITY0x570d1e0"/>
  1701       <property name="ABSLENGTH" ref="ABSLENGTH0x570e460"/>
  1702     </opticalsurface>


::

    epsilon:offline blyth$ jgr opStrutAcrylic
    ./Simulation/DetSimV2/CentralDetector/src/StrutAcrylicConstruction.cc:    G4OpticalSurface *strut_optical_surface = new G4OpticalSurface("opStrutAcrylic");
    epsilon:offline blyth$ jgr opStrut2Acrylic
    ./Simulation/DetSimV2/CentralDetector/src/StrutBar2AcrylicConstruction.cc:    G4OpticalSurface *strut2_optical_surface = new G4OpticalSurface("opStrut2Acrylic");
    epsilon:offline blyth$ 


::

    125 void
    126 StrutAcrylicConstruction::initMaterials() {
    127     Steel = G4Material::GetMaterial("StrutSteel");
    128 }
    129 

    157 void
    158 StrutAcrylicConstruction::makeStrutOpSurface() {
    159     G4OpticalSurface *strut_optical_surface = new G4OpticalSurface("opStrutAcrylic");
    160     strut_optical_surface->SetMaterialPropertiesTable(Steel->GetMaterialPropertiesTable());
    161     strut_optical_surface->SetModel(unified);
    162     strut_optical_surface->SetType(dielectric_metal);
    163     strut_optical_surface->SetFinish(ground);
    164     strut_optical_surface->SetSigmaAlpha(0.2);
    165 
    166     new G4LogicalSkinSurface("StrutAcrylicOpSurface", logicStrut, strut_optical_surface);
    167 }




    117 void
    118 StrutBar2AcrylicConstruction::initMaterials() {
    119     Steel = G4Material::GetMaterial("StrutSteel");
    120 }

    149 void
    150 StrutBar2AcrylicConstruction::makeStrutOpSurface() {
    151     G4OpticalSurface *strut2_optical_surface = new G4OpticalSurface("opStrut2Acrylic");
    152     strut2_optical_surface->SetMaterialPropertiesTable(Steel->GetMaterialPropertiesTable());
    153     strut2_optical_surface->SetModel(unified);
    154     strut2_optical_surface->SetType(dielectric_metal);
    155     strut2_optical_surface->SetFinish(ground);
    156     strut2_optical_surface->SetSigmaAlpha(0.2);
    157 
    158     new G4LogicalSkinSurface("Strut2AcrylicOpSurface", logicStrut, strut2_optical_surface);
    159 }



    epsilon:offline blyth$ jgr StrutSteel
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh:     G4Material* StrutSteel;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:    StrutSteel = G4Material::GetMaterial("StrutSteel", any_warnings);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:    if(StrutSteel) {
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        G4cout << "StrutSteel is constructed from the GDML file" << G4endl;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        G4cout << "StrutSteel is constructed from the code" <<G4endl;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel = new G4Material("StrutSteel",density,8);                  
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel->AddElement(Fe, 0.70845);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel->AddElement(C, 0.0008);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel->AddElement(Mn, 0.02);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel->AddElement(P, 0.00045);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel->AddElement(S, 0.00030);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel->AddElement(Si, 0.01);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel->AddElement(Cr, 0.18);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel->AddElement(Ni, 0.08);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        G4MaterialPropertiesTable* StrutSteelMPT = new G4MaterialPropertiesTable();
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        G4cout << "Setup StrutSteel Material Tables from MCParamsSvc" << G4endl;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        helper_mpt(StrutSteelMPT, "REFLECTIVITY", mcgt.data(), "Material.StrutSteel.REFLECTIVITY");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        helper_mpt(StrutSteelMPT, "ABSLENGTH", mcgt.data(), "Material.StrutSteel.ABSLENGTH");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        StrutSteel->SetMaterialPropertiesTable(StrutSteelMPT);
    ./Simulation/DetSimV2/CentralDetector/src/StrutBar2AcrylicConstruction.cc:    Steel = G4Material::GetMaterial("StrutSteel");
    ./Simulation/DetSimV2/CentralDetector/src/StrutAcrylicConstruction.cc:    Steel = G4Material::GetMaterial("StrutSteel");
    epsilon:offline blyth$ 




That could be a G4OpticalSurface GDML writing bug, 
that writes the referenced matrix every time it is encountered without checking if it has been 
written already.  


::

    epsilon:offline blyth$ g4-
    epsilon:offline blyth$ g4-cc opticalsurface
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:             G4OpticalSurface* opticalsurface)
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:            + "' should have \n two columns as a property table for opticalsurface: "
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:            + opticalsurface->GetName();
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:   G4MaterialPropertiesTable* matprop=opticalsurface->GetMaterialPropertiesTable();
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:     opticalsurface->SetMaterialPropertiesTable(matprop);
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:OpticalSurfaceRead(const xercesc::DOMElement* const opticalsurfaceElement)
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:         = opticalsurfaceElement->getAttributes();
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:   G4OpticalSurface* opticalsurface
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:   for (xercesc::DOMNode* iter = opticalsurfaceElement->getFirstChild();
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:      if (tag=="property") { PropertyRead(child,opticalsurface); }
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLReadSolids.cc:      if (tag=="opticalsurface") { OpticalSurfaceRead(child); } else
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLWriteSolids.cc:   xercesc::DOMElement* optElement = NewElement("opticalsurface");
    epsilon:offline blyth$ 



::

    1033 void G4GDMLWriteSolids::
    1034 OpticalSurfaceWrite(xercesc::DOMElement* solElement,
    1035                     const G4OpticalSurface* const surf)
    1036 {
    1037    xercesc::DOMElement* optElement = NewElement("opticalsurface");
    1038    G4OpticalSurfaceModel smodel = surf->GetModel();
    1039    G4double sval = (smodel==glisur) ? surf->GetPolish() : surf->GetSigmaAlpha();
    1040 
    1041    optElement->setAttributeNode(NewAttribute("name", surf->GetName()));
    1042    optElement->setAttributeNode(NewAttribute("model", smodel));
    1043    optElement->setAttributeNode(NewAttribute("finish", surf->GetFinish()));
    1044    optElement->setAttributeNode(NewAttribute("type", surf->GetType()));
    1045    optElement->setAttributeNode(NewAttribute("value", sval));
    1046 
    1047    // Write any property attached to the optical surface...
    1048    //
    1049    if (surf->GetMaterialPropertiesTable())
    1050    {
    1051      PropertyWrite(optElement, surf);
    1052    }
    1053 
    1054    solElement->appendChild(optElement);
    1055 }


    1057 void G4GDMLWriteSolids::PropertyWrite(xercesc::DOMElement* optElement,
    1058                                          const G4OpticalSurface* const surf)
    1059 {
    1060    xercesc::DOMElement* propElement;
    1061    G4MaterialPropertiesTable* ptable = surf->GetMaterialPropertiesTable();
    1062    const std::map< G4int, G4PhysicsOrderedFreeVector*,
    1063                  std::less<G4int> >* pmap = ptable->GetPropertyMap();
    1064    const std::map< G4int, G4double,
    1065                  std::less<G4int> >* cmap = ptable->GetConstPropertyMap();
    1066    std::map< G4int, G4PhysicsOrderedFreeVector*,
    1067                  std::less<G4int> >::const_iterator mpos;
    1068    std::map< G4int, G4double,
    1069                  std::less<G4int> >::const_iterator cpos;
    1070    for (mpos=pmap->begin(); mpos!=pmap->end(); mpos++)
    1071    {
    1072       propElement = NewElement("property");
    1073       propElement->setAttributeNode(NewAttribute("name",
    1074                             ptable->GetMaterialPropertyNames()[mpos->first]));
    1075       propElement->setAttributeNode(NewAttribute("ref",
    1076                  GenerateName(ptable->GetMaterialPropertyNames()[mpos->first],
    1077                                                  mpos->second)));
    1078       if (mpos->second)
    1079       {
    1080          PropertyVectorWrite(ptable->GetMaterialPropertyNames()[mpos->first],
    1081                              mpos->second);
    1082          optElement->appendChild(propElement);
    1083       }
    1084       else
    1085       {
    1086          G4String warn_message = "Null pointer for material property -"
    1087                   + ptable->GetMaterialPropertyNames()[mpos->first]
    1088                   + "- of optical surface -" + surf->GetName() + "- !";
    1089          G4Exception("G4GDMLWriteSolids::PropertyWrite()", "NullPointer",
    1090                      JustWarning, warn_message);
    1091          continue;
    1092       }
    1093    }


    epsilon:offline blyth$ g4-cc PropertyVectorWrite
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLWriteMaterials.cc:void G4GDMLWriteMaterials::PropertyVectorWrite(const G4String& key,
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLWriteMaterials.cc:         PropertyVectorWrite(ptable->GetMaterialPropertyNames()[mpos->first],
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLWriteSolids.cc:         PropertyVectorWrite(ptable->GetMaterialPropertyNames()[mpos->first],
    epsilon:offline blyth$ 


    210 void G4GDMLWriteMaterials::PropertyVectorWrite(const G4String& key,
    211                            const G4PhysicsOrderedFreeVector* const pvec)
    212 {
    213    const G4String matrixref = GenerateName(key, pvec);
    214    xercesc::DOMElement* matrixElement = NewElement("matrix");
    215    matrixElement->setAttributeNode(NewAttribute("name", matrixref));
    216    matrixElement->setAttributeNode(NewAttribute("coldim", "2"));
    217    std::ostringstream pvalues;
    218    for (size_t i=0; i<pvec->GetVectorLength(); i++)
    219    {
    220        if (i!=0)  { pvalues << " "; }
    221        pvalues << pvec->Energy(i) << " " << (*pvec)[i];
    222    }
    223    matrixElement->setAttributeNode(NewAttribute("values", pvalues.str()));
    224 
    225    defineElement->appendChild(matrixElement);
    226 }


* YEP: THIS DOES LOOK LIKE A GEANT4 BUG FOR MULTIPLE G4OpticalSurface referencing the same properties
  yields GDML with duplicated matrix that causes error on being read

* kludge fix is to prune duplicated 






Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc::

     449     CDReflectorSteel = G4Material::GetMaterial("CDReflectorSteel", any_warnings);
     450     if(CDReflectorSteel) {
     451         G4cout << "CDReflectorSteel is constructed from the GDML file" << G4endl;
     452     } else {
     453         G4cout << "CDReflectorSteel is constructed from the code" <<G4endl;
     454         density = 8.1*g/cm3;                                            
     455         CDReflectorSteel = new G4Material("CDReflectorSteel",density,8);
     456         
     457         CDReflectorSteel->AddElement(Fe, 0.70845);
     458         CDReflectorSteel->AddElement(C, 0.0008);
     459         CDReflectorSteel->AddElement(Mn, 0.02);
     460         CDReflectorSteel->AddElement(P, 0.00045);
     461         CDReflectorSteel->AddElement(S, 0.00030);
     462         CDReflectorSteel->AddElement(Si, 0.01);
     463         CDReflectorSteel->AddElement(Cr, 0.18);
     464         CDReflectorSteel->AddElement(Ni, 0.08);
     465         
     466         G4MaterialPropertiesTable* CDReflectorSteelMPT = new G4MaterialPropertiesTable();
     467         G4cout << "Setup CDReflectorSteel Material Tables from MCParamsSvc" << G4endl;
     468         helper_mpt(CDReflectorSteelMPT, "REFLECTIVITY", mcgt.data(), "Material.CDInnerReflector.REFLECTIVITY");
     469         helper_mpt(CDReflectorSteelMPT, "ABSLENGTH", mcgt.data(), "Material.CDInnerReflector.ABSLENGTH");
     470         CDReflectorSteel->SetMaterialPropertiesTable(CDReflectorSteelMPT);
     471     }
     472 
     473     // Strut steel
     474     // --Yaoguang Wang, 16th, Aug, 2021
     475     StrutSteel = G4Material::GetMaterial("StrutSteel", any_warnings);
     476     if(StrutSteel) {
     477         G4cout << "StrutSteel is constructed from the GDML file" << G4endl;
     478     } else {
     479         G4cout << "StrutSteel is constructed from the code" <<G4endl;
     480         density = 8.1*g/cm3;
     481         StrutSteel = new G4Material("StrutSteel",density,8);
     482         StrutSteel->AddElement(Fe, 0.70845);
     483         StrutSteel->AddElement(C, 0.0008);
     484         StrutSteel->AddElement(Mn, 0.02);
     485         StrutSteel->AddElement(P, 0.00045);
     486         StrutSteel->AddElement(S, 0.00030);
     487         StrutSteel->AddElement(Si, 0.01);
     488         StrutSteel->AddElement(Cr, 0.18);
     489         StrutSteel->AddElement(Ni, 0.08);
     490 
     491         G4MaterialPropertiesTable* StrutSteelMPT = new G4MaterialPropertiesTable();
     492         G4cout << "Setup StrutSteel Material Tables from MCParamsSvc" << G4endl;
     493         helper_mpt(StrutSteelMPT, "REFLECTIVITY", mcgt.data(), "Material.StrutSteel.REFLECTIVITY");
     494         helper_mpt(StrutSteelMPT, "ABSLENGTH", mcgt.data(), "Material.StrutSteel.ABSLENGTH");
     495         StrutSteel->SetMaterialPropertiesTable(StrutSteelMPT);
     496     }








::

    Start  3: CFG4Test.CTestDetectorTest
     3/45 Test  #3: CFG4Test.CTestDetectorTest ...............Subprocess aborted***Exception:   4.89 sec
    2021-12-12 03:33:14.516 INFO  [173588] [main@44] /data/blyth/junotop/ExternalLibs/opticks/head/build/cfg4/tests/CTestDetectorTest
    2021-12-12 03:33:14.521 ERROR [173588] [OpticksResource::SetupG4Environment@220] inipath /data/blyth/junotop/ExternalLibs/opticks/head/externals/config/geant4.ini
    2021-12-12 03:33:14.521 ERROR [173588] [OpticksResource::SetupG4Environment@229]  MISSING inipath /data/blyth/junotop/ExternalLibs/opticks/head/externals/config/geant4.ini (create it with bash functions: g4-;g4-export-ini ) 
    2021-12-12 03:33:14.531 INFO  [173588] [OpticksHub::loadGeometry@283] [ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    2021-12-12 03:33:15.311 INFO  [173588] [GParts::add@1323]  NOT ENABLED --gparts_transform_offset, COUNT  1
    2021-12-12 03:33:16.234 INFO  [173588] [Opticks::makeSimpleTorchStep@4289] [ts.setFrameTransform
    2021-12-12 03:33:16.236 INFO  [173588] [BOpticksResource::IsGeant4EnvironmentDetected@305]  n 11 detect 1
    2021-12-12 03:33:16.236 ERROR [173588] [CG4::preinit@146] External Geant4 environment is detected, not changing this. 

    **************************************************************
     Geant4 version Name: geant4-10-04-patch-02 [MT]   (25-May-2018)
                           Copyright : Geant4 Collaboration
                          References : NIM A 506 (2003), 250-303
                                     : IEEE-TNS 53 (2006), 270-278
                                     : NIM A 835 (2016), 186-225
                                 WWW : http://geant4.org/
    **************************************************************

    G4GDML: Reading '/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml'...
    G4GDML: Reading definitions...

    -------- EEEE ------- G4Exception-START -------- EEEE -------
    *** G4Exception : InvalidExpression
          issued by : G4GDMLEvaluator::DefineConstant()
    Redefinition of constant or variable: REFLECTIVITY0x570d1e0_0_0
    *** Fatal Exception *** core dump ***
     **** Track information is not available at this moment
     **** Step information is not available at this moment

    -------- EEEE -------- G4Exception-END --------- EEEE -------


    *** G4Exception: Aborting execution ***

          Start  4: CFG4Test.CGDMLTest
     4/45 Test  #4: CFG4Test.CGDMLTest .......................   Passed    0.21 sec
          Start  5: CFG4Test.CGDMLDetectorTest
     5/45 Test  #5: CFG4Test.CGDMLDetectorTest ...............Subprocess aborted***Exception:   4.84 sec
    2021-12-12 03:33:19.630 INFO  [173602] [main@97] /data/blyth/junotop/ExternalLibs/opticks/head/build/cfg4/tests/CGDMLDetectorTest
    2021-12-12 03:33:19.645 INFO  [173602] [OpticksHub::loadGeometry@283] [ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    2021-12-12 03:33:20.423 INFO  [173602] [GParts::add@1323]  NOT ENABLED --gparts_transform_offset, COUNT  1
    ...
    2021-12-12 03:33:21.327 INFO  [173602] [Opticks::makeSimpleTorchStep@4289] [ts.setFrameTransform
    2021-12-12 03:33:21.327 ERROR [173602] [main@102] //////////////////////////  AFTER OpticksHub instanciation ///////////////////////////////////// 
    G4GDML: Reading '/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml'...
    G4GDML: Reading definitions...

    -------- EEEE ------- G4Exception-START -------- EEEE -------

    *** ExceptionHandler is not defined ***
    *** G4Exception : InvalidExpression
          issued by : G4GDMLEvaluator::DefineConstant()
    Redefinition of constant or variable: REFLECTIVITY0x570d1e0_0_0
    *** Fatal Exception ***
    -------- EEEE -------- G4Exception-END --------- EEEE -------


    *** G4Exception: Aborting execution ***

          Start  6: CFG4Test.CGDMLPropertyTest
     6/45 Test  #6: CFG4Test.CGDMLPropertyTest ...............   Passed    0.20 sec
          Start  7: CFG4Test.CGeometryTest
     7/45 Test  #7: CFG4Test.CGeometryTest ...................Subprocess aborted***Exception:   4.88 sec
    2021-12-12 03:33:24.660 INFO  [173609] [main@61] /data/blyth/junotop/ExternalLibs/opticks/head/build/cfg4/tests/CGeometryTest
    G4GDML: Reading '/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml'...
    G4GDML: Reading definitions...

    -------- EEEE ------- G4Exception-START -------- EEEE -------

    *** ExceptionHandler is not defined ***
    *** G4Exception : InvalidExpression
          issued by : G4GDMLEvaluator::DefineConstant()
    Redefinition of constant or variable: REFLECTIVITY0x570d1e0_0_0
    *** Fatal Exception ***
    -------- EEEE -------- G4Exception-END --------- EEEE -------


    *** G4Exception: Aborting execution ***

          Start  8: CFG4Test.G4MaterialTest
     8/45 Test  #8: CFG4Test.G4MaterialTest ..................   Passed    0.30 sec
          Start  9: CFG4Test.G4StringTest




::

    N[blyth@localhost opticks]$ grep REFLECTIVITY /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml
        <matrix coldim="2" name="REFLECTIVITY0x7171d50" values="1.55e-06 0.1 6.2e-06 0.1 1.033e-05 0.1 1.55e-05 0.1"/>
        <matrix coldim="2" name="REFLECTIVITY0x570d1e0" values="1.55e-06 0.535 1.55e-05 0.535"/>
        <matrix coldim="2" name="REFLECTIVITY0x570d1e0" values="1.55e-06 0.535 1.55e-05 0.535"/>
        <matrix coldim="2" name="REFLECTIVITY0x570d1e0" values="1.55e-06 0.535 1.55e-05 0.535"/>
        <matrix coldim="2" name="REFLECTIVITY0x570bf50" values="1.55e-06 0.535 1.55e-05 0.535"/>
        <matrix coldim="2" name="REFLECTIVITY0x570bf50" values="1.55e-06 0.535 1.55e-05 0.535"/>
        <matrix coldim="2" name="REFLECTIVITY0x572c260" values="1.55e-06 0 6.2e-06 0 1.033e-05 0 1.55e-05 0"/>
        <matrix coldim="2" name="REFLECTIVITY0x5f20630" values="1.55e-06 0.92 1.55e-05 0.92"/>
        <matrix coldim="2" name="REFLECTIVITY0x570bf50" values="1.55e-06 0.535 1.55e-05 0.535"/>
        <matrix coldim="2" name="REFLECTIVITY0x5730120" values="1.55e-06 0 6.2e-06 0 1.033e-05 0 1.55e-05 0"/>
        <matrix coldim="2" name="REFLECTIVITY0x5efdbe0" values="1.55e-06 0.92 1.55e-05 0.92"/>
        <matrix coldim="2" name="REFLECTIVITY0x5729f10" values="1.55e-06 0 6.2e-06 0 1.033e-05 0 1.55e-05 0"/>
        <matrix coldim="2" name="REFLECTIVITY0x66b0f10" values="1.55e-06 0 1.55e-05 0"/>
        <matrix coldim="2" name="REFLECTIVITY0x7174300" values="1.55e-06 0.4 6.2e-06 0.4 1.033e-05 0.4 1.55e-05 0.4"/>
        <matrix coldim="2" name="REFLECTIVITY0x570bf50" values="1.55e-06 0.535 1.55e-05 0.535"/>
        <matrix coldim="2" name="REFLECTIVITY0x572c260" values="1.55e-06 0 6.2e-06 0 1.033e-05 0 1.55e-05 0"/>
        <matrix coldim="2" name="REFLECTIVITY0x5f31b10" values="1.55e-06 0.9999 1.55e-05 0.9999"/>
        <matrix coldim="2" name="REFLECTIVITY0x5936000" values="1.55e-06 0.91 2.034e-06 0.91 2.068e-06 0.91 2.103e-06 0.91 2.139e-06 0.91 2.177e-06 0.91 2.216e-06 0.91 2.256e-06 0.91 2.298e-06 0.91 2.341e-06 0.91 2.386e-06 0.91 2.433e-06 0.91 2.481e-06 0.91 2.532e-06 0.912 2.585e-06 0.913 2.64e-06 0.915 2.697e-06 0.918 2.757e-06 0.92 2.82e-06 0.92 2.885e-06 0.925 2.954e-06 0.925 3.026e-06 0.92 3.102e-06 0.92 3.181e-06 0.91 3.265e-06 0.89 3.353e-06 0.88 3.446e-06 0.87 3.545e-06 0.86 3.649e-06 0.84 3.76e-06 0.82 3.877e-06 0.8 4.002e-06 0.76 4.136e-06 0.73 6.2e-06 0.53 1.033e-05 0.53 1.55e-05 0.53"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x570d1e0"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x570bf50"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x7171d50"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x570d1e0"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x570d1e0"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x570bf50"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x572c260"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x5f20630"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x570bf50"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x5730120"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x5efdbe0"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x5729f10"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x66b0f10"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x7174300"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x570bf50"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x572c260"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x5f31b10"/>
          <property name="REFLECTIVITY" ref="REFLECTIVITY0x5936000"/>
    N[blyth@localhost opticks]$ 




::

    N[blyth@localhost opticks]$ gdb $(which CTestDetectorTest)
    GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-114.el7
    ...
    2021-12-12 03:58:05.664 INFO  [175103] [main@44] /data/blyth/junotop/ExternalLibs/opticks/head/lib/CTestDetectorTest
    ...
    2021-12-12 03:58:07.356 ERROR [175103] [CG4::preinit@146] External Geant4 environment is detected, not changing this. 

    **************************************************************
     Geant4 version Name: geant4-10-04-patch-02 [MT]   (25-May-2018)
                           Copyright : Geant4 Collaboration
                          References : NIM A 506 (2003), 250-303
                                     : IEEE-TNS 53 (2006), 270-278
                                     : NIM A 835 (2016), 186-225
                                 WWW : http://geant4.org/
    **************************************************************

    G4GDML: Reading '/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml'...
    G4GDML: Reading definitions...

    -------- EEEE ------- G4Exception-START -------- EEEE -------
    *** G4Exception : InvalidExpression
          issued by : G4GDMLEvaluator::DefineConstant()
    Redefinition of constant or variable: REFLECTIVITY0x570d1e0_0_0
    *** Fatal Exception *** core dump ***
     **** Track information is not available at this moment
     **** Step information is not available at this moment

    -------- EEEE -------- G4Exception-END --------- EEEE -------


    *** G4Exception: Aborting execution ***

    Program received signal SIGABRT, Aborted.
    0x00007fffe83fa387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-4.el7_9.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-59.el7_9.1.x86_64 libicu-50.2-4.el7_7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-24.el7_9.x86_64 openssl-libs-1.0.2k-22.el7_9.x86_64 pcre-8.32-17.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007fffe83fa387 in raise () from /lib64/libc.so.6
    #1  0x00007fffe83fba78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff160fbee in G4Exception(char const*, char const*, G4ExceptionSeverity, char const*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4global.so
    #3  0x00007ffff5ef3587 in G4GDMLEvaluator::DefineConstant(G4String const&, double) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #4  0x00007ffff5ef46e7 in G4GDMLEvaluator::DefineMatrix(G4String const&, int, std::vector<double, std::allocator<double> >) ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #5  0x00007ffff5f06b78 in G4GDMLReadDefine::MatrixRead(xercesc_3_2::DOMElement const*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #6  0x00007ffff5f09460 in G4GDMLReadDefine::DefineRead(xercesc_3_2::DOMElement const*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #7  0x00007ffff5f02b14 in G4GDMLRead::Read(G4String const&, bool, bool, bool) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #8  0x00007ffff7b1dd8d in G4GDMLParser::Read (this=0x7fffffff5ab0, filename=..., validate=false) at /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4GDMLParser.icc:37
    #9  0x00007ffff7b1d0c6 in CGDMLDetector::parseGDML (this=0xa836000, 
        path=0x6e6470 "/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml") at /home/blyth/opticks/cfg4/CGDMLDetector.cc:121
    #10 0x00007ffff7b1cee3 in CGDMLDetector::init (this=0xa836000) at /home/blyth/opticks/cfg4/CGDMLDetector.cc:91
    #11 0x00007ffff7b1cb84 in CGDMLDetector::CGDMLDetector (this=0xa836000, hub=0x7fffffff6ba0, query=0x6de5d0, sd=0xa833670) at /home/blyth/opticks/cfg4/CGDMLDetector.cc:63
    #12 0x00007ffff7ac02e6 in CGeometry::init (this=0xa835f20) at /home/blyth/opticks/cfg4/CGeometry.cc:99
    #13 0x00007ffff7ac00dc in CGeometry::CGeometry (this=0xa835f20, hub=0x7fffffff6ba0, sd=0xa833670) at /home/blyth/opticks/cfg4/CGeometry.cc:82
    #14 0x00007ffff7b3403d in CG4::CG4 (this=0x7fffffff6ac0, hub=0x7fffffff6ba0) at /home/blyth/opticks/cfg4/CG4.cc:167
    #15 0x0000000000405a49 in main (argc=1, argv=0x7fffffff7558) at /home/blyth/opticks/cfg4/tests/CTestDetectorTest.cc:52
    (gdb) 


    (gdb) bt
    #0  0x00007fffe83fa387 in raise () from /lib64/libc.so.6
    #1  0x00007fffe83fba78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff160fbee in G4Exception(char const*, char const*, G4ExceptionSeverity, char const*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4global.so
    #3  0x00007ffff5ef3587 in G4GDMLEvaluator::DefineConstant(G4String const&, double) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #4  0x00007ffff5ef46e7 in G4GDMLEvaluator::DefineMatrix(G4String const&, int, std::vector<double, std::allocator<double> >) ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #5  0x00007ffff5f06b78 in G4GDMLReadDefine::MatrixRead(xercesc_3_2::DOMElement const*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #6  0x00007ffff5f09460 in G4GDMLReadDefine::DefineRead(xercesc_3_2::DOMElement const*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #7  0x00007ffff5f02b14 in G4GDMLRead::Read(G4String const&, bool, bool, bool) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    #8  0x00007ffff7b1dd8d in G4GDMLParser::Read (this=0x7fffffff5ab0, filename=..., validate=false) at /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4GDMLParser.icc:37
    #9  0x00007ffff7b1d0c6 in CGDMLDetector::parseGDML (this=0xa836000, 
        path=0x6e6470 "/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml") at /home/blyth/opticks/cfg4/CGDMLDetector.cc:121
    #10 0x00007ffff7b1cee3 in CGDMLDetector::init (this=0xa836000) at /home/blyth/opticks/cfg4/CGDMLDetector.cc:91
    #11 0x00007ffff7b1cb84 in CGDMLDetector::CGDMLDetector (this=0xa836000, hub=0x7fffffff6ba0, query=0x6de5d0, sd=0xa833670) at /home/blyth/opticks/cfg4/CGDMLDetector.cc:63
    #12 0x00007ffff7ac02e6 in CGeometry::init (this=0xa835f20) at /home/blyth/opticks/cfg4/CGeometry.cc:99
    #13 0x00007ffff7ac00dc in CGeometry::CGeometry (this=0xa835f20, hub=0x7fffffff6ba0, sd=0xa833670) at /home/blyth/opticks/cfg4/CGeometry.cc:82
    #14 0x00007ffff7b3403d in CG4::CG4 (this=0x7fffffff6ac0, hub=0x7fffffff6ba0) at /home/blyth/opticks/cfg4/CG4.cc:167
    #15 0x0000000000405a49 in main (argc=1, argv=0x7fffffff7558) at /home/blyth/opticks/cfg4/tests/CTestDetectorTest.cc:52
    (gdb) f 9
    #9  0x00007ffff7b1d0c6 in CGDMLDetector::parseGDML (this=0xa836000, 
        path=0x6e6470 "/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml") at /home/blyth/opticks/cfg4/CGDMLDetector.cc:121
    121	    parser.Read(path, validate);
    (gdb) f 8
    #8  0x00007ffff7b1dd8d in G4GDMLParser::Read (this=0x7fffffff5ab0, filename=..., validate=false) at /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4GDMLParser.icc:37
    37	  reader->Read(filename,validate,false,strip);
    (gdb) f 7
    #7  0x00007ffff5f02b14 in G4GDMLRead::Read(G4String const&, bool, bool, bool) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    (gdb) f 6
    #6  0x00007ffff5f09460 in G4GDMLReadDefine::DefineRead(xercesc_3_2::DOMElement const*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    (gdb) f 5
    #5  0x00007ffff5f06b78 in G4GDMLReadDefine::MatrixRead(xercesc_3_2::DOMElement const*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    (gdb) f 4
    #4  0x00007ffff5ef46e7 in G4GDMLEvaluator::DefineMatrix(G4String const&, int, std::vector<double, std::allocator<double> >) ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    (gdb) f 3
    #3  0x00007ffff5ef3587 in G4GDMLEvaluator::DefineConstant(G4String const&, double) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so
    (gdb) f 2
    #2  0x00007ffff160fbee in G4Exception(char const*, char const*, G4ExceptionSeverity, char const*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4global.so
    (gdb) 



     80 void G4GDMLEvaluator::DefineMatrix(const G4String& name,
     81                                          G4int coldim,
     82                                          std::vector<G4double> valueList)
     83 {  
     84    const G4int size = valueList.size();
     85    
     86    if (size == 0)
     87    { 
     88      G4String error_msg = "Matrix '"+name+"' is empty!";
     89      G4Exception("G4GDMLEvaluator::DefineMatrix()", "InvalidSize",
     90                  FatalException, error_msg);
     91    }
     92    /*
     93    if (size == 1)
     94    {
     95      G4String error_msg = "Matrix '" + name
     96                         + "' has only one element! "
     97                         + "Define a constant instead!!";
     98      G4Exception("G4GDMLEvaluator::DefineMatrix()", "InvalidSize",
     99                  FatalException, error_msg);
    100    }
    101    */
    102    
    103    if (size % coldim != 0)
    104    { 
    105      G4String error_msg = "Matrix '" + name + "' is not filled correctly!";
    106      G4Exception("G4GDMLEvaluator::DefineMatrix()", "InvalidSize",
    107                  FatalException, error_msg);
    108    }
    109    
    110    if ((size == coldim) || (coldim == 1))   // Row- or column matrix
    111    {  
    112       for (G4int i=0;i<size;i++)
    113       {  
    114          std::stringstream MatrixElementNameStream;
    115          MatrixElementNameStream << name << "_" << i;
    116          DefineConstant(MatrixElementNameStream.str(),valueList[i]);
    117       }
    118    }
    119    else   // Normal matrix
    120    {  
    121       const G4int rowdim = size/coldim;
    122       
    123       for (G4int i=0;i<rowdim;i++)
    124       { 
    125         for (G4int j=0;j<coldim;j++)
    126         { 
    127           std::stringstream MatrixElementNameStream;
    128           MatrixElementNameStream << name << "_" << i << "_" << j;
    129           DefineConstant(MatrixElementNameStream.str(),valueList[coldim*i+j]);
    130         }
    131       }



