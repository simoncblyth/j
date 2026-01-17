working_out_status : sequence of events
============================================


History
---------

Thu Jan 15 2026 : Evening
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Made opticks release v0.5.7 using standard addtag approach, that appeared to complete OK.


Fri Jan 16 2026 : Evening
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Workstation c4 was on branch v0.1.8_transient with::

    (ok) A[blyth@localhost customgeant4]$ git branch
    * main
      v0.1.8_transient

* see :doc:`recover_git_branch_mixup`

* this v0.1.8_transient intended to test a minor change ontop of v0.1.8 to
  remove the C4TrackInfo template allowing dynamic_caset interoperation


Sat Jan 17 : Afternoon
~~~~~~~~~~~~~~~~~~~~~~~

Investigating CI build fails, see that a non-standard and non-distributed external (Custom4) path 
was configured by the build that causes issue with CI OJ builds starting on Fri 16th.
Added protection to prevent this mistake happening again, see:

* ~/opticks/notes/issues/okdist-did-not-check-for-non-distributable-paths-leading-to-broken-OJ-build.rst


How to proceed ? Options below. Decided on 1.

1. return to prefix_default and make a new Opticks release v0.5.8 based off the old default Custom4 0.1.8?  
   Suspect that will fail from template C4TrackInfo having different definitions
   in different places ? 

   * YES, it did : so added WITH_CUSTOM4_OLD block prior to WITH_CUSTOM4 that 
     handles the templated C4TrackInfo

2. make a new Custom4 0.1.9 with just the template change

   * HMM : Thats not practical just before a week of travel




Sat Jan 17 : Evening
~~~~~~~~~~~~~~~~~~~~~~~

* made new Opticks release v0.5.8
* a MR gitlab build succeeds


Investigations
--------------


Looking for clues in branches
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Not sure this is it, but its related::

    A[blyth@localhost junosw]$ git switch blyth-NormalTrackInfo-C4Pho-label-Opticks-integration
    Switched to branch 'blyth-NormalTrackInfo-C4Pho-label-Opticks-integration'
    Your branch is up to date with 'origin/blyth-NormalTrackInfo-C4Pho-label-Opticks-integration'.
    A[blyth@localhost junosw]$ git l -n4
    commit 22ee7520d9f22046aacc6c07e4cb0e92e102e480 (HEAD -> blyth-NormalTrackInfo-C4Pho-label-Opticks-integration, origin/blyth-NormalTrackInfo-C4Pho-label-Opticks-integration)
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Sat Jun 7 16:40:23 2025 +0800

        changing NormalTrackInfo has difficulties, so defer the spearate label approach

    M       Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
    M       Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc


::

    +
    +#ifdef WITH_NORMAL_LABEL
    +void U4RecorderAnaMgr::PreUserTrackingAction( const G4Track* trk) { m_recorder->PreUserTrackingAction_(  trk, LabelData(trk)); }
    +void U4RecorderAnaMgr::PostUserTrackingAction(const G4Track* trk) { m_recorder->PostUserTrackingAction_( trk, LabelData(trk)); }
    +#else
    +void U4RecorderAnaMgr::PreUserTrackingAction( const G4Track* trk) { m_recorder->PreUserTrackingAction(  trk ); }
    +void U4RecorderAnaMgr::PostUserTrackingAction(const G4Track* trk) { m_recorder->PostUserTrackingAction( trk ); }
    +#endif
    +
    +
     void U4RecorderAnaMgr::UserSteppingAction(const G4Step* step) {     m_recorder->UserSteppingAction(step);    }
    +
    +int* U4RecorderAnaMgr::LabelData( const G4Track* trk )  // static
    +{
    +#ifdef WITH_NORMAL_LABEL
    +    NormalTrackInfo* ui = (NormalTrackInfo*)(trk->GetUserInformation());
    +    int* label_data =  ui ? ui->getLabelData() : nullptr ;
    +#else
    +    int* label_data = nullptr ; 
    +#endif
    +    return label_data ;
    +}
    +
     #else
     void U4RecorderAnaMgr::BeginOfRunAction(const G4Run* ) {}
     void U4RecorderAnaMgr::EndOfRunAction(const G4Run* ) {}
    @@ -45,5 +70,9 @@ void U4RecorderAnaMgr::EndOfEventAction(const G4Event* ) {}
     void U4RecorderAnaMgr::PreUserTrackingAction(const G4Track* ) {}
     void U4RecorderAnaMgr::PostUserTrackingAction(const G4Track* ) {}
     void U4RecorderAnaMgr::UserSteppingAction(const G4Step* ) {}
    +int* U4RecorderAnaMgr::LabelData( const G4Track* trk ){ return nullptr ; }
    +



