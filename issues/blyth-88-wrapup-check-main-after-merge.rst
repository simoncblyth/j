blyth-88-wrapup-check-main-after-merge
=========================================

issue 1 : need "bash junoenv offline-data" 
---------------------------------------------

::

    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /data/blyth/junotop/data/Simulation/DetSim
    junotoptask:PMTSimParamSvc.init_file_common_LPMT  INFO: Loading parameters from file: /data/blyth/junotop/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root
    Detaching after fork from child process 336876.
    junotoptask:PMTSimParamSvc.init_file_CD_SPMT  INFO: Loading parameters from file: /data/blyth/junotop/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_SPMT.root
    junotoptask:PMTSimParamSvc.init_file_common_LPMT ERROR: Can't find PMT parameters file ''.
    python: /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:173: void PMTSimParamSvc::init_all_pmtID_qe_scale(): Assertion `m_PmtTotal+m_PmtTotal_WP == int(pd_vector.size())' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 key


    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd3d19b99 in PMTSimParamSvc::init_all_pmtID_qe_scale (this=0x926b60)
        at /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:173
    #5  0x00007fffd3d196eb in PMTSimParamSvc::initialize (this=0x926b60)
        at /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:128
    #6  0x00007fffed573266 in DleSupervisor::initialize() ()


    (gdb) l
    168	void PMTSimParamSvc::init_all_pmtID_qe_scale()
    169	{
    170	    m_all_pmtID.clear();
    171	
    172	    // pd_vector will contain both CD-LPMT and WP-LPMT
    173	    assert( m_PmtTotal+m_PmtTotal_WP == int(pd_vector.size()) ); 
    174	
    175	    if (m_PmtTotal+m_PmtTotal_WP != int(pd_vector.size())) {
    176	        LogError << "Mismatch m_PmtTotal+m_PmtTotal_WP != int(pd_vector.size())." << std::endl;
    177	        LogError << " m_PmtTotal: " << m_PmtTotal << std::endl;
    (gdb) p m_PmtTotal
    $1 = (int &) @0x926d10: 17612
    (gdb) p m_PmtTotal_WP
    $2 = (int &) @0x926d34: 2400
    (gdb) p int(pd_vector.size())
    A syntax error in expression, near `pd_vector.size())'.
    (gdb) p pd_vector.size()
    $3 = 17612
    (gdb) 



::

     430 bool PMTSimParamSvc::init_file_CD_LPMT() {
     431     bool st = true;
     432 
     433     pd_vector.clear();
     434 
     435     init_file_common_LPMT(pd_vector,
     436                           m_PmtTotal, // CD-LPMT
     437                           kOFFSET_CD_LPMT,
     438                           m_db_path_CD_LPMT,
     439                           "/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root");
     440 
     441     return st;
     442 }

::

    epsilon:junotop blyth$ find . -name '*PMT.root'
    ./data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_SPMT.root
    ./data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root
    epsilon:junotop blyth$ 


    N[blyth@localhost junotop]$ find data -name '*PMT.root'
    data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root
    data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_SPMT.root
    data/Reconstruction/RecMuon/ConeMuonData/PDF_LPMT.root
    data/Reconstruction/RecMuon/ConeMuonData/PDF_SPMT.root
    N[blyth@localhost junotop]$ 



Need to "bash junoenv offline-data"::


    ==== junoenv-offline-data-checkout: checkout the code https://juno.ihep.ac.cn/svn/offline-data/trunk
    ==== junoenv-offline-data-checkout: svn co https://juno.ihep.ac.cn/svn/offline-data/trunk data
    A    data/Reconstruction/RecMuon/SphMuonData
    A    data/Reconstruction/RecMuon/SphMuonData/sph_muon_spline_300.root
    A    data/Reconstruction/RecMuon/SphMuonData/photons_spline_300.root
    A    data/Reconstruction/RecMuon/SphMuonData/pmt_distribution_20inch.dat
    A    data/Reconstruction/RecMuon/SphMuonData/pmt_distribution_3inch.dat
    A    data/Reconstruction/OMILREC/RecMap/nPEMap/nHEScaleFactor.txt
    A    data/Simulation/ElecSim/share/VFL_Threshold_Windows.txt
    A    data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_WP_LPMT.root
    U    data/Simulation/DetSim/Material/LS/ConstantProperty
    D    data/Generator/AtmNC/data/nuwro_nc_rfg1030_02.root
    D    data/Generator/AtmNC/data/nuwro_nc_rfg990withTEM_02.root
    D    data/Generator/AtmNC/data/genie_ncdata_02.root
    D    data/Generator/AtmNC/data/nuwro_nc_rfg1350_02.root
    D    data/Generator/AtmNC/data/nuwro_nc_sf990_02.root
    D    data/Generator/AtmNC/data/genie_ccdata.root
    D    data/Generator/AtmNC/data/genie3.0.2_atm.root
    D    data/Generator/AtmNC/data/nuwro_nc_rfg990_02.root
    D    data/Generator/NuAtm/data/tree_100000100.root
    Checked out revision 161.
    /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ bash junoenv offline-data


issue 2 : before switching to non-zero opticks mode need to rebuild
----------------------------------------------------------------------------

