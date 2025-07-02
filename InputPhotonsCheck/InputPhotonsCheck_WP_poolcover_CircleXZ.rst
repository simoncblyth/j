InputPhotonsCheck_WP_poolcover_CircleXZ
==========================================


ipcv::

    188     elif [ "$TEST" == "POOLCOVER" ]; then
    189 
    190       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    191       #opticks_input_photon=UpXZ1000_f8.npy
    192       opticks_input_photon=CircleXZ_R500_100k_f8.npy
    193       #opticks_input_photon=CircleXZ_R10_361_f8.npy
    194       #opticks_input_photon_frame=3345.569,20623.73,21500
    195       opticks_input_photon_frame=3345.569,20623.73,21000
    196       #export PIDX=99999
    197 

ipc env_chi2::

    [sseq_index_test.cc
    a_path $AFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/A000/seq.npy a_seq (100000, 2, 2, )
    b_path $BFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/B000/seq.npy b_seq (100000, 2, 2, )
    sseq_index_test__DEBUG:0
     t0 1751455593420587
     t1 1751455593427498 (t1 - t0)     6911 0.006911
     t2 1751455593437784 (t2 - t1)    10286 0.010286
     t3 1751455593437853 (t3 - t2)       69 0.000069
    AB
    [sseq_index_ab::desc u_size 104 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum  1923.0197 ndf 12.0000 sum/ndf   160.2516 sseq_index_ab_chi2_ABSUM_MIN:40.0000
    :r:`TO BT SA                                                                                         :   38156  44430 :   476.6313 : Y :    3160   3160 : DEVIANT  `
        TO SA                                                                                            :   39084  39241 :     0.3147 : Y :       0      0 :   
    :r:`TO AB                                                                                            :   17552  13928 :   417.1975 : Y :       1     40 : DEVIANT  `
        TO BR SA                                                                                         :    3607     -1 :     0.0000 : N :    3163     -1 : BZERO C2EXC  
    :r:`TO BT AB                                                                                         :      97   1250 :   986.9406 : Y :    3833   3202 : DEVIANT  `
        TO BR AB                                                                                         :     662     -1 :     0.0000 : N :    4203     -1 : BZERO C2EXC  
        TO BT BR SA                                                                                      :      -1    317 :     0.0000 : N :      -1   3303 : AZERO C2EXC  
        TO BT BT BT BT EC                                                                                :      96    145 :     9.9627 : Y :   71553  71574 :   
        TO BT BT BT BT SA                                                                                :     112    129 :     1.1992 : Y :   71372  71556 :   
        TO BT BT AB                                                                                      :     125    104 :     1.9258 : Y :   71358  71346 :   
        TO BT BT BT AB                                                                                   :      86    117 :     4.7340 : Y :   71362  71368 :   
        TO BT BT BT BT AB                                                                                :      79     64 :     1.5734 : Y :   71432  71432 :   
        TO BT BT BT BT BT AB                                                                             :      41     71 :     8.0357 : Y :   71434  71434 :   
        TO BT BT BT BT BT SA                                                                             :      55     -1 :     0.0000 : N :   71448     -1 : BZERO C2EXC  
    :r:`TO BT BT BT BT BR BT BT BT BT SA                                                                 :      20     51 :    13.5352 : Y :   71583  71566 : DEVIANT  `
        TO BT BT BT BT BT EC                                                                             :      38     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
        TO BT BT BR BT BT SA                                                                             :      29     37 :     0.9697 : Y :   71537  71538 :   
        TO BT BT BT SA                                                                                   :      16      2 :     0.0000 : N :   71352  71365 : C2EXC  
        TO BT BT BT BR BT BT BT SA                                                                       :      10     12 :     0.0000 : N :   71561  71571 : C2EXC  
        TO BT BR BT SA                                                                                   :      12     12 :     0.0000 : N :   71532  71557 : C2EXC  
        TO BT BT BT BT BR BT BT SA                                                                       :       7     10 :     0.0000 : N :   71824  71825 : C2EXC  
        TO BT BT BT BT EX                                                                                :       5      9 :     0.0000 : N :   71609  71903 : C2EXC  
        TO BT BT BT BT BT BR BT BT BT BT SA                                                              :       9     -1 :     0.0000 : N :   71575     -1 : C2EXC  
        TO BT BT SA                                                                                      :       4      9 :     0.0000 : N :   71342  71343 : C2EXC  
        TO BT BT BT BR BT BT SA                                                                          :       7     -1 :     0.0000 : N :   71566     -1 : C2EXC  
        TO BT BT BT BR BT SA                                                                             :       7      4 :     0.0000 : N :   71823  71822 : C2EXC  
        TO BT BT BT BT BT BT SA                                                                          :       6      7 :     0.0000 : N :   71509  71548 : C2EXC  
        TO BT BT BR BT SA                                                                                :       6     -1 :     0.0000 : N :   71755     -1 : C2EXC  
        TO BT BT BT BT BT BR BT BT SA                                                                    :       6     -1 :     0.0000 : N :   71826     -1 : C2EXC  
        TO BT BT BR BT BT AB                                                                             :       2      6 :     0.0000 : N :   71753  71755 : C2EXC  
        TO BT BT BT BT BT BT EC                                                                          :       3      5 :     0.0000 : N :   73281  73280 : C2EXC  
        TO BT BT BT BT BR BR BR BT BT SA                                                                 :       1      4 :     0.0000 : N :   71834  71826 : C2EXC  
        TO BT BT BT BT BR BT BR BT SA                                                                    :       4     -1 :     0.0000 : N :   71638     -1 : C2EXC  
        TO BT BT BT BT BR BT BT BT SA                                                                    :       4     -1 :     0.0000 : N :   71732     -1 : C2EXC  
        TO BT BT BR BR BR BT BT SA                                                                       :       1      3 :     0.0000 : N :   71538  71759 : C2EXC  
        TO BT BT BT BT BT BR BT BT BT SA                                                                 :       2      2 :     0.0000 : N :   73277  73292 : C2EXC  
        TO BT BT BT BT BT BT BT SA                                                                       :       2     -1 :     0.0000 : N :   73278     -1 : C2EXC  
        TO BT BT BT BT BT BT BT EC                                                                       :       2     -1 :     0.0000 : N :   73282     -1 : C2EXC  
        TO BT BT BT BR BR BR BT BT AB                                                                    :       2     -1 :     0.0000 : N :   72044     -1 : C2EXC  
        TO BT BT BR BR BR BR BR BT BT BT BT BT BT EC                                                     :      -1      2 :     0.0000 : N :      -1  72051 : C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 104 NUM_MAX 40 num 104 opt AZERO mode 1
        TO BT BR SA                                                                                      :      -1    317 :     0.0000 : N :      -1   3303 : AZERO C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 104 NUM_MAX 40 num 104 opt BZERO mode 2
        TO BR SA                                                                                         :    3607     -1 :     0.0000 : N :    3163     -1 : BZERO C2EXC  
        TO BR AB                                                                                         :     662     -1 :     0.0000 : N :    4203     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SA                                                                             :      55     -1 :     0.0000 : N :   71448     -1 : BZERO C2EXC  
        TO BT BT BT BT BT EC                                                                             :      38     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 104 NUM_MAX 40 num 104 opt DEVIANT mode 5
    :r:`TO BT SA                                                                                         :   38156  44430 :   476.6313 : Y :    3160   3160 : DEVIANT  `
    :r:`TO AB                                                                                            :   17552  13928 :   417.1975 : Y :       1     40 : DEVIANT  `
    :r:`TO BT AB                                                                                         :      97   1250 :   986.9406 : Y :    3833   3202 : DEVIANT  `
    :r:`TO BT BT BT BT BR BT BT BT BT SA                                                                 :      20     51 :    13.5352 : Y :   71583  71566 : DEVIANT  `
    ]sseq_index_ab::desc

    ]sseq_index_test.cc
    pvplt MODE:2 



