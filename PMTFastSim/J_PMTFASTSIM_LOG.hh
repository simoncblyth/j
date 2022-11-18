#pragma once

#ifdef PMTFASTSIM_STANDALONE

#define J_PMTFASTSIM_API  __attribute__ ((visibility ("default")))

//#define OK_PMTSIM_LOG_( IDX ) {  OK_PMTSIM_LOG::Initialize(plog::get<IDX>()->getMaxSeverity(), plog::get<IDX>(), nullptr ); }  
#define J_PMTFASTSIM_LOG_( IDX ) {  J_PMTFASTSIM_LOG::Init<IDX>( info, plog::get<IDX>(), nullptr ) ; }

struct J_PMTFASTSIM_API J_PMTFASTSIM_LOG 
{
    static void Initialize(int level, void* app1, void* app2 );
    static void Check(const char* msg);

    template<int IDX>
    static void Init(int level, void* app1, void* app2 );

};

#endif

