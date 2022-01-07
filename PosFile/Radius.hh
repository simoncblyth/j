#pragma once

/**
jcv LSExpDetectorConstruction

 118   ball_r = 19.434*m; //19.5*m;
 119   ball_vetoPmt_r=20.55*m;
 120   //strut_r_acrylic =17820. *mm + 155.*mm + 600. *mm;  //17820. *mm + 165. *mm + 600. *mm + 35. *mm;
 121   strut_r_acrylic =17820. *mm + 256.9*mm + 1807.6/2. *mm;
 122   strut2_r_acrylic =17820. *mm + 256.9*mm + 1913.6/2 *mm;
 123   strutballhead_r_acrylic=17820. *mm + 256.9*mm-50.*mm;  
 124     
 125 
 126   strut_r_balloon =17715. *mm + 700 *mm + 5. *mm;
 127   fastener_r = 17820.*mm + 20.*mm; //17826. *mm;
 128   addition_r = 17820. *mm;
 129   upper_r = 17820.*mm + 140.*mm; 
 130   xjanchor_r = 17820.*mm ;
 131   xjfixture_r = 17820.*mm + 10.*mm + 13./2*mm; 
 132   sjclsanchor_r = 17699.938*mm;
 133   sjfixture_r = 17699.975*mm;
 134   sjreceiver_r = 17699.938*mm;
 135   sjreceiver_fastener_r = 17699.938*mm - 10.*mm - 13./2*mm;
 136   m_cd_name = "DetSim1";
 137   m_cd_enabled = true;
 138   m_wp_enabled = true;
 139   m_tt_enabled = true;

**/


struct Radius
{
    static constexpr double mm = 1.  ; 
    static constexpr double strut_r_acrylic =17820. *mm + 256.9*mm + 1807.6/2. *mm;
    static constexpr double strut2_r_acrylic =17820. *mm + 256.9*mm + 1913.6/2 *mm;
    static constexpr double strutballhead_r_acrylic=17820. *mm + 256.9*mm-50.*mm;  
    static constexpr double strut_r_balloon =17715. *mm + 700 *mm + 5. *mm;
    static constexpr double fastener_r = 17820.*mm + 20.*mm; //17826. *mm;
    static constexpr double addition_r = 17820. *mm;
    static constexpr double upper_r = 17820.*mm + 140.*mm; 
    static constexpr double xjanchor_r = 17820.*mm ;
    static constexpr double xjfixture_r = 17820.*mm + 10.*mm + 13./2*mm;        // NOT USED ?
    static constexpr double sjclsanchor_r = 17699.938*mm;
    static constexpr double sjfixture_r = 17699.975*mm;
    static constexpr double sjreceiver_r = 17699.938*mm;
    static constexpr double sjreceiver_fastener_r = 17699.938*mm - 10.*mm - 13./2*mm;
    static const char* NAMES ;      
    static void Dump();
    static double Get(const char* name );
    static double GetCSV(const char* name );
};

const char* Radius::NAMES = R"LITERAL(
strut_r_acrylic
strut2_r_acrylic
strutballhead_r_acrylic
strut_r_balloon
fastener_r
addition_r
upper_r
xjanchor_r
xjfixture_r
sjclsanchor_r
sjfixture_r
sjreceiver_r
sjreceiver_fastener_r
)LITERAL" ; 


#include <vector>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>


inline void Radius::Dump()
{
    std::stringstream ss; 
    ss.str(NAMES)  ;
    std::string s;
    
    typedef std::pair<double,std::string> DS ; 
    std::vector<DS> rk ; 
    while (std::getline(ss, s)) 
    {  
        const char* k = s.c_str(); 
        if(strlen(k) == 0 ) continue ; 
        double r = Get(k) ; 
        rk.push_back(std::make_pair(r,k));  
    } 

    std::sort( rk.begin(), rk.end() ); 

    double rmin = rk[0].first ; 
    double rmax = rk[rk.size()-1].first ;

    std::cout << "j/PosFile/Radius.hh Radius::Dump r/r-rmin/r-max" << std::endl ; 

    for(unsigned i=0 ; i < rk.size() ; i++) 
    {
        const std::string& k = rk[i].second ;
        double r = rk[i].first ;

        std::cout 
            << std::setw(30) << k 
            << " : "
            << std::fixed << std::setw(10) << std::setprecision(4) << r
            << " : "
            << std::fixed << std::setw(10) << std::setprecision(4) << ( r - rmin )
            << " : "
            << std::fixed << std::setw(10) << std::setprecision(4) << ( r - rmax )
            << std::endl
            ; 
    }
}

inline double Radius::Get(const char* name )
{
    double r = 0. ; 
    if( strcmp(name, "strut_r_acrylic") == 0 )          r = strut_r_acrylic ; 
    if( strcmp(name, "strut2_r_acrylic") == 0 )         r = strut2_r_acrylic ; 
    if( strcmp(name, "strutballhead_r_acrylic") == 0 )  r = strutballhead_r_acrylic ; 
    if( strcmp(name, "strut_r_balloon") == 0 )          r = strut_r_balloon ;
    if( strcmp(name, "fastener_r") == 0 )               r = fastener_r ;
    if( strcmp(name, "addition_r") == 0 )               r = addition_r ;
    if( strcmp(name, "upper_r") == 0)                   r = upper_r ;
    if( strcmp(name, "xjanchor_r") == 0 )               r = xjanchor_r ;
    if( strcmp(name, "xjfixture_r") == 0 )              r = xjfixture_r ;
    if( strcmp(name, "sjclsanchor_r") == 0 )            r = sjclsanchor_r ;
    if( strcmp(name, "sjfixture_r") == 0 )              r = sjfixture_r ;
    if( strcmp(name, "sjreceiver_r") == 0 )             r = sjreceiver_r ;
    if( strcmp(name, "sjreceiver_fastener_r") == 0 )    r = sjreceiver_fastener_r ;
    return r ; 
}

inline double Radius::GetCSV(const char* name )
{
    double r = 0. ; 
    if( strcmp(name, "Strut_Acrylic.csv") == 0 )        r = strut_r_acrylic ; 
    if( strcmp(name, "StrutBar2_Acrylic.csv") == 0 )    r = strut2_r_acrylic ; 
    if( strcmp(name, "Strut_Anchor_Acrylic.csv") == 0 ) r = -1. ; 
    if( strcmp(name, "XJanchor.csv") == 0 )             r = xjanchor_r  ; 
    if( strcmp(name, "SJCLSanchor.csv") == 0 )          r = sjclsanchor_r  ; 
    if( strcmp(name, "SJFixturePos.csv") == 0 )         r = sjfixture_r ;
    if( strcmp(name, "SJReceiverPos.csv") == 0 )        r = sjreceiver_r  ; 
    std::cout << "Radius::Get " << name << " radius " << r << std::endl ; 
    return r ; 
}


