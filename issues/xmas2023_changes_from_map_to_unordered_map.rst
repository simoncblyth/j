xmas2023_changes_from_map_to_unordered_map.rst
=======================================================


Overview
----------

* extensive changes adding many "Unordered" methods to 
  NPX.h on both serialize and import sides : manages to get this to compile

* PMT serializations results not yet checked : dont expect issues though 



Issue : Tao Changed several std::map to std::unordered_map causing PMT persisting to stop compiling
------------------------------------------------------------------------------------------------------




::

    N[blyth@localhost junosw]$ git status
    # On branch main
    # Your branch is behind 'origin/main' by 38 commits, and can be fast-forwarded.
    #   (use "git pull" to update your local branch)
    #
    nothing to commit, working directory clean
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ git pull 
    Updating 3f6a299..50d6228
    Fast-forward
     Calibration/PMTCalibSvc/src/PMTCalibSvc.cc                                               |  71 ++++++--
     Calibration/SPMTCalibAlg/src/SPMTCalibAlg.cc                                             |   6 -
     Calibration/WpPMTCalibAlg/src/WpPMTCalibAlg.cc                                           |   6 -
     Database/dbi/dbi/FrontierDB.h                                                            |   3 +
     Database/dbi/src/FrontierDB.cc                                                           |   1 +
     Detector/Geometry/Geometry/IPMTParamSvc.h                                                |  11 +-
     Detector/Geometry/Geometry/PMTParamData.h                                                |   5 +-
     Detector/Geometry/src/PMTParamSvc.cc                                                     |  39 +++-
     Detector/Geometry/src/PMTParamSvc.h                                                      |  37 ++--
     Detector/Identifier/Identifier/CdID.h                                                    |  52 +++++-
     Detector/Identifier/src/CdID.cc                                                          |   6 +-
     Detector/Identifier/src/WpID.cc                                                          |   2 +-
     Doc/oum/source/releasenotes/J23.1.0.md                                                   | 139 ++++++++++++++
     Examples/Tutorial/python/Tutorial/JUNOApplication.py                                     |  13 +-
     Examples/Tutorial/python/Tutorial/JUNOCommonModule.py                                    |  12 +-
     Examples/Tutorial/python/Tutorial/JUNODetSimModule.py                                    |  23 ++-
     Examples/Tutorial/python/Tutorial/JUNOElecSimModule.py                                   |   1 -
     Examples/Tutorial/python/Tutorial/JUNOEventRecModule.py                                  |   9 +-
     Examples/Tutorial/python/Tutorial/JUNOMtApplication.py                                   |   3 +-
     Examples/Tutorial/share/tut_calib2rec.py                                                 |   4 +-
     Examples/Tutorial/share/tut_elec2calib.py                                                |   2 +-
     Examples/Tutorial/share/tut_elec2rec.py                                                  |   2 +-
     Examples/Tutorial/share/tut_rtraw2rec.py                                                 |   2 +-
     Generator/Supernova/CMakeLists.txt                                                       |  22 +++
     Generator/Supernova/src/dataflux.cc                                                      | 256 ++++++++++++++++++--------
     Generator/Supernova/src/dataflux.h                                                       |  39 +++-
     Generator/Supernova/src/def.h                                                            |   2 +-
     Generator/Supernova/src/detector.cc                                                      |  90 ++++++++-
     Generator/Supernova/src/detector.h                                                       |   7 +-
     Generator/Supernova/src/event.cc                                                         |   2 +
     Generator/Supernova/src/event.h                                                          |   1 +
     Generator/Supernova/src/genSN.cc                                                         | 978 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++--------------------
     Generator/Supernova/src/genSN.h                                                          | 151 +++++++++++++++
     Generator/Supernova/src/pdfs.cc                                                          | 124 ++++++++++---
     Generator/Supernova/src/sneventsoutput.cc                                                |   3 +-
     Generator/UnifiedGen/CommonXSec/CommonXSec/EESXSec.hh                                    |  51 ++++++
     Generator/UnifiedGen/{UnifiedInverseBeta/src => CommonXSec/CommonXSec}/NuOscillations.hh |   1 +
     Generator/UnifiedGen/CommonXSec/CommonXSec/ReadIBDXSecParam.hh                           |   4 +-
     Generator/UnifiedGen/CommonXSec/src/EESXSec.cc                                           | 119 ++++++++++++
     Generator/UnifiedGen/CommonXSec/src/IBDXSec.cc                                           |   9 +
     Generator/UnifiedGen/{UnifiedInverseBeta => CommonXSec}/src/NuOscillations.cc            |   5 +-
     Generator/UnifiedGen/CommonXSec/src/ReadIBDXSecParam.cc                                  |  15 ++
     Generator/UnifiedGen/CommonXSec/src/ReadOscParam.cc                                      |  11 +-
     Generator/UnifiedGen/UnifiedInverseBeta/src/inverse_beta.cc                              |   2 +-
     OEC/EvtProcessor/EvtSteering/EvtSteering/StepHandler.h                                   |   4 +
     OEC/EvtProcessor/EvtSteering/share/sig.json                                              |   2 +-
     OEC/EvtProcessor/EvtSteering/src/StepHandler.cc                                          |  11 ++
     OEC/HECAlg/HECAlg/HECTriggerTool.h                                                       |  46 +++++
     OEC/HECAlg/src/HECAlg.cc                                                                 |  35 +++-
     OEC/HECAlg/src/HECAlg.h                                                                  |   2 +
     OEC/HECAlg/src/HECTriggerTool.cc                                                         | 119 ++++++++++++
     OEC/HECAtmAlg/src/HECAtmAlg.cc                                                           |  36 +++-
     OEC/HECAtmAlg/src/HECAtmAlg.h                                                            |  10 +-
     OEC/OECConfig/OECTagSvc/OECTagSvc/OECTagID.h                                             |  14 ++
     OEC/OECConfig/OECTagSvc/OECTagSvc/OECTagSvc.h                                            |   6 +
     OEC/OECConfig/OECTagSvc/share/tag.json                                                   |  10 +
     OEC/OECConfig/OECTagSvc/src/OECTagSvc.cc                                                 |  59 +++++-
     OEC/OECProcessor/src/OECOutputHelper.cc                                                  |   3 +-
     OEC/OECTutorial/python/OECTutorial/JUNOOECModule.py                                      |  33 +++-
     OEC/OECTutorial/share/tut_oec.py                                                         |   9 +-
     OEC/OECTutorial/share/tut_oec_mt.py                                                      |   3 +
     OEC/OECTutorial/tests/test_oec.py                                                        |   8 +-
     Reconstruction/OECWFrec/CMakeLists.txt                                                   |   1 +
     Reconstruction/OECWFrec/share/run.py                                                     |  52 ++++++
     Reconstruction/OECWFrec/src/CheckTimeOffset.cc                                           | 203 +++++++++++++++++++++
     Reconstruction/OMILREC/src/OMILREC.cc                                                    |  85 ++++++---
     Reconstruction/OMILREC/src/PMTRealInputTool.cc                                           |  17 +-
     Reconstruction/OMILREC/src/PMTRealParaTool.cc                                            |  11 +-
     Reconstruction/RecMuon/LsqMuonRecTool/src/LsqMuonRecTool.cc                              |   6 +-
     Reconstruction/RecMuon/RecCdMuonAlg/src/RecCdMuonAlg.cc                                  |  63 +++++--
     Reconstruction/RecMuon/RecCdMuonAlg/src/RecCdMuonAlg.h                                   |   4 +
     Reconstruction/RecMuon/RecMuonAlg/src/RecMuonAlg.cc                                      |   5 +-
     Reconstruction/RecMuon/RecWpMuonAlg/src/RecWpMuonAlg.cc                                  |  52 ++++--
     Reconstruction/RecMuon/RecWpMuonAlg/src/RecWpMuonAlg.h                                   |   4 +-
     Reconstruction/RecMuon/SpmtMuonRecTool/src/SpmtMuonRecTool.cc                            |   1 +
     Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc                                 |   8 +-
     Simulation/DetSimV2/PMTSim/include/PMTSDMgr.hh                                           |   2 -
     Simulation/DetSimV2/PMTSim/include/junoHit_PMT.hh                                        |   2 +
     Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh                                      |  21 ++-
     Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh                              |   9 +-
     Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc                                               |  15 --
     Simulation/DetSimV2/PMTSim/src/junoHit_PMT.cc                                            |  33 ++++
     Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc                                          | 178 +++++++-----------
     Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc                                  | 191 ++++---------------
     Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc                                    |   4 +-
     Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc                                  |  52 ++++--
     Simulation/ElecSimV3/ElecSimAlg/src/TriggerHandlerTT.cc                                  |   2 +-
     Simulation/ElecSimV3/ElecSimAlg/src/TriggerToolTT.cc                                     |  45 ++++-
     Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h                        |  17 +-
     Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc                                   |  47 +++--
     Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h                                    |   7 +-
     cmake/legacy/JUNODependencies.cmake                                                      |   2 +-
     92 files changed, 3012 insertions(+), 878 deletions(-)
     create mode 100644 Generator/Supernova/src/genSN.h
     create mode 100644 Generator/UnifiedGen/CommonXSec/CommonXSec/EESXSec.hh
     rename Generator/UnifiedGen/{UnifiedInverseBeta/src => CommonXSec/CommonXSec}/NuOscillations.hh (96%)
     create mode 100644 Generator/UnifiedGen/CommonXSec/src/EESXSec.cc
     rename Generator/UnifiedGen/{UnifiedInverseBeta => CommonXSec}/src/NuOscillations.cc (97%)
     create mode 100644 OEC/HECAlg/HECAlg/HECTriggerTool.h
     create mode 100644 OEC/HECAlg/src/HECTriggerTool.cc
     create mode 100644 Reconstruction/OECWFrec/share/run.py
     create mode 100644 Reconstruction/OECWFrec/src/CheckTimeOffset.cc
    N[blyth@localhost junosw]$ 


