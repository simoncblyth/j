/**
LSExpDetectorConstruction::setupCD_Sticks
-------------------------------------------


   declProp              csv

   StrutPosFile          Strut_Acrylic.csv             370
   Strut2PosFile         StrutBar2_Acrylic.csv         220
   FastenerPosFile       Strut_Anchor_Acrylic.csv      590
   XJanchorPosFile       XJanchor.csv                  56
   SJCLSanchorPosFile    SJCLSanchor.csv               2
   SJReceiverPosFile     SJReceiverPos.csv             8
   SJFixturePosFile      SJFixturePos.csv              36






j/PosFile/HexagonPosBallTest.py 
+------------------+-----------------+----------------------+--------------------------------------------------------------------------------------------+
|             csv  |             npy |                  key |                                   $JUNOTOP/offline/Simulation/DetSimV2/DetSimOptions/data/ |
+==================+=================+======================+============================================================================================+
|          (370,)  |     (370, 4, 4) |         StrutPosFile |                                                                          Strut_Acrylic.csv |
+------------------+-----------------+----------------------+--------------------------------------------------------------------------------------------+
|          (220,)  |     (220, 4, 4) |        Strut2PosFile |                                                                      StrutBar2_Acrylic.csv |
+------------------+-----------------+----------------------+--------------------------------------------------------------------------------------------+
|          (590,)  |     (590, 4, 4) |      FastenerPosFile |                                                                   Strut_Anchor_Acrylic.csv |
+------------------+-----------------+----------------------+--------------------------------------------------------------------------------------------+
|           (56,)  |      (56, 4, 4) |      XJanchorPosFile |                                                                               XJanchor.csv |
+------------------+-----------------+----------------------+--------------------------------------------------------------------------------------------+
|            (2,)  |       (2, 4, 4) |   SJCLSanchorPosFile |                                                                            SJCLSanchor.csv |
+------------------+-----------------+----------------------+--------------------------------------------------------------------------------------------+
|            (8,)  |       (8, 4, 4) |    SJReceiverPosFile |                                                                          SJReceiverPos.csv |
+------------------+-----------------+----------------------+--------------------------------------------------------------------------------------------+
|           (36,)  |      (36, 4, 4) |     SJFixturePosFile |                                                                           SJFixturePos.csv |
+------------------+-----------------+----------------------+--------------------------------------------------------------------------------------------+

Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py::

    self._factory.property("CDName").set("DetSim1")
    self._factory.property("StrutPosFile").set(DetSimOptions.data_load("Strut_Acrylic.csv"))
    self._factory.property("Strut2PosFile").set(DetSimOptions.data_load("StrutBar2_Acrylic.csv"))
    self._factory.property("FastenerPosFile").set(DetSimOptions.data_load("Strut_Anchor_Acrylic.csv"))
    self._factory.property("XJanchorPosFile").set(DetSimOptions.data_load("XJanchor.csv"))
    self._factory.property("SJCLSanchorPosFile").set(DetSimOptions.data_load("SJCLSanchor.csv"))
    self._factory.property("SJReceiverPosFile").set(DetSimOptions.data_load("SJReceiverPos.csv"))
    self._factory.property("SJFixturePosFile").set(DetSimOptions.data_load("SJFixturePos.csv"))


   declProp              csv

   StrutPosFile          Strut_Acrylic.csv             370
   Strut2PosFile         StrutBar2_Acrylic.csv         220
   FastenerPosFile       Strut_Anchor_Acrylic.csv      590
   XJanchorPosFile       XJanchor.csv                  56
   SJCLSanchorPosFile    SJCLSanchor.csv               2
   SJReceiverPosFile     SJReceiverPos.csv             8
   SJFixturePosFile      SJFixturePos.csv              36




**/


#include <iostream>
#include <iomanip>

#include "HexagonPosBall.hh"
#include "Radius.hh"
#include "NP.hh"

using JUNO::Ball::HexagonPosBall ; 


void ReadTransform( double* vv, const G4Transform3D& tr )
{
    vv[ 0] = tr.xx()  ;  vv[1] = tr.yx()  ; vv[ 2] = tr.zx()  ; vv[ 3] = 0. ; 
    vv[ 4] = tr.xy()  ;  vv[5] = tr.yy()  ; vv[ 6] = tr.zy()  ; vv[ 7] = 0. ; 
    vv[ 8] = tr.xz()  ;  vv[9] = tr.yz()  ; vv[10] = tr.zz()  ; vv[11] = 0. ;  
    vv[12] = tr.dx() ;  vv[13] = tr.dy()  ; vv[14] = tr.dz()  ; vv[15] = 1. ;  
} 




int main(int argc, char** argv)
{
     const char* path = argc > 1 ? argv[1] : nullptr ; 
     if(path == nullptr ) 
     {
         //std::cout << " ERROR expecting path to PosFile " << std::endl ;  
         Radius::Dump(); 
         return 1 ;  
     }

     // HMM: potentially due to a bug the CSV name cannot be used as the key  


     std::string name = U::BaseName(path); 
     double radius = Radius::GetCSV(name.c_str()) ; 
     bool lpmt = false ; 
     HexagonPosBall posfile(path, radius, lpmt ); 
     unsigned num_tran = posfile.m_position.size() ;

     NP* a = NP::Make<double>( num_tran, 4, 4 ) ; 
     for(unsigned i=0 ; i < num_tran ; i++) ReadTransform( a->values<double>() + i*4*4, posfile.m_position[i] ); 

     std::string apath = U::ChangeExt(path, ".csv", ".npy" ); 
     std::cout 
         << " posfile.m_position.size " << std::setw(6) << num_tran 
         << " save to " << apath  
         << std::endl 
         ;

     a->save( apath.c_str() ); 

     return 0 ; 
}
