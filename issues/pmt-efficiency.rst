> Recently I have finished some updates as follows:
> 
> 1. I think we should keep the PMTType Name the same between PMTSimParamSvc and
> PMTParamSvc, so currently I modified codes in PMTSimParamSvc.
> 
> I noticed you have used the type name I defined before in PMTEfficiency. Maybe
> you could also change them as the definition in PMTParamSvc. Then we can remove
> my definition in IPMTSimParamSvc.

In summary I hope that when you are finished with PMTSimParamSvc it 
will be possible for me to delete the PMTEfficiency class 
and the below methods that I added::

   junoSD_PMT_v2::getCollectionEfficiency
   junoSD_PMT_v2::getEfficiencyScale
   junoSD_PMT_v2::getDetectionEfficiency
   junoSD_PMT_v2::getQuantumEfficiency

Let me give some background about what Opticks needs with regard to 
PMT efficiencies.  

During detector construction G4Opticks is initialized and 
the efficiencies of all PMTs and angular efficiencies
of the PMT categories are intended to be passed to it within 

Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc

In order to collect all the efficiencies I added some methods to junoSD_PMT_v2 namely::

     947 double junoSD_PMT_v2::getCollectionEfficiency(double theta, int pmtID) const
     948 {
     949     int simcat = pmtID<18000 ? m_PMTSimParsvc->getPMTCategory(pmtID) : -1 ;
     950     assert(PMTEfficiency::GetPMTCategoryType() == 'S');
     951     return m_PMTEfficiency->getEfficiency(theta, simcat) ;
     952 }
     953 
     954 double junoSD_PMT_v2::getEfficiencyScale() const
     955 {
     956     return m_angle_response ;
     957 }
     958 
     959 double junoSD_PMT_v2::getDetectionEfficiency(double theta, int pmtID) const
     960 {
     961     double qe = getQuantumEfficiency(pmtID);
     962     double ce = getCollectionEfficiency(theta, pmtID);
     963     double es = getEfficiencyScale();
     964     double de = qe*ce*es;
     965     return de ;
     966 }
     967
     892 double junoSD_PMT_v2::getQuantumEfficiency(int pmtID) const
     893 {
     894     double eff_pde = 1.;
     895     double qe_calc = 1.;
     896     double qescale = m_qescale ;
     897 
     898     if(pmtID<18000)
     899     {
     900         qescale = m_enable_optical_model ? m_qescale_optical_model : m_qescale ;
     901 
     902         eff_pde = m_PMTSimParsvc->get_pde(pmtID);
     903         if( m_PMTSimParsvc->isHamamatsu(pmtID))
     904         {
     905             qe_calc = eff_pde / eff_ce_Hamamatsu;
     906         }
     907         else if ( m_PMTSimParsvc->isHiQENNVT(pmtID) )
     908         {
     909             qe_calc = eff_pde / eff_ce_NNVT_HiQE;
     910         }
     911         else if ( m_PMTSimParsvc->isNormalNNVT(pmtID) )
     912         {
     913             qe_calc = eff_pde / eff_ce_NNVT_Normal;
     914         }
     915     }
     916     else if(pmtID<300000)
     917     {
     918         qe_calc = 0.3;
     919     }
     920     else if(pmtID>=300000)
     921     {
     922         qe_calc = m_PMTParamsvc->getPMTQE(pmtID);
     923     }
     924     return qescale*qe_calc ;
     925 }
     926 


I also added the PMTEfficiency class with duplicates 
the angular efficienciens copied from junoSD_PMT_v2::ProcessHits

These methods all duplicate other code because the code (mainly in junoSD_PMT_v2::ProcessHits)
is not arranged into methods.  

Clearly it would be better if all these methods could be provided by 
your PMT info service.  Then these methods can be removed from junoSD_PMT_v2
and junoSD_PMT_v2::ProcessHits could then be greatly simplified by using 
these methods from the service.  

