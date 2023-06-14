revive_junosw_opticksMode_1_and_3_plus_simtrace_cxs
=======================================================

The goal is junosw opticksMode 1 and 3 initially with input photons.  
But getting there will be faster with more standalone tests 
like simtrace or things like the below initially.:


DONE : sort out CSGOptiX API for minimal render/simtrace/simulate
--------------------------------------------------------------------

While the code is minimal all these are using full CSGFoundry geometry::

    epsilon:CSGOptiX blyth$ l tests/CSGOptiX*MTest.cc
    8 -rw-r--r--  1 blyth  staff  205 Jun 13 16:29 tests/CSGOptiXTMTest.cc
    8 -rw-r--r--  1 blyth  staff  255 Jun 13 13:56 tests/CSGOptiXSMTest.cc
    8 -rw-r--r--  1 blyth  staff  343 Jun 13 13:55 tests/CSGOptiXRMTest.cc
    epsilon:CSGOptiX blyth$ 

    epsilon:CSGOptiX blyth$ l *_min.sh 
    8 -rwxr-xr-x  1 blyth  staff  2336 Jun 13 17:23 cxt_min.sh
    8 -rwxr-xr-x  1 blyth  staff  2701 Jun 13 16:33 cxs_min.sh
    8 -rwxr-xr-x  1 blyth  staff  3659 Jun 13 13:56 cxr_min.sh
    epsilon:CSGOptiX blyth$ 
        


Issue 1 : Getting all SR off the PMT : as expected : need to "Custom4" special case the surface name
------------------------------------------------------------------------------------------------------

::

    epsilon:CSGOptiX blyth$ ./cxs_min.sh ana
    CSGFoundry.CFBase returning [/Users/blyth/.opticks/GEOM/V1J009], note:[via GEOM] 
    GLOBAL:0 MODE:3
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ['/Users/blyth/.opticks/GEOM/V1J009/CSGOptiXSMTest/ALL/000'] quiet:1
    INFO:opticks.ana.pvplt:init_ee with_photon_meta:0 with_ff:0
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol e pid -1 opt  off [0. 0. 0.] 
    SEvt symbol e pid -1 opt  off [0. 0. 0.] e.f.base /Users/blyth/.opticks/GEOM/V1J009/CSGOptiXSMTest/ALL/000 
    INFO:opticks.ana.pvplt:minimal_qtab : np.c_[nq,iq,uq][oq][:10] 
    [[b'746' b'185' b'TO BT BT BT BT SA                                                                               ']
     [b'734' b'1736' b'TO BT BT BT BT SR BT BT BT BT BT BT AB                                                          ']
     [b'372' b'1666' b'TO BT BT BT BT SR BT BT BT BT AB                                                                ']
     [b'227' b'2189' b'TO BT BT BT BT SR BT BT BT BT BT BT SC AB                                                       ']
     [b'91' b'319' b'TO BT BT BT BT SR BR BR BR BR BR BR BR BT DR AB                                                 ']
     [b'90' b'1641' b'TO BT BT BT BT SR BT BT BT BT BT AB                                                             ']
     [b'86' b'2198' b'TO BT BT BT BT SR BT BT BT BT BT BT SC SC AB                                                    ']
     [b'84' b'0' b'TO BT BT BR BR BR BR BT SA                                                                      ']
     [b'80' b'26' b'TO BT BT AB                                                                                     ']
     [b'69' b'349' b'TO BT BT BT BT SR BR BR BR BR BR BR BR BT SA                                                    ']]



WIP : Convert FewPMT geometry from PMTSim into CSGFoundry 
-------------------------------------------------------------

For shakedown of Custom4 equivalent GPU side prefer using simpler FewPMT geometry. 
So start by saving a FewPMT geometry into CSGFoundry and running the three minimals on it 
FewPMT running was done in u4 using PMTSim. 

But u4 does not depend on CSG so cannot convert there. 
So get a G4CX test to do the PV to CSGFoundry conversion. 

