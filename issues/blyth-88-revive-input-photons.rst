blyth-88-revive-input-photons
================================


revive input photons
----------------------

old tds3::

    4129 
    4130    local input_photon_path=${INPUT_PHOTON_PATH}
    4131    local input_photon_repeat=${INPUT_PHOTON_REPEAT}
    4132    local input_photon_wavelength=${INPUT_PHOTON_WAVELENGTH}
    4133 
    4134    local trgs=""
    4135    if [ -n "${input_photon_path}" -a -f "${input_photon_path}" ]; then
    4136        trgs="$trgs opticks --input-photon-path ${input_photon_path}"
    4137        if [ -n "${input_photon_repeat}" ]; then
    4138            trgs="$trgs --input-photon-repeat ${input_photon_repeat}"
    4139        fi
    4140        if [ -n "${input_photon_wavelength}" ]; then
    4141            trgs="$trgs --input-photon-wavelength ${input_photon_wavelength}"
    4142        fi
    4143    else
    4144        trgs="$trgs gun"
    4145    fi
    4146 


jcv JUNODetSimModule::

    0796     def register_subparser_opticks(self, subparsers, base_parser_positioner):
     797         parser_opticks = subparsers.add_parser("opticks", help="opticks debugging generator", parents=[base_parser_positioner])
     798         parser_opticks.add_argument("--input-photon-path", default=None,
     799                                 help="path to Opticks format input photons in NumPy .npy files."
     800                                      " Used for Opticks debugging, requires compilation WITH_G4OPTICKS" )
     801         parser_opticks.add_argument("--input-photon-repeat", default=0, type=int,
     802                                 help="number of times to repeat the input photons, >0 for outer repeat of entire array, <0 for inner repeat of each phot     on. "
     803                                      " Used for Opticks debugging, requires compilation WITH_G4OPTICKS" )
     804         parser_opticks.add_argument("--input-photon-wavelength", default=None, type=str,
     805                                 help="comma delimited list of override wavelengths in nm that are modulo repeated when using --input-photon-repeat "
     806                                      " Used for Opticks debugging, requires compilation WITH_G4OPTICKS" )
     807 
     808 


    1316     def setup_generator_opticks(self, task, args):
    1317         import GenTools
    1318         gt = task.createAlg("GenTools")
    1319         ok = gt.createTool("GtOpticksTool/ok")
    1320         import os.path
    1321         path = os.path.expandvars(os.path.expanduser(args.input_photon_path))
    1322         repeat = args.input_photon_repeat
    1323         wavelength = args.input_photon_wavelength
    1324         objName = ok.objName()
    1325         log.info("setting inputPhotonPath:%s objName:%s repeat:%d wavelength:%s " % (path, objName, repeat, wavelength) )
    1326         if os.path.exists(path):
    1327             ok.property("inputPhotonPath").set(path)
    1328             ok.property("inputPhotonRepeat").set(repeat)
    1329             ok.property("inputPhotonWavelength").set(wavelength)
    1330         else:
    1331             log.fatal("input_photon_path:%s DOES NOT EXIST " % path )
    1332         pass
    1333         gt.property("GenToolNames").set([objName])
    1334 


