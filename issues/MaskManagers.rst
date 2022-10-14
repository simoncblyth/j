MaskManagers
=================

For a long time have had uncommitted SVN change::

    N[blyth@localhost ~]$ jre
    === j-runtime-env-:
    === j-runtime-env-:
    /data/blyth/junotop/offline
    M       Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    M       Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    M       Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    M       Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    N[blyth@localhost offline]$ 

Need to revisit this and commit before can work on updating 
the integration to use the new workflow. 

The changes are 

1. addition of debugging getLV code and PMTSim standalone instrumentation : changes to header and imp
2. substantive uncoincide additions
3. documenation text 



HAMA Fix #33
--------------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/issues/33

* NNVT : BodySolid and MaskTail : ellipsoids look to share centers with just scale difference. 
* HAMA : BodySolid and MaskTail : ellipsoids appear offset causing crossover 

Find how NNVT ellipsoids get tied together. 

* suspect just by using same params, not by using a common source 



Manual "fitting" ellipses to the NNVT PMT works easily without any offsets::

    ELLIPSE0=249,179 ./mct.sh ## NNVT pmt_in
    ELLIPSE0=254,184 ./mct.sh ## NNVT pmt_out  +5
    ELLIPSE0=256,186 ./mct.sh ## NNVT mask_in  +5+2
    ELLIPSE0=264,194 ./mct.sh ## NNVT mask_out +5+2+8

HAMA PMT top hemi also works easily::

    ELLIPSE0=249,185      ELLIPSE0_OPT=top ./mct.sh  ##        HAMA pmt_in   
    ELLIPSE0=254,190      ELLIPSE0_OPT=top ./mct.sh  ## +5     HAMA pmt_out 
    ELLIPSE0=256,192      ELLIPSE0_OPT=top ./mct.sh  ## +5+2   HAMA mask_in  
    ELLIPSE0=264,200      ELLIPSE0_OPT=top ./mct.sh  ## +5+2+8 HAMA mask_out

HAMA PMT bottom hemi, not so easy, needs -5 offset for PMT but not for mask::

    ELLIPSE0=249,185,0,-5 ELLIPSE0_OPT=bot ./mct.sh  ## HAMA pmt_in 
    ELLIPSE0=254,190,0,-5 ELLIPSE0_OPT=bot ./mct.sh  ## HAMA pmt_out 
    ELLIPSE0=256,192      ELLIPSE0_OPT=bot ./mct.sh  ## HAMA mask_in 
    ELLIPSE0=264,200      ELLIPSE0_OPT=bot ./mct.sh  ## HAMA mask_out 

The need for offset ellipse for PMT but not for mask explains the problem. 


To match the HAMA PMT shape the mask will need the 
thin equatorial cylinder ? To offset shift the ellipsoid downwards ?

HMM : But 

