InputPhotonsCheck_WP_virtualwrapper_touching
================================================


ipcv::

    223     elif [ "$TEST" == "WP_PMT_SEMI" ]; then
    224
    225        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    226        opticks_input_photon=SemiCircleXZ_R-500_100k_f8.npy
    227        opticks_input_photon_frame=PMT_20inch_veto:0:1000
    228        observation=""



Using SemiCircle input photons onto WP_PMT gives OK CHI2
BUT quite a few BZERO (Opticks-only) histories


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum    58.2633 ndf 64.0000 sum/ndf     0.9104 </span> ]
    TO BT BT BT BT SA                                                                                :   26918  26986 :     0.0858 : Y :       2      2 :    
    TO BT BT BT BT EC                                                                                :   25676  25837 :     0.5032 : Y :      15     27 :    
    TO BT BT BT BT BT SR SA                                                                          :   10281  10314 :     0.0529 : Y :      57    205 :    
    TO BT BT BT BT BR BT BT BT BT SA                                                                 :    9972  10021 :     0.1201 : Y :    1668   1665 :    
    TO BT BT BT BT BT SR BT BT BT BT BT SA                                                           :    8187   8225 :     0.0880 : Y :    7251   7262 :    
    TO BT BT BT BT BT SA                                                                             :    2686   2623 :     0.7476 : Y :      32     19 :    
    TO BT BT BT BT BT SR BR SR SA                                                                    :    2418   2400 :     0.0672 : Y :    7328   7099 :    
    TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                     :    2047   1929 :     3.5020 : Y :    9325   9317 :    
    TO BT BT BT BT EX                                                                                :    1896   1862 :     0.3076 : Y :       7      3 :    
    TO BT BT BT BT BT SR BR SA                                                                       :     823    816 :     0.0299 : Y :    3687   3693 :    
    TO BT BT BT BT BT SR BR SR BR SR SA                                                              :     740    712 :     0.5399 : Y :    8209   8570 :    
    TO BT BT BT BT BT SR SR SA                                                                       :     632    660 :     0.6068 : Y :      83    116 :    
    TO BT BT BT BT BT SR BR SR BR SR BT BT BT BT BT SA                                               :     576    632 :     2.5960 : Y :    8515   8566 :    
    TO AB                                                                                            :     587    592 :     0.0212 : Y :      25     96 :    
    TO BT BT BT BT BT SR BT BT BT BT BT AB                                                           :     456    419 :     1.5646 : Y :    3695   4870 :    
    TO BT BT BT BT BR BT BT BT BT AB                                                                 :     355    351 :     0.0227 : Y :     374     23 :    
    TO BT BT BT BT AB                                                                                :     298    309 :     0.1993 : Y :     199    239 :    
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT SA                                                     :     297    266 :     1.7069 : Y :    5807   5807 :    
    TO BT BR BT SA                                                                                   :     270    291 :     0.7861 : Y :    2273   1760 :    
    TO BT BT BR BT BT SA                                                                             :     279    270 :     0.1475 : Y :    3312   1779 :    
    TO BT BT BT BR BT BT BT SA                                                                       :     244    234 :     0.2092 : Y :    2006   1988 :    
    TO BT BT BT BT BT SR BR SR BR SR BR SR SA                                                        :     200    192 :     0.1633 : Y :    8372   9199 :    
    TO BT BT BT BT BT SR BR SR BR SR BR SR BT BT BT BT BT SA                                         :     178    181 :     0.0251 : Y :    8682   8350 :    
    TO BT BT BT BT BT SR BR SR BR SA                                                                 :     177    176 :     0.0028 : Y :    7958   7788 :    
    TO BT BT BT BT BT SR SR BR SR SA                                                                 :     159    163 :     0.0497 : Y :     999    917 :    
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT SA                                               :     126    138 :     0.5455 : Y :    3697   3692 :    
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT EC                                               :     111    133 :     1.9836 : Y :    3733   3698 :    
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT SA                                                  :     101    121 :     1.8018 : Y :    2557   2542 :    
    TO BT BT BT BT BT SR SR BR SR BT BT BT BT BT SA                                                  :     102    114 :     0.6667 : Y :    1424   1389 :    
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT BT SA                                            :      92    112 :     1.9608 : Y :     781    786 :    
    ...
    </pre>

