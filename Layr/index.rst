Layr index
=============

Headers from j/Layr that are included into PMTFastSim pkg by ../PMTFastSim/CMakeLists.txt
---------------------------------------------------------------------------------------------

::

    ../Layr/Layr.h  
    ../Layr/JPMT.h  
    ../Layr/IPMTAccessor.h  
    ../Layr/PMTAccessor.h  
 

Common standalone/monolith interface for PMT data access 
------------------------------------------------------------

IPMTAccessor.h
   protocol base interface including get_stackspec get_pmtid_qe


Old JPMT.h access to PMT data without the Svc, using NP array reading
-----------------------------------------------------------------------

JPMT.h
   implements IPMTAccessor.h interface using data read from files without using Svc  

JPMTTest.cc
JPMTTest.py
JPMTTest.sh
   various tests including of IPMTAccessor::get_stackspec interface 


Standalone access to PMT data using persisted PMTSimParamData
--------------------------------------------------------------- 

PMTAccessor.h
   implements the IPMTAccessor.h interface, can be 
   used both within and without the monolith

   * within monolith boot the accessor with PMTSimParamData pointer
     obtained from the PMTSimParamSvc 

   * without monolith boot the accessor using PMTSimParamData_BASE envvar
     that points to a persisted folder : thus despite standalone usage 
     the data does come from the Svc   


Layr.h
   single header CPU/GPU reimplementation of MultiFilmModel 

Layr.rst
   notes and references for Layr.h 

LayrTest.cc
   gets StackSpec from JPMT.h and uses LayrTest to 
   do cpu scans, and when WITH_THRUST enabled also GPU scans 

LayrTest.h

   * LayrTestData struct acts as primary host device communication conduit
   * hostside upload/download/scan mechanics  
 
LayrTest.cu

   * LayrTest_launch, Stack_computeART_gpu NB passing StackSpec by value in kernel call 

LayrTest.py
   ARTPlot etc..  

LayrTest.sh
   aoi scans, WITH_THRUST/without for GPU/CPU test 
   



LayrMinimal.cc
LayrMinimal.sh
LayrMin.cc
   demonstrate minimal usage of Layr.h  


planning_CustomG4OpBoundaryProcess_development.rst