gxt::

    G4CXOpticks_setGeometry_Test.sh 

    001 /**
      2 G4CXOpticks_setGeometry_Test.cc
      3 =================================
      4 
      5 Action depends on envvars such as OpticksGDMLPath, see G4CXOpticks::setGeometry
      6 
      7 **/
      8 
      9 #include "OPTICKS_LOG.hh"
     10 #include "G4CXOpticks.hh"
     11 
     12 int main(int argc, char** argv)
     13 {
     14     OPTICKS_LOG(argc, argv);
     15     
     16     G4CXOpticks::SetGeometry();
     17     
     18     return 0 ;
     19 }   



    153 void G4CXOpticks::setGeometry()
    ...
    192     else if(SSys::hasenvvar("GEOM"))
    193     {
    194         LOG(LEVEL) << " GEOM/U4VolumeMaker::PV " ;
    195         setGeometry( U4VolumeMaker::PV() );  // this may load GDML using U4VolumeMaker::PVG if "GEOM"_GDMLPath is defined   
    196     }






::

    epsilon:tests blyth$ ./G4CXOpticks_setGeometry_Test.sh dbg
    ./G4CXOpticks_setGeometry_Test.sh : GEOM FewPMT : sourcing geomscript /Users/blyth/opticks/g4cx/tests/../../u4/tests/FewPMT.sh
    BASH_SOURCE                    : /Users/blyth/opticks/g4cx/tests/../../u4/tests/FewPMT.sh 
    VERSION                        : 1 
    version_desc                   : N=1 natural geometry : CustomBoundary 
    POM                            : 1 
    pom_desc                       : POM:1 allow photons into PMT which has innards 
    GEOM                           : FewPMT 
    FewPMT_GEOMList                : nnvtLogicalPMT 
    LAYOUT                         : one_pmt 
    G4CXOpticks=INFO
    CSGFoundry=INFO
    Dummy=INFO
    GSurfaceLib=INFO
    HEAD
    TAIL -o run
    /Applications/Xcode/Xcode_10_1.app/Contents/Developer/usr/bin/lldb -f G4CXOpticks_setGeometry_Test -o run --
    (lldb) target create "/usr/local/opticks/lib/G4CXOpticks_setGeometry_Test"
    Current executable set to '/usr/local/opticks/lib/G4CXOpticks_setGeometry_Test' (x86_64).
    (lldb) run
    SLOG::EnvLevel adjusting loglevel by envvar   key GSurfaceLib level INFO fallback DEBUG upper_level INFO
    SLOG::EnvLevel adjusting loglevel by envvar   key CSGFoundry level INFO fallback DEBUG upper_level INFO
    SLOG::EnvLevel adjusting loglevel by envvar   key G4CXOpticks level INFO fallback DEBUG upper_level INFO
    2023-06-14 12:14:26.968 INFO  [14498525] [G4CXOpticks::init@116] CSGOptiX::Desc Version 6 PTXNAME CSGOptiX6 GEO_PTXNAME CSGOptiX6geo
    G4CXOpticks::desc sim 0x10c85a050 tr 0x0 wd 0x0 gg 0x0 fd 0x0 cx N qs N
    2023-06-14 12:14:26.969 INFO  [14498525] [G4CXOpticks::setGeometry@162]  argumentless 
    2023-06-14 12:14:26.969 INFO  [14498525] [G4CXOpticks::setGeometry@201]  GEOM/U4VolumeMaker::PV 
    U4VolumeMaker::PV name FewPMT
    U4VolumeMaker::PVG_ name FewPMT gdmlpath - sub - exists 0
    [ PMTSim::GetLV [nnvtLogicalPMT]
    PMTSim::init                   yielded chars :  cout  24933 cerr      0 : set VERBOSE to see them 
    PMTSim::getLV geom [nnvtLogicalPMT] mgr Y head [LogicalPMT]
    Option RealSurface is enabled in Central Detector.  Reduce the m_pmt_h from 570 to 357.225
     GetName() nnvt
    NNVT_MCPPMT_PMTSolid::NNVT_MCPPMT_PMTSolid
    G4Material::GetMaterial() WARNING: The material: PMT_Mirror does not exist in the table. Return NULL pointer.
    Warning: setting PMT mirror reflectivity to 0.9999 because no PMT_Mirror material properties defined
    [ ZSolid::ApplyZCutTree zcut    173.225 pmt_delta      0.001 body_delta     -4.999 inner_delta     -5.000 zcut+pmt_delta    173.226 zcut+body_delta    168.226 zcut+inner_delta    168.225
    ] ZSolid::ApplyZCutTree zcut 173.225
    Option RealSurface is enabed. Reduce the height of tube_hz from 60.000 to 21.112
    ] PMTSim::GetLV [nnvtLogicalPMT] lv Y
    2023-06-14 12:14:27.030 INFO  [14498525] [G4CXOpticks::setGeometry@242]  G4VPhysicalVolume world 0x10cd10100
    2023-06-14 12:14:27.107 INFO  [14498525] [GSurfaceLib::GSurfaceLib@173] 
    2023-06-14 12:14:27.207 INFO  [14498525] [GSurfaceLib::add@332]  GBorderSurface  name ChimneyTyvekSurface pv1 pLowerChimneyAcrylic pv2 pLowerChimneyTyvek keys REFLECTIVITY has_EFFICIENCY 0
    2023-06-14 12:14:27.209 INFO  [14498525] [*GSurfaceLib::createStandardSurface@475]  is_sensor 0
    2023-06-14 12:14:27.209 INFO  [14498525] [GSurfaceLib::add@332]  GBorderSurface  name nnvt_mcp_plate_opsurface pv1 nnvt_inner_phys pv2 nnvt_plate_phy keys REFLECTIVITY has_EFFICIENCY 0
    2023-06-14 12:14:27.209 INFO  [14498525] [*GSurfaceLib::createStandardSurface@475]  is_sensor 0
    2023-06-14 12:14:27.210 INFO  [14498525] [GSurfaceLib::add@332]  GBorderSurface  name nnvt_mcp_edge_opsurface pv1 nnvt_inner_phys pv2 nnvt_edge_phy keys REFLECTIVITY has_EFFICIENCY 0
    2023-06-14 12:14:27.210 INFO  [14498525] [*GSurfaceLib::createStandardSurface@475]  is_sensor 0
    2023-06-14 12:14:27.210 INFO  [14498525] [GSurfaceLib::add@332]  GBorderSurface  name nnvt_mcp_tube_opsurface pv1 nnvt_inner_phys pv2 nnvt_tube_phy keys REFLECTIVITY has_EFFICIENCY 0
    2023-06-14 12:14:27.210 INFO  [14498525] [*GSurfaceLib::createStandardSurface@475]  is_sensor 0
    2023-06-14 12:14:27.211 INFO  [14498525] [GSurfaceLib::add@332]  GBorderSurface  name nnvt_mcp_opsurface pv1 nnvt_inner_phys pv2 nnvt_mcp_phy keys REFLECTIVITY has_EFFICIENCY 0
    2023-06-14 12:14:27.211 INFO  [14498525] [*GSurfaceLib::createStandardSurface@475]  is_sensor 0
    2023-06-14 12:14:27.212 INFO  [14498525] [GSurfaceLib::add@332]  GBorderSurface  name water_rock_bs pv1 Water_lv_pv pv2 Rock_lv_pv keys RINDEX REFLECTIVITY GROUPVEL has_EFFICIENCY 0
    2023-06-14 12:14:27.212 INFO  [14498525] [*GSurfaceLib::createStandardSurface@475]  is_sensor 0
    2023-06-14 12:14:27.212 INFO  [14498525] [GSurfaceLib::add@393]  GSkinSurface  name nnvt_photocathode_mirror_logsurf keys REFLECTIVITY has_EFFICIENCY 0
    2023-06-14 12:14:27.213 INFO  [14498525] [*GSurfaceLib::createStandardSurface@475]  is_sensor 0
    2023-06-14 12:14:27.216 INFO  [14498525] [GSurfaceLib::sort@642]  not sorting 
    2023-06-14 12:14:27.217 INFO  [14498525] [*GSurfaceLib::createMeta@958] 
    2023-06-14 12:14:27.217 INFO  [14498525] [GSurfaceLib::dumpSkinSurface@1486] dumpSkinSurface
    2023-06-14 12:14:27.217 INFO  [14498525] [GSurfaceLib::dumpSkinSurface@1491]  SS    0 :         nnvt_photocathode_mirror_logsurf : nnvt_inner_log
    2023-06-14 12:14:27.283 INFO  [14498525] [BFile::preparePath@837] created directory /tmp/blyth/opticks/GGeo/GItemList
    2023-06-14 12:14:27.309 INFO  [14498525] [BFile::preparePath@837] created directory /tmp/blyth/opticks/GGeo/GNodeLib
    2023-06-14 12:14:27.313 INFO  [14498525] [GSurfaceLib::save@100] 
    2023-06-14 12:14:27.321 INFO  [14498525] [G4CXOpticks::setGeometry@263] 
    2023-06-14 12:14:27.322 INFO  [14498525] [CSGFoundry::setMeta@162]                      : -
    2023-06-14 12:14:27.322 INFO  [14498525] [CSGFoundry::setMeta@162]                 HOME : /Users/blyth
    2023-06-14 12:14:27.322 INFO  [14498525] [CSGFoundry::setMeta@162]                 USER : blyth
    2023-06-14 12:14:27.322 INFO  [14498525] [CSGFoundry::setMeta@162]               SCRIPT : -
    2023-06-14 12:14:27.322 INFO  [14498525] [CSGFoundry::setMeta@162]                  PWD : /Users/blyth/opticks/g4cx/tests
    2023-06-14 12:14:27.322 INFO  [14498525] [CSGFoundry::setMeta@162]              CMDLINE : -
    2023-06-14 12:14:27.344 INFO  [14498525] [G4CXOpticks::setGeometry_@303] [ fd 0x10bf538e0
    2023-06-14 12:14:27.344 INFO  [14498525] [G4CXOpticks::setGeometry_@307]  Calling SEvt::Create 
    2023-06-14 12:14:27.344 INFO  [14498525] [G4CXOpticks::setGeometry_@325]  skip CSGOptiX::Create as NoGPU has been set 
    2023-06-14 12:14:27.344 INFO  [14498525] [G4CXOpticks::setGeometry_@332]  cx N qs N QSim::Get N
    2023-06-14 12:14:27.344 INFO  [14498525] [G4CXOpticks::setGeometry_@338] ] fd 0x10bf538e0
    2023-06-14 12:14:27.344 INFO  [14498525] [CSGFoundry::getFrameE@3187]  ipf 0
    2023-06-14 12:14:27.344 INFO  [14498525] [G4CXOpticks::setupFrame@373] sframe::desc inst 0 frs 0
     ekvid sframe_OPTICKS_INPUT_PHOTON_FRAME_0 ek OPTICKS_INPUT_PHOTON_FRAME ev 0
     ce  ( 0.000, 0.000, 0.000,373.333)  is_zero 0
     m2w ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000,   nan) ( 0.000, 0.000, 0.000,   nan) 
     w2m ( 1.000,-0.000, 0.000, 0.000) (-0.000, 1.000,-0.000, 0.000) ( 0.000,-0.000, 1.000,   nan) (-0.000, 0.000,-0.000,   nan) 
     midx    0 mord    0 iidx    0
     inst    0
     ix0     0 ix1     0 iy0     0 iy1     0 iz0     0 iz1     0 num_photon    0
     ins     0 gas     0 sensor_identifier       -1 sensor_index     -1
     propagate_epsilon    0.05000 is_hostside_simtrace NO

    Process 30296 exited with status = 0 (0x00000000) 

    Process 30296 launched: '/usr/local/opticks/lib/G4CXOpticks_setGeometry_Test' (x86_64)
    (lldb) 



