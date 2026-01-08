manual_cleanup
=================


Kill processes using cvmfs : especially those stuck in D state
---------------------------------------------------------------


::

    A[blyth@localhost junosw]$ ps aux | grep cvmfs
    root       15496  0.0  0.0 504948  2972 ?        D    11:17   0:02 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 juno.ihep.ac.cn /cvmfs/juno.ihep.ac.cn
    root       15511  0.0  0.0 222276  2688 ?        S    11:17   0:00 /usr/bin/mount -t cvmfs juno.ihep.ac.cn /cvmfs/juno.ihep.ac.cn
    root       15513  0.0  0.0  14692  5376 ?        S    11:17   0:06 /sbin/mount.cvmfs juno.ihep.ac.cn /cvmfs/juno.ihep.ac.cn -o rw
    cvmfs      15533  0.0  0.0  31448 16872 ?        D    11:17   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 juno.ihep.ac.cn /cvmfs/juno.ihep.ac.cn
    cvmfs      15563  0.0  0.0  17664  1796 ?        S    11:17   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 juno.ihep.ac.cn /cvmfs/juno.ihep.ac.cn
    cvmfs      16986  0.0  0.0  17668  1792 ?        S    11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    cvmfs      16988  0.0  0.0  29224 10752 ?        Sl   11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      16992  0.0  0.0  17556  1812 ?        S    11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      17000  0.0 11.0 34149484 29074920 ?   Sl   11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    root       91256 55.0  0.0 439408  3236 ?        D    13:38   0:02 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    root       91272  0.0  0.0 222276  2688 ?        S    13:38   0:00 /usr/bin/mount -t cvmfs opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    root       91273  0.0  0.0  14692  5824 ?        S    13:38   0:00 /sbin/mount.cvmfs opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn -o rw
    cvmfs      91295 91.0  4.0 33587948 10751428 ?   R    13:38   0:01 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    cvmfs      91329  0.0  0.0  17664  1816 ?        S    13:38   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    blyth      91334  0.0  0.0 221800  2240 pts/19   S+   13:38   0:00 grep --color=auto cvmfs
    A[blyth@localhost junosw]$ sudo kill -9 15496 15511 15513 15533 15563
    [sudo] password for blyth: 
    A[blyth@localhost junosw]$ ps aux | grep cvmfs
    cvmfs      16986  0.0  0.0  17668  1792 ?        S    11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    cvmfs      16988  0.0  0.0  29224 10752 ?        Sl   11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      16992  0.0  0.0  17556  1812 ?        S    11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      17000  0.0 11.0 34149484 29074920 ?   Sl   11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    root       92230 54.5  0.0 439412  3440 ?        D    13:39   0:02 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    root       92244  0.0  0.0 222276  2688 ?        S    13:39   0:00 /usr/bin/mount -t cvmfs opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    root       92245  0.0  0.0  14692  5824 ?        S    13:39   0:00 /sbin/mount.cvmfs opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn -o rw
    cvmfs      92268  0.0  0.0  31448 16180 ?        D    13:39   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    cvmfs      92302  0.0  0.0  17664  1792 ?        S    13:39   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    blyth      92308  0.0  0.0 221800  2240 pts/19   S+   13:40   0:00 grep --color=auto cvmfs
    A[blyth@localhost junosw]$ sudo kill -9 92244 92245 92268  92302
    A[blyth@localhost junosw]$ ps aux | grep cvmfs
    cvmfs      16986  0.0  0.0  17668  1792 ?        S    11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    cvmfs      16988  0.0  0.0  29224 10752 ?        Sl   11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      16992  0.0  0.0  17556  1812 ?        S    11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      17000  0.0 11.0 34149484 29074920 ?   Sl   11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    blyth      92360  0.0  0.0 221800  2240 pts/19   S+   13:40   0:00 grep --color=auto cvmfs
    A[blyth@localhost junosw]$ 



Lazy unmounts
---------------

::

    sudo umount -l /cvmfs/juno.ihep.ac.cn
    sudo umount -l /cvmfs/opticks.ihep.ac.cn


Kill any remaining cvmfs processes
------------------------------------


