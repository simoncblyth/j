G4VTouchable::GetReplicaNumber
================================


G4VTouchable::GetReplicaNumber(1)
-----------------------------------

* https://geant4-forum.web.cern.ch/t/identification-of-unique-physical-volumes-with-ids/2568

What you can do at tracking time is make use of the G4Touchable from the
G4Step. From touchable->GetCopyNumber(), you can get the SiPM’s copy number,
iSiPM. Then you can go up the placement tree, what’s called the touchable’s
“history”, and get touchable->GetCopyNumber(1) for the copy number of the
SiPM’s parent volume, touchable->GetCopyNumber(2) for the grandparent volume,
and so on. If the SiPM’s are placed directly into your scintillator assembly,
then iScint = touchable->GetCopyNumber(1) is the scintillator’s copy number.


GetReplicaNumber
-------------------

::

    epsilon:ntds blyth$ g4-hh GetReplicaNumber
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/visualization/modeling/include/G4PhysicalVolumeModel.hh:    G4int GetReplicaNumber(G4int depth) const;
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/visualization/gMocren/include/G4GMocrenTouchable.hh:  virtual G4int GetReplicaNumber(G4int depth=0) const;
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/visualization/gMocren/include/G4GMocrenTouchable.hh:G4int G4GMocrenTouchable::GetReplicaNumber(G4int depth) const {
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/visualization/gMocren/include/G4GMocrenTouchable.hh:    G4Exception("G4GMocrenTouchable::GetReplicaNumber(G4int)", "gMocren0001",
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/geometry/management/include/G4VTouchable.hh://   4) GetReplicaNumber or GetCopyNumber gives the copy number of the
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/geometry/management/include/G4VTouchable.hh://   6) GetReplicaNumber/GetCopyNumber, GetVolume, GetTranslation and
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/geometry/management/include/G4VTouchable.hh:  virtual G4int GetReplicaNumber(G4int depth=0) const;
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/geometry/volumes/include/G4TouchableHistory.hh:  inline G4int GetReplicaNumber( G4int depth=0 ) const;
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/geometry/biasing/include/G4GeometryCell.hh:  G4int GetReplicaNumber() const;
    epsilon:ntds blyth$ 


g4-cls G4TouchableHistory::

    074   inline G4int GetReplicaNumber( G4int depth=0 ) const;
    ...
     93  private:
     94 
     95   inline G4int CalculateHistoryIndex( G4int stackDepth ) const;
     96 
     97   G4RotationMatrix frot;
     98   G4ThreeVector ftlate;
     99   G4NavigationHistory fhistory;
    100 };


     53 inline
     54 G4int G4TouchableHistory::CalculateHistoryIndex( G4int stackDepth ) const
     55 {
     56   return (fhistory.GetDepth()-stackDepth); // was -1
     57 }
     58 

     72 inline
     73 G4int G4TouchableHistory::GetReplicaNumber( G4int depth ) const
     74 {
     75   return fhistory.GetReplicaNo(CalculateHistoryIndex(depth));
     76 }

g4-cls G4NavigationHistory::

    147  private:
    148 
    149   std::vector<G4NavigationLevel> *fNavHistory;
    150     // Pointer to the vector of navigation levels.
    151 
    152   G4int fStackDepth;
    153     // Depth of stack: effectively depth in geometrical tree.
    154 };

    159 inline
    160 G4int G4NavigationHistory::GetReplicaNo(G4int n) const
    161 {
    162   return (*fNavHistory)[n].GetReplicaNo();
    163 }
    164 


g4-cls G4NavigationLevel::

    060 inline
     61 G4int G4NavigationLevel::GetReplicaNo() const
     62 {
     63   return fLevelRep->GetReplicaNo() ;
     64 }


g4-cls G4NavigationLevelRep::

    098  private:
     99 
    100    G4AffineTransform  sTransform;
    101      // Compounded global->local transformation (takes a point in the 
    102      // global reference system to the system of the volume at this level)
    103 
    104    G4VPhysicalVolume* sPhysicalVolumePtr;
    105      // Physical volume ptrs, for this level's volume
    106 
    107    G4int              sReplicaNo;
    108    EVolume            sVolumeType;
    109      // Volume `type' 
    110 
    111    G4int              fCountRef;
    112 
    113 };



