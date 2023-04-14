
#include <iostream>
#include "PMT.h"

int main()
{
    std::cout << " kOFFSET_CD_LPMT " << kOFFSET_CD_LPMT << std::endl ;  
    std::cout << " kOFFSET_WP_PMT  " << kOFFSET_WP_PMT  << std::endl ;  
    std::cout << " kOFFSET_CD_SPMT " << kOFFSET_CD_SPMT << std::endl ;  

    int _IsCD = 0 ; 
    int _IsWP = 0 ; 
    int _Is20inch = 0 ; 
    int _Is3inch = 0 ; 

    for(int pmtid=0 ; pmtid < kOFFSET_CD_SPMT+10 ; pmtid++ )
    {
         if(PMT::IsCD(pmtid)) _IsCD++ ; 
         if(PMT::IsWP(pmtid)) _IsWP++ ; 
         if(PMT::Is20inch(pmtid)) _Is20inch++ ; 
         if(PMT::Is3inch(pmtid)) _Is3inch++ ; 
    }

    std::cout
        << " IsCD " << _IsCD
        << std::endl 
        << " IsWP " << _IsWP 
        << std::endl 
        << " Is20inch " << _Is20inch 
        << std::endl 
        << " Is3inch " << _Is3inch 
        << std::endl 
        ;

     //   
     // kOFFSET_CD_SPMT<=pmtid and pmtid<kOFFSET_WP_PMT


    return 0 ; 
}
