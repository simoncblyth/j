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






