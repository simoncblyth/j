cvmfs notes
=============

cvmfs expert
-------------

::

    HU Qingbao <huqb@ihep.ac.cn>


detailed instructions ~/home/admin/opticks/hcvmfs.bash
----------------------------------------------------------

:: 
   
   home-
   hcvmfs-vi 


find notes
-----------

::

    epsilon:~ blyth$ mdfind cvmfs_server
    /Users/blyth/j/j.bash
    #/Users/blyth/txt/cvmfs.txt
    /Users/blyth/opticks/bin/okdist.bash
    /Users/blyth/home/admin/opticks/hcvmfs.bash



script to change paths : using "sed -i" on all files including binary
------------------------------------------------------------------------

::

    cp /afs/ihep.ac.cn/users/l/lint/fixed-genie.sh g/lint-sed-switch-all-paths-in-tree-of-files.sh 


some old instructions that are not very good : above hcvmfs-vi ones much  better
-----------------------------------------------------------------------------------

::

    you can login lxslc6 with your cluster account "blyth", then ssh 
    optickspub@cvmfs-stratum-zero.ihep.ac.n with your ssh-key.


    To become the shared user execute:
        sudo -i -u optickspub
    To start a transaction:
        cvmfs_server transaction opticks.ihep.ac.cn
    To edit repo
        cd /cvmfs/opticks.ihep.ac.cn && edit repo && cd /cvmfs
    To publish a transaction
        cvmfs_server publish -m "your publish info" opticks.ihep.ac.cn


    when you login cvmfs-stratum-zero.ihep.ac.cn, you can transaction and publish  opticks.ihep.ac.cn


    you can access this path on gpu worknode : /cvmfs/opticks.ihep.ac.cn


Updating cvmfs workflow
-------------------------

1. prepare a tarball on some other filesystem at a path chosen to 
   have a length that matches the destination : so can run a script 
   to change all the paths



how to publish a tarball on cvmfs
-----------------------------------

::

    /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc1120/b

    cvmfs_server transaction opticks.ihep.ac.cn
    cvmfs_server publish  -m "update dbdata: add pmt_20230326_CDSPMT.csv again. " opticks.ihep.ac.cn




thoughts on cvfms usage for junosw+opticks deployment
------------------------------------------------------

Once opticks becomes stable it can be regarded as 
just another junosw external. But while it is 
changing frequently it is more convenient to 
for junosw to use opticks from::

   OPTICKS_PREFIX
   /cvmfs/opticks.ihep.ac.cn/ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg/

connecting to cvmfs stratum zero : for publishing
----------------------------------------------------

::

    L7[blyth@lxslc713 ~]$ vi /afs/ihep.ac.cn/users/b/blyth/.ssh/known_hosts +11
    L7[blyth@lxslc713 ~]$ ssh O
    The authenticity of host 'cvmfs-stratum-zero.ihep.ac.cn (202.122.33.83)' can't be established.
    ECDSA key fingerprint is SHA256:Kz8480kKx/c9NG1xd5nDB2ZdtMtH85T+eXGyIH24TJs.
    ECDSA key fingerprint is MD5:15:db:e1:1a:8c:23:77:cf:4e:e8:33:e3:02:ae:41:4a.
    Are you sure you want to continue connecting (yes/no)? yes
    Warning: Permanently added 'cvmfs-stratum-zero.ihep.ac.cn,202.122.33.83' (ECDSA) to the list of known hosts.
    Enter passphrase for key '/afs/ihep.ac.cn/users/b/blyth/.ssh/id_rsa': 
    Last login: Sun Jul  5 17:55:53 2020
    [optickspub@cvmfs-stratum-zero-b ~]$ 




cvmfs directory tree : for sharing opticks releases
-----------------------------------------------------

::

    L7[blyth@lxslc708 ~]$ cd /cvmfs/opticks.ihep.ac.cn
    L7[blyth@lxslc708 opticks.ihep.ac.cn]$ ls -l 
    total 3
    drwxrwxr-x 2 cvmfs cvmfs  6 Apr 25  2019 common
    drwxrwxr-x 2 cvmfs cvmfs  6 Apr 25  2019 external
    -rw-r--r-- 1 cvmfs cvmfs 48 Apr 25  2019 new_repository
    drwxrwxr-x 3 cvmfs cvmfs 22 Oct 10  2019 ok
    drwxrwxr-x 2 cvmfs cvmfs  6 Apr 25  2019 software
    L7[blyth@lxslc708 opticks.ihep.ac.cn]$ 


Mostly empty except::

    L7[blyth@lxslc708 opticks.ihep.ac.cn]$ find . 
    .
    ./new_repository
    ./software
    ./common
    ./external
    ./.cvmfsdirtab
    ./ok
    ./ok/releases
    ./ok/releases/Opticks-0.0.0_alpha
    ./ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg
    ./ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg/include
    ./ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg/include/OpticksGeo
    ./ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg/include/OpticksGeo/OpticksGeometry.hh
    ./ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg/include/OpticksGeo/OpticksHub.hh
    ./ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg/include/OpticksGeo/OKGEO_HEAD.hh
    ./ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg/include/OpticksGeo/OpticksGen.hh
    ./ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg/include/OpticksGeo/OKGEO_LOG.hh


::

    L7[blyth@lxslc708 opticks.ihep.ac.cn]$ l /cvmfs/opticks.ihep.ac.cn/ok/releases/Opticks-0.0.0_alpha/x86_64-slc7-gcc48-geant4_10_04_p02-dbg/
    total 32
     1 drwxrwxr-x 15 cvmfs cvmfs   192 Oct 10  2019 .
     1 drwxrwxr-x  3 cvmfs cvmfs    52 Oct 10  2019 ..
     1 drwxrwxr-x  2 cvmfs cvmfs   232 Oct 10  2019 bin
     1 drwxrwxr-x  3 cvmfs cvmfs    21 Oct 10  2019 cmake
     1 drwxrwxr-x  8 cvmfs cvmfs    81 Oct 10  2019 externals
     1 drwxrwxr-x 15 cvmfs cvmfs   242 Oct 10  2019 gl
     1 drwxrwxr-x 24 cvmfs cvmfs   330 Oct 10  2019 include
     1 drwxrwxr-x  3 cvmfs cvmfs    17 Oct 10  2019 installcache
     1 drwxrwxr-x  3 cvmfs cvmfs    43 Oct 10  2019 integration
    17 drwxrwxr-x  2 cvmfs cvmfs 16384 Oct 10  2019 lib
     5 drwxrwxr-x  4 cvmfs cvmfs  4096 Oct 10  2019 lib64
     1 drwxrwxr-x  2 cvmfs cvmfs    56 Oct 10  2019 metadata
     1 drwxrwxr-x  5 cvmfs cvmfs    59 Oct 10  2019 opticksaux
     1 drwxrwxr-x  3 cvmfs cvmfs    21 Oct 10  2019 py
     5 drwxrwxr-x 24 cvmfs cvmfs  4096 Oct 10  2019 tests
    L7[blyth@lxslc708 opticks.ihep.ac.cn]$ 


