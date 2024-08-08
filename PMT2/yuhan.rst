


Hi Simon,

Here is my consideration.

The motivation of the two implementation is to model non-uniform photocathode
properties with backward QE contributions.
If done, QE calculation based on thicknesss will depend on the photon hit point
at PMT and at which PMT, and especially, if a transmitted photon is absorbed at
another point (backward QE) different from its primary incident point
(frontward QE), the thickness input will be different.

1. ARC and photocathode thickness vs theta

I mean each PMT has its own thickness(theta) curve, and I have put all these
parameters in a ROOT file. In junosw, I think getting thickness will be similar
to service functions of other data, such as get_PDE to get PDE, and it's not a
problem.  However, I'm not quite sure if you disable all calculations in
junoPMTOpticalModel.cc, so thickness access and all related ART calculations
are actually implemented in custom4.

2. non-zero backward QE

If non-zero backward QE is calculated, CE will be updated as well. I think, to
some extend, the change of CE will compensate for the change of total QE caused
by counting backward photons, and guarantee PDE keeps unchanged, which is
important.  The procedure of getting new CE can be found in Docdb-9330
https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/ShowDocument?docid=9330, page 11. And
after applying the method to all PMTs, currently, each PMT has its own CE curve
corresponding to its ARC and photocathode thickness.
As for junosw update, I understand the implementation of CE. But for non-zero
backward QE, I also wonder if this should be done in custom4.

It would be better to meet. 
And, yeah, I'm at IHEP now. Both Friday and next Monday are OK for me.

Best,
Yuhan






https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/ShowDocument?docid=9330


std::array<double,3> 

Hi Yuhan, 

> The motivation of the two implementation is to model non-uniform photocathode
> properties with backward QE contributions.

You need to think up some good descriptive names for 
the different implementations.  

> If done, QE calculation based on thicknesss will depend on the photon hit point
> at PMT and at which PMT, 

Do you really mean which PMT. Or just which type of PMT ? 
Currently the thicknesses and refractive indices depend
only on the category of PMT "pmtcat" and energy. 

Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h::

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


> and especially, if a transmitted photon is absorbed at
> another point (backward QE) different from its primary incident point
> (frontward QE), the thickness input will be different.

The accessor is called whenever the photon reaches the boundary of the 
upper hemisphere of the PMT.  When the lower hemisphere is reached 
an equivalent of the Geant4 standard reflection happens, so the accessor
is not called. 

Square PMT for ease of drawing::
 


                             0
                                

          +------------1--------------+
          |                           |
          |                           |
          |                           |
          2                           |
          |                           |
          |                           |
          |                           |
          +- - - - - - - - - - - - - -+
          |                           |
          |                           |
          |                           |
          |                           |
          |                           |
          |                           |
          |                           |
          +---------------------------+
         



>
>
> 1. ARC and photocathode thickness vs theta
>
> I mean each PMT has its own thickness(theta) curve, and I have put all these
> parameters in a ROOT file. 

For ease of standalone testing and use from GPU it will be necessary to 
convert the data from the ROOT file into a NumPy array. 
Please point to your code that uses the data.  

When me meet you can explain to me the content of the ROOT file, 
and I can suggest how best to convert it. 


> In junosw, I think getting thickness will be similar
> to service functions of other data, such as get_PDE to get PDE, and it's not a
> problem.  

Where do you propose to add this ?  The PMTAccessor.h gets its data from 
PMTSimParamData which in turn is populated by the PMTSimParamSvc. 

In order to work with standalone testing and GPU running you need to 
arrange the data access in a specific way. 