Surprise directory to write to::

    epsilon:tests blyth$ l /tmp/blyth/opticks/GGeo/
    total 16
    8 -rw-r--r--   1 blyth  wheel  285 Jun 14 12:14 cachemeta.json
    0 drwxr-xr-x  15 blyth  wheel  480 Jun 14 12:14 .
    8 -rw-r--r--   1 blyth  wheel  222 Jun 14 12:14 runcomment.txt
    0 drwxr-xr-x  14 blyth  wheel  448 Jun 14 12:14 stree
    0 drwxr-xr-x   3 blyth  wheel   96 Jun 14 12:14 GBndLib
    0 drwxr-xr-x   6 blyth  wheel  192 Jun 14 12:14 GItemList
    0 drwxr-xr-x   3 blyth  wheel   96 Jun 14 12:14 GSourceLib
    0 drwxr-xr-x   5 blyth  wheel  160 Jun 14 12:14 GSurfaceLib
    0 drwxr-xr-x   4 blyth  wheel  128 Jun 14 12:14 GMaterialLib
    0 drwxr-xr-x  11 blyth  wheel  352 Jun 14 12:14 GNodeLib
    0 drwxr-xr-x  11 blyth  wheel  352 Jun 14 12:14 GMeshLib
    0 drwxr-xr-x  10 blyth  wheel  320 Jun 14 12:14 GMeshLibNCSG
    0 drwxr-xr-x   3 blyth  wheel   96 Jun 14 12:14 GPts
    0 drwxr-xr-x   3 blyth  wheel   96 Jun 14 12:14 GMergedMesh