Tao switched PMTParamData.h to use unordered_map
---------------------------------------------------

::


    N[blyth@localhost junosw]$ git diff fd0b127e9d2b3e3a8ec17a685f8223e9822a9efe..fb1dc105686d420f09b3bcde22fe1330665ab472 Detector/Geometry/Geometry/PMTParamData.h
    diff --git a/Detector/Geometry/Geometry/PMTParamData.h b/Detector/Geometry/Geometry/PMTParamData.h
    index bdc296d..b5a4871 100644
    --- a/Detector/Geometry/Geometry/PMTParamData.h
    +++ b/Detector/Geometry/Geometry/PMTParamData.h
    @@ -1,10 +1,11 @@
     #pragma once
     #include <map>
    +#include <unordered_map>
     #include <ostream>
     
     struct PMTParamData
     {
    -    std::map<int, int> m_pmt_categories ;
    +    std::unordered_map<int, int> m_pmt_categories ;
     };
     
     inline std::ostream& operator<<(std::ostream& os, const PMTParamData& d )
    @@ -18,7 +19,7 @@ inline std::ostream& operator<<(std::ostream& os, const PMTParamData& d )
            ; 
     
         unsigned edge = 10 ; 
    -    typedef std::map<int,int> MII ; 
    +    typedef std::unordered_map<int,int> MII ; 
         MII::const_iterator it = d.m_pmt_categories.begin() ; 
     
         for(unsigned i=0 ; i < ni ; i++)
    N[blyth@localhost junosw]$ 