Where c4 is configured
-----------------------


::

    150 local_c4_prefix_default()
    151 {
    152     : default path from cvmfs
    153     echo /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8
    154 }
    155 local_c4_prefix()
    156 {
    157     : function that enables switching to a non default c4 to check
    158     : SEE NOTES AT HEAD ABOUT THE ORDER OF BUILD OPERATIONS WHEN CHANGING C4 PREFIX
    159 
    160     #echo $(local_c4_prefix_default)
    161     echo /data1/blyth/local/custom4_Debug/0.1.8
    162 }
    163 
    164 local_c4_build()
    165 {
    166    : ~/local.sh
    167    : setup externals needed to c4_build
    168    : using J25.4.0 standard versions of externals copied from JUNOTOP/bashrc.sh
    169    : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/bashrc.sh
    170    
    171    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Xercesc/3.2.4/bashrc
    172    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/CLHEP/2.4.7.1/bashrc
    173    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/bashrc
    174    
    175    if [ "$(local_c4_prefix)" == "$(local_c4_prefix_default)" ]; then
    176        c4_build()
    177        {
    178           : ~/local.sh
    179           echo $BASH_SOURCE $FUNCNAME - NO BUILD NEEDED AS PREFIX IS DEFAULT
    180           local ff="local_c4_prefix local_c4_prefix_default"
    181           for f in $ff ; do printf "%30s : %s\n" "$f" $(eval $f) ; done
    182        }  
    183    else
    184        c4_build()
    185        {
    186           : ~/local.sh
    187           : NB returned v0.1.8 in transient branch with
    188           :      git checkout -b v0.1.8_transient v0.1.8
    189           
    190           echo $BASH_SOURCE $FUNCNAME - BUILD NEEDED AS PREFIX IS NOT DEFAULT
    191           local ff="local_c4_prefix local_c4_prefix_default"
    192           for f in $ff ; do printf "%30s : %s\n" "$f" $(eval $f) ; done
    193 
    194           cd $HOME/customgeant4
    195           export CUSTOM4_PREFIX=$(local_c4_prefix)
    196           ./build_Debug.sh
    197 
    198           source ~/j/JUNOTOP/JUNOTOP_generate_custom4_bashrc.sh
    199           JUNOTOP_generate_custom4_bashrc > ${CUSTOM4_PREFIX}/bashrc
    200        }
    201    fi
    202    type c4_build
    203 }  



Build order : C4 OK OJ
-----------------------


Advice on build order from ~/j/local.sh::

    Do each of the below setup and build in separate clean tabs:

    1. local_c4_build ; c4_build   ## does nothing when using default c4 v0.1.8
    2. local_ok_build ; ok_build   ## 

       * HMM: AFTER CHANGING C4 prefix an om-cleaninstall is needed

    3. local_oj_build ; NOINIT=1 OJ_BUILD_CLEAN=1 oj_build

    #4. local_oj_init  ; oj_init  ## THIS IS NOW PART OF oj_build THAT IS OFTEN DISABLED WITH NOINIT




