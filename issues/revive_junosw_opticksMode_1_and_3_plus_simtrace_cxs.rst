revive_junosw_opticksMode_1_and_3_plus_simtrace_cxs
=======================================================

The goal is junosw opticksMode 1 and 3 initially with input photons.  
But getting there will be faster with more standalone tests 
like simtrace or things like the below initially.:

High Level Progress
---------------------

1. DONE : summarized the PMTSimParamData NPFold into a few arrays in SPMT.h 
2. DONE : checked  SPMT.h by comparison with JPMT get_stackspec scans



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



DONE : rerun geom creation with additional SSim/jpmt RINDEX data
-------------------------------------------------------------------

::

    ntds_noxj()
    {
       #local gpfx=R           # R:Release builds of junosw+custom4   
       local gpfx=V          # V:Debug builds of junosw+custom4  
       GPFX=${GPFX:-$gpfx}    # need to match with j/ntds/ntds.sh  AGEOM, BGEOM

       export EVTMAX=1

       NOXJ=1 GEOM=${GPFX}1J009 OPTICKS_INTEGRATION_MODE=${OPTICKS_INTEGRATION_MODE:-0} ntds 

       ## HMM: INPUT PHOTONS WILL NOT WORK IN OPTICKS MODE 0 HOW AND WHERE TO RAISE AN ERROR FOR THAT ?
    }

    ntds0_noxj(){ OPTICKS_INTEGRATION_MODE=0 ntds_noxj ; }
    ntds2_noxj(){ OPTICKS_INTEGRATION_MODE=2 ntds_noxj ; }


DONE : grab geom with additional SSim/jpmt RINDEX data
--------------------------------------------------------

::

    epsilon:junosw blyth$ t ntds2_noxj_getgeom
    ntds2_noxj_getgeom () 
    { 
        source $OPTICKS_HOME/bin/rsync.sh .opticks/GEOM/${GEOM:-V1J009};
        : j/jx.bash
    }

DONE : Check standalone PMT data access
-----------------------------------------

::

    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.sh


DONE : Convert FewPMT geometry from PMTSim into CSGFoundry 
-------------------------------------------------------------

For shakedown of Custom4 equivalent GPU side prefer using simpler FewPMT geometry. 
So start by saving a FewPMT geometry into CSGFoundry and running the three minimals on it 
FewPMT running was done in u4 using PMTSim. 

But u4 does not depend on CSG so cannot convert there. 
So get a G4CX test to do the PV to CSGFoundry conversion. 


* :doc:`G4CXOpticks_setGeometry_Test_unexpected_GGeo_writing`


DONE : Fix undersized FewPMT box
------------------------------------

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

    gxt
    ./G4CXOpticks_setGeometry_Test.sh

FewPMT.sh boxscale use the aspect for both x and y::

    epsilon:opticks blyth$ git diff
    diff --git a/u4/tests/FewPMT.sh b/u4/tests/FewPMT.sh
    index 43ca769f3..cb0f79605 100644
    --- a/u4/tests/FewPMT.sh
    +++ b/u4/tests/FewPMT.sh
    @@ -111,7 +111,7 @@ if [ "$LAYOUT" == "one_pmt" ]; then
     
        export U4VolumeMaker_WrapRockWater_Rock_HALFSIDE=210
        export U4VolumeMaker_WrapRockWater_Water_HALFSIDE=200
    -   export U4VolumeMaker_WrapRockWater_BOXSCALE=$aspect,1,1
    +   export U4VolumeMaker_WrapRockWater_BOXSCALE=$aspect,$aspect,1
     
     elif [ "$LAYOUT" == "two_pmt" ]; then 


    N[blyth@localhost tests]$ grep box ~/.opticks/GEOM/FewPMT/origin.gdml
        <box lunit="mm" name="Water_solid0x7eee30" x="711.11111111108" y="711.11111111108" z="400"/>
        <box lunit="mm" name="Rock_solid0x7eeca0" x="746.666666666634" y="746.666666666634" z="420"/>




DONE : cxr_min/cxt_min/cxs_min all working with the FewPMT geometry 
---------------------------------------------------------------------

DONE : Review CPU C4CustomART and work out how to do it standalone and then on GPU
--------------------------------------------------------------------------------------------


WIP : provisioning the C4CustomART calculation ?
-------------------------------------------------

* see PMTSimParamData_test.sh 
* see PMTAccessor_test.sh : it does standalone calc from persisted jpmt 

* Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.sh 

  * python load the persisted PMTSimParamData 

* Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh 

  * _PMTSimParamData::Load from "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/jpmt/PMTSimParamData"
  * test a few simple queries against the loaded PMTSimParamData 

* Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.sh

  * PMTAccessor::Load from "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/jpmt" 
  * standalone CPU use of PMTAccessor to do the stack calc  

* qudarap/tests/QPMTTest.sh 

  * JPMT NP_PROP_BASE loading rindex and thickness
  * on GPU interpolation check using QPMT
  * TODO: extend this to do the full calculation based off the PMTAccessor NPFold data, not JPMT

    * form a (17612,4) array (pmtcat,qescale,spare,pmtidx) 
    * 1st reproduce the JPMT.rindex JPMT.thickness arrays frm PMTAccessor NPFold
    * HMM: dont want to use junosw within opticks so start from NPFold ?





TODO : generalise qsim::propagate for special surfaces
---------------------------------------------------------

* devise optical enumeration to handle boundary/ordinarySurface/specialSurface/...
* use the enumeration in the translation to CSGFoundry

qsim.h::

    1461     if( command == BOUNDARY )
    1462     {
    1463         command = ctx.s.optical.x == 0 ?
    1464                                       propagate_at_boundary( flag, rng, ctx )
    1465                                   :
    1466                                       propagate_at_surface( flag, rng, ctx )
    1467                                   ; 
    1468 
    1469 
    1470     }



**CPU kickoff**

