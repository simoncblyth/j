PMTSimParSvc
==============

Hi Yuxiang, 

Thank you for the explanation.  
I can see the advantage of handling the efficiency all in one place.
 
To bring per-PMT QE and CE to the GPU will require use of some big 2D textures
Fortunately even ancient GPUs like my laptops are able to handle 2D texture dimensions 
sufficient for the ~45,612 JUNO sensors

 675      GGeo::getSensorBoundaryReport()
 676      boundary  30 b+1  31 sensor_count  12612 Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_logsurf2/NNVTMCPPMT_PMT_20inch_photocathode_logsurf1/Vacuum
 677      boundary  33 b+1  34 sensor_count   5000 Pyrex/HamamatsuR12860_PMT_20inch_photocathode_logsurf2/HamamatsuR12860_PMT_20inch_photocathode_logsurf1/Vacuum
 678      boundary  35 b+1  36 sensor_count  25600 Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum
 679      boundary  40 b+1  41 sensor_count   2400 Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum
 680                           sensor_total  45612


TITAN RTX/V  : Maximum Texture Dimension Size (x,y,z)         1D=(131072), 2D=(*131072*, 65536), 3D=(16384, 16384, 16384)
Geforce 750M : Maximum Texture Dimension Size (x,y,z)         1D=(65536), 2D=(*65536*, 65536), 3D=(4096, 4096, 4096) 



With the textures, the below code:
 
 457      if(m_use_pmtsimsvc){
 458         qe = m_enable_optical_model ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);
 459         ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());
 461      }

Can be replaced via texture lookups using 2D QE and CE textures:

    2D QE texture (pmtContiguousIndex, edep)
    2D CE texture (pmtContiguousIndex, theta) 

Where pmtContiguousIndex can be obtained from pmtID knowing the ranges of pmtIDs.  

To enable Opticks to build textures it is necessary  
to add some additional methods to PMTSimParSvc::

     void     get_all_pmtID(std::vector<int>& pmtIDs ) const ; 
     int      get_pmtContiguousIndex( int pmtID ) const ; 
     int      get_pmtId_from_contiguousIndex( int pmtContiguousIndex ) const ;   

The pmtContiguousIndex does not need to be totally contiguous but the 
gaps between the sequences of Idx for different LPMT/veto/SPMT categories 
should not be large because there is a texture dimension limit of 65,536

Example (uncompiled and untested) guess implementations are below, 
the real implementation will require some experimentation using the actual 
pmtID to check can convert both ways and avoid overlapping of contiguousIdx 
between types of PMTs.


int get_pmtContiguousIndex(int pmtID ) const
{
    int contiguousIdx = -1 ;
    if(pmtID<18000)           //  0:18000 for LPMT 
    {
        contiguousIdx = pmtID ;
    }
    else if( pmtID<300000 )    //  18000:22000  for vetoPMT   (space for 4000)  
    {
        contiguousIdx = 18000 + pmtID - vetoPMTidStart  ;  // hmm do not know where veto pmtID start
    }
    else if(pmtID>=300000)     //  22000:47600   for SPMT     (nominally 25600, but with headroom for more)
    {
        contiguousIdx = 18000 + 4000 + pmtID - 300000 ;
    }

    assert( contiguousIdx > -1 && contiguousIdx < 65536); 

    int pmtID_check = get_pmtId_from_contiguousIndex( contiguousIdx ); 
    assert(  pmtID_check == pmtID ); 

    return contiguousIdx ;
}

int get_pmtId_from_contiguousIndex( int contiguousIdx ) const 
{
     int pmtId = -1 ; 
     if( contiguousIdx < 18000 )
     {
          pmtId = contiguousIdx ; 
     }
     else if( contiguousIdx < 18000 + 4000 )
     {
          pmtId = contiguousIdx - 18000 + vetoPMTidStart  ; 
     }
     else if( contiguousIdx < 18000 + 4000 + 25600 )
     {
          pmtId = contiguousIdx - ( 18000 + 4000 ) + 3000000 ; 
     }

     int contiguousIdx_check = get_pmtContiguousIndex( pmtId ); 
     assert( contiguousIdx_check == contiguousIdx ); 

     return pmtId ; 
}


