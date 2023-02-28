#pragma once

#ifdef PMTSIM_STANDALONE

#define J_PMTSIM_API  __attribute__ ((visibility ("default")))

//#define OK_PMTSIM_LOG_( IDX ) {  OK_PMTSIM_LOG::Initialize(plog::get<IDX>()->getMaxSeverity(), plog::get<IDX>(), nullptr ); }  
#define J_PMTSIM_LOG_( IDX ) {  J_PMTSIM_LOG::Init<IDX>( info, plog::get<IDX>(), nullptr ) ; }

struct J_PMTSIM_API J_PMTSIM_LOG 
{
    static void Initialize(int level, void* app1, void* app2 );
    static void Check(const char* msg);

    template<int IDX>
    static void Init(int level, void* app1, void* app2 );

};

#endif

