G4CXAppTest_comparison
========================

Context
--------

* previous :doc:`G4CXAppTest_shakedown`


Workflow 
---------

::

    gxt ; ./G4CXAppTest.sh                # workstation
    gxt ; ./G4CXAppTest.sh grab           # laptop
    PICK=AB MODE=2 ./G4CXAppTest.sh ana   # laptop

Next
-----

* need to persist and grab the geometry to debug 

Initial issues
---------------

1. Looks like B (on workstation) is POM:0 with photons not entering PMT
2. Bizarrely B on laptop looks more normal POM:1 ... IS THAT CUSTOM4 VERSION DIFFERENCE ?
3. A has no SD, so no hits 


A has no SD, maybe lacking Sensor setup ?
-------------------------------------------

HMM Probably need::

   export GBndLib__SENSOR_BOUNDARY_LIST=$(cat << EOL
    Pyrex/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/Vacuum
    Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/Vacuum
    Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum
    Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum
   EOL