Using the above API will then allow to add another method that 
collects all the QE data into a vector. 
This data can then be copied into a GPU float texture.   

// below is untested scratch code to illustrate how to collect 
// QE data for all PMTs

void getQEData(std::vector<double>& qe_data, double en0, double en1, unsigned num_edep  ) const 
{
    std::vector<int> all_pmtIDs ; 
    get_all_pmtID( all_pmtIDs );  
    std::sort( all_pmtIDs.begin(), all_pmtIDs.end() );  

    int pmtId_first = all_pmtIDs.front() ; 
    int pmtId_last  = all_pmtIDs.back() ; 
    assert( pmtId_first == 0 );  
                
    int idx_first = get_pmtContiguousIndex(pmtId_first) ; 
    int idx_last  = get_pmtContiguousIndex(pmtId_last) ;     
    int num_idx = idx_last - idx_first + 1 ; 

    assert( idx_first == 0 ) ; 
    assert( num_idx == all_pmtIDs.size() );  

    qe_data.clear();
    qe_data.resize( num_idx*num_edep );  
 
    double* qe_data_ = qe_data.data() ;   

    for(unsigned i=0 ; i < all_pmtIDs.size() ; i++ )
    {   
       int pmtId = all_pmtIDs[i] ; 
       int pmtContiguousIdx = get_pmtContiguousIndex(pmtId) ;   

       for(unsigned j=0 ; j < num_edep ; j++)
       {   
           double efrac = double(j)/double(num_edep) ; 
           double edep = en0 + (en1 - en0)*efrac ; 
           double qe = get_pmtid_qe(pmtID,edep);

           qe_data_[ pmtContiguousIdx*num_edep + j ] = qe ;    
       }   
    }   
}



The translation from pmtId to pmtContiguousIdx will 
have to be used elsewhere so that all Opticks references to PMTs 
use the contiguous index rather than the ordinary pmtID.  
This way the GPU will have access to the energy dependent QE.

A similar method can be used to collect the theta dependent CE data.

void getCEData(std::vector<double>& ce_data, double th0, double th1, unsigned num_theta  ) const 

2. Then I need to clear about some details of my va

lidation of QE in order to answer your question about my QE validation result.

I check QE and CE just in my local Offline sorfware and my trunk of local Offline is the latest version. In order to prove the equivalence of the two implementation which shows above, we modify some QE data type to make sure the data of two implementation is the same.

[10:29:05][localhost.localdomain]~/2020-3-17/trunk/offline % svn info
Path: .
Working Copy Root Path: /home/ihep/2020-3-17/trunk/offline
URL: https://juno.ihep.ac.cn/svn/offline/trunk
Repository Root: https://juno.ihep.ac.cn/svn/offline
Repository UUID: aa2a40f7-5b9f-4796-82c0-4247cb6b7b64
Revision: 5113
Node Kind: directory
Schedule: normal
Last Changed Author: lintao
Last Changed Rev: 5113
Last Changed Date: 2021-10-29 23:52:59 +0800 (Fri, 29 Oct 2021)

  else if (volname == "HamamatsuR12860_PMT_20inch_body_phys") {
 732             double theta = localpos.theta();
 733 
 734             double s_theta_hamamatsu[] = {
 735                 0.*deg, 13.*deg, 28.*deg, 41.*deg, 55.*deg, 66.*deg,
 736                 79.*deg, 85.*deg, 90.*deg,
 737             };
 738             double s_ce_hamamatsu[] =    {
 739                 0.911,    0.911,    0.9222,     0.9294,     0.9235,     0.93,
 740                 0.9095, 0.6261, 0.2733,
 741             };
 742             G4MaterialPropertyVector s_di(s_theta_hamamatsu,s_ce_hamamatsu,9);
 743             //static G4DataInterpolation s_di(s_theta_hamamatsu, s_ce_hamamatsu, 9, 0., 0.);  
 744             ce_cat = 4 ;
 745             s_di.SetSpline(false);
 746             //ce = ->Value(theta) 
 747             return s_di.Value(theta);
 748         }
 749 
 750 
 751         else if (volname == "NNVTMCPPMT_PMT_20inch_body_phys") {
 752             // calculate the angle theta
 753             double theta = localpos.theta();
 754             // do interpolate
 755             double s_theta_NNVT[] = {
 756                 0.*deg, 14.*deg, 30.*deg, 42.5*deg, 55.*deg, 67.*deg,
 757                 77.5*deg, 85.*deg, 90.*deg,
 758             };
 759             double s_ce_NNVT[] =    {
 760                 1.0,    1.0,    0.9453,     0.9105,     0.8931,     0.9255,
 761                 0.9274,     0.8841,     0.734,  
 762             };  
 763             double s_ce_NNVT_highQE[] = {
 764                1.0,     1.0,    0.9772,     0.9723,     0.9699,     0.9697,
 765                0.9452,  0.9103,     0.734,      
 766             };  
 767             
 768             if(!pmt_type && !qe_type){
 769                 //static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT, 9, 0., 0.);
 770                 G4MaterialPropertyVector  s_di(s_theta_NNVT,s_ce_NNVT,9);
 771                 ce_cat = 5 ; 
 772                 s_di.SetSpline(false);
 773                 return s_di.Value(theta);
 774             }
 775             else if(!pmt_type && qe_type) {
 776                 //static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT_highQE, 9, 0., 0.);
 777                 G4MaterialPropertyVector  s_di(s_theta_NNVT,s_ce_NNVT_highQE,9);
 778                 ce_cat = 6 ; 
 779                 s_di.SetSpline(false);
 780                 return s_di.Value(theta);
 781             }
 782             ce_cat = 7 ;  
 783         }       