c4/C4OpBoundaryProcess.cc::

     502             //[OpticalSurface.mpt.CustomPrefix
     503             if( OpticalSurfaceName0 == '@' || OpticalSurfaceName0 == '#' )  // only customize specially named OpticalSurfaces 
     504             {
     505                 if( m_custom_art->local_z(aTrack) < 0. ) // lower hemi : No customization, standard boundary  
     506                 {
     507                     m_custom_status = 'Z' ;
     508                 }
     509                 else if( OpticalSurfaceName0 == '@') //  upper hemi with name starting @ : MultiFilm ART transmit thru into PMT
     510                 {
     511                     m_custom_status = 'Y' ;
     512 
     513                     m_custom_art->doIt(aTrack, aStep) ;
     514 


c4/C4CustomART.h 

* connector between c4/C4OpBoundaryProcess and the Stack calculation 

::

    251 inline void C4CustomART::doIt(const G4Track& aTrack, const G4Step& )
    252 {
    253     G4double minus_cos_theta = OldMomentum*theRecoveredNormal ;
    254     G4double energy = thePhotonMomentum ;
    255     G4double wavelength = CLHEP::twopi*CLHEP::hbarc/energy ;
    256     G4double energy_eV = energy/CLHEP::eV ;
    257     G4double wavelength_nm = wavelength/CLHEP::nm ;
    258 
    259     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );

    ///  THIS STILL THE OLD SLOW WAY : CAN DO IT MUCH FASTER   

    260     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    261     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;
    262     // following the old junoPMTOpticalModel with "backwards" _qe always zero 

    ///  HMM: WOULD BE MORE GENERAL TO MAKE CHOICE OF BACKWARDS QE ZERO OR NOT INSIDE ACCESSOR ?

    263 
    264     std::array<double,16> a_spec ;
    265     accessor->get_stackspec(a_spec, pmtcat, energy_eV );

    /// providing layer thicknesses, complex refractive indices for that energy 

    266     StackSpec<double,4> spec ;
    267     spec.import( a_spec );

    /// import just copying into different type, could be avoided 

    268 
    269     Stack<double,4> stack(wavelength_nm, minus_cos_theta, spec );
    270 


jcv DsPhysConsOptical::

    367 #include "IPMTSimParamSvc/IPMTSimParamSvc.h"
    368 #include "PMTSimParamSvc/PMTSimParamData.h"
    369 #include "PMTSimParamSvc/PMTAccessor.h"
    370 
    371 C4OpBoundaryProcess* DsPhysConsOptical::CreateCustomG4OpBoundaryProcess()
    372 {
    373     SniperPtr<IPMTSimParamSvc> psps_ptr(*getParent(), "PMTSimParamSvc");
    374 
    375     if(psps_ptr.invalid()) 
    376     {
    377         std::cout << "invalid" << std::endl ;
    378         return nullptr ; 
    379     }   
    380 
    381     IPMTSimParamSvc* ipsps = psps_ptr.data();
    382     PMTSimParamData* pspd = ipsps->getPMTSimParamData() ;
    383 
    384     C4IPMTAccessor* accessor = new PMTAccessor(pspd) ;
    385     C4OpBoundaryProcess* boundproc = new C4OpBoundaryProcess(accessor) ;
    386     std::cout << "DsPhysConsOptical::CreateCustomG4OpBoundaryProcess" << std::endl ;
    387 
    388     return boundproc ;
    389 }   


PMTAccessor
-------------

::

    epsilon:PMTSimParamData blyth$ jcv PMTAccessor
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h




DONE : Check PMTSimParamData is complete and can provide standalone StackSpec creation
------------------------------------------------------------------------------------------

DONE : cleaned up the test::

   /Users/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh


Accessor is built on top of PMTSimParamData which should be persisted. Is it complete::

    epsilon:jpmt blyth$ pwd
    /Users/blyth/.opticks/GEOM/V1J009/CSGFoundry/SSim/jpmt
    epsilon:jpmt blyth$ cd PMTSimParamData/
    epsilon:PMTSimParamData blyth$ l
    total 10992
       0 drwxr-xr-x  17 blyth  staff      544 Jun  7 14:17 .
       0 drwxr-xr-x   9 blyth  staff      288 Jun  7 14:17 CONST
       0 drwxr-xr-x   8 blyth  staff      256 Jun  7 14:17 QEshape
       0 drwxr-xr-x   6 blyth  staff      192 Jun  7 14:17 MPT
       8 -rw-rw-r--   1 blyth  staff      116 Jun  7 14:17 NPFold_index.txt
       8 -rw-rw-r--   1 blyth  staff      144 Jun  7 14:17 pmtTotal.npy
       8 -rw-rw-r--   1 blyth  staff       48 Jun  7 14:17 pmtTotal_names.txt
    3736 -rw-rw-r--   1 blyth  staff  1440992 Jun  7 14:17 lpmtData.npy
       8 -rw-rw-r--   1 blyth  staff       26 Jun  7 14:17 spmtData_meta.txt
     144 -rw-rw-r--   1 blyth  staff    70576 Jun  7 14:17 lpmtCat.npy
       8 -rw-rw-r--   1 blyth  staff       21 Jun  7 14:17 lpmtCat_meta.txt
     720 -rw-rw-r--   1 blyth  staff   365024 Jun  7 14:17 pmtCat.npy
     360 -rw-rw-r--   1 blyth  staff   182576 Jun  7 14:17 pmtCatVec.npy
    4912 -rw-rw-r--   1 blyth  staff  2048128 Jun  7 14:17 spmtData.npy
       0 drwxr-xr-x   5 blyth  staff      160 Jun  7 14:17 ..
     360 -rw-rw-r--   1 blyth  staff   182576 Jun  7 14:17 pmtID.npy
     720 -rw-rw-r--   1 blyth  staff   365024 Jun  7 14:17 qeScale.npy

    epsilon:PMTSimParamData blyth$ l ../PMTParamData/
    total 688
      0 drwxr-xr-x  4 blyth  staff     128 Jun  7 14:17 .
      0 drwxr-xr-x  5 blyth  staff     160 Jun  7 14:17 ..
      8 -rw-rw-r--  1 blyth  staff      11 Jun  7 14:17 NPFold_index.txt
    680 -rw-rw-r--  1 blyth  staff  345824 Jun  7 14:17 pmtCat.npy
    epsilon:PMTSimParamData blyth$ 

    epsilon:SSim blyth$ cd jpmt/PMTSimParamData/MPT
    epsilon:MPT blyth$ l
    total 8
    0 drwxr-xr-x  17 blyth  staff  544 Jun  7 14:17 ..
    0 drwxr-xr-x   6 blyth  staff  192 Jun  7 14:17 .
    0 drwxr-xr-x   7 blyth  staff  224 Jun  7 14:17 001
    0 drwxr-xr-x   7 blyth  staff  224 Jun  7 14:17 003
    0 drwxr-xr-x   7 blyth  staff  224 Jun  7 14:17 000
    8 -rw-rw-r--   1 blyth  staff   12 Jun  7 14:17 NPFold_index.txt
    epsilon:MPT blyth$ l 000/
    total 40
    0 drwxr-xr-x  6 blyth  staff  192 Jun  7 14:17 ..
    0 drwxr-xr-x  7 blyth  staff  224 Jun  7 14:17 .
    8 -rw-rw-r--  1 blyth  staff  160 Jun  7 14:17 ARC_KINDEX.npy
    8 -rw-rw-r--  1 blyth  staff  352 Jun  7 14:17 ARC_RINDEX.npy
    8 -rw-rw-r--  1 blyth  staff   60 Jun  7 14:17 NPFold_index.txt
    8 -rw-rw-r--  1 blyth  staff  352 Jun  7 14:17 PHC_KINDEX.npy
    8 -rw-rw-r--  1 blyth  staff  352 Jun  7 14:17 PHC_RINDEX.npy


jcv _PMTSimParamData::

    198 inline NPFold* _PMTSimParamData::serialize() const
    199 {
    200     NP* pmtID = NPX::ArrayFromVec<int, int>(data.m_all_pmtID) ;
    201     NP* qeScale = NPX::ArrayFromVec<double,double>(data.m_all_pmtID_qe_scale) ;
    202     NP* lpmtCat = NPX::ArrayFromMap<int, int>(data.m_map_pmt_category) ;
    203     NP* pmtCat = NPX::ArrayFromDiscoMap<int>(data.m_all_pmt_category) ;
    204     NP* pmtCatVec = NPX::ArrayFromVec<int, int>(data.m_all_pmt_catvec) ;
    205 
    206     NP* spmtData = NPX::ArrayFromMap<double, PmtSimData_SPMT>(data.pd_map_SPMT) ;
    207     NP* lpmtData = NPX::ArrayFromVec<double, PmtSimData_LPMT>(data.pd_vector) ;
    208     NP* pmtTotal = serialize_pmtTotal();
    209 
    210     NPFold* MPT = S4MaterialPropertyVector::Serialize_MIMSV(data.m_PMT_MPT);
    211     NPFold* CONST = NPFold::Serialize_MIMSD(data.m_PMT_CONST);
    212     NPFold* QEshape = serialize_QEshape() ;
    213 


Q: where do the 0,1,3 keys come from and why no 2?
A: Those are PMTCategory enums with no entry for 2 kPMT_HZC


jcv PMTCategory::

     06 enum PMT_CATEGORY {
      7   kPMT_Unknown=-1,
      8   kPMT_NNVT,
      9   kPMT_Hamamatsu,
     10   kPMT_HZC,
     11   kPMT_NNVT_HighQE
     12 };
     13 
     14 
     15 struct PMTCategory
     16 {
     17    static constexpr const char* Unknown     = "kPMT_Unknown" ;
     18    static constexpr const char* NNVT        = "kPMT_NNVT" ;
     19    static constexpr const char* Hamamatsu   = "kPMT_Hamamatsu" ;
     20    static constexpr const char* HZC         = "kPMT_HZC" ;
     21    static constexpr const char* NNVT_HighQE = "kPMT_NNVT_HighQE" ;


        

::

    :set nowrap

    epsilon:issues blyth$ jgr m_PMT_MPT
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    std::map<int, std::map<std::string, G4MaterialPropertyVector*>>& MPT = data.m_PMT_MPT;
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    NPFold* MPT = S4MaterialPropertyVector::Serialize_MIMSV(data.m_PMT_MPT); 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    S4MaterialPropertyVector::Import_MIMSV( data.m_PMT_MPT, MPT ); 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    ss << S4MaterialPropertyVector::Desc_MIMSV(data.m_PMT_MPT)   << std::endl ; 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h:    std::map<int, std::map<std::string, G4MaterialPropertyVector*>> m_PMT_MPT;
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h:    return m_PMT_MPT.at(pmtcat).at(prop_name) ;
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTQty.h:            if(data.m_PMT_MPT.count(cat) == 0)           continue ; 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTQty.h:            if(data.m_PMT_MPT.at(cat).count(qname) == 0) continue ; 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTQty.h:            mpva[cat] = data.m_PMT_MPT.at(cat).at(qname) ;  
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h:  std::map<int, std::map<std::string, G4MaterialPropertyVector*>>& m_PMT_MPT;
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    m_PMT_MPT(m_data.m_PMT_MPT),
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["ARC_RINDEX"], mcgt.data(), "PMTProperty.R12860.ARC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["ARC_KINDEX"], mcgt.data(), "PMTProperty.R12860.ARC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["PHC_RINDEX"], mcgt.data(), "PMTProperty.R12860.PHC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["PHC_KINDEX"], mcgt.data(), "PMTProperty.R12860.PHC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT]["ARC_RINDEX"], mcgt.data(), "PMTProperty.NNVTMCP.ARC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT]["ARC_KINDEX"], mcgt.data(), "PMTProperty.NNVTMCP.ARC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT]["PHC_RINDEX"], mcgt.data(), "PMTProperty.NNVTMCP.PHC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT]["PHC_KINDEX"], mcgt.data(), "PMTProperty.NNVTMCP.PHC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT_HighQE]["ARC_RINDEX"], mcgt.data(), "PMTProperty.NNVTMCP_HiQE.ARC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT_HighQE]["ARC_KINDEX"], mcgt.data(), "PMTProperty.NNVTMCP_HiQE.ARC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT_HighQE]["PHC_RINDEX"], mcgt.data(), "PMTProperty.NNVTMCP_HiQE.PHC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT_HighQE]["PHC_KINDEX"], mcgt.data(), "PMTProperty.NNVTMCP_HiQE.PHC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    auto iter1 = m_PMT_MPT.find(pmtcat);
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    assert(iter1 != m_PMT_MPT.end());
    epsilon:junosw blyth$ 





