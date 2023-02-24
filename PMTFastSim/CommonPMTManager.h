#pragma once
/**
CommonPMTManager.h
====================

To understand the PMTManager implementations::

    HamamatsuR12860PMTManager.cc
    NNVTMCPPMTManager.cc

it is necessary to keep in mind the distinction between:

1. POM : PMT Optical Model approach (m_enable_optical_model)
2. PMT : detail of the unnatural/natural PMT geometry implementation (m_natural_geometry)

These POM and PMT bools result in four POM*PMT cases to consider::
   
               +-------------------------------+------------------------------+-------------------------------+   
               |  4 POM*PMT cases              | Unnatural PMT Impl           |  Natural PMT Impl             |
               |                               |                              |                               |
               |                               |  m_natural_geometry:false    |  m_natural_geometry:true      |        
               +===============================+==============================+===============================+   
               |  Traditional POM              |                              |                               |
               |  (all Detection               |  ProcessHits QE              |  CustomG4OpBoundaryProcess    |
               |   at photocathode)            |                              |                               |
               |                               |                              |                               |
               |                               | OpticalSurfaceName           |  OpticalSurfaceName           |
               |                               | without special prefix       |  starting '#'                 |
               |                               |                              |                               |
               |                               |                              |                               |
               | m_enable_optical_model:false  |                              |                               |
               |                               |                              |                               |
               +-------------------------------+------------------------------+-------------------------------+
               |  MultiFilm POM                |                              |                               |
               |  (photons refract             | junoPMTOpticalModel.hh       | MultiLayrStack.h              |
               |   into PMT, complex           | FastSim in control           | CustomART.h                   |
               |   rindex layers)              | (boundary not run)           | CustomG4OpBoundaryProcess     |
               |                               |                              |                               |
               |                               |                              |                               |
               |                               |                              |                               |
               |                               | OpticalSurfaceName           |  OpticalSurfaceName           |
               |                               | without special prefix       |  starting '@'                 |
               |                               |                              |                               |
               |                               |                              |                               |
               |                               |                              |                               |
               | m_enable_optical_model:true   |                              |                               |
               |                               |                              |                               |
               +-------------------------------+------------------------------+-------------------------------+


**/

struct CommonPMTManager
{
    static char GetMirrorOpticalSurfacePrefix(bool natural_geometry, bool enable_optical_model ); 
};

/**
CommonPMTManager::GetMirrorOpticalSurfacePrefix
------------------------------------------------

The first char of the OpticalSurfaceName is used to control 
the customization of the CustomG4OpBoundaryProcess only for 
local_z > 0, ie only for the upper hemisphere of PMT solid.
This method returns the appropriate prefix for the active config. 
For the lower hemisphere there is no customization and standard 
Geant4 boundary handling is done. 

POM (PMT Optical Model, enable_optical_model) 
and PMT (natural PMT geometry, natural_geometry) matrix:

 +-------------+--------------+-----------+
 |             |   PMT:false  |  PMT:true |
 +=============+==============+===========+
 |  POM:false  |   '\0'       |   '#'     | 
 +-------------+--------------+-----------+
 |  POM:true   |   '\0'       |   '@'     |
 +-------------+--------------+-----------+

See CustomG4OpBoundaryProcess::PostStepDoIt  

'\0'
    without any special prefix char, CustomG4OpBoundaryProcess behaves standardly 

'#' 
    dielectric_metal, Traditional Detection at photocathode surface
    theReflectivity = 0.
    theTransmittance = 0.
    theEfficiency = 1.
'@' 
    dielectric_dielectric, Custom MultiFilm ART calculation of:
    theTransmittance, theReflectivity, theEfficiency 
    using the copyNo to get pmtid and lookup PMT properties


For intersects onto the upper hemi with both '@' and '#' prefixes the mirror
behavior is overridden by the CustomG4OpBoundaryProcess handling. 

Notice that as the customization applies only to the
upper hemisphere of the shape it becomes possible with PMT:true 
to model the PMT with a natural 2-volume Pyrex+Vacuum geometry. 
Hence the Pyrex->Vacuum boundary needs to be have the mirror optical surface
associated with it. 
   
**/

inline char CommonPMTManager::GetMirrorOpticalSurfacePrefix(bool natural_geometry, bool enable_optical_model ) // static 
{
    return natural_geometry == false ? '\0' : ( enable_optical_model ? '@' : '#' ) ; 
} 

