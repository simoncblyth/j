#pragma once

#if defined (_WIN32) 

   #if defined(PMTSIM_EXPORTS)
       #define  PMTSIM_API __declspec(dllexport)
   #else
       #define  PMTSIM_API __declspec(dllimport)
   #endif

#else

   #define PMTSIM_API  __attribute__ ((visibility ("default")))

#endif