EVT::

     58     elif [ "$check" == "poolcover_ipc" ]; then
     59 
     60         export AFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/A000
     61         export BFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/B000




alt-A alt-B alt-T alt-M examine the record animation with ssst.sh
-------------------------------------------------------------------

B side has no immediate BR reflection, A side does that lots : but apex hole.

EVT::

     58     elif [ "$check" == "poolcover_ipc" ]; then
     59 
     60         export AFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/A000
     61         export BFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/B000
     62 
     63         export AFOLD_RECORD_SLICE="TO BR SA"



ipc env_pdb::

    In [14]: a.f.record[w,:3,3,0].view(np.uint32) >> 16
    Out[14]: 
    array([[ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           ...,
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25]], shape=(3607, 3), dtype=uint32)



    In [15]: w = a.q_startswith("TO BR SA") ; w
    Out[15]: array([ 3163,  3165,  3168,  3170,  3171, ..., 48936, 48939, 48951, 48954, 48956], shape=(3607,))



    In [18]: np.unique( a.f.record[w,1,3,0].view(np.uint32) >> 16, return_counts=True )
    Out[18]: (array([24], dtype=uint32), array([3607]))

    In [19]: np.unique( a.f.record[w,2,3,0].view(np.uint32) >> 16, return_counts=True )
    Out[19]: (array([25], dtype=uint32), array([3607]))


