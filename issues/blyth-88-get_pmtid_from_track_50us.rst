blyth-88-get_pmtid_from_track_50us
====================================

Overview
------------

Investigations in :doc:`blyth-88-merge-totalTime` reveal that junoPMT_SD_v2::get_pmtid 
is consuming 50us for every SD hit candidate. Just the same for N=0 and N=1.  
Here looking into alternatives.  

HMM: this should be a separate junosw issue


DONE : Getting get_pmtid result into SEvt ? Added U4Touchable::ImmediateReplicaNumber used from U4Recorder step pointing
-------------------------------------------------------------------------------------------------------------------------


* Note the limitation to SD step points only

* 
  

::

    iix = b.f.photon[:,1,3].view(np.uint32) 

    MODE=3 N=0 W=IXX  ~/j/ntds/ntds.sh ana

::

     795 #ifdef U4RECORDER_EXPENSIVE_IINDEX
     796     // doing replica number search for every step is very expensive and often pointless
     797     // its the kind of thing to do only for low stats or simple geometry running 
     798     current_photon.iindex = U4Touchable::ReplicaNumber(touch, REPLICA_NAME_SELECT);
     799 #else
     800     current_photon.iindex = is_surface_flag ? U4Touchable::ReplicaNumber(touch, REPLICA_NAME_SELECT) : -2 ;
     801 #endif

