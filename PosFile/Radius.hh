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

#include <vector>
#include <string>

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

    static const char* strut_r_acrylic_ ; 
    static const char* strut2_r_acrylic_ ; 
    static const char* strutballhead_r_acrylic_ ; 
    static const char* strut_r_balloon_ ; 
    static const char* fastener_r_ ; 
    static const char* addition_r_ ; 
    static const char* upper_r_ ; 
    static const char* xjanchor_r_ ; 
    static const char* xjfixture_r_ ; 
    static const char* sjclsanchor_r_ ; 
    static const char* sjfixture_r_ ; 
    static const char* sjreceiver_r_ ; 
    static const char* sjreceiver_fastener_r_ ; 

    static const char* NAMES ;      
    static void Dump();
    static double Get(const char* key );
    static void Get(std::vector<std::pair<double, std::string>>& radius_name ); 
    static const char* KeyForCSVName(const char* csvname );
    static void Save(const char* path); 

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

const char* Radius::strut_r_acrylic_         = "strut_r_acrylic" ; 
const char* Radius::strut2_r_acrylic_        = "strut2_r_acrylic" ; 
const char* Radius::strutballhead_r_acrylic_ = "strutballhead_r_acrylic" ; 
const char* Radius::strut_r_balloon_         = "strut_r_balloon" ; 
const char* Radius::fastener_r_              = "fastener_r" ; 
const char* Radius::addition_r_              = "addition_r" ; 
const char* Radius::upper_r_                 = "upper_r" ;  
const char* Radius::xjanchor_r_              = "xjanchor_r" ; 
const char* Radius::xjfixture_r_             = "xjfixture_r" ; 
const char* Radius::sjclsanchor_r_           = "sjclsanchor_r" ; 
const char* Radius::sjfixture_r_             = "sjfixture_r" ; 
const char* Radius::sjreceiver_r_            = "sjreceiver_r" ; 
const char* Radius::sjreceiver_fastener_r_   = "sjreceiver_fastener_r" ; 


#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "NP.hh"

inline void Radius::Get(std::vector<std::pair<double, std::string>>& radius_name )
{
    std::stringstream ss; 
    ss.str(NAMES)  ;
    std::string s;
    while (std::getline(ss, s)) 
    {  
        const char* k = s.c_str(); 
        if(strlen(k) == 0 ) continue ; 
        double r = Get(k) ; 
        radius_name.push_back(std::make_pair(r,k));  
    } 
}

inline void Radius::Save(const char* path)
{
    typedef std::pair<double,std::string> DS ; 
    std::vector<DS> rk ; 
    Get(rk);  

    NP* a = NP::Make<double>( rk.size() ) ; 
    double* aa = a->values<double>(); 

    std::stringstream ss ; 
    for(unsigned i=0 ; i < rk.size() ; i++) 
    {
        aa[i] = rk[i].first ; 
        ss << rk[i].second << std::endl ; 
    }
    a->meta = ss.str() ; 
    std::cout << "Radius::Save " << path << std::endl ;   
    a->save(path); 

}
inline void Radius::Dump()
{
    typedef std::pair<double,std::string> DS ; 
    std::vector<DS> rk ; 
    Get(rk);  

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

inline double Radius::Get(const char* key )
{
    double r = 0. ; 
    if(0 == strcmp(key,strut_r_acrylic_))          r = strut_r_acrylic ; 
    if(0 == strcmp(key,strut2_r_acrylic_))         r = strut2_r_acrylic ; 
    if(0 == strcmp(key,strutballhead_r_acrylic_))  r = strutballhead_r_acrylic ; 
    if(0 == strcmp(key,strut_r_balloon_))          r = strut_r_balloon ;
    if(0 == strcmp(key,fastener_r_))               r = fastener_r ;
    if(0 == strcmp(key,addition_r_))               r = addition_r ;
    if(0 == strcmp(key,upper_r_))                  r = upper_r ;
    if(0 == strcmp(key,xjanchor_r_))               r = xjanchor_r ;
    if(0 == strcmp(key,xjfixture_r_))              r = xjfixture_r ;
    if(0 == strcmp(key,sjclsanchor_r_))            r = sjclsanchor_r ;
    if(0 == strcmp(key,sjfixture_r_))              r = sjfixture_r ;
    if(0 == strcmp(key,sjreceiver_r_))             r = sjreceiver_r ;
    if(0 == strcmp(key,sjreceiver_fastener_r_))    r = sjreceiver_fastener_r ;
    return r ; 
}

/**
LSExpDetectorConstruction::setupCD_Sticks
-------------------------------------------

+=============================+==================================+=========================+========================+======================+
|  member                     |  class                           | pos_file                | radius                 |  notes               |             
+=============================+==================================+=========================+========================+======================+
| m_strut_name                | StrutAcrylicConstruction         | m_strut_pos_file        | strut_r                |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_strut2_name               | StrutBar2AcrylicConstruction     | m_strut2_pos_file       | strut2_r               |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+    
| m_strutballhead_name        | StrutBallheadAcrylicConstruction | m_fastener_pos_file     | strutballhead_r        |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+                      |   
| m_fastener_name             | FastenerAcrylicConstruction      | m_fastener_pos_file     | fastener_r             | 4 users of           |
+-----------------------------+----------------------------------+-------------------------+------------------------+ one pos_file         |
| m_upper_name                | UpperAcrylicConstruction         | m_fastener_pos_file     | upper_r                |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+                      | 
| m_addition_name             | AdditionAcrylicConstruction      | m_fastener_pos_file     | addition_r             |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+    
| m_xjanchor_name             | XJanchorConstruction             | m_xjanchor_pos_file     | xjanchor_r             |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+    
| m_xjfixture_name            | XJfixtureConstruction            | *m_xjanchor_pos_file*   | xjfixture_r            | out of pattern, bug? | 
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+    
| m_sjclsanchor_name          | SJCLSanchorConstruction          | m_sjclsanchor_pos_file  | sjclsanchor_r          |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjfixture_name            | SJFixtureConstruction            | m_sjfixture_pos_file    | sjfixture_r            |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjreceiver_name           | SJReceiverConstruction           | m_sjreceiver_pos_file   | sjreceiver_r           |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjreceiver_fastener_name  | XJfixtureConstruction            | *m_sjreceiver_pos_file* | sjreceiver_fastener_r  | out of pattern, bug? |
+=============================+==================================+=========================+========================+======================+

**/


inline const char* Radius::KeyForCSVName(const char* csvname )
{
    const char* key = nullptr ;  
    if( strcmp(csvname, "Strut_Acrylic.csv") == 0 )        key = strut_r_acrylic_ ; 
    if( strcmp(csvname, "StrutBar2_Acrylic.csv") == 0 )    key = strut2_r_acrylic_ ; 
    if( strcmp(csvname, "Strut_Anchor_Acrylic.csv") == 0 ) key = nullptr  ; 
    if( strcmp(csvname, "XJanchor.csv") == 0 )             key = xjanchor_r_  ; 
    if( strcmp(csvname, "SJCLSanchor.csv") == 0 )          key = sjclsanchor_r_  ; 
    if( strcmp(csvname, "SJFixturePos.csv") == 0 )         key = sjfixture_r_ ;
    if( strcmp(csvname, "SJReceiverPos.csv") == 0 )        key = sjreceiver_r_  ; 
    std::cout << "Radius::KeyForCSVName " << csvname << " key " << ( key ? key : "-" ) << std::endl ; 
    return key ; 
}