::

    A[blyth@localhost junosw]$ ps aux | grep cvmfs
    cvmfs      16986  0.0  0.0  17668  1792 ?        S    11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    cvmfs      16988  0.0  0.0  29224 10752 ?        Sl   11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      16992  0.0  0.0  17556  1812 ?        S    11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      17000  0.0 11.0 34149484 29074920 ?   Sl   11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    blyth      92585  0.0  0.0 221800  2240 pts/19   S+   13:44   0:00 grep --color=auto cvmfs
    A[blyth@localhost junosw]$ 


    A[blyth@localhost junosw]$ ps aux | grep cvmfs
    cvmfs      16986  0.0  0.0  17668  1792 ?        S    11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    cvmfs      16988  0.0  0.0  29224 10752 ?        Sl   11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      16992  0.0  0.0  17556  1812 ?        S    11:35   0:00 /usr/bin/cvmfs2 __cachemgr__ . 10 11 209715200000 104857600000 1 3 -1 :
    cvmfs      17000  0.0 11.0 34149484 29074920 ?   Sl   11:35   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 cvmfs-config.cern.ch /cvmfs/cvmfs-config.cern.ch
    blyth      92585  0.0  0.0 221800  2240 pts/19   S+   13:44   0:00 grep --color=auto cvmfs
    A[blyth@localhost junosw]$ sudo kill -9 16986 16988 16992 17000
    A[blyth@localhost junosw]$ ps aux | grep cvmfs
    blyth      92666  0.0  0.0 221668  2240 pts/19   S+   13:45   0:00 grep --color=auto cvmfs
    A[blyth@localhost junosw]$ 



restart autofs
----------------

::

    sudo systemctl restart autofs

    A[blyth@localhost junosw]$ sudo systemctl restart autofs
    A[blyth@localhost junosw]$ sudo systemctl status autofs
    ● autofs.service - Automounts filesystems on demand
         Loaded: loaded (/usr/lib/systemd/system/autofs.service; enabled; preset: disabled)
        Drop-In: /usr/lib/systemd/system/autofs.service.d
                 └─50-cvmfs.conf
         Active: active (running) since Thu 2026-01-08 13:46:33 CST; 7s ago
       Main PID: 92726 (automount)
          Tasks: 7 (limit: 1638992)
         Memory: 2.5M
            CPU: 23ms
         CGroup: /system.slice/autofs.service
                 └─92726 /usr/sbin/automount --systemd-service --dont-check-daemon

    Jan 08 13:46:33 localhost.localdomain systemd[1]: Starting Automounts filesystems on demand...
    Jan 08 13:46:33 localhost.localdomain automount[92726]: setautomntent: lookup(sss): setautomountent: entry for map auto.master not found
    Jan 08 13:46:33 localhost.localdomain automount[92726]: setautomntent: lookup(sss): setautomountent: entry for map auto_master not found
    Jan 08 13:46:33 localhost.localdomain automount[92726]: setautomntent: lookup(sss): setautomountent: entry for map auto.master not found
    Jan 08 13:46:33 localhost.localdomain systemd[1]: Started Automounts filesystems on demand.
    A[blyth@localhost junosw]$ 



try access
------------