::

    N[blyth@localhost junosw]$ jgr PMTParamData.h
    ./Detector/Geometry/Geometry/_PMTParamData.h:#include "PMTParamData.h"
    ./Detector/Geometry/src/PMTParamSvc.h:#include "Geometry/PMTParamData.h"
    ./Detector/Geometry/tests/PMTParamData_test.cc:#include "PMTParamData.h"
    ./Detector/Geometry/tests/PMTParamData_test.cc:#include "_PMTParamData.h"
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#include "Geometry/PMTParamData.h"
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#include "Geometry/_PMTParamData.h"
    N[blyth@localhost junosw]$ 


::

     44 inline NPFold* _PMTParamData::serialize() const
     45 {
     46     NPFold* f = new NPFold ;
     47     f->add("pmtCat", NPX::ArrayFromDiscoMap<int>(data.m_pmt_categories));
     48     return f ;
     49 }
     50 inline void _PMTParamData::import( const NPFold* f )
     51 {
     52     const NP* pmtCat = f->get("pmtCat");
     53     NPX::DiscoMapFromArray<int>(data.m_pmt_categories, pmtCat );
     54 }




::

     451 /**
     452 SPMT::init_lcqs
     453 -----------------
     454 
     455 1. get lpmtCat, qeScale arrays from PMTSimParamData NPFold
     456 2. check appropriate sizes with info for all NUM_LPMT 17612 
     457 3. populate v_lcqs vector of LCQS struct holding int:lc 
     458    "local 0/1/2 pmtcat" and float:qeScale
     459 4. convert the vector of LCQS struct into lcqs array 
     460 
     461 NB EVEN WHEN TESTING WITH REDUCED N_LPMT STILL NEED TO INCLUDE INFO FOR ALL 17612 LPMT
     462 
     463 **/
     464 
     465 inline void SPMT::init_lcqs()
     466 {
     467     assert( PMTSimParamData );
     468     const NP* lpmtCat = PMTSimParamData->get("lpmtCat") ;
     469     assert( lpmtCat && lpmtCat->uifc == 'i' && lpmtCat->ebyte == 4 );
     470     assert( lpmtCat->shape[0] == NUM_LPMT );
     471     const int* lpmtCat_v = lpmtCat->cvalues<int>();
     472 
     473     const NP* qeScale = PMTSimParamData->get("qeScale") ;
     474     assert( qeScale && qeScale->uifc == 'f' && qeScale->ebyte == 8 );
     475     assert( qeScale->shape[0] >= NUM_LPMT );  // SPMT, WPMT info after LPMT 
     476     const double* qeScale_v = qeScale->cvalues<double>();
     477 
     478     for(int i=0 ; i < NUM_LPMT ; i++ )
     479     {
     480         v_lcqs[i] = { TranslateCat(lpmtCat_v[i]), float(qeScale_v[i]) } ;
     481     }
     482     lcqs = NPX::ArrayFromVec<int,LCQS>( v_lcqs ) ;
     483 
     484     if(VERBOSE) std::cout
     485        << "SPMT::init_lcqs" << std::endl
     486        << " NUM_LPMT " << NUM_LPMT << std::endl
     487        << " lpmtCat " << ( lpmtCat ? lpmtCat->sstr() : "-" ) << std::endl
     488        << " qeScale " << ( qeScale ? qeScale->sstr() : "-" ) << std::endl
     489        << " lcqs " << ( lcqs ? lcqs->sstr() : "-" ) << std::endl
     490        ;
     491 
     492     assert( lcqs->shape[0] == NUM_LPMT );
     493     assert( NUM_LPMT == 17612 );
     494 }