then I modify the G4OpBoundaryProcess. I just design the API which get the efficiecy in order to know about the efficiency value which G4OpBoudaryProcess used and I didn't modify other code of G4OpBoundaryProcess . I don't understand why it is problematic like you said.



When I do the QE compare, I run the script like the following: 

#!/bin/bash

python $TUTORIALROOT/share/tut_detsim.py --no-use-pmtsimsvc --disable-pmt-optical-model  --output det_sample.root --user-output det_sample_user.root --evtmax 1 gun --positions 0 0 0 --particles gamma --momentums 30000.0 --directions 0 0 -1
I use the argument  --no-use-pmtsimsvc  so that Efficiency actually be register to the PMT volume and the Boundary Process can get the Efficiency. Thus the efficiency is not 1 !! and then in my validation code in junoSD_PMT_v2::ProcessHit.cc, I directly use PMTSimSvc which now is not under the control of *m_use_pmtsimsvc*.

thus

 int debug = 1 ;  
    if(debug){
      std::cout<<"   pmtid   =  "<< pmtID
               << "  theta   = " <<  local_pos.theta()
               <<"   pmtcat  = "<< m_PMTParamsvc->getPMTCategory(pmtID)
               <<"   volname = " << volname << std::endl ;
      double epsilon = 1e-10;
      double qe_0= qe * (boundary_proc->GetTheEff());

thus the qe_0 is not same as qe since in my run.sh script which shows above the efficiency is registered. These code are just in my local trunk of Offline.

See More
2. Then I need to clear about some details of my va

lidation of QE in order to answer your question about my QE validation result.

I check QE and CE just in my local Offline sorfware and my trunk of local Offline is the latest version. In order to prove the equivalence of the two implementation which shows above, we modify some QE data type to make sure the data of two implementation is the same.

[10:29:05][localhost.localdomain]~/2020-3-17/trunk/offline % svn info
Path: .
Working Copy Root Path: /home/ihep/2020-3-17/trunk/offline
URL: https://juno.ihep.ac.cn/svn/offline/trunk
Repository Root: https://juno.ihep.ac.cn/svn/offline
Repository UUID: aa2a40f7-5b9f-4796-82c0-4247cb6b7b64
Revision: 5113
Node Kind: directory
Schedule: normal
Last Changed Author: lintao
Last Changed Rev: 5113
Last Changed Date: 2021-10-29 23:52:59 +0800 (Fri, 29 Oct 2021)

  else if (volname == "HamamatsuR12860_PMT_20inch_body_phys") {
 732             double theta = localpos.theta();
 733 
 734             double s_theta_hamamatsu[] = {
 735                 0.*deg, 13.*deg, 28.*deg, 41.*deg, 55.*deg, 66.*deg,
 736                 79.*deg, 85.*deg, 90.*deg,
 737             };
 738             double s_ce_hamamatsu[] =    {
 739                 0.911,    0.911,    0.9222,     0.9294,     0.9235,     0.93,
 740                 0.9095, 0.6261, 0.2733,
 741             };
 742             G4MaterialPropertyVector s_di(s_theta_hamamatsu,s_ce_hamamatsu,9);
 743             //static G4DataInterpolation s_di(s_theta_hamamatsu, s_ce_hamamatsu, 9, 0., 0.);  
 744             ce_cat = 4 ;
 745             s_di.SetSpline(false);
 746             //ce = ->Value(theta) 
 747             return s_di.Value(theta);
 748         }
 749 
 750 
 751         else if (volname == "NNVTMCPPMT_PMT_20inch_body_phys") {
 752             // calculate the angle theta
 753             double theta = localpos.theta();
 754             // do interpolate
 755             double s_theta_NNVT[] = {
 756                 0.*deg, 14.*deg, 30.*deg, 42.5*deg, 55.*deg, 67.*deg,
 757                 77.5*deg, 85.*deg, 90.*deg,
 758             };
 759             double s_ce_NNVT[] =    {
 760                 1.0,    1.0,    0.9453,     0.9105,     0.8931,     0.9255,
 761                 0.9274,     0.8841,     0.734,  
 762             };  
 763             double s_ce_NNVT_highQE[] = {
 764                1.0,     1.0,    0.9772,     0.9723,     0.9699,     0.9697,
 765                0.9452,  0.9103,     0.734,      
 766             };  
 767             
 768             if(!pmt_type && !qe_type){
 769                 //static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT, 9, 0., 0.);
 770                 G4MaterialPropertyVector  s_di(s_theta_NNVT,s_ce_NNVT,9);
 771                 ce_cat = 5 ; 
 772                 s_di.SetSpline(false);
 773                 return s_di.Value(theta);
 774             }
 775             else if(!pmt_type && qe_type) {
 776                 //static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT_highQE, 9, 0., 0.);
 777                 G4MaterialPropertyVector  s_di(s_theta_NNVT,s_ce_NNVT_highQE,9);
 778                 ce_cat = 6 ; 
 779                 s_di.SetSpline(false);
 780                 return s_di.Value(theta);
 781             }
 782             ce_cat = 7 ;  
 783         }       
then I modify the G4OpBoundaryProcess. I just design the API which get the efficiecy in order to know about the efficiency value which G4OpBoudaryProcess used and I didn't modify other code of G4OpBoundaryProcess . I don't understand why it is problematic like you said.



When I do the QE compare, I run the script like the following: 

#!/bin/bash

python $TUTORIALROOT/share/tut_detsim.py --no-use-pmtsimsvc --disable-pmt-optical-model  --output det_sample.root --user-output det_sample_user.root --evtmax 1 gun --positions 0 0 0 --particles gamma --momentums 30000.0 --directions 0 0 -1
I use the argument  --no-use-pmtsimsvc  so that Efficiency actually be register to the PMT volume and the Boundary Process can get the Efficiency. Thus the efficiency is not 1 !! and then in my validation code in junoSD_PMT_v2::ProcessHit.cc, I directly use PMTSimSvc which now is not under the control of *m_use_pmtsimsvc*.

thus

 int debug = 1 ;  
    if(debug){
      std::cout<<"   pmtid   =  "<< pmtID
               << "  theta   = " <<  local_pos.theta()
               <<"   pmtcat  = "<< m_PMTParamsvc->getPMTCategory(pmtID)
               <<"   volname = " << volname << std::endl ;
      double epsilon = 1e-10;
      double qe_0= qe * (boundary_proc->GetTheEff());

thus the qe_0 is not same as qe since in my run.sh script which shows above the efficiency is registered. These code are just in my local trunk of Offline.



