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
   test 


Standalone access to PMT data using persisted PMTSimParamData
--------------------------------------------------------------- 

PMTAccessor.h
   implements the IPMTAccessor.h interface, can be 
   used both within and without the monolith

   * within monolith boot the accessor with PMTSimParamData pointer
     obtained from the PMTSimParamSvc 

   * without monolith boot the accessor using PMTSimParamData_BASE envvar
     that points to a persisted folder : this despite standalone usage 
     the data does come from the Svc   


Layr.h
   single header CPU/GPU reimplementation of MultiFilmModel 

Layr.rst
   notes and references for Layr.h 

LayrTest.cc
LayrTest.cu
LayrTest.h
LayrTest.py
LayrTest.sh
   aoi scans 
   
   HMM: how did I make the original POM scan ?

LayrMinimal.cc
LayrMinimal.sh
LayrMin.cc
   demonstrate minimal usage of Layr.h  


planning_CustomG4OpBoundaryProcess_development.rst




