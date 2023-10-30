opticksMode3-3rd-wave-contents-comparison
============================================

Context
--------

* Previous :doc:`opticksMode3-2nd-wave-contents-comparison`

Overview
-----------

* workstation needs to run the SAB so can see status without so many rsyncs 

* HMM flipping between geometries is time consuming due to the rsyncs "GEOM get" 
  maybe adopt different GEOM names for the OSUR switcn ?


Summary understanding of the OSUR implicit scrambled boundary issue
----------------------------------------------------------------------

The steel tube of the 3inch PMT needs OSUR implicits (from no RINDEX in the Steel)
to match Geant4, as shown by standalone G4CXTest.sh running.
Without this bounce back photons from LPMT enter the SPMT from the back. 

However on enabling OSUR implicits in U4Tree/U4TreeBorder find that the 
border indices used in the CSGNode get out of whack with the bnd array 
with the surface properties.  The result of this is that all photons 
get "TO SA" absorbed at the first boundary. The effect is kinda random
because it is using a border index to lookup the wrong mat/sur properties. 

The reason for the shear is that the OSUR implicits are enabled 
only for the new workflow (in U4Tree/U4TreeBorder) 
and not for the old in X4PhysicalVolume::convertImplicitSurfaces_r

There are two possible ways to fix this

1. implement OSUR implicits in the old workflow within X4PhysicalVolume::convertImplicitSurfaces_r
2. drop the old workflow X4/GGeo/.. by leaping to using CSGFoundry::CreateFromSim 
   which does CSGFoundry::importSim using SSim+stree imputs

   * DID THIS : DROPPING THE OLD WORKFLOW
    
While the first is easier in the shortterm it is not the best in the longterm.
As really need to drop the old code to avoid similar such problems in future. 


Investigate Longterm Solution
-------------------------------

CSG/tests/CSGFoundry_CreateFromSimTest.sh
     loads SSim from BASE such as $HOME/.opticks/GEOM/$GEOM/CSGFoundry
     and creates a CSGFoundry from that 
     then runs a comparison 

All discrep coming from two G4VSolid::

    len(np.where(a.prim[:,0]!=b.prim[:,0])[0])                                       : 776
    #numNode                                                                         : 
    len(np.where(a.prim[:,0,0].view(np.int32)!=b.prim[:,0,0].view(np.int32))[0])     : 9
    len(w_numNode)                                                                   : 9
    np.c_[np.unique(a.primname[w_numNode],return_counts=True)]                       
    [['solidSJReceiverFastern' 8]
     ['uni1' 1]]



::

    ~/opticks/CSG/tests/CSGFoundry_CreateFromSimTest.sh
    ...


    # A : (numNode,nodeOffset,tranOffset,planOffset) where prim_numNode discrepant   : 
    a.prim[ab.prim_numNode,0].view(np.int32)                                         
    [[   15 15209  6672     0]
     [   15 15224  6680     0]
     [   15 15239  6688     0]
     [   15 15254  6696     0]
     [   15 15269  6704     0]
     [   15 15284  6712     0]
     [   15 15299  6720     0]
     [   15 15314  6728     0]
     [   31 16082  7410     0]]

    # B : (numNode,nodeOffset,tranOffset,planOffset) where prim_numNode discrepant   : 
    b.prim[ab.prim_numNode,0].view(np.int32)                                         
    [[  127 15209  6672     0]
     [  127 15336  6680     0]
     [  127 15463  6688     0]
     [  127 15590  6696     0]
     [  127 15717  6704     0]
     [  127 15844  6712     0]
     [  127 15971  6720     0]
     [  127 16098  6728     0]
     [ 1023 16978  7410     0]]


    In [1]: 127*8+1023
    Out[1]: 2039

    In [2]: 15*8+31
    Out[2]: 151

    In [3]: 2039-151
    Out[3]: 1888


    In [7]: b.node.shape[0]
    Out[7]: 18145

    In [8]: a.node.shape[0]
    Out[8]: 16257

    In [9]: b.node.shape[0] - a.node.shape[0]
    Out[9]: 1888


solidSJReceiverFastern : SJReceiverFasternConstruction : NEED TO --debug-disable-sj
--------------------------------------------------------------------------------------

::

    epsilon:junosw blyth$ jgl solidSJReceiverFastern
    ./Simulation/DetSimV2/CentralDetector/include/SJReceiverFasternConstruction.hh
    ./Simulation/DetSimV2/CentralDetector/src/SJReceiverFasternConstruction.cc

Where is it used::

    BP=SJReceiverFasternConstruction::getLV ntds3_noxj


    (gdb) bt
    #0  SJReceiverFasternConstruction::getLV (this=0x5bcf0c0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/SJReceiverFasternConstruction.cc:32
    #1  0x00007fffcd7ce1ef in DetSim1Construction::inject (this=0xb2dd50, motherName=..., other=0x5bcf0c0, pos=0x5bcf350)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:123
    #2  0x00007fffcde36ad4 in LSExpDetectorConstruction::setupAnchor (this=0x580cfa0, anchor_name=..., anchor_mother_name=..., 
        anchor_pos_file=..., cd_det=0xb2dd50)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1444
    #3  0x00007fffcde3657d in LSExpDetectorConstruction::setupCD_Sticks (this=0x580cfa0, cd_det=0xb2dd50)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1427
    #4  0x00007fffcde2e84e in LSExpDetectorConstruction::setupCentralDetector (this=0x580cfa0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:576
    #5  0x00007fffcde2d43f in LSExpDetectorConstruction::Construct (this=0x580cfa0)

    (gdb) f 3
    #3  0x00007fffcde3657d in LSExpDetectorConstruction::setupCD_Sticks (this=0x580cfa0, cd_det=0xb2dd50)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1427
    1427	      setupAnchor(m_sjreceiver_fastener_name , m_sjreceiver_fastener_mother, m_sjreceiver_pos_file , cd_det);
    (gdb) p m_sjreceiver_fastener_name
    $1 = {static npos = 18446744073709551615, 
      _M_dataplus = {<std::allocator<char>> = {<__gnu_cxx::new_allocator<char>> = {<No data fields>}, <No data fields>}, 
        _M_p = 0x580da00 "SJReceiverFastern"}, _M_string_length = 17, {_M_local_buf = "\036", '\000' <repeats 14 times>, 
        _M_allocated_capacity = 30}}
    (gdb) p  m_sjreceiver_fastener_mother
    $2 = {static npos = 18446744073709551615, 
      _M_dataplus = {<std::allocator<char>> = {<__gnu_cxx::new_allocator<char>> = {<No data fields>}, <No data fields>}, 
        _M_p = 0x580d8d0 "lTarget"}, _M_string_length = 7, {_M_local_buf = "lTarget\000\000\000\000\000\000\000\000", 
        _M_allocated_capacity = 32762592273454188}}
    (gdb) 


::

    1403   bool DEBUG_DISABLE_XJ = getenv("JUNO_DEBUG_DISABLE_XJ") == nullptr ? false : true ;
    1404   if(DEBUG_DISABLE_XJ)
    1405   {   
    1406       G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-xj " << G4endl ;
    1407   }
    1408   else
    1409   {   
    1410       // XJ
    1411       setupAnchor(m_xjanchor_name  , m_xjanchor_mother , m_xjanchor_pos_file,cd_det);
    1412       setupAnchor(m_xjfixture_name , m_xjfixture_mother , m_xjanchor_pos_file,cd_det);
    1413   }
    1414 
    1415 
    1416   bool DEBUG_DISABLE_SJ = getenv("JUNO_DEBUG_DISABLE_SJ") == nullptr ? false : true ;
    1417   if(DEBUG_DISABLE_SJ)
    1418   {
    1419       G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-sj " << G4endl ;
    1420   }
    1421   else
    1422   {
    1423       // SJ
    1424       setupAnchor(m_sjclsanchor_name , m_sjclsanchor_mother,  m_sjclsanchor_pos_file, cd_det);
    1425       setupAnchor(m_sjfixture_name , m_sjfixture_mother, m_sjfixture_pos_file, cd_det);
    1426       setupAnchor(m_sjreceiver_name , m_sjreceiver_mother, m_sjreceiver_pos_file, cd_det);
    1427       setupAnchor(m_sjreceiver_fastener_name , m_sjreceiver_fastener_mother, m_sjreceiver_pos_file , cd_det);
    1428   }




uni1 : FastenerAcrylicConstruction
-------------------------------------

::

    epsilon:junosw blyth$ jgl uni1
    ./Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc
    ## this is it, the Greek temple 

    ## uni1 not a solid name in the below 
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc
    ./Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc         
    ./Simulation/DetSimV2/CentralDetector/include/SJReceiverFasternConstruction.hh
    ./Simulation/DetSimV2/CentralDetector/src/SJReceiverFasternConstruction.cc
    epsilon:junosw blyth$ 


Where is it used::

    BP=FastenerAcrylicConstruction::getLV ntds3_noxj

::

    (gdb) bt
    #0  FastenerAcrylicConstruction::getLV (this=0x5b10f50)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc:33
    #1  0x00007fffcd7ce1ef in DetSim1Construction::inject (this=0xb2dd40, motherName=..., other=0x5b10f50, pos=0x5aa41c0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:123
    #2  0x00007fffcde36ad4 in LSExpDetectorConstruction::setupAnchor (this=0x580cf70, anchor_name=..., anchor_mother_name=..., 
        anchor_pos_file=..., cd_det=0xb2dd40)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1444
    #3  0x00007fffcde35e7d in LSExpDetectorConstruction::setupCD_Sticks (this=0x580cf70, cd_det=0xb2dd40)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1382
    #4  0x00007fffcde2e84e in LSExpDetectorConstruction::setupCentralDetector (this=0x580cf70)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:576
    #5  0x00007fffcde2d43f in LSExpDetectorConstruction::Construct (this=0x580cf70)

    (gdb) f 4
    #4  0x00007fffcde2e84e in LSExpDetectorConstruction::setupCentralDetector (this=0x580cf70)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:576
    576	      setupCD_Sticks(cd_det);
    (gdb) f 3
    #3  0x00007fffcde35e7d in LSExpDetectorConstruction::setupCD_Sticks (this=0x580cf70, cd_det=0xb2dd40)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1382
    1382	     setupAnchor(m_fastener_name , m_fastener_mother , m_fastener_pos_file , cd_det);    
    (gdb) p m_fastener_name.c_str()
    $1 = 0x580d500 "FastenerAcrylic"
    (gdb) p m_fastener_mother.c_str()
    $2 = 0x580d520 "lWaterPool"
    (gdb) p m_fastener_pos_file.c_str()
    $3 = 0x580dac0 "/data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv"
    (gdb) 