.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc AZERO 
    ]sseq_index_ab::desc
    </pre>

.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc BZERO 
    TO BT BT BT SA                                                                                   :      45     -1 :     0.0000 : N :       3     -1 : BZERO C2EXC  
    TO BT BT BT EC                                                                                   :      38     -1 :     0.0000 : N :   49757     -1 : BZERO C2EXC  
    TO BT BT BT BT SR SA                                                                             :      17     -1 :     0.0000 : N :   49855     -1 : BZERO C2EXC  
    TO BT BT BT BT BT SR SR SR AB                                                                    :      17     -1 :     0.0000 : N :     706     -1 : BZERO C2EXC  
    TO BT BT BT BT SR BT BT BT BT BT SA                                                              :      15     -1 :     0.0000 : N :   49881     -1 : BZERO C2EXC  
    TO BT BT BT BR BT BT BT BT SA                                                                    :      11     -1 :     0.0000 : N :   49853     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc
    </pre>






EVT::

    elif [ "$EVT_CHECK" == "wp_pmt_semi_ipc" ]; then

        export AFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_SemiCircleXZ_R-500_100k_f8/A000
        export BFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_SemiCircleXZ_R-500_100k_f8/B000

        #export AFOLD_RECORD_SLICE="TO BT BT BT SA"    # just apex and waist
        #export AFOLD_RECORD_SLICE="TO BT BT BT EC"    # just apex and waist on one side 
        #export AFOLD_RECORD_SLICE="TO BT BT BT SA,TO BT BT BT EC"   # just apex and waist
        #export AFOLD_RECORD_SLICE="TO BT BT BT BT SR SA"   # from apex crosses vacuum SR on bottom and absorbed in way out
        #export AFOLD_RECORD_SLICE="TO BT BT BT BT BT SR SR SR AB"    # in close to waist bounce before absorbed on base
        #export AFOLD_RECORD_SLICE="TO BT BT BT BT SR BT BT BT BT BT SA"  # in thru apex, SR at bottom retrace path out the apex
        #export AFOLD_RECORD_SLICE="TO BT BT BT BR BT BT BT BT SA"    ## in thru apex, reflect before vacuum, and retrace path out 





Viz all those Opticks only histories shows all at apex OR waist.

Adding a BT makes the reason clear::

        export AFOLD_RECORD_SLICE="TO BT BT BT BT SA"
        export BFOLD_RECORD_SLICE="TO BT BT BT BT SA"




branch : blyth-add-envvar-control-R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM
--------------------------------------------------------------------------------------------

From branch with::

     43    export WaterPoolConstruction__CONFIG=3                              # HIERARCHY
     44    export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10                  # default 1.e-3
     45    export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10        # default 0.05
     46    export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10             # default 0.05
     47    export R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM=0.10  # default 0.05