SSim/jpmt vs SSim/juno ? jpmt is the standard now 
------------------------------------------------------

:: 

    epsilon:junosw blyth$ jgr SSim
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#include "SSim.hh"
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:        SSim::Create();                    // done by G4CXOpticks::G4CXOpticks in opticksMode > 0
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:        SSim::AddSubfold("jpmt", jpmt );
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:        SSim::AddSubfold("jpmt", jpmt );  // needs to be before SaveGeometry 
    Binary file ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/.PMTSimParamData_test.sh.swp matches
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh:    base=$HOME/.opticks/GEOM/${GEOM:-J006}/CSGFoundry/SSim/juno/PMTSimParamData
    ./Detector/Geometry/Geometry/tests/PMTParamData_test.sh:    base=$HOME/.opticks/GEOM/J005/CSGFoundry/SSim/juno/PMTParamData
    epsilon:junosw blyth$ 


::

     16 void LSExpDetectorConstruction_Opticks::Setup(
     17           int opticksMode,
     18           const G4VPhysicalVolume* world,
     19           const G4VSensitiveDetector* sd,
     20           PMTParamData* ppd,
     21           PMTSimParamData* psd,
     22           NPFold* pmtscan
     23           )
     24 {   
     25     bool opticksMode_valid = opticksMode > -1 && opticksMode <= 3 ;  
     26     LOG_IF(fatal, !opticksMode_valid ) << " unexpected opticksMode " << opticksMode ;
     27     assert( opticksMode_valid );
     28     
     29     NPFold* jpmt = SerializePMT(ppd, psd, pmtscan) ;
     30     
     31     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     32     if( opticksMode == 0 )
     33     {   
     34         SEvt::HighLevelCreateOrReuse();    // U4RecorderAnaMgr not active in opticksMode:0 
     35         SSim::Create();                    // done by G4CXOpticks::G4CXOpticks in opticksMode > 0
     36         SSim::AddSubfold("jpmt", jpmt );
     37     }
     38     else if( opticksMode == 1 || opticksMode == 3 || opticksMode == 2 )
     39     {   
     40         if(opticksMode == 2) G4CXOpticks::SetNoGPU() ;
     41         G4CXOpticks::SetGeometry(world) ; 
     42         SSim::AddSubfold("jpmt", jpmt );  // needs to be before SaveGeometry 
     43         G4CXOpticks::SaveGeometry();
     44     }
     45     LOG(info) << "] WITH_G4CXOPTICKS " ;
     46 }



