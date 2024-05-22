Calib_GuideTube_Construction/Calib_GuideTube_Construction.rst
================================================================

::

     jcv Calib_GuideTube_Construction


Two sets of nested G4Torus (Teflon and Water) volumes split in phi::

    45     enum {GT_number = 39}


Both sets have same Rtor Rmin 0. and Rmax differs::

     49 //     G4Torus(const G4String      &pName
     50 //             G4double      pRmin
     51 //             G4double      pRmax
     52 //             G4double      pRtor
     53 //             G4double      pSPhi
     54 //             G4double      pDPhi )
     55 //

