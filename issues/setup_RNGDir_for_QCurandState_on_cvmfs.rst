setup_RNGDir_for_QCurandState_on_cvmfs
========================================


First update my RNGDir on lxslc7, adding the 50M file to the already 1,3,10M::

    N[blyth@localhost ~]$ M=50 ./rngscp.sh 

    scp .opticks/rngcache/RNG/QCurandState_50000000_0_0.bin L7:g/.opticks/rngcache/RNG/

    N[blyth@localhost ~]$ M=50 ./rngscp.sh | sh 
    Warning: Permanently added 'lxslc7.ihep.ac.cn,202.122.33.193' (ECDSA) to the list of known hosts.
    QCurandState_50000000_0_0.bin                                                                                                                               100% 2098MB  11.2MB/s   03:07    
    N[blyth@localhost ~]$ 



Then scp over from L7 to O (stratum-zero) RNG dir in home directory::

    L7[blyth@lxslc708 ~]$ M=50 ./rngscp_to_cvmfs_stratum_zero.sh

    scp .opticks/rngcache/RNG/QCurandState_50000000_0_0.bin O:RNG/

    L7[blyth@lxslc708 ~]$ M=50 ./rngscp_to_cvmfs_stratum_zero.sh | sh 
    Enter passphrase for key '/afs/ihep.ac.cn/users/b/blyth/.ssh/id_rsa': 
    QCurandState_50000000_0_0.bin                                                                                                                               100% 2098MB 104.8MB/s   00:20    
    L7[blyth@lxslc708 ~]$ M=10 ./rngscp_to_cvmfs_stratum_zero.sh | sh 
    Enter passphrase for key '/afs/ihep.ac.cn/users/b/blyth/.ssh/id_rsa': 
    QCurandState_10000000_0_0.bin                                                                                                                               100%  420MB  88.4MB/s   00:04    
    L7[blyth@lxslc708 ~]$ M=3 ./rngscp_to_cvmfs_stratum_zero.sh | sh 
    Enter passphrase for key '/afs/ihep.ac.cn/users/b/blyth/.ssh/id_rsa': 
    QCurandState_3000000_0_0.bin                                                                                                                                100%  126MB  69.9MB/s   00:01    
    L7[blyth@lxslc708 ~]$ M=1 ./rngscp_to_cvmfs_stratum_zero.sh | sh 
    Enter passphrase for key '/afs/ihep.ac.cn/users/b/blyth/.ssh/id_rsa': 
    QCurandState_1000000_0_0.bin                                                                                                                                100%   42MB  68.3MB/s   00:00    
    L7[blyth@lxslc708 ~]$ 



Then start transation and create RNG dir and move the above files into it::

    [optickspub@cvmfs-stratum-zero-b ~]$ cvmfs_server transaction opticks.ihep.ac.cn
    [optickspub@cvmfs-stratum-zero-b ~]$ mkdir -p /cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG


    [optickspub@cvmfs-stratum-zero-b ~]$ ls RNG/*
    RNG/QCurandState_10000000_0_0.bin  RNG/QCurandState_1000000_0_0.bin  RNG/QCurandState_3000000_0_0.bin  RNG/QCurandState_50000000_0_0.bin

    [optickspub@cvmfs-stratum-zero-b ~]$ mv RNG/* /cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG/


::

    [optickspub@cvmfs-stratum-zero-b ~]$ du -h /cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG/
    2.7G	/cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG/

    [optickspub@cvmfs-stratum-zero-b ~]$ du -h /cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG/*
    420M	/cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG/QCurandState_10000000_0_0.bin
    42M	/cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG/QCurandState_1000000_0_0.bin
    126M	/cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG/QCurandState_3000000_0_0.bin
    2.1G	/cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG/QCurandState_50000000_0_0.bin
    [optickspub@cvmfs-stratum-zero-b ~]$ 



::

    [optickspub@cvmfs-stratum-zero-b ~]$ cvmfs_server publish -m "setup shared /cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG for QCurandState files" opticks.ihep.ac.cn
    Using auto tag 'generic-2024-01-11T14:02:45Z'
    WARNING: cannot apply pathspec /software/*/*
    WARNING: cannot apply pathspec /software/*/*/*
    Processing changes...
    Waiting for upload of files before committing...
    WARNING: file at /.opticks/rngcache/RNG/QCurandState_50000000_0_0.bin is larger than 1024 megabytes (2098). CernVM-FS works best with small files. Please remove the file or increase the limit.
    Committing file catalogs...
    Wait for all uploads to finish
    Exporting repository manifest
    Statistics stored at: /var/spool/cvmfs/opticks.ihep.ac.cn/stats.db
    Tagging opticks.ihep.ac.cn
    Flushing file system buffers
    Signing new manifest
    Remounting newly created repository revision
    [optickspub@cvmfs-stratum-zero-b ~]$ 



Despite that big file warning the file appear to be there, as viewed from workstation::

    N[blyth@localhost RNG]$ du -hs *
    420M	QCurandState_10000000_0_0.bin
    42M	QCurandState_1000000_0_0.bin
    126M	QCurandState_3000000_0_0.bin
    2.1G	QCurandState_50000000_0_0.bin
    N[blyth@localhost RNG]$ pwd
    /cvmfs/opticks.ihep.ac.cn/.opticks/rngcache/RNG
    N[blyth@localhost RNG]$ 



