automount_fail
================


Observe "cd /cvmfs/opticks.ihep.ac.cn" works on P,L but not on A
------------------------------------------------------------------

* https://cvmfs.readthedocs.io/en/stable/cpt-quickstart.html


::

    A[blyth@localhost ~]$ cd /cvmfs/opticks.ihep.ac.cn
    -bash: cd: /cvmfs/opticks.ihep.ac.cn: No such file or directory

    A[blyth@localhost ~]$ which cvmfs_config
    /usr/bin/cvmfs_config

    A[blyth@localhost ~]$ cvmfs_config probe
    Probing /cvmfs/sft.cern.ch... OK
    Probing /cvmfs/juno.ihep.ac.cn... OK
    Probing /cvmfs/container.ihep.ac.cn... OK
    A[blyth@localhost ~]$ 

    A[blyth@localhost ~]$ cat /etc/cvmfs/default.local
    CVMFS_REPOSITORIES='sft.cern.ch,juno.ihep.ac.cn,container.ihep.ac.cn'
    CVMFS_HTTP_PROXY=DIRECT


    A[blyth@localhost ~]$ sudo systemctl restart autofs
    A[blyth@localhost ~]$ 
    A[blyth@localhost ~]$ cd /cvmfs/opticks.ihep.ac.cn
    -bash: cd: /cvmfs/opticks.ihep.ac.cn: No such file or directory
    A[blyth@localhost ~]$ 





    P[blyth@localhost Latest]$ cat /etc/cvmfs/default.local
    CVMFS_REPOSITORIES='sft.cern.ch,juno.ihep.ac.cn,container.ihep.ac.cn'
    CVMFS_HTTP_PROXY=DIRECT



::

    A[blyth@localhost ~]$ cvmfs_config status
    cvmfs-config.cern.ch mounted on /cvmfs/cvmfs-config.cern.ch with pid 746063
    juno.ihep.ac.cn mounted on /cvmfs/juno.ihep.ac.cn with pid 746118
    sft.cern.ch mounted on /cvmfs/sft.cern.ch with pid 747131
    container.ihep.ac.cn mounted on /cvmfs/container.ihep.ac.cn with pid 747279




    P[blyth@localhost Latest]$ cvmfs_config probe
    Probing /cvmfs/sft.cern.ch... OK
    Probing /cvmfs/juno.ihep.ac.cn... OK
    Probing /cvmfs/container.ihep.ac.cn... OK
    P[blyth@localhost Latest]$ 



