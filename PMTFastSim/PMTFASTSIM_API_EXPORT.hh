#pragma once

#if defined (_WIN32) 

   #if defined(PMTFASTSIM_EXPORTS)
       #define  PMTFASTSIM_API __declspec(dllexport)
   #else
       #define  PMTFASTSIM_API __declspec(dllimport)
   #endif

#else

   #define PMTFASTSIM_API  __attribute__ ((visibility ("default")))

#endif


