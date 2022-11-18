#ifdef PMTFASTSIM_STANDALONE
#include <plog/Log.h>
#include "SLOG_INIT.hh"
#include "SLOG.hh"

#include "J_PMTFASTSIM_LOG.hh"

    
void J_PMTFASTSIM_LOG::Initialize(int level, void* app1, void* app2 )
{
    SLOG_INIT(level, app1, app2);
}
void J_PMTFASTSIM_LOG::Check(const char* msg)
{
    SLOG_CHECK(msg);
}


template<int IDX>
void J_PMTFASTSIM_LOG::Init(int level, void* app1, void* app2 )
{
    SLOG_INIT_(level, app1, app2, IDX );  
}

template void J_PMTFASTSIM_LOG::Init<0>( int, void*, void* ); 
template void J_PMTFASTSIM_LOG::Init<1>( int, void*, void* ); 


#endif

