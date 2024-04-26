MR405_POM_veto_PMT
====================

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/405


Q: Does the PMTAccessor provide all the WP PMT data needed by C4CustomART ?
A: As shown below, it looks like it does.



::

    371 #include "IPMTSimParamSvc/IPMTSimParamSvc.h"
    372 #include "PMTSimParamSvc/PMTSimParamData.h"
    373 #include "PMTSimParamSvc/PMTAccessor.h"
    374 
    375 C4OpBoundaryProcess* DsPhysConsOptical::CreateCustomG4OpBoundaryProcess()
    376 {
    377     SniperPtr<IPMTSimParamSvc> psps_ptr(*getParent(), "PMTSimParamSvc");
    378 
    379     if(psps_ptr.invalid())
    380     {
    381         std::cout << "invalid" << std::endl ;
    382         return nullptr ;
    383     }
    384 
    385     IPMTSimParamSvc* ipsps = psps_ptr.data();
    386     PMTSimParamData* pspd = ipsps->getPMTSimParamData() ;
    387 
    388     C4IPMTAccessor* accessor = new PMTAccessor(pspd) ;
    389     C4OpBoundaryProcess* boundproc = new C4OpBoundaryProcess(accessor) ;
    390     std::cout << "DsPhysConsOptical::CreateCustomG4OpBoundaryProcess" << std::endl ;
    391 
    392     return boundproc ;
    393 }



::

    293 inline void C4CustomART::doIt(const G4Track& aTrack, const G4Step& )
    294 {
    295     G4double zero = 0. ;
    296     G4double minus_one = -1. ;
    297     G4double minus_cos_theta = OldMomentum*theRecoveredNormal ;
    298     G4double dot_pol_cross_mom_nrm = OldPolarization*OldMomentum.cross(theRecoveredNormal) ;
    299 
    300     G4double energy = thePhotonMomentum ;
    301     G4double wavelength = CLHEP::twopi*CLHEP::hbarc/energy ;
    302     G4double energy_eV = energy/CLHEP::eV ;
    303     G4double wavelength_nm = wavelength/CLHEP::nm ;
    304 
    305     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );
    306     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    307     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;  // energy_eV ?
    308     // following the old junoPMTOpticalModel with "backwards" _qe always zero 
    309 
    310     std::array<double,16> a_spec ;
    311     accessor->get_stackspec(a_spec, pmtcat, energy_eV );
    312 


    003 #include <array>
      4 
      5 struct C4IPMTAccessor
      6 {
      7     virtual int    get_num_lpmt() const = 0 ;
      8     virtual double get_pmtid_qe( int pmtid, double energy ) const = 0 ;
      9     virtual double get_qescale( int pmtid ) const = 0 ;
     10     virtual int    get_pmtcat( int pmtid  ) const = 0 ;
     11     virtual void   get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const = 0 ;
     12     virtual const char* get_typename() const = 0 ;
     13 
     14 };



PMTAccessor just passthru to PMTSimParamData::

    206 inline int PMTAccessor::get_num_lpmt() const
    207 {
    208     return data->get_num_lpmt() ;
    209 }
    210 inline double PMTAccessor::get_pmtid_qe( int pmtid, double energy ) const
    211 {
    212     return data->get_pmtid_qe(pmtid, energy) ;
    213 }




    214 inline double PMTAccessor::get_qescale( int pmtid ) const
    215 {
    216     return data->get_qescale(pmtid) ;
    217 }
    218 
    219 inline int PMTAccessor::get_pmtcat( int pmtid  ) const
    220 {
    221     return data->get_pmtcat(pmtid) ;
    222 }
    223 inline void PMTAccessor::get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const
    224 {
    225     double energy = energy_eV*CLHEP::eV ;
    226 
    227     ss.fill(0.);
    228 
    229     ss[4*0+0] = PyrexRINDEX ? PyrexRINDEX->Value(energy) : 0. ;
    230 
    231     ss[4*1+0] = data->get_pmtcat_prop(       pmtcat, "ARC_RINDEX" , energy );
    232     ss[4*1+1] = data->get_pmtcat_prop(       pmtcat, "ARC_KINDEX" , energy );
    233     ss[4*1+2] = data->get_pmtcat_const_prop( pmtcat, "ARC_THICKNESS" )/CLHEP::nm ;
    234 
    235     ss[4*2+0] = data->get_pmtcat_prop(       pmtcat, "PHC_RINDEX" , energy );
    236     ss[4*2+1] = data->get_pmtcat_prop(       pmtcat, "PHC_KINDEX" , energy );
    237     ss[4*2+2] = data->get_pmtcat_const_prop( pmtcat, "PHC_THICKNESS" )/CLHEP::nm ;
    238 
    239     ss[4*3+0] = VacuumRINDEX ? VacuumRINDEX->Value(energy) : 1. ;
    240 }




::

    217 inline double PMTSimParamData::get_pmtid_qe(int pmtid, double energy) const
    218 {
    219     int idx = get_pmtContiguousIndex(pmtid) ;
    220     int cat = m_all_pmt_catvec[idx] ;
    221     double qe = get_pmtcat_qe(cat, energy);
    222     double qe_scale = m_all_pmtID_qe_scale[idx] ;
    223     qe *= qe_scale ;
    224     assert(qe > 0 && qe < 1);
    225     return qe ;
    226 }
    227 
    228 inline double PMTSimParamData::get_pmtcat_qe(int cat, double energy) const
    229 {
    230     G4MaterialPropertyVector* vec = get_pmtcat_qe_vs_energy(cat);
    231     double qe = vec->Value(energy);
    232     return qe;
    233 }
    234 
    235 inline double PMTSimParamData::get_qescale(int pmtid) const
    236 {
    237     int idx = get_pmtContiguousIndex(pmtid) ;
    238     return m_all_pmtID_qe_scale[idx] ;
    239 }


    248 /**
    249 PMTSimParamData::get_pmtContiguousIndex
    250 ---------------------------------------
    251 
    252 ::
    253 
    254     pmtid
    255     |
    256     |                          SPMT 
    257     |
    258     + kOFFSET_CD_SPMT=300000
    259     |
    260     |                          WPMT    
    261     |
    262     + kOFFSET_WP_PMT=30000
    263     |  
    264     |                          LPMT 
    265     |
    266     + kOFFSET_CD_LPMT=0 
    267 
    268 
    269 **/
    270 inline int PMTSimParamData::get_pmtContiguousIndex(int pmtid) const
    271 {
    272     int idx = -1 ;
    273     if(PMT::IsCD(pmtid) and PMT::Is20inch(pmtid)) {
    274         idx = pmtid ;    // LPMT 
    275     } else if(PMT::IsWP(pmtid)) {
    276         idx = pmtid - kOFFSET_WP_PMT  + m_PmtTotal ;  // WPMT 
    277     } else if (PMT::IsCD(pmtid) and PMT::Is3inch(pmtid)){
    278         idx = pmtid - kOFFSET_CD_SPMT + m_PmtTotal + m_PmtTotal_WP ;  // SPMT  
    279     }
    280 
    281     return idx ; 
    282 }