ADDED THIS::

    1381   bool DEBUG_DISABLE_FA = getenv("JUNO_DEBUG_DISABLE_FA") == nullptr ? false : true ;
    1382   if(DEBUG_DISABLE_FA)
    1383   {
    1384       G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-fa " << G4endl ;
    1385   }   
    1386   else
    1387   { 
    1388       if (m_fastener_name == "FastenerAcrylic") {
    1389          setupAnchor(m_fastener_name , m_fastener_mother , m_fastener_pos_file , cd_det);
    1390       } else if (m_fastener_name == "FastenerBalloon") { 
    1391           // no fastener in Balloon Option
    1392       }   
    1393   }   




FIXED : inst[:,2,3].view(np.int32) off-by-one
-----------------------------------------------

* snode::sensor_id -1 signifies not-a-sensor 
  which gets passes unchanged into inst for B 

* where is the sensor_id +1 done in the A workflow ? 

  * CSGFoundry::addInstance hence do that also in CSGFoundry::addInstanceVector


::

    453 extern "C" __global__ void __closesthit__ch()
    454 {   
    455     unsigned iindex = optixGetInstanceIndex() ;    // 0-based index within IAS
    456     unsigned instance_id = optixGetInstanceId() ;  // user supplied instanceId, see IAS_Builder::Build 
    457     unsigned prim_idx = optixGetPrimitiveIndex() ; // GAS_Builder::MakeCustomPrimitivesBI_11N  (1+index-of-CSGPrim within CSGSolid/GAS)
    458     
    459     //unsigned identity = (( prim_idx & 0xffff ) << 16 ) | ( instance_id & 0xffff ) ; 
    460     unsigned identity = instance_id ;  // CHANGED July 2023, as now carrying sensor_identifier, see sysrap/sqat4.h 
    461 


    366     QAT4_METHOD int get_IAS_OptixInstance_instanceId() const
    367     {
    368         //const unsigned& ins_idx = q0.u.w ;  
    369         //return ins_idx ; 
    370         const int& sensor_identifier = q2.i.w ;
    371         assert( sensor_identifier >= 0 );  // 0 means not a sensor GPU side, so subtract 1 to get actual sensorId
    372         return sensor_identifier ;
    373     }


    049 void IAS_Builder::CollectInstances(std::vector<OptixInstance>& instances, const std::vector<qat4>& ias_inst, const SBT* sbt ) // static 
     50 {
     51     unsigned num_ias_inst = ias_inst.size() ;
     52     unsigned flags = OPTIX_INSTANCE_FLAG_DISABLE_ANYHIT ;
     53     unsigned prim_idx = 0u ;  // need sbt offset for the outer prim(aka layer) of the GAS 
     54 
     55     std::map<unsigned, unsigned> gasIdx_sbtOffset ;
     56 
     57     for(unsigned i=0 ; i < num_ias_inst ; i++)
     58     {
     59         const qat4& q = ias_inst[i] ;
     60         int ins_idx,  gasIdx, sensor_identifier, sensor_index ;
     61         q.getIdentity(ins_idx, gasIdx, sensor_identifier, sensor_index );
     62         unsigned instanceId = q.get_IAS_OptixInstance_instanceId() ;
     ..
     87         OptixInstance instance = {} ;
     88         q.copy_columns_3x4( instance.transform );
     89         instance.instanceId = instanceId ;
     90         instance.sbtOffset = sbtOffset ;

    375     /**
    376     sqat4::setIdentity
    377     -------------------
    378 
    379     Canonical usage from CSGFoundry::addInstance  where sensor_identifier gets +1 
    380     with 0 meaning not a sensor. 
    381     **/
    382 
    383     QAT4_METHOD void setIdentity(int ins_idx, int gas_idx, int sensor_identifier_1, int sensor_index )
    384     {
    385         assert( sensor_identifier_1 >= 0 );
    386 
    387         q0.i.w = ins_idx ;             // formerly unsigned and "+ 1"
    388         q1.i.w = gas_idx ;
    389         q2.i.w = sensor_identifier_1 ;   // now +1 with 0 meaning not-a-sensor 
    390         q3.i.w = sensor_index ;
    391     }








::

    In [1]: a.inst[:,2,3].view(np.int32)
    Out[1]: array([     0, 300001, 300002, 300003, 300004, ...,      0,      0,      0,      0,      0], dtype=int32)

    In [2]: b.inst[:,2,3].view(np.int32)
    Out[2]: array([    -1, 300000, 300001, 300002, 300003, ...,     -1,     -1,     -1,     -1,     -1], dtype=int32)

    In [3]: np.all( b.inst[:,2,3].view(np.int32) + 1 == a.inst[:,2,3].view(np.int32) )
    Out[3]: True

    In [5]: a.base
    Out[5]: '/Users/blyth/.opticks/GEOM/V1J009'

    In [6]: b.base
    Out[6]: '/tmp/blyth/opticks/CSGFoundry_CreateFromSimTest'

::

    2811 inline void stree::add_inst(
    2812     glm::tmat4x4<double>& tr_m2w,  
    2813     glm::tmat4x4<double>& tr_w2m,
    2814     int gas_idx, 
    2815     int nidx )
    2816 {
    2817     assert( nidx > -1 && nidx < int(nds.size()) );
    2818     const snode& nd = nds[nidx];    // structural volume node
    2819 
    2820     int ins_idx = int(inst.size()); // follow sqat4.h::setIdentity
    2821     
    2822     glm::tvec4<int64_t> col3 ;   // formerly uint64_t 
    2823     
    2824     col3.x = ins_idx ;            // formerly  +1 
    2825     col3.y = gas_idx ;            // formerly  +1 
    2826     col3.z = nd.sensor_id ;       // formerly ias_idx + 1 (which was always 1)
    2827     col3.w = nd.sensor_index ;
    2828     
    2829     strid::Encode(tr_m2w, col3 );   
    2830     strid::Encode(tr_w2m, col3 );
    2831     
    2832     inst.push_back(tr_m2w);




How to proceed to investigate the OSUR issue ?
------------------------------------------------

Need to reproduce it standalone for the fast cycle ... 

* so G4CXTest with FewPMT adjusted to include the mask and virtualMask 
* added FewPMT/nmskLogicMaskVirtual

::

    jcv HamamatsuMaskManager
    jcv NNVTMaskManager

::

      3495     <volume name="HamamatsuR12860lMaskVirtual0x61b1910">
      ...
      3561     <volume name="NNVTMCPPMTlMaskVirtual0x61c2ef0">
      ...


* standalone fails to reproduce the issue, and has some of its own 

::

    In [1]: boundary___(a.f.record) 
    Out[1]: 
    array([[0, 2, 3, 3, 3, ..., 0, 0, 0, 0, 0],
           [0, 2, 3, 2, 1, ..., 0, 0, 0, 0, 0],
           [0, 2, 3, 3, 3, ..., 0, 0, 0, 0, 0],
           [0, 2, 3, 3, 3, ..., 0, 0, 0, 0, 0],
           [0, 2, 3, 3, 3, ..., 0, 0, 0, 0, 0],
           ...,
           [0, 2, 3, 3, 3, ..., 0, 0, 0, 0, 0],
           [0, 2, 3, 3, 3, ..., 0, 0, 0, 0, 0],
           [0, 2, 3, 3, 3, ..., 0, 0, 0, 0, 0],
           [0, 2, 3, 3, 3, ..., 0, 0, 0, 0, 0],
           [0, 2, 3, 3, 3, ..., 0, 0, 0, 0, 0]], dtype=uint32)

    In [2]: cf.sim.bndnamedict
    Out[2]: 
    {0: 'Rock///Rock',
     1: 'Rock//water_rock_bs/Water',
     2: 'Water///Water',
     3: 'Water///AcrylicMask',
     4: 'Water/NNVTMaskOpticalSurface//CDReflectorSteel'}




Insitu Comparison Workflow
-----------------------------

After Opticks updates::

    ~/opticks/bin/rsync_put.sh    # laptop
    o ; oo                        # workstation  


After JSW updates::

    jo
    ./build_Debug.sh    ## when change C4 directories, needs fully clean rebuild


config, run, pullback, ana, repeat::

    jxv               # laptop, for example change "ntds" ipho stats to 10k 
    jxscp             # laptop, scp jx.bash to remote 

    jxf               # workstation, pick up updated jx.bash functions 
    ntds3_noxj        # workstation, run opticksMode:3 doing both optical simulations in one invokation
    jxf ; ntds3_noxj  # workstation : generally need to do both 


    GEOM              # check the GEOM setting is eg V1J009 for current full geom (not FewPMT for standalone geom)
    GEOM tmpget       # laptop, pullback the paired SEvt 
    jxn               # laptop, cd to /Users/blyth/j/ntds
    ./ntds3.sh        # laptop, run analysis ntds3.py loading two SEvt into ipython for comparison, plotting


With solids needing balancing removed::

    ntds3_noxjsjfa    # workstation

    GEOM              # check the GEOM configured matches that being written on workstation
    GEOM get          # laptop





OOPS : almost all A:"TO SA" at the virtual mask after enabling U4Tree osur
----------------------------------------------------------------------------

Confirmed that U4Tree__DISABLE_OSUR_IMPLICIT returns to old behaviour::

     678 ntds_noxj()
     679 {
     680    #local gpfx=R           # R:Release builds of junosw+custom4   
     681    local gpfx=V          # V:Debug builds of junosw+custom4  
     682    GPFX=${GPFX:-$gpfx}    # need to match with j/ntds/ntds.sh  AGEOM, BGEOM
     683 
     684    export EVTMAX=1
     685 
     686    export U4Tree__DISABLE_OSUR_IMPLICIT=1
     687 
     688 
     689    NOXJ=1 GEOM=${GPFX}1J009 OPTICKS_INTEGRATION_MODE=${OPTICKS_INTEGRATION_MODE:-0} ntds
     690 
     691    ## HMM: INPUT PHOTONS WILL NOT WORK IN OPTICKS MODE 0 HOW AND WHERE TO RAISE AN ERROR FOR THAT ?
     692 }


::

    In [5]: boundary___(a.f.record)
    Out[5]: 
    array([[ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0],
           [ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0],
           [ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0],
           [ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0],
           [ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0],
           ...,
           [ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0],
           [ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0],
           [ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0],
           [ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0],
           [ 0, 26,  0,  0,  0, ...,  0,  0,  0,  0,  0]], dtype=uint32)

HUH 26 makes no sense:: 

    In [1]: cf.sim.bndnamedict                                                                                                                                                  
    Out[1]: 
    {0: 'Galactic///Galactic',
     1: 'Galactic///Rock',
     2: 'Rock///Galactic',
     3: 'Rock//Implicit_RINDEX_NoRINDEX_pDomeAir_pDomeRock/Air',
     4: 'Rock///Rock',
    ...

     21: 'Air/Implicit_RINDEX_NoRINDEX_pPlane_1_ff__pPanel_3_f_//Aluminium',
     22: 'Rock///Tyvek',
     23: 'Tyvek//VETOTyvekSurface/vetoWater',
     24: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up10_up11_HBeam_phys//LatticedShellSteel',
     25: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up09_up10_HBeam_phys//LatticedShellSteel',
     26: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up08_up09_HBeam_phys//LatticedShellSteel',
     27: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up07_up08_HBeam_phys//LatticedShellSteel',
     28: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up06_up07_HBeam_phys//LatticedShellSteel',
     29: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up05_up06_HBeam_phys//LatticedShellSteel',
     30: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up04_up05_HBeam_phys//LatticedShellSteel',


::

    In [9]: a.f.record[0,:2]
    Out[9]:
    array([[[-12052.896,   9510.562,  11538.329,      0.1  ],
            [    -0.621,      0.49 ,      0.611,      1.   ],
            [    -0.619,     -0.785,      0.   ,    440.   ],
            [     0.   ,      0.   ,      0.   ,      0.   ]],

           [[-12127.06 ,   9569.081,  11611.27 ,      0.65 ],
            [    -0.621,      0.49 ,      0.611,      0.   ],
            [    -0.619,     -0.785,      0.   ,    440.   ],
            [     0.   ,      0.   ,     -0.   ,      0.   ]]], dtype=float32)

    In [10]: a.f.record[0,:2].view(np.int32)
    Out[10]:
    array([[[ -969124970,  1175755327,  1177831761,  1036831949],
            [-1088482647,  1056639493,  1058829117,  1065353216],
            [-1088515022, -1085736912,           0,  1138491392],
            [       4096,           0,           0,        4096]],

           [[ -969049027,  1175815251,  1177906452,  1059485181],
            [-1088482647,  1056639493,  1058829117,       39216],
            [-1088515022, -1085736912,           0,  1138491392],
            [    1704064,        3355, -2147483648,        4224]]], dtype=int32)

    In [11]: cf.inst[39216]   ## follow up the iindex 
    Out[11]:
    array([[     0.48 ,     -0.379,      0.792,      0.   ],
           [    -0.619,     -0.785,      0.   ,      0.   ],
           [     0.621,     -0.49 ,     -0.611,      0.   ],
           [-12075.873,   9528.691,  11876.771,      0.   ]], dtype=float32)

    In [12]: cf.inst[39216,:,3]
    Out[12]: array([0., 0., 0., 0.], dtype=float32)

    In [13]: cf.inst[39216,:,3].view(np.int32)
    Out[13]: array([39216,     3,  3355,  3354], dtype=int32)



What has made the geometry give incorrect border 26 when it should give 107?::

    In [8]: a.f.record[:,1,3,0].view(np.int32) >> 16
    Out[8]: array([26, 26, 26, 26, 26, ..., 26, 26, 26, 26, 26], dtype=int32)

    In [9]: cf.sim.bndnamedict[26]
    Out[9]: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up08_up09_HBeam_phys//LatticedShellSteel'


HMM: is there some ordering issue with the implicit boundaries, that results in 
use of stale boundary indices::

     105: 'Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lFasteners_phys//Steel',
     106: 'Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lUpper_phys//Steel',
     107: 'Water///Water',
     108: 'Water///AcrylicMask',
     109: 'Water/HamamatsuMaskOpticalSurface//CDReflectorSteel',


::

    In [11]: a.f.record[0,:2,0]
    Out[11]: 
    array([[-12052.896,   9510.562,  11538.329,      0.1  ],
           [-12127.06 ,   9569.081,  11611.27 ,      0.65 ]], dtype=float32)



Where does the boundary come from in the geometry ?
------------------------------------------------------

The inst dont help::

    In [15]: cf.inst[:,:,3].view(np.int32)
    Out[15]: 
    array([[     0,      0,      0,     -1],
           [     1,      1, 300001,  17612],
           [     2,      1, 300002,  17613],
           [     3,      1, 300003,  17614],
           [     4,      1, 300004,  17615],
           ...,
           [ 48472,      9,      0,     -1],
           [ 48473,      9,      0,     -1],
           [ 48474,      9,      0,     -1],
           [ 48475,      9,      0,     -1],
           [ 48476,      9,      0,     -1]], dtype=int32)


At the lowest level the boundary comes from CSGNode::boundary::

    505 extern "C" __global__ void __intersection__is()
    506 {
    507     HitGroupData* hg  = (HitGroupData*)optixGetSbtDataPointer();
    508     int nodeOffset = hg->nodeOffset ;
    509 
    510     const CSGNode* node = params.node + nodeOffset ;  // root of tree
    511     const float4* plan = params.plan ;
    512     const qat4*   itra = params.itra ;
    513 
    514     const float  t_min = optixGetRayTmin() ;
    515     const float3 ray_origin = optixGetObjectRayOrigin();
    516     const float3 ray_direction = optixGetObjectRayDirection();
    517 
    518     float4 isect ; // .xyz normal .w distance 
    519     if(intersect_prim(isect, node, plan, itra, t_min , ray_origin, ray_direction ))
    520     {
    521         const float lposcost = normalize_z(ray_origin + isect.w*ray_direction ) ;  // scuda.h 
    522         const unsigned hitKind = 0u ;            // only 8bit : could use to customize how attributes interpreted
    523         const unsigned boundary = node->boundary() ;  // all nodes of tree have same boundary 
    524         //printf("//__intersection__is boundary %d \n", boundary ); 
    525 


::

    235     NODE_METHOD unsigned boundary()  const {      return q1.u.z ; }
    236     NODE_METHOD void setBoundary(unsigned bnd){          q1.u.z = bnd ; }




    In [18]: cf.node[:,1,2].view(np.int32)
    Out[18]: array([ 0,  1,  2,  1,  1, ..., 13, 12, 13, 12, 13], dtype=int32)

    In [19]: cf.node[:,1,2].view(np.int32).min()
    Out[19]: 0

    In [20]: cf.node[:,1,2].view(np.int32).max()
    Out[20]: 51

    In [21]: np.c_[np.unique( cf.node[:,1,2].view(np.int32), return_counts=True )]
    Out[21]:
    array([[    0,     1],
           [    1,     5],
           [    2,     1],
           [    3,     3],
           [    4,     1],
           [    5,     3],
           [    6,     6],
           [    7,   193],
           [    8,     1],
           [    9,     3],
           [   10,     1],
           [   11,     1],
           [   12,    64],
           [   13,    64],
           [   14,     1],
           [   15,     1],
           [   16, 14840],
           [   17,     3],
           [   18,     3],
           [   19,    20],
           [   20,     3],
           [   21,   138],
           [   22,   120],
           [   23,   370],
           [   24,   220],
           [   25,    40],
           [   26,    18],
           [   27,    14],
           [   28,    15],
           [   29,    20],
           [   30,    15],
           [   31,     3],
           [   32,     3],
           [   33,     3],
           [   34,     3],
           [   35,     3],
           [   36,     1],
           [   37,     3],
           [   38,    15],
           [   39,     1],
           [   40,     3],
           [   41,     3],
           [   42,     3],
           [   43,     1],
           [   44,     1],
           [   45,     1],
           [   46,     1],
           [   47,     3],
           [   48,     1],
           [   49,     3],
           [   50,     7],
           [   51,     7]])


HUH: those boundaries look really out of whack with these::


    In [23]: cf.sim.bndnamedict
    Out[23]: 
    {0: 'Galactic///Galactic',
     1: 'Galactic///Rock',
     2: 'Rock///Galactic',
     3: 'Rock//Implicit_RINDEX_NoRINDEX_pDomeAir_pDomeRock/Air',
     4: 'Rock///Rock',
     5: 'Rock//Implicit_RINDEX_NoRINDEX_pExpHall_pExpRockBox/Air',
     6: 'Air/Implicit_RINDEX_NoRINDEX_pExpHall_pPoolCover//Steel',
     7: 'Air///Air',
     8: 'Air///LS',
     9: 'Air/Implicit_RINDEX_NoRINDEX_lUpperChimney_phys_pUpperChimneySteel//Steel',
     10: 'Air/Implicit_RINDEX_NoRINDEX_lUpperChimney_phys_pUpperChimneyTyvek//Tyvek',
     11: 'Air/Implicit_RINDEX_NoRINDEX_pPlane_0_ff__pPanel_0_f_//Aluminium',
     12: 'Aluminium///Adhesive',
     13: 'Adhesive///TiO2Coating',
     14: 'TiO2Coating///Scintillator',
     15: 'Air/Implicit_RINDEX_NoRINDEX_pPlane_0_ff__pPanel_1_f_//Aluminium',
     16: 'Air/Implicit_RINDEX_NoRINDEX_pPlane_0_ff__pPanel_2_f_//Aluminium',
     17: 'Air/Implicit_RINDEX_NoRINDEX_pPlane_0_ff__pPanel_3_f_//Aluminium',
     18: 'Air/Implicit_RINDEX_NoRINDEX_pPlane_1_ff__pPanel_0_f_//Aluminium',
     19: 'Air/Implicit_RINDEX_NoRINDEX_pPlane_1_ff__pPanel_1_f_//Aluminium',
     20: 'Air/Implicit_RINDEX_NoRINDEX_pPlane_1_ff__pPanel_2_f_//Aluminium',
     21: 'Air/Implicit_RINDEX_NoRINDEX_pPlane_1_ff__pPanel_3_f_//Aluminium',
     22: 'Rock///Tyvek',
     23: 'Tyvek//VETOTyvekSurface/vetoWater',
     24: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up10_up11_HBeam_phys//LatticedShellSteel',
     25: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up09_up10_HBeam_phys//LatticedShellSteel',
     26: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up08_up09_HBeam_phys//LatticedShellSteel',
     27: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up07_up08_HBeam_phys//LatticedShellSteel',
     28: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up06_up07_HBeam_phys//LatticedShellSteel',
     29: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up05_up06_HBeam_phys//LatticedShellSteel',
     30: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up04_up05_HBeam_phys//LatticedShellSteel',
     31: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up03_up04_HBeam_phys//LatticedShellSteel',
     32: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up02_up03_HBeam_phys//LatticedShellSteel',
     33: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up01_up02_HBeam_phys//LatticedShellSteel',
     34: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw2.equ_up01_HBeam_phys//LatticedShellSteel',
     35: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw2.equ_bt01_HBeam_phys//LatticedShellSteel',
     36: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw3.bt01_bt02_HBeam_phys//LatticedShellSteel',
     37: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw3.bt02_bt03_HBeam_phys//LatticedShellSteel',
     38: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw2.bt03_bt04_HBeam_phys//LatticedShellSteel',
     39: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw2.bt04_bt05_HBeam_phys//LatticedShellSteel',
     40: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.bt05_bt06_HBeam_phys//LatticedShellSteel',
     41: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.bt06_bt07_HBeam_phys//LatticedShellSteel',
     42: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.bt07_bt08_HBeam_phys//LatticedShellSteel',
     43: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.bt08_bt09_HBeam_phys//LatticedShellSteel',
     44: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.bt09_bt10_HBeam_phys//LatticedShellSteel',
     45: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.bt10_bt11_HBeam_phys//LatticedShellSteel',
     46: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb3.up11_HBeam_phys//LatticedShellSteel',
     47: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb4.up10_HBeam_phys//LatticedShellSteel',
     48: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb3.up09_HBeam_phys//LatticedShellSteel',
     49: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb2.up08_HBeam_phys//LatticedShellSteel',
     50: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb2.up07_HBeam_phys//LatticedShellSteel',
     51: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb2.up06_HBeam_phys//LatticedShellSteel',
     52: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.up05_HBeam_phys//LatticedShellSteel',
     53: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.up04_HBeam_phys//LatticedShellSteel',
     54: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.up03_HBeam_phys//LatticedShellSteel',
     55: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.up02_HBeam_phys//LatticedShellSteel',
     56: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.up01_HBeam_phys//LatticedShellSteel',
     57: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb2.equ_HBeam_phys//LatticedShellSteel',
     58: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb2.bt01_HBeam_phys//LatticedShellSteel',
     59: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.bt02_HBeam_phys//LatticedShellSteel',
     60: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb2.bt03_HBeam_phys//LatticedShellSteel',
     61: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb2.bt04_HBeam_phys//LatticedShellSteel',
     62: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.bt05_HBeam_phys//LatticedShellSteel',
     63: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.bt06_HBeam_phys//LatticedShellSteel',
     64: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.bt07_HBeam_phys//LatticedShellSteel',
     65: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb1.bt08_HBeam_phys//LatticedShellSteel',
     66: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb3.bt09_HBeam_phys//LatticedShellSteel',
     67: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb3.bt10_HBeam_phys//LatticedShellSteel',
     68: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLb3.bt11_HBeam_phys//LatticedShellSteel',
     69: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.A01_02_HBeam_phys//LatticedShellSteel',
     70: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.A02_03_HBeam_phys//LatticedShellSteel',
     71: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.A03_04_HBeam_phys//LatticedShellSteel',
     72: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.A04_05_HBeam_phys//LatticedShellSteel',
     73: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.A05_06_HBeam_phys//LatticedShellSteel',
     74: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.A06_07_HBeam_phys//LatticedShellSteel',
     75: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.B01_02_HBeam_phys//LatticedShellSteel',
     76: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.B02_03_HBeam_phys//LatticedShellSteel',
     77: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.B03_04_HBeam_phys//LatticedShellSteel',
     78: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.B04_05_HBeam_phys//LatticedShellSteel',
     79: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.B05_06_HBeam_phys//LatticedShellSteel',
     80: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GZ1.B06_07_HBeam_phys//LatticedShellSteel',
     81: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A02_B02_HBeam_phys//LatticedShellSteel',
     82: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A03_B03_HBeam_phys//LatticedShellSteel',
     83: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A04_B04_HBeam_phys//LatticedShellSteel',
     84: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A05_B05_HBeam_phys//LatticedShellSteel',
     85: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A06_B06_HBeam_phys//LatticedShellSteel',
     86: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A02_B03_HBeam_phys//LatticedShellSteel',
     87: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A03_B04_HBeam_phys//LatticedShellSteel',
     88: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A04_B05_HBeam_phys//LatticedShellSteel',
     89: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A05_B06_HBeam_phys//LatticedShellSteel',
     90: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A06_B07_HBeam_phys//LatticedShellSteel',
     91: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.B01_B01_HBeam_phys//LatticedShellSteel',
     92: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.B03_B03_HBeam_phys//LatticedShellSteel',
     93: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.B05_B05_HBeam_phys//LatticedShellSteel',
     94: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A03_A03_HBeam_phys//LatticedShellSteel',
     95: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A05_A05_HBeam_phys//LatticedShellSteel',
     96: 'vetoWater/CDTyvekSurface//Tyvek',
     97: 'Tyvek//CDInnerTyvekSurface/Water',
     98: 'Water///Acrylic',
     99: 'Acrylic///LS',
     100: 'LS///Acrylic',
     101: 'LS///PE_PA',
     102: 'Water/StrutAcrylicOpSurface//StrutSteel',
     103: 'Water/Strut2AcrylicOpSurface//StrutSteel',
     104: 'Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lSteel_phys//Steel',
     105: 'Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lFasteners_phys//Steel',
     106: 'Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lUpper_phys//Steel',
     107: 'Water///Water',
     108: 'Water///AcrylicMask',
     109: 'Water/HamamatsuMaskOpticalSurface//CDReflectorSteel',
     110: 'Water///Pyrex',
     111: 'Pyrex/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/Vacuum',
     112: 'Vacuum/HamamatsuR12860_PMT_20inch_dynode_plate_opsurface//Steel',
     113: 'Vacuum/HamamatsuR12860_PMT_20inch_outer_edge_opsurface//Steel',
     114: 'Vacuum/HamamatsuR12860_PMT_20inch_inner_edge_opsurface//Steel',
     115: 'Vacuum/HamamatsuR12860_PMT_20inch_inner_ring_opsurface//Steel',
     116: 'Vacuum/HamamatsuR12860_PMT_20inch_dynode_tube_opsurface//Steel',
     117: 'Vacuum/HamamatsuR12860_PMT_20inch_grid_opsurface//Steel',
     118: 'Vacuum/HamamatsuR12860_PMT_20inch_shield_opsurface//Steel',
     119: 'Water/NNVTMaskOpticalSurface//CDReflectorSteel',
     120: 'Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/Vacuum',
     121: 'Vacuum/NNVTMCPPMT_PMT_20inch_mcp_edge_opsurface//Steel',
     122: 'Vacuum/NNVTMCPPMT_PMT_20inch_mcp_plate_opsurface//Steel',
     123: 'Vacuum/NNVTMCPPMT_PMT_20inch_mcp_tube_opsurface//Steel',
     124: 'Vacuum/NNVTMCPPMT_PMT_20inch_mcp_opsurface//Steel',
     125: 'Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum',
     126: 'Pyrex/PMT_3inch_absorb_logsurf2/PMT_3inch_absorb_logsurf1/Vacuum',
     127: 'Water/Implicit_RINDEX_NoRINDEX_PMT_3inch_log_phys_PMT_3inch_cntr_phys//Steel',
     128: 'Water///LS',
     129: 'Water/Steel_surface//Steel',
     130: 'vetoWater///Water',
     131: 'Pyrex///Pyrex',
     132: 'Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum',
     133: 'Pyrex/PMT_20inch_veto_mirror_logsurf2/PMT_20inch_veto_mirror_logsurf1/Vacuum'}

    In [24]:         





PIDX dumping
---------------


PIDX=0 ntds3_noxj::

    //qsim.propagate.head idx 0 : bnc 0 cosTheta -0.79700178 
    //qsim.propagate.head idx 0 : mom = np.array([-0.62137848,0.49031082,0.61113340]) ; lmom = 0.99999994  
    //qsim.propagate.head idx 0 : pos = np.array([-12052.89648,9510.56152,11538.32910]) ; lpos = 19205.62695312 
    //qsim.propagate.head idx 0 : nrm = np.array([(0.20547514,-0.16213273,-0.96513873]) ; lnrm = 0.99999988  
    //qsim.propagate_to_boundary.head idx 0 : u_absorption 0.15698862 logf(u_absorption) -1.85158193 absorption_length 41631.9062 absorption_distance 77084.882812 
    //qsim.propagate_to_boundary.head idx 0 : post = np.array([-12052.89648,9510.56152,11538.32910,   0.10000]) 
    //qsim.propagate_to_boundary.head idx 0 : distance_to_boundary   119.3520 absorption_distance 77084.8828 scattering_distance 659687.8750 
    //qsim.propagate_to_boundary.head idx 0 : u_scattering     0.5170 u_absorption     0.1570 
    //qsim.propagate_to_boundary.tail.SAIL idx 0 : post = np.array([-12127.05957,9569.08105,11611.26953,   0.65024]) ;  sail_time_delta =    0.55024   
    //qsim.propagate idx 0 bounce 0 command 3 flag 0 s.optical.x 56 s.optical.y 2 
    //qsim.propagate.WITH_CUSTOM4 idx 0  BOUNDARY ems 2 lposcost   0.405 
    //qsim.propagate_at_surface.SA/SD.BREAK idx 0 : flag 128 2023-08-12 00:10:08.571 FATAL [233302] [SEvt::gather_components@2901]  SKIP ASSERT : SHOULD NOW ALWAYS HAVE HIT ARRAY (EVEN IF EMPTY?)  AS HAVE SEvt::gatherHit  
    2023-08-12 00:10:08.572 INFO  [233302] [SEvt::save@3243]  dir /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 


How to follow up unexpected bnd ... look at the surface indices
-----------------------------------------------------------------

::

    In [21]: cf.sim.stree.standard.bd.shape
    Out[21]: (134, 4)

    In [22]: cf.sim.stree.standard.bd[20:30]
    Out[22]:
    array([[ 0, 51, -1,  9],
           [ 0, 52, -1,  9],
           [ 1, -1, -1,  5],
           [ 5, -1,  2, 19],
           [19, 53, -1, 10],
           [19, 54, -1, 10],
           [19, 55, -1, 10],
           [19, 56, -1, 10],
           [19, 57, -1, 10],
           [19, 58, -1, 10]], dtype=int32)

    In [26]: cf.sim.stree.standard.bnd_names[26]
    Out[26]: 'vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_GLw1.up08_up09_HBeam_phys//LatticedShellSteel'





    In [25]: np.c_[np.arange(20), cf.sim.stree.standard.mat_names]
    Out[25]:
    array([['0', 'Air'],
           ['1', 'Rock'],
           ['2', 'Galactic'],
           ['3', 'Steel'],
           ['4', 'LS'],
           ['5', 'Tyvek'],
           ['6', 'Scintillator'],
           ['7', 'TiO2Coating'],
           ['8', 'Adhesive'],
           ['9', 'Aluminium'],
           ['10', 'LatticedShellSteel'],
           ['11', 'Acrylic'],
           ['12', 'PE_PA'],
           ['13', 'StrutSteel'],
           ['14', 'AcrylicMask'],
           ['15', 'CDReflectorSteel'],
           ['16', 'Vacuum'],
           ['17', 'Pyrex'],
           ['18', 'Water'],
           ['19', 'vetoWater']], dtype='<U21')





Comparison
-------------

::

    epsilon:~ blyth$ PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh


Add the bnd_names to CSGFoundry.py dumping
---------------------------------------------

They make sense when creating geometry with g4cx/tests/G4CXOpticks_setGeometry_Test.sh
and disabling OSUR::

    export U4Tree__DISABLE_OSUR_IMPLICIT=1


::


    CSGFoundry.descSolid ridx  1 label               r1 numPrim      5 primOffset   2977 lv_one 1 
    pidx 2977 lv 127 pxl    0 :                       PMT_3inch_pmt_solid0x6948250 : no 15927 nn    3 tcn 1:union 105:cylinder 101:sphere tcs [  1 105 101] : bnd 26 : Water///Water 
    pidx 2978 lv 125 pxl    1 :       PMT_3inch_body_solid_ell_ell_helper0x69484b0 : no 15930 nn    1 tcn 103:zsphere tcs [103] : bnd 29 : Water///Pyrex 
    pidx 2979 lv 123 pxl    2 :         PMT_3inch_inner1_solid_ell_helper0x6948550 : no 15931 nn    1 tcn 103:zsphere tcs [103] : bnd 37 : Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum 
    pidx 2980 lv 124 pxl    3 :         PMT_3inch_inner2_solid_ell_helper0x69485f0 : no 15932 nn    1 tcn 103:zsphere tcs [103] : bnd 38 : Pyrex//PMT_3inch_absorb_logsurf1/Vacuum 
    pidx 2981 lv 126 pxl    4 :                      PMT_3inch_cntr_solid0x69486c0 : no 15933 nn    1 tcn 105:cylinder tcs [105] : bnd 25 : Water///Steel 

    CSGFoundry.descSolid ridx  2 label               r2 numPrim      8 primOffset   2982 lv_one 1 
    pidx 2982 lv 114 pxl    1 :                           NNVTMCPPMTsMask0x61c3290 : no 15934 nn    7 tcn 2:intersection 1:union 2:intersection 103:zsphere 105:cylinder 103:!zsphere 105:!cylinder tcs [  2   1   2 103 105 103 105] : bnd 27 : Water///AcrylicMask 
    pidx 2983 lv 115 pxl    2 :                            NNVTMCPPMTTail0x61c45d0 : no 15941 nn   15 tcn 3(2:intersection) 2(1:union) 4(105:cylinder) 2(103:zsphere) 4(0:zero) tcs [  2   1   2   1 105   2 105 103 105   0   0 103 105   0   0] : bnd 33 : Water/NNVTMaskOpticalSurface//CDReflectorSteel 
    pidx 2984 lv 121 pxl    3 :      NNVTMCPPMT_PMT_20inch_pmt_solid_head0x5a63cc0 : no 15956 nn    1 tcn 103:zsphere tcs [103] : bnd 29 : Water///Pyrex 
    pidx 2985 lv 120 pxl    4 :    NNVTMCPPMT_PMT_20inch_inner_solid_head0x61ba970 : no 15957 nn    1 tcn 103:zsphere tcs [103] : bnd 34 : Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/Vacuum 
    pidx 2986 lv 116 pxl    5 :          NNVTMCPPMT_PMT_20inch_edge_solid0x61bc8b0 : no 15958 nn    3 tcn 2:intersection 105:cylinder 105:!cylinder tcs [  2 105 105] : bnd 35 : Vacuum/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf//Steel 
    pidx 2987 lv 117 pxl    6 :         NNVTMCPPMT_PMT_20inch_plate_solid0x61bccc0 : no 15961 nn    3 tcn 2:intersection 105:cylinder 105:!cylinder tcs [  2 105 105] : bnd 36 : Vacuum/NNVTMCPPMT_PMT_20inch_mcp_plate_opsurface//Steel 
    pidx 2988 lv 118 pxl    7 :          NNVTMCPPMT_PMT_20inch_tube_solid0x61bcfe0 : no 15964 nn    3 tcn 2:intersection 105:cylinder 105:!cylinder tcs [  2 105 105] : bnd 35 : Vacuum/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf//Steel 
    pidx 2989 lv 119 pxl    8 :           NNVTMCPPMT_PMT_20inch_mcp_solid0x61bd2e0 : no 15967 nn    1 tcn 105:cylinder tcs [105] : bnd 35 : Vacuum/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf//Steel 

    CSGFoundry.descSolid ridx  3 label               r3 numPrim     11 primOffset   2990 lv_one 1 
    pidx 2990 lv 102 pxl    1 :                      HamamatsuR12860sMask0x61b1d70 : no 15968 nn    7 tcn 2:intersection 1:union 2:intersection 103:zsphere 105:cylinder 103:!zsphere 105:!cylinder tcs [  2   1   2 103 105 103 105] : bnd 27 : Water///AcrylicMask 
    pidx 2991 lv 103 pxl    2 :                       HamamatsuR12860Tail0x61b3b50 : no 15975 nn   15 tcn 3(2:intersection) 2(1:union) 4(105:cylinder) 2(103:zsphere) 4(0:zero) tcs [  2   1   2   1 105   2 105 105 103   0   0 105 103   0   0] : bnd 28 : Water/HamamatsuMaskOpticalSurface//CDReflectorSteel 
    pidx 2992 lv 112 pxl    3 :  HamamatsuR12860_PMT_20inch_pmt_solid_1_40x619ed30 : no 15990 nn   15 tcn 3(1:union) 1(108:cone) 2(103:zsphere) 8(0:zero) 1(105:cylinder) tcs [  1   1 108   1 103   0   0 103 105   0   0   0   0   0   0] : bnd 29 : Water///Pyrex 
    pidx 2993 lv 111 pxl    4 : HamamatsuR12860_PMT_20inch_inner_solid_1_40x61a4350 : no 16005 nn   15 tcn 3(1:union) 1(108:cone) 2(103:zsphere) 8(0:zero) 1(105:cylinder) tcs [  1   1 108   1 103   0   0 103 105   0   0   0   0   0   0] : bnd 30 : Pyrex/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/Vacuum 
    pidx 2994 lv 104 pxl    5 :    HamamatsuR12860_PMT_20inch_plate_solid0x61a60e0 : no 16020 nn    3 tcn 2:intersection 105:cylinder 105:!cylinder tcs [  2 105 105] : bnd 31 : Vacuum/HamamatsuR12860_PMT_20inch_dynode_plate_opsurface//Steel 
    pidx 2995 lv 105 pxl    6 : HamamatsuR12860_PMT_20inch_outer_edge_solid0x61a9350 : no 16023 nn    3 tcn 2:intersection 105:cylinder 105:!cylinder tcs [  2 105 105] : bnd 32 : Vacuum/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf//Steel 
    pidx 2996 lv 106 pxl    7 : HamamatsuR12860_PMT_20inch_inner_edge_solid0x61a9680 : no 16026 nn    3 tcn 2:intersection 105:cylinder 105:!cylinder tcs [  2 105 105] : bnd 32 : Vacuum/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf//Steel 
    pidx 2997 lv 107 pxl    8 : HamamatsuR12860_PMT_20inch_inner_ring_solid0x61a99e0 : no 16029 nn    3 tcn 2:intersection 105:cylinder 105:!cylinder tcs [  2 105 105] : bnd 32 : Vacuum/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf//Steel 
    pidx 2998 lv 108 pxl    9 : HamamatsuR12860_PMT_20inch_dynode_tube_solid0x61a9d40 : no 16032 nn    3 tcn 2:intersection 105:cylinder 105:!cylinder tcs [  2 105 105] : bnd 32 : Vacuum/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf//Steel 
    pidx 2999 lv 109 pxl   10 :     HamamatsuR12860_PMT_20inch_grid_solid0x61aa0a0 : no 16035 nn    1 tcn 105:cylinder tcs [105] : bnd 32 : Vacuum/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf//Steel 
    pidx 3000 lv 110 pxl   11 :   HamamatsuR12860_PMT_20inch_shield_solid0x61aa950 : no 16036 nn    3 tcn 2:intersection 105:cylinder 105:!cylinder tcs [  2 105 105] : bnd 32 : Vacuum/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf//Steel 

    CSGFoundry.descSolid ridx  4 label               r4 numPrim      5 primOffset   3001 lv_one 1 
    pidx 3001 lv 134 pxl    1 :                 mask_PMT_20inch_vetosMask0x61c6740 : no 16039 nn    7 tcn 2:intersection 1:union 2:intersection 103:zsphere 105:cylinder 103:!zsphere 105:!cylinder tcs [  2   1   2 103 105 103 105] : bnd 19 : Water///Acrylic 
    pidx 3002 lv 138 pxl    2 :             PMT_20inch_veto_pmt_solid_1_20x61c8680 : no 16046 nn    3 tcn 1:union 103:zsphere 105:cylinder tcs [  1 103 105] : bnd 29 : Water///Pyrex 
    pidx 3003 lv 137 pxl    3 :            PMT_20inch_veto_body_solid_1_20x61c8f90 : no 16049 nn    3 tcn 1:union 103:zsphere 105:cylinder tcs [  1 103 105] : bnd 42 : Pyrex///Pyrex 
    pidx 3004 lv 135 pxl    4 :              PMT_20inch_veto_inner1_solid0x61c9be0 : no 16052 nn    7 tcn 2:intersection 1:union 105:cylinder 103:zsphere 105:cylinder 0:zero 0:zero tcs [  2   1 105 103 105   0   0] : bnd 43 : Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum 
    pidx 3005 lv 136 pxl    5 :              PMT_20inch_veto_inner2_solid0x61c9dd0 : no 16059 nn    7 tcn 2:intersection 1:union 105:!cylinder 103:zsphere 105:cylinder 0:zero 0:zero tcs [  2   1 105 103 105   0   0] : bnd 44 : Pyrex//PMT_20inch_veto_mirror_logsurf1/Vacuum 

    CSGFoundry.descSolid ridx  5 label               r5 numPrim      1 primOffset   3006 lv_one 1 
    pidx 3006 lv  98 pxl    0 :                            sStrutBallhead0x5a9c000 : no 16066 nn    1 tcn 101:sphere tcs [101] : bnd 25 : Water///Steel 

    CSGFoundry.descSolid ridx  6 label               r6 numPrim      1 primOffset   3007 lv_one 1 
    pidx 3007 lv  99 pxl    0 :                                      uni10x5aa4f70 : no 16067 nn   31 tcn 8(1:union) 1(2:intersection) 10(105:cylinder) 12(0:zero) tcs [  1   1   2   1   1 105 105   1   1   1   1   0   0   0   0 105 105 105 105 105 105 105 105   0   0   0   0   0   0   0   0] : bnd 25 : Water///Steel 

    CSGFoundry.descSolid ridx  7 label               r7 numPrim      1 primOffset   3008 lv_one 1 
    pidx 3008 lv 100 pxl    0 :                                base_steel0x5b450d0 : no 16098 nn    7 tcn 2:intersection 1:union 2:intersection 105:cylinder 105:cylinder 105:!cylinder 105:!cylinder tcs [  2   1   2 105 105 105 105] : bnd 25 : Water///Steel 

    CSGFoundry.descSolid ridx  8 label               r8 numPrim      1 primOffset   3009 lv_one 1 
    pidx 3009 lv 101 pxl    0 :                              uni_acrylic10x5bede30 : no 16105 nn    7 tcn 2:intersection 1:union 101:!sphere 108:cone 105:cylinder 0:zero 0:zero tcs [  2   1 101 108 105   0   0] : bnd 19 : Water///Acrylic 

    CSGFoundry.descSolid ridx  9 label               r9 numPrim    130 primOffset   3010 lv_one 0 
     i   3 ulv  11 xlv    0 nlv   1 : pidx 3010 lv  11 pxl    0 :                                    sPanel0x73d9660 : no 16112 nn    1 tcn 110:box3 tcs [110] : bnd 10 : Air///Aluminium  
     i   2 ulv  10 xlv    1 nlv   1 : pidx 3011 lv  10 pxl    1 :                                sPanelTape0x73d9a60 : no 16113 nn    1 tcn 110:box3 tcs [110] : bnd 11 : Aluminium///Adhesive  
     i   1 ulv   9 xlv    2 nlv  64 : pidx 3012 lv   9 pxl    2 :                                      sBar0x73d9bd0 : no 16114 nn    1 tcn 110:box3 tcs [110] : bnd 12 : Adhesive///TiO2Coating  
     i   0 ulv   8 xlv    3 nlv  64 : pidx 3013 lv   8 pxl    3 :                                      sBar0x73d9d40 : no 16115 nn    1 tcn 110:box3 tcs [110] : bnd 13 : TiO2Coating///Scintillator  



With OSUR enabled the above gets scrambled. 



When enabling osur the two stree diverge::

    In [1]: len(abn)                                                                                                                             
    Out[1]: 45

    In [2]: len(bbn)                                                                                                                             
    Out[2]: 127


Contrast creation of the two stree : then remove one
-------------------------------------------------------

::

    104 G4CXOpticks::G4CXOpticks()
    105     :
    106     sim(SSim::CreateOrReuse()),
    107     tr(nullptr),

    119 SSim::SSim()
    120     :
    121     relp(ssys::getenvvar("SSim__RELP", RELP_DEFAULT )), // alt: "extra/GGeo"
    122     sctx(new scontext),
    123     top(nullptr),
    124     extra(nullptr),
    125     tree(new stree)
    126 {
    127     init();
    128 }


    254 void G4CXOpticks::setGeometry(const G4VPhysicalVolume* world )
    255 {   
    256     LOG(LEVEL) << " G4VPhysicalVolume world " << world ;
    257     assert(world);
    258     wd = world ;
    259     
    260     assert(sim && "sim instance should have been created in ctor" );
    261     stree* st = sim->get_tree();
    262     
    263     tr = U4Tree::Create(st, world, SensorIdentifier ) ;
    264     
    265     // GGeo creation done when starting from a gdml or live G4,  still needs Opticks instance
    266     Opticks::Configure("--gparts_transform_offset --allownokey" );
    267     GGeo* gg_ = X4Geo::Translate(wd) ;
    268     
    269     setGeometry(gg_);
    270 }


::

    1405 void X4PhysicalVolume::convertStructure()
    1406 {
    1407     assert(m_top) ;
    1408     LOG(LEVEL) << "[ creating large tree of GVolume instances" ;
    1409 
    1410     m_tree = new stree ;   // HMM: m_tree is a spy from the future 
    1411     m_ggeo->setTree(m_tree);
    1412 


Where is the stree/snode/boundary used to populate the CSGNode ?
-----------------------------------------------------------------

::

     727 CSGNode* CSG_GGeo_Convert::convertNode(const GParts* comp, unsigned primIdx, unsigned partIdxRel )
     728 {
     729     unsigned repeatIdx = comp->getRepeatIndex();  // set in GGeo::deferredCreateGParts
     730     unsigned partOffset = comp->getPartOffset(primIdx) ;
     731     unsigned partIdx = partOffset + partIdxRel ;
     732     unsigned idx = comp->getIndex(partIdx);
     733     assert( idx == partIdx );
     734     unsigned boundary = comp->getBoundary(partIdx); // EXPT
     ...
     810     n->setTransform(tranIdx);
     811     n->setComplement(complement);
     812     n->setBoundary(boundary);       // EXPT
     813 

::

    X4PhysicalVolume::convertImplicitSurfaces_r





ntds3_noxjshfa : V1J010
--------------------------

::

    In [48]: a.node.shape
    Out[48]: (15968, 4, 4)

    In [49]: ab.node.shape   ## ab.node is max deviation of the 16 values in the a and b nodes
    Out[49]: (15968,)

    In [12]: w = np.where(ab.node>0.1)[0]    ## 12/15968 nodes have differences

    In [38]: w
    Out[38]: array([  15679, 15680,    15720, 15721,     15750, 15753,     15765, 15768,    15827, 15829, 15830, 15834])
                          

    #(numNode,nodeOffset,tranOffset,planOffset)(sbtIndexOffset,meshIdx,repeatIdx,primIdx)

    In [39]: a.prim.view(np.int32)[:,:2].reshape(-1,8)[-160:-140]
    Out[39]:
    array([[    7, 15676,  7182,     0,     0,   117,     2,     0],     ## NNVTMCPPMTsMask_virtual
           [    7, 15683,  7185,     0,     1,   109,     2,     1],
           [   15, 15690,  7189,     0,     2,   110,     2,     2],
           [    1, 15705,  7195,     0,     3,   116,     2,     3],
           [    1, 15706,  7196,     0,     4,   115,     2,     4],
           [    3, 15707,  7197,     0,     5,   111,     2,     5],
           [    3, 15710,  7199,     0,     6,   112,     2,     6],
           [    3, 15713,  7201,     0,     7,   113,     2,     7],
           [    1, 15716,  7203,     0,     8,   114,     2,     8],

           [    7, 15717,  7204,     0,     0,   108,     3,     0],     ## HamamatsuR12860sMask_virtual
           [    7, 15724,  7207,     0,     1,    97,     3,     1],
           [   15, 15731,  7211,     0,     2,    98,     3,     2],
           [   15, 15746,  7217,     0,     3,   107,     3,     3],     ## 
           [   15, 15761,  7221,     0,     4,   106,     3,     4],     ##
           [    3, 15776,  7225,     0,     5,    99,     3,     5],
           [    3, 15779,  7227,     0,     6,   100,     3,     6],
           [    3, 15782,  7229,     0,     7,   101,     3,     7],
           [    3, 15785,  7231,     0,     8,   102,     3,     8],
           [    3, 15788,  7233,     0,     9,   103,     3,     9],
           [    1, 15791,  7235,     0,    10,   104,     3,    10]], dtype=int32)


    In [47]: np.c_[a.meshname[a.prim.view(np.int32)[:,1,1][-160:-140]]]
    Out[47]: 
    array([['NNVTMCPPMTsMask_virtual'],                     ##
           ['NNVTMCPPMTsMask'],
           ['NNVTMCPPMTTail'],
           ['NNVTMCPPMT_PMT_20inch_pmt_solid_head'],
           ['NNVTMCPPMT_PMT_20inch_inner_solid_head'],
           ['NNVTMCPPMT_PMT_20inch_edge_solid'],
           ['NNVTMCPPMT_PMT_20inch_plate_solid'],
           ['NNVTMCPPMT_PMT_20inch_tube_solid'],
           ['NNVTMCPPMT_PMT_20inch_mcp_solid'],

           ['HamamatsuR12860sMask_virtual'],                   ##
           ['HamamatsuR12860sMask'],
           ['HamamatsuR12860Tail'],
           ['HamamatsuR12860_PMT_20inch_pmt_solid_1_4'],       ##  
           ['HamamatsuR12860_PMT_20inch_inner_solid_1_4'],     ##
           ['HamamatsuR12860_PMT_20inch_plate_solid'],
           ['HamamatsuR12860_PMT_20inch_outer_edge_solid'],
           ['HamamatsuR12860_PMT_20inch_inner_edge_solid'],
           ['HamamatsuR12860_PMT_20inch_inner_ring_solid'],
           ['HamamatsuR12860_PMT_20inch_dynode_tube_solid'],
           ['HamamatsuR12860_PMT_20inch_grid_solid']], dtype=object)



Probably polycone shifts in NNVTMCPPMTsMask_virtual
-----------------------------------------------------

::

    In [56]: print(ab.descLVDetail(117))
    CSGFoundryAB.descLVDetail
    descLV lvid:117 meshname:NNVTMCPPMTsMask_virtual pidxs:[2928]
    pidx 2928 lv 117 pxl    0 :                            NNVTMCPPMTsMask_virtual : no 15676 nn    7 tcn 1:union 1:union 108:cone 105:cylinder 105:cylinder 0:zero 0:zero tcs [  1   1 108 105 105   0   0] : bnd 24 : Water///Water 

    a.node[15676:15676+7].reshape(-1,16)[:,:6] # descNodeParam 
    [[   0.       0.       0.       0.       0.       0.   ]  union
     [   0.       0.       0.       0.       0.       0.   ]  union
     [ 264.05    97.     132.025  194.05     0.       0.   ]  cone
     [   0.       0.       0.     264.05  -183.225    1.   ]  cylinder
     [   0.       0.       0.     264.05     0.      98.   ]  cylinder
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]]

    a.node[15676:15676+7].reshape(-1,16)[:,8:14] # descNodeBB 
    [[  -0.      -0.      -0.       0.       0.       0.   ]
     [  -0.      -0.      -0.       0.       0.       0.   ]
     [-264.05  -264.05    97.     264.05   264.05   194.05 ]
     [-264.05  -264.05  -183.225  264.05   264.05     1.   ]
     [-264.05  -264.05     0.     264.05   264.05    98.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]]
    a.node[15676:15676+7].reshape(-1,16).view(np.int32)[:,6:8] # descNodeBoundaryIndex 
    [[24  0]
     [24  1]
     [24  2]
     [24  3]
     [24  4]
     [24  5]
     [24  6]]
    a.node[15676:15676+7].reshape(-1,16).view(np.int32)[:,14:16] # descNodeTCTran 
    [[   1    0]
     [   1    0]
     [ 108 7183]
     [ 105 7184]
     [ 105 7185]
     [   0    0]
     [   0    0]]
    a.node[15676:15676+7].reshape(-1,16).view(np.int32)[:,14:16] & 0x7ffffff  # descNodeTCTran 
    [[   1    0]
     [   1    0]
     [ 108 7183]
     [ 105 7184]
     [ 105 7185]
     [   0    0]
     [   0    0]]
    descLV lvid:117 meshname:NNVTMCPPMTsMask_virtual pidxs:[2928]
    pidx 2928 lv 117 pxl    0 :                            NNVTMCPPMTsMask_virtual : no 15676 nn    7 tcn 1:union 1:union 108:cone 105:cylinder 105:cylinder 0:zero 0:zero tcs [  1   1 108 105 105   0   0] : bnd 24 : Water///Water 
    b.node[15676:15676+7].reshape(-1,16)[:,:6] # descNodeParam 
    [[   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [ 264.05    97.     132.025  194.05     0.       0.   ]
     [   0.       0.       0.     264.05  -183.225    0.   ]
     [   0.       0.       0.     264.05     0.      97.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]]
    b.node[15676:15676+7].reshape(-1,16)[:,8:14] # descNodeBB 
    [[  -0.      -0.      -0.       0.       0.       0.   ]
     [  -0.      -0.      -0.       0.       0.       0.   ]
     [-264.05  -264.05    97.     264.05   264.05   194.05 ]
     [-264.05  -264.05  -183.225  264.05   264.05     0.   ]
     [-264.05  -264.05     0.     264.05   264.05    97.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]]
    b.node[15676:15676+7].reshape(-1,16).view(np.int32)[:,6:8] # descNodeBoundaryIndex 
    [[   24 15676]
     [   24 15677]
     [   24 15678]
     [   24 15679]
     [   24 15680]
     [   24 15681]
     [   24 15682]]
    b.node[15676:15676+7].reshape(-1,16).view(np.int32)[:,14:16] # descNodeTCTran 
    [[   1    0]
     [   1    0]
     [ 108 7183]
     [ 105 7184]
     [ 105 7185]
     [   0    0]
     [   0    0]]
    b.node[15676:15676+7].reshape(-1,16).view(np.int32)[:,14:16] & 0x7ffffff  # descNodeTCTran 
    [[   1    0]
     [   1    0]
     [ 108 7183]
     [ 105 7184]
     [ 105 7185]
     [   0    0]
     [   0    0]]












::


    In [50]: a.prim.view(np.int32)[:,:2].reshape(-1,8)[-140:-120]
    Out[50]:
    array([[    3, 15792,  7236,     0,    11,   105,     3,    11],
           [    1, 15795,  7238,     0,     0,   134,     4,     0],
           [    7, 15796,  7239,     0,     1,   129,     4,     1],
           [    3, 15803,  7243,     0,     2,   133,     4,     2],
           [    3, 15806,  7245,     0,     3,   132,     4,     3],
           [    7, 15809,  7247,     0,     4,   130,     4,     4],
           [    7, 15816,  7250,     0,     5,   131,     4,     5],
           [    1, 15823,  7253,     0,     0,    94,     5,     0],
          #[    7, 15824,  7254,     0,     0,   #95,     6,     0],
          #[    7, 15831,  7258,     0,     0,   #96,     7,     0],
           [    1, 15838,  7261,     0,     0,    11,     8,     0],
           [    1, 15839,  7262,     0,     1,    10,     8,     1],
           [    1, 15840,  7263,     0,     2,     9,     8,     2],
           [    1, 15841,  7264,     0,     3,     8,     8,     3],
           [    1, 15842,  7265,     0,     4,     9,     8,     4],
           [    1, 15843,  7266,     0,     5,     8,     8,     5],
           [    1, 15844,  7267,     0,     6,     9,     8,     6],
           [    1, 15845,  7268,     0,     7,     8,     8,     7],
           [    1, 15846,  7269,     0,     8,     9,     8,     8],
           [    1, 15847,  7270,     0,     9,     8,     8,     9]], dtype=int32)

    In [51]: w
    Out[51]: array([15679, 15680, 15720, 15721, 15750, 15753, 15765, 15768,     15827, 15829, 15830, 15834])

    In [52]: np.c_[a.meshname[a.prim.view(np.int32)[:,1,1][-140:-120]]]
    Out[52]:
    array([['HamamatsuR12860_PMT_20inch_shield_solid'],
           ['mask_PMT_20inch_vetosMask_virtual'],
           ['mask_PMT_20inch_vetosMask'],
           ['PMT_20inch_veto_pmt_solid_1_2'],
           ['PMT_20inch_veto_body_solid_1_2'],
           ['PMT_20inch_veto_inner1_solid'],
           ['PMT_20inch_veto_inner2_solid'],
           ['sStrutBallhead'],
          #['base_steel'],
          #['uni_acrylic1'],
           ['sPanel'],
           ['sPanelTape'],
           ['sBar'],
           ['sBar'],
           ['sBar'],
           ['sBar'],
           ['sBar'],
           ['sBar'],
           ['sBar'],
           ['sBar']], dtype=object)






GEOM V1J010 : LV 95
----------------------

::

    In [53]: print(ab.descLVDetail(95))
    CSGFoundryAB.descLVDetail
    descLV lvid:95 meshname:base_steel pidxs:[2956]
    pidx 2956 lv  95 pxl    0 :                                         base_steel : no 15824 nn    7 tcn 2:intersection 1:union 2:intersection 105:cylinder 105:cylinder 105:!cylinder 105:!cylinder tcs [  2   1   2 105 105 105 105] : bnd 23 : Water///Steel 
    a.node[15824:15824+7].reshape(-1,16)[:,:6] # descNodeParam 
    [[   0.     0.     0.     0.     0.     0. ]
     [   0.     0.     0.     0.     0.     0. ]
     [   0.     0.     0.     0.     0.     0. ]
     [   0.     0.     0.    70.  -101.   -14. ]
     [   0.     0.     0.   195.   -15.     0. ]
     [   0.     0.     0.    55.5 -102.   -15. ]
     [   0.     0.     0.    43.   -16.     1. ]]
    a.node[15824:15824+7].reshape(-1,16)[:,8:14] # descNodeBB 
    [[  -0.    -0.    -0.     0.     0.     0. ]
     [  -0.    -0.    -0.     0.     0.     0. ]
     [  -0.    -0.    -0.     0.     0.     0. ]
     [ -70.   -70.  -101.    70.    70.   -14. ]
     [-195.  -195.   -15.   195.   195.     0. ]
     [ -55.5  -55.5 -102.    55.5   55.5  -15. ]
     [ -43.   -43.   -16.    43.    43.     1. ]]
    a.node[15824:15824+7].reshape(-1,16).view(np.int32)[:,6:8] # descNodeBoundaryIndex 
    [[23  0]
     [23  1]
     [23  2]
     [23  3]
     [23  4]
     [23  5]
     [23  6]]
    a.node[15824:15824+7].reshape(-1,16).view(np.int32)[:,14:16] # descNodeTCTran 
    [[          2           0]
     [          1           0]
     [          2           0]
     [        105        7255]
     [        105        7256]
     [        105 -2147476391]
     [        105 -2147476390]]
    a.node[15824:15824+7].reshape(-1,16).view(np.int32)[:,14:16] & 0x7ffffff  # descNodeTCTran 
    [[   2    0]
     [   1    0]
     [   2    0]
     [ 105 7255]
     [ 105 7256]
     [ 105 7257]
     [ 105 7258]]
    descLV lvid:95 meshname:base_steel pidxs:[2956]
    pidx 2956 lv  95 pxl    0 :                                         base_steel : no 15824 nn    7 tcn 3:difference 1:union 1:union 105:cylinder 105:cylinder 105:cylinder 105:cylinder tcs [  3   1   1 105 105 105 105] : bnd 23 : Water///Steel 

    b.node[15824:15824+7].reshape(-1,16)[:,:6] # descNodeParam 
    [[   0.     0.     0.     0.     0.     0. ]
     [   0.     0.     0.     0.     0.     0. ]
     [   0.     0.     0.     0.     0.     0. ]
     [   0.     0.     0.    70.  -101.   -15. ]
     [   0.     0.     0.   195.   -15.     0. ]
     [   0.     0.     0.    55.5 -101.   -15. ]
     [   0.     0.     0.    43.   -15.     0. ]]

    b.node[15824:15824+7].reshape(-1,16)[:,8:14] # descNodeBB 
    [[  -0.    -0.    -0.     0.     0.     0. ]
     [  -0.    -0.    -0.     0.     0.     0. ]
     [  -0.    -0.    -0.     0.     0.     0. ]
     [ -70.   -70.  -101.    70.    70.   -15. ]
     [-195.  -195.   -15.   195.   195.     0. ]
     [ -55.5  -55.5 -101.    55.5   55.5  -15. ]
     [ -43.   -43.   -15.    43.    43.     0. ]]

    b.node[15824:15824+7].reshape(-1,16).view(np.int32)[:,6:8] # descNodeBoundaryIndex 
    [[   23 15824]
     [   23 15825]
     [   23 15826]
     [   23 15827]
     [   23 15828]
     [   23 15829]
     [   23 15830]]

    b.node[15824:15824+7].reshape(-1,16).view(np.int32)[:,14:16] # descNodeTCTran 
    [[   3    0]
     [   1    0]
     [   1    0]
     [ 105 7255]
     [ 105 7256]
     [ 105 7257]
     [ 105 7258]]

    b.node[15824:15824+7].reshape(-1,16).view(np.int32)[:,14:16] & 0x7ffffff  # descNodeTCTran 
    [[   3    0]
     [   1    0]
     [   1    0]
     [ 105 7255]
     [ 105 7256]
     [ 105 7257]
     [ 105 7258]]

    In [54]:                  


LV 96 : uni_acrylic1
-----------------------

* looks like uncoincidence diffs 


::

    In [54]: print(ab.descLVDetail(96))
    CSGFoundryAB.descLVDetail
    descLV lvid:96 meshname:uni_acrylic1 pidxs:[2957]
    pidx 2957 lv  96 pxl    0 :                                       uni_acrylic1 : no 15831 nn    7 tcn 2:intersection 1:union 101:!sphere 108:cone 105:cylinder 0:zero 0:zero tcs [  2   1 101 108 105   0   0] : bnd 19 : Water///Acrylic 

    a.node[15831:15831+7].reshape(-1,16)[:,:6] # descNodeParam 
    [[    0.        0.        0.        0.        0.        0.   ]
     [    0.        0.        0.        0.        0.        0.   ]
     [    0.        0.        0.    17824.        0.        0.   ]
     [  200.     -140.      451.786     1.        0.        0.   ]
     [    0.        0.        0.      450.        0.        5.7  ]
     [    0.        0.        0.        0.        0.        0.   ]
     [    0.        0.        0.        0.        0.        0.   ]]

    b.node[15831:15831+7].reshape(-1,16)[:,:6] # descNodeParam 
    [[    0.      0.      0.      0.      0.      0. ]
     [    0.      0.      0.      0.      0.      0. ]
     [    0.      0.      0.  17824.      0.      0. ]     ### HUGE SPHERE
     [  200.   -140.    450.      0.      0.      0. ]     ### UNCOINCIDENCE CHANGE TO CONE PARAM ? 
     [    0.      0.      0.    450.      0.      5.7]
     [    0.      0.      0.      0.      0.      0. ]
     [    0.      0.      0.      0.      0.      0. ]]


    a.node[15831:15831+7].reshape(-1,16)[:,8:14] # descNodeBB 
    [[    -0.        -0.        -0.         0.         0.         0.   ]
     [    -0.        -0.        -0.         0.         0.         0.   ]
     [-17824.    -17824.         0.     17824.     17824.     35648.   ]
     [  -451.786   -451.786   -140.       451.786    451.786      1.   ]
     [  -450.      -450.         0.       450.       450.         5.7  ]
     [  -100.      -100.      -100.       100.       100.       100.   ]
     [  -100.      -100.      -100.       100.       100.       100.   ]]


    a.node[15831:15831+7].reshape(-1,16).view(np.int32)[:,6:8] # descNodeBoundaryIndex 
    [[19  0]
     [19  1]
     [19  2]
     [19  3]
     [19  4]
     [19  5]
     [19  6]]
    a.node[15831:15831+7].reshape(-1,16).view(np.int32)[:,14:16] # descNodeTCTran 
    [[          2           0]
     [          1           0]
     [        101 -2147476389]
     [        108        7260]
     [        105        7261]
     [          0           0]
     [          0           0]]
    a.node[15831:15831+7].reshape(-1,16).view(np.int32)[:,14:16] & 0x7ffffff  # descNodeTCTran 
    [[   2    0]
     [   1    0]
     [ 101 7259]
     [ 108 7260]
     [ 105 7261]
     [   0    0]
     [   0    0]]
    descLV lvid:96 meshname:uni_acrylic1 pidxs:[2957]
    pidx 2957 lv  96 pxl    0 :                                       uni_acrylic1 : no 15831 nn    7 tcn 3:difference 1:union 101:sphere 108:cone 105:cylinder 0:zero 0:zero tcs [  3   1 101 108 105   0   0] : bnd 19 : Water///Acrylic 

    b.node[15831:15831+7].reshape(-1,16)[:,:6] # descNodeParam 
    [[    0.      0.      0.      0.      0.      0. ]
     [    0.      0.      0.      0.      0.      0. ]
     [    0.      0.      0.  17824.      0.      0. ]
     [  200.   -140.    450.      0.      0.      0. ]
     [    0.      0.      0.    450.      0.      5.7]
     [    0.      0.      0.      0.      0.      0. ]
     [    0.      0.      0.      0.      0.      0. ]]

    b.node[15831:15831+7].reshape(-1,16)[:,8:14] # descNodeBB 
    [[    -0.      -0.      -0.       0.       0.       0. ]
     [    -0.      -0.      -0.       0.       0.       0. ]
     [-17824.  -17824.       0.   17824.   17824.   35648. ]
     [  -450.    -450.    -140.     450.     450.       0. ]
     [  -450.    -450.       0.     450.     450.       5.7]
     [  -100.    -100.    -100.     100.     100.     100. ]
     [  -100.    -100.    -100.     100.     100.     100. ]]

    b.node[15831:15831+7].reshape(-1,16).view(np.int32)[:,6:8] # descNodeBoundaryIndex 
    [[   19 15831]
     [   19 15832]
     [   19 15833]
     [   19 15834]
     [   19 15835]
     [   19 15836]
     [   19 15837]]
    b.node[15831:15831+7].reshape(-1,16).view(np.int32)[:,14:16] # descNodeTCTran 
    [[   3    0]
     [   1    0]
     [ 101 7259]
     [ 108 7260]
     [ 105 7261]
     [   0    0]
     [   0    0]]
    b.node[15831:15831+7].reshape(-1,16).view(np.int32)[:,14:16] & 0x7ffffff  # descNodeTCTran 
    [[   3    0]
     [   1    0]
     [ 101 7259]
     [ 108 7260]
     [ 105 7261]
     [   0    0]
     [   0    0]]

    In [55]:                           





::


    In [58]: print(ab.descLVDetail(107))                                                                                                         
    CSGFoundryAB.descLVDetail
    descLV lvid:107 meshname:HamamatsuR12860_PMT_20inch_pmt_solid_1_4 pidxs:[2940]
    pidx 2940 lv 107 pxl    3 :           HamamatsuR12860_PMT_20inch_pmt_solid_1_4 : no 15746 nn   15 tcn 3(1:union) 1(108:cone) 2(103:zsphere) 8(0:zero) 1(105:cylinder) tcs [  1   1 108   1 103   0   0 103 105   0   0   0   0   0   0] : bnd 27 : Water///Pyrex 

    a.node[15746:15746+15].reshape(-1,16)[:,:6] # descNodeParam 
    [[   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [ 139.245    5.99   142.968   17.17     0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.     190.001 -168.226    1.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.     190.001   -1.     190.101]
     [   0.       0.       0.     254.001   -2.5      2.5  ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]]

    b.node[15746:15746+15].reshape(-1,16)[:,:6] # descNodeParam 
    [[   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [ 139.245    5.99   142.968   17.17     0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.     190.001 -168.226    0.   ]    ##
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.     190.001    0.     190.101]
     [   0.       0.       0.     254.001   -2.5      2.5  ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]]


    a.node[15746:15746+15].reshape(-1,16)[:,8:14] # descNodeBB 
    [[  -0.      -0.      -0.       0.       0.       0.   ]
     [  -0.      -0.      -0.       0.       0.       0.   ]
     [-142.968 -142.968 -173.226  142.968  142.968 -162.045]
     [  -0.      -0.      -0.       0.       0.       0.   ]
     [-254.001 -254.001 -173.226  254.001  254.001   -4.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-254.001 -254.001   -1.     254.001  254.001  190.101]
     [-254.001 -254.001   -5.     254.001  254.001    0.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]]

    a.node[15746:15746+15].reshape(-1,16).view(np.int32)[:,6:8] # descNodeBoundaryIndex 
    [[27 29]
     [27 30]
     [27 31]
     [27 32]
     [27 33]
     [27 34]
     [27 35]
     [27 36]
     [27 37]
     [27 38]
     [27 39]
     [27 40]
     [27 41]
     [27 42]
     [27 43]]


                  U
           U               C
       U      S       .         .
     S   C  .   .   .   .     .    .



    a.node[15746:15746+15].reshape(-1,16).view(np.int32)[:,14:16] # descNodeTCTran 
    [[   1    0]    UNION
     [   1    0]    UNION
     [ 108 7218]    CONE
     [   1    0]    UNION
     [ 103 7219]    ZSPHERE
     [   0    0]
     [   0    0]
     [ 103 7220]    ZSPHERE
     [ 105 7221]    CYLINDER
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]]

    a.node[15746:15746+15].reshape(-1,16).view(np.int32)[:,14:16] & 0x7ffffff  # descNodeTCTran 
    [[   1    0]
     [   1    0]
     [ 108 7218]
     [   1    0]
     [ 103 7219]
     [   0    0]
     [   0    0]
     [ 103 7220]
     [ 105 7221]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]]
    descLV lvid:107 meshname:HamamatsuR12860_PMT_20inch_pmt_solid_1_4 pidxs:[2940]
    pidx 2940 lv 107 pxl    3 :           HamamatsuR12860_PMT_20inch_pmt_solid_1_4 : no 15746 nn   15 tcn 3(1:union) 1(108:cone) 2(103:zsphere) 8(0:zero) 1(105:cylinder) tcs [  1   1 108   1 103   0   0 103 105   0   0   0   0   0   0] : bnd 27 : Water///Pyrex 

    b.node[15746:15746+15].reshape(-1,16)[:,:6] # descNodeParam 
    [[   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [ 139.245    5.99   142.968   17.17     0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.     190.001 -168.226    0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.     190.001    0.     190.101]
     [   0.       0.       0.     254.001   -2.5      2.5  ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]
     [   0.       0.       0.       0.       0.       0.   ]]


    b.node[15746:15746+15].reshape(-1,16)[:,8:14] # descNodeBB 
    [[  -0.      -0.      -0.       0.       0.       0.   ]
     [  -0.      -0.      -0.       0.       0.       0.   ]
     [-142.968 -142.968 -173.226  142.968  142.968 -162.045]
     [  -0.      -0.      -0.       0.       0.       0.   ]
     [-254.001 -254.001 -173.226  254.001  254.001   -5.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-254.001 -254.001    0.     254.001  254.001  190.101]
     [-254.001 -254.001   -5.     254.001  254.001    0.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]
     [-100.    -100.    -100.     100.     100.     100.   ]]
    b.node[15746:15746+15].reshape(-1,16).view(np.int32)[:,6:8] # descNodeBoundaryIndex 
    [[   27 15746]
     [   27 15747]
     [   27 15748]
     [   27 15749]
     [   27 15750]
     [   27 15751]
     [   27 15752]
     [   27 15753]
     [   27 15754]
     [   27 15755]
     [   27 15756]
     [   27 15757]
     [   27 15758]
     [   27 15759]
     [   27 15760]]
    b.node[15746:15746+15].reshape(-1,16).view(np.int32)[:,14:16] # descNodeTCTran 
    [[   1    0]
     [   1    0]
     [ 108 7218]
     [   1    0]
     [ 103 7219]
     [   0    0]
     [   0    0]
     [ 103 7220]
     [ 105 7221]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]]
    b.node[15746:15746+15].reshape(-1,16).view(np.int32)[:,14:16] & 0x7ffffff  # descNodeTCTran 
    [[   1    0]
     [   1    0]
     [ 108 7218]
     [   1    0]
     [ 103 7219]
     [   0    0]
     [   0    0]
     [ 103 7220]
     [ 105 7221]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]
     [   0    0]]