Update Opticks to work with newer Custom4 eg v0.1.8_transient as well as the old default v0.1.8 : using WITH_CUSTOM4_OLD
----------------------------------------------------------------------------------------------------------------------------

Default Custom4 v0.1.8 has templated C4TrackInfo, causing opticks/u4 compilation fail::

    [ 17%] Building CXX object CMakeFiles/U4.dir/Local_DsG4Scintillation.cc.o
    [ 17%] Building CXX object CMakeFiles/U4.dir/Local_G4Cerenkov_modified.cc.o
    [ 18%] Building CXX object CMakeFiles/U4.dir/ShimG4OpRayleigh.cc.o
    [ 19%] Building CXX object CMakeFiles/U4.dir/U4Physics.cc.o
    /home/blyth/opticks/u4/U4.cc: In static member function ‘static void U4::GenPhotonAncestor(const G4Track*)’:
    /home/blyth/opticks/u4/U4.cc:346:16: error: ‘template<class T> struct C4TrackInfo’ used without template arguments
      346 |     ancestor = C4TrackInfo::Get(aTrack) ;
          |                ^~~~~~~~~~~
    compilation terminated due to -fmax-errors=1.
    make[2]: *** [CMakeFiles/U4.dir/build.make:90: CMakeFiles/U4.dir/U4.cc.o] Error 1
    make[2]: *** Waiting for unfinished jobs....
    In file included from /home/blyth/opticks/u4/U4Recorder.cc:41:
    /home/blyth/opticks/u4/U4Track.h: In static member function ‘static void U4Track::SetFabricatedLabel(const G4Track*)’:
    /home/blyth/opticks/u4/U4Track.h:103:21: error: qualified-id in declaration before ‘(’ token
      103 |     C4TrackInfo::Set(_track, fab );
          |                     ^
    compilation terminated due to -fmax-errors=1.
    make[2]: *** [CMakeFiles/U4.dir/build.make:160: CMakeFiles/U4.dir/U4Recorder.cc.o] Error 1
    make[1]: *** [CMakeFiles/Makefile2:934: CMakeFiles/U4.dir/all] Error 2
    make: *** [Makefile:146: all] Error 2
    === om-one-or-all cleaninstall : non-zero rc 2
    === om-all om-cleaninstall : ERROR bdir /data1/blyth/local/opticks_Debug/build/u4 : non-zero rc 2
    === om-one-or-all cleaninstall : non-zero rc 2
    A[blyth@localhost opticks]$ 




::

    (ok) A[blyth@localhost u4]$ git lg U4.cc
    * 2025-11-25 f500ae3e3 - change STrackInfo to not be templated, and adapt for C4TrackInfo that does the same : as the templating forces static_cast which is unsafe for general use (8 weeks ago) <Simon C Blyth>
    * 2025-09-22 ba6752fb7 - review genstep collection and hit handling, conclude that forming sensor frame local hits should happen on client side to avoid doubling hit size (4 months ago) <Simon C Blyth>
    * 2025-06-24 440241054 - within WITH_CUSTOM4 try using SPMT qe to replace SD:SURFACE_DETECT with EC:EFFICIENCY_COLLECT/EX:EFFICIENCY_CULL, but currently getting 25% more EC than B side (7 months ago) <Simon C Blyth>
    * 2024-12-11 166ef01e5 - arrange curand state usage to almost always use RNG, remove old s_mock_curand.h, instead adopt : using RNG = curandStateWhatever : approach (1 year, 1 month ago) <Simon C Blyth>
    * 2023-12-08 7a50cdc76 - re-express quad6 gs to scerenkov/sscint casting via a pointer to avoid strict aliasing warnings from Release build (2 years, 1 month ago) <Simon C Blyth>
    * 2023-12-08 d18c2c64a - remove more Release warnings (2 years, 1 month ago) <Simon C Blyth>





Opticks/U4 add WITH_CUSTOM4_OLD
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    215 if(Custom4_FOUND)
    216     target_link_libraries(${name} PUBLIC Custom4::Custom4)
    217     target_compile_definitions(${name} PRIVATE WITH_CUSTOM4)
    218 
    219     set(Custom4_VERSION_TRANSITION "0.1.8")
    220     if(Custom4_VERSION VERSION_LESS_EQUAL ${Custom4_VERSION_TRANSITION})
    221         target_compile_definitions(${name} PRIVATE WITH_CUSTOM4_OLD)
    222         message(STATUS "${name}: Custom4 version ${Custom4_VERSION} <= ${Custom4_VERSION_TRANSITION}, adding WITH_CUSTOM4_OLD")
    223     else()
    224         message(STATUS "${name}: Custom4 version NOT: ${Custom4_VERSION} <= ${Custom4_VERSION_TRANSITION}, NOT:adding WITH_CUSTOM4_OLD")
    225     endif()
    226 endif()
    227 



Opticks WITH_CUSTOM4
~~~~~~~~~~~~~~~~~~~~~~

::


    (ok) A[blyth@localhost opticks]$ opticks-fl WITH_CUSTOM4
    ./CSGOptiX/CMakeLists.txt

        107 if(Custom4_FOUND)
        108    list(APPEND CSGOptiX_COMPILE_DEFINITIONS_PUBLIC WITH_CUSTOM4)
        109 endif()


    ./CSGOptiX/CSGOptiX.cc

         293 void CSGOptiX::InitMeta()
         294 {
         295     std::string gm = SEventConfig::GetGPUMeta() ;     // (QSim) scontext sdevice::brief
         296     SEvt::SetRunMetaString("GPUMeta", gm.c_str() );  // set CUDA_VISIBLE_DEVICES to control
         297 
         298     std::string switches = QSim::Switches() ;
         299     SEvt::SetRunMetaString("QSim__Switches", switches.c_str() );
         300 
         301 #ifdef WITH_CUSTOM4
         302     std::string c4 = "TBD" ; //C4Version::Version(); // octal version number bug in Custom4 v0.1.8 : so skip the version metadata
         303     SEvt::SetRunMetaString("C4Version", c4.c_str());
         304 #else
         305     SEvt::SetRunMetaString("C4Version", "NOT-WITH_CUSTOM4" );
         306 #endif
         307 
         308 }



    ./examples/UseCustom4/UseCustom4.cc
    ./qudarap/QPMT_MOCK.h
    ./qudarap/QSim__Desc.sh
    ./qudarap/tests/QPMT_MockTest.sh
    ./qudarap/tests/QPMT_Test.sh
    ./qudarap/tests/QSim_MockTest.cc
    ./qudarap/tests/QSim_MockTest.sh
    ./qudarap/CMakeLists.txt
    ./qudarap/QPMT.cu
    ./qudarap/qpmt.h
    ./qudarap/QPMT.cc
    ./qudarap/qsim.h
    ./qudarap/QSim.cc

          WITH_CUSTOM4 WHEELS IN LOTS OF METHODS      

    ./sysrap/CMakeLists.txt
    ./sysrap/SPMT.h
    ./sysrap/SPMTAccessor.h
    ./sysrap/ssys.h
    ./sysrap/sbuild.h
    ./sysrap/ssys__Desc.sh
    ./sysrap/tests/SPMTAccessor_test.sh
    ./sysrap/tests/sreport.py
    ./sysrap/tests/SPMT_test.sh



    ./u4/U4Track.h
    ./u4/InstrumentedG4OpBoundaryProcess.cc
    ./u4/U4OpBoundaryProcess.h
    ./u4/U4PMTAccessor.h
    ./u4/U4StepPoint.cc
    ./u4/U4Physics.cc
    ./u4/U4Recorder.cc
    ./u4/tests/U4Custom4Test.cc
    ./u4/CMakeLists.txt
    ./u4/U4.cc



    (ok) A[blyth@localhost opticks]$ 
       


