#include <cassert>
#include <iostream>
#include <string>
#include "TGraph.h"
#include "NP.hh"


// from IPMTParamSvc.h
enum PMT_CATEGORY {
  kPMT_Unknown=-1,
  kPMT_NNVT,
  kPMT_Hamamatsu,
  kPMT_HZC,
  kPMT_NNVT_HighQE
};


struct PMTAngular
{
    TGraph *gTT_MCP, *gAmp_MCP, *gCE_Dynode, *gCE_MCP, *gCE_R12860, *gCE_NNVTMCP, *gCE_NNVTMCP_HiQE ; 

    PMTAngular(); 


    static const int NUM_PV = 5 ;
    static std::string PV[NUM_PV] ; 

    double get_pmt_ce(const std::string &ce_mode, const std::string &volname, double theta, bool pmt_type, bool qe_type, int &ce_cat) const ;
    double get_pmt_ce(int pmtcat, double theta, int& ce_cat) const ;

    void   save_scan(const char* dir) const ;
    void   save(TGraph* g, const char* dir, const char* name) const ;
    void   save(const char* dir) const ;

};

PMTAngular::PMTAngular()
{
  double tt_angle[9] = {0, 14, 30, 42.5, 55, 67, 77.5, 85, 90};
  double tt_ratio[9] = {0., 0., 0.2142, 4.5757, 6.2484, 9.1953, 8.9885, 7.87506618, 7.1328014};
  gTT_MCP = new TGraph(9, tt_angle, tt_ratio);

  double amp_angle[9] = {-80, -60, -40, -20, 0, 20, 40, 60, 80};
  double amp_ratio[9] = {0.177,0.0479,0.04835,0.0445,0.0433,0.0552,0.0403,0.0372,0.1849};
  gAmp_MCP = new TGraph(9, amp_angle, amp_ratio );

  double ce_angle_dynode[9] = {0, 13, 28, 41, 55, 66, 79, 85, 90};
  double ce_dynode[9] = {0.873, 0.873, 0.888, 0.896, 0.881, 0.9, 0.881, 0.627, 0.262};
  gCE_Dynode = new TGraph(9, ce_angle_dynode, ce_dynode);

  double ce_angle_mcp[9] = {0, 14, 40, 42.5, 55, 67, 77.5, 85, 90};
  double ce_mcp[9]    = {0.900, 0.900, 0.845, 0.801, 0.775, 0.802, 0.802, 0.771, 0.660};
  gCE_MCP = new TGraph(9, ce_angle_mcp, ce_mcp);

  double ce_R12860[9] = {0.911, 0.911, 0.9222, 0.9294, 0.9235, 0.93, 0.9095, 0.6261, 0.2733};
  gCE_R12860 = new TGraph(9, ce_angle_dynode, ce_R12860);

  double ce_NNVTMCP[9] = {1.0, 1.0, 0.9453, 0.9105, 0.8931, 0.9255, 0.9274, 0.8841, 0.734};
  gCE_NNVTMCP = new TGraph(9, ce_angle_mcp, ce_NNVTMCP);

  double ce_NNVTMCP_HiQE[9] = {1.0, 1.0, 0.9772, 0.9723, 0.9699, 0.9697, 0.9452, 0.9103, 0.734};
  gCE_NNVTMCP_HiQE = new TGraph(0, ce_angle_mcp, ce_NNVTMCP_HiQE);
                         //   ^^^^^ THAT WAS ZERO ? DELIBERATE ?
}


/**
Convention is that variables starting with "m_" are member variables, so this "m_ce_mode" should be changed to "ce_mode"
**/

double PMTAngular::get_pmt_ce(const std::string& ce_mode, const std::string& volname, double theta, bool pmt_type, bool qe_type, int& ce_cat) const
{
   
    if (ce_mode == "None") {
        ce_cat = 1;
        return 1.0;
    } else if (ce_mode == "20inch") {
        if (volname == "PMT_20inch_body_phys") {
            if (pmt_type) {
                ce_cat = 2;
                return gCE_Dynode->Eval(theta);
            } else {
                ce_cat = 3;
                return gCE_MCP->Eval(theta);
            }
        }
        else if (volname == "HamamatsuR12860_PMT_20inch_body_phys") {

            ce_cat = 4 ; 
            return gCE_R12860->Eval(theta, 0, "S");
        }


        else if (volname == "NNVTMCPPMT_PMT_20inch_body_phys") {

            if(!pmt_type && !qe_type){
                ce_cat = 5 ;
                return gCE_NNVTMCP->Eval(theta, 0, "S");
            }
            else if(!pmt_type && qe_type) {
                ce_cat = 6 ;
                return gCE_NNVTMCP_HiQE->Eval(theta, 0, "S");
            }
        }
        ce_cat = 100 ;  // added this as the point of ce_cat is to enumerate all code paths, 
                        // otherwise it would be undefined  for volname other than the above
          
    }
/*
    else if (ce_mode == "20inchflat") { 
        if(volname == "PMT_20inch_body_phys") {
            static double mean_val = m_ce_flat_value;
            ce_cat = 7;
            return mean_val; 
        }
    } else if (ce_mode == "flat") {
        if (volname == "R12860TorusPMTManager_body_phys") {
            ce_cat = 8;
            static double Ham20inch_R12860_mean_val = Ham20inch_m_ce_flat_value * Ham20inch_m_EAR_value;
            return Ham20inch_R12860_mean_val;
        } 
        else if (volname == "MCP20inchPMTManager_body_phys") {
            ce_cat = 9;
            static double MCP20inch_mean_val = MCP20inch_m_ce_flat_value * MCP20inch_m_EAR_value;
            return MCP20inch_mean_val;
        }
        else if (volname == "MCP8inchPMTManager_body_phys") {
            ce_cat = 10;
            static double MCP8inch_mean_val = MCP8inch_m_ce_flat_value * MCP8inch_m_EAR_value;
            return MCP8inch_mean_val;
        } else if (volname == "Ham8inchPMTManager_body_phys") {
            ce_cat = 11;
            static double Ham8inch_mean_val = Ham8inch_m_ce_flat_value * Ham8inch_m_EAR_value;
        } else if (volname == "HZC9inchPMTManager_body_phys") {
            ce_cat = 12;
            static double HZC9inch_mean_val = HZC9inch_m_ce_flat_value * HZC9inch_m_EAR_value;
        }
    }  else if (ce_mode == "20inchfunc") {
        if (!m_ce_func) {
            std::cout << "WARNING: TheCE Function is not defined!" << std::endl;
            assert(m_ce_func);
        }
        if(theta>90) theta = 90;
        theta = 90 - theta;
        ce_cat = 13;
        return m_ce_func->Eval(theta);
    }
*/
    else {
        ce_cat = 14;
        std::cout << "WARNING: unknown CE mode " << ce_mode << std::endl;
    }

    return 1.0;
}