::

    A[blyth@localhost junosw]$ ls -alst /cvmfs/opticks.ihep.ac.cn
    total 8
    1 drwxrwxr-x. 6 cvmfs cvmfs  231 Jun  6  2025 external
    1 drwxrwxr-x. 3 cvmfs cvmfs   30 Jun  6  2025 oj
    1 drwxrwxr-x. 3 cvmfs cvmfs   30 Jun  6  2025 ok
    1 drwxrwxr-x. 5 cvmfs cvmfs   35 Jun  6  2025 .opticks
    1 drwxrwxr-x. 6 cvmfs cvmfs  111 Jun  6  2025 opticks_download_cache
    1 -rw-rw-r--. 1 cvmfs cvmfs   24 Jun  6  2025 .cvmfsdirtab
    1 -rw-r--r--. 1 cvmfs cvmfs   48 Apr 25  2019 new_repository
    5 drwxr-xr-x. 7 cvmfs cvmfs 4096 Apr 25  2019 .

    A[blyth@localhost junosw]$ ls -alst /cvmfs/juno.ihep.ac.cn
    total 14
    1 drwxrwxr-x.  3 cvmfs cvmfs   26 Dec 25 19:22 tao-dbdata
    1 -rw-rw-r--.  1 cvmfs cvmfs  128 Jul 10 18:22 .cvmfsdirtab
    1 drwxrwxr-x.  5 cvmfs cvmfs   29 Jul 10 18:06 el9_amd64_gcc11
    1 drwxrwxr-x.  4 cvmfs cvmfs   28 Jun 28  2025 singularity
    1 drwxrwxr-x.  3 cvmfs cvmfs   26 Feb  3  2025 dbdata
    1 drwxr-xr-x.  9 cvmfs cvmfs   75 Dec 11  2024 docutil
    1 drwxrwxr-x.  5 cvmfs cvmfs   29 Jun 13  2024 centos7_amd64_gcc1120
    1 drwxrwxr-x.  7 cvmfs cvmfs   30 Jan  5  2024 sw
    1 drwxrwxr-x.  3 cvmfs cvmfs   33 Dec 18  2023 centos7_amd64_gcc1120_opticks
    1 drwxrwxr-x.  4 cvmfs cvmfs   29 Dec  1  2021 centos7_amd64_gcc830
    1 drwxrwxr-x.  3 cvmfs cvmfs   33 Jun  4  2020 sl7_amd64_gcc485
    1 drwxrwxr-x.  4 cvmfs cvmfs   28 Jun  2  2020 ci
    1 drwxrwxr-x.  4 cvmfs cvmfs   52 May 13  2020 sl6_amd64_gcc447
    1 drwxrwxr-x.  4 cvmfs cvmfs   29 Apr 28  2020 sl6_amd64_gcc830
    1 drwxrwxr-x.  4 cvmfs cvmfs   29 Nov 27  2019 sl6_amd64_gcc494
    1 drwxrwxr-x.  9 cvmfs cvmfs  162 Jun 28  2019 sl6_amd64_gcc44
    1 drwxrwxr-x.  3 cvmfs cvmfs   29 Jun 25  2019 sl7_amd64_gcc48
    1 drwxrwxr-x.  4 cvmfs cvmfs   58 Mar 22  2017 sl5_amd64_gcc41
    1 -rw-r--r--.  1 cvmfs cvmfs   45 Mar 27  2015 new_repository
    5 drwxr-xr-x. 19 cvmfs cvmfs 4096 Mar 27  2015 .
    A[blyth@localhost junosw]$ 
         

check processes
-----------------

::

    A[blyth@localhost junosw]$ ps aux | grep cvmfs
    cvmfs      92850  0.0  0.0  17664  1792 ?        S    13:47   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    cvmfs      92852  0.4  0.0  31872 10752 ?        Sl   13:47   0:00 /usr/bin/cvmfs2 __cachemgr__ . 11 12 209715200000 104857600000 1 3 -1 :
    cvmfs      92856  0.0  0.0  17556  1812 ?        S    13:47   0:00 /usr/bin/cvmfs2 __cachemgr__ . 11 12 209715200000 104857600000 1 3 -1 :
    cvmfs      92866  0.0 11.0 34083932 29074584 ?   Sl   13:47   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 opticks.ihep.ac.cn /cvmfs/opticks.ihep.ac.cn
    cvmfs      92940  0.0  0.0  17668  1796 ?        S    13:47   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 juno.ihep.ac.cn /cvmfs/juno.ihep.ac.cn
    cvmfs      92945  0.0 11.0 34083936 29074472 ?   Sl   13:47   0:00 /usr/bin/cvmfs2 -o rw,system_mount,fsname=cvmfs2,allow_other,grab_mountpoint,uid=975,gid=975 juno.ihep.ac.cn /cvmfs/juno.ihep.ac.cn
    blyth      92993  0.0  0.0 221668  2240 pts/19   S+   13:48   0:00 grep --color=auto cvmfs
    A[blyth@localhost junosw]$ 