Instead try::

     804     current_photon.iindex = is_detect_flag ? U4Touchable::ImmediateReplicaNumber(touch) : -2 ;


    In [5]: np.set_printoptions(edgeitems=100)

    In [6]: np.c_[np.unique(b.iix[b.iix>-1],return_counts=True)]
    Out[6]: 
    array([[     0,    710],
           [     1,    724],
           [     2,     28],
           [     3,      3],
           [     4,      6],
           [     5,    145],
           [     6,    646],
           [     7,    751],
           [     8,    644],
           [     9,     46],
           [    10,     14],
           [    12,      3],
           [    15,      1],
           [    16,      1],
           [    17,     17],
           [    18,     16],
           [    19,    713],
           [    20,    735],
           [    21,    426],
           [    22,    638],
           [    23,     75],
           [    24,      2],
           [    27,      2],
           ...
           [ 17587,      1],
           [ 17588,      1],
           [ 17604,      1],
           [ 17609,      1],
           [300024,      1],
           [300025,      1],
           [300284,      1],
           [300476,      1],
           [300777,      1],
           [300830,      1],
           [301796,      1],
           [301952,      1],
           [302998,      1],
           [303236,      1],
           [303768,      1],
           [303794,      1],
           [303831,      1],
           [304166,      1],
           [304308,      1],
           [307435,      1],
           [307841,      1],
           [308241,      1],
           [308312,      1],
           [308521,      1],
           [308948,      1],
           [310076,      1],
           [310424,      1],
           [310609,      1],
           [310751,      1],
           [310992,      1],





DONE : Confirmed Culprit "get_pmtid(track)" taking ~50us for every ProcessHits call that gets that far
--------------------------------------------------------------------------------------------------------

Thoughts on this, the CE(pmtID) is only used to compare against a random for DE culling.
So it seems very expensive to get the precise CE for every hit candidate. 
It would be much faster to use a generic CE for the culling and only 
do the pmtID lookup post the culling. So then do it much less often.  

On the otherhand maybe the simpler PMT geometry means can get simpler get_pmtid to work ?

* YEP, this seems to be the case

Simplify profile stamping to confirm::

     489 #ifdef WITH_G4CXOPTICKS
     490     m_profile->stamp(1);
     491 #endif
     492 
     493     double qe = 1;
     494     double ce = 1;
     495     // == get the copy number -> pmt id
     496     int pmtID = get_pmtid(track);
     497 
     498 #ifdef WITH_G4CXOPTICKS
     499     m_profile->stamp(2);
     500 #endif

::

    In [11]: (pp - pp[:,0,np.newaxis])[10:30]   ## ~50us 1->2
    Out[11]: 
    array([[                   0,                    1,                   50,                   55],
           [                   0,                    1,                   49,                   53],
           [                   0,                    0,                   49,                   53],
           [                   0,                    1,                   50,                   56],
           [                   0,                    0,                   48,                   52],

    In [3]: np.diff(a.pf[a.pfr>20,1:],axis=1)[10:]
    Out[3]: 
    array([[ 1, 49,  5],
           [ 1, 48,  4],
           [ 0, 49,  4],
           [ 1, 49,  6],
           [ 0, 48,  4],
           ...,
           [ 0, 48,  5],
           [ 1, 51,  5],
           [ 1, 48,  5],
           [ 1, 48,  6],
           [ 1, 54,  5]], dtype=uint64)



Overcomplex get_pmtid : Looping over daughters at multiple levels and comparing names seems unneccessary 
------------------------------------------------------------------------------------------------------------

The sensitive volumes at which ProcessHits is called will always 
be one of a few, so can use less general approach to get copynumber.

fast "get_pmtid" (~1us)::

    const G4VTouchable* touch = track->GetTouchable();
    int pmtID = touch->GetReplicaNumber(1) ; 
    if(pmtID <= 0) pmtID = touch->GetReplicaNumber(2) ; 

slow get_pmtid (~50us)::

     int junoSD_PMT_v2::get_pmtid(G4Track* track) {
         int ipmt= -1;
         const G4VTouchable* touch= track->GetTouchable();
         int nd= touch->GetHistoryDepth();
         int id=0;
         for (id=0; id<nd; id++) {
             if (touch->GetVolume(id)==track->GetVolume()) {
                 int idid=1;
                 G4VPhysicalVolume* tmp_pv=NULL;
                 for (idid=1; idid < (nd-id); ++idid) {
                     tmp_pv = touch->GetVolume(id+idid);
     
                     G4LogicalVolume* mother_vol = tmp_pv->GetLogicalVolume();
                     G4LogicalVolume* daughter_vol = touch->GetVolume(id+idid-1)->
                         GetLogicalVolume();
                     int no_daugh = mother_vol -> GetNoDaughters();
                     if (no_daugh > 1) {
                         int count = 0;
                         for (int i=0; (count<2) &&(i < no_daugh); ++i) {
                             if (daughter_vol->GetName()
                                     ==mother_vol->GetDaughter(i)->GetLogicalVolume()->GetName()) {
                                 ++count;
                             }
                         }
                         if (count > 1) {
                             break;
                         }
                     }
                     // continue to find
                 }
                 ipmt= touch->GetReplicaNumber(id+idid-1);
                 break;
             }
         return ipmt;
     }


DONE : Whats the pmtID used for ? Can it be deferred ? Can it be made faster ?
--------------------------------------------------------------------------------

The pmtid is used only to find the pmtcat to give the CE.
Maybe can find the pmtcat by a faster way ?
The problem is distinguishing kPMT_NNVT and kPMT_NNVT_HighQE. 
Unless were to adopt a naming convention to make it easier 
to distinguish those?

* but it seems that there is a faster way to get_pmtid anyhow

::

     504     // = final DE = QE * CE, 
     505     // but QE is already applied (this is old implementation,
     506     // Now we use PMTSimParamSvc to get real QE and CE ), so only CE is important.
     507     // = DE: Detection Efficiency
     508     if(m_use_pmtsimsvc){
     509         qe = (m_enable_optical_model && PMT::Is20inch(pmtID)) ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);
     510 
     511         ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());
     512 
     513      }
     514      else{
     515         std::string volname = track->GetVolume()->GetName();
     516     GetQEandCEByOldWay(qe , ce , pmtID,  volname, local_pos);
     517      }
     518 

     966 double PMTSimParamSvc::get_pmtid_ce(int pmtid , double theta) const
     967 {
     968      int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
     969      double ce = get_pmtcat_ce(pmtcat,theta);
     970      assert( ce > 0 );
     971      return  ce ;
     972 
     973 }

     975 double PMTSimParamSvc::get_pmtcat_ce(int pmtcat, double theta) const
     976 {
     977 
     978   assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
     979   double ce = -1;
     980   G4MaterialPropertyVector * vec = 0 ;
     981   switch(pmtcat)
     982     {   //FIXME:KPMT_Unknown represent WP pmt,which are use normal NNVTMCP ?
     983         case kPMT_Unknown:     { vec = m_CE_WP_PMT ; } ; break ;
     984         case kPMT_NNVT:        { vec = m_CE_NNVTMCP ; } ; break ;
     985         case kPMT_Hamamatsu:   { vec = m_CE_R12860 ; } ; break ;
     986         case kPMT_HZC:         { ce = 1.0 ; } ; return ce ;
     987         case kPMT_NNVT_HighQE: { vec = m_CE_NNVTMCP_HiQE ; } ; break ;
     988     }
     989  
     990   if(vec){
     991         //vec -> SetSpline(false);  that is default 
     992         ce = vec->Value(theta);
     993   }
     994    
     995   //double CE = ce >= 1 ? 1 : ce ;  
     996   assert(ce > 0 && ce <= 1 );
     997   return ce;
     998 }

The CE are different::

    epsilon:PMTProperty blyth$ diff -y NNVTMCP_HiQE/CE NNVTMCP/CE
    0   *deg   1							0   *deg   1
    14   *deg   1							14   *deg   1
    30   *deg   0.9772					      |	30   *deg   0.9453
    42.5   *deg   0.9723					      |	42.5   *deg   0.9105
    55   *deg   0.9699					      |	55   *deg   0.8931
    67   *deg   0.9697					      |	67   *deg   0.9255
    77.5   *deg   0.9452					      |	77.5   *deg   0.9274
    85   *deg   0.9103					      |	85   *deg   0.8841
    90   *deg   0.734						90   *deg   0.734
    epsilon:PMTProperty blyth$ 



DONE : Compare Result and timings for get_pmtid alternates
-----------------------------------------------------------

::

    In [11]: np.diff(a.pf[a.pfr>20,1:],axis=1)[2:,:5]
    Out[11]: 
    array([[ 1, 51, 46,  0, 46],
           [ 0, 51, 46,  0,  7],
           [ 0, 50, 46,  1,  5],
           [ 1, 50, 46,  0,  7],
           [ 1, 51, 52,  0,  5],
           [ 1, 50, 46,  0,  5],
           [ 1, 50, 46,  1,  4],
           [ 1, 51, 46,  0,  7],
           [ 1, 50, 46,  0,  6],
           [ 1, 50, 46,  0,  5],
           ...,
           [ 1, 50, 46,  0,  5],
           [ 1, 51, 47,  0,  5],
           [ 1, 50, 46,  0,  7],
           [ 1, 51, 47,  0,  5],
           [ 1, 50, 46,  0,  5],
           [ 1, 50, 46,  0,  6],
           [ 1, 52, 46,  0,  6],
           [ 1, 50, 52,  1,  5],
           [ 1, 50, 47,  0,  6],
           [ 1, 50, 46,  0,  6]], dtype=uint64)

::

     496 #ifdef WITH_G4CXOPTICKS
     497     m_profile->stamp(1); 
     498 #endif 
     499     int pmtID = get_pmtid(track);
     500 #ifdef WITH_G4CXOPTICKS
     501     m_profile->stamp(2); 
     502 #endif
     503     int pmtID_1 = C4Touchable::VolumeIdentifier(track, false );
     504 #ifdef WITH_G4CXOPTICKS       
     505     m_profile->stamp(3); 
     506 #endif
     507     //int pmtID_2 = C4Touchable::VolumeCopyNo(track);  // this always 0 
     508     const G4VTouchable* touch = track->GetTouchable();
     509     int pmtID_2 = touch->GetReplicaNumber(1) ; 
     510     if(pmtID_2 == 0) pmtID_2 = touch->GetReplicaNumber(2) ;
     511     // HMM: with Natural PMT Geom should be (1) with Unnatural should be (2)
     512 
     513 #ifdef WITH_G4CXOPTICKS
     514     m_profile->stamp(4);
     515 #endif 
     516        
     517     bool pmtID_consistent = pmtID_2 == pmtID && pmtID_1 == pmtID ;
     518     if( pmtID_consistent == false )
     519     {   
     520         std::cout 
     521             << "junoSD_PMT_v2::ProcessHits"
     522             << " pmtID " << pmtID    
     523             << " pmtID_1 " << pmtID_1
     524             << " pmtID_2 " << pmtID_2
     525             << " pv " << track->GetVolume()->GetName()
     526             << std::endl
     527             ;
     528     }
     529     assert( pmtID_consistent );


::

    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 315564 pmtID_1 315564 pmtID_2 0 pv PMT_3inch_body_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 315564 pmtID_1 315564 pmtID_2 0 pv PMT_3inch_body_phys
    junoSD_PMT_v2::ProcessHits pmtID 315564 pmtID_1 315564 pmtID_2 0 pv PMT_3inch_body_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 315564 pmtID_1 315564 pmtID_2 0 pv PMT_3inch_body_phys
    junoSD_PMT_v2::ProcessHits pmtID 315564 pmtID_1 315564 pmtID_2 0 pv PMT_3inch_body_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 315564 pmtID_1 315564 pmtID_2 0 pv PMT_3inch_body_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 0 pv NNVTMCPPMT_PMT_20inch_log_phys



DONE : Explain why the simple "get_pmtid_fast" approach seems to be working
-----------------------------------------------------------------------------

For new_LPMT and SPMT the below simple approach seems to be working.::

     508     const G4VTouchable* touch = track->GetTouchable();
     509     int pmtID_2 = touch->GetReplicaNumber(1) ; 

Initially was surprised by this, expecting one more level would
be needed to get up to the copynumber. BUT, I think I see why now. 
The SD is defined at lower LV level but it has impact for the PV level above it. 
Hence one level of touch hierarchy is effectively skipped. 

For old LPMT adding the below seems to work::

     510     if(pmtID_2 == 0) pmtID_2 = touch->GetReplicaNumber(2) ;

BUT, There is an inherent problem with this as pmtid:0 is a valid pmtid.
Even if it will usually work, its confusing. Better to standardly arrange 
copynumber -1 for non repeated  PMT volumes, so can then get_pmtid
with more certainty. 



spmt (old/new makes no difference)::

    junoSD_PMT_v2::ProcessHits pmtID 325044 pmtID_1 325044 pmtID_2 325044 pv PMT_3inch_body_phys
    junoSD_PMT_v2::ProcessHits
    C4Touchable::Desc HistoryDepth  7 TouchDepth  0 ReplicaDepth  1 ReplicaNumber 325044
     i  0 cp      0 nd      2 so PMT_3inch_body_solid_ell_ell_helper pv  PMT_3inch_body_phys
     i  1 cp 325044 nd      2 so  PMT_3inch_pmt_solid pv   PMT_3inch_log_phys
     i  2 cp      0 nd  46276 so          sInnerWater pv          pInnerWater
     i  3 cp      0 nd      1 so       sReflectorInCD pv     pCentralDetector
     i  4 cp      0 nd   4521 so      sOuterWaterPool pv      pOuterWaterPool
     i  5 cp      0 nd      1 so          sPoolLining pv          pPoolLining
     i  6 cp      0 nd      1 so          sBottomRock pv             pBtmRock

LPMT_NEW (same depth to get copynumber as SPMT)::

    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 1425 pv NNVTMCPPMT_PMT_20inch_log_phys
    junoSD_PMT_v2::ProcessHits
    C4Touchable::Desc HistoryDepth  7 TouchDepth  0 ReplicaDepth  1 ReplicaNumber   1425
     i  0 cp      0 nd      1 so NNVTMCPPMT_PMT_20inch_pmt_solid_head pv NNVTMCPPMT_PMT_20inch_log_phys
     i  1 cp   1425 nd      3 so NNVTMCPPMTsMask_virtual pv    pLPMT_NNVT_MCPPMT
     i  2 cp      0 nd  46276 so          sInnerWater pv          pInnerWater
     i  3 cp      0 nd      1 so       sReflectorInCD pv     pCentralDetector
     i  4 cp      0 nd   4521 so      sOuterWaterPool pv      pOuterWaterPool
     i  5 cp      0 nd      1 so          sPoolLining pv          pPoolLining
     i  6 cp      0 nd      1 so          sBottomRock pv             pBtmRock

LPMT_OLD (one more level to get copynumber)::

    junoSD_PMT_v2::ProcessHits pmtID 1425 pmtID_1 1425 pmtID_2 1425 pv NNVTMCPPMT_PMT_20inch_body_phys
    junoSD_PMT_v2::ProcessHits
    C4Touchable::Desc HistoryDepth  8 TouchDepth  0 ReplicaDepth  2 ReplicaNumber   1425
     i  0 cp      0 nd      2 so NNVTMCPPMT_PMT_20inch_body_solid_head pv NNVTMCPPMT_PMT_20inch_body_phys
     i  1 cp      0 nd      1 so NNVTMCPPMT_PMT_20inch_pmt_solid_head pv NNVTMCPPMT_PMT_20inch_log_phys
     i  2 cp   1425 nd      3 so NNVTMCPPMTsMask_virtual pv    pLPMT_NNVT_MCPPMT
     i  3 cp      0 nd  46276 so          sInnerWater pv          pInnerWater
     i  4 cp      0 nd      1 so       sReflectorInCD pv     pCentralDetector
     i  5 cp      0 nd   4521 so      sOuterWaterPool pv      pOuterWaterPool
     i  6 cp      0 nd      1 so          sPoolLining pv          pPoolLining
     i  7 cp      0 nd      1 so          sBottomRock pv             pBtmRock



DONE : Check "get_pmtid_fast" when targetting Hama:0:0 (pmtid 0 is a valid ID)
-----------------------------------------------------------------------------------

vim -R ~/.opticks/GEOM/V1J008/origin.gdml ## reverse search for copynumber="1" to get here::

     18997       <physvol name="pLPMT_Hamamatsu_R128600x61c7720">
     18998         <volumeref ref="HamamatsuR12860lMaskVirtual0x61adac0"/>
     18999         <position name="pLPMT_Hamamatsu_R128600x61c7720_pos" unit="mm" x="-930.297607421875" y="-111.872398376465" z="19365"/>
     19000         <rotation name="pLPMT_Hamamatsu_R128600x61c7720_rot" unit="deg" x="180" y="0" z="180"/>
     19001       </physvol>
     19002       <physvol copynumber="1" name="pLPMT_Hamamatsu_R128600x61c77d0">
     19003         <volumeref ref="HamamatsuR12860lMaskVirtual0x61adac0"/>
     19004         <position name="pLPMT_Hamamatsu_R128600x61c77d0_pos" unit="mm" x="-492.565704345703" y="-797.087219238281" z="19365"/>
     19005         <rotation name="pLPMT_Hamamatsu_R128600x61c77d0_rot" unit="deg" x="180" y="0" z="180"/>
     19006       </physvol>



DONE : target WP PMT ? Try with OPTICKS_INPUT_PHOTON_FRAME PMT_20inch_veto:0:1000
-----------------------------------------------------------------------------------

Opticks frame targetting picks the volume with solid names starting 
with the provided string. Checking solid names::

    epsilon:~ blyth$ grep veto  ~/.opticks/GEOM/V1J008/CSGFoundry/meshname.txt 
    mask_PMT_20inch_vetosMask
    PMT_20inch_veto_inner1_solid
    PMT_20inch_veto_inner2_solid
    PMT_20inch_veto_body_solid_1_2
    PMT_20inch_veto_pmt_solid_1_2
    mask_PMT_20inch_vetosMask_virtual
    epsilon:~ blyth$ 

Using in ntds::

    export OPTICKS_INPUT_PHOTON_FRAME=PMT_20inch_veto:0:1000

WP (like LPMT_OLD needs the one more level)::

    junoSD_PMT_v2::ProcessHits pmtID 31000 pmtID_1 31000 pmtID_2 31000 pv PMT_20inch_veto_body_phys
    junoSD_PMT_v2::ProcessHits
    C4Touchable::Desc HistoryDepth  6 TouchDepth  0 ReplicaDepth  2 ReplicaNumber  31000
     i  0 cp      0 nd      2 so PMT_20inch_veto_body_solid_1_2 pv PMT_20inch_veto_body_phys
     i  1 cp      0 nd      1 so PMT_20inch_veto_pmt_solid_1_2 pv PMT_20inch_veto_log_phys
     i  2 cp  31000 nd      2 so mask_PMT_20inch_vetosMask_virtual pv mask_PMT_20inch_vetolMaskVirtual_phys
     i  3 cp      0 nd   4521 so      sOuterWaterPool pv      pOuterWaterPool
     i  4 cp      0 nd      1 so          sPoolLining pv          pPoolLining
     i  5 cp      0 nd      1 so          sBottomRock pv             pBtmRock


WP GDML
-----------

::

    vim -R ~/.opticks/GEOM/V1J008/origin.gdml

    245714       <physvol copynumber="30000" name="mask_PMT_20inch_vetolMaskVirtual_phys0x73549a0">
    245715         <volumeref ref="mask_PMT_20inch_vetolMaskVirtual0x61c24e0"/>
    245716         <position name="mask_PMT_20inch_vetolMaskVirtual_phys0x73549a0_pos" unit="mm" x="-1205.30004882812" y="-879.47802734375" z=       "20502"/>
    245717         <rotation name="mask_PMT_20inch_vetolMaskVirtual_phys0x73549a0_rot" unit="deg" x="-2.45630010165137" y="3.36143615676494" z       ="143.810910635206"/>
    245718       </physvol>
    245719       <physvol copynumber="30001" name="mask_PMT_20inch_vetolMaskVirtual_phys0x7354b30">
    245720         <volumeref ref="mask_PMT_20inch_vetolMaskVirtual0x61c24e0"/>
    245721         <position name="mask_PMT_20inch_vetolMaskVirtual_phys0x7354b30_pos" unit="mm" x="-576.010986328125" y="-735.794006347656" z       ="20502"/>
    245722         <rotation name="mask_PMT_20inch_vetolMaskVirtual_phys0x7354b30_rot" unit="deg" x="-2.05540563078894" y="1.60827063420383" z       ="128.02614046264"/>
    245723       </physvol>



::

    736    if [ -n "$IPHO" ]; then
    737        export OPTICKS_INPUT_PHOTON=$IPHO
    738 
    739        #moi=Hama:0:1000 
    740        #moi=NNVT:0:1000 
    741        #export MOI=${MOI:-$moi}
    742 
    743        #oipf=Hama:0:1000
    744        #oipf=NNVT:0:1000 
    745        oipf=PMT_20inch_veto:0:1000
    746        export OPTICKS_INPUT_PHOTON_FRAME=${OPTICKS_INPUT_PHOTON_FRAME:-$oipf}
    747        
    748        layout="OIPF_$OPTICKS_INPUT_PHOTON_FRAME"

::

    junotoptask:SniperProfiling.initialize  INFO: 
    GtOpticksTool::configure WITH_G4CXOPTICKS SEvt::Brief  SEvt::Exists Y INSTANCE SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed N
     ret true


    ### Run : 0
    junotoptask.initialize          INFO: initialized
    GtOpticksTool::mutate event_number 0 deferred SEvt::GetInputPhoton  SEvt::Brief  SEvt::Exists Y INSTANCE SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     m_input_photon (10000, 4, 4, )




DONE : Check get_pmtid fast alternative works for SPMT WPMT and old+new LPMT  
--------------------------------------------------------------------------------

Looks like it does. 



SPMT Volumes : 3 pv levels : PMT_3inch_log_phys/PMT_3inch_body_phys/
----------------------------------------------------------------------



::

    107134       <physvol copynumber="300000" name="PMT_3inch_log_phys0x695d430">
    107135         <volumeref ref="PMT_3inch_log0x695c3c0"/>
    107136         <position name="PMT_3inch_log_phys0x695d430_pos" unit="mm" x="-3734.24731445312" y="1835.06555175781" z="18932.177734375"/>
    107137         <rotation name="PMT_3inch_log_phys0x695d430_rot" unit="deg" x="-174.463707486899" y="-11.1072346781693" z="-26.7089254961022"/>
    107138       </physvol>


    003721     <volume name="PMT_3inch_log0x695c3c0">
      3722       <materialref ref="Water0x59d8640"/>
      3723       <solidref ref="PMT_3inch_pmt_solid0x695b8c0"/>
      3724       <physvol name="PMT_3inch_body_phys0x695c810">
      3725         <volumeref ref="PMT_3inch_body_log0x695c310"/>
      3726       </physvol>
      3727       <physvol name="PMT_3inch_cntr_phys0x695ca00">
      3728         <volumeref ref="PMT_3inch_cntr_log0x695c6f0"/>
      3729       </physvol>
      3730     </volume>

    003706     <volume name="PMT_3inch_body_log0x695c310">
      3707       <materialref ref="Pyrex0x59cbfd0"/>
      3708       <solidref ref="PMT_3inch_body_solid_ell_ell_helper0x695bb20"/>
      3709       <physvol name="PMT_3inch_inner1_phys0x695c8a0">
      3710         <volumeref ref="PMT_3inch_inner1_log0x695c4b0"/>
      3711       </physvol>
      3712       <physvol name="PMT_3inch_inner2_phys0x695c930">
      3713         <volumeref ref="PMT_3inch_inner2_log0x695c5d0"/>
      3714       </physvol>
      3715       <auxiliary auxtype="SensDet" auxvalue="PMTSDMgr"/>
      3716     </volume>




GDML : Check New Volume Structure
------------------------------------

vim -R /Users/blyth/.opticks/GEOM/V1J008/origin.gdml::

     18997       <physvol name="pLPMT_Hamamatsu_R128600x61c7720">
     18998         <volumeref ref="HamamatsuR12860lMaskVirtual0x61adac0"/>
     18999         <position name="pLPMT_Hamamatsu_R128600x61c7720_pos" unit="mm" x="-930.297607421875" y="-111.872398376465" z="19365"/>
     19000         <rotation name="pLPMT_Hamamatsu_R128600x61c7720_rot" unit="deg" x="180" y="0" z="180"/>
     19001       </physvol>
     19002       <physvol copynumber="1" name="pLPMT_Hamamatsu_R128600x61c77d0">
     19003         <volumeref ref="HamamatsuR12860lMaskVirtual0x61adac0"/>
     19004         <position name="pLPMT_Hamamatsu_R128600x61c77d0_pos" unit="mm" x="-492.565704345703" y="-797.087219238281" z="19365"/>
     19005         <rotation name="pLPMT_Hamamatsu_R128600x61c77d0_rot" unit="deg" x="180" y="0" z="180"/>
     19006       </physvol>
     19007       <physvol copynumber="2" name="pLPMT_NNVT_MCPPMT0x61c78d0">
     19008         <volumeref ref="NNVTMCPPMTlMaskVirtual0x61bf0d0"/>
     19009         <position name="pLPMT_NNVT_MCPPMT0x61c78d0_pos" unit="mm" x="316.078186035156" y="-882.0791015625" z="19365"/>
     19010         <rotation name="pLPMT_NNVT_MCPPMT0x61c78d0_rot" unit="deg" x="180" y="0" z="180"/>
     19011       </physvol>

     03609     <volume name="NNVTMCPPMTlMaskVirtual0x61bf0d0">
      3610       <materialref ref="Water0x59d85d0"/>
      3611       <solidref ref="NNVTMCPPMTsMask_virtual0x61be1b0"/>
      3612       <physvol name="NNVTMCPPMTpMask0x61bfcd0">
      3613         <volumeref ref="NNVTMCPPMTlMask0x61bfb70"/>
      3614       </physvol>
      3615       <physvol name="NNVTMCPPMTpMaskTail0x61c1010">
      3616         <volumeref ref="NNVTMCPPMTlMaskTail0x61c0eb0"/>
      3617       </physvol>
      3618       <physvol name="NNVTMCPPMT_PMT_20inch_log_phys0x61c11f0">
      3619         <volumeref ref="NNVTMCPPMT_PMT_20inch_log0x61b8dc0"/>
      3620       </physvol>
      3621     </volume>

     03602     <volume name="NNVTMCPPMT_PMT_20inch_log0x61b8dc0">
      3603       <materialref ref="Pyrex0x59cbf60"/>
      3604       <solidref ref="NNVTMCPPMT_PMT_20inch_pmt_solid_head0x61b4ed0"/>
      3605       <physvol name="NNVTMCPPMT_PMT_20inch_inner_phys0x61b8f20">
      3606         <volumeref ref="NNVTMCPPMT_PMT_20inch_inner_log0x61b8e70"/>
      3607       </physvol>
      3608     </volume>




GDML : Check Old Volume structure 
------------------------------------------------------

It is clear that the old structure has one extra level of hierarchy. 


The pv with the pmtid copynumber holds the MaskVirtual which holds NNVTMCPPMT_PMT_20inch_log 

vim -R /Users/blyth/.opticks/GEOM/V0J008/origin.gdml::

     19074       <physvol name="pLPMT_Hamamatsu_R128600x61de6a0">
     19075         <volumeref ref="HamamatsuR12860lMaskVirtual0x61bd980"/>
     19076         <position name="pLPMT_Hamamatsu_R128600x61de6a0_pos" unit="mm" x="-930.297607421875" y="-111.872398376465" z="19365"/>
     19077         <rotation name="pLPMT_Hamamatsu_R128600x61de6a0_rot" unit="deg" x="180" y="0" z="180"/>
     19078       </physvol>
     19079       <physvol copynumber="1" name="pLPMT_Hamamatsu_R128600x61de750">
     19080         <volumeref ref="HamamatsuR12860lMaskVirtual0x61bd980"/>
     19081         <position name="pLPMT_Hamamatsu_R128600x61de750_pos" unit="mm" x="-492.565704345703" y="-797.087219238281" z="19365"/>
     19082         <rotation name="pLPMT_Hamamatsu_R128600x61de750_rot" unit="deg" x="180" y="0" z="180"/>
     19083       </physvol>
     19084       <physvol copynumber="2" name="pLPMT_NNVT_MCPPMT0x61de850">
     19085         <volumeref ref="NNVTMCPPMTlMaskVirtual0x61d6050"/>
     19086         <position name="pLPMT_NNVT_MCPPMT0x61de850_pos" unit="mm" x="316.078186035156" y="-882.0791015625" z="19365"/>
     19087         <rotation name="pLPMT_NNVT_MCPPMT0x61de850_rot" unit="deg" x="180" y="0" z="180"/>
     19088       </physvol>
     19089       <physvol copynumber="3" name="pLPMT_Hamamatsu_R128600x61de950">
     19090         <volumeref ref="HamamatsuR12860lMaskVirtual0x61bd980"/>
     19091         <position name="pLPMT_Hamamatsu_R128600x61de950_pos" unit="mm" x="886.708801269531" y="-302.847412109375" z="19365"/>
     19092         <rotation name="pLPMT_Hamamatsu_R128600x61de950_rot" unit="deg" x="180" y="0" z="180"/>
     19093       </physvol>


     03684     <volume name="NNVTMCPPMTlMaskVirtual0x61d6050">
      3685       <materialref ref="Water0x59d8640"/>
      3686       <solidref ref="NNVTMCPPMTsMask_virtual0x61d5910"/>
      3687       <physvol name="NNVTMCPPMTpMask0x61d6ce0">
      3688         <volumeref ref="NNVTMCPPMTlMask0x61d6b80"/>
      3689       </physvol>
      3690       <physvol name="NNVTMCPPMTpMaskTail0x61d8020">
      3691         <volumeref ref="NNVTMCPPMTlMaskTail0x61d7ec0"/>
      3692       </physvol>
      3693       <physvol name="NNVTMCPPMT_PMT_20inch_log_phys0x61d8200">
      3694         <volumeref ref="NNVTMCPPMT_PMT_20inch_log0x61cd810"/>
      3695       </physvol>
      3696     </volume>

     03677     <volume name="NNVTMCPPMT_PMT_20inch_log0x61cd810">
      3678       <materialref ref="Pyrex0x59cbfd0"/>
      3679       <solidref ref="NNVTMCPPMT_PMT_20inch_pmt_solid_head0x61c5a50"/>
      3680       <physvol name="NNVTMCPPMT_PMT_20inch_body_phys0x61cdad0">
      3681         <volumeref ref="NNVTMCPPMT_PMT_20inch_body_log0x61cd8c0"/>
      3682       </physvol>
      3683     </volume>


     03666     <volume name="NNVTMCPPMT_PMT_20inch_body_log0x61cd8c0">
      3667       <materialref ref="Pyrex0x59cbfd0"/>
      3668       <solidref ref="NNVTMCPPMT_PMT_20inch_body_solid_head0x61c7be0"/>
      3669       <physvol name="NNVTMCPPMT_PMT_20inch_inner1_phys0x61cdb50">
      3670         <volumeref ref="NNVTMCPPMT_PMT_20inch_inner1_log0x61cd970"/>
      3671       </physvol>
      3672       <physvol name="NNVTMCPPMT_PMT_20inch_inner2_phys0x61cddd0">
      3673         <volumeref ref="NNVTMCPPMT_PMT_20inch_inner2_log0x61cda20"/>
      3674       </physvol>
      3675       <auxiliary auxtype="SensDet" auxvalue="PMTSDMgr"/>
      3676     </volume>



Does junoSD_PMT_v2 needs to know UsePMTNatural ? NO, Not Needed Yet
----------------------------------------------------------------------

* Could be done easily by adding another declProp, but not currently needed

:doc:`junoSD_PMT_v2_UsePMTNatural`


G4VTouchable::GetReplicaNumber Take a look at Geant4 impl
--------------------------------------------------------------

* :doc:`G4VTouchable_GetReplicaNumber`


WIP : Insitu : NOFAKESKIP=1 ntds2_cf
-------------------------------------

::

    NOFAKESKIP=1 ntds2_cf


* TODO: get Fake skipping setting into RunMeta

::

    In [6]: a.fp.run_meta
    Out[6]: 
    T_BeginOfRun:1684583398751971
    T_EndOfRun:1684583405402707





::

     176 void U4Recorder::EndOfRunAction(const G4Run*)
     177 {
     178     SEvt::EndOfRun();
     179     SEvt::SaveRunMeta();
     180 


     835 /**
     836 SEvt::SaveRunMeta
     837 -------------------
     838 
     839 May be called for example from U4Recorder::EndOfRunAction
     840 
     841 **/
     842 
     843 void SEvt::SaveRunMeta(const char* base)
     844 {
     845     const char* dir = RunDir(base);
     846     NP* m = NP::Make<float>(1);
     847     m->set_meta<uint64_t>("T_BeginOfRun", T_BeginOfRun );
     848     m->set_meta<uint64_t>("T_EndOfRun",   T_EndOfRun );
     849     m->save(dir, "run.npy") ;
     850 }
     851 

::

     176 void U4Recorder::EndOfRunAction(const G4Run*)
     177 {
     178     SEvt::EndOfRun();
     179 
     180     SEvt::SetRunMeta<int>("FAKES_SKIP", int(FAKES_SKIP) ); 
     181     SEvt::SaveRunMeta();
     182     

::

    In [2]: a.fp.run_meta
    Out[2]: 
    FAKES_SKIP:1
    T_BeginOfRun:1684678995630639
    T_EndOfRun:1684679543766151





TODO : BP=DetSim1Construction::inject check whats doing the placement
------------------------------------------------------------------------ 



TODO : Make Connection between SniperProfile totals and my timestamp durations
---------------------------------------------------------------------------------

::

    SEvt::save@2640:  dir /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/002
    SEvt::gatherHit@2092:  not yet implemented for hostside running : change CompMask with SEventConfig to avoid 
    SEvt::clear_@986: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    [ U4Recorder::EndOfRunAction U4Recorder__EndOfRunAction_Simtrace:N
    ] U4Recorder::EndOfRunAction U4Recorder__EndOfRunAction_Simtrace:N
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 3           49.82700       16.60900     2.67074      
    DetSimAlg                3           7007.20703     2335.73568   21.45958     
    Sum of junotoptask       3           7057.25806     2352.41935   23.87170     
    #############################################################################


    SEvt::save@2640:  dir /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/002
    SEvt::gatherHit@2092:  not yet implemented for hostside running : change CompMask with SEventConfig to avoid 
    SEvt::clear_@986: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    [ U4Recorder::EndOfRunAction U4Recorder__EndOfRunAction_Simtrace:N
    ] U4Recorder::EndOfRunAction U4Recorder__EndOfRunAction_Simtrace:N
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 3           50.88600       16.96200     3.96913      
    DetSimAlg                3           6438.51807     2146.17269   185.90667    
    Sum of junotoptask       3           6489.59912     2163.19971   189.88513    
    #############################################################################


::

    jxn
    ./tt.sh 

    ranno
              np.diff(a.rr)[0]/1e6 :    7.058 :  Run 
                      a.ee[-1]/1e6 :    2.129 :  Evt 
                  np.sum(a.ss)/1e6 :    2.026 :  Pho  
             np.sum(a.ss)/a.ee[-1] :    0.951 :  Pho/Evt 

              np.diff(b.rr)[0]/1e6 :    6.490 :  Run 
                      b.ee[-1]/1e6 :    2.114 :  Evt 
                  np.sum(b.ss)/1e6 :    2.003 :  Pho  
             np.sum(b.ss)/b.ee[-1] :    0.947 :  Pho/Evt 




FAKES_SKIP enabled for both (that may explain the lack of N=0/1 difference insitu, as opposed to standalone)::

    In [1]: a.fp.run_meta
    Out[1]: 
    FAKES_SKIP:1
    T_BeginOfRun:1684680817324754
    T_EndOfRun:1684680824382895

    In [2]: b.fp.run_meta
    Out[2]: 
    FAKES_SKIP:1
    T_BeginOfRun:1684681043518810
    T_EndOfRun:1684681050009289




Check SProfile of ProcessHits again
-------------------------------------

::

    In [4]: a.pf.shape
    Out[4]: (15617, 17)

    In [5]: b.pf.shape      
    Out[5]: (18490, 17)    ## more calls to ProcessHits with B(N=1) 


::

    334     def init_junoSD_PMT_v2_SProfile(self, f):
    335         """
    336         The timestamps come from sysrap/stamp.h and are datetime64[us] (UTC) compliant 
    337         """
    338         if hasattr(f, 'junoSD_PMT_v2_SProfile') and not f.junoSD_PMT_v2_SProfile is None:
    339             pf = f.junoSD_PMT_v2_SProfile
    340             pfmx = np.max(pf[:,1:], axis=1 )
    341             pfmi = pf[:,1]
    342             pfr = pfmx - pfmi
    343         else:
    344             pf = None
    345             pfmx = None
    346             pfmi = None
    347             pfr = None
    348         pass
    349         self.pf = pf  ## CAUTION: multiple ProcessHits calls per photon, so not in photon index order 
    350         self.pfmx = pfmx
    351         self.pfmi = pfmi
    352         self.pfr  = pfr 
    353         
    354 


More than 10% of event processing time spent in ProcessHits::

    In [16]: np.sum(a.pfr)/a.ee[-1]
    Out[16]: 0.10450881266649384

    In [17]: np.sum(b.pfr)/b.ee[-1]
    Out[17]: 0.11134881257006096


    In [30]: aa = a.pf[a.pf[:,6]>0,1:]     ## select complete SProfile (ProcessHit calls that close to being hits)  

    In [38]: bb = b.pf[b.pf[:,6]>0,1:]   


    In [35]: aa[:,:6] - aa[:,0,np.newaxis]  ## subtract first timestamp for each ProcessHits call
    Out[35]: 
    array([[   0,  551,  551,  571,  678, 1899],
           [   0,    1,    1,    1,   53,   96],
           [   0,    1,    1,    1,   54,   61],
           [   0,    0,    0,    1,   52,   57],
           [   0,    1,    1,    1,   57,   63],
           [   0,    1,    1,    1,   57,   61],
           [   0,    1,    1,    1,   57,   63],
           [   0,    0,    1,    1,   54,   58],
           [   0,    1,    1,    1,   54,   61],
           [   0,    0,    0,    0,   51,   55],
           [   0,    0,    0,    0,   50,   53],
           [   0,    1,    1,    1,   53,   58],
           [   0,    0,    0,    0,   50,   55],
           [   0,    1,    1,    1,   51,   54],
           [   0,    1,    1,    1,   51,   55],
           [   0,    1,    1,    1,   52,   57],
           ...,
           [   0,    1,    1,    1,   50,   54],
           [   0,    0,    0,    1,   51,   54],
           [   0,    1,    1,    1,   51,   56],
           [   0,    1,    1,    1,   51,   55],
           [   0,    1,    1,    1,   51,   55],
           [   0,    1,    1,    1,   52,   58],
           [   0,    1,    1,    1,   51,   55],
           [   0,    1,    1,    1,   50,   54],
           [   0,    0,    0,    0,   50,   56],
           [   0,    0,    0,    1,   52,   56],
           [   0,    0,    1,    1,   51,   56],
           [   0,    1,    1,    1,   54,   60],
           [   0,    1,    1,    1,   51,   54],
           [   0,    1,    1,    1,   51,   55],
           [   0,    1,    1,    1,   53,   59],
           [   0,    1,    1,    1,   53,   57]], dtype=uint64)
                                 3--->4


    In [39]: bb[:,:6] - bb[:,0,np.newaxis]
    Out[39]: 
    array([[   0,    0,    0,    1,   53, 1192],
           [   0,    0,    0,    1,   54,   99],
           [   0,    1,    1,    1,   54,   64],
           [   0,    1,    1,    1,   53,   59],
           [   0,    1,    1,    1,   53,   61],
           [   0,    1,    1,    1,   52,   57],
           [   0,    0,    0,    0,   53,   60],
           [   0,    1,    1,    1,   52,   56],
           [   0,    1,    1,    1,   53,   60],
           [   0,    0,    1,    1,   53,   58],
           [   0,    1,    1,    1,   53,   59],
           [   0,    1,    1,    1,   52,   56],
           [   0,    1,    1,    1,   53,   60],
           [   0,    1,    1,    1,   55,   60],
           [   0,    1,    1,    1,   53,   60],
           [   0,    1,    1,    1,   52,   59],
           ...,
           [   0,    1,    1,    1,   52,   57],
           [   0,    0,    0,    0,   52,   58],
           [   0,    1,    1,    1,   55,   61],
           [   0,    0,    0,    0,   56,   62],
           [   0,    1,    1,    1,   54,   63],
           [   0,    1,    1,    1,   53,   59],
           [   0,    0,    1,    1,   51,   56],
           [   0,    0,    0,    0,   57,   64],
           [   0,    1,    1,    1,   53,   58],
           [   0,    1,    1,    1,   53,   58],
           [   0,    0,    0,    0,   51,   56],
           [   0,    0,    0,    0,   52,   57],
           [   0,    1,    1,    1,   52,   57],
           [   0,    1,    1,    1,   52,   58],
           [   0,    0,    1,    1,   53,   60],
           [   0,    0,    1,    1,   54,   60]], dtype=uint64)




::

     499 #ifdef WITH_G4CXOPTICKS
     500     m_profile->stamp(1);
     501 #endif
     502 
     503     const G4VTouchable* touch = track->GetTouchable();
     504     int pmtID_1 = touch->GetReplicaNumber(1) ;
     505     if(pmtID_1 <= 0) pmtID_1 = touch->GetReplicaNumber(2) ;
     506 
     507 #ifdef WITH_G4CXOPTICKS
     508     m_profile->stamp(2);
     509 #endif
     510 
     511 #ifdef WITH_G4CXOPTICKS
     512     int pmtID_2 = U4Touchable::AncestorReplicaNumber(touch) ;
     513 #endif
     514 
     515 #ifdef WITH_G4CXOPTICKS
     516     m_profile->stamp(3);
     517 #endif
     518 
     519     int pmtID = get_pmtid(track);   // takes ~50us (totals > 10% of event time) 
     520 
     521 #ifdef WITH_G4CXOPTICKS
     522     m_profile->stamp(4);
     523 #endif



TODO : Comparison with the faster get_pmtid
-----------------------------------------------

TODO : write this into a new issue
--------------------------------------