DONE : incorporate PyrexRINDEX VacuumRINDEX into SerializePMT
--------------------------------------------------------------- 


::

     48 NPFold* LSExpDetectorConstruction_Opticks::SerializePMT(
     49           PMTParamData* ppd,
     50           PMTSimParamData* psd,
     51           NPFold* pmtscan
     52      )
     53 {
     54     _PMTParamData    _ppd(*ppd) ;
     55     _PMTSimParamData _psd(*psd) ;
     56 
     57     NPFold* j = new NPFold ;
     58     j->add_subfold( "PMTParamData",    _ppd.serialize() );
     59     j->add_subfold( "PMTSimParamData", _psd.serialize() );
     60     if(pmtscan) j->add_subfold( "PMTScan",  pmtscan );
     61 
     62     return j ;
     63 }

::

    118 inline const PMTAccessor* PMTAccessor::Load(const char* base )
    119 {   
    120     const PMTSimParamData* data = LoadData(base) ;
    121     assert( data ); 
    122     return Create(data);
    123 }
    124 

::

      4 int main(int argc, char** argv)
      5 {
      6     const char* pathspec = "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/jpmt/PMTSimParamData" ;
      7     const PMTAccessor* pmt = PMTAccessor::Load(pathspec) ;
      8     if( pmt == nullptr )


Can PMTAccessor::Load from one directory up::

    $HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/jpmt

Thence can include the RINDEX in another subfold. 


TODO : commit persisted jpmt changes into another branch and MR
-----------------------------------------------------------------------

::

    epsilon:issues blyth$ jo
    /Users/blyth/junotop/junosw
    On branch blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping
    Your branch is up-to-date with 'origin/blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh

    Untracked files:
      (use "git add <file>..." to include in what will be committed)

        Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.cc
        Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.sh

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:junosw blyth$ 




What is missing with JPMT approach ?
---------------------------------------

See c4/C4CustomART::doIt getting pmtcat from pmtid and getting qe for (pmtid,energy)::

    260     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    261     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;

::

    210 inline double PMTAccessor::get_pmtid_qe( int pmtid, double energy ) const
    211 {   
    212     return data->get_pmtid_qe(pmtid, energy) ;
    213 }

    134 inline int PMTSimParamData::get_pmtcat(int pmtid) const
    135 {
    136     int idx = get_pmtContiguousIndex(pmtid);
    137     return m_all_pmt_catvec[idx];
    138 }

    177 inline double PMTSimParamData::get_pmtid_qe(int pmtid, double energy) const
    178 {
    179     int idx = get_pmtContiguousIndex(pmtid) ;
    180     int cat = m_all_pmt_catvec[idx] ;
    181     double qe = get_pmtcat_qe(cat, energy);   // interpolation on m_QEshape_.. MPV
    182     double qe_scale = m_all_pmtID_qe_scale[idx] ;
    183     qe *= qe_scale ;


    184     assert(qe > 0 && qe < 1);
    185     return qe ;
    186 }


    188 inline double PMTSimParamData::get_pmtcat_qe(int cat, double energy) const
    189 {
    190     G4MaterialPropertyVector* vec = get_pmtcat_qe_vs_energy(cat);
    191     double qe = vec->Value(energy);
    192     return qe;
    193 }

    245 inline G4MaterialPropertyVector* PMTSimParamData::get_pmtcat_qe_vs_energy(int pmtcat) const
    246 {
    247     G4MaterialPropertyVector * vec = 0 ;
    248     switch(pmtcat)
    249     {
    250         case kPMT_Unknown:     vec = m_QEshape_WP_PMT    ; break ;
    251         case kPMT_NNVT:        vec = m_QEshape_NNVT      ; break ;
    252         case kPMT_Hamamatsu:   vec = m_QEshape_R12860    ; break ;
    253         case kPMT_HZC:         vec = m_QEshape_HZC       ; break ;
    254         case kPMT_NNVT_HighQE: vec = m_QEshape_NNVT_HiQE ; break ;
    255     }

   
Whats missing is contiguous pmt index array with category and qe_scale.


HMM : Skip WPMTs SPMTs from the arrays needed for QPMT ?
----------------------------------------------------------

Only pmtid from NNVT,NNVTHiQE,HAMA PMTs will be arriving into 
QPMT because only those have the special "@/#" surface names prefix.  
So can skip WPMTs and SPMTs. 

HMM: that restriction means the pmtid is already contiguous so 
can directly use it to lookup pmtCat and qeScale. 


::

    /Users/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.py


                                          t.pmtID.shape  : (45612, 1) 
                                         t.pmtCat.shape  : (45612, 2) 
                                      t.pmtCatVec.shape  : (45612, 1) 
                                        t.qeScale.shape  : (45612, 1) 
                                         t.lpmtCat.shape : (17612, 1) 
                                        t.lpmtData.shape : (20012, 9) 

                     np.all(t.pmtID[:,0]==t.pmtCat[:,0]) : True 
                 np.all(t.pmtCatVec[:,0]==t.pmtCat[:,1]) : True 
      np.all(t.pmtCat[:len(t.lpmtCat),1]==t.lpmtCat[:,0]) : True 

      np.all(t.lpmtData[:len(t.lpmtCat),0].view(np.int64)==t.pmtID[:len(t.lpmtCat),0]) : True 



