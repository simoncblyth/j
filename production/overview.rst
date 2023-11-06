overview
=========


tidy up opticks
-----------------

::

    This opticks_ancient fork of opticks done Nov 3 2023 is to provide an easily
    visible record of inactive opticks packages that are soon to be removed from
    the primary opticks repository


opticks_ancient
-----------------

* TODO: workaround for github fork into same organization limitation 



revisit opticks-t
---------------------


okdist updates
-----------------





build opticks, create binary distribution for upload to /cvmfs/opticks.ihep.ac.cn 
-----------------------------------------------------------------------------------

* testing okdist-create on laptop 

  * this means need squeeky clean build and install dirs 




build junosw with opticks included : using opticks from /cvmfs/opticks.ihep.ac.cn 
------------------------------------------------------------------------------------

* would be best if the existing scripts can do this::
 
  /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b/build-tools/build.sh  

The above script is very high level : so no change needed

The junoenv scripts need small changes to get opticks from release dir 
on /cvmfs/opticks.ihep.ac.cn instead of getting from tarball or git clone 



::

   in principal the opticks build could be done via normal junoenv
   but thats not convenient while opticks needs changing : so start 
   with it separate 



