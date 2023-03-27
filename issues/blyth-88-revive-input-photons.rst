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






