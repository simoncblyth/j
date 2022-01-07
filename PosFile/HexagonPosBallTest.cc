
/**
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
**/


#include <iostream>
#include <iomanip>

#include "HexagonPosBall.hh"
#include "Radius.hh"
#include "NP.hh"

using JUNO::Ball::HexagonPosBall ; 

/**

 
    00:xx 01:yx 02:zx 03:0
    04:xy 05:yy 06:zy 07:0
    08:xz 09:yz 10:zz 11:0
    12:dx 13:dy 14:dz 15:1

**/

void ReadTransform( double* vv, const G4Transform3D& tr )
{
    vv[0] = tr.xx()  ;  vv[1] = tr.yx()  ; vv[2] = tr.zx()  ; vv[3] = 0. ; 
    vv[4] = tr.xy()  ;  vv[5] = tr.yy()  ; vv[6] = tr.zy()  ; vv[7] = 0. ; 
    vv[8] = tr.xz()  ;  vv[9] = tr.yz()  ; vv[10] = tr.zz() ; vv[11] = 0. ;  
    vv[12] = tr.dx() ;  vv[13] = tr.dy() ; vv[14] = tr.dz() ; vv[15] = 1. ;  
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

     std::string name = U::BaseName(path); 
     double radius = Radius::GetCSV(name.c_str()) ; 
     bool lpmt = false ; 
     HexagonPosBall posfile(path, radius, lpmt ); 
     unsigned num_tran = posfile.m_position.size() ;

     NP* a = NP::Make<double>( num_tran, 4, 4 ) ; 
     double* aa = a->values<double>(); 
     for(unsigned i=0 ; i < num_tran ; i++) ReadTransform( aa + i*4*4, posfile.m_position[i] ); 
     std::string apath = U::ChangeExt(path, ".csv", ".npy" ); 

     std::cout 
         << " posfile.m_position.size " << std::setw(6) << num_tran 
         << " save to " << apath  
         << std::endl 
         ;

     a->save( apath.c_str() ); 

     return 0 ; 
}