Plant std::raise(SIGINT) to find where writing done::

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGINT
      * frame #0: 0x00007fff77104b66 libsystem_kernel.dylib`__pthread_kill + 10
        frame #1: 0x00007fff772cf080 libsystem_pthread.dylib`pthread_kill + 333
        frame #2: 0x00007fff770126fe libsystem_c.dylib`raise + 26
        frame #3: 0x000000010aa48da6 libBoostRap.dylib`BFile::preparePath(dir_="/tmp/blyth/opticks/GGeo/GPts/0", name="GPts.txt", create=true) at BFile.cc:836
        frame #4: 0x000000010aa48993 libBoostRap.dylib`BFile::preparePath(dir_="/tmp/blyth/opticks/GGeo/GPts/0", reldir_=0x0000000000000000, name="GPts.txt", create=true) at BFile.cc:815
        frame #5: 0x0000000106a9e388 libGGeo.dylib`GItemList::save(this=0x000000010cc48d10, idpath="/tmp/blyth/opticks/GGeo/GPts/0") at GItemList.cc:105
        frame #6: 0x0000000106c28d70 libGGeo.dylib`GPts::save(this=0x000000010cc48d90, dir="/tmp/blyth/opticks/GGeo/GPts/0") at GPts.cc:76
        frame #7: 0x0000000106c58e08 libGGeo.dylib`GGeoLib::saveConstituents(this=0x000000010ca38eb0, idpath="/tmp/blyth/opticks/GGeo") at GGeoLib.cc:329
        frame #8: 0x0000000106c585a0 libGGeo.dylib`GGeoLib::save(this=0x000000010ca38eb0) at GGeoLib.cc:167
        frame #9: 0x0000000106ccbdbc libGGeo.dylib`GGeo::save_(this=0x000000010ca365b0) at GGeo.cc:833
        frame #10: 0x0000000106cc8b2a libGGeo.dylib`GGeo::save(this=0x000000010ca365b0) at GGeo.cc:821
        frame #11: 0x0000000106cc7ca9 libGGeo.dylib`GGeo::postDirectTranslation(this=0x000000010ca365b0) at GGeo.cc:632
        frame #12: 0x000000010080d6e1 libExtG4.dylib`X4Geo::Translate(top=0x000000010cd004e0) at X4Geo.cc:27
        frame #13: 0x000000010018c7d8 libG4CX.dylib`G4CXOpticks::setGeometry(this=0x000000010c850a30, world=0x000000010cd004e0) at G4CXOpticks.cc:256
        frame #14: 0x000000010018c3da libG4CX.dylib`G4CXOpticks::setGeometry(this=0x000000010c850a30) at G4CXOpticks.cc:202
        frame #15: 0x000000010018b570 libG4CX.dylib`G4CXOpticks::SetGeometry() at G4CXOpticks.cc:59
        frame #16: 0x000000010003efbf G4CXOpticks_setGeometry_Test`main(argc=1, argv=0x00007ffeefbfe598) at G4CXOpticks_setGeometry_Test.cc:17
        frame #17: 0x00007fff76fb4015 libdyld.dylib`start + 1
        frame #18: 0x00007fff76fb4015 libdyld.dylib`start + 1
    (lldb) 



    (lldb) f 7
    frame #7: 0x0000000106c58e08 libGGeo.dylib`GGeoLib::saveConstituents(this=0x000000010ca38eb0, idpath="/tmp/blyth/opticks/GGeo") at GGeoLib.cc:329
       326 	        {          
       327 	           std::string ptsp_ = BFile::FormPath(idpath, GPTS, sidx );
       328 	           const char* ptsp = ptsp_.c_str();
    -> 329 	           pts->save(ptsp); 
       330 	        }
       331 	
       332 	    }
    (lldb) p idpath
    (const char *) $0 = 0x000000010c815140 "/tmp/blyth/opticks/GGeo"
    (lldb) f 8 
    frame #8: 0x0000000106c585a0 libGGeo.dylib`GGeoLib::save(this=0x000000010ca38eb0) at GGeoLib.cc:167
       164 	void GGeoLib::save()
       165 	{
       166 	    const char* idpath = m_ok->getIdPath() ;
    -> 167 	    saveConstituents(idpath);
       168 	}
       169 	
       170 	
    (lldb) p idpath
    (const char *) $1 = 0x000000010c815140 "/tmp/blyth/opticks/GGeo"
    (lldb) 