.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum    60.5086 ndf 65.0000 sum/ndf     0.9309 </span> ]
    TO BT BT BT BT SA                                                                                :   26964  26997 :     0.0202 : Y :       2      2 :   
    TO BT BT BT BT EC                                                                                :   25721  25839 :     0.2701 : Y :      12     27 :   
    TO BT BT BT BT BT SR SA                                                                          :   10292  10313 :     0.0214 : Y :      23    205 :   
    TO BT BT BT BT BR BT BT BT BT SA                                                                 :    9983  10018 :     0.0612 : Y :    1668   1664 :   
    TO BT BT BT BT BT SR BT BT BT BT BT SA                                                           :    8210   8225 :     0.0137 : Y :    7311   7262 :   
    TO BT BT BT BT BT SA                                                                             :    2689   2612 :     1.1185 : Y :       6     19 :   
    TO BT BT BT BT BT SR BR SR SA                                                                    :    2420   2400 :     0.0830 : Y :    7328   7099 :   
    TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                     :    2052   1929 :     3.8003 : Y :    9325   9317 :   
    TO BT BT BT BT EX                                                                                :    1900   1853 :     0.5886 : Y :       1      3 :   
    TO BT BT BT BT BT SR BR SA                                                                       :     824    821 :     0.0055 : Y :    3687   3693 :   
    TO BT BT BT BT BT SR BR SR BR SR SA                                                              :     744    712 :     0.7033 : Y :    8209   8570 :   
    TO BT BT BT BT BT SR SR SA                                                                       :     631    661 :     0.6966 : Y :      83    116 :   
    TO BT BT BT BT BT SR BR SR BR SR BT BT BT BT BT SA                                               :     576    632 :     2.5960 : Y :    8515   8566 :   
    TO AB                                                                                            :     587    589 :     0.0034 : Y :      25     96 :   
    TO BT BT BT BT BT SR BT BT BT BT BT AB                                                           :     456    420 :     1.4795 : Y :    3695   4870 :   
    TO BT BT BT BT BR BT BT BT BT AB                                                                 :     355    347 :     0.0912 : Y :     374     23 :   
    TO BT BT BT BT AB                                                                                :     298    309 :     0.1993 : Y :     199    239 :   
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT SA                                                     :     297    266 :     1.7069 : Y :    5807   5807 :   
    TO BT BR BT SA                                                                                   :     270    291 :     0.7861 : Y :    2273   1759 :   
    TO BT BT BR BT BT SA                                                                             :     279    270 :     0.1475 : Y :    3312   1778 :   
    TO BT BT BT BR BT BT BT SA                                                                       :     241    234 :     0.1032 : Y :    2006   1987 :   
    TO BT BT BT BT BT SR BR SR BR SR BR SR SA                                                        :     201    192 :     0.2061 : Y :    8372   9199 :   
    TO BT BT BT BT BT SR BR SR BR SR BR SR BT BT BT BT BT SA                                         :     178    181 :     0.0251 : Y :    8682   8350 :   
    TO BT BT BT BT BT SR BR SR BR SA                                                                 :     177    176 :     0.0028 : Y :    7958   7788 :   
    TO BT BT BT BT BT SR SR BR SR SA                                                                 :     158    163 :     0.0779 : Y :     999    920 :   
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT SA                                               :     127    141 :     0.7313 : Y :    3697   3692 :   
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT EC                                               :     111    130 :     1.4979 : Y :    3733   3698 :   
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT SA                                                  :     102    124 :     2.1416 : Y :    2557   2541 :   
    TO BT BT BT BT BT SR SR BR SR BT BT BT BT BT SA                                                  :     102    114 :     0.6667 : Y :    1420   1388 :   
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT BT SA                                            :      94    110 :     1.2549 : Y :     818    780 :   
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT BT EC                                            :      90     91 :     0.0055 : Y :     815    824 :   
    TO BT BT AB                                                                                      :      88     74 :     1.2099 : Y :    2589    300 :   
    TO BT BT BT BT BR BT BT BT BT BT BT SA                                                           :      83     72 :     0.7806 : Y :    1124   1119 :   
    TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                     :      83     66 :     1.9396 : Y :      27     53 :   
    TO BT BT BT BT BT SR SR SR SA                                                                    :      69     81 :     0.9600 : Y :      46     69 :   
    TO BT BT BT BT BR BT BT BT BT BT BT BT BT EC                                                     :      75     75 :     0.0000 : Y :      17      7 :   
    TO BT BT BT BT BT SR BR SR BT BT BT BT BT AB                                                     :      68     71 :     0.0647 : Y :    9746   8998 :   
    TO BT AB                                                                                         :      70     64 :     0.2687 : Y :    9600   9585 :   
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                     :      64     69 :     0.1880 : Y :    4724   5907 :   
    TO BT BT BT BT BT SR BR BR SR SA                                                                 :      46     67 :     3.9027 : Y :    3740   3856 :   
    ]sseq_index_ab::desc
    </pre>


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc AZERO 
    ]sseq_index_ab::desc
    </pre>


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc BZERO 
    TO BT BT BT BT BT SR SR SR AB                                                                    :      17     -1 :     0.0000 : N :     489     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc
    </pre>


