Above assuming lpmtCat and qeScale in same pmtid order. 


::

    N[blyth@localhost opticks]$ jgr lpmtCat
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    NP* lpmtCat = NPX::ArrayFromMap<int, int>(data.m_map_pmt_category) ; 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    f->add("lpmtCat", lpmtCat ); 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    const NP* lpmtCat = f->get("lpmtCat"); 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:                      lpmtCat == nullptr || 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:         << " lpmtCat " << ( lpmtCat ? "YES" : "NO " ) << std::endl 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    NPX::MapFromArray<int>(data.m_map_pmt_category, lpmtCat ); 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.py:    t.lpmtCat.shape
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.py:    np.all(t.pmtCat[:len(t.lpmtCat),1]==t.lpmtCat[:,0])
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.py:    np.all(t.lpmtData[:len(t.lpmtCat),0].view(np.int64)==t.pmtID[:len(t.lpmtCat),0])
    N[blyth@localhost junosw]$ 





SPMT not actually on critical path, its more for non-GPU testing
-------------------------------------------------------------------- 


QPMT workflow : kicks in when SSim provides spmt NPFold
----------------------------------------------------------

::

     179 
     180     const NPFold* spmt_f = ssim->get_spmt_f() ;
     181     QPMT<float>* qpmt = spmt_f ? new QPMT<float>(spmt_f) : nullptr ;
     182     LOG_IF(LEVEL, qpmt == nullptr )
     183         << " NO QPMT instance "
     184         << " spmt_f " << ( spmt_f ? "YES" : "NO " )
     185         << " qpmt " << ( qpmt ? "YES" : "NO " )
     186         ;
     187 
     188     LOG(LEVEL)
     189         << QPMT<float>::Desc()
     190         << std::endl
     191         << " spmt_f " << ( spmt_f ? "YES" : "NO " )
     192         << " qpmt " << ( qpmt ? "YES" : "NO " )
     193         ;