::

     620 void GGeo::postDirectTranslation()
     621 {
     622     LOG(LEVEL) << "[" ;
     623 
     624     prepare();     // instances are formed here     
     625 
     626     LOG(LEVEL) << "( GBndLib::fillMaterialLineMap " ;
     627     GBndLib* blib = getBndLib();
     628     blib->fillMaterialLineMap();
     629     LOG(LEVEL) << ") GBndLib::fillMaterialLineMap " ;
     630 
     631     LOG(LEVEL) << "( GGeo::save " ;
     632     save();
     633     LOG(LEVEL) << ") GGeo::save " ;
     634 
     635 
     636     deferred();
     637 
     638     postDirectTranslationDump();
     639 
     640     LOG(LEVEL) << "]" ;
     641 }


Unexpected relative path save of CSGFoundry::

    epsilon:tests blyth$ l 1
    total 248
      0 drwxr-xr-x  25 blyth  staff    800 Jun 14 12:58 ..
      8 -rw-r--r--   1 blyth  staff    159 Jun 14 12:56 origin_gdxml_report.txt
    120 -rw-r--r--   1 blyth  staff  57820 Jun 14 12:56 origin.gdml
    120 -rw-r--r--   1 blyth  staff  57863 Jun 14 12:56 origin_raw.gdml
      0 drwxr-xr-x   6 blyth  staff    192 Jun 14 12:56 .
      0 drwxr-xr-x  13 blyth  staff    416 Jun 14 12:51 CSGFoundry
    epsilon:tests blyth$ pwd
    /Users/blyth/opticks/g4cx/tests
    epsilon:tests blyth$ l 1/CSGFoundry/
    total 80
    8 -rw-r--r--   1 blyth  staff   192 Jun 14 12:56 inst.npy
    8 -rw-r--r--   1 blyth  staff   832 Jun 14 12:56 itra.npy
    8 -rw-r--r--   1 blyth  staff   832 Jun 14 12:56 tran.npy
    8 -rw-r--r--   1 blyth  staff  1024 Jun 14 12:56 node.npy
    8 -rw-r--r--   1 blyth  staff   640 Jun 14 12:56 prim.npy
    8 -rw-r--r--   1 blyth  staff   176 Jun 14 12:56 solid.npy
    8 -rw-r--r--   1 blyth  staff   147 Jun 14 12:56 meta.txt
    8 -rw-r--r--   1 blyth  staff    13 Jun 14 12:56 mmlabel.txt
    8 -rw-r--r--   1 blyth  staff   129 Jun 14 12:56 primname.txt
    8 -rw-r--r--   1 blyth  staff   129 Jun 14 12:56 meshname.txt
    0 drwxr-xr-x   6 blyth  staff   192 Jun 14 12:56 ..
    0 drwxr-xr-x   8 blyth  staff   256 Jun 14 12:51 SSim
    0 drwxr-xr-x  13 blyth  staff   416 Jun 14 12:51 .
    epsilon:tests blyth$ pwd
    /Users/blyth/opticks/g4cx/tests
    epsilon:tests blyth$ 

