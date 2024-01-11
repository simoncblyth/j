xmas2023_changes_from_map_to_unordered_map.rst
=======================================================

Tao Changed several std::map to std::unordered_map


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