Essentially you do high level things like reading ROOT files 
in the PMTSimParamSvc. The Svc copies all the needed data into low
level structs/vectors/maps etc.. that can be serialized::

     47 struct PMTSimParamData
     48 {
     49     const char*                    loaddir ;
     50     std::vector<int>               m_all_pmtID;
     51     std::vector<double>            m_all_pmtID_qe_scale ;
     52     std::unordered_map<int, int>   m_map_pmt_category ; // NB not all, only LPMT
     53     std::unordered_map<int, int>   m_all_pmt_category ;
     54     std::vector<int>               m_all_pmt_catvec ;
     55 
     56     int                            m_PmtTotal_SPMT ;
     57     std::unordered_map<int, PmtSimData_SPMT> pd_map_SPMT;
     58 
     59     int                            m_PmtTotal ;  // _LPMT
     60     std::vector<PmtSimData_LPMT>   pd_vector;
     61 
     62     int                            m_PmtTotal_ALL ;
     63     int                            m_PmtTotal_WP ;
     64 
     65 
     66 
     67     G4MaterialPropertyVector* m_QEshape_HZC;
     68     G4MaterialPropertyVector* m_QEshape_NNVT;
     69     G4MaterialPropertyVector* m_QEshape_NNVT_HiQE;
     70     G4MaterialPropertyVector* m_QEshape_R12860;
     71     G4MaterialPropertyVector* m_QEshape_WP_PMT;
     72 
      
Low level in this context means the PMTSimParamData does NOT depend on:

* ROOT 
* JUNOSW structs/classes (unless they are simple data holders like PmtSimData_SPMT PmtSimData_LPMT)

Keeping this data holding PMTSimParamData struct low level 
and low dependency is what enables:

0. persisting the data into standard NumPy files 
1. standalone testing external to JUNOSW
2. uploading the data to the GPU
2. access to precisely the same data on GPU as on CPU 



> However, I'm not quite sure if you disable all calculations in
> junoPMTOpticalModel.cc, so thickness access and all related ART calculations
> are actually implemented in custom4.

junoPMTOpticalModel.cc is no longer used, other than if your use specific
options to re-enable it with all its bugs. 

Custom4 does the ART calculation, but it gets all information on the PMTs
via the C4IPMTAccessor protocol implemented in JUNOSW by PMTAccessor.h

Your proposal will require an addition to the protocol within custom4, 
but most of the change will be within JUNOSW::  

    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h

    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h    
    Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData.cc

    Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc
    Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h




> 2. non-zero backward QE
>
> If non-zero backward QE is calculated, CE will be updated as well. I think, to
> some extend, the change of CE will compensate for the change of total QE caused
> by counting backward photons, and guarantee PDE keeps unchanged, which is
> important.  The procedure of getting new CE can be found in Docdb-9330
> https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/ShowDocument?docid=9330, page 11. And
> after applying the method to all PMTs, currently, each PMT has its own CE curve
> corresponding to its ARC and photocathode thickness.
>
> As for junosw update, I understand the implementation of CE. But for non-zero
> backward QE, I also wonder if this should be done in custom4.
>

Yes,  this needs to be changed in C4CustomART::doIt, also a way of configuring 
the different approaches will need to be communicated to C4CustomART via
adding a method to the C4IPMTAccessor protocol to pick between 
different choices of implementation. 


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
    313     const double* ss = a_spec.data() ;
    314 
    315     Stack<double,4> stack ;
    316 
    317     theEfficiency = zero ;
    318     if( minus_cos_theta < zero ) // only ingoing photons 
    319     {
    320         stack.calc( wavelength_nm, minus_one, zero, ss, 16u );
    321         theEfficiency = _qe/stack.art.A ;    // aka escape_fac
    322 
    323         bool expect = theEfficiency <= 1. ;
    324         if(!expect) std::cerr
    325             << "C4CustomART::doIt"
    326             << " FATAL "
    327             << " ERR: theEfficiency > 1. : " << theEfficiency
    328             << " _qe " << _qe
    329             << " stack.art.A (aka An) " << stack.art.A
    330             << std::endl
    331             ;
    332         assert( expect );
    333     }



> It would be better to meet. 
> And, yeah, I'm at IHEP now. Both Friday and next Monday are OK for me.

I expect to be in office 515 Multi-disciplinary building for most of Friday.
Visiting after 10am would give me some time to review the Custom4 and JUNOSW
code a little.  

Simon

PS find below a few notes on Custom4







Custom4 Explained 
------------------

MOVED EXPLANATION INTO C4 REPO