::

    545 void G4CXOpticks::saveGeometry() const
    546 {
    547     // SGeo::DefaultDir() was giving null : due to static const depending on static const
    548     const char* dir = SEventConfig::OutFold() ;
    549     LOG(LEVEL)  << "dir [" << ( dir ? dir : "-" )  ;
    550     saveGeometry(dir) ;
    551 }

::

    epsilon:tests blyth$ SEventConfigTest  | grep OutFold
             OPTICKS_OUT_FOLD            OutFold  : $DefaultOutputDir


Hmm, probably the token being treated as envvar rather than internal token. 

HUH, look like its resolving to "1"::

    552 void G4CXOpticks::saveGeometry(const char* dir_) const
    553 {
    554     const char* dir = SPath::Resolve(dir_, DIRPATH);
    555     LOG(LEVEL) << "[ " << ( dir ? dir : "-" ) ;
    556     LOG(info)  << "[ " << ( dir ? dir : "-" ) ;
    557     std::cout << "G4CXOpticks::saveGeometry [ " << ( dir ? dir : "-" ) << std::endl ;
    558 

    2023-06-14 12:56:46.909 INFO  [14565081] [G4CXOpticks::setGeometry_@298] [ G4CXOpticks__setGeometry_saveGeometry 
    2023-06-14 12:56:46.909 INFO  [14565081] [G4CXOpticks::saveGeometry@555] [ 1
    2023-06-14 12:56:46.909 INFO  [14565081] [G4CXOpticks::saveGeometry@556] [ 1
    G4CXOpticks::saveGeometry [ 1

Plot thickens its "1" before resolution. Thats pilot error need to set the 
envvar to directory not a bool::

    export G4CXOpticks__setGeometry_saveGeometry=~/.opticks/GEOM/$GEOM

 


The GGeo save directory is unrelated to this one.. add GGeo__save_SIGINT::

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGINT
      * frame #0: 0x00007fff77104b66 libsystem_kernel.dylib`__pthread_kill + 10
        frame #1: 0x00007fff772cf080 libsystem_pthread.dylib`pthread_kill + 333
        frame #2: 0x00007fff770126fe libsystem_c.dylib`raise + 26
        frame #3: 0x0000000106cc98e0 libGGeo.dylib`GGeo::save(this=0x000000010c99cec0) at GGeo.cc:821
        frame #4: 0x0000000106cc88d9 libGGeo.dylib`GGeo::postDirectTranslation(this=0x000000010c99cec0) at GGeo.cc:632
        frame #5: 0x000000010080d6e1 libExtG4.dylib`X4Geo::Translate(top=0x000000010c9744e0) at X4Geo.cc:27
        frame #6: 0x000000010018c688 libG4CX.dylib`G4CXOpticks::setGeometry(this=0x000000010c957490, world=0x000000010c9744e0) at G4CXOpticks.cc:256
        frame #7: 0x000000010018c28a libG4CX.dylib`G4CXOpticks::setGeometry(this=0x000000010c957490) at G4CXOpticks.cc:202
        frame #8: 0x000000010018b420 libG4CX.dylib`G4CXOpticks::SetGeometry() at G4CXOpticks.cc:59
        frame #9: 0x000000010003efbf G4CXOpticks_setGeometry_Test`main(argc=1, argv=0x00007ffeefbfe580) at G4CXOpticks_setGeometry_Test.cc:17
        frame #10: 0x00007fff76fb4015 libdyld.dylib`start + 1
    (lldb) 


::

    199     else if(SSys::hasenvvar("GEOM"))
    200     {
    201         LOG(LEVEL) << " GEOM/U4VolumeMaker::PV " ;
    202         setGeometry( U4VolumeMaker::PV() );  // this may load GDML using U4VolumeMaker::PVG if "GEOM"_GDMLPath is defined   
    203     }

    240 void G4CXOpticks::setGeometry(const G4VPhysicalVolume* world )
    241 {   
    242     LOG(LEVEL) << " G4VPhysicalVolume world " << world ;
    243     assert(world);
    244     wd = world ;
    245     
    246     assert(sim && "sim instance should have been created in ctor" );
    247     
    248     stree* st = sim->get_tree(); 
    249     // TODO: sim argument, not st : or do SSim::Create inside U4Tree::Create 
    250     tr = U4Tree::Create(st, world, SensorIdentifier ) ;
    251 
    252     
    253     // GGeo creation done when starting from a gdml or live G4,  still needs Opticks instance
    254     Opticks::Configure("--gparts_transform_offset --allownokey" );
    255     
    256     GGeo* gg_ = X4Geo::Translate(wd) ;
    257     setGeometry(gg_);
    258 }


    0620 void GGeo::postDirectTranslation()
     621 {
     622     LOG(LEVEL) << "[" ;
     623 
     624     prepare();     // instances are formed here     
     625 
     626     LOG(LEVEL) << "( GBndLib::fillMaterialLineMap " ;
     627     GBndLib* blib = getBndLib();
     628     blib->fillMaterialLineMap();
     629     LOG(LEVEL) << ") GBndLib::fillMaterialLineMap " ;
     630 
     631     LOG(LEVEL) << "( GGeo::save " ;
     632     save();
     633     LOG(LEVEL) << ") GGeo::save " ;
     634 
     635 
     636     deferred();
     637 
     638     postDirectTranslationDump();
     639 
     640     LOG(LEVEL) << "]" ;
     641 }



Suspect the Rock_solid, Water_solid box too small in Y::

    ELV=t6,7 ./cxr_min.sh 

::

    339     <box lunit="mm" name="Water_solid0x7eee30" x="711.11111111108" y="400" z="400"/>
    345     <box lunit="mm" name="Rock_solid0x7eeca0" x="746.666666666634" y="420" z="420"/>
    346   </solids>


Eyeballing size of outer Rock in XZ directions "MODE=2 ./cxt_min.sh ana"::

    In [2]: 214*2 
    Out[2]: 428

    In [3]: 373*2
    Out[3]: 746


HMM doing a XY simtrace at Z=0 would confirm. Probably the Y needs the aspect 1.7777 too. 

* YEP: confirmed, needs more room in Y avoid clipping


Cycle on the conversion whilst dumping from U4VolumeMaker::

    ./G4CXOpticks_setGeometry_Test.sh