::

    102 template<typename T>
    103 inline QPMT<T>::QPMT(const NPFold* jpmt )
    104     :
    105     ExecutableName(sproc::ExecutableName()),
    106     src_rindex(   jpmt->get("rindex")),
    107     src_thickness(jpmt->get("thickness")),
    108     src_qeshape(  jpmt->get("qeshape")),
    109     src_lcqs(     jpmt->get_optional("lcqs")),

    /// HUH: NO LONGER OPTIONAL ? 

    110     rindex3(  NP::MakeCopy3D(src_rindex)),   // make copy and change shape to 3D
    111     rindex(   NP::MakeWithType<T>(rindex3)), // adopt template type, potentially narrowing
    112     rindex_prop(new QProp<T>(rindex)),
    113     qeshape(   NP::MakeWithType<T>(src_qeshape)), // adopt template type, potentially narrowing
    114     qeshape_prop(new QProp<T>(qeshape)),
    115     thickness(NP::MakeWithType<T>(src_thickness)),
    116     lcqs(src_lcqs ? NP::MakeWithType<T>(src_lcqs) : nullptr),
    117     i_lcqs( lcqs ? (int*)lcqs->cvalues<T>() : nullptr ),    // CPU side lookup lpmtid->lpmtcat 0/1/2
    118     pmt(new qpmt<T>()),                    // host-side qpmt.h instance 
    119     d_pmt(nullptr)                         // device-side pointer set at upload in init
    120 {
    121     init();
    122 }



Need to check shapes and content of the arrays before and after change to unordered_map
----------------------------------------------------------------------------------------- 

* qudarap/tests/QPMT_Test.sh

Can do this by getting to build and run and then comparing the persisted jpmt folder
by virtue of minting a new GEOM identifier. 


::

    In [2]: f.PMTSimParamData                                                                                                                                               
    Out[2]: 
    PMTSimParamData

    CMDLINE:/Users/blyth/np/f.py
    PMTSimParamData.base:./PMTSimParamData

      : PMTSimParamData.lpmtData                           :           (20012, 9) : 40 days, 3:00:45.683882 
      : PMTSimParamData.pmtTotal                           :                 (4,) : 40 days, 3:00:45.678726 
      : PMTSimParamData.MPT                                :                 None : 40 days, 3:00:45.652390 
      : PMTSimParamData.pmtCat                             :           (45612, 2) : 40 days, 3:00:45.682065 
      : PMTSimParamData.QEshape                            :                 None : 40 days, 3:00:45.652332 
      : PMTSimParamData.pmtCatVec                          :           (45612, 1) : 40 days, 3:00:45.680098 
      : PMTSimParamData.pmtCatName_names                   :                 (5,) : 40 days, 3:00:45.681042 
      : PMTSimParamData.CONST                              :                 None : 40 days, 3:00:45.652406 
      : PMTSimParamData.pmtID                              :           (45612, 1) : 40 days, 3:00:45.679141 
      : PMTSimParamData.NPFold_index                       :                (12,) : 40 days, 3:00:45.702147 
      : PMTSimParamData.spmtData_meta                      :                    2 : 40 days, 3:00:45.669278 
      : PMTSimParamData.spmtData                           :          (25600, 10) : 40 days, 3:00:45.669874 
      : PMTSimParamData.pmtTotal_names                     :                 (4,) : 40 days, 3:00:45.678379 
      : PMTSimParamData.qeScale                            :           (45612, 1) : 40 days, 3:00:45.676217 
      : PMTSimParamData.lpmtCat_meta                       :                    2 : 40 days, 3:00:45.700887 
      : PMTSimParamData.lpmtCat                            :           (17612, 1) : 40 days, 3:00:45.701286 
      : PMTSimParamData.NPFold_names                       :                 (0,) : 40 days, 3:00:45.701853 
      : PMTSimParamData.pmtCatName                         :                 (5,) : 40 days, 3:00:45.681486 

     min_stamp : 2023-11-29 14:22:49.409378 
     max_stamp : 2023-11-29 14:22:49.459193 
     dif_stamp : 0:00:00.049815 
     age_stamp : 40 days, 3:00:45.652332 

    In [3]: pwd                                                                                                                                                             
    Out[3]: '/Users/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/CSGFoundry/SSim/extra/jpmt'