HMM those boundaries look the wrong way around::

    In [20]: cf.sim.stree.standard.bd_names[24]
    Out[20]: np.str_('DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek')

    In [21]: cf.sim.stree.standard.bd_names[25]
    Out[21]: np.str_('Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater')

    In [23]: cf.sim.stree.standard.bd_names[23]
    Out[23]: np.str_('Air///DeadWater')

    In [24]: cf.sim.stree.standard.bd_names[26]
    Out[24]: np.str_('vetoWater/Implicit_RINDEX_NoRINDEX_pWaterPool_GZ1.A01_02_HBeam_phys//LatticedShellSteel')



BP=WaterPoolConstruction::makeWPLogical_hierarchy ipc
---------------------------------------------------------

jcv WaterPoolConstruction2::

   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+
   |  solid             |    z0                                                       |      z1                                                     |     r                                                |   
   +====================+=============================================================+=============================================================+======================================================+
   |  sAirGap           |   -m_heightWP/2                                             |    m_heightWP/2 + m_airGapThickness                         |   m_radWP    *COIN*                                  |   
   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+
   |  sDeadWater_shell  |   -m_heightWP/2                                             |    m_heightWP/2                                             |   m_radWP    *COIN*                                  |   
   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+
   |  sTyvek_shell      |   -m_heightWP/2 + m_deadWaterThickness - m_tyvekThickness   |    m_heightWP/2 - m_deadWaterThickness +  m_tyvekThickness  |   m_radWP - m_deadWaterThickness + m_tyvekThickness  |
   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+
   |  sOuterWaterPool   |   -m_heightWP/2                                             |    m_heightWP/2                                             |   m_radWP - m_deadWaterThickness                     |   
   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+


::

    (gdb) p m_heightWP
    $1 = 43500
    (gdb) p m_heightWP/2
    $2 = 21750
    (gdb) p m_airGapThickness
    $3 = 500
    (gdb) p m_radWP
    $4 = 21750
    (gdb) p m_deadWaterThickness
    $5 = 100
    (gdb) p m_tyvekThickness
    $6 = 2
    (gdb) 
  

                                                                                                                    + m_radWP - m_deadWaterThickness
                                                                                                                    : 
                                                                                                                    :
                                                                                                                    : + m_radWP - m_deadWaterThickness + m_tyvekThickness
                                                                                                                    : :
                                                                                                                    : :   + m_radWP
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                    0                                               : :   :
               +-----------Air--------------------------------------|-----------------------------------------------:-:---+     m_heightWP/2 + m_airGapThickness
               |                                                    |                                               : :   |
               |                                                    |                                               : :   |
               |                                                    |                                               : :   |
               |                                                    |                                               : :   |
               |                                                    |                                               : :   |
               +---------DeadWater----------------------------------|-----------------------------------------------:-:---+     m_heightWP/2
               |                                                    |                                               : :   |    
               |   +------Tyvek-------------------------------------|-----------------Tyvek-------------------------:-+   |     m_heightWP/2 - m_deadWaterThickness + m_tyvekThickness 
               |   | +-------vetoWater------------------------------|-----------------------------------------------+ |   |     m_heightWP/2 - m_deadWaterThickness  (TOFIX)
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |   
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | +------vetoWater-------------------------------|------------------vetoWater--------------------+ |   |    -m_heightWP/2 + m_deadWaterThickness - m_tyvekThickness
               |   +-----Tyvek--------------------------------------|-------------------------------------------------+   |    -m_heightWP/2 + m_deadWaterThickness (TOFIX)
               |                                                    |                                                     |    
               +---------DeadWater----------------------------------|-----------------------------------------------------+    -m_heightWP/2
                                                                    0 

Expect Air DeadWater coincidence should not matter as stopped at Tyv.