::

    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::initializeOpticks m_opticksMode 2 **NOT** WITH_G4CXOPTICKS 
    junotoptask:DetSim0Svc.initializeOpticks ERROR:  FATAL : non-zero opticksMode **NOT** WITH_G4CXOPTICKS 
    python: /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:315: bool DetSim0Svc::initializeOpticks(): Assertion `0' failed.



issue 3 : persisters need updating for PMT.h ?
-------------------------------------------------------

::

    [ 99%] Building CXX object Simulation/DetSimV2/DetSimOptions/CMakeFiles/DetSimOptions.dir/src/LSExpSteppingAction.cc.o
    [ 99%] Building CXX object Simulation/DetSimV2/DetSimOptions/CMakeFiles/DetSimOptions.dir/src/WaterPoolConstruction.cc.o
    In file included from /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc::
    /data/blyth/junotop/junosw/Detector/Geometry/Geometry/_PMTParamData.h: In member function 'void _PMTParamData::populate()':
    /data/blyth/junotop/junosw/Detector/Geometry/Geometry/_PMTParamData.h:31:15: error: 'kOFFSET_CD_SPMT' was not declared in this scope
         for(int i=kOFFSET_CD_SPMT ; i < kOFFSET_CD_SPMT_END ; i++) data.m_pmt_categories[i] = 5 ;
                   ^~~~~~~~~~~~~~~
    /data/blyth/junotop/junosw/Detector/Geometry/Geometry/_PMTParamData.h:31:37: error: 'kOFFSET_CD_SPMT_END' was not declared in this scope
         for(int i=kOFFSET_CD_SPMT ; i < kOFFSET_CD_SPMT_END ; i++) data.m_pmt_categories[i] = 5 ;
                                         ^~~~~~~~~~~~~~~~~~~
    gmake[2]: *** [Simulation/DetSimV2/DetSimOptions/CMakeFiles/DetSimOptions.dir/src/LS





issue 4 : hmm grab_evt is using GEOM starting with R for release, but are back to Debug
------------------------------------------------------------------------------------------

Fixed by adding auto determination of Debug,Release::

    detect_cmake_build_type()
    {
       : detect Debug or Release of last build by perl oneliner applied to build/CMakeCache.txt
       perl -ne 'm/CMAKE_BUILD_TYPE:STRING=(.*)/ && print $1' $JUNOTOP/junosw/build/CMakeCache.txt 
    }


* looks like grabbing far more than need too, or even the wrong dir ? 
* cleaned up the directories, dont need 10 event for quick input photon tests

::

    N[blyth@localhost ~]$ du -hs /tmp/blyth/opticks/GEOM/*
    55M	/tmp/blyth/opticks/GEOM/ntds2
    1.2G	/tmp/blyth/opticks/GEOM/R0J008
    1.2G	/tmp/blyth/opticks/GEOM/R1J008
    1.2G	/tmp/blyth/opticks/GEOM/V0J008
    1.2G	/tmp/blyth/opticks/GEOM/V1J008


Actually when GEOM not defined are populating that small dir::

    N[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/ntds2/ALL1/
    total 192
      0 drwxr-xr-x. 3 blyth blyth    109 May 31 22:34 .
      4 -rw-rw-r--. 1 blyth blyth    224 May 31 22:34 ntds2.tlog.npy
    168 -rw-rw-r--. 1 blyth blyth 170358 May 31 22:34 ntds2.tlog
      8 -rw-r--r--. 1 blyth blyth   4153 May 31 22:34 ntds2.log
      4 -rw-rw-r--. 1 blyth blyth     71 May 31 22:21 run_meta.txt
      4 -rw-rw-r--. 1 blyth blyth    132 May 31 22:21 run.npy
      4 drwxr-xr-x. 2 blyth blyth   4096 May 31 22:21 000
      0 drwxr-xr-x. 3 blyth blyth     18 May 31 22:21 ..
    N[blyth@localhost ~]$ date
    Wed May 31 23:43:06 CST 2023
    N[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/ntds2/ALL1/000/
    total 55728
        0 drwxr-xr-x. 3 blyth blyth      109 May 31 22:34 ..
        4 drwxr-xr-x. 2 blyth blyth     4096 May 31 22:21 .
        4 -rw-rw-r--. 1 blyth blyth      144 May 31 22:21 gs.npy


HMM: Better not to run without GEOM envvar defined for definiteness. 

::

    ntds2_cf()
    {
       : this function runs simulation with N:0 and N:1 geometries allowing comparison of histories
       : the logs are copied into event dir from TDS_LOG_COPYDIR setting by ntds 

       local evtmax=1
       export EVTMAX=${EVTMAX:-$evtmax}
       export NODBG=1

       local btype=$(detect_cmake_build_type)
       local gpfx=V          # V:Debug builds of junosw+custom4  
       case $btype in 
         Debug)   gpfx=V ;;    # V:Debug builds of junosw+custom4
         Release) gpfx=R ;;    # R:Release builds of junosw+custom4
       esac

       GPFX=${GPFX:-$gpfx}    # need to match with j/ntds/ntds.sh  AGEOM, BGEOM
       echo $BASH_SOURCE btype $btype gpfx $gpfx GPFX $GPFX

       N=0 GEOM=${GPFX}0J008 ntds2
       [ $? -ne 0 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 0 && return 1

       N=1 GEOM=${GPFX}1J008 ntds2
       [ $? -ne 1 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 1 && return 2

       return 0
    }




