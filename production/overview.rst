overview
=========

Current Scripts
-----------------

::

   ~/opticks/CSGOptiX/cxs_min.sh
   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh
   ~/j/jok.bash 


DONE : revisit opticks-t
--------------------------

DONE : okdist updates
------------------------

DONE : forked opticks to opticks_ancient on bitbucket
--------------------------------------------------------

* https://bitbucket.org/simoncblyth/opticks_ancient/

Description of opticks_ancient on bitbuket::

    This opticks_ancient fork of opticks done Nov 3 2023 is to provide an easily
    visible record of inactive opticks packages that are soon to be removed from
    the primary opticks repository


DONE : created and tested binary release standalone opticks distribution 
----------------------------------------------------------------------------

DONE : more release GPU job tests : output checks beyond just ctest
---------------------------------------------------------------------

DONE : upload binary opticks distrib to /cvmfs/opticks.ihep.ac.cn  : just a mechanics test
-------------------------------------------------------------------------------------------

DONE :  generalized oktar.py for packing .opticks GEOM, curandState ...
-------------------------------------------------------------------------------------------

* decide on naming convention : probably follow juno+opticks release name 
  to reflect the geometry 

HMM : does a shared .opticks belong in /cvmfs OR /hpcfs ? 

Probably /hpcfs because for running large numbers of 
photons it needs to be big::

    /hpcfs/juno/junogpu/opticks/  ?   


DONE : .opticks location flexibility without changing HOME ?  
-------------------------------------------------------------

Split relatively "fixed" .opticks which make sense to be shared
from more transient .opticksrc that makes less sense to share.  

.opticks::

  GEOM
  rngcache  
  InputPhotons
  precooked

.opticksrc::

  scontext 


DONE : scontest_test investigate scontext/sdevice.bin of zero length 
-----------------------------------------------------------------------

DONE : building against the binary release : in examples/UseRelease
---------------------------------------------------------------------

Expt in R:BuildAgainstRelease and examples/UseRelease

HMM : maybe should include some source examples with the binary release ? 



DONE : consider if it make sense to include custom4 and optix7.5 into the opticks binary release ? 
----------------------------------------------------------------------------------------------------

custom4
   NO : it should not be included because junosw depends on that too, hence
   to ensure are using the same external and avoid version shear crashes need 
   to keep it separate so it gets configured once only  

optix7.5
   NO : just two directories with ~16 headers, this could be included 
   because the expectation is that only opticks depends on it 
   
   * BUT IT IS CLEARER TO JUST TO REFER TO SEPARATE /cvmfs WITH OPTIX  


DONE : switch from disc beam to surface of sphere radial generation
----------------------------------------------------------------------

* OLD:~/opticks/optixrap/cu/torchstep.h 
* ~/opticks/sysrap/tests/storch_test.sh 


DONE : get G4CXTest_GEOM operational with JUNO geometry for fast cycle 
------------------------------------------------------------------------

Follow approach of g4cx/tests/G4CXTest_raindrop.sh with g4cx/tests/G4CXTest_GEOM.sh

* :doc:`G4CXTest_GEOM`

* ~/opticks/g4cx/tests/G4CXTest_GEOM.sh







TODO : workaround the github fork into same organization limitation 
----------------------------------------------------------------------

* simply add opticks_ancient and push ? 

TODO : tidy up opticks inactive packages 
---------------------------------------------


TODO : check using opticks python functionality from the release
------------------------------------------------------------------

Convert G4CXTest_raindrop.sh into a "user example" 


TODO : junosw+opticks release : using opticks from /cvmfs/opticks.ihep.ac.cn 
------------------------------------------------------------------------------------

* would be best if the existing scripts can do this::
 
  /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b/build-tools/build.sh  

The above script is very high level : so no change needed

The junoenv scripts need small changes to get opticks from release dir 
on /cvmfs/opticks.ihep.ac.cn instead of getting from tarball or git clone 

::

   in principal the opticks build could be done via normal junoenv
   but thats not convenient while opticks needs frequent changes,
   so start with it separate 



WIP : investigate slow sevt.py SAB chi2 comparison, maybe need to do that in C++ ?
--------------------------------------------------------------------------------------



WIP : junosw + opticks : profile iteration
-------------------------------------------

* mode:3 iterating with input photons giving factor of only 100x so far 
* iteration is hampered by 2-3min delay to initialize junosw

* DONE : central source instead of input photons
* TODO : mode 1 vs 2 vs 3 comparison



DONE : get cxs_min.sh to do the same as the A side of G4CXTest_GEOM.sh : check match
---------------------------------------------------------------------------------------

Currently using input photons. Need to switch it to same torch as G4CXTest_GEOM. 
Hmm factor off the torch setup ?::

   ~/opticks/CSGOptiX/cxs_min.sh
   ~/opticks/CSGOptiX/cxs_min.sh ana 
   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh


See :doc:`cxs_min_shakedown`


TODO : CMake separate Debug and Release build tree ?
------------------------------------------------------

* https://cmake.org/cmake/help/latest/guide/tutorial/Packaging%20Debug%20and%20Release.html

::

    cd debug
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    cmake --build .
    cd ../release
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .



TODO : use NPFold profile and stamp summary in job scripts ?
-------------------------------------------------------------------

::

    ~/np/tests/NPFold_profile_test.sh 
    ~/np/tests/NPFold_stamps_test.sh 


~/np/tests/NPFold_stamps_test.cc::

    int main(int argc, char** argv)
    {
        const char* path = argc > 1 ? argv[1] : nullptr ;   
        if(path == nullptr) return 0 ; 

        NPFold* f = NPFold::Load(path); 
        //std::cout << " path " << path << std::endl << f->desc() << std::endl ; 

        NPFold* ab = f->subfold_summary('S', "a://p", "b://n"); 
        ab->save("$FOLD"); 

        return 0 ; 
    } 


    #include "NPFold.h"

    int main(int argc, char** argv)
    {
        std::cout << argv[0] << std::endl ; 
        const char* path = argc > 1 ? argv[1] : nullptr ;   
        if(path == nullptr) return 0 ; 

        NPFold* f = NPFold::Load(path);
        std::cout << "NPFold::Load(\"" << path << "\")" << std::endl ;

        NPFold* ab = f->subfold_summary('P', "a://p", "b://n");
        ab->save("$FOLD");
        std::cout << "NPFold::subprofile_summary.P created and saved subprofile symmary NPFold to $FOLD " << std::endl ;

        return 0 ; 
    }




 
