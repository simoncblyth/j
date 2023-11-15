FIXED : jok-tds-flag-zeros-at-PMT-special-surface-from-missing-WITH_CUSTOM4
============================================================================

Overview
----------

Recent change to avoid qudarap depending on custom4 lib (and all Geant4 libs) 
as just need a single header : had accidental effect of missing the WITH_CUSTOM4 
defininition causing this flag zero issue. 


Issue : qsim.h history has spaces corresponding to flag zeros
----------------------------------------------------------------

N::

     N 
     jre
     jok-tds


Spaced out history issue::

    QCF qcf :  
    a.q 1000000 b.q 1000000 lim slice(None, None, None) 
    c2sum : 1772472.8750 c2n :  2113.0000 c2per:   838.8419  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  1772472.88/2113:838.842 (30) pv[0.00,< 0.05 : NOT:null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SD                                                                              ' ' 0' '     0 331327' '331327.0000' '    -1      1']
     [' 1' 'TO BT BT BT BT SA                                                                              ' ' 1' '     0 281937' '281937.0000' '    -1      2']
     [' 2' 'TO BT BT BT BT    SA                                                                           ' ' 2' '187448      0' '187448.0000' '     4     -1']
     [' 3' 'TO BT BT BT BT    SR SA                                                                        ' ' 3' ' 75719      0' '75719.0000' '    20     -1']
     [' 4' 'TO BT BT BT BT BT SR SA                                                                        ' ' 4' '     0  62886' '62886.0000' '    -1 103703']
     [' 5' 'TO BT BT BT BT    SR    BT BT BT BT BT BT AB                                                   ' ' 5' ' 62442      0' '62442.0000' '120824     -1']
     [' 6' 'TO BT BT BT BT BT SA                                                                           ' ' 6' '     0  46679' '46679.0039' '    -1  84186']
     [' 7' 'TO BT BT BT BT    SR    BT BT BT BT AB                                                         ' ' 7' ' 22410      0' '22410.0000' '121428     -1']
     [' 8' 'TO BT BT BT BT    SR    BT BT BT BT BT BT SC AB                                                ' ' 8' ' 19747      0' '19747.0000' '139242     -1']
     [' 9' 'TO BT BT BT BT    SR SR SA                                                                     ' ' 9' ' 15680      0' '15680.0000' '     6     -1']
     ['10' 'TO BT BT BT BT BT SR BR SR SA                                                                  ' '10' '     0  11901' '11901.0010' '    -1 209894']


::

    In [7]: a.q[:10]
    Out[7]: 
    array([[b'TO BT BT BT BR BT BT BT BT SA                                                                   '],
           [b'TO BT BT BT BT    SR SR SR SR SR    BT BT BT BT BT BT SC BT BT BT BT BT BT    SR SR SR    BT BT '],
           [b'TO BT BT BR BT BT BT SA                                                                         '],
           [b'TO BT BT BT BR BT BT BT BT SA                                                                   '],
           [b'TO BT BT BT BT    SA                                                                            '],
           [b'TO BT BT BR BT BT BT SA                                                                         '],
           [b'TO BT BT BT BT    SR SR SA                                                                      '],
           [b'TO BT BT BT BR BR BT    SR SR SR SR    BT BT BT BT BT BT SC BT BT BT BT BT BT    SR    BT BT BT '],
           [b'TO BT BT BT BT    SR SR SA                                                                      '],
           [b'TO BT BT BT BT    SR SR SR SR SR    BT BR BT       BR       BR       BT BR BT    SR SR SA       ']], dtype='|S96')


    In [12]: a.f.record[4,:7,0]
    Out[12]:
    array([[-3191.862, 10522.16 , 15746.497,     0.1  ],
           [-3211.837, 10588.01 , 15847.825,     0.665],
           [-3219.135, 10612.065, 15884.841,     0.871],
           [-3220.854, 10617.735, 15898.214,     0.946],
           [-3222.139, 10621.969, 15904.019,     0.98 ],
           [-3223.488, 10626.416, 15914.526,     1.038],
           [-3235.901, 10667.338, 16011.216,     1.391]], dtype=float32)

    In [13]: a.q[4]
    Out[13]: array([b'TO BT BT BT BT    SA                                                                            '], dtype='|S96')

    In [15]: a.f.record[4,:7,3].view(np.int32)
    Out[15]:
    array([[       4096,           0,           0,        4096],
           [    6817792,        1426, -2147483648,        6144],
           [    6883328,        1426, -2147483648,        6144],
           [    6883328,        1426,           0,        6144],
           [    7014400,        1426, -2147483648,        6144],
           [    7667712,        1426, -2147483648,        6144],
           [    7667840,        1426,           0,        6272]], dtype=int32)

::

    sphoton.h
    ============

    +----+----------------+----------------+----------------+----------------+--------------------------+
    | q  |      x         |      y         |     z          |      w         |  notes                   |
    +====+================+================+================+================+==========================+
    |    |  pos.x         |  pos.y         |  pos.z         |  time          |                          |
    | q0 |                |                |                |                |                          |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    |  mom.x         |  mom.y         | mom.z          |  iindex        |                          |
    | q1 |                |                |                | (unsigned)     |                          |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    |  pol.x         |  pol.y         |  pol.z         |  wavelength    |                          |
    | q2 |                |                |                |                |                          |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    | boundary_flag  |  identity      |  orient_idx    |  flagmask      |  (unsigned)              |
    | q3 | (3,0)          |                |  orient:1bit   |                |                          |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+



    In [16]: a.f.record[4,:7,3,0].view(np.int32) >> 16
    Out[16]: array([  0, 104, 105, 105, 107, 117, 117], dtype=int32)        ## boundary 

    In [22]: cf.bdn.shape
    Out[22]: (131,)

    In [25]: cf.bdn[104]
    Out[25]: 'Water///Water'

    In [26]: cf.bdn[105]
    Out[26]: 'Water///AcrylicMask'

    In [24]: cf.bdn[107]
    Out[24]: 'Water///Pyrex'

    In [23]: cf.bdn[117]
    Out[23]: 'Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/Vacuum'


    In [17]: a.f.record[4,:7,3,0].view(np.int32) & 0xffff
    Out[17]: array([4096, 2048, 2048, 2048, 2048,    0,  128], dtype=int32)  ## flag
    ##                                              ## FLAG ZERO 


::

    epsilon:opticks blyth$ qu
    /Users/blyth/opticks/qudarap
    epsilon:qudarap blyth$ opticks-fh set_flag 
    ./qcerenkov.h:    p.set_flag(CERENKOV) ;
    ./qscint.h:    p.set_flag(SCINTILLATION) ;

    ./qsim.h:    p.set_flag(TORCH); 
    ./qsim.h:    p.set_flag(TORCH);  // setting initial flag : in reality this should be done by generation

    ./qsim.h:    ctx.p.set_flag(flag);   

    ./qsim.h:        case OpticksGenstep_INPUT_PHOTON:    { p = evt->photon[photon_id] ; p.set_flag(TORCH) ; }        ; break ;        

    ./QSim.cu:    ctx.p.set_flag(flag); 

    epsilon:qudarap blyth$ 


That flag is set at the tail of qsim::propagate so need PIDX debug to see 
whats going down. 

PIDX dumping::

    N[blyth@localhost ~]$ PIDX=4 jok-tds

    //qsim.propagate.head idx 4 : bnc 4 cosTheta -0.39930016 
    //qsim.propagate.head idx 4 : mom = np.array([-0.11741339,0.38706133,0.91454768]) ; lmom = 0.99999988  
    //qsim.propagate.head idx 4 : pos = np.array([-3222.13867,10621.96875,15904.01855]) ; lpos = 19394.48828125 
    //qsim.propagate.head idx 4 : nrm = np.array([(-0.19651425,0.64781749,-0.73601264]) ; lnrm = 0.99999994  
    //qsim.propagate_to_boundary.head idx 4 : u_absorption 0.47640604 logf(u_absorption) -0.74148464 absorption_length  1687.2012 absorption_distance 1251.033813 
    //qsim.propagate_to_boundary.head idx 4 : post = np.array([-3222.13867,10621.96875,15904.01855,   0.98008]) 
    //qsim.propagate_to_boundary.head idx 4 : distance_to_boundary    11.4896 absorption_distance  1251.0338 scattering_distance 93758078976.0000 
    //qsim.propagate_to_boundary.head idx 4 : u_scattering     0.9105 u_absorption     0.4764 
    //qsim.propagate_to_boundary.tail.SAIL idx 4 : post = np.array([-3223.48779,10626.41602,15914.52637,   1.03841]) ;  sail_time_delta =    0.05833   
    //qsim.propagate idx 4 bounce 4 command 3 flag 0 s.optical.x 38 s.optical.y 4 
    //qsim.propagate.NOT:WITH_CUSTOM4 idx 4 BOUNDARY ems 4 lposcost   0.120 

    //qsim.propagate.head idx 4 : bnc 5 cosTheta 0.37537837 
    //qsim.propagate.head idx 4 : mom = np.array([-0.11741339,0.38706133,0.91454768]) ; lmom = 0.99999988  
    //qsim.propagate.head idx 4 : pos = np.array([-3223.48779,10626.41602,15914.52637]) ; lpos = 19405.76562500 
    //qsim.propagate.head idx 4 : nrm = np.array([(-0.29014045,0.95646232,-0.03159767]) ; lnrm = 1.00000000  
    //qsim.propagate_to_boundary.head idx 4 : u_absorption 0.77081919 logf(u_absorption) -0.26030141 absorption_length 1000000000.0000 absorption_distance 260301408.000000 
    //qsim.propagate_to_boundary.head idx 4 : post = np.array([-3223.48779,10626.41602,15914.52637,   1.03841]) 
    //qsim.propagate_to_boundary.head idx 4 : distance_to_boundary   105.7234 absorption_distance 260301408.0000 scattering_distance 2386616385536.0000 
    //qsim.propagate_to_boundary.head idx 4 : u_scattering     0.0919 u_absorption     0.7708 
    //qsim.propagate_to_boundary.tail.SAIL idx 4 : post = np.array([-3235.90112,10667.33789,16011.21582,   1.39107]) ;  sail_time_delta =    0.35266   
    //qsim.propagate idx 4 bounce 5 command 3 flag 0 s.optical.x 38 s.optical.y 4 
    //qsim.propagate.NOT:WITH_CUSTOM4 idx 4 BOUNDARY ems 4 lposcost  -0.311 
    //qsim.propagate (lposcost < 0.f) idx 4 bounce 5 command 3 flag 0 ems 4 
    //qsim.propagate_at_surface.SA/SD.BREAK idx 4 : flag 128 


Checking paths custom4 is there to some extent. Why not felt by qsim.h ?::

    N[blyth@localhost opticks]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/lib64/
    total 103
      1 drwxr-xr-x. 3 cvmfs cvmfs     60 Nov  6 22:15 .
      1 drwxr-xr-x. 4 cvmfs cvmfs     82 Nov  6 22:15 ..
      1 drwxr-xr-x. 2 cvmfs cvmfs     79 Nov  6 22:15 Custom4-0.1.8
    102 -rwxr-xr-x. 1 cvmfs cvmfs 103784 Nov  6 22:15 libCustom4.so
    N[blyth@localhost opticks]$ 


At CMake level it looks like Custom4 is found::

    N[blyth@localhost qudarap]$ touch CMakeLists.txt 
    N[blyth@localhost qudarap]$ om


    -- Custom4_VERBOSE       : ON 
    -- Custom4_FOUND         : YES 
    -- Custom4_VERSION       : 0.1.8 
    -- Custom4_PREFIX        : /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8 
    -- Custom4_INCLUDE_DIR   : /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/include/Custom4 
    -- Custom4_INCLUDE_DIRS  : /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/include/Custom4 
    -- Custom4_CFLAGS        : -I/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/include/Custom4 
    -- Custom4_DEFINITIONS   : -DWITH_CUSTOM4 
    -- Custom4_LIBRARY_DIR   : /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/lib64 
    -- Custom4_LIBRARY_PATH  : /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so 
    -- Custom4_LIBRARIES     : -L/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4 
    -- Custom4_CMAKE_PATH    : /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4Config.cmake 
    -- Custom4_CMAKE_DIR     : /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8 
    -- QUDARap Custom4_FOUND:1  


But at runtime its not there::

    2023-11-15 10:08:38.208 INFO  [424870] [G4CXOpticks::setGeometry@254] CSGOptiX::Desc Version 7 PTXNAME CSGOptiX7 GEO_PTXNAME - NOT:WITH_CUSTOM4 



CONFIRMED : Possible cause in quadrap/CMakeLists.txt::

    178 #[=[
    179 As QUDARap only requires a single header-only header from Custom4,
    180 not the library it is unnecessarily adding dependency on the lib and 
    181 all the Geant4 libs when hooking up the full target with::
    182 
    183    # set(LIBS ${LIBS} Custom4::Custom4) 
    184 
    185 So instead just hookup the include_directories and 
    186 compile_definitions not the full target. 
    187 #]=]
    188 
    189 if(Custom4_FOUND)
    190    target_compile_definitions( ${name} PUBLIC WITH_CUSTOM4 )
    191    target_include_directories( ${name} PUBLIC ${Custom4_INCLUDE_DIR})
    192 endif()



::

    epsilon:opticks blyth$ o
    On branch master
    Your branch is up-to-date with 'origin/master'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   CSGOptiX/CSGOptiX.cc
        modified:   CSGOptiX/tests/CMakeLists.txt
        modified:   qudarap/CMakeLists.txt
        modified:   qudarap/QSim.cc
        modified:   qudarap/QSim.hh
        modified:   qudarap/tests/CMakeLists.txt

    Untracked files:
      (use "git add <file>..." to include in what will be committed)

        CSGOptiX/tests/CSGOptiXDescTest.cc
        qudarap/tests/QSimDescTest.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:opticks blyth$ git add . 
    epsilon:opticks blyth$ git commit -m "possible fix for unexpected lack of WITH_CUSTOM4 in opticks build that just needs single header-only header from optional Custom4"
    [master 8eecad750] possible fix for unexpected lack of WITH_CUSTOM4 in opticks build that just needs single header-only header from optional Custom4
     8 files changed, 62 insertions(+), 9 deletions(-)
     create mode 100644 CSGOptiX/tests/CSGOptiXDescTest.cc
     create mode 100644 qudarap/tests/QSimDescTest.cc
    epsilon:opticks blyth$ git push 
    Connection to bitbucket.org port 22 [tcp/ssh] succeeded!
    Counting objects: 14, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (14/14), done.
    Writing objects: 100% (14/14), 2.59 KiB | 2.59 MiB/s, done.
    Total 14 (delta 10), reused 0 (delta 0)
    To bitbucket.org:simoncblyth/opticks.git
       157415f2d..8eecad750  master -> master
    epsilon:opticks blyth$ 




Thrust warning::

    -- Build files have been written to: /data/blyth/junotop/ExternalLibs/opticks/head/build/CSGOptiX
    [  5%] Building NVCC ptx file CSGOptiX_generated_Check.cu.ptx
    [  5%] Building NVCC ptx file CSGOptiX_generated_CSGOptiX7.cu.ptx
    In file included from /usr/local/cuda-11.7/include/thrust/detail/config/config.h:27,
                     from /usr/local/cuda-11.7/include/thrust/detail/config.h:23,
                     from /usr/local/cuda-11.7/include/thrust/complex.h:24,
                     from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/include/Custom4/C4MultiLayrStack.h:59,
                     from /data/blyth/junotop/ExternalLibs/opticks/head/include/QUDARap/qpmt.h:29,
                     from /data/blyth/junotop/ExternalLibs/opticks/head/include/QUDARap/qsim.h:66,
                     from /data/blyth/junotop/opticks/CSGOptiX/CSGOptiX7.cu:70:
    /usr/local/cuda-11.7/include/thrust/detail/config/cpp_dialect.h:131:13: warning: Thrust requires at least C++14. C++11 is deprecated but still supported. C++11 support will be removed in a future release. Define THRUST_IGNORE_DEPRECATED_CPP_DIALECT to suppress this message.
      131 |      THRUST_COMPILER_DEPRECATION_SOFT(C++14, C++11);
          |             ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                                                                                                                                           