::

    146 G4VSolid* Hamamatsu_R12860_PMTSolid::GetSolid(G4String solidname, double thickness, char mode)
    147 {
    148     G4VSolid* pmt_solid = NULL;
    149 
    150     double P_I_R = m1_r + thickness;
    151     double P_I_H = m1_h + thickness;
    152 
    153     G4VSolid* solid_I = new G4Ellipsoid(
    154                     solidname+"_I",
    155                     P_I_R,
    156                     P_I_R,
    157                     P_I_H,
    158                     0, // pzBottomCut -> equator
    159                     P_I_H // pzTopCut -> top
    160                     );
    161 
    162     G4VSolid* solid_II = new G4Tubs(
    163                     solidname+"_II",
    164                     0.0,
    165                     P_I_R,
    166                     m2_h/2,
    167                     0.*deg,
    168                     360.*deg
    169                     );
    170     G4cout << __FILE__ << ":" <<  __LINE__ << G4endl;
    171     // I+II
    172 
    173     if( mode == ' ' || mode == 'H' )   // head mode 'H' doesnt care, as solid_I is returned  
    174     {
    175         pmt_solid = new G4UnionSolid(
    176                  solidname+"_1_2",
    177                  solid_I,     // upper hemi-ellipsoid
    178                  solid_II,    // thin equatorial cylinder, pushed down in z, top at z=0
    179                  0,
    180                  G4ThreeVector(0,0,-m2_h/2)
    181                  );
    182     }
    ...
    207 
    208     G4VSolid* solid_III = new G4Ellipsoid(
    209                       solidname+"_III",
    210                       P_I_R,
    211                       P_I_R,
    212                       P_I_H,
    213                       -P_I_H,
    214                       0);
    215 
    216     // +III
    217     pmt_solid = new G4UnionSolid(
    218                  solidname+"_1_3",
    219                  pmt_solid,
    220                  solid_III,
    221                  0,
    222                  G4ThreeVector(0,0,-m2_h)
    223                  );
    224 


HMM: there is no need for the waist tubs just need to arrange to push the ellipsoids down by 5mm  

* suppose could do that by using G4Polycone for


The structure of mask inner and outer is::


     Tail_outer_I   : Union ( Tail_outer_I_Ellipsoid ,  Tail_outer_I_Tube )

     Tail_outer_II_Tube 

     Tail_outer     : Union( Tail_outer_I , Tail_outer_II_Tube ) 


     Tail_outer  :    Union( Union( Tail_outer_I_Ellipsoid ,  Tail_outer_I_Tube ),  Tail_outer_II_Tube ) 




                                                Tail_outer
                                              /             \

                             Tail_outer_I                  Tail_outer_II_Tube

                            /             \
                             
          Tail_outer_I_Ellipsoid        Tail_outer_I_Tube         




Union of two tubs and an ellipsoid : with offsets for every RHS (so ellipsoid doesnt get a transform)

* BUT the ellipsoid needs dz -5 mm  
* could flip the ellipsoid tubs union using polycone for the tubs to place it 
  and then can shift the ellipsoid



* TODO: PMTSIM_STANDALONE addValue in NNVTMCPPMTManager, HamamatsuR12860PMTManager


jcv NNVTMaskManager NNVTMCPPMTManager::

    207 void NNVTMCPPMTManager::init_variables()
    208 {
    209     m_pmt_r = 254.*mm;
    210     m_pmt_h = 570.*mm;
    211     m_z_equator = 184.*mm; // From top to equator
    212 
    213     // Reduce the height of PMT
    214     // Tao Lin, 09 Aug 2021
    215     if (m_useRealSurface) {
    216         const double radInnerWaterRealSurface = 19.629*m;
    217         const double r = m_pmt_r + 1.*cm; // 1cm is the mask
    218         double pmt_eq_to_bottom = sqrt(radInnerWaterRealSurface*radInnerWaterRealSurface
    219                                        -r*r) - 19.434*m; // at z equator
    220         // then, subtract the thickness of mask
    221         pmt_eq_to_bottom -= 10.*mm;
    222 
    223         // avoid the overlap between PMT tail and innerWater
    224         const double safety_distance = 1.*cm;
    225         pmt_eq_to_bottom -= safety_distance;
    226 
    227 
    228 
    229         m_pmt_equator_to_bottom = pmt_eq_to_bottom ;
    230 
    231         double pmt_h = pmt_eq_to_bottom + m_z_equator ;
    232         LogInfo << "Option RealSurface is enabled in Central Detector. "
    233                 << " Reduce the m_pmt_h from "
    234                 << m_pmt_h << " to " << pmt_h
    235                 << std::endl;
    236         m_pmt_h = pmt_h;
    237     }
    238 




Compare HamamatsuMaskManager with NNVTMaskManager to fix impingement of Mask and MaskVirtual
-------------------------------------------------------------------------------------------------

Need to compare::

     HamamatsuMaskManager::makeMaskTailLogical
     NNVTMaskManager::makeMaskTailLogical

This comparison led to probable NNVT fix

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/issues/32

   


::

    epsilon:CSG blyth$ GEOM=nmskSolidMaskTail__U1 ~/opticks/CSG/ct.sh ana 

    In [1]: sv 
    Out[1]: 
    Values.sv : /tmp/blyth/opticks/GEOM/nmskSolidMaskTail__U1/Values : contains:None  
      0 :   264.0000 : SolidMaskTail.TailOuterIEllipsoid.pxySemiAxis.mask_radiu_out 
      1 :   194.0000 : SolidMaskTail.TailOuterIEllipsoid.pzSemiAxis.htop_out 
      2 :  -194.0000 : SolidMaskTail.TailOuterIEllipsoid.pzBottomCut.-htop_out 
      3 :   -39.0000 : SolidMaskTail.TailOuterIEllipsoid.pzTopCut.-height_out 

      4 :   264.0000 : SolidMaskTail.TailOuterITube.outerRadius.mask_radiu_out 
      5 :     0.1500 : SolidMaskTail.TailOuterITube.zhalfheight.paramRealMaskTail.edge_height/2 
      6 :   -39.1500 : SolidMaskTail.TailOuterITube.zoffset.-(height_out+paramRealMaskTail.edge_height/2) 
      ## thin lip at the top 


      7 :   134.0000 : SolidMaskTail.TailOuterIITube.outerRadius.paramRealMaskTail.r2 
      8 :    72.1123 : SolidMaskTail.TailOuterIITube.zhalfheight.paramRealMaskTail.height/2 
      9 :  -111.1123 : SolidMaskTail.TailOuterIITube.zoffset.-(height_out+paramRealMaskTail.height/2) 
     10 :   256.0000 : SolidMaskTail.TailInnerIEllipsoid.pxySemiAxis.mask_radiu_in 
     11 :   186.0000 : SolidMaskTail.TailInnerIEllipsoid.pzSemiAxis.htop_in 
     12 :  -186.0000 : SolidMaskTail.TailInnerIEllipsoid.pzBottomCut.-htop_in 
     13 :   -39.0000 : SolidMaskTail.TailInnerIEllipsoid.pzTopCut.-height_out 
     14 :     0.5000 : SolidMaskTail.TailInnerITube.TailInnerI_uncoincide_z/2 
     15 :   256.0000 : SolidMaskTail.TailInnerITube.outerRadius.mask_radiu_in 
     16 :     0.6500 : SolidMaskTail.TailInnerITube.zhalfheight.paramRealMaskTail.edge_height/2 + TailInnerI_uncoincide_z/2 
     17 :   -38.6500 : SolidMaskTail.TailInnerITube.zoffset.-(height_out+paramRealMaskTail.edge_height/2) + TailInnerI_uncoincide_z/2 
     18 :   126.0000 : SolidMaskTail.TailInnerIITube.outerRadius.paramRealMaskTail.r2 - requator_thickness 
     19 :    68.1123 : SolidMaskTail.TailInnerIITube.zhalfheight.(paramRealMaskTail.height-htop_thickness)/2 
     20 :  -107.1123 : SolidMaskTail.TailInnerIITube.zoffset.-(height_out+(paramRealMaskTail.height-htop_thickness)/2) 




WIP : review all changes from jps that want to be in offline
--------------------------------------------------------------

jdiff HamamatsuR12860PMTManager

   * switch to CamelCase lv/pv/solid names in debug interface as underscore used to delimit options
   * proper base class setup for now non-pure-virtual IGeomManager (providing eg getValues debug method)
   * reduce code differences with and without PMTSIM_STANDALONE (due to new IGeomManager dummy declProp)

jdiff NNVTMCPPMTManager

   * switch to CamelCase lv/pv/solid names in debug interface as underscore used to delimit options
   * proper base class setup for now non-pure-virtual IGeomManager (providing eg getValues debug method)
    
jdiff NNVTMaskManager

   * add IGeomManager base class with PMTSIM_STANDALONE macro providing debug access to Geant4 objects 
   * add debug interface getLV getPV getSolid by name, and private members for Geant4 objects 
   * use private members instead of method scope variables for Geant4 objects
   * within PMTSIM_STANDALONE addValue collection of values for debug access as NP array via IGeomManager base class  
   * add MaskIn_uncoincide_z to avoid coincidence 
   * add TailInnerI_uncoincide_z to avoid coincidence

jdiff HamamatsuMaskManager

   * add IGeomManager base class with PMTSIM_STANDALONE macro providing debug access to Geant4 objects 
   * add debug interface getLV getPV getSolid by name, and private members for Geant4 objects 
   * use private members instead of method scope variables for Geant4 objects
   * within PMTSIM_STANDALONE addValue collection of values for debug access as NP array via IGeomManager base class  
   * add MaskIn_uncoincide_z to avoid coincidence 
   * add TailInnerI_uncoincide_z to avoid coincidence 


Branch title : blyth-PMTSIM_STANDALONE-debug-interface-for-mask-managers-and-uncoincide-mask-subtractions



ZSolid vs X4SolidTree
------------------------

Why did I make the change from ZSolid to X4SolidTree withinn jps ?

* this is presumably because PMTSim depends on SysRap which has SCanvas.h already 
  
  * BUT: as offline dev so inconvenient compared to Opticks it is expedient 
    just to throw away code put into offline : not regarding it as part of the 
    ongoing history of the versions within Opticks

  * SO : that means to use different names within offline and opticks

* HMM: it was a mistake to change names within jps:j/PMTSim  
* should regard jps as temporary development ground for visiting classes from offline
  and keep them distinct from Opticks : with minimal changes

* regard ZSolid/ZCanvas as names of version included with offline
* keep X4SolidTree.hh as distinct other class kept with extg4 

Sort this out by:

1. changing the X4SolidTree name back to ZSolid : to reduce differences
2. review differences between jps and jo and decide if any diffs should be 
   incorporated into offline 




How do the SVN WC changes compare with j ?
----------------------------------------------

::

    epsilon:j blyth$ find . -name HamamatsuMaskManager.* -o -name NNVTMaskManager.* 
    ./PMTSim/HamamatsuMaskManager.cc
    ./PMTSim/NNVTMaskManager.cc
    ./PMTSim/NNVTMaskManager.hh
    ./PMTSim/HamamatsuMaskManager.hh
    epsilon:j blyth$ 


No difference::

    N[blyth@localhost PMTSim]$ jdiff HamamatsuMaskManager NNVTMaskManager
    diff /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh /home/blyth/j/PMTSim/HamamatsuMaskManager.hh
    diff /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh /home/blyth/j/PMTSim/NNVTMaskManager.hh
    diff /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc /home/blyth/j/PMTSim/HamamatsuMaskManager.cc
    diff /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc /home/blyth/j/PMTSim/NNVTMaskManager.cc
    N[blyth@localhost PMTSim]$ jdiff HamamatsuMaskManager NNVTMaskManager | sh 
    N[blyth@localhost PMTSim]$ 

The SVN working copy can safely be reverted as the jps versions match them::

    N[blyth@localhost PMTSim]$ jcopyback HamamatsuMaskManager NNVTMaskManager 
    cp /home/blyth/j/PMTSim/HamamatsuMaskManager.hh /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    cp /home/blyth/j/PMTSim/NNVTMaskManager.hh /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    cp /home/blyth/j/PMTSim/HamamatsuMaskManager.cc /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    cp /home/blyth/j/PMTSim/NNVTMaskManager.cc /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    N[blyth@localhost PMTSim]$ 


Source SVN has probably been updated ?
----------------------------------------

* 5 months ago changes in .cc from lintao 

* 5306 WIP: try to reduce the radius at front using 4 zplanes (bottom:R, 
* 5305 WIP: in order to avoid the overlap between water and tail of PMT, 
* 5302 WIP: debug the overlap problem in the virtual volumes.

* https://juno.ihep.ac.cn/trac/log/offline/trunk/Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
* https://juno.ihep.ac.cn/trac/log/offline/trunk/Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc

No changes in header since 11 months:

* https://juno.ihep.ac.cn/trac/log/offline/trunk/Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
* https://juno.ihep.ac.cn/trac/log/offline/trunk/Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh


* https://juno.ihep.ac.cn/trac/changeset/5302/offline
 
  * changing visatt

* https://juno.ihep.ac.cn/trac/changeset/5305/offline

  * pmt_eq_to_bottom 1cm change done in quadriplicate

* https://juno.ihep.ac.cn/trac/changeset/5306/offline

  * "// BELOW is using 4 zplanes"




revert the WC changes
-------------------------

Looking at my versions it looks like the lintao changes are already there 

* so I can revert the WC, update svn and compare again and it should be possible 
  to jcopyback : if not I just have to make the changes again 


::

    N[blyth@localhost offline]$ jo
    /data/blyth/junotop/offline
    M       Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    M       Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    M       Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    M       Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    N[blyth@localhost offline]$ svn revert Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    Reverted 'Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh'
    N[blyth@localhost offline]$ svn revert Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    Reverted 'Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh'
    N[blyth@localhost offline]$ svn revert Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    Reverted 'Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc'
    N[blyth@localhost offline]$ svn revert Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    Reverted 'Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc'
    N[blyth@localhost offline]$ jo
    /data/blyth/junotop/offline
    N[blyth@localhost offline]$ 