Cannot update until fix the unorderd map issue
-----------------------------------------------------

::

    n file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h: In member function 'void _PMTSimParamData::populate_SPMT()':
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:143:32: warning: implicitly-declared 'constexpr PmtSimData_SPMT& PmtSimData_SPMT::operator=(const PmtSimData_SPMT&)' is deprecated [-Wdeprecated-copy]
      143 |         data.pd_map_SPMT[id] = spmt ;
          |                                ^~~~
    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h:42,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:368:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_SPMT.h:29:3: note: because 'PmtSimData_SPMT' has user-provided 'PmtSimData_SPMT::PmtSimData_SPMT(const PmtSimData_SPMT&)'
       29 |   PmtSimData_SPMT(const PmtSimData_SPMT &others)
          |   ^~~~~~~~~~~~~~~
    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h: In member function 'NPFold* _PMTSimParamData::serialize() const':
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:219:52: error: cannot convert 'std::unordered_map<int, int>' to 'const std::map<int, int>&'
      219 |     NP* lpmtCat = NPX::ArrayFromMap<int, int>(data.m_map_pmt_category) ;
          |                                               ~~~~~^~~~~~~~~~~~~~~~~~
          |                                                    |
          |                                                    std::unordered_map<int, int>
    In file included from /home/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NPFold.h:91,
                     from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:5,
                     from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /home/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NPX.h:583:55: note:   initializing argument 1 of 'static NP* NPX::ArrayFromMap(const std::map<int, S>&, bool) [with T = int; S = int]'
      583 | inline NP* NPX::ArrayFromMap( const std::map<int, S>& m, bool contiguous_key )
          |                               ~~~~~~~~~~~~~~~~~~~~~~~~^
    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:220:51: error: cannot convert 'std::unordered_map<int, int>' to 'const std::map<int, int>&'
      220 |     NP* pmtCat = NPX::ArrayFromDiscoMap<int>(data.m_all_pmt_category) ;
          |                                              ~~~~~^~~~~~~~~~~~~~~~~~
          |                                                   |
          |                                                   std::unordered_map<int, int>



