#pragma once

#include <cassert>
#include <string>
#include <cstring>
#include <vector>

template<typename ... Args>
std::string Form(const char* fmt, Args ... args )
{
    int sz = std::snprintf( nullptr, 0, fmt, args ... ) + 1 ; // +1 for null termination
    assert( sz > 0 );   
    std::vector<char> buf(sz) ;    
    std::snprintf( buf.data(), sz, fmt, args ... );
    return std::string( buf.begin(), buf.begin() + sz - 1 );  // exclude null termination 
}

template std::string Form( const char*, int );  




#include <cmath>
namespace TMath 
{
   inline double Sin(double a){ return std::sin(a) ; }
   inline double Cos(double a){ return std::cos(a) ; }
   inline double Pi(){ return M_PI ; }

}