Look for the coincidence in code
---------------------------------

::


    (ok) A[blyth@localhost opticks]$ jgr 20inch_veto
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            pmt_det_veto = sim_conf.tool("R12860OnlyFrontPMTManager/PMT_20inch_veto")
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det_veto = dynamic_cast<IPMTElement*>(det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      IDetElement* t = det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      IDetElement* mask = det_elem("R12860OnlyFrontMaskManager/mask_PMT_20inch_veto");
    (ok) A[blyth@localhost junosw]$ 

    2020         # == enable or disable PMTs in WP ==
    2021         if not args.pmt_optical_model:
    2022             pmt_det_veto = sim_conf.tool("R12860OnlyFrontPMTManager/PMT_20inch_veto")
    2023             pmt_det_veto.property("UsePMTOpticalModel").set(args.pmt_optical_model)



    1188 void LSExpDetectorConstruction::setupPMT(G4VSensitiveDetector* not_a_leak) {
    1189 
    ...
    1271   // Veto PMT
    1272   if (m_veto_pmt_name == "R12860OnlyFront") {
    1273       pmt_det_veto = dynamic_cast<IPMTElement*>(det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto"));
    1274       assert (pmt_det_veto);
    1275       auto lv = pmt_det_veto->getLV();
    1276       assert (lv);
    1277   } else if (m_veto_pmt_name == "R12860OnlyFrontMask") {
    1278       IDetElement* t = det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto");
    1279       IDetElement* mask = det_elem("R12860OnlyFrontMaskManager/mask_PMT_20inch_veto");
    1280       if (t && mask) {
    1281           // build
    1282           mask->getLV();
    1283           t->getLV();
    1284           pmt_det_veto = dynamic_cast<IPMTElement*>(mask);
    1285           pmt_det_veto->inject("lMaskVirtual", t, 0);
    1286       }
    1287 
    1288       assert(pmt_det_veto);
    1289   } else {
    1290       G4cerr << "Failed to find the VetoPMT named " << m_veto_pmt_name << G4endl;
    1291       assert (pmt_det_veto);
    1292   }


    BP=LSExpDetectorConstruction::setupPMT ipc

    (gdb) p m_pmt_name
    $1 = "PMTMask"
    (gdb) p m_extra_lpmt
    $2 = "TWO-mask"
    (gdb) p m_veto_pmt_name 
    $3 = "R12860OnlyFrontMask"
    (gdb) 


    jcv R12860OnlyFrontPMTManager
    jcv R12860OnlyFrontMaskManager



    153 void
    154 R12860OnlyFrontPMTManager::init_variables() {
    155     m_pmt_r = 254.*mm;
    156     m_pmt_h = 523.*mm;
    157     m_z_equator = 184.*mm; // From top to equator
    158 
    159     G4cout << __FILE__ << ":" << __LINE__ << std::endl;
    160     m_pmtsolid_maker = new R12860OnlyFront_PMTSolid(
    161                             m_pmt_r,
    162                             m_z_equator, // z front
    163                             -10.*mm       // z back (guess). NOTE: it should be nagative.
    164                             );
    165 }


    466 void
    467 R12860OnlyFrontPMTManager::init_cover() {
    468     // solid
    469     double thickness = 1E-3*mm;
    470     G4double zPlane[] = {
    471                         (m_z_equator-m_pmt_h)+thickness,
    472                         m_z_equator+thickness 
    473                         };
    474     G4double rInner[] = {0.,
    475                          0.};
    476     G4double rOuter[] = {m_pmt_r + thickness,
    477                          m_pmt_r + thickness};
    478 
    479     G4VSolid* cover_solid = new G4Polycone(
    480                                 GetName()+"Tubs",
    481                                 0,
    482                                 360*deg,
    483                                 2,
    484                                 zPlane,
    485                                 rInner,
    486                                 rOuter
    487                                 );
    488     // volume
    489     G4LogicalVolume* cover_lv = new G4LogicalVolume
    490         ( cover_solid,
    491           m_cover_mat,
    492           GetName()+"_cover");
    493     // place pmt into the cover
    494     G4ThreeVector noTranslation(0.,0.,0.);
    495     new G4PVPlacement
    496         (0,
    497          noTranslation,
    498          m_logical_pmt,
    499          GetName()+"_cover_phys",
    500          cover_lv,
    501          false,
    502          0
    503         );
    504     
    505     m_logical_pmt = cover_lv;



GEOM cf::

    298 mask_PMT_20inch_vetosMask
    301 mask_PMT_20inch_vetosMask_virtual

    299 PMT_20inch_veto_inner_solid_1_2
    300 PMT_20inch_veto_pmt_solid_1_2



    257 R12860OnlyFrontPMTManager::helper_make_solid()
    258 {
    259     if(m_UsePMTOpticalModel == false)
    260     {
    ...
    281     }
    282     else
    283     {
    284         pmt_solid = m_pmtsolid_maker->GetSolid(GetName() + "_pmt_solid", 1E-3*mm);
    285         inner_solid = m_pmtsolid_maker->GetSolid(GetName() + "_inner_solid", -5*mm);
    286     }
    287 

    153 void
    154 R12860OnlyFrontPMTManager::init_variables() {
    155     m_pmt_r = 254.*mm;
    156     m_pmt_h = 523.*mm;
    157     m_z_equator = 184.*mm; // From top to equator
    158 
    159     G4cout << __FILE__ << ":" << __LINE__ << std::endl;
    160     m_pmtsolid_maker = new R12860OnlyFront_PMTSolid(
    161                             m_pmt_r,
    162                             m_z_equator, // z front
    163                             -10.*mm       // z back (guess). NOTE: it should be nagative.
    164                             );
    165 }





BP=R12860OnlyFrontPMTManager::helper_make_solid ipc
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    (gdb) p m_UsePMTOpticalModel
    $1 = true

    (gdb) p this->GetName()
    $2 = {<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >> = "PMT_20inch_veto", <No data fields>}

    (gdb) p m_pmtsolid_maker
    $3 = (R12860OnlyFront_PMTSolid *) 0xac9f2a0

    (gdb) p m_fast_cover
    $4 = false





    013 #include <cmath>
     14 using namespace CLHEP;
     15 double R12860OnlyFront_PMTSolid::delta_torlerance = 1E-2*mm;
     16 
     17 R12860OnlyFront_PMTSolid::R12860OnlyFront_PMTSolid(
     18         double R1, double zfront, double zback)
     19     : m_R1(R1), m_zfront(zfront), m_zback(zback) {
     20     G4cout << __FILE__ << ":" << __LINE__ << std::endl;
     21 }
     22 
     23 G4VSolid*
     24 R12860OnlyFront_PMTSolid::GetSolid(G4String solidname, double thickness) {
     25     // Calculate Parameter first
     26     double r1t = m_R1 + thickness;
     27     double zft = m_zfront + thickness; // front
     28     double zbt = m_zback - thickness;  // back. Because m_zback<0
     29 
     30     // Show variables
     31     G4cout << "r1t: " << r1t/mm << " mm" << G4endl;
     32     G4cout << "zft: " << zft/mm << " mm" << G4endl;
     33     G4cout << "zbt: " << zbt/mm << " mm" << G4endl;
     34     // Construct the PMT Solid
     35     // * PART 1
     36     // G4Sphere* pmttube_solid_sphere = new G4Sphere(
     37     //                                         solidname+"_1_Sphere",
     38     //                                         0*mm, // R min
     39     //                                         r1t, // R max
     40     //                                         0*deg, // Start Phi
     41     //                                         360*deg, // Delta Phi
     42     //                                         0*deg, // Start Theta
     43     //                                         180*deg  // Delta Theta
     44     //                                         );
     45     G4Ellipsoid* pmttube_solid_sphere = new G4Ellipsoid(
     46                                             solidname+"_1_Front_Ellipsoid",
     47                                             r1t, // pxSemiAxis
     48                                             r1t, // pySemiAxis
     49                                             zft, // pzSemiAxis
     50                                             zbt, // cut at bottom
     51                                             zft  // cut at top
     52                                             );
     53     // * PART 2




HMM : virtual wrapper different from the mask ?
---------------------------------------------------


::

     22 R12860OnlyFrontMaskManager::R12860OnlyFrontMaskManager(const std::string& name)
     23     : ToolBase(name)
     24 {
     25     declProp("BufferMaterial", m_buffer_material = "Water");
     26     declProp("TopThickness", htop_thickness=8.*mm);
     27     declProp("TopGap", htop_gap=2.*mm); // gap between PMT and Mask at top
     28 
     29     declProp("EquatorThickness", requator_thickness=8.*mm); // thickness at equator
     30     declProp("EquatorGap", requator_gap=2.*mm); // gap between PMT and Mask at equator
     31 
     32     logicMaskVirtual = 0;
     33 
     34     MAGIC_virtual_thickness = 0.05*mm;
     35 }




Finding corners and apex with POINT
--------------------------------------


::

    GSGRID=1 PRIMTAB=1 GRID=1 GLOBAL=0 POINT=264.05,0,-24.9,264,0,-24.9,264.05,0,-25.05,-264.05,0,-24.9,-264,0,-24.9,-264.05,0,-25.05,0,0,184,0,0,186,0,0,194,0,0,194.05 POINTSIZE=20 cxt_min.sh pdb


    In [3]: p = np.fromstring("264.05,0,-24.9,264,0,-24.9,264.05,0,-25.05,-264.05,0,-24.9,-264,0,-24.9,-264.05,0,-25.05,0,0,184,0,0,186,0,0,194,0,0,194.05",sep=",").reshape(-1,3)

    In [4]: p
    Out[4]: 
    array([[ 264.05,    0.  ,  -24.9 ],
           [ 264.  ,    0.  ,  -24.9 ],
           [ 264.05,    0.  ,  -25.05],
           [-264.05,    0.  ,  -24.9 ],
           [-264.  ,    0.  ,  -24.9 ],
           [-264.05,    0.  ,  -25.05],
           [   0.  ,    0.  ,  184.  ],
           [   0.  ,    0.  ,  186.  ],
           [   0.  ,    0.  ,  194.  ],
           [   0.  ,    0.  ,  194.05]])



Clearance of 0.050 is not enough, need twice that: 0.100



Follow the pattern
------------------


::

     43    export WaterPoolConstruction__CONFIG=3                        # HIERARCHY
     44    export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10            # default 1.e-3
     45    export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10  # default 0.05
     46    export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10       # default 0.05


blyth-add-envvar-control-R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM
--------------------------------------------------------------------------------------

::

    (ok) A[blyth@localhost junosw]$ js
    /home/blyth/junosw
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw.git (fetch)
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw.git (push)
    On branch blyth-add-envvar-control-R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM
    Your branch is up to date with 'origin/blyth-add-envvar-control-R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Examples/Tutorial/share/opticks_juno.sh
        modified:   Simulation/DetSimV2/PMTSim/include/R12860OnlyFrontMaskManager.hh
        modified:   Simulation/DetSimV2/PMTSim/src/R12860OnlyFrontMaskManager.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    (ok) A[blyth@localhost junosw]$ 