::

    215 inline NPFold* _PMTSimParamData::serialize() const
    216 {
    217     NP* pmtID = NPX::ArrayFromVec<int, int>(data.m_all_pmtID) ;
    218     NP* qeScale = NPX::ArrayFromVec<double,double>(data.m_all_pmtID_qe_scale) ;

    219     NP* lpmtCat = NPX::ArrayFromMap<int, int>(data.m_map_pmt_category) ;
    220     NP* pmtCat = NPX::ArrayFromDiscoMap<int>(data.m_all_pmt_category) ;

    221     NP* pmtCatVec = NPX::ArrayFromVec<int, int>(data.m_all_pmt_catvec) ;
    222 


::

    epsilon:PMTSimParamData blyth$ pwd
    /Users/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/CSGFoundry/SSim/extra/jpmt/PMTSimParamData
    epsilon:PMTSimParamData blyth$ f
    f

    CMDLINE:/Users/blyth/np/f.py
    f.base:.

      : f.lpmtData                                         :           (20012, 9) : 65 days, 3:09:53.825717 
      : f.pmtTotal                                         :                 (4,) : 65 days, 3:09:53.820561 
      : f.MPT                                              :                 None : 65 days, 3:09:53.794225 
      : f.pmtCat                                           :           (45612, 2) : 65 days, 3:09:53.823900 
      : f.QEshape                                          :                 None : 65 days, 3:09:53.794167 
      : f.pmtCatVec                                        :           (45612, 1) : 65 days, 3:09:53.821933 
      : f.pmtCatName_names                                 :                 (5,) : 65 days, 3:09:53.822877 
      : f.CONST                                            :                 None : 65 days, 3:09:53.794241 
      : f.pmtID                                            :           (45612, 1) : 65 days, 3:09:53.820976 
      : f.NPFold_index                                     :                (12,) : 65 days, 3:09:53.843982 
      : f.spmtData_meta                                    :                    2 : 65 days, 3:09:53.811113 
      : f.spmtData                                         :          (25600, 10) : 65 days, 3:09:53.811709 
      : f.pmtTotal_names                                   :                 (4,) : 65 days, 3:09:53.820214 
      : f.qeScale                                          :           (45612, 1) : 65 days, 3:09:53.818052 
      : f.lpmtCat_meta                                     :                    2 : 65 days, 3:09:53.842722 
      : f.lpmtCat                                          :           (17612, 1) : 65 days, 3:09:53.843121 
      : f.NPFold_names                                     :                 (0,) : 65 days, 3:09:53.843688 
      : f.pmtCatName                                       :                 (5,) : 65 days, 3:09:53.823321 

     min_stamp : 2023-11-29 14:22:49.409378 
     max_stamp : 2023-11-29 14:22:49.459193 
     dif_stamp : 0:00:00.049815 
     age_stamp : 65 days, 3:09:53.794167 

    In [1]:                                 


    In [1]: f.lpmtCat
    Out[1]: 
    array([[1],
           [1],
           [3],
           [1],
           [3],
           ...,
           [1],
           [1],
           [1],
           [1],
           [1]], dtype=int32)

    In [2]: f.lpmtCat.shape 
    Out[2]: (17612, 1)

    In [3]: f.lpmtCat_meta
    Out[3]: 
    k0:0
    ContiguousKey:1


    In [4]: f.pmtCat
    Out[4]: 
    array([[     0,      1],
           [     1,      1],
           [     2,      3],
           [     3,      1],
           [     4,      3],
           ...,
           [325595,      2],
           [325596,      2],
           [325597,      2],
           [325598,      2],
           [325599,      2]], dtype=int32)

    In [5]: f.pmtCat.shape
    Out[5]: (45612, 2)

    In [7]: f.pmtCat[17600:17700,0]
    Out[7]:
    array([17600, 17601, 17602, 17603, 17604, 17605, 17606, 17607, 17608, 17609, 17610, 17611, 30000, 30001, 30002, 30003, 30004, 30005, 30006, 30007, 30008, 30009, 30010, 30011, 30012, 30013, 30014,
           30015, 30016, 30017, 30018, 30019, 30020, 30021, 30022, 30023, 30024, 30025, 30026, 30027, 30028, 30029, 30030, 30031, 30032, 30033, 30034, 30035, 30036, 30037, 30038, 30039, 30040, 30041,
           30042, 30043, 30044, 30045, 30046, 30047, 30048, 30049, 30050, 30051, 30052, 30053, 30054, 30055, 30056, 30057, 30058, 30059, 30060, 30061, 30062, 30063, 30064, 30065, 30066, 30067, 30068,
           30069, 30070, 30071, 30072, 30073, 30074, 30075, 30076, 30077, 30078, 30079, 30080, 30081, 30082, 30083, 30084, 30085, 30086, 30087], dtype=int32)

    In [8]:


    In [21]: f.pmtID[:,0]
    Out[21]: array([     0,      1,      2,      3,      4, ..., 325595, 325596, 325597, 325598, 325599], dtype=int32)

    In [22]: f.pmtCat[:,0]
    Out[22]: array([     0,      1,      2,      3,      4, ..., 325595, 325596, 325597, 325598, 325599], dtype=int32)

    In [23]: np.all( f.pmtID[:,0] == f.pmtCat[:,0] )
    Out[23]: True





Same compilation error from spmt data
---------------------------------------

::

    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h: In member function 'NPFold* _PMTSimParamData::serialize() const':
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:223:68: error: cannot convert 'std::unordered_map<int, PmtSimData_SPMT>' to 'const std::map<int, PmtSimData_SPMT, std::less<int>, std::allocator<std::pair<const int, PmtSimData_SPMT> > >&'
      223 |     NP* spmtData = NPX::ArrayFromMap<double, PmtSimData_SPMT>(data.pd_map_SPMT) ;
          |                                                               ~~~~~^~~~~~~~~~~
          |                                                                    |
          |                                                                    std::unordered_map<int, PmtSimData_SPMT>


    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h: In member function 'int _PMTSimParamData::import(const NPFold*)':




::

    In [4]: f.spmtData.view(np.int64)[:,0]
    Out[4]: array([300000, 300001, 300002, 300003, 300004, ..., 325595, 325596, 325597, 325598, 325599])

    In [5]: f.spmtData.view(np.int64)[:,0].shape
    Out[5]: (25600,)

    In [6]: f.spmtData_meta
    Out[6]:
    k0:300000
    ContiguousKey:1



::

    215 inline NPFold* _PMTSimParamData::serialize() const
    216 {
    217     NP* pmtID = NPX::ArrayFromVec<int, int>(data.m_all_pmtID) ;
    218     NP* qeScale = NPX::ArrayFromVec<double,double>(data.m_all_pmtID_qe_scale) ;
    219     NP* lpmtCat = NPX::ArrayFromMapUnordered<int, int>(data.m_map_pmt_category) ;
    220     NP* pmtCat = NPX::ArrayFromDiscoMapUnordered<int>(data.m_all_pmt_category) ;
    221     NP* pmtCatVec = NPX::ArrayFromVec<int, int>(data.m_all_pmt_catvec) ;
    222

    223     NP* spmtData = NPX::ArrayFromMap<double, PmtSimData_SPMT>(data.pd_map_SPMT) ;

    224     NP* lpmtData = NPX::ArrayFromVec<double, PmtSimData_LPMT>(data.pd_vector) ;
    225     NP* pmtTotal = serialize_pmtTotal();
    226 
    227     NPFold* MPT = S4MaterialPropertyVector::Serialize_MIMSV(data.m_PMT_MPT);
    228     NPFold* CONST = NPFold::Serialize_MIMSD(data.m_PMT_CONST);
    229     NPFold* QEshape = serialize_QEshape() ;




Also get the error for other direction : importing
----------------------------------------------------


::

    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:311:33: error: cannot convert 'std::unordered_map<int, int>' to 'std::map<int, int>&'
      311 |     NPX::MapFromArray<int>(data.m_map_pmt_category, lpmtCat );
          |                            ~~~~~^~~~~~~~~~~~~~~~~~
          |                                 |
          |                                 std::unordered_map<int, int>



    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:312:38: error: cannot convert 'std::unordered_map<int, int>' to 'std::map<int, int>&'
      312 |     NPX::DiscoMapFromArray<int>(data.m_all_pmt_category, pmtCat );
          |                                 ~~~~~^~~~~~~~~~~~~~~~~~
          |                                      |
          |                                      std::unordered_map<int, int>


    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:314:45: error: cannot convert 'std::unordered_map<int, PmtSimData_SPMT>' to 'std::map<int, PmtSimData_SPMT, std::less<int>, std::allocator<std::pair<const int, PmtSimData_SPMT> > >&'
      314 |     NPX::MapFromArray<PmtSimData_SPMT>(data.pd_map_SPMT, spmtData);
          |                                        ~~~~~^~~~~~~~~~~
          |                                             |
          |                                             std::unordered_map<int, PmtSimData_SPMT>



    gmake[2]: *** [Simulation/DetSimV2/PhysiSim/CMakeFiles/PhysiSim.dir/src/DsPhysConsOptical.cc.o] Error 1
    gmake[1]: *** [Simulation/DetSimV2/PhysiSim/CMakeFiles/PhysiSim.dir/all] Error 2
    gmake[1]: *** Waiting for unfinished jobs....
    [ 89%] Linking CXX shared library ../../../lib/libPMTSim.so



::

    306 
    307     if(incomplete) return 1 ;
    308 
    309     NPX::VecFromArray<int>(data.m_all_pmtID, pmtID );
    310     NPX::VecFromArray<double>(data.m_all_pmtID_qe_scale, qeScale );
    311*    NPX::MapFromArray<int>(data.m_map_pmt_category, lpmtCat );
    312*    NPX::DiscoMapFromArray<int>(data.m_all_pmt_category, pmtCat );
    313     NPX::VecFromArray<int>(data.m_all_pmt_catvec, pmtCatVec );
    314*    NPX::MapFromArray<PmtSimData_SPMT>(data.pd_map_SPMT, spmtData);
    315     NPX::VecFromArray<PmtSimData_LPMT>(data.pd_vector, lpmtData);
    316     import_pmtTotal(pmtTotal);
    317 
    318     S4MaterialPropertyVector::Import_MIMSV( data.m_PMT_MPT, MPT );
    319     NPFold::Import_MIMSD( data.m_PMT_CONST, CONST );
    320     import_QEshape(QEshape);
    321 
    322 
    323     return 0 ;
    324 }