jcv GtOpticksTool::

    118 #if  (defined WITH_G4CXOPTICKS) || (defined WITH_G4OPTICKS)
    119 void GtOpticksTool::add_optical_photon(HepMC::GenEvent& event, unsigned idx, unsigned override_wavelength_nm, bool dump )
    120 {
    121 #ifdef WITH_G4CXOPTICKS
    122     LOG(info) << " WITH_G4CXOPTICKS event.event_number " << event.event_number() ;
    123     sphoton p ;
    124     sphoton::Get(p, m_input_photons, idx );
    125     HepMC::GenVertex* vertex = new HepMC::GenVertex(HepMC::FourVector(p.pos.x,p.pos.y,p.pos.z,p.time));
    126     G4double wavelength_nm = override_wavelength_nm > 0u ? double(override_wavelength_nm) : double(p.wavelength)  ;
    127 #elif WITH_G4OPTICKS
        

No transforming of photons in GtOpticksTool, so the input photons must be pre-transformed into global frame. 
Thats a pain::

    epsilon:issues blyth$ cd ~/.opticks/InputPhotons/
    epsilon:InputPhotons blyth$ l
    total 42080
        0 drwxr-xr-x  18 blyth  staff       576 Feb  6 17:13 ..
        8 -rw-r--r--   1 blyth  staff        77 Jul 16  2022 DownXZ1000_f8.json
        0 drwxr-xr-x  66 blyth  staff      2112 Jul 16  2022 .
      256 -rw-r--r--   1 blyth  staff    128128 Jul 16  2022 DownXZ1000_f8.npy
        8 -rw-r--r--   1 blyth  staff        77 Jul 16  2022 DownXZ1000_f4.json
      128 -rw-r--r--   1 blyth  staff     64128 Jul 16  2022 DownXZ1000_f4.npy
        0 drwxr-xr-x   3 blyth  staff        96 Jul 16  2022 storch
        8 -rw-r--r--   1 blyth  staff        75 Jul 16  2022 UpXZ1000_f8.json
      256 -rw-r--r--   1 blyth  staff    128128 Jul 16  2022 UpXZ1000_f8.npy
        8 -rw-r--r--   1 blyth  staff        75 Jul 16  2022 UpXZ1000_f4.json
      128 -rw-r--r--   1 blyth  staff     64128 Jul 16  2022 UpXZ1000_f4.npy
        0 drwxr-xr-x   4 blyth  staff       128 Jul 15  2022 storch_test
        8 -rw-r--r--   1 blyth  staff        79 Jun 22  2022 RandomDisc100_f8.json
       32 -rw-r--r--   1 blyth  staff     12928 Jun 22  2022 RandomDisc100_f8.npy
        8 -rw-r--r--   1 blyth  staff        77 Jun 22  2022 RandomDisc10_f8.json
        8 -rw-r--r--   1 blyth  staff      1408 Jun 22  2022 RandomDisc10_f8.npy
        8 -rw-r--r--   1 blyth  staff        79 Jun 22  2022 RandomDisc100_f4.json
       16 -rw-r--r--   1 blyth  staff      6528 Jun 22  2022 RandomDisc100_f4.npy
        8 -rw-r--r--   1 blyth  staff        77 Jun 22  2022 RandomDisc10_f4.json
        8 -rw-r--r--   1 blyth  staff       768 Jun 22  2022 RandomDisc10_f4.npy
        8 -rw-r--r--   1 blyth  staff        84 Jun 22  2022 RandomSpherical100_f8.json
       32 -rw-r--r--   1 blyth  staff     12928 Jun 22  2022 RandomSpherical100_f8.npy
        8 -rw-r--r--   1 blyth  staff        84 Jun 22  2022 RandomSpherical100_f4.json
       16 -rw-r--r--   1 blyth  staff      6528 Jun 22  2022 RandomSpherical100_f4.npy
        8 -rw-r--r--   1 blyth  staff        83 Jun 14  2022 InwardsCubeCorners1_f4.json
        8 -rw-r--r--   1 blyth  staff       640 Jun 14  2022 InwardsCubeCorners1_f4.npy
        8 -rw-r--r--   1 blyth  staff        87 Jun 14  2022 InwardsCubeCorners17699_f4.json
        8 -rw-r--r--   1 blyth  staff       640 Jun 14  2022 InwardsCubeCorners17699_f4.npy
        8 -rw-r--r--   1 blyth  staff        82 Jun 14  2022 RandomSpherical10_f4.json
        8 -rw-r--r--   1 blyth  staff       768 Jun 14  2022 RandomSpherical10_f4.npy


::

    epsilon:opticks blyth$ opticks-fl InputPhotons
    ./ana/input_photons.sh
    ./ana/parallel_input_photons.py
    ./ana/input_photons.py
    ./ana/input_photons_plt.py
    ./opticksgeo/OpticksGen.cc
    ./opticksgeo/OpticksHub.hh
    ./opticksgeo/OpticksHub.cc
    ./opticksgeo/OpticksGen.hh
    ./cfg4/CEvent.hh
    ./cfg4/CEvent.cc
    ./cfg4/CCtx.cc
    ./cfg4/CGenerator.cc
    ./bin/OPTICKS_INPUT_PHOTON_.sh
    ./g4ok/G4Opticks.cc
    ./g4ok/tests/G4OKTest.cc
    ./g4ok/tests/G4OKTest.sh
    ./g4ok/G4Opticks.hh
    ./sysrap/tests/storch_test.sh
    ./sysrap/tests/stranTest.cc
    ./sysrap/SEvt.cc
    ./optickscore/OpticksGenstep.cc
    ./npy/tests/NPY7Test.cc
    epsilon:opticks blyth$ 
    epsilon:opticks blyth$ 


sphoton now has transform capability::

    470 SPHOTON_METHOD void sphoton::transform( const glm::tmat4x4<double>& tr, bool normalize )
    471 {
    472     float one(1.);
    473     float zero(0.);
    474 
    475     unsigned count = 1 ;
    476     unsigned stride = 4*4 ; // effectively not used as count is 1
    477 
    478     assert( sizeof(*this) == sizeof(float)*16 );
    479     float* p0 = (float*)this ;
    480 
    481     Tran<double>::ApplyToFloat( tr, p0, one,  count, stride, 0, false );      // transform pos as position
    482     Tran<double>::ApplyToFloat( tr, p0, zero, count, stride, 4, normalize );  // transform mom as direction
    483     Tran<double>::ApplyToFloat( tr, p0, zero, count, stride, 8, normalize );  // transform pol as direction
    484 }


TODO: arrange for an input transform : using another path to .npy file with the 4x4 transform



Higher level approach is to use sframe.h
-------------------------------------------

::

    381 /**
    382 sframe::transform_photon_m2w
    383 -------------------------------
    384 
    385 Canonical call from SEvt::setFrame for transforming input photons into frame 
    386 When normalize is true the mom and pol are normalized after the transformation. 
    387 
    388 Note that the transformed photon array is always in double precision. 
    389 That will be narrowed down to float prior to upload by QEvent::setInputPhoton
    390 
    391 **/
    392 
    393 inline NP* sframe::transform_photon_m2w( const NP* ph, bool normalize ) const
    394 {
    395     if( ph == nullptr ) return nullptr ;
    396     if(!tr_m2w) std::cerr << "sframe::transform_photon_m2w MUST sframe::prepare before calling this " << std::endl;
    397     assert( tr_m2w) ;
    398     NP* pht = Tran<double>::PhotonTransform(ph, normalize,  tr_m2w );
    399     assert( pht->ebyte == 8 );
    400     return pht ;
    401 }



::

    epsilon:sysrap blyth$ opticks-fl sframe.h 
    ./ana/framegensteps.py
    ./CSGOptiX/CSGOptiX.h
    ./CSGOptiX/tests/CSGOptiXSimtraceTest.cc
    ./CSGOptiX/CSGOptiX.cc
    ./CSG/CSGTarget.cc
    ./CSG/tests/CSGTargetTest.cc
    ./CSG/tests/CSGFoundry_MakeCenterExtentGensteps_Test.cc
    ./CSG/tests/CSGFoundry_getFrame_Test.cc
    ./CSG/CSGSimtrace.hh
    ./CSG/CSGFoundry.cc
    ./extg4/X4Simtrace.hh
    ./sysrap/SFrameGenstep.hh
    ./sysrap/CMakeLists.txt
    ./sysrap/CheckGeo.cc
    ./sysrap/stree.h
    ./sysrap/tests/CheckGeoTest.cc
    ./sysrap/tests/sframe_test.cc
    ./sysrap/tests/SFrameGenstep_MakeCenterExtentGensteps_Test.cc
    ./sysrap/tests/sframeTest.cc
    ./sysrap/SFrameGenstep.cc
    ./sysrap/SEvt.hh
    ./sysrap/SEvent.cc
    ./sysrap/SSimtrace.h
    ./sysrap/sframe.h
    ./ggeo/GGeo.cc
    ./u4/tests/U4App.h
    ./g4cx/G4CXOpticks.cc
    epsilon:opticks blyth$ 



    epsilon:CSG blyth$ grep sframe.h *.*
    CSGFoundry.cc:#include "sframe.h"
    CSGSimtrace.hh:#include "sframe.h"
    CSGTarget.cc:#include "sframe.h"
    epsilon:CSG blyth$ 


jcv LSExpDetectorConstruction_Opticks::

     25     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     26     if( opticksMode == 0 )
     27     {
     28         LOG(info) << " opticksMode 0 : no setup needed " ;
     29     } 
     30     else if( opticksMode == 1 || opticksMode == 3 || opticksMode == 2 )
     31     {
     32         if(opticksMode == 2) G4CXOpticks::SetNoGPU() ; 
     33         G4CXOpticks::SetGeometry(world) ; 
     34 
     35         _PMTParamData    _ppd(*ppd) ; 
     36         _PMTSimParamData _psd(*psd) ; 
     37 
     38         NPFold* j = new NPFold ; 
     39         j->add_subfold( "PMTParamData",    _ppd.serialize() );
     40         j->add_subfold( "PMTSimParamData", _psd.serialize() );
     41         if(pmtscan) j->add_subfold( "PMTScan",  pmtscan );
     42 
     43         SSim::AddSubfold("juno", j );
     44 
     45         G4CXOpticks::SaveGeometry(); 
     46     } 
     47     else
     48     {
     49         LOG(fatal) << " unexpected opticksMode " << opticksMode ; 
     50         assert(0);
     51     }


HMM: need the translated geometry with no GPU involvement for opticksMode:2 

DONE : Changed opticksMode:2 to do G4CXOpticks::SetGeometry also but with a NoGPU switch to skip CSGOptiX.




Save two GEOM and grab to laptop
-----------------------------------

workstation::

    N=0 GEOM=V0J008 ntds2  ## save old 4-volume PMT geometry 
    N=1 GEOM=V1J008 ntds2  ## save new 2-volume PMT geometry 

laptop::

    jxn
    ./ntds.sh grab2
    ./ntds.sh geom2


N=0 GEOM=V0J008 ntds2::

    ...
    GInstancer::dumpRepeatCandidates@464:  num_repcan 9 dmax 20
     pdig b3fc1b34f6c638171dcf673e68721077 ndig  25600 nprog      4 placements  25600 n PMT_3inch_log_phys
     pdig c548c90809b63b1bb5d73822a56eb94f ndig  12615 nprog     10 placements  12615 n pLPMT_NNVT_MCPPMT
     pdig 7372f25e8407ff948e91b2cd3bf3d4ad ndig   4997 nprog     13 placements   4997 n pLPMT_Hamamatsu_R12860
     pdig 903a1448ff2cf7df67b245af126db74f ndig   2400 nprog      5 placements   2400 n mask_PMT_20inch_vetolMaskVirtual_phys
     pdig ed3d2c21991e3bef5e069713af9fa6ca ndig    590 nprog      0 placements    590 n lSteel_phys
     pdig ac627ab1ccbdb62ec96e702f07f6425b ndig    590 nprog      0 placements    590 n lFasteners_phys
     pdig f899139df5e1059396431415e770c6dd ndig    590 nprog      0 placements    590 n lUpper_phys
     pdig 38b3eff8baf56627478ec76a704e9b52 ndig    590 nprog      0 placements    590 n lAddition_phys
     pdig 4c29bcd2a52a397de5036b415af92efe ndig    504 nprog    129 placements    504 n pPanel_0_f_
    G4CXOpticks::setGeometry@250: 
    G4CXOpticks::setGeometry@286: [ fd 0x18af90a10
    G4CXOpticks::setGeometry@296:  Using pre-existing SEvt (happens when U4Recorder instanciated it first) 
    G4CXOpticks::setGeometry@314:  skip CSGOptiX::Create as NoGPU has been set 
    G4CXOpticks::setGeometry@321:  cx N qs N QSim::Get N
    G4CXOpticks::setGeometry@327: ] fd 0x18af90a10
    G4CXOpticks::SaveGeometry@580:  save to dir /home/blyth/.opticks/GEOM/V0J008 configured via envvar G4CXOpticks__SaveGeometry_DIR

    ...

    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 4606 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    U4Recorder::EndOfEventAction@162:  eventID 0 eventID_ 0 eidx 0 consistent_eventID  YES
    SEvt::save@2019: SGeo::DefaultDir $DefaultOutputDir
    SEvt::save@2109:  dir /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000
    SEvt::save@2110: SEvt::descOutputDir dir_ $DefaultOutputDir dir  /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000 reldir ALL0 with_index Y index 0 this 0xb4fc30

                  SCRIPT :                                                                                                ntds2
                  LAYOUT :                                                                                      POM 1 VERSION 0
                 VERSION :                                                                                                    0
                    GEOM :                                                                                               V0J008
             COMMANDLINE : gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-unnatural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer gun
               DIRECTORY :                                                                                   /tmp/u4debug/ntds2
        ${GEOM}_GEOMList :                                                                                      V0J008_GEOMList
    SEvt::gatherHit@1823:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@682: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    U4Recorder::EndOfRunAction@147: 
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           5.25100        5.25100      0.00000      
    DetSimAlg                1           194351.04688   194351.04688 0.00000      
    Sum of junotoptask       1           194356.45312   194356.45312 0.00000      
    #############################################################################



N=1 GEOM=V1J008 ntds2::

    GInstancer::dumpRepeatCandidates@464:  num_repcan 9 dmax 20
     pdig 2e94fd9ad31943ff32b5c24d2ef6f9cb ndig  25600 nprog      4 placements  25600 n PMT_3inch_log_phys
     pdig 399d95401b4b48dd6dd373c56b665cce ndig  12615 nprog      8 placements  12615 n pLPMT_NNVT_MCPPMT
     pdig 5c4494e0a36bdef4044b064895239c1c ndig   4997 nprog     11 placements   4997 n pLPMT_Hamamatsu_R12860
     pdig c4033813f7fc89ef25da44cce4caae49 ndig   2400 nprog      5 placements   2400 n mask_PMT_20inch_vetolMaskVirtual_phys
     pdig ed3d2c21991e3bef5e069713af9fa6ca ndig    590 nprog      0 placements    590 n lSteel_phys
     pdig ac627ab1ccbdb62ec96e702f07f6425b ndig    590 nprog      0 placements    590 n lFasteners_phys
     pdig f899139df5e1059396431415e770c6dd ndig    590 nprog      0 placements    590 n lUpper_phys
     pdig 38b3eff8baf56627478ec76a704e9b52 ndig    590 nprog      0 placements    590 n lAddition_phys
     pdig 4c29bcd2a52a397de5036b415af92efe ndig    504 nprog    129 placements    504 n pPanel_0_f_
    G4CXOpticks::setGeometry@250: 
    G4CXOpticks::setGeometry@286: [ fd 0x16a31ee00
    G4CXOpticks::setGeometry@296:  Using pre-existing SEvt (happens when U4Recorder instanciated it first) 
    G4CXOpticks::setGeometry@314:  skip CSGOptiX::Create as NoGPU has been set 
    G4CXOpticks::setGeometry@321:  cx N qs N QSim::Get N
    G4CXOpticks::setGeometry@327: ] fd 0x16a31ee00
    G4CXOpticks::SaveGeometry@580:  save to dir /home/blyth/.opticks/GEOM/V1J008 configured via envvar G4CXOpticks__SaveGeometry_DIR
    G4CXOpticks::saveGeometry@525: [ /home/blyth/.opticks/GEOM/V1J008
    G4CXOpticks::saveGeometry@526: [ /home/blyth/.opticks/GEOM/V1J008
    G4CXOpticks::saveGeometry [ /home/blyth/.opticks/GEOM/V1J008
    U4GDML::write@186:  ekey U4GDML_GDXML_FIX_DISABLE U4GDML_GDXML_FIX_DISABLE 0 U4GDML_GDXML_FIX 1
    G4GDML: Writing '/home/blyth/.opticks/GEOM/V1J008/origin_raw.gdml'...
    ...
    SEvt::hostside_running_resize_@1027: resizing photon 9508 to evt.num_photon 9810
    U4Debug::Save eventID 0 dir /tmp/u4debug/ntds2/000 EKEY U4Debug_SaveDir
    U4Cerenkov_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 6
    U4Scintillation_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 77
    U4Hit_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 28
    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 28 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    U4Recorder::EndOfEventAction@162:  eventID 0 eventID_ 0 eidx 0 consistent_eventID  YES
    SEvt::save@2019: SGeo::DefaultDir $DefaultOutputDir
    SEvt::save@2109:  dir /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000
    SEvt::save@2110: SEvt::descOutputDir dir_ $DefaultOutputDir dir  /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000 reldir ALL1 with_index Y index 0 this 0xb4fc10

                  SCRIPT :                                                                                                ntds2
                  LAYOUT :                                                                                      POM 1 VERSION 1
                 VERSION :                                                                                                    1
                    GEOM :                                                                                               V1J008
             COMMANDLINE : gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-natural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer gun
               DIRECTORY :                                                                                   /tmp/u4debug/ntds2
        ${GEOM}_GEOMList :                                                                                      V1J008_GEOMList
    SEvt::gatherHit@1823:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@682: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    U4Recorder::EndOfRunAction@147: 
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           5.62200        5.62200      0.00000      
    DetSimAlg                1           215193.98438   215193.98438 0.00000      
    Sum of junotoptask       1           215199.76562   215199.76562 39.33122     
    #############################################################################



Related machinery
--------------------

::

    bin/OPTICKS_INPUT_PHOTON.sh
    bin/OPTICKS_INPUT_PHOTON_.sh
    CSG/tests/CSGFoundry_getFrame_Test.sh
    CSG/tests/CSGFoundry_getFrame_Test.cc



rejig setupFrame
--------------------

Factored off G4CXOpticks::setupFrame and now invoke from G4CXOpticks::setGeometry

* this means that with appropriate envvars SEvt::GetInputPhoton() should be 
  auto-transformed into the chosen frame 

* so all "jcv GtOpticksTool" needs to do it grab the input photons from SEvt 

* test transformed input photon and labelling in  g4cx/tests/G4CXOpticks_setGeometry_Test.sh


try to use the SEvt::GetInputPhoton with GtOpticksTool
----------------------------------------------------------

::

    N=0 GEOM=V0J008 ntds2
    N=1 GEOM=V1J008 ntds2



::

    G4CXOpticks::setGeometry@249: 
    G4CXOpticks::setGeometry_@289: [ fd 0x18afaff60
    G4CXOpticks::setGeometry_@299:  Using pre-existing SEvt (happens when U4Recorder instanciated it first) 
    G4CXOpticks::setGeometry_@311:  skip CSGOptiX::Create as NoGPU has been set 
    G4CXOpticks::setGeometry_@318:  cx N qs N QSim::Get N
    G4CXOpticks::setGeometry_@324: ] fd 0x18afaff60
    G4CXOpticks::setupFrame@358: sframe::desc inst 0 frs Hama:0:1000
     ekvid sframe_MOI_Hama_0_1000 ek MOI ev Hama:0:1000
     ce  (-12026.132,9489.441,11827.850,366.053)  is_zero 0
     m2w ( 0.480,-0.379, 0.792, 0.000) (-0.619,-0.785, 0.000, 0.000) ( 0.621,-0.490,-0.611, 0.000) (-12075.873,9528.691,11876.771, 1.000) 
     w2m ( 0.480,-0.619, 0.621, 0.000) (-0.379,-0.785,-0.490, 0.000) ( 0.792, 0.000,-0.611, 0.000) (-0.006,-0.009,19434.000, 1.000) 
     midx  104 mord    0 iidx 1000
     inst    0
     ix0     0 ix1     0 iy0     0 iy1     0 iz0     0 iz1     0 num_photon    0
     ins     0 gas     0 sensor_identifier        0 sensor_index      0
     propagate_epsilon    0.05000 is_hostside_simtrace NO

    G4CXOpticks::SaveGeometry@593:  save to dir /home/blyth/.opticks/GEOM/V0J008 configured via envvar G4CXOpticks__SaveGeometry_DIR
    G4CXOpticks::saveGeometry@538: [ /home/blyth/.opticks/GEOM/V0J008


    ### Run : 0
    junotoptask.initialize          INFO: initialized
    sphoton::Get not expected error  a Y a.shape (1000, 4, 4, ) a.ebyte 8 a.shape[0] 1000 idx 0
    python: /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/sphoton.h:422: static void sphoton::Get(sphoton&, const NP*, unsigned int): Assertion `expected' failed.

    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd382a0cf in sphoton::Get (p=..., a=0xb50d90, idx=0) at /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/sphoton.h:422
    #5  0x00007fffd381c0ab in GtOpticksTool::add_optical_photon (this=0x943360, event=..., idx=0, override_wavelength_nm=0, dump=true)
        at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtOpticksTool.cc:131
    #6  0x00007fffd381cb46 in GtOpticksTool::mutate (this=0x943360, event=...) at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtOpticksTool.cc:221
    #7  0x00007fffd37f7a95 in GenTools::execute (this=0x942ed0) at /data/blyth/junotop/junosw/Simulation/GenTools/src/GenTools.cc:120
    #8  0x00007fffed5c984a in Task::execute() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so


    (gdb) f 6
    #6  0x00007fffd381cb46 in GtOpticksTool::mutate (this=0x943360, event=...) at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtOpticksTool.cc:221
    221	                add_optical_photon(event, idx, override_wavelength_nm, dump);
    (gdb) f 5
    #5  0x00007fffd381c0ab in GtOpticksTool::add_optical_photon (this=0x943360, event=..., idx=0, override_wavelength_nm=0, dump=true)
        at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtOpticksTool.cc:131
    131	    sphoton::Get(p, m_input_photons, idx );  // hmm float precision, perhaps use sphotond for double 
    (gdb) f 4
    #4  0x00007fffd382a0cf in sphoton::Get (p=..., a=0xb50d90, idx=0) at /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/sphoton.h:422
    422	    assert( expected  ); 
    (gdb) 



Reworked GtOpticksTool to work with float or double photon arrays
----------------------------------------------------------------------




::


    N=0 GEOM=V0J008 ntds2


    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     9 seq TO BT BT DR BT BT SC BT BT AB
    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     8 seq TO BT BT DR BT BT BT BT BT BT BT BT BT SD
    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     7 seq TO BT BT DR BT BT BT BT BT SD
    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     6 seq TO BT BT AB
    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     5 seq TO SC BT BR BT BT BR BT BT BR BT SC BT BT BT BT BT BT BT BT SD
    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     4 seq TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     3 seq TO SC BT BT BT BT BT BT BT SD
    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     2 seq TO BT BT DR AB
    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     1 seq TO AB
    U4Recorder::PreUserTrackingAction_Optical@293:  modulo : label->id 0
    U4Recorder::PostUserTrackingAction_Optical@466:  l.id     0 seq TO BT BT SA
    U4Debug::Save eventID 0 dir /tmp/u4debug/ntds2/000 EKEY U4Debug_SaveDir
    U4Cerenkov_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 0
    U4Scintillation_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 0
    U4Hit_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 341
    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 341 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    U4Recorder::EndOfEventAction@162:  eventID 0 eventID_ 0 eidx 0 consistent_eventID  YES
    SEvt::save@2100: SGeo::DefaultDir $DefaultOutputDir
    SEvt::save@2190:  dir /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000
    SEvt::save@2191: SEvt::descOutputDir dir_ $DefaultOutputDir dir  /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000 reldir ALL0 with_index Y index 0 this 0xb500c0

                  SCRIPT :                                                                                                ntds2
                  LAYOUT :                                                                                      POM 1 VERSION 0
                 VERSION :                                                                                                    0
                    GEOM :                                                                                               V0J008
             COMMANDLINE : gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-unnatural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer opticks
               DIRECTORY :                                                                                   /tmp/u4debug/ntds2
        ${GEOM}_GEOMList :                                                                                      V0J008_GEOMList
    SEvt::gatherHit@1890:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@749: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    U4Recorder::EndOfRunAction@147: 
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           7.02600        7.02600      0.00105      
    DetSimAlg                1           30465.80273    30465.80273  0.00000      
    Sum of junotoptask       1           30472.97461    30472.97461  0.00000      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 2 WITH_G4CXOPTICKS 
    G4CXOpticks::Finalize@72: placeholder mimic G4Opticks 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    Delete G4SvcRunManager

    **************************************************
    Terminating @ localhost.localdomain on Tue Mar 28 23:02:34 2023
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully



::

    N=1 GEOM=V1J008 ntds2




HMM GtOpticksTool::configure happens before sframe set into SEvt
--------------------------------------------------------------------

This explains why the input photons are not transformed into target frame. 

::

    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::initializeOpticks m_opticksMode 2 WITH_G4CXOPTICKS 
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr U4RecorderAnaMgr
    junotoptask:SniperProfiling.initialize  INFO: 
    GtOpticksTool::configure WITH_G4CXOPTICKS path - SEvt::Brief  SEvt::Exists Y INSTANCE SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed N
     m_input_photons (1000, 4, 4, )
    GtOpticksTool::configure SEvt::Brief SEvt::Brief  SEvt::Exists Y INSTANCE SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed N

    GtOpticksTool::configure ret 1
    GtOpticksTool::configure ret 1


Try deferring SEvt::GetInputPhoton until the mutate


::

    jxf ; N=0 GEOM=V0J008 ntds2
    jxf ; N=1 GEOM=V1J008 ntds2


plotting the U4Recorder points with frame targetted input photons : clear POM quadrant control issue
-------------------------------------------------------------------------------------------------------

::

    jxn    # cd ~/j/ntds
    ./ntds.sh grab_evt

    MODE=2 ./ntds.sh ana
    MODE=3 ./ntds.sh ana

Its immediately apparent that the N=0 photons are ending at photocathode
and not entering the PMT wheras the N=1 photons do often enter the PMT.

They should both be entering PMT. Suggests POM quadrant control issue. 


compare boundary status char
-------------------------------

Collected by::

     744 #if defined(WITH_CUSTOM4)
     745 template<>
     746 void U4Recorder::CollectBoundaryAux<C4OpBoundaryProcess>(quad4* current_aux)
     747 {
     748     C4OpBoundaryProcess* bop = U4OpBoundaryProcess::Get<C4OpBoundaryProcess>() ;
     749     assert(bop) ;
     750     assert(current_aux);
     751 
     752     char customStatus = bop ? bop->m_custom_status : 'B' ;
     753     C4CustomART* cart   = bop ? bop->m_custom_art : nullptr ;
     754     const double* recoveredNormal =  bop ? (const double*)&(bop->theRecoveredNormal) : nullptr ;
     755     C4CustomART_Debug* cdbg = cart ? &(cart->dbg) : nullptr ;
     756 
     757     LOG(LEVEL)
     758         << " bop " << ( bop ? "Y" : "N" )
     759         << " cart " << ( cart ? "Y" : "N" )
     760         << " cdbg " << ( cdbg ? "Y" : "N" )
     761         << " current_aux " << ( current_aux ? "Y" : "N" )
     762         << " bop.m_custom_status " << customStatus
     763         << " CustomStatus::Name " << CustomStatus::Name(customStatus)
     764         ;
     765 
     766     if(cdbg && customStatus == 'Y') current_aux->load( cdbg->data(), C4CustomART_Debug::N ) ;
     767     current_aux->set_v(3, recoveredNormal, 3);   // nullptr are just ignored
     768     current_aux->q3.i.w = int(customStatus) ;    // moved from q1 to q3
     769 }

For customStatus Y the first three quads from cdbg get loaded into aux::

     05 struct C4CustomART_Debug
      6 {
      7     static constexpr const int N = 12 ;
      8 
      9     double A ;
     10     double R ;
     11     double T ;
     12     double _qe ;
     13 
     14     double An ;
     15     double Rn ;
     16     double Tn ;
     17     double escape_fac ;
     18 
     19     double minus_cos_theta ;
     20     double wavelength_nm ;
     21     double pmtid ;
     22     double spare ;
     23 
     24     void serialize( std::array<double, 16>& a );
     25     const double* data() const ;
     26 };

m_custom_status starts as 'U'::

     119 C4OpBoundaryProcess::C4OpBoundaryProcess(
     120                                                const C4IPMTAccessor* accessor,
     121                                                const G4String& processName,
     122                                                G4ProcessType type)
     123              :
     124              G4VDiscreteProcess(processName, type),
     125              m_custom_status('U'),
     126              m_custom_art(new C4CustomART(
     127                                         accessor,
     128                                         theAbsorption,
     129                                         theReflectivity,
     130                                         theTransmittance,
     131                                         theEfficiency,
     132                                         theGlobalPoint,
     133                                         OldMomentum,
     134                                         OldPolarization,
     135                                         theRecoveredNormal,
     136                                         thePhotonMomentum
     137                                        ))
     138 {

Actually starts every step as 'U'::

     199 G4VParticleChange*
     200 C4OpBoundaryProcess::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
     201 {
     202         m_track_label = C4TrackInfo<C4Pho>::GetRef(&aTrack);
     203         assert( m_track_label );
     204         m_track_dump = m_track_label->ix == PIDX && PIDX_ENABLED ;
     205 
     206         theStatus = Undefined;
     207         m_custom_status = 'U' ;



::

     503             //[OpticalSurface.mpt.CustomPrefix
     504             if( OpticalSurfaceName0 == '@' || OpticalSurfaceName0 == '#' )  // only customize specially named OpticalSurfaces 
     505             {
     506                 if( m_custom_art->local_z(aTrack) < 0. ) // lower hemi : No customization, standard boundary  
     507                 {
     508                     m_custom_status = 'Z' ;
     509                 }
     510                 else if( OpticalSurfaceName0 == '@') //  upper hemi with name starting @ : MultiFilm ART transmit thru into PMT
     511                 {
     512                     m_custom_status = 'Y' ;
     513 
     514                     m_custom_art->doIt(aTrack, aStep) ;
     515 
     516                     /**
     517                     m_custom_art calculates 3-way probabilities (A,R,T) that sum to 1. 
     518                     and looks up theEfficiency appropriate for the PMT 
     519                     
     520                     BUT: as DielectricDielectric is expecting a 2-way *theTransmittance* probability 
     521                     m_custom_art leaves theAbsorption as A and rescales the others to create 2-way probs::
     522 
     523                          ( theAbsorption, theReflectivity, theTransmittance ) =  ( A, R/(1-A), T/(1-A) )
     524 
     525                     **/
     526 
     527 
     528                     type = dielectric_dielectric ;
     529                     theModel = glisur ;
     530                     theFinish = polished ;  // to make Rindex2 get picked up below, plus use theGlobalNormal as theFacetNormal 
     531 
     532                     // ACTUALLY : ITS SIMPLER TO TREAT m_custom_status:Y as kinda another type 
     533                     // in the big type switch below to avoid depending on the jungle
     534 
     535                 }
     536                 else if( OpticalSurfaceName0 == '#' ) // upper hemi with name starting # : Traditional Detection at photocathode
     537                 {
     538                     m_custom_status = '-' ;
     539 
     540                     type = dielectric_metal ;
     541                     theModel = glisur ;
     542                     theReflectivity = 0. ;
     543                     theTransmittance = 0. ;
     544                     theEfficiency = 1. ;
     545                 }   
     546             }   
     547             //]OpticalSurface.mpt.CustomPrefix
     548             else
     549             {
     550                 m_custom_status = 'X' ;
     551             }



**C4CustomStatus.h**

The custom status char is set by C4OpBoundaryProcess::PostStepDoIt

+------+-------------------------------------------------------------------------------+
| char |                                                                               |
+======+===============================================================================+
|  U   |  starting value set at initialization and at every step                       |
+------+-------------------------------------------------------------------------------+
|  Z   |  @/# OpticalSurface BUT local_z < 0 : so ordinary surface                     |         
+------+-------------------------------------------------------------------------------+
|  Y   |  @ OpticalSurface AND local_z > 0 : so C4CustomART::doIt runs                 |
+------+-------------------------------------------------------------------------------+
|  -   |  # OpticalSurface AND local_z > 0 : so traditional detect at photocathode     |                
+------+-------------------------------------------------------------------------------+
|  X   |  NOT @/# OpticalSurface : so ordinary surface                                 | 
+------+-------------------------------------------------------------------------------+
|  \0  |  Uninitialized array content                                                  |
+------+-------------------------------------------------------------------------------+


::

   jxn
   ./ntds.sh ana

    In [13]: a_bop = a.f.aux.view(np.int32)[:,:,3,3]
    In [14]: b_bop = b.f.aux.view(np.int32)[:,:,3,3]

    In [15]: np.c_[np.unique( a_bop, return_counts=True )]
    Out[15]: 
    array([[    0, 26037],       ## uninit
           [   85,  5003],       ## U 
           [   88,   960]])      ## X

    In [16]: np.c_[np.unique( b_bop, return_counts=True )]
    Out[16]: 
    array([[    0, 25784],      ## uninit
           [   85,  4746],      ## U
           [   88,   270],      ## X
           [   89,  1073],      ## Y
           [   90,   127]])     ## Z

    In [18]: list(map(chr, [0, 85, 88, 89, 90]))
    Out[18]: [        '\x00', 'U','X','Y','Z']



FIXED : FastSim was not kicking in due to declProp usage bug : organize TDS_LOG renaming, check log
---------------------------------------------------------------------------------------------------------

::

    jxf ; N=0 GEOM=V0J008 ntds2
    jxf ; N=1 GEOM=V1J008 ntds2


YEP its not set::

    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  m_useScintSimple == 0
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  level                   : 0
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  m_UsePMTNaturalGeometry : 0
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  m_UsePMTOpticalModel    : 1
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  m_doFastSim             : 0
    DsPhysConsOptical::CreateCustomG4OpBoundaryProcess

jcv DsPhysConsOptical::

    .    declProp("UsePMTOpticalModel", m_UsePMTOpticalModel=true);
         declProp("UsePMTNaturalGeometry", m_UsePMTNaturalGeometry=true);
    -    m_doFastSim = m_UsePMTOpticalModel == true && m_UsePMTNaturalGeometry == false ; 
    -    // see Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h for notes on the PMT*POM quadrants 
    +    m_doFastSim = false ;  // maybe changed later based on config of above two 
    +
     

Fixed the bug : cannot derive from declProp config in the ctor

* have to do it latter after declProp settings have been set from the python.
* THATS ANOTHER REASON NOT TO LIKE declProp


Succeed to switch it on::

    junotoptask:DetSimAlg.DsPhysConsOptical.SetParameters  INFO: Alpha birksConstant2 = 0.000
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check: m_useCerenKov == 1
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check: m_useScintillation == 1
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  m_useScintSimple == 0
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  level                   : 0
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  m_UsePMTNaturalGeometry : 0
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  m_UsePMTOpticalModel    : 1
    junotoptask:DetSimAlg.DsPhysConsOptical.ConstructProcess  INFO: check:  m_doFastSim             : 1
    DsPhysConsOptical::CreateCustomG4OpBoundaryProcess

FIXED : Now DEFER_FSTRACKINFO flag zero assert : Fixed by rejig of labelling 
----------------------------------------------------------------------------------

::

    U4Recorder::UserSteppingAction_Optical@647:  DEFER_FSTRACKINFO  FAILED TO GET THE FastSim status from trackinfo  fstrackinfo_stat 
    U4Recorder::UserSteppingAction_Optical@660:  ERR flag zero : post U4StepPoint::Desc
     proc 5 procName fast_sim_man procNameRaw fast_sim_man
     status 1 statusName fGeomBoundary
     bstat 12 bstatName SameMaterial
     flag 2097152 flagName DEFER_FSTRACKINFO
    python: /data/blyth/junotop/opticks/u4/U4Recorder.cc:661: void U4Recorder::UserSteppingAction_Optical(const G4Step*) [with T = C4OpBoundaryProcess]: Assertion `flag > 0' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) 

    (gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd28cb8e7 in U4Recorder::UserSteppingAction_Optical<C4OpBoundaryProcess> (this=0x933760, step=0xadee10)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:661
    #5  0x00007fffd28c3fc4 in U4Recorder::UserSteppingAction (this=0x933760, step=0xadee10) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:185
    #6  0x00007fffcea4fa32 in U4RecorderAnaMgr::UserSteppingAction (this=0x933660, step=0xadee10)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:35
    #7  0x00007fffccdd8009 in MgrOfAnaElem::UserSteppingAction (this=0x7fffccfe6b00 <MgrOfAnaElem::instance()::s_mgr>, step=0xadee10)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:74
    #8  0x00007fffced74065 in LSExpSteppingAction::UserSteppingAction (this=0x5989d90, fStep=0xadee10)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpSteppingAction.cc:56
    #9  0x00007fffdb982e1d in G4SteppingManager::Stepping() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffdb98e472 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so


    (gdb) f 6
    #6  0x00007fffcea4fa32 in U4RecorderAnaMgr::UserSteppingAction (this=0x933660, step=0xadee10)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:35
    35	void U4RecorderAnaMgr::UserSteppingAction(const G4Step* step) {     m_recorder->UserSteppingAction(step);    } 
    (gdb) f 5
    #5  0x00007fffd28c3fc4 in U4Recorder::UserSteppingAction (this=0x933760, step=0xadee10) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:185
    185	     UserSteppingAction_Optical<C4OpBoundaryProcess>(step); 
    (gdb) list
    180	void U4Recorder::UserSteppingAction(const G4Step* step)
    181	{ 
    182	    if(!U4Track::IsOptical(step->GetTrack())) return ; 
    183	
    184	#if defined(WITH_CUSTOM4)
    185	     UserSteppingAction_Optical<C4OpBoundaryProcess>(step); 
    186	#elif defined(WITH_PMTSIM)
    187	     UserSteppingAction_Optical<CustomG4OpBoundaryProcess>(step); 
    188	#else
    189	     UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess>(step);
    (gdb) f 4
    #4  0x00007fffd28cb8e7 in U4Recorder::UserSteppingAction_Optical<C4OpBoundaryProcess> (this=0x933760, step=0xadee10)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:661
    661	    assert( flag > 0 ); 
    (gdb) l
    656	            << " flag " << OpticksPhoton::Flag(flag) 
    657	            ; 
    658	    }
    659	
    660	    LOG_IF(error, flag == 0) << " ERR flag zero : post " << U4StepPoint::Desc<T>(post) ; 
    661	    assert( flag > 0 ); 
    662	
    663	    bool PIDX_DUMP = label->id == PIDX && PIDX_ENABLED ; 
    664	
    665	    LOG(LEVEL) << U4StepPoint::DescPositionTime(post) ;  
    (gdb) 





This could be the C4TrackInfo label versus S4TrackInfo ?.

U4Recorder.cc::

    0570 template <typename T>
     571 void U4Recorder::UserSteppingAction_Optical(const G4Step* step)
     572 {
     573     const G4Track* track = step->GetTrack();
     574     G4VPhysicalVolume* pv = track->GetVolume() ;
     575     LOG(LEVEL) << "[ pv " << ( pv ? pv->GetName() : "-" ) ;
     576 
     577     spho* label = STrackInfo<spho>::GetRef(track);
     578     assert( label->isDefined() );
     579     if(!Enabled(*label)) return ;   // EIDX, GIDX skipping 
     580 

    (gdb) p label
    $1 = (spho *) 0x244dd0330
    (gdb) p *label
    $2 = {gs = 0, ix = 999, id = 999, uc4 = {x = 0 '\000', y = 0 '\000', z = 0 '\000', w = 95 '_'}}
    (gdb) 




     632 
     633     if(flag == DEFER_FSTRACKINFO)
     634     {
     635         char fstrackinfo_stat = label->uc4.w ;
     636         label->uc4.w = '_' ;   // scrub after access 
     637 
     638         switch(fstrackinfo_stat)
     639         {
     640            case 'T': flag = BOUNDARY_TRANSMIT ; break ;
     641            case 'R': flag = BOUNDARY_REFLECT  ; break ;
     642            case 'A': flag = SURFACE_ABSORB    ; break ;
     643            case 'D': flag = SURFACE_DETECT    ; break ;
     644            case '_': flag = 0                 ; break ;
     645            default:  flag = 0                 ; break ;
     646         }
     647         LOG_IF(error, flag == 0)
     648             << " DEFER_FSTRACKINFO "
     649             << " FAILED TO GET THE FastSim status from trackinfo "
     650             << " fstrackinfo_stat " << fstrackinfo_stat
     651             ;
     652 
     653         LOG(LEVEL)
     654             << " DEFER_FSTRACKINFO "
     655             << " fstrackinfo_stat " << fstrackinfo_stat
     656             << " flag " << OpticksPhoton::Flag(flag)
     657             ;
     658     }



U4Recorder was expecting spho, now added C4::

     579 #ifdef WITH_CUSTOM4
     580     C4Pho* label = C4TrackInfo<C4Pho>::GetRef(track);
     581 #else
     582     spho* label = STrackInfo<spho>::GetRef(track);
     583 #endif

But need to swap over to C4 everywhere tracks are labelled (Scint+Cerenkov+FastSim)::

    epsilon:u4 blyth$ opticks-f C4TrackInfo
    ./u4/U4Recorder.cc:    C4Pho* label = C4TrackInfo<C4Pho>::GetRef(track); 
    epsilon:opticks blyth$ 


::

    N[blyth@localhost junosw]$ jgr C4TrackInfo
    ./Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc:#include "C4TrackInfo.h"
    ./Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc:    m_track_label = C4TrackInfo<C4Pho>::GetRef(_track);
    N[blyth@localhost junosw]$ 


Looks like label not there in non standalone running::

    135 G4bool junoPMTOpticalModel::ModelTrigger(const G4FastTrack &fastTrack)
    136 {
    137     _track = fastTrack.GetPrimaryTrack();
    138     _pv = _track->GetVolume() ;
    139     _mlv = _pv->GetMotherLogical();
    140 
    141     envelope_solid = fastTrack.GetEnvelopeSolid();
    142 
    143     pos     = fastTrack.GetPrimaryTrackLocalPosition();
    144     dir     = fastTrack.GetPrimaryTrackLocalDirection();
    145     pol     = fastTrack.GetPrimaryTrackLocalPolarization();
    146     time    = fastTrack.GetPrimaryTrack()->GetGlobalTime();
    147     energy  = fastTrack.GetPrimaryTrack()->GetKineticEnergy();
    148 
    149     dist2 = kInfinity ;
    150 
    151 #ifdef PMTSIM_STANDALONE
    152     m_track_label = C4TrackInfo<C4Pho>::GetRef(_track);
    153     assert( m_track_label && "all photon tracks must be labelled" );
    154 
    155     bool PIDX_DUMP = m_track_label->id == PIDX && PIDX_ENABLED ;
    156     LOG_IF(info, PIDX_DUMP) << " PIDX " << PIDX << " label.id " << m_track_label->id ;
    157 #endif


FIXED : Rebuild issue, fixed by getting nuclear
--------------------------------------------------

::

    Consolidate compiler generated dependencies of target GenTools
    make[2]: *** No rule to make target `/data/blyth/junotop/ExternalLibs/custom4/0.0.7/lib64/libCustom4.so', needed by `lib/libGenTools.so'.  Stop.
    make[1]: *** [Simulation/GenTools/CMakeFiles/GenTools.dir/all] Error 2
    make: *** [all] Error 2
    N[blyth@localhost build]$ 

HUH clean build of GenTools still gives::

    [100%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/IGenTool.cc.o
    [100%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/PostGenTools.cc.o
    [100%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/binding.cc.o
    make[2]: *** No rule to make target `/data/blyth/junotop/ExternalLibs/custom4/0.0.7/lib64/libCustom4.so', needed by `lib/libGenTools.so'.  Stop.
    make[1]: *** [Simulation/GenTools/CMakeFiles/GenTools.dir/all] Error 2
    make: *** [all] Error 2
    N[blyth@localhost GenTools]$ jt

    N[blyth@localhost junosw]$ cd build/Simulation/GenTools
    N[blyth@localhost GenTools]$ export VERBOSE=1
    N[blyth@localhost GenTools]$ make

/data/blyth/junotop/junosw/build/Simulation/GenTools/CMakeFiles/GenTools.dir/build.make::

   lib/libGenTools.so: /data/blyth/junotop/ExternalLibs/custom4/0.0.7/lib64/libCustom4.so

Even after clean build this path is stuck in the craw.::

    build/CMakeCache.txt:Custom4_LIBRARY_PATH:FILEPATH=/data/blyth/junotop/ExternalLibs/custom4/0.0.7/lib64/libCustom4.so
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ find build -type f -exec grep -H custom4/0.0.7 {} \;


FIXED : build issue : lots of opticks macro leaking, they need to be private
--------------------------------------------------------------------------------

Left field, looks like PMTSIM_STANDALONE macro is leaking::

    keFiles/PhysiSim.dir/src/OK_PHYSISIM_LOG.cc.o -MF CMakeFiles/PhysiSim.dir/src/OK_PHYSISIM_LOG.cc.o.d -o CMakeFiles/PhysiSim.dir/src/OK_PHYSISIM_LOG.cc.o -c /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/OK_PHYSISIM_LOG.cc
    In file included from /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc:2:
    /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh:9:10: fatal error: IGeomManager.h: No such file or directory
     #include "IGeomManager.h"
              ^~~~~~~~~~~~~~~~
    In file included from /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc:2:
    /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh:9:10: fatal error: IGeomManager.h: No such file or directory
     #include "IGeomManager.h"
              ^~~~~~~~~~~~~~~~
    compilation terminated.
    compilation terminated.

    [ 88%] Building CXX object Simulation/DetSimV2/PhysiSim/CMakeFiles/PhysiSim.dir/src/OK_PHYSISIM_LOG.cc.o
    cd
    /data/blyth/junotop/junosw/build/Simulation/DetSimV2/PhysiSim
    &&
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++
    -DBOOST_ATOMIC_DYN_LINK
    -DBOOST_ATOMIC_NO_LIB
    -DBOOST_FILESYSTEM_DYN_LINK
    -DBOOST_FILESYSTEM_NO_LIB
    -DBOOST_PROGRAM_OPTIONS_DYN_LINK
    -DBOOST_PROGRAM_OPTIONS_NO_LIB
    -DBOOST_PYTHON_DYN_LINK
    -DBOOST_PYTHON_NO_LIB
    -DBOOST_REGEX_DYN_LINK
    -DBOOST_REGEX_NO_LIB
    -DBOOST_SYSTEM_DYN_LINK
    -DBOOST_SYSTEM_NO_LIB
    -DDEBUG_PIDX
    -DDEBUG_TAG
    -DG4INTY_USE_XT
    -DG4MULTITHREADED
    -DG4UI_USE
    -DG4UI_USE_TCSH
    -DG4USE_STD11
    -DG4VERBOSE
    -DG4VIS_USE
    -DG4VIS_USE_OPENGL
    -DG4VIS_USE_OPENGLX
    -DG4VIS_USE_RAYTRACERX
    -DG4_STORE_TRAJECTORY
    -DOPTICKS_BRAP
    -DOPTICKS_CSG
    -DOPTICKS_CSGOPTIX
    -DOPTICKS_CSG_GGEO
    -DOPTICKS_G4CX
    -DOPTICKS_GDXML
    -DOPTICKS_GGEO
    -DOPTICKS_NPY
    -DOPTICKS_OKCONF
    -DOPTICKS_OKCORE
    -DOPTICKS_QUDARAP
    -DOPTICKS_SYSRAP
    -DOPTICKS_U4
    -DOPTICKS_X4
    -DPLOG_LOCAL
    -DPMTSIM_STANDALONE
    -DPhysiSim_EXPORTS
    -DSNIPER_VERSION_2
    -DSTANDALONE
    -DWITH_BOOST_ASIO
    -DWITH_CONTIGUOUS
    -DWITH_CUSTOM4
    -DWITH_G4CXOPTICKS
    -DWITH_G4CXOPTICKS_DEBUG
    -DWITH_NP
    -DWITH_OEC
    -DWITH_PMTSIM
    -DWITH_SGLM
    -DWITH_SLOG
    -DWITH_STTF
    -I/data/blyth/junotop/junosw/build/include
    -I/data/blyth/junotop/ExternalLibs/Boost/1.78.0
    -I/data/blyth/junotop/ExternalLibs/log4cpp/1.1.3/include
    -I/data/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/include
    -I/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/CLHEP/2.4.1.0/lib/CLHEP-2.4.1.0/../../include
    -I/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/geant4
    -I/data/blyth/junotop/ExternalLibs/HepMC/2.06.09/include
    -I/data/blyth/junotop/ExternalLibs




DONE : Rejigged to U4Recorder track labelling : including bumped Custom4 to 0.0.8 
-------------------------------------------------------------------------------------

Still the same error, junoPMTOpticalModel needs attention : lots only done for PMTSIM_STANDALONE


DONE : Track label status char "?DART" from junoPMTOpticalModel::DoIt only done for PMTSIM_STANDALONE
--------------------------------------------------------------------------------------------------------

::

    403 void junoPMTOpticalModel::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
    404 {
    ...
    592 #ifdef PMTSIM_STANDALONE
    593     // HMM: does the update immediate get back to the track ?
    594     LOG_IF(info, m_track_label->ix == PIDX && PIDX_ENABLED )
    595          << " PIDX " << PIDX
    596          << " track.GetMomentumDirection " << track->GetMomentumDirection()
    597          ;
    598 
    599     G4double& u0 = rand_absorb ;
    600     G4double& u1 = rand_escape ;
    601     G4double& D  = escape_fac ;
    602 
    603     char status = '?' ;
    604     if(      u0 < A)    status = u1 < D ? 'D' : 'A' ;
    605     else if( u0 < A+R)  status = 'R' ;
    606     else                status = 'T' ;
    607 
    608     m_track_label->uc4.w = status ;
    609 
    610     LOG(LEVEL)
    611         << " pmtid " << pmtid
    612         << " pmtcat " << pmtcat
    613         << " A " << A
    614         << " R " << R
    615         << " A+R " << A+R
    616         << " T " << ( 1. - (A+R) )
    617         << " D " << D
    618         << " u0 " << u0
    619         << " status " << status
    620         ;
    621 
    622 #endif
    623 
    624     return;
    625 }



DONE : try again with junoPMTOpticalModel enhancements
----------------------------------------------------------

::

    jxf ; N=0 GEOM=V0J008 ntds2



    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 296 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    SEvt::save@2100: SGeo::DefaultDir $DefaultOutputDir
    SEvt::save@2190:  dir /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000
    SEvt::save@2191: SEvt::descOutputDir dir_ $DefaultOutputDir dir  /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000 reldir ALL0 with_index Y index 0 this 0xb51020

                  SCRIPT :                                                                                                ntds2
                  LAYOUT :                                                                                      POM 1 VERSION 0
                 VERSION :                                                                                                    0
                    GEOM :                                                                                               V0J008
             COMMANDLINE : gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-unnatural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer opticks
               DIRECTORY :                                                                                   /tmp/u4debug/ntds2
        ${GEOM}_GEOMList :                                                                                      V0J008_GEOMList
    SEvt::gatherHit@1890:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@749: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           6.93100        6.93100      0.00085      
    DetSimAlg                1           19805.85742    19805.85742  3.43284      
    Sum of junotoptask       1           19812.92188    19812.92188  0.00000      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 2 WITH_G4CXOPTICKS 
    G4CXOpticks::Finalize@72: placeholder mimic G4Opticks 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    Delete G4SvcRunManager




::

    jxf ; N=1 GEOM=V1J008 ntds2


    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 2 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    SEvt::save@2100: SGeo::DefaultDir $DefaultOutputDir
    SEvt::save@2190:  dir /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000
    SEvt::save@2191: SEvt::descOutputDir dir_ $DefaultOutputDir dir  /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000 reldir ALL1 with_index Y index 0 this 0xb50e80

                  SCRIPT :                                                                                                ntds2
                  LAYOUT :                                                                                      POM 1 VERSION 1
                 VERSION :                                                                                                    1
                    GEOM :                                                                                               V1J008
             COMMANDLINE : gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-natural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer opticks
               DIRECTORY :                                                                                   /tmp/u4debug/ntds2
        ${GEOM}_GEOMList :                                                                                      V1J008_GEOMList
    SEvt::gatherHit@1890:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@749: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           8.50400        8.50400      0.00000      
    DetSimAlg                1           17481.63672    17481.63672  0.00000      
    Sum of junotoptask       1           17490.28320    17490.28320  3.07806      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully



DONE : Compare Those
----------------------

::

    epsilon:issues blyth$ jxn
    epsilon:ntds blyth$ ./ntds.sh grab_evt 


    CHECK=all_point ./ntds.sh ana 
    CHECK=few_point ./ntds.sh ana 

Now the N=0 go inside PMT just like N=1

::

    epsilon:ntds blyth$ ./ntds.sh cf
             BASH_SOURCE : ./ntds.sh 
                   CHECK : all_point 
                     arg : cf 
                  defarg : cf 
                     DIR : . 
            OPTICKS_MODE : 2 
                  SCRIPT : ntds2 
                    BASE :  
                     EVT : 000 
                   AGEOM : V0J008 
                   ABASE : /tmp/blyth/opticks/GEOM/V0J008/ntds2 
                   AFOLD : /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000 
                   BGEOM : V1J008 
                   BBASE : /tmp/blyth/opticks/GEOM/V1J008/ntds2 
                   BFOLD : /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000 
                       N :  
                 VERSION : -1 
    ./ntds.sh VERSION:-1 load both AFOLD and BFOLD

    QCF qcf 
    c2sum :  1310.9436 c2n :     8.0000 c2per:   163.8680  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  1310.94/8:163.868 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SA                   ' ' 0' '     0    387' '387.0000' '    -1      0']
     [' 1' 'TO BT BT BT BT BT SA                ' ' 1' '   364    112' '133.4118' '     3     98']
     [' 2' 'TO BT BT BT BT BT SD                ' ' 2' '   304      0' '304.0000' '     5     -1']
     [' 3' 'TO BT BT BT BT SD                   ' ' 3' '     0    301' '301.0000' '    -1      1']
     [' 4' 'TO BT BT BT BT BT BT BT SA          ' ' 4' '   109      0' '109.0000' '   133     -1']
     [' 5' 'TO BT BT BT BT BT BT BT SR SA       ' ' 5' '    38      0' '38.0000' '   110     -1']
     [' 6' 'TO BT BT BT BT BT SR SA             ' ' 6' '     0     38' '38.0000' '    -1    127']
     [' 7' 'TO AB                               ' ' 7' '    26     21' ' 0.5319' '    17     22']
     [' 8' 'TO BT BT BT BT BT BT BT SR SR SA    ' ' 8' '    18      0' ' 0.0000' '   142     -1']
     [' 9' 'TO BT BT BT BT BT SR SR SA          ' ' 9' '     0     14' ' 0.0000' '    -1    114']
     ['10' 'TO BT BT AB                         ' '10' '    10      9' ' 0.0000' '    39     25']


B has an extra BT causing terrible chi2

Check the positions::

    In [1]: aq[:10]
    Out[1]: 
    array([[b'TO BT BT BR BT BT BT SA                               '],
           [b'TO BT BT BT BT BT BR BT BT BT BT BT DR BT DR BT BT SA '],
           [b'TO BT BT BT BR BT BT BT BT SA                         '],
           [b'TO BT BT BT BT BT SA                                  '],
           [b'TO BT BT BT BT BT SA                                  '],
           [b'TO BT BT BT BT BT SD                                  '], #5
           [b'TO BT BT BT BT BT SD                                  '],
           [b'TO BT BT BT BT BT SD                                  '],
           [b'TO BT BT BR BT BT BT SA                               '],
           [b'TO BT BT BT BT BT SD                                  ']], dtype='|S96')

    In [2]: bq[:10]
    Out[2]: 
    array([[b'TO BT BT BT BT SA                                     '],
           [b'TO BT BT BT BT SD                                     '],
           [b'TO BT BT BT BT SA                                     '],
           [b'TO BT BT BR BT BT BT SA                               '],
           [b'TO BT BT BT BT SD                                     '],
           [b'TO BT BT BT BT SD                                     '], #5
           [b'TO BT BT BT BT SD                                     '],
           [b'TO BT BT BT BT SD                                     '],
           [b'TO BT BR BT BT SA                                     '],
           [b'TO BT BT BT BT SD                                     ']], dtype='|S96')



HMM these global frame positions difficult to grok, but extra just before last 
looks like a fake that is not being skipped::

    In [3]: a.f.record[5,:10,0]
    Out[3]: 
    array([[-11573.234,   9132.074,  11069.737,      0.1  ],
           [-12124.681,   9567.203,  11612.092,      4.191],
           [-12151.363,   9588.258,  11638.334,      4.389],
           [-12158.912,   9594.215,  11648.854,      4.463],
           [-12162.97 ,   9597.416,  11652.498,      4.492],
           [-12168.719,   9601.953,  11660.428,      4.547],  ## EXTRA JUST BEFORE LAST
           [-12168.721,   9601.954,  11660.43 ,      4.547],
           [     0.   ,      0.   ,      0.   ,      0.   ],
           [     0.   ,      0.   ,      0.   ,      0.   ],
           [     0.   ,      0.   ,      0.   ,      0.   ]], dtype=float32)

    In [4]: b.f.record[5,:10,0]
    Out[4]: 
    array([[-11573.234,   9132.074,  11069.737,      0.1  ],
           [-12124.681,   9567.203,  11612.092,      4.191],
           [-12151.363,   9588.258,  11638.334,      4.389],
           [-12158.912,   9594.215,  11648.854,      4.463],
           [-12162.97 ,   9597.416,  11652.498,      4.492],
           [-12168.721,   9601.954,  11660.43 ,      4.547],
           [     0.   ,      0.   ,      0.   ,      0.   ],
           [     0.   ,      0.   ,      0.   ,      0.   ],
           [     0.   ,      0.   ,      0.   ,      0.   ],
           [     0.   ,      0.   ,      0.   ,      0.   ]], dtype=float32)


Check the aux point spec status::

    In [3]: a.f.aux[5,:10,2,3].view(np.int32)
    Out[3]: array([ 0,  1,  2,  3,  4, -5,  6,  0,  0,  0], dtype=int32)
    ## HMM: -5: LOOKS LIKE FAKE SKIPPING IS NOT SWITCHED ON 

    In [4]: b.f.aux[5,:10,2,3].view(np.int32)   ## these enumerations are not directly comparable
    Out[4]: array([0, 1, 2, 3, 4, 5, 0, 0, 0, 0], dtype=int32)


DONE : Rerun with SPECS metadata saved to see what the enum mean
---------------------------------------------------------------------

Moved U4Recorder::SaveMeta to U4Recorder::EndOfEventAction so can see what those enum mean.

::

    jxf ; N=0 GEOM=V0J008 ntds2
    jxf ; N=1 GEOM=V1J008 ntds2


    epsilon:ntds blyth$ wc -l /tmp/blyth/opticks/GEOM/V?J008/ntds2/ALL?/000/U4R_names.txt
          66 /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000/U4R_names.txt
          54 /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000/U4R_names.txt
         120 total

::


    ## need np.abs as detected fakes that are not skipped are negated
    In [10]: np.c_[a.spec[5,:a.n[5]],a.SPECS[np.abs(a.spec[5,:a.n[5]])]]
    Out[10]: 
    array([['0', 'UNSET'],
           ['1', 'Water/Water:pInnerWater/pLPMT_Hamamatsu_R12860'],
           ['2', 'Water/AcrylicMask:pLPMT_Hamamatsu_R12860/HamamatsuR12860pMask'],
           ['3', 'AcrylicMask/Water:HamamatsuR12860pMask/pLPMT_Hamamatsu_R12860'],
           ['4', 'Water/Pyrex:pLPMT_Hamamatsu_R12860/HamamatsuR12860_PMT_20inch_log_phys'],
           ['-5', 'Pyrex/Pyrex:HamamatsuR12860_PMT_20inch_log_phys/HamamatsuR12860_PMT_20inch_body_phys'],
           ['6', 'Pyrex/Pyrex:HamamatsuR12860_PMT_20inch_body_phys/HamamatsuR12860_PMT_20inch_body_phys']], dtype='<U94')

    In [11]: np.c_[b.spec[5,:b.n[5]],b.SPECS[np.abs(b.spec[5,:b.n[5]])]]
    Out[11]: 
    array([['0', 'UNSET'],
           ['1', 'Water/Water:pInnerWater/pLPMT_Hamamatsu_R12860'],
           ['2', 'Water/AcrylicMask:pLPMT_Hamamatsu_R12860/HamamatsuR12860pMask'],
           ['3', 'AcrylicMask/Water:HamamatsuR12860pMask/pLPMT_Hamamatsu_R12860'],
           ['4', 'Water/Pyrex:pLPMT_Hamamatsu_R12860/HamamatsuR12860_PMT_20inch_log_phys'],
           ['5', 'Pyrex/Vacuum:HamamatsuR12860_PMT_20inch_log_phys/HamamatsuR12860_PMT_20inch_inner_phys']], dtype='<U93')


Encapsulate that into sevt.py::

    In [1]: a.spec_(5)
    Out[1]: 
    array([['0', 'UNSET'],
           ['1', 'Water/Water:pInnerWater/pLPMT_Hamamatsu_R12860'],
           ['2', 'Water/AcrylicMask:pLPMT_Hamamatsu_R12860/HamamatsuR12860pMask'],
           ['3', 'AcrylicMask/Water:HamamatsuR12860pMask/pLPMT_Hamamatsu_R12860'],
           ['4', 'Water/Pyrex:pLPMT_Hamamatsu_R12860/HamamatsuR12860_PMT_20inch_log_phys'],
           ['-5', 'Pyrex/Pyrex:HamamatsuR12860_PMT_20inch_log_phys/HamamatsuR12860_PMT_20inch_body_phys'],
           ['6', 'Pyrex/Pyrex:HamamatsuR12860_PMT_20inch_body_phys/HamamatsuR12860_PMT_20inch_body_phys']], dtype='<U94')

    In [2]: b.spec_(5)
    Out[2]: 
    array([['0', 'UNSET'],
           ['1', 'Water/Water:pInnerWater/pLPMT_Hamamatsu_R12860'],
           ['2', 'Water/AcrylicMask:pLPMT_Hamamatsu_R12860/HamamatsuR12860pMask'],
           ['3', 'AcrylicMask/Water:HamamatsuR12860pMask/pLPMT_Hamamatsu_R12860'],
           ['4', 'Water/Pyrex:pLPMT_Hamamatsu_R12860/HamamatsuR12860_PMT_20inch_log_phys'],
           ['5', 'Pyrex/Vacuum:HamamatsuR12860_PMT_20inch_log_phys/HamamatsuR12860_PMT_20inch_inner_phys']], dtype='<U93')



DONE : review U4Recorder::ClassifyFake skipping : is it going to work here, IT SHOULD
---------------------------------------------------------------------------------------

+-----------------+---------------------------------------------------------------------------+
| enum (0x1 << n) | U4Recorder::ClassifyFake heuristics, all contribute to fakemask           |  
+=================+===========================================================================+
| FAKE_STEP_MM    | step length less than EPSILON thats not a reflection turnaround           |
+-----------------+---------------------------------------------------------------------------+
| FAKE_FDIST      | distance to body_phys volume in direction of photon is less than EPSILON  |
+-----------------+---------------------------------------------------------------------------+
| FAKE_SURFACE    | body_phys solid frame localPoint EInside is kSurface (powerful)           |
+-----------------+---------------------------------------------------------------------------+
| FAKE_MANUAL     | manual selection via spec label (not recommended anymore)                 |
+-----------------+---------------------------------------------------------------------------+
| FAKE_VV_INNER12 | U4Step::IsSameMaterialPVBorder Vacuum inner1_phys/inner2_phys             |
+-----------------+---------------------------------------------------------------------------+


DONE : Rerun with fake skipping enabled
----------------------------------------

::

    jxf ; N=0 GEOM=V0J008 ntds2
    #jxf ; N=1 GEOM=V1J008 ntds2



DONE : Grab and compare : chi2 looks OK : but need higher stats 
------------------------------------------------------------------

::

   jxn ; 
   ./ntds.sh grab_evt 
   ./ntds.sh ana

::

    QCF qcf 
    c2sum :     2.7831 c2n :     6.0000 c2per:     0.4639  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)   2.78/6:0.464 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SA                         ' ' 0' '   364    387' ' 0.7044' '     3      0']
     [' 1' 'TO BT BT BT BT SD                         ' ' 1' '   304    301' ' 0.0149' '     5      1']
     [' 2' 'TO BT BT BT BT BT SA                      ' ' 2' '   110    112' ' 0.0180' '   102     98']
     [' 3' 'TO BT BT BT BT BT SR SA                   ' ' 3' '    41     38' ' 0.1139' '   110    127']
     [' 4' 'TO AB                                     ' ' 4' '    26     21' ' 0.5319' '    17     22']
     [' 5' 'TO BT BT BT BT BT SR SR SA                ' ' 5' '    21     14' ' 1.4000' '   142    114']
     [' 6' 'TO BT BT AB                               ' ' 6' '    10      9' ' 0.0000' '    39     25']
     [' 7' 'TO BT BT BT BT BT SR SR SR SA             ' ' 7' '     2      7' ' 0.0000' '   739    162']
     [' 8' 'TO BT BT BT BT BR BT BT BT BT BT BT AB    ' ' 8' '     6      1' ' 0.0000' '   451    466']
     [' 9' 'TO BT BT BT BT BT SR BR SA                ' ' 9' '     5      4' ' 0.0000' '   368    563']
     ['10' 'TO BT BT BT BT AB                         ' '10' '     5      4' ' 0.0000' '    41    244']



DONE : Higher stats run asserts from FastSim/SlowSim of reemission photon
-------------------------------------------------------------------------------

::

    jxf ; N=0 GEOM=V0J008 ntds2
    #jxf ; N=1 GEOM=V1J008 ntds2


FastSim of reemission photon::

    python: /data/blyth/junotop/opticks/u4/U4Recorder.cc:259: void U4Recorder::PreUserTrackingAction_Optical(const G4Track*): Assertion `resume_fSuspend == false' failed.

    (gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd29ac29e in U4Recorder::PreUserTrackingAction_Optical (this=0xb27110, track=0x24d94d520) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:259
    #5  0x00007fffd29abaa6 in U4Recorder::PreUserTrackingAction (this=0xb27110, track=0x24d94d520) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:179
    #6  0x00007fffcde089d6 in U4RecorderAnaMgr::PreUserTrackingAction (this=0xb4fe40, trk=0x24d94d520)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:33
    #7  0x00007fffce81dd39 in MgrOfAnaElem::PreUserTrackingAction (this=0x7fffcea2cb00 <MgrOfAnaElem::instance()::s_mgr>, trk=0x24d94d520)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #8  0x00007fffce12d163 in LSExpTrackingAction::PreUserTrackingAction (this=0x596b180, aTrack=0x24d94d520)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
    #9  0x00007fffdba8e5f0 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffdbcc5389 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #11 0x00007fffce5e345d in G4SvcRunManager::SimulateEvent (this=0x923b50, i_event=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29



    (gdb) f 5
    #5  0x00007fffd29abaa6 in U4Recorder::PreUserTrackingAction (this=0xb27110, track=0x24d94d520) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:179
    179	void U4Recorder::PreUserTrackingAction(const G4Track* track){  LOG(LEVEL) ; if(U4Track::IsOptical(track)) PreUserTrackingAction_Optical(track); }
    (gdb) f 4
    #4  0x00007fffd29ac29e in U4Recorder::PreUserTrackingAction_Optical (this=0xb27110, track=0x24d94d520) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:259
    259	        assert( resume_fSuspend == false ); 

    (gdb) list
    254	        }
    255	    }
    256	    else if( ulabel.gen() > 0 )
    257	    {
    258	        // HMM: FastSim/SlowSim transitions for reemission photons will trip this assert 
    259	        assert( resume_fSuspend == false ); 
    260	        sev->rjoinPhoton(ulabel); 
    261	    }
    262	    LOG(LEVEL) << "]" ; 
    263	}
    (gdb) p ulabel
    $1 = {static N = 4, gs = 0, ix = 90191, id = 90191, uc4 = {x = 2 '\002', y = 0 '\000', z = 0 '\000', w = 82 'R'}}
    (gdb) 



DONE : provide rjoin_resumePhoton method to handle this situation, that just does what resumePhoton 
-----------------------------------------------------------------------------------------------------

::

     245     if(ulabel.gen() == 0)
     246     {
     247         if(resume_fSuspend == false)
     248         {
     249             sev->beginPhoton(ulabel);  // THIS ZEROS THE SLOT 
     250         }
     251         else  // resume_fSuspend:true happens following FastSim ModelTrigger:YES, DoIt
     252         {
     253             sev->resumePhoton(ulabel);
     254         }
     255     }
     256     else if( ulabel.gen() > 0 )   // HMM: thats going to stick for reemission photons 
     257     {
     258         if(resume_fSuspend == false)
     259         {
     260             sev->rjoinPhoton(ulabel);
     261         }
     262         else   // resume_fSuspend:true happens following FastSim ModelTrigger:YES, DoIt
     263         {
     264             sev->rjoin_resumePhoton(ulabel);
     265         }
     266     }


ONHOLD : Single photon rerun of the reemission photon undergoing FastSim/SlowSim transition
----------------------------------------------------------------------------------------------

* suspect will need to debug reemission rjoin in future, not important now 


DONE : rerun with placeholder SEvt::rjoin_resumePhoton
--------------------------------------------------------

::

    jxf ; N=0 GEOM=V0J008 ntds2
    #jxf ; N=1 GEOM=V1J008 ntds2


    U4Cerenkov_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 0
    U4Scintillation_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 0
    U4Hit_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 10000
    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 29208 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    SEvt::save@2142: SGeo::DefaultDir $DefaultOutputDir
    SEvt::save@2232:  dir /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000
    SEvt::save@2233: SEvt::descOutputDir dir_ $DefaultOutputDir dir  /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000 reldir ALL0 with_index Y index 0 this 0xb501e0

                  SCRIPT :                                                                                                ntds2
                  LAYOUT :                                                                                      POM 1 VERSION 0
                 VERSION :                                                                                                    0
                    GEOM :                                                                                               V0J008
             COMMANDLINE : gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-unnatural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer opticks
               DIRECTORY :                                                                                   /tmp/u4debug/ntds2
        ${GEOM}_GEOMList :                                                                                      V0J008_GEOMList
    SEvt::gatherHit@1932:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@749: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           174.83400      174.83400    0.01751      
    DetSimAlg                1           1842971.12500  1842971.12500304.99874    
    Sum of junotoptask       1           1843146.12500  1843146.125000.00000      
    #############################################################################


::

    #jxf ; N=0 GEOM=V0J008 ntds2
    jxf ; N=1 GEOM=V1J008 ntds2



    U4Hit_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 189
    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 189 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    SEvt::save@2142: SGeo::DefaultDir $DefaultOutputDir
    SEvt::save@2232:  dir /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000
    SEvt::save@2233: SEvt::descOutputDir dir_ $DefaultOutputDir dir  /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000 reldir ALL1 with_index Y index 0 this 0xb500c0

                  SCRIPT :                                                                                                ntds2
                  LAYOUT :                                                                                      POM 1 VERSION 1
                 VERSION :                                                                                                    1
                    GEOM :                                                                                               V1J008
             COMMANDLINE : gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-natural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer opticks
               DIRECTORY :                                                                                   /tmp/u4debug/ntds2
        ${GEOM}_GEOMList :                                                                                      V1J008_GEOMList
    SEvt::gatherHit@1932:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@749: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           190.01700      190.01700    0.03603      
    DetSimAlg                1           1779382.62500  1779382.625000.00000      
    Sum of junotoptask       1           1779572.87500  1779572.875000.00000      
    #############################################################################



DONE : Compare high stats : chi2 matching when shooting Hama:0:1000
----------------------------------------------------------------------

::

    N[blyth@localhost ~]$ du -h /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000
    583M	/tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000
    N[blyth@localhost ~]$ du -h /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000
    583M	/tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/000

::

    CHECK=all_point ./ntds.sh ana  # all_point looks same  for N=0,1 : fake skipping working at 0th order

    QCF qcf 
    c2sum :    86.1359 c2n :   107.0000 c2per:     0.8050  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  86.14/107:0.805 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SA                          ' ' 0' ' 37047  36886' ' 0.3506' '     0      1']
     [' 1' 'TO BT BT BT BT SD                          ' ' 1' ' 29898  29846' ' 0.0453' '     6      3']
     [' 2' 'TO BT BT BT BT BT SA                       ' ' 2' ' 12157  12317' ' 1.0460' '  8819   9163']
     [' 3' 'TO BT BT BT BT BT SR SA                    ' ' 3' '  3641   3692' ' 0.3547' ' 10883  11145']
     [' 4' 'TO BT BT BT BT BT SR SR SA                 ' ' 4' '  2002   1910' ' 2.1636' ' 10886  10879']
     [' 5' 'TO AB                                      ' ' 5' '  1970   1959' ' 0.0308' '    46     23']
     [' 6' 'TO BT BT AB                                ' ' 6' '   836    863' ' 0.4291' '   120     33']
     [' 7' 'TO BT BT BT BT BT SR SR SR SA              ' ' 7' '   573    565' ' 0.0562' ' 14738  14725']
     [' 8' 'TO BT BT BT BT BR BT BT BT BT BT SA        ' ' 8' '   454    406' ' 2.6791' '  1055   1052']
     [' 9' 'TO BT BT BT BT BR BT BT BT BT BT BT AB     ' ' 9' '   380    416' ' 1.6281' ' 12054   8203']
     ['10' 'TO BT BT BT BT BR BT BT BT BT BT SD        ' '10' '   350    327' ' 0.7814' '  5250   5255']
     ['11' 'TO BT BT BT BT AB                          ' '11' '   312    340' ' 1.2025' '   133    639']
     ['12' 'TO BT BT BT BT BT SR BR SA                 ' '12' '   320    318' ' 0.0063' ' 33580  33567']
     ['13' 'TO BT BT BR BT BT BT SA                    ' '13' '   307    306' ' 0.0016' '    10      0']
     ['14' 'TO BT BT BT BT BR BT BT BT BT AB           ' '14' '   306    271' ' 2.1231' '   510   4396']
     ['15' 'TO BT BT BT BR BT BT BT BT SA              ' '15' '   280    269' ' 0.2204' '   209    197']



WIP : investigate hitCollection counts difference
------------------------------------------------------

::

    N=0 junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 29208 hitCollection_muon 0 hitCollection_opticks 0
    N=1 junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 189 hitCollection_muon 0 hitCollection_opticks 0


* Many input photons will be arriving at very close to the same time ? But thats true for both N=0 and N=1 ?
* HMM: is there hit merging happening here ? 
* Does hit merging work with opticksMode:2 ? 

* DONE : incorporate those hit counts into opticks logging 
* DONE : incorporate ProcessHits info into opticks SEvt

::

    optepsilon:ntds blyth$ jgr getMergerOpticks
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        PMTHitMerger*    getMergerOpticks() const ;  
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:1. sets m_pmthitmerger_opticks using  junoSD_PMT_v2::getMergerOpticks with result depending on m_opticksMode 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        m_pmthitmerger_opticks = m_jpmt->getMergerOpticks(); 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:junoSD_PMT_v2::getMergerOpticks
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:PMTHitMerger* junoSD_PMT_v2::getMergerOpticks() const 
    epsilon:junosw blyth$ 


DONE : basic instrumentation of junoSD_PMT_v2
------------------------------------------------

N=0::

    junoSD_PMT_v2::EndOfEvent@1131:  m_opticksMode 2 gpu_simulation  NO  hitCollection 296 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1139: junoSD_PMT_v2_Debug::desc
     ProcessHits_count     1486
     ProcessHits_true       296    //  296/1486  ~0.2
     ProcessHits_false     1190
     SaveNormHit_count      296
     SaveMuonHit_count        0

N=1::

    junoSD_PMT_v2::EndOfEvent@1131:  m_opticksMode 2 gpu_simulation  NO  hitCollection 2 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1139: junoSD_PMT_v2_Debug::desc
     ProcessHits_count      523
     ProcessHits_true         2     // 2/523  ~0.004 
     ProcessHits_false      521
     SaveNormHit_count        2
     SaveMuonHit_count        0


DONE : more detailed instrumentation and make pmt_log sensitive
------------------------------------------------------------------

Q: Why is ProcessHits_count 1486 for N=0 but only 523 for N=1 ? 
A: Mostly it seems due to pmt_log not being sensitive. 
   
Q: Why is ProcessHits_true/ProcessHits_count fraction much lower for N=1 ? 
A: After pmt_log sensitive are much closer. 

N=0,1 edited together, first without HAMA pmt_log being sensitive in N=1::

    N=0 junoSD_PMT_v2::EndOfEvent@1186:  m_opticksMode 2 gpu_simulation  NO  hitCollection 296 hitCollection_muon 0 hitCollection_opticks 0
    N=1 junoSD_PMT_v2::EndOfEvent@1186:  m_opticksMode 2 gpu_simulation  NO  hitCollection 2 hitCollection_muon 0 hitCollection_opticks 0
    
    N=0                                 N=1 
     ProcessHits_count      1486         ProcessHits_count       523
     ProcessHits_true        296         ProcessHits_true          2
     ProcessHits_false      1190         ProcessHits_false       521
     SaveNormHit_count       296         SaveNormHit_count         2
     SaveMuonHit_count         0         SaveMuonHit_count         0
               EPH_UNSET       0                   EPH_UNSET       0
                EPH_NDIS       0                    EPH_NDIS       0
                EPH_NOPT       0                    EPH_NOPT       0
               EPH_NEDEP    1153                   EPH_NEDEP     514
              EPH_NBOUND       0                  EPH_NBOUND       0
               EPH_NPROC       0                   EPH_NPROC       0
             EPH_NDETECT       0                 EPH_NDETECT       0
             EPH_NDECULL      37                 EPH_NDECULL       7
              EPH_YMERGE       0                  EPH_YMERGE       0
               EPH_YSAVE     296                   EPH_YSAVE       2

N=0,1 edited together, now with HAMA pmt_log sensitive::

    N=0 junoSD_PMT_v2::EndOfEvent@1186:  m_opticksMode 2 gpu_simulation  NO  hitCollection 296 hitCollection_muon 0 hitCollection_opticks 0
    N=1 junoSD_PMT_v2::EndOfEvent@1186:  m_opticksMode 2 gpu_simulation  NO  hitCollection 266 hitCollection_muon 0 hitCollection_opticks 0

    N=0                                 N=1
     ProcessHits_count      1486         ProcessHits_count      1815
     ProcessHits_true        296         ProcessHits_true        266
     ProcessHits_false      1190         ProcessHits_false      1549
     SaveNormHit_count       296         SaveNormHit_count       266
     SaveMuonHit_count         0         SaveMuonHit_count         0
               EPH_UNSET       0    #0             EPH_UNSET       0
                EPH_NDIS       0    #1              EPH_NDIS       0
                EPH_NOPT       0    #2              EPH_NOPT       0
               EPH_NEDEP    1153    #3             EPH_NEDEP    1520   
              EPH_NBOUND       0    #4            EPH_NBOUND       4
               EPH_NPROC       0    #5             EPH_NPROC       0
             EPH_NDETECT       0    #6           EPH_NDETECT       0
             EPH_NDECULL      37    #7           EPH_NDECULL      25
              EPH_YMERGE       0    #8            EPH_YMERGE       0
               EPH_YSAVE     296    #9             EPH_YSAVE     266


DONE : include eph enum into current_aux, getting ProcessHits info into SEvt
------------------------------------------------------------------------------

Q: How to associate ProcessHits info like eph back into the opticks SEvt ? 
A: Write eph into C4Pho G4Track info label, and from U4Recorder::UserSteppingAction  
   copy that into current_aux for each step point ?    

So can viz the photons with the different EPH enum values::

    In [41]: a_eph = a.f.aux[:,:,2,2].copy().view(np.uint8).reshape(-1,32,4)
    In [42]: b_eph = b.f.aux[:,:,2,2].copy().view(np.uint8).reshape(-1,32,4)

    In [43]: np.c_[np.unique( a_eph[:,:,1], return_counts=True )]
    Out[43]: 
    array([[    0, 29826],
           [    3,  1841],  # EPH_NEDEP
           [    7,    37],  # EPH_NDECULL
           [    9,   296]]) # EPH_YSAVE

    In [44]: np.c_[np.unique( b_eph[:,:,1], return_counts=True )]
    Out[44]: 
    array([[    0, 29651],
           [    3,  2054],  # EPH_NEDEP
           [    4,     4],  # EPH_NBOUND 
           [    7,    25],  # EPH_NDECULL
           [    9,   266]]) # EPH_YSAVE


TODO : make sense of a_eph b_eph values wrt photon histories, positions, spec etc..
---------------------------------------------------------------------------------------

TODO : redo the above with higher stats    
------------------------------------------

* but first, need to get logging controlled

::

    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 694  694[  0,  0,  0, 68]) eph EPH_YSAVE
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 693  693[  0,  0,  0, 65]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 692  692[  0,  0,  0, 65]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 691  691[  0,  0,  0, 84]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 691  691[  0,  0,  0, 84]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 690  690[  0,  0,  0, 65]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 689  689[  0,  0,  0, 65]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 688  688[  0,  0,  0, 84]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 688  688[  0,  0,  0, 84]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 687  687[  0,  0,  0, 68]) eph EPH_YSAVE
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 686  686[  0,  0,  0, 65]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 685  685[  0,  0,  0, 84]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 685  685[  0,  0,  0, 84]) eph EPH_NEDEP
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 684  684[  0,  0,  0, 68]) eph EPH_YSAVE
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 683  683[  0,  0,  0, 68]) eph EPH_YSAVE
    junoSD_PMT_v2::ProcessHits@364:  label C4Pho (gs:ix:id:gn   0 682  682[  0,  0,  0, 84]) eph EPH_NEDEP


DONE : Maybe need pmt_log volume as sensitive with N=1, not just inner_log as now ?
--------------------------------------------------------------------------------------

jcv HamamatsuR12860PMTManager::

     713 void
     714 HamamatsuR12860PMTManager::helper_make_logical_volume()
     715 {
     716     if( m_UsePMTNaturalGeometry == false )
     717     {
     718         pmt_log = new G4LogicalVolume
     719             ( pmt_solid,
     720               GlassMat,
     721               GetName()+"_log" );
     722 
     723         body_log= new G4LogicalVolume
     724             ( body_solid,
     725               GlassMat,
     726               GetName()+"_body_log" );
     727 
     728         body_log->SetSensitiveDetector(m_detector);
     729 
     730         inner1_log= new G4LogicalVolume
     731             ( inner1_solid,
     732               PMT_Vacuum,
     733               GetName()+"_inner1_log" );
     734 
     735         inner1_log->SetSensitiveDetector(m_detector);
     736 
     737         inner2_log= new G4LogicalVolume
     738             ( inner2_solid,
     739               PMT_Vacuum,
     740               GetName()+"_inner2_log" );
     741 
     742         m_logical_pmt = pmt_log ;
     743     }
     744     else
     745     {
     746         pmt_log = new G4LogicalVolume
     747             ( pmt_solid,
     748               GlassMat,
     749               GetName()+"_log" );
     750 
     751         inner_log= new G4LogicalVolume
     752             ( inner_solid,
     753               PMT_Vacuum,
     754               GetName()+"_inner_log" );
     755 
     756         inner_log->SetSensitiveDetector(m_detector);
     757         m_logical_pmt = pmt_log ;
     758     }
     759 
     760 }


Changed that to::

     744     else
     745     {
     746         pmt_log = new G4LogicalVolume
     747             ( pmt_solid,
     748               GlassMat,
     749               GetName()+"_log" );
     750         pmt_log->SetSensitiveDetector(m_detector);
     751         // G4SteppingManager::Stepping only calls Hit/ProcessHits 
     752         // when the prestep point volume is sensitive so for 
     753         // sensitive boundary need to set two volumes as sensitive 
     754    
     755         inner_log= new G4LogicalVolume
     756             ( inner_solid,
     757               PMT_Vacuum,
     758               GetName()+"_inner_log" );
     759    
     760         inner_log->SetSensitiveDetector(m_detector);
     761         m_logical_pmt = pmt_log ;
     762     }



TODO : Same fix for NNVT 
---------------------------

  

DONE : Review ProcessHits : prestep point volume needs to be sensitive for Hit/ProcessHits to run
----------------------------------------------------------------------------------------------------

::

   79 class junoSD_PMT_v2 : public G4VSensitiveDetector, public IToolForSD_PMT


g4-cls G4VSensitiveDetector::

    113   public: // with description
    114       inline G4bool Hit(G4Step*aStep)
    115       { 
    116         G4TouchableHistory* ROhis = 0;
    117         if(!isActive()) return false;
    118         if(filter)
    119         { if(!(filter->Accept(aStep))) return false; }
    120         if(ROgeometry)
    121         { if(!(ROgeometry->CheckROVolume(aStep,ROhis))) return false; }
    122         return ProcessHits(aStep,ROhis);
    123       }

g4-cls G4SteppingManager::

    116 G4StepStatus G4SteppingManager::Stepping()
    ...
    221 // Update 'TrackLength' and remeber the Step length of the current Step
    222    fTrack->AddTrackLength(fStep->GetStepLength());
    223    fPreviousStepSize = fStep->GetStepLength();
    224    fStep->SetTrack(fTrack);
    225 #ifdef G4VERBOSE
    226                          // !!!!! Verbose
    227 
    228            if(verboseLevel>0) fVerbose->StepInfo();
    229 #endif
    230 // Send G4Step information to Hit/Dig if the volume is sensitive
    231    fCurrentVolume = fStep->GetPreStepPoint()->GetPhysicalVolume();
    232    StepControlFlag =  fStep->GetControlFlag();
    233    if( fCurrentVolume != 0 && StepControlFlag != AvoidHitInvocation) {
    234       fSensitive = fStep->GetPreStepPoint()->
    235                                    GetSensitiveDetector();
    236       if( fSensitive != 0 ) {
    237         fSensitive->Hit(fStep);
    238       }
    239    }
    240 
    241 // User intervention process.
    242    if( fUserSteppingAction != 0 ) {
    243       fUserSteppingAction->UserSteppingAction(fStep);
    244    }
    245    G4UserSteppingAction* regionalAction
    246     = fStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetRegion()
    247       ->GetRegionalSteppingAction();
    248    if( regionalAction ) regionalAction->UserSteppingAction(fStep);
    249 
    250 // Stepping process finish. Return the value of the StepStatus.
    251    return fStepStatus;
    252 
    253 }



TODO : add presentation plots and chi2 tables for these comparisons
----------------------------------------------------------------------

TODO : target NNVT and do comparisons 
----------------------------------------

* heavy 600M SEvt for 100k input photons, so complete Hama presentation plots before doing NNVT


TODO : simtrace running insitu : how to do that ?
-----------------------------------------------------

* moved simtrace_scan to U4Tree


