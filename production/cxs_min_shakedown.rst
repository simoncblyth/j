cxs_min_shakedown
==================

Workflow
----------

::

    ~/opticks/CSGOptiX/cxs_min.sh info
    ~/opticks/CSGOptiX/cxs_min.sh info_run
    LOG=1 ~/opticks/CSGOptiX/cxs_min.sh info_run
    ~/opticks/CSGOptiX/cxs_min.sh grab
    ~/opticks/CSGOptiX/cxs_min.sh ana



Faster cycling with CSGOptiX/cxs_min.sh ?
--------------------------------------------

::

    /**
    CSGOptiXSMTest : used from cxs_min.sh 
    =========================================

    **/

    #include "OPTICKS_LOG.hh"
    #include "CSGOptiX.h"

    int main(int argc, char** argv)
    {
        OPTICKS_LOG(argc, argv); 
        CSGOptiX::SimulateMain(); 
        return 0 ; 
    }

    0169 void CSGOptiX::SimulateMain() // static
     170 {
     171     SEventConfig::SetRGModeSimulate();
     172     CSGFoundry* fd = CSGFoundry::Load(); 
     173     CSGOptiX* cx = CSGOptiX::Create(fd) ;
     174     cx->simulate(0); 
     175 }