std::string PMTAngular::PV[NUM_PV] = {
"kPMT_Unknown",
"NNVTMCPPMT_PMT_20inch_body_phys",
"HamamatsuR12860_PMT_20inch_body_phys",
"kPMT_HZC",
"NNVTMCPPMT_PMT_20inch_body_phys"
};


double PMTAngular::get_pmt_ce(int pmtcat, double theta, int& ce_cat) const 
{
    bool first = ce_cat == -1 ; 
    assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 ); 
    unsigned pmtidx = pmtcat + 1 ; 
    const std::string& volname = PV[pmtidx] ;  
    bool pmt_type, qe_type ; 
    switch(pmtcat)
    {
        case kPMT_Unknown:     { qe_type = false ; pmt_type = false ; } ; break ;   
        case kPMT_NNVT:        { qe_type = false ; pmt_type = false ; } ; break ; 
        case kPMT_Hamamatsu:   { qe_type = false ; pmt_type = true  ; } ; break ;  
        case kPMT_HZC:         { qe_type = false ; pmt_type = false ; } ; break ; 
        case kPMT_NNVT_HighQE: { qe_type = true  ; pmt_type = false ; } ; break ;  
    }


    std::string ce_mode = "20inch" ; 
    double ce = get_pmt_ce( ce_mode, volname, theta, pmt_type, qe_type, ce_cat ); 

    if(first)
    {
        std::cout 
           << "PMTAngular::get_pmt_ce"
           << " pmtcat " << std::setw(2) << pmtcat
           << " pmtidx " << pmtidx
           << " qe_type " << qe_type
           << " pmt_type " << pmt_type
           << " ce_cat " << std::setw(4) << ce_cat    
           << " ce " << std::fixed << std::setw(10) << std::setprecision(5) << ce 
           << " volname " << volname
           << std::endl 
           ; 
    }
    return ce ; 

}

void PMTAngular::save_scan(const char* dir) const 
{
    unsigned num_cat = 5 ; 
    unsigned num_angle = 901u ; 
    NP* d = NP::Linspace<double>(0., 90., num_angle ); 
    const double* dd = d->cvalues<double>(); 

    NP* a = NP::Make<double>(num_cat, num_angle) ;
    double* aa = a->values<double>(); 

    for(unsigned i=0 ; i < num_cat ; i++)
    { 
        int pmtcat = i - 1 ;     
        int ce_cat = -1 ; 
        for(unsigned j=0 ; j < num_angle ; j++)
        {
            double theta = dd[j] ;   
            aa[i*num_angle+j] = get_pmt_ce(pmtcat, theta, ce_cat ); 
        }
    }

    d->save(dir, "theta.npy"); 
    a->save(dir, "ce.npy"); 
}


void PMTAngular::save(TGraph* g, const char* dir, const char* name) const 
{
    unsigned n = g->GetN(); 
    NP* p = NP::Make<double>(n, 2); 
    double* pp = p->values<double>(); 
    for(unsigned i=0 ; i < n ; i++)
    {
        double x, y ; 
        int rc = g->GetPoint(i, x, y ) ;
        //std::cout << "rc " << rc << std::endl ;
        assert( rc > -1 ); 
        pp[i*2+0] = x ; 
        pp[i*2+1] = y ; 
    }
    p->save(dir, name); 
}

void PMTAngular::save(const char* dir) const
{
    save(gCE_R12860, dir, "gCE_R12860.npy"); 
    save(gCE_NNVTMCP, dir, "gCE_NNVTMCP.npy"); 
    save(gCE_NNVTMCP_HiQE, dir, "gCE_NNVTMCP_HiQE.npy"); 

    save_scan(dir); 
}



int main()
{
    PMTAngular pa ; 
    pa.save("/tmp/PMTAngular"); 
    return 0 ; 
}