Similarly it should be possible to also delete the PMTEfficiency  class
if the service can also provide a method something like the below.::


    double PMTSimParamSvc::get_pmt_ce(double theta, int pmt_cat)
    {
        TGraph* gCE = nullptr ; 
        switch(pmt_cat)
        {   
            case kPMTType_Unknown:              gCE = nullptr          ; break ;
            case kPMTType_Hamamatsu:            gCE = gCE_R12860       ; break ;
            case kPMTType_HiQENNVT:             gCE = gCE_NNVTMCP_HiQE ; break ;
            case kPMTType_NormalNNVT:           gCE = gCE_NNVTMCP      ; break ;
            case kPMTType_HZC:                  gCE = nullptr          ; break ;
            //case kPMTType_Dynode:               gCE = gCE_Dynode       ; break ;
            //case kPMTType_MCP:                  gCE = gCE_MCP          ; break ;
        }   
        return gCE ? gCE->Eval(theta, 0, "S") : 1. ;
    }


Using the PMT category integer like this can also avoid 
doing volname string comparisons for every photon hit.

Regarding gCE_Dynode gCE_MCP. Are some more PMT categories needed ?

> 2. I have implemented get_pmt_ce in PMTSimParamSvc. Maybe you could check
> these updates, because I think you used this function somewhere. Then I think
> we could invoke this function instead of codes in junoSD.

Checking all unique volume names contaning PMT in them 
I notice that there is no "PMT_20inch_body_phys" in the current geometry::

    O[blyth@localhost GNodeLib]$ cat all_volume_PVNames.txt | sort | uniq | grep PMT
    HamamatsuR12860_PMT_20inch_body_phys
    HamamatsuR12860_PMT_20inch_inner1_phys
    HamamatsuR12860_PMT_20inch_inner2_phys
    HamamatsuR12860_PMT_20inch_log_phys
    mask_PMT_20inch_vetolMaskVirtual_phys
    mask_PMT_20inch_vetopMask
    NNVTMCPPMTpMask
    NNVTMCPPMT_PMT_20inch_body_phys
    NNVTMCPPMT_PMT_20inch_inner1_phys
    NNVTMCPPMT_PMT_20inch_inner2_phys
    NNVTMCPPMT_PMT_20inch_log_phys
    pLPMT_Hamamatsu_R12860
    pLPMT_NNVT_MCPPMT
    PMT_20inch_veto_body_phys
    PMT_20inch_veto_inner1_phys
    PMT_20inch_veto_inner2_phys
    PMT_20inch_veto_log_phys
    PMT_3inch_body_phys
    PMT_3inch_cntr_phys
    PMT_3inch_inner1_phys
    PMT_3inch_inner2_phys
    PMT_3inch_log_phys

So the branch that uses gCE_Dynode gCE_MCP will never happen::

    867     } else if (m_ce_mode == "20inch") {
    868         if (volname == "PMT_20inch_body_phys") {
    869             if (pmt_type) {
    870                 ce_cat = 2;
    871                 return gCE_Dynode->Eval(theta);
    872             } else {
    873                 ce_cat = 3;
    874                 return gCE_MCP->Eval(theta);
    875             }
    876         }


> 3. Cerenkov process has a litter correction. 
>  Maybe you can test it on opticks and give me some feedbacks.


For Opticks to use a Cerenkov process it is currently necessary to modify 
the process to do genstep collection. It is a straightforward change 
that I can do to your modified Cerenkov once you have made the changes that will allow
me to delete PMTEfficiency and the other methods. :-)

Do you have a standalone program that tests your modified Cerenkov and 
compares it with the Geant4 standard one ?  

To incorporate your change into future Geant4 releases it is 
necessary to provide such a standalone test.

I recently added something related to this in the Opticks repository 
which might be of interest to you.

   https://bitbucket.org/simoncblyth/opticks/src/master/examples/Geant4/CerenkovMinimal/src/L4CerenkovTest.cc
   https://bitbucket.org/simoncblyth/opticks/src/master/examples/Geant4/CerenkovMinimal/src/L4CerenkovTest.py
   https://bitbucket.org/simoncblyth/opticks/src/master/examples/Geant4/CerenkovMinimal/src/L4CerenkovTest.sh

The test is rather standalone : it does not need an Opticks install, just depending 
on geant4, clhep and my NP.hh header from https://github.com/simoncblyth/np/ and 
python, NumPy and matplotlib for the plotting
The python plots MeanNumberOfPhotons against BetaInverse.


Simon

