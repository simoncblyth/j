juno-offline-reinstall-july6-2021
===================================

Summary
--------

* need to adjust Geant4 build ``-DGEANT4_BUILD_MULTITHREADED=OFF`` 

  * are trying to match against Geant4 so clearly cannot be multithreaded

* Offline has many PMTSvc changes now, so currently just using placeholders
  for PMT info collected by Opticks

  * so the angular efficiencies need work 







Steps
------

Following a failed in-situ update attempt to reinstall into old JUNOTOP /home/blyth/junotop
that ran out of disk space try again into a fresh JUNOTOP /data/blyth/junotop

Following 

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation


Use mode O::

    epsilon:~ blyth$ O
    Last login: Tue Jul  6 17:28:18 2021 from lxslc711.ihep.ac.cn
    mo .bashrc OPTICKS_MODE:dev O : ordinary opticks dev ontop of juno externals CMTEXTRATAGS:
    O[blyth@localhost ~]$ 


    O[blyth@localhost ~]$ jt
    /data/blyth/junotop
    O[blyth@localhost junotop]$ svn co https://juno.ihep.ac.cn/svn/offline/trunk/installation/junoenv
    ...   
    Checked out revision 4802.
    O[blyth@localhost junotop]$ je
    /data/blyth/junotop/junoenv

    O[blyth@localhost junoenv]$ bash junoenv preq
    = The junoenv is in /data/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /data/blyth/junotop
    = THE JUNOENVDIR is /data/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: ""
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: ""
    == setup-juno-basic-preq: ================================================================
    [sudo] password for blyth: 
    == setup-juno-preq:
    === junoenv-preq: Auto Detect Distro: centos
    ==== junoenv-preq-check-os: check the os
    ==== junoenv-preq-check-os-centos: OS version: 7.6.1810

    Dependencies Resolved

    =======================================================================================================================================================================================================
     Package                                              Arch                                      Version                                               Repository                                  Size
    =======================================================================================================================================================================================================
    Updating:
     binutils                                             x86_64                                    2.27-44.base.el7                                      base                                       5.9 M
     curl                                                 x86_64                                    7.29.0-59.el7_9.1                                     updates                                    271 k
     gcc                                                  x86_64                                    4.8.5-44.el7                                          base                                        16 M
     gcc-c++                                              x86_64                                    4.8.5-44.el7                                          base                                       7.2 M
     gcc-gfortran                                         x86_64                                    4.8.5-44.el7                                          base                                       6.7 M
     git                                                  x86_64                                    1.8.3.1-23.el7_8                                      base                                       4.4 M
     graphviz-devel                                       x86_64                                    2.30.1-22.el7                                         base                                        83 k
     libX11-devel                                         x86_64                                    1.6.7-3.el7_9                                         updates                                    981 k
     libcurl-devel                                        x86_64                                    7.29.0-59.el7_9.1                                     updates                                    303 k
     libxml2-devel                                        x86_64                                    2.9.1-6.el7.5                                         base                                       1.1 M
     mariadb-devel                                        x86_64                                    1:5.5.68-1.el7                                        base                                       757 k
     mesa-libGL-devel                                     x86_64                                    18.3.4-12.el7_9                                       updates                                    164 k
     openldap-devel                                       x86_64                                    2.4.44-23.el7_9                                       updates                                    804 k
     openssl-devel                                        x86_64                                    1:1.0.2k-21.el7_9                                     updates                                    1.5 M
     python-devel                                         x86_64                                    2.7.5-90.el7                                          updates                                    399 k
     qt-devel                                             x86_64                                    1:4.8.7-9.el7_9                                       updates                                     11 M
     unzip                                                x86_64                                    6.0-22.el7_9                                          updates                                    171 k
    Updating for dependencies:
     cpp                                                  x86_64                                    4.8.5-44.el7                                          base                                       5.9 M
     gcc-objc                                             x86_64                                    4.8.5-44.el7                                          base                                       5.7 M
     graphviz                                             x86_64                                    2.30.1-22.el7                                         base                                       1.3 M
     graphviz-gd                                          x86_64                                    2.30.1-22.el7                                         base                                        33 k
     libX11                                               x86_64                                    1.6.7-3.el7_9                                         updates                                    607 k
     libX11-common                                        noarch                                    1.6.7-3.el7_9                                         updates                                    164 k
     libcurl                                              x86_64                                    7.29.0-59.el7_9.1                                     updates                                    223 k
     libgcc                                               i686                                      4.8.5-44.el7                                          base                                       111 k
     libgcc                                               x86_64                                    4.8.5-44.el7                                          base                                       103 k
     libgfortran                                          x86_64                                    4.8.5-44.el7                                          base                                       301 k
     libgomp                                              x86_64                                    4.8.5-44.el7                                          base                                       159 k
     libobjc                                              x86_64                                    4.8.5-44.el7                                          base                                        80 k
     libquadmath                                          x86_64                                    4.8.5-44.el7                                          base                                       190 k
     libquadmath-devel                                    x86_64                                    4.8.5-44.el7                                          base                                        54 k
     libstdc++                                            i686                                      4.8.5-44.el7                                          base                                       319 k
     libstdc++                                            x86_64                                    4.8.5-44.el7                                          base                                       306 k
     libstdc++-devel                                      x86_64                                    4.8.5-44.el7                                          base                                       1.5 M
     libxml2                                              x86_64                                    2.9.1-6.el7.5                                         base                                       668 k
     libxml2-python                                       x86_64                                    2.9.1-6.el7.5                                         base                                       247 k
     mariadb-libs                                         x86_64                                    1:5.5.68-1.el7                                        base                                       760 k
     mesa-khr-devel                                       x86_64                                    18.3.4-12.el7_9                                       updates                                     20 k
     mesa-libEGL                                          x86_64                                    18.3.4-12.el7_9                                       updates                                    110 k
     mesa-libEGL-devel                                    x86_64                                    18.3.4-12.el7_9                                       updates                                     33 k
     mesa-libGL                                           x86_64                                    18.3.4-12.el7_9                                       updates                                    166 k
     mesa-libGLES                                         x86_64                                    18.3.4-12.el7_9                                       updates                                     16 k
     mesa-libgbm                                          x86_64                                    18.3.4-12.el7_9                                       updates                                     39 k
     mesa-libglapi                                        x86_64                                    18.3.4-12.el7_9                                       updates                                     46 k
     openldap                                             x86_64                                    2.4.44-23.el7_9                                       updates                                    356 k
     openssl                                              x86_64                                    1:1.0.2k-21.el7_9                                     updates                                    493 k
     openssl-libs                                         x86_64                                    1:1.0.2k-21.el7_9                                     updates                                    1.2 M
     perl-Git                                             noarch                                    1.8.3.1-23.el7_8                                      base                                        56 k
     python                                               x86_64                                    2.7.5-90.el7                                          updates                                     96 k
     python-libs                                          x86_64                                    2.7.5-90.el7                                          updates                                    5.6 M
     qt                                                   x86_64                                    1:4.8.7-9.el7_9                                       updates                                    4.6 M
     qt-x11                                               x86_64                                    1:4.8.7-9.el7_9                                       updates                                     13 M

    Transaction Summary
    =======================================================================================================================================================================================================
    Upgrade  17 Packages (+35 Dependent packages)

    Total size: 101 M
    Is this ok [y/d/N]: y
    Downloading packages:
    Running transaction check
    Running transaction test
    Transaction test succeeded
    Running transaction
      Updating   : libgcc-4.8.5-44.el7.x86_64                                                                                                                                                        1/104 
      Updating   : libstdc++-4.8.5-44.el7.x86_64                                                                                                                                                     2/104 
      Updating   : 1:openssl-libs-1.0.2k-21.el7_9.x86_64                                                                                                                                             3/104 
      Updating   : mesa-libglapi-18.3.4-12.el7_9.x86_64                                                                                                                                              4/104 
      Updating   : python-libs-2.7.5-90.el7.x86_64                                                                                                                                                   5/104 
      Updating   : python-2.7.5-90.el7.x86_64                                                                                                                                                        6/104 
      Updating   : libquadmath-4.8.5-44.el7.x86_64                                                                                                                                                   7/104 
      Updating   : 1:qt-4.8.7-9.el7_9.x86_64                                                                                                                                                         8/104 
      Updating   : openldap-2.4.44-23.el7_9.x86_64                                                                                                                                                   9/104 
      Updating   : libcurl-7.29.0-59.el7_9.1.x86_64                                                                                                                                                 10/104 
      Updating   : mesa-khr-devel-18.3.4-12.el7_9.x86_64                                                                                                                                            11/104 
      Updating   : libxml2-2.9.1-6.el7.5.x86_64                                                                                                                                                     12/104 
      Updating   : perl-Git-1.8.3.1-23.el7_8.noarch                                                                                                                                                 13/104 
      Updating   : git-1.8.3.1-23.el7_8.x86_64                                                                                                                                                      14/104 
      Updating   : libgfortran-4.8.5-44.el7.x86_64                                                                                                                                                  15/104 
      Updating   : mesa-libgbm-18.3.4-12.el7_9.x86_64                                                                                                                                               16/104 
      Updating   : 1:mariadb-libs-5.5.68-1.el7.x86_64                                                                                                                                               17/104 
      Updating   : 1:openssl-devel-1.0.2k-21.el7_9.x86_64                                                                                                                                           18/104 
      Updating   : libstdc++-devel-4.8.5-44.el7.x86_64                                                                                                                                              19/104 
      Updating   : libobjc-4.8.5-44.el7.x86_64                                                                                                                                                      20/104 
      Updating   : binutils-2.27-44.base.el7.x86_64                                                                                                                                                 21/104 
      Updating   : libgomp-4.8.5-44.el7.x86_64                                                                                                                                                      22/104 
      Updating   : libX11-common-1.6.7-3.el7_9.noarch                                                                                                                                               23/104 
      Updating   : libX11-1.6.7-3.el7_9.x86_64                                                                                                                                                      24/104 
      Updating   : libX11-devel-1.6.7-3.el7_9.x86_64                                                                                                                                                25/104 
      Updating   : graphviz-2.30.1-22.el7.x86_64                                                                                                                                                    26/104 
      Updating   : graphviz-gd-2.30.1-22.el7.x86_64                                                                                                                                                 27/104 
      Updating   : mesa-libGL-18.3.4-12.el7_9.x86_64                                                                                                                                                28/104 
      Updating   : mesa-libGL-devel-18.3.4-12.el7_9.x86_64                                                                                                                                          29/104 
      Updating   : mesa-libEGL-18.3.4-12.el7_9.x86_64                                                                                                                                               30/104 
      Updating   : 1:qt-x11-4.8.7-9.el7_9.x86_64                                                                                                                                                    31/104 
      Updating   : cpp-4.8.5-44.el7.x86_64                                                                                                                                                          32/104 
      Updating   : gcc-4.8.5-44.el7.x86_64                                                                                                                                                          33/104 
      Updating   : libquadmath-devel-4.8.5-44.el7.x86_64                                                                                                                                            34/104 
      Updating   : libgcc-4.8.5-44.el7.i686                                                                                                                                                         35/104 
      Updating   : gcc-gfortran-4.8.5-44.el7.x86_64                                                                                                                                                 36/104 
      Updating   : gcc-c++-4.8.5-44.el7.x86_64                                                                                                                                                      37/104 
      Updating   : gcc-objc-4.8.5-44.el7.x86_64                                                                                                                                                     38/104 
      Updating   : 1:qt-devel-4.8.7-9.el7_9.x86_64                                                                                                                                                  39/104 
      Updating   : mesa-libEGL-devel-18.3.4-12.el7_9.x86_64                                                                                                                                         40/104 
      Updating   : graphviz-devel-2.30.1-22.el7.x86_64                                                                                                                                              41/104 
      Updating   : 1:mariadb-devel-5.5.68-1.el7.x86_64                                                                                                                                              42/104 
      Updating   : libxml2-python-2.9.1-6.el7.5.x86_64                                                                                                                                              43/104 
      Updating   : libxml2-devel-2.9.1-6.el7.5.x86_64                                                                                                                                               44/104 
      Updating   : curl-7.29.0-59.el7_9.1.x86_64                                                                                                                                                    45/104 
      Updating   : libcurl-devel-7.29.0-59.el7_9.1.x86_64                                                                                                                                           46/104 
      Updating   : openldap-devel-2.4.44-23.el7_9.x86_64                                                                                                                                            47/104 
      Updating   : python-devel-2.7.5-90.el7.x86_64                                                                                                                                                 48/104 
      Updating   : mesa-libGLES-18.3.4-12.el7_9.x86_64                                                                                                                                              49/104 
      Updating   : 1:openssl-1.0.2k-21.el7_9.x86_64                                                                                                                                                 50/104 
      Updating   : unzip-6.0-22.el7_9.x86_64                                                                                                                                                        51/104 
      Updating   : libstdc++-4.8.5-44.el7.i686                                                                                                                                                      52/104 
      Cleanup    : 1:qt-devel-4.8.7-8.el7.x86_64                                                                                                                                                    53/104 
      Cleanup    : graphviz-devel-2.30.1-21.el7.x86_64                                                                                                                                              54/104 
      Cleanup    : 1:qt-x11-4.8.7-8.el7.x86_64                                                                                                                                                      55/104 
      Cleanup    : perl-Git-1.8.3.1-22.el7_8.noarch                                                                                                                                                 56/104 
      Cleanup    : git-1.8.3.1-22.el7_8.x86_64                                                                                                                                                      57/104 
      Cleanup    : mesa-libGL-devel-18.3.4-7.el7.x86_64                                                                                                                                             58/104 
      Cleanup    : 1:qt-4.8.7-8.el7.x86_64                                                                                                                                                          59/104 
      Cleanup    : gcc-gfortran-4.8.5-39.el7.x86_64                                                                                                                                                 60/104 
      Cleanup    : libxml2-python-2.9.1-6.el7.4.x86_64                                                                                                                                              61/104 
      Cleanup    : gcc-c++-4.8.5-39.el7.x86_64                                                                                                                                                      62/104 
      Cleanup    : mesa-libEGL-devel-18.3.4-7.el7.x86_64                                                                                                                                            63/104 
      Cleanup    : python-devel-2.7.5-88.el7.x86_64                                                                                                                                                 64/104 
      Cleanup    : libquadmath-devel-4.8.5-39.el7.x86_64                                                                                                                                            65/104 
      Cleanup    : libxml2-devel-2.9.1-6.el7.4.x86_64                                                                                                                                               66/104 
      Cleanup    : 1:mariadb-devel-5.5.65-1.el7.x86_64                                                                                                                                              67/104 
      Cleanup    : 1:openssl-devel-1.0.2k-19.el7.x86_64                                                                                                                                             68/104 
      Cleanup    : libX11-devel-1.6.7-2.el7.x86_64                                                                                                                                                  69/104 
      Cleanup    : libstdc++-devel-4.8.5-39.el7.x86_64                                                                                                                                              70/104 
      Cleanup    : mesa-libGLES-18.3.4-7.el7.x86_64                                                                                                                                                 71/104 
      Cleanup    : libcurl-devel-7.29.0-57.el7.x86_64                                                                                                                                               72/104 
      Cleanup    : openldap-devel-2.4.44-21.el7_6.x86_64                                                                                                                                            73/104 
      Cleanup    : libstdc++-4.8.5-39.el7                                                                                                                                                           74/104 
      Cleanup    : mesa-libEGL-18.3.4-7.el7.x86_64                                                                                                                                                  75/104 
      Cleanup    : graphviz-gd-2.30.1-21.el7.x86_64                                                                                                                                                 76/104 
      Cleanup    : graphviz-2.30.1-21.el7.x86_64                                                                                                                                                    77/104 
      Cleanup    : 1:mariadb-libs-5.5.65-1.el7.x86_64                                                                                                                                               78/104 
      Cleanup    : libgfortran-4.8.5-39.el7.x86_64                                                                                                                                                  79/104 
      Cleanup    : mesa-libGL-18.3.4-7.el7.x86_64                                                                                                                                                   80/104 
      Cleanup    : gcc-objc-4.8.5-39.el7.x86_64                                                                                                                                                     81/104 
      Cleanup    : gcc-4.8.5-39.el7.x86_64                                                                                                                                                          82/104 
      Cleanup    : libobjc-4.8.5-39.el7.x86_64                                                                                                                                                      83/104 
      Cleanup    : libX11-1.6.7-2.el7.x86_64                                                                                                                                                        84/104 
      Cleanup    : libstdc++-4.8.5-39.el7                                                                                                                                                           85/104 
      Cleanup    : mesa-libgbm-18.3.4-7.el7.x86_64                                                                                                                                                  86/104 
      Cleanup    : python-2.7.5-88.el7.x86_64                                                                                                                                                       87/104 
      Cleanup    : python-libs-2.7.5-88.el7.x86_64                                                                                                                                                  88/104 
      Cleanup    : curl-7.29.0-57.el7.x86_64                                                                                                                                                        89/104 
      Cleanup    : libcurl-7.29.0-57.el7.x86_64                                                                                                                                                     90/104 
      Cleanup    : openldap-2.4.44-21.el7_6.x86_64                                                                                                                                                  91/104 
      Cleanup    : 1:openssl-1.0.2k-19.el7.x86_64                                                                                                                                                   92/104 
      Cleanup    : libX11-common-1.6.7-2.el7.noarch                                                                                                                                                 93/104 
      Cleanup    : libgcc-4.8.5-39.el7                                                                                                                                                              94/104 
      Cleanup    : mesa-khr-devel-18.3.4-7.el7.x86_64                                                                                                                                               95/104 
      Cleanup    : 1:openssl-libs-1.0.2k-19.el7.x86_64                                                                                                                                              96/104 
      Cleanup    : mesa-libglapi-18.3.4-7.el7.x86_64                                                                                                                                                97/104 
      Cleanup    : libgcc-4.8.5-39.el7                                                                                                                                                              98/104 
      Cleanup    : binutils-2.27-43.base.el7.x86_64                                                                                                                                                 99/104 
      Cleanup    : cpp-4.8.5-39.el7.x86_64                                                                                                                                                         100/104 
      Cleanup    : libgomp-4.8.5-39.el7.x86_64                                                                                                                                                     101/104 
      Cleanup    : libquadmath-4.8.5-39.el7.x86_64                                                                                                                                                 102/104 
      Cleanup    : libxml2-2.9.1-6.el7.4.x86_64                                                                                                                                                    103/104 
      Cleanup    : unzip-6.0-21.el7.x86_64                                                                                                                                                         104/104 
      Verifying  : gcc-c++-4.8.5-44.el7.x86_64                                                                                                                                                       1/104 
      Verifying  : 1:qt-devel-4.8.7-9.el7_9.x86_64                                                                                                                                                   2/104 
      Verifying  : git-1.8.3.1-23.el7_8.x86_64                                                                                                                                                       3/104 
      Verifying  : libgcc-4.8.5-44.el7.i686                                                                                                                                                          4/104 
      Verifying  : cpp-4.8.5-44.el7.x86_64                                                                                                                                                           5/104 
      Verifying  : 1:openssl-1.0.2k-21.el7_9.x86_64                                                                                                                                                  6/104 
      Verifying  : 1:mariadb-libs-5.5.68-1.el7.x86_64                                                                                                                                                7/104 
      Verifying  : mesa-libgbm-18.3.4-12.el7_9.x86_64                                                                                                                                                8/104 
      Verifying  : graphviz-gd-2.30.1-22.el7.x86_64                                                                                                                                                  9/104 
      Verifying  : libX11-common-1.6.7-3.el7_9.noarch                                                                                                                                               10/104 
      Verifying  : libX11-1.6.7-3.el7_9.x86_64                                                                                                                                                      11/104 
      Verifying  : libcurl-7.29.0-59.el7_9.1.x86_64                                                                                                                                                 12/104 
      Verifying  : libstdc++-4.8.5-44.el7.i686                                                                                                                                                      13/104 
      Verifying  : 1:openssl-libs-1.0.2k-21.el7_9.x86_64                                                                                                                                            14/104 
      Verifying  : mesa-libGL-devel-18.3.4-12.el7_9.x86_64                                                                                                                                          15/104 
      Verifying  : libxml2-python-2.9.1-6.el7.5.x86_64                                                                                                                                              16/104 
      Verifying  : python-libs-2.7.5-90.el7.x86_64                                                                                                                                                  17/104 
      Verifying  : perl-Git-1.8.3.1-23.el7_8.noarch                                                                                                                                                 18/104 
      Verifying  : libobjc-4.8.5-44.el7.x86_64                                                                                                                                                      19/104 
      Verifying  : openldap-devel-2.4.44-23.el7_9.x86_64                                                                                                                                            20/104 
      Verifying  : libgcc-4.8.5-44.el7.x86_64                                                                                                                                                       21/104 
      Verifying  : python-devel-2.7.5-90.el7.x86_64                                                                                                                                                 22/104 
      Verifying  : mesa-libGL-18.3.4-12.el7_9.x86_64                                                                                                                                                23/104 
      Verifying  : libgfortran-4.8.5-44.el7.x86_64                                                                                                                                                  24/104 
      Verifying  : mesa-libEGL-devel-18.3.4-12.el7_9.x86_64                                                                                                                                         25/104 
      Verifying  : curl-7.29.0-59.el7_9.1.x86_64                                                                                                                                                    26/104 
      Verifying  : 1:qt-4.8.7-9.el7_9.x86_64                                                                                                                                                        27/104 
      Verifying  : libquadmath-devel-4.8.5-44.el7.x86_64                                                                                                                                            28/104 
      Verifying  : libgomp-4.8.5-44.el7.x86_64                                                                                                                                                      29/104 
      Verifying  : python-2.7.5-90.el7.x86_64                                                                                                                                                       30/104 
      Verifying  : binutils-2.27-44.base.el7.x86_64                                                                                                                                                 31/104 
      Verifying  : libX11-devel-1.6.7-3.el7_9.x86_64                                                                                                                                                32/104 
      Verifying  : libxml2-2.9.1-6.el7.5.x86_64                                                                                                                                                     33/104 
      Verifying  : openldap-2.4.44-23.el7_9.x86_64                                                                                                                                                  34/104 
      Verifying  : gcc-4.8.5-44.el7.x86_64                                                                                                                                                          35/104 
      Verifying  : libcurl-devel-7.29.0-59.el7_9.1.x86_64                                                                                                                                           36/104 
      Verifying  : unzip-6.0-22.el7_9.x86_64                                                                                                                                                        37/104 
      Verifying  : mesa-libGLES-18.3.4-12.el7_9.x86_64                                                                                                                                              38/104 
      Verifying  : 1:mariadb-devel-5.5.68-1.el7.x86_64                                                                                                                                              39/104 
      Verifying  : libstdc++-4.8.5-44.el7.x86_64                                                                                                                                                    40/104 
      Verifying  : graphviz-2.30.1-22.el7.x86_64                                                                                                                                                    41/104 
      Verifying  : mesa-libEGL-18.3.4-12.el7_9.x86_64                                                                                                                                               42/104 
      Verifying  : gcc-gfortran-4.8.5-44.el7.x86_64                                                                                                                                                 43/104 
      Verifying  : gcc-objc-4.8.5-44.el7.x86_64                                                                                                                                                     44/104 
      Verifying  : mesa-khr-devel-18.3.4-12.el7_9.x86_64                                                                                                                                            45/104 
      Verifying  : libquadmath-4.8.5-44.el7.x86_64                                                                                                                                                  46/104 
      Verifying  : libxml2-devel-2.9.1-6.el7.5.x86_64                                                                                                                                               47/104 
      Verifying  : 1:qt-x11-4.8.7-9.el7_9.x86_64                                                                                                                                                    48/104 
      Verifying  : mesa-libglapi-18.3.4-12.el7_9.x86_64                                                                                                                                             49/104 
      Verifying  : 1:openssl-devel-1.0.2k-21.el7_9.x86_64                                                                                                                                           50/104 
      Verifying  : libstdc++-devel-4.8.5-44.el7.x86_64                                                                                                                                              51/104 
      Verifying  : graphviz-devel-2.30.1-22.el7.x86_64                                                                                                                                              52/104 
      Verifying  : mesa-libEGL-devel-18.3.4-7.el7.x86_64                                                                                                                                            53/104 
      Verifying  : python-2.7.5-88.el7.x86_64                                                                                                                                                       54/104 
      Verifying  : libquadmath-devel-4.8.5-39.el7.x86_64                                                                                                                                            55/104 
      Verifying  : gcc-4.8.5-39.el7.x86_64                                                                                                                                                          56/104 
      Verifying  : libxml2-python-2.9.1-6.el7.4.x86_64                                                                                                                                              57/104 
      Verifying  : gcc-objc-4.8.5-39.el7.x86_64                                                                                                                                                     58/104 
      Verifying  : git-1.8.3.1-22.el7_8.x86_64                                                                                                                                                      59/104 
      Verifying  : mesa-libgbm-18.3.4-7.el7.x86_64                                                                                                                                                  60/104 
      Verifying  : mesa-libglapi-18.3.4-7.el7.x86_64                                                                                                                                                61/104 
      Verifying  : 1:mariadb-devel-5.5.65-1.el7.x86_64                                                                                                                                              62/104 
      Verifying  : mesa-libGL-18.3.4-7.el7.x86_64                                                                                                                                                   63/104 
      Verifying  : unzip-6.0-21.el7.x86_64                                                                                                                                                          64/104 
      Verifying  : mesa-libGLES-18.3.4-7.el7.x86_64                                                                                                                                                 65/104 
      Verifying  : 1:qt-devel-4.8.7-8.el7.x86_64                                                                                                                                                    66/104 
      Verifying  : 1:openssl-libs-1.0.2k-19.el7.x86_64                                                                                                                                              67/104 
      Verifying  : libgcc-4.8.5-39.el7.i686                                                                                                                                                         68/104 
      Verifying  : graphviz-gd-2.30.1-21.el7.x86_64                                                                                                                                                 69/104 
      Verifying  : mesa-libGL-devel-18.3.4-7.el7.x86_64                                                                                                                                             70/104 
      Verifying  : libgfortran-4.8.5-39.el7.x86_64                                                                                                                                                  71/104 
      Verifying  : libxml2-devel-2.9.1-6.el7.4.x86_64                                                                                                                                               72/104 
      Verifying  : libcurl-devel-7.29.0-57.el7.x86_64                                                                                                                                               73/104 
      Verifying  : libstdc++-4.8.5-39.el7.x86_64                                                                                                                                                    74/104 
      Verifying  : graphviz-devel-2.30.1-21.el7.x86_64                                                                                                                                              75/104 
      Verifying  : libobjc-4.8.5-39.el7.x86_64                                                                                                                                                      76/104 
      Verifying  : python-libs-2.7.5-88.el7.x86_64                                                                                                                                                  77/104 
      Verifying  : gcc-c++-4.8.5-39.el7.x86_64                                                                                                                                                      78/104 
      Verifying  : 1:openssl-1.0.2k-19.el7.x86_64                                                                                                                                                   79/104 
      Verifying  : mesa-khr-devel-18.3.4-7.el7.x86_64                                                                                                                                               80/104 
      Verifying  : python-devel-2.7.5-88.el7.x86_64                                                                                                                                                 81/104 
      Verifying  : libxml2-2.9.1-6.el7.4.x86_64                                                                                                                                                     82/104 
      Verifying  : cpp-4.8.5-39.el7.x86_64                                                                                                                                                          83/104 
      Verifying  : openldap-2.4.44-21.el7_6.x86_64                                                                                                                                                  84/104 
      Verifying  : 1:qt-4.8.7-8.el7.x86_64                                                                                                                                                          85/104 
      Verifying  : libcurl-7.29.0-57.el7.x86_64                                                                                                                                                     86/104 
      Verifying  : graphviz-2.30.1-21.el7.x86_64                                                                                                                                                    87/104 
      Verifying  : 1:qt-x11-4.8.7-8.el7.x86_64                                                                                                                                                      88/104 
      Verifying  : libgomp-4.8.5-39.el7.x86_64                                                                                                                                                      89/104 
      Verifying  : openldap-devel-2.4.44-21.el7_6.x86_64                                                                                                                                            90/104 
      Verifying  : perl-Git-1.8.3.1-22.el7_8.noarch                                                                                                                                                 91/104 
      Verifying  : gcc-gfortran-4.8.5-39.el7.x86_64                                                                                                                                                 92/104 
      Verifying  : 1:openssl-devel-1.0.2k-19.el7.x86_64                                                                                                                                             93/104 
      Verifying  : mesa-libEGL-18.3.4-7.el7.x86_64                                                                                                                                                  94/104 
      Verifying  : libquadmath-4.8.5-39.el7.x86_64                                                                                                                                                  95/104 
      Verifying  : 1:mariadb-libs-5.5.65-1.el7.x86_64                                                                                                                                               96/104 
      Verifying  : libstdc++-4.8.5-39.el7.i686                                                                                                                                                      97/104 
      Verifying  : curl-7.29.0-57.el7.x86_64                                                                                                                                                        98/104 
      Verifying  : libgcc-4.8.5-39.el7.x86_64                                                                                                                                                       99/104 
      Verifying  : libX11-1.6.7-2.el7.x86_64                                                                                                                                                       100/104 
      Verifying  : libX11-common-1.6.7-2.el7.noarch                                                                                                                                                101/104 
      Verifying  : libstdc++-devel-4.8.5-39.el7.x86_64                                                                                                                                             102/104 
      Verifying  : binutils-2.27-43.base.el7.x86_64                                                                                                                                                103/104 
      Verifying  : libX11-devel-1.6.7-2.el7.x86_64                                                                                                                                                 104/104 

    Updated:
      binutils.x86_64 0:2.27-44.base.el7  curl.x86_64 0:7.29.0-59.el7_9.1           gcc.x86_64 0:4.8.5-44.el7               gcc-c++.x86_64 0:4.8.5-44.el7            gcc-gfortran.x86_64 0:4.8.5-44.el7  
      git.x86_64 0:1.8.3.1-23.el7_8       graphviz-devel.x86_64 0:2.30.1-22.el7     libX11-devel.x86_64 0:1.6.7-3.el7_9     libcurl-devel.x86_64 0:7.29.0-59.el7_9.1 libxml2-devel.x86_64 0:2.9.1-6.el7.5
      mariadb-devel.x86_64 1:5.5.68-1.el7 mesa-libGL-devel.x86_64 0:18.3.4-12.el7_9 openldap-devel.x86_64 0:2.4.44-23.el7_9 openssl-devel.x86_64 1:1.0.2k-21.el7_9   python-devel.x86_64 0:2.7.5-90.el7  
      qt-devel.x86_64 1:4.8.7-9.el7_9     unzip.x86_64 0:6.0-22.el7_9              

    Dependency Updated:
      cpp.x86_64 0:4.8.5-44.el7                        gcc-objc.x86_64 0:4.8.5-44.el7                   graphviz.x86_64 0:2.30.1-22.el7                     graphviz-gd.x86_64 0:2.30.1-22.el7          
      libX11.x86_64 0:1.6.7-3.el7_9                    libX11-common.noarch 0:1.6.7-3.el7_9             libcurl.x86_64 0:7.29.0-59.el7_9.1                  libgcc.i686 0:4.8.5-44.el7                  
      libgcc.x86_64 0:4.8.5-44.el7                     libgfortran.x86_64 0:4.8.5-44.el7                libgomp.x86_64 0:4.8.5-44.el7                       libobjc.x86_64 0:4.8.5-44.el7               
      libquadmath.x86_64 0:4.8.5-44.el7                libquadmath-devel.x86_64 0:4.8.5-44.el7          libstdc++.i686 0:4.8.5-44.el7                       libstdc++.x86_64 0:4.8.5-44.el7             
      libstdc++-devel.x86_64 0:4.8.5-44.el7            libxml2.x86_64 0:2.9.1-6.el7.5                   libxml2-python.x86_64 0:2.9.1-6.el7.5               mariadb-libs.x86_64 1:5.5.68-1.el7          
      mesa-khr-devel.x86_64 0:18.3.4-12.el7_9          mesa-libEGL.x86_64 0:18.3.4-12.el7_9             mesa-libEGL-devel.x86_64 0:18.3.4-12.el7_9          mesa-libGL.x86_64 0:18.3.4-12.el7_9         
      mesa-libGLES.x86_64 0:18.3.4-12.el7_9            mesa-libgbm.x86_64 0:18.3.4-12.el7_9             mesa-libglapi.x86_64 0:18.3.4-12.el7_9              openldap.x86_64 0:2.4.44-23.el7_9           
      openssl.x86_64 1:1.0.2k-21.el7_9                 openssl-libs.x86_64 1:1.0.2k-21.el7_9            perl-Git.noarch 0:1.8.3.1-23.el7_8                  python.x86_64 0:2.7.5-90.el7                
      python-libs.x86_64 0:2.7.5-90.el7                qt.x86_64 1:4.8.7-9.el7_9                        qt-x11.x86_64 1:4.8.7-9.el7_9                      

    Complete!




Reviewing PATH decide to comment miniconda::

    O[blyth@localhost junoenv]$ echo $PATH | tr ":" "\n"
    /home/blyth/opticks/ana
    /usr/local/cuda/bin
    /home/blyth/local/env/bin
    /home/blyth/local/env/tools/conda/miniconda3/bin
    /home/blyth/local/env/tools/conda/miniconda3/condabin
    /usr/local/bin
    /usr/bin
    /usr/local/sbin
    /usr/sbin
    /var/lib/snapd/snap/bin
    /home/blyth/local/opticks/bin
    /home/blyth/local/opticks/lib
    O[blyth@localhost junoenv]$ 

After that are down to assumed harmless::

    O[blyth@localhost junoenv]$ echo $PATH | tr ":" "\n"
    /home/blyth/opticks/ana
    /usr/local/cuda/bin
    /home/blyth/local/env/bin
    /usr/local/bin
    /usr/bin
    /usr/local/sbin
    /usr/sbin
    /var/lib/snapd/snap/bin
    /home/blyth/local/opticks/bin
    /home/blyth/local/opticks/lib
    O[blyth@localhost junoenv]$ 


Use jlibs for the externals::

    jlibs(){
        cd $JUNOTOP/junoenv
        local libs=$(bash junoenv libs list | perl -ne 'm, (\S*)@, && print "$1\n"' -)
        for lib in $libs ; do 
            echo $lib 
            bash junoenv libs all $lib || return 1 
        done  
    }    



Sampling some of the hundreds of thousands of lines of output does not show any obvious errors.
Usual ones are network blocks preventing downloads.

    === junoenv-external-libs: packages: python python-setuptools python-pip python-cython python-numpy boost cmake git xercesc gsl fftw3 sqlite3 log4cpp libxml2 LHAPDF pythia6 tbb cmt clhep xrootd ROOT hepmc geant4 genie nuwro talys libmore libmore-data mysql-connector-c mysql-connector-cpp libyaml python-yaml podio pacparser frontier
    ==== juno-ext-libs-list: [x] python@3.8.8 

    ==== juno-ext-libs-list: [?] python-setuptools@54.2.0 -> python
    ==== juno-ext-libs-list: [?] python-pip@20.3.4 -> python python-setuptools

    ==== juno-ext-libs-list: [x] python-cython@0.29.22 -> python

    ==== juno-ext-libs-list: [?] python-numpy@1.20.1 -> python python-setuptools python-cython

    ==== juno-ext-libs-list: [x] boost@1.75.0 -> python python-numpy
    ==== juno-ext-libs-list: [x] cmake@3.19.6 
    ==== juno-ext-libs-list: [x] git@1.8.4.3 
    ==== juno-ext-libs-list: [x] xercesc@3.2.2 
    ==== juno-ext-libs-list: [x] gsl@2.5 
    ==== juno-ext-libs-list: [x] fftw3@3.3.8 
    ==== juno-ext-libs-list: [x] sqlite3@3.35.2 
    ==== juno-ext-libs-list: [x] log4cpp@1.1.3 
    ==== juno-ext-libs-list: [x] libxml2@2.9.12 -> python
    ==== juno-ext-libs-list: [x] LHAPDF@6.3.0 -> python

    ==== juno-ext-libs-list: [?] pythia6@6.4.28 -> python

    ==== juno-ext-libs-list: [x] tbb@2019_U8 
    ==== juno-ext-libs-list: [x] cmt@v1r26 
    ==== juno-ext-libs-list: [x] clhep@2.4.1.0 -> cmake
    ==== juno-ext-libs-list: [x] xrootd@4.12.6 -> python cmake
    ==== juno-ext-libs-list: [x] ROOT@6.22.08 -> python boost cmake +git +gccxml xercesc +qt4 gsl fftw3 tbb xrootd +sqlite3 pythia6
    ==== juno-ext-libs-list: [x] hepmc@2.06.09 
    ==== juno-ext-libs-list: [x] geant4@10.04.p02.juno -> python boost cmake xercesc +qt4 +clhep ROOT
    ==== juno-ext-libs-list: [x] genie@3.00.06 -> python log4cpp libxml2 LHAPDF pythia6 ROOT

    ==== juno-ext-libs-list: [?] nuwro@19.02.2 -> libxml2 pythia6 ROOT

    ==== juno-ext-libs-list: [x] talys@1.95 -> pythia6 ROOT
    ==== juno-ext-libs-list: [x] libmore@0.8.3 
    ==== juno-ext-libs-list: [x] libmore-data@20140630 -> libmore
    ==== juno-ext-libs-list: [x] mysql-connector-c@6.1.9 -> cmake
    ==== juno-ext-libs-list: [x] mysql-connector-cpp@1.1.8 -> boost cmake mysql-connector-c
    ==== juno-ext-libs-list: [x] libyaml@0.2.2 
    ==== juno-ext-libs-list: [x] python-yaml@5.1.2 -> python python-cython libyaml
    ==== juno-ext-libs-list: [x] podio@00-10 -> python +python-yaml cmake ROOT
    ==== juno-ext-libs-list: [x] pacparser@1.3.7 
    ==== juno-ext-libs-list: [x] frontier@2.9.1 -> pacparser
    O[blyth@localhost junoenv]$ 

 


Five packages have questionmarks.

python-numpy
-------------

::


    O[blyth@localhost junoenv]$ bash junoenv libs all python-numpy 
    = The junoenv is in /data/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /data/blyth/junotop
    = THE JUNOENVDIR is /data/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: ""
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: ""
    == setup-juno-basic-preq: ================================================================
    == setup-juno-external-libs
    === junoenv-external-libs: command: all
    === junoenv-external-libs: packages: python-numpy
    === junoenv-external-libs: create function juno-ext-libs-python-numpy-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init python-numpy
    ==== juno-ext-libs-check-init: setup dependencies for python-numpy
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-numpy: create function juno-ext-libs-python-numpy-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-numpy: source /data/blyth/junotop/junoenv/packages/python-numpy.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-numpy: After source: python-numpy
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: create function juno-ext-libs-python-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: source /data/blyth/junotop/junoenv/packages/python.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: After source: python
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: status: 0 python
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: source /data/blyth/junotop/ExternalLibs/Python/3.8.8/bashrc
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-setuptools: create function juno-ext-libs-python-setuptools-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-setuptools: source /data/blyth/junotop/junoenv/packages/python-setuptools.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-setuptools: After source: python-setuptools
    ==== juno-ext-libs-dependencies-setup-rec-impl: ### setup python: python already setup
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-setuptools: status: 0 python-setuptools
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-setuptools: source /data/blyth/junotop/ExternalLibs/python-setuptools/54.2.0/bashrc
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-cython: create function juno-ext-libs-python-cython-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-cython: source /data/blyth/junotop/junoenv/packages/python-cython.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-cython: After source: python-cython
    ==== juno-ext-libs-dependencies-setup-rec-impl: ### setup python: python already setup
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-cython: status: 0 python-cython
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python-cython: source /data/blyth/junotop/ExternalLibs/python-cython/0.29.22/bashrc
    === junoenv-external-libs: juno-ext-libs-check-is-reused python-numpy
    === junoenv-external-libs: juno-ext-libs-all python-numpy
    ==== juno-ext-libs-get:
    [python-numpy-conf] ===== juno-ext-libs-PKG-get: SKIP DOWNLOADING: numpy-1.20.1.tar.gz already exists
    ==== juno-ext-libs-conf:
    ==== juno-ext-libs-make:
    [python-numpy-make] ===== juno-ext-libs-PKG-make: call juno-ext-libs-python-numpy-make-
    [python-numpy-make] Running from numpy source directory.
    [python-numpy-make] /data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/distutils_patch.py:25: UserWarning: Distutils was imported before Setuptools. This usage is discouraged and may exhibit undesirable behaviors or errors. Please use Setuptools' objects directly or at least import Setuptools first.
    [python-numpy-make]   warnings.warn(
    [python-numpy-make] Traceback (most recent call last):
    [python-numpy-make]   File "setup.py", line 513, in <module>
    [python-numpy-make]     setup_package()
    [python-numpy-make]   File "setup.py", line 489, in setup_package
    [python-numpy-make]     import setuptools  # noqa: F401
    [python-numpy-make]   File "/data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/__init__.py", line 23, in <module>
    [python-numpy-make]     from setuptools.dist import Distribution
    [python-numpy-make]   File "/data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/dist.py", line 34, in <module>
    [python-numpy-make]     from setuptools import windows_support
    [python-numpy-make]   File "/data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/windows_support.py", line 2, in <module>
    [python-numpy-make]     import ctypes
    [python-numpy-make]   File "/data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/ctypes/__init__.py", line 7, in <module>
    [python-numpy-make]     from _ctypes import Union, Structure, Array
    [python-numpy-make] ModuleNotFoundError: No module named '_ctypes'
    ==== juno-ext-libs-install:
    [python-numpy-install] ===== juno-ext-libs-PKG-install: call juno-ext-libs-python-numpy-install-
    [python-numpy-install] Running from numpy source directory.
    [python-numpy-install] /data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/distutils_patch.py:25: UserWarning: Distutils was imported before Setuptools. This usage is discouraged and may exhibit undesirable behaviors or errors. Please use Setuptools' objects directly or at least import Setuptools first.
    [python-numpy-install]   warnings.warn(
    [python-numpy-install] 
    [python-numpy-install] Note: if you need reliable uninstall behavior, then install
    [python-numpy-install] with pip instead of using `setup.py install`:
    [python-numpy-install] 
    [python-numpy-install]   - `pip install .`       (from a git repo or downloaded source
    [python-numpy-install]                            release)
    [python-numpy-install]   - `pip install numpy`   (last NumPy release on PyPi)
    [python-numpy-install] 
    [python-numpy-install] 
    [python-numpy-install] Traceback (most recent call last):
    [python-numpy-install]   File "setup.py", line 513, in <module>
    [python-numpy-install]     setup_package()
    [python-numpy-install]   File "setup.py", line 489, in setup_package
    [python-numpy-install]     import setuptools  # noqa: F401
    [python-numpy-install]   File "/data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/__init__.py", line 23, in <module>
    [python-numpy-install]     from setuptools.dist import Distribution
    [python-numpy-install]   File "/data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/dist.py", line 34, in <module>
    [python-numpy-install]     from setuptools import windows_support
    [python-numpy-install]   File "/data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/site-packages/setuptools/windows_support.py", line 2, in <module>
    [python-numpy-install]     import ctypes
    [python-numpy-install]   File "/data/blyth/junotop/ExternalLibs/Python/3.8.8/lib/python3.8/ctypes/__init__.py", line 7, in <module>
    [python-numpy-install]     from _ctypes import Union, Structure, Array
    [python-numpy-install] ModuleNotFoundError: No module named '_ctypes'
    ==== juno-ext-libs-setup:
    [python-numpy-setup] /data/blyth/junotop/ExternalLibs/python-numpy/1.20.1 /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [python-numpy-setup] /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    O[blyth@localhost junoenv]$ 
    O[blyth@localhost junoenv]$ which python
    /usr/bin/python
    O[blyth@localhost junoenv]$ 


Look for zero sized tarballs::

    O[blyth@localhost junoenv]$ find /data/blyth/junotop/ExternalLibs/ -name '*.gz' -exec du -h {} \; 
    2.0M	/data/blyth/junotop/ExternalLibs/Build/setuptools-54.2.0.tar.gz
    8.4M	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/backends/test_backend-0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/indexes/empty_with_pkg/simple-1.0.tar.gz
    20K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/INITools-0.2.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/TopoRequires-0.0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/TopoRequires2-0.0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/TopoRequires3-0.0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/TopoRequires4-0.0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/Upper-1.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/Upper-2.0.tar.gz
    68K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/argparse-1.2.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/broken-0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/broken-0.2broken.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/brokenegginfo-0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/child-0.1.tar.gz

    0	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/duplicate-1.0.tar.gz
    0	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/gmpy-1.15.tar.gz
    0	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/gmpy2-2.0.tar.gz

    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/parent-0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/pep518-3.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/pep518_forkbomb-235.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/pep518_twin_forkbombs_first-234.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/pep518_twin_forkbombs_second-238.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/pep518_with_extra_and_markers-1.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/pip-test-package-0.1.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/pip-test-package-0.1.tar.gz

    0	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/pkgwithmpkg-1.0.tar.gz
    0	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/priority-1.0.tar.gz

    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/require_simple-1.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/requiresupper-1.0.tar.gz
    748K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/setuptools-0.9.6.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/simple-1.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/simple-2.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/simple-3.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/simple2-1.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/simple2-2.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/simple2-3.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/singlemodule-0.0.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/singlemodule-0.0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/source-1.0.tar.gz
    28K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/translationstring-1.1.tar.gz
    1.3M	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/virtualenv-1.10.tar.gz
    2.0M	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/virtualenv-1.9.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/wheelbroken-0.1.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages/wheelbrokenafter-0.1.tar.gz

    0	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages2/duplicate-1.0.tar.gz

    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages3/dinner/Dinner-1.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages3/dinner/Dinner-2.0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/pip-20.3.4/tests/data/packages3/requiredinner/requiredinner-1.0.tar.gz
    2.0M	/data/blyth/junotop/ExternalLibs/Build/cython-0.29.22.tar.gz
    6.9M	/data/blyth/junotop/ExternalLibs/Build/numpy-1.20.1.tar.gz
    138M	/data/blyth/junotop/ExternalLibs/Build/boost_1_75_0.tar.gz
    4.0K	/data/blyth/junotop/ExternalLibs/Build/boost_1_75_0/tools/boost_install/test/iostreams/test.txt.gz
    8.9M	/data/blyth/junotop/ExternalLibs/Build/cmake-3.19.6.tar.gz
    6.8M	/data/blyth/junotop/ExternalLibs/Build/xerces-c-3.2.2.tar.gz
    7.0M	/data/blyth/junotop/ExternalLibs/Build/gsl-2.5.tar.gz
    4.0M	/data/blyth/junotop/ExternalLibs/Build/fftw-3.3.8.tar.gz
    2.9M	/data/blyth/junotop/ExternalLibs/Build/sqlite-autoconf-3350200.tar.gz
    584K	/data/blyth/junotop/ExternalLibs/Build/log4cpp-1.1.3.tar.gz
    5.0M	/data/blyth/junotop/ExternalLibs/Build/libxml2-2.9.12.tar.gz
    756K	/data/blyth/junotop/ExternalLibs/Build/LHAPDF-6.3.0.tar.gz
    556K	/data/blyth/junotop/ExternalLibs/Build/pythia6-6.4.28/pythia6.tar.gz
    2.5M	/data/blyth/junotop/ExternalLibs/Build/2019_U8.tar.gz
    2.1M	/data/blyth/junotop/ExternalLibs/Build/CMTv1r26.tar.gz
    166M	/data/blyth/junotop/ExternalLibs/Build/root_v6.22.08.source.tar.gz
    912K	/data/blyth/junotop/ExternalLibs/Build/root-6.22.08/root-6.22.08/core/lzma/src/xz-5.2.4-win32.tar.gz
    1.5M	/data/blyth/junotop/ExternalLibs/Build/root-6.22.08/root-6.22.08/core/lzma/src/xz-5.2.4.tar.gz
    27M	/data/blyth/junotop/ExternalLibs/Build/root-6.22.08/root-6.22.08/documentation/doxygen/mathjax.tar.gz
    2.2M	/data/blyth/junotop/ExternalLibs/Build/root-6.22.08/root-6.22.08/graf2d/freetype/src/freetype-2.6.1.tar.gz
    6.7M	/data/blyth/junotop/ExternalLibs/Build/root-6.22.08/root-6.22.08/gui/webdisplay/res/openui5.tar.gz
    696K	/data/blyth/junotop/ExternalLibs/Build/root-6.22.08/root-6.22.08/math/unuran/src/unuran-1.8.0-root.tar.gz
    60K	/data/blyth/junotop/ExternalLibs/Build/root-6.22.08/root-6.22.08/root-build/VDT-prefix/src/vdt-0.4.3.tar.gz
    33M	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02.tar.gz
    403M	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/G4NDL-4.5/src/G4NDL.4.5.tar.gz
    72M	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/G4EMLOW-7.3/src/G4EMLOW.7.3.tar.gz
    9.7M	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/PhotonEvaporation-5.2/src/G4PhotonEvaporation.5.2.tar.gz
    1.1M	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/RadioactiveDecay-5.2/src/G4RadioactiveDecay.5.2.tar.gz
    2.2M	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/G4NEUTRONXS-1.4/src/G4NEUTRONXS.1.4.tar.gz
    4.1M	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/G4PII-1.3/src/G4PII.1.3.tar.gz
    128M	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/RealSurface-2.1.1/src/G4RealSurface.2.1.1.tar.gz
    28K	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/G4SAIDDATA-1.1/src/G4SAIDDATA.1.1.tar.gz
    108K	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/G4ABLA-3.1/src/G4ABLA.3.1.tar.gz
    284K	/data/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/geant4-build/Externals/G4ENSDFSTATE-2.2/src/G4ENSDFSTATE.2.2.tar.gz
    8.8M	/data/blyth/junotop/ExternalLibs/Build/R-3_00_06.tar.gz
    8.7M	/data/blyth/junotop/ExternalLibs/Build/nuwro_19.02.2.tar.gz
    3.4M	/data/blyth/junotop/ExternalLibs/Build/mysql-connector-c-6.1.9-src.tar.gz
    520K	/data/blyth/junotop/ExternalLibs/Build/mysql-connector-c++-1.1.8.tar.gz
    592K	/data/blyth/junotop/ExternalLibs/Build/yaml-0.2.2.tar.gz
    164K	/data/blyth/junotop/ExternalLibs/Build/PyYAML-5.1.2.tar.gz
    888K	/data/blyth/junotop/ExternalLibs/Build/pacparser-1.3.7.tar.gz
    824K	/data/blyth/junotop/ExternalLibs/Build/pacparser-1.3.7/src/spidermonkey/js-1.7.0.tar.gz

    0	/data/blyth/junotop/ExternalLibs/Build/pacparser-1.3.7/src/spidermonkey/js.tar.gz

    96K	/data/blyth/junotop/ExternalLibs/Build/frontier-2.9.1.tar.gz
    558M	/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/share/Geant4-10.4.2/data/G4TENDL.1.3.2.tar.gz
    O[blyth@localhost junoenv]$ 



Try proceeding "bash junoenv opticks" clones from bitbucket, but fails saying need "bash junoenv env" first.
After that get a bit further "bash junoenv opticks" succeeds to clone bcm(ssh) from bitbucket but 
fails to https download from github.

::
   

    ############## glm ###############

    curl -L -O https://github.com/g-truc/glm/releases/download/0.9.9.5/glm-0.9.9.5.zip
      % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                     Dload  Upload   Total   Spent    Left  Speed
      0     0    0     0    0     0      0      0 --:--:--  0:02:10 --:--:--     0
    curl: (35) Encountered end of file
    === glm-get : fFAILED TO DOWNLOAD FROM https://github.com/g-truc/glm/releases/download/0.9.9.5/glm-0.9.9.5.zip
    === opticks-installer- : RC 1 from pkg glm : ABORTING
    === opticks-full : ERR from opticks-full-externals
    ==== junoenv-opticks-command: from opticks-full rc 2
    ==== junoenv-opticks-command: error from function opticks-full
    === junoenv-opticks: junoenv-opticks-full rc 2
    === junoenv-opticks: junoenv-opticks-full rc 2
    === junoenv-opticks: rc 2
    O[blyth@localhost junoenv]$ 


::

    O[blyth@localhost junoenv]$ cd /tmp
    O[blyth@localhost tmp]$ curl -L -O https://github.com/g-truc/glm/releases/download/0.9.9.5/glm-0.9.9.5.zip
      % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                     Dload  Upload   Total   Spent    Left  Speed
      0     0    0     0    0     0      0      0 --:--:--  0:00:12 --:--:--     0



This is all too familiar GFW problem.

Introduce OPTICKS_DOWNLOAD_CACHE in .bashrc::

     38 export JUNOTOP=/data/$USER/junotop
     39 export OPTICKS_DOWNLOAD_CACHE=/data/opticks_download_cache



bash junoenv opticks confused by OPTICKS_HOME ?

::

    [ 51%] Building CXX object tests/CMakeFiles/NFieldCacheTest.dir/NFieldCacheTest.cc.o
    [ 52%] Linking CXX executable ReportTest
    [ 53%] Linking CXX executable TypesTest
    [ 53%] Linking CXX executable EnvTest
    [ 53%] Linking CXX executable CountsTest
    /usr/bin/ld: warning: libboost_system.so.1.72.0, needed by /home/blyth/local/opticks/lib64/libBoostRap.so, not found (try using -rpath or -rpath-link)
    /usr/bin/ld: warning: libboost_program_options.so.1.72.0, needed by /home/blyth/local/opticks/lib64/libBoostRap.so, not found (try using -rpath or -rpath-link)
    /usr/bin/ld: warning: libboost_filesystem.so.1.72.0, needed by /home/blyth/local/opticks/lib64/libBoostRap.so, not found (try using -rpath or -rpath-link)
    /usr/bin/ld: warning: libboost_regex.so.1.72.0, needed by /home/blyth/local/opticks/lib64/libBoostRap.so, not found (try using -rpath or -rpath-link)
    /home/blyth/local/opticks/lib64/libBoostRap.so: undefined reference to `boost::re_detail_107200::perl_matcher<__gnu_cxx::__normal_iterator<char const*, std::string>, std::allocator<boost::sub_match<__gnu_cxx::__normal_iterator<char const*, std::string> > >, boost::regex_traits<char, boost::cpp_regex_traits<char> > >::match()'
    /home/blyth/local/opticks/lib64/libBoostRap.so: undefined reference to `boost::re_detail_107200::perl_matcher<__gnu_cxx::__normal_iterator<char const*, std::string>, std::allocator<boost::sub_match<__gnu_cxx::__normal_iterator<char const*, std::string> > >, boost::regex_traits<char, boost::cpp_regex_traits<char> > >::construct_init(boost::basic_regex<char, boost::regex_traits<char, boost::cpp_regex_traits<char> > > const&, boost::regex_constants::_match_flags)'
    /home/blyth/local/opticks/lib64/libBoostRap.so: undefined reference to `boost::filesystem::absolute(boost::filesystem::path const&, boost::filesystem::path const&)'
    /home/blyth/local/opticks/lib64/libBoostRap.so: undefined reference to `boost::re_detail_107200::perl_matcher<char const*, std::allocator<boost::sub_match<char const*> >, boost::regex_traits<char, boost::cpp_regex_traits<char> > >::construct_init(boost::basic_regex<char, boost::regex_traits<char, boost::cpp_regex_traits<char> > > const&, boost::regex_constants::_match_flags)'
    /home/blyth/local/opticks/lib64/libBoostRap.so: undefined reference to `boost::re_detail_107200::perl_matcher<char const*, std::allocator<boost::sub_match<char const*> >, boost::regex_traits<char, boost::cpp_regex_traits<char> > >::match()'
    /home/blyth/local/opticks/lib64/libBoostRap.so: undefined reference to `boost::re_detail_107200::perl_matcher<char const*, std::allocator<boost::sub_match<char const*> >, boost::regex_traits<char, boost::cpp_regex_traits<char> > >::find()'
    /home/blyth/local/opticks/lib64/libBoostRap.so: undefined reference to `boost::re_detail_107200::perl_matcher<__gnu_cxx::__normal_iterator<char const*, std::string>, std::allocator<boost::sub_match<__gnu_cxx::__normal_iterator<char const*, std::string> > >, boost::regex_traits<char, boost::cpp_regex_traits<char> > >::find()'
    collect2: error: ld returned 1 exit status
    [ 54%] Linking CXX executable readFlagsTest
    make[2]: *** [tests/ReportTest] Error 1
    make[1]: *** [tests/CMakeFiles/ReportTest.dir/all] Error 2
    make[1]: *** Waiting for unfinished jobs....






G4MTHepRandom::getTheEngine again
-----------------------------------

::

    [ 69%] Building CXX object tests/CMakeFiles/X4SolidTest.dir/X4SolidTest.cc.o
    [ 70%] Building CXX object tests/CMakeFiles/X4GDMLParserTest.dir/X4GDMLParserTest.cc.o
    [ 71%] Building CXX object tests/CMakeFiles/X4PhysicalVolume2Test.dir/X4PhysicalVolume2Test.cc.o
    [ 72%] Building CXX object tests/CMakeFiles/X4GDMLBalanceTest.dir/X4GDMLBalanceTest.cc.o
    [ 73%] Linking CXX executable X4MaterialWaterStandaloneTest
    [ 73%] Linking CXX executable X4NameOrderTest
    [ 74%] Linking CXX executable X4Test
    [ 75%] Linking CXX executable X4PhysicsVectorTest
    [ 76%] Linking CXX executable X4MeshTest
    [ 77%] Linking CXX executable X4MaterialPropertyVectorTest
    [ 79%] Linking CXX executable X4DumpTest
    [ 79%] Linking CXX executable X4MaterialWaterTest
    [ 80%] Linking CXX executable X4EntityTest
    [ 81%] Linking CXX executable X4MaterialTest
    [ 82%] Linking CXX executable X4SolidListTest
    [ 83%] Linking CXX executable X4PhysicsOrderedFreeVectorTest
    [ 84%] Linking CXX executable X4MaterialTableTest
    [ 85%] Linking CXX executable X4GDMLReadDefineTest
    [ 86%] Linking CXX executable X4AffineTransformTest
    [ 87%] Linking CXX executable X4SolidLoadTest
    [ 88%] Linking CXX executable X4ThreeVectorTest
    [ 89%] Linking CXX executable X4SolidExtentTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4MaterialWaterStandaloneTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4MaterialWaterStandaloneTest.dir/all] Error 2
    make[1]: *** Waiting for unfinished jobs....
    [ 90%] Linking CXX executable X4PhysicalVolumeTest
    [ 91%] Linking CXX executable X4PolyconeTest
    [ 92%] Linking CXX executable X4CSGTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[1]: *** [tests/CMakeFiles/X4NameOrderTest.dir/all] Error 2
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4MaterialWaterTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4MaterialWaterTest.dir/all] Error 2
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4Test] Error 1
    make[1]: *** [tests/CMakeFiles/X4Test.dir/all] Error 2
    [ 93%] Linking CXX executable X4SolidTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4DumpTest] Error 1


::

    049 class G4MTHepRandom
     50 {
     51 
    ...
    114   static CLHEP::HepRandomEngine * getTheEngine();
    115   // Returns a pointer to the underlying algorithm object.
    116 


    028 //
     29 #if __clang__
     30   #if ((defined(G4MULTITHREADED) && !defined(G4USE_STD11)) || \
     31       !__has_feature(cxx_thread_local)) || !__has_feature(c_atomic)
     32     #define CLANG_NOSTDTLS
     33   #endif
     34 #endif
     35 
     36 #if (defined(G4MULTITHREADED) && \
     37     (!defined(G4USE_STD11) || (defined(CLANG_NOSTDTLS) || defined(__INTEL_COMPILER))))
     38 
     39 #include <CLHEP/Random/StaticRandomStates.h>
     40 #include <CLHEP/Random/JamesRandom.h>
     41 
     42 #include "G4MTHepRandom.hh"
     43 #include "G4Threading.hh"
     44 #include "G4AutoLock.hh"
     45 
     46 G4ThreadLocal CLHEP::HepRandomEngine* G4MTHepRandom::theEngine = 0;
     47 G4ThreadLocal G4MTHepRandom* G4MTHepRandom::theGenerator = 0;
     48 G4ThreadLocal G4int G4MTHepRandom::isActive  = 0 ;
     49 
    ...
    154 CLHEP::HepRandomEngine * G4MTHepRandom::getTheEngine()
    155 {
    156   if (!isActive)  { isActive = G4MTHepRandom::createInstanceOnce(); }
    157   return theEngine;
    158 }
    ...
    233 
    234 #endif




Flip to -DGEANT4_BUILD_MULTITHREADED=OFF and build geant4 again::

    O[blyth@localhost junoenv]$ vi packages/geant4.sh 

    137 
    138 function juno-ext-libs-geant4-conf-10 {
    139     local msg="===== $FUNCNAME: "
    140     cmake .. -DCMAKE_INSTALL_PREFIX=$(juno-ext-libs-geant4-install-dir) \
    141         -DGEANT4_USE_GDML=ON \
    142         -DGEANT4_INSTALL_DATA=ON \
    143         -DGEANT4_USE_OPENGL_X11=ON \
    144         -DGEANT4_USE_RAYTRACER_X11=ON \
    145         -DGEANT4_BUILD_MULTITHREADED=OFF \
    146         -DGEANT4_BUILD_TLS_MODEL=global-dynamic \
    147         -DXERCESC_ROOT_DIR=$(juno-ext-libs-xercesc-install-dir) \
    148         -DGEANT4_USE_SYSTEM_CLHEP=ON
    149 
    150 

    O[blyth@localhost junoenv]$ bash junoenv libs all geant4


    O[blyth@localhost ~]$ which geant4-config
    /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config
    O[blyth@localhost ~]$ geant4-config --cflags
    -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -std=c++11 -I/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4 -I/data/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/include
    O[blyth@localhost ~]$ geant4-config --libs
    -L/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../lib64 -lG4OpenGL -lG4gl2ps -lG4Tree -lG4FR -lG4GMocren -lG4visHepRep -lG4RayTracer -lG4VRML -lG4vis_management -lG4modeling -lG4interfaces -lG4persistency -lG4analysis -lG4error_propagation -lG4readout -lG4physicslists -lG4run -lG4event -lG4tracking -lG4parmodels -lG4processes -lG4digits_hits -lG4track -lG4particles -lG4geometry -lG4materials -lG4graphics_reps -lG4intercoms -lG4global -L/data/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/lib -lCLHEP-2.4.1.0 -lG4zlib
    O[blyth@localhost ~]$ 


After that "opticks full" completes::

    O[blyth@localhost junoenv]$ bash junoenv opticks full
    O[blyth@localhost junoenv]$ bash junoenv opticks hookup


Network blockage ?, Stuck at:: 

    sniper-1.7/sniper-modulefile.in
    sniper-1.7/tests/
    sniper-1.7/tests/CMakeLists.txt
    sniper-1.7/tests/TestJSON.cc
    ==== junoenv-sniper-get: download the source code
    --2021-07-07 16:39:50--  https://github.com/SNiPER-Framework/mt.sniper/archive/v0.1.1.tar.gz
    Resolving github.com (github.com)... 140.82.112.3
    Connecting to github.com (github.com)|140.82.112.3|:443... failed: Connection timed out.
    Retrying.

    --2021-07-07 16:42:07--  (try: 2)  https://github.com/SNiPER-Framework/mt.sniper/archive/v0.1.1.tar.gz
    Connecting to github.com (github.com)|140.82.112.3|:443... connected.
    HTTP request sent, awaiting response... 302 Found
    Location: https://codeload.github.com/SNiPER-Framework/mt.sniper/tar.gz/v0.1.1 [following]
    --2021-07-07 16:43:12--  https://codeload.github.com/SNiPER-Framework/mt.sniper/tar.gz/v0.1.1
    Resolving codeload.github.com (codeload.github.com)... 



Need to source $JUNOTOP/bashrc.sh after the opticks hookup to get CMTEXTRATAGS=opticks::

    O[blyth@localhost junoenv]$ echo $CMTEXTRATAGS

    O[blyth@localhost junoenv]$ source $JUNOTOP/bashrc.sh
    O[blyth@localhost junoenv]$ echo $CMTEXTRATAGS
    opticks
    O[blyth@localhost junoenv]$ 



::


    #--------------------------------------------------------------
    # Now trying [cmt make] in /data/blyth/junotop/offline/Reconstruction/RecTimeLikeAlg/cmt (108/126)
    #--------------------------------------------------------------
    #CMT---> Info: Execute action make => gmake bin=../Linux-x86_64/ 
    #CMT---> (Makefile.header) Rebuilding ../Linux-x86_64/Linux-x86_64.make
    #CMT---> (constituents.make) Rebuilding library links
    #CMT---> (constituents.make) Building RecTimeLikeAlg.make
    #CMT---> (constituents.make) Building RecTimeLikeAlg_python.make
    #CMT---> Info: Library RecTimeLikeAlg
    #CMT---> Info: Document RecTimeLikeAlg_python
    #CMT---> (constituents.make) Starting RecTimeLikeAlgprototype
    #CMT---> (constituents.make) Starting RecTimeLikeAlg_python
    gmake[2]: `RecTimeLikeAlgprototype' is up to date.
    #CMT---> (constituents.make) RecTimeLikeAlgprototype done
    Installing files from ../python to /data/blyth/junotop/offline/InstallArea
    #CMT---> (constituents.make) Starting RecTimeLikeAlgcompile
    #CMT---> (RecTimeLikeAlg.make) Rebuilding ../Linux-x86_64/RecTimeLikeAlg_dependencies.make
    #CMT---> Info: calculating dependencies for ../src/RecTimeLikeAlg.cc
    Create dir '/data/blyth/junotop/offline/InstallArea/python/RecTimeLikeAlg'
    Copy '../../../Reconstruction/RecTimeLikeAlg/python/RecTimeLikeAlg/__init__.py' -> '/data/blyth/junotop/offline/InstallArea/python/RecTimeLikeAlg/__init__.py'
    installation done
    #CMT---> (constituents.make) RecTimeLikeAlg_python done
    #CMT---> compiling ../src/RecTimeLikeAlg.cc
    In file included from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/exception_translator.hpp:10:0,
                     from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python.hpp:28,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/Property.h:22,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/PropertyMgr.h:22,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/DLElement.h:23,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/SvcBase.h:22,
                     from /data/blyth/junotop/offline/InstallArea/include/Geometry/RecGeomSvc.h:10,
                     from ../src/RecTimeLikeAlg.h:27,
                     from ../src/RecTimeLikeAlg.cc:23:
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/bind.hpp:41:265: note: #pragma message: The practice of declaring the Bind placeholders (_1, _2, ...) in the global namespace is deprecated. Please use <boost/bind/bind.hpp> + using namespace boost::placeholders, or define BOOST_BIND_GLOBAL_PLACEHOLDERS to retain the current behavior.
     )
                                                                                                                                                                                                                                                                             ^
    In file included from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/config.hpp:61:0,
                     from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/detail/config.hpp:15,
                     from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/detail/prefix.hpp:14,
                     from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/args.hpp:8,
                     from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python.hpp:11,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/Property.h:22,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/PropertyMgr.h:22,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/DLElement.h:23,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/SvcBase.h:22,
                     from /data/blyth/junotop/offline/InstallArea/include/Geometry/RecGeomSvc.h:10,
                     from ../src/RecTimeLikeAlg.h:27,
                     from ../src/RecTimeLikeAlg.cc:23:
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/filesystem/directory.hpp:291:28: warning: unused parameter 'that' [-Wunused-parameter]
       BOOST_DEFAULTED_FUNCTION(directory_iterator(directory_iterator const& that), : m_imp(that.m_imp) {})
                                ^
    In file included from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/filesystem.hpp:18:0,
                     from ../src/RecTimeLikeAlg.h:28,
                     from ../src/RecTimeLikeAlg.cc:23:
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/filesystem/directory.hpp: In function 'boost::filesystem::directory_iterator boost::filesystem::range_begin(const boost::filesystem::directory_iterator&)':
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/filesystem/directory.hpp:359:95: note: synthesized method 'boost::filesystem::directory_iterator::directory_iterator(const boost::filesystem::directory_iterator&)' first required here 
     inline directory_iterator range_begin(const directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
                                                                                                   ^
    In file included from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/config.hpp:61:0,
                     from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/detail/config.hpp:15,
                     from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/detail/prefix.hpp:14,
                     from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/args.hpp:8,
                     from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python.hpp:11,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/Property.h:22,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/PropertyMgr.h:22,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/DLElement.h:23,
                     from /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/SvcBase.h:22,
                     from /data/blyth/junotop/offline/InstallArea/include/Geometry/RecGeomSvc.h:10,
                     from ../src/RecTimeLikeAlg.h:27,
                     from ../src/RecTimeLikeAlg.cc:23:
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/filesystem/directory.hpp: At global scope:
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/filesystem/directory.hpp:482:28: warning: unused parameter 'that' [-Wunused-parameter]
       BOOST_DEFAULTED_FUNCTION(recursive_directory_iterator(recursive_directory_iterator const& that), : m_imp(that.m_imp) {})
                                ^
    In file included from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/filesystem.hpp:18:0,
                     from ../src/RecTimeLikeAlg.h:28,
                     from ../src/RecTimeLikeAlg.cc:23:
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/filesystem/directory.hpp: In function 'boost::filesystem::recursive_directory_iterator boost::filesystem::range_begin(const boost::filesystem::recursive_directory_iterator&)':
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/filesystem/directory.hpp:607:115: note: synthesized method 'boost::filesystem::recursive_directory_iterator::recursive_directory_iterator(const boost::filesystem::recursive_directory_iterator&)' first required here 
     inline recursive_directory_iterator range_begin(const recursive_directory_iterator& iter) BOOST_NOEXCEPT { return iter; }
                                                                                                                       ^
    ../src/RecTimeLikeAlg.cc: In member function 'bool RecTimeLikeAlg::Load_LikeFun()':
    ../src/RecTimeLikeAlg.cc:439:119: error: variable-sized object 'zbinning' may not be initialized
       double zbinning[nbins_z+1] = {0, 8.21561, 10.351, 11.849, 13.0415, 14.0485, 14.9288, 15.7159, 16.4312, 17.0892, 17.7};
                                                                                                                           ^
    gmake[2]: *** [../Linux-x86_64/RecTimeLikeAlg.o] Error 1
    gmake[1]: *** [RecTimeLikeAlgcompile] Error 2
    gmake: *** [all] Error 2
    #CMT---> Error: execution failed : make
    #CMT---> Error: execution error : cmt make
    /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    O[blyth@localhost junoenv]$ 



Looking at timeline, I dont see any recent changes.

* https://juno.ihep.ac.cn/trac/timeline


::

    181         int nbins_z;




     424     }
     425     //use z-r-dist pdf
     426     else if (m_Algorithm == 2){
     427         file_Time_nhit_mcp[0] = new TFile(TString((s/"pdf_zli_3d_mcp.root").string()));
     428         file_Time_nhit_ham[0] = new TFile(TString((s/"pdf_zli_3d_hamamastu.root").string()));
     429 
     430         if(!file_Time_nhit_mcp[0]) {
     431             LogError  << "Failed to get Likelihood Function File!" << std::endl;
     432             return true;
     433         }
     434         else {
     435             LogDebug << "PDF : " << file_Time_nhit_mcp[0]->GetName() << std::endl;
     436             LogDebug << "PDF : " << file_Time_nhit_ham[0]->GetName() << std::endl;
     437         }
     438         nbins_z = 10;
     439         double zbinning[nbins_z+1] = {0, 8.21561, 10.351, 11.849, 13.0415, 14.0485, 14.9288, 15.7159, 16.4312, 17.0892, 17.7};
     440         for (int j=0; j<=nbins_z; j++){
     441             vec_zbinning.push_back(zbinning[j]);
     442         }
     443         for (int j=0; j<nbins_z; j++){
     444             pdf_z_r_dist2pmt_mcp[j] = (TH3F*)file_Time_nhit_mcp[0]->Get(Form("pdf_r_dist2pmt_tres_%d",j));
     445             pdf_z_r_dist2pmt_cdf_mcp[j] = (TH3F*)file_Time_nhit_mcp[0]->Get(Form("pdf_r_dist2pmt_tres_cdf_%d",j));
     446 
     447             pdf_z_r_dist2pmt_ham[j] = (TH3F*)file_Time_nhit_ham[0]->Get(Form("pdf_r_dist2pmt_tres_%d",j));
     448             pdf_z_r_dist2pmt_cdf_ham[j] = (TH3F*)file_Time_nhit_ham[0]->Get(Form("pdf_r_dist2pmt_tres_cdf_%d",j));
     449         }
     450         pdf_dn_ham = (TH1F*)pdf_z_r_dist2pmt_ham[0]->ProjectionZ("pdf_dn_ham",1,1,1,1);
     451         pdf_dn_mcp = (TH1F*)pdf_z_r_dist2pmt_mcp[0]->ProjectionZ("pdf_dn_mcp",1,1,1,1);
     452         for (int i=1; i<= pdf_dn_mcp->GetNbinsX(); i++){
     453             pdf_dn_mcp->SetBinContent(i, 1);
     454         }
     455         for (int i=1; i<= pdf_dn_ham->GetNbinsX(); i++){
     456             pdf_dn_ham->SetBinContent(i, 1);
     457         }



::

    O[blyth@localhost src]$ svn log RecTimeLikeAlg.cc -l3
    ------------------------------------------------------------------------
    r4785 | lizy | 2021-07-03 22:25:51 +0800 (Sat, 03 Jul 2021) | 1 line

    add function to use dynode/mcp only for rec
    ------------------------------------------------------------------------
    r4766 | lizy | 2021-07-01 15:59:37 +0800 (Thu, 01 Jul 2021) | 1 line

    add r-z-dist tres pdf & charge map
    ------------------------------------------------------------------------
    r4646 | lintao | 2021-05-29 15:30:08 +0800 (Sat, 29 May 2021) | 1 line

    In order to keep safe in the deconstructor, initialize the pointers to nullptr. 
    ------------------------------------------------------------------------
    O[blyth@localhost src]$ 


Find fix with ~/opticks/sysrap/tests/variable_size_object_may_not_be_initialized.cc


Tao gives me write access::


    O[blyth@localhost offline]$ svn ci Reconstruction/RecTimeLikeAlg/src/RecTimeLikeAlg.cc Reconstruction/RecTimeLikeAlg/src/RecTimeLikeAlg.h \
    > -m "fix to get RecTimeLikeAlg to compile with gcc 4.8.5, see https://bitbucket.org/simoncblyth/opticks/src/master/sysrap/tests/variable_size_object_may_not_be_initialized.cc for a standalone demonstration of the issue and the fix"
    Sending        Reconstruction/RecTimeLikeAlg/src/RecTimeLikeAlg.cc
    Sending        Reconstruction/RecTimeLikeAlg/src/RecTimeLikeAlg.h
    Transmitting file data ..
    Committed revision 4829.
    O[blyth@localhost offline]$ 




::

    #--------------------------------------------------------------
    # Now trying [cmt make] in /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/cmt (116/126)
    #--------------------------------------------------------------


::

    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/slice.hpp: In constructor 'boost::python::slice::slice(Integer1, Integer2)':
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/slice.hpp:56:9: warning: declaration of 'stop' shadows a member of 'this' [-Wshadow]
             : base( object(start).ptr(), object(stop).ptr(), 0 )
             ^
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/slice.hpp:56:9: warning: declaration of 'start' shadows a member of 'this' [-Wshadow]
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/slice.hpp: In constructor 'boost::python::slice::slice(Integer1, Integer2, Integer3)':
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/slice.hpp:61:9: warning: declaration of 'stop' shadows a member of 'this' [-Wshadow]
             : base( object(start).ptr(), object(stop).ptr(), object(stride).ptr() )
             ^
    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/slice.hpp:61:9: warning: declaration of 'start' shadows a member of 'this' [-Wshadow]
    ../src/PMTEfficiencyCheck.cc: In constructor 'PMTEfficiencyCheck::PMTEfficiencyCheck(const junoSD_PMT_v2*)':
    ../src/PMTEfficiencyCheck.cc:27:5: error: class 'PMTEfficiencyCheck' does not have any field named 'm_parcat_mismatch_count'
         m_parcat_mismatch_count(0),
         ^
    ../src/PMTEfficiencyCheck.cc:28:5: error: class 'PMTEfficiencyCheck' does not have any field named 'm_simcat_mismatch_count'
         m_simcat_mismatch_count(0)
         ^
    ../src/PMTEfficiencyCheck.cc: In member function 'void PMTEfficiencyCheck::addHitRecord(int, const G4ThreeVector&, const G4ThreeVector&, double, double, double, const string&, int)':
    ../src/PMTEfficiencyCheck.cc:207:49: error: 'parcat' was not declared in this scope
         d.push_back(SPack::unsigned_as_double(pmtID,parcat));    
                                                     ^
    ../src/PMTEfficiencyCheck.cc:247:43: error: 'simcat' was not declared in this scope
         d.push_back(SPack::unsigned_as_double(simcat,mismatch));    
                                               ^
    ../src/PMTEfficiencyCheck.cc:247:50: error: 'mismatch' was not declared in this scope
         d.push_back(SPack::unsigned_as_double(simcat,mismatch));    
                                                      ^
    ../src/PMTEfficiencyCheck.cc:247:50: note: suggested alternative:
    In file included from /usr/include/c++/4.8.2/bits/char_traits.h:39:0,
                     from /usr/include/c++/4.8.2/ios:40,
                     from /usr/include/c++/4.8.2/istream:38,
                     from /usr/include/c++/4.8.2/sstream:38,
                     from /usr/include/c++/4.8.2/complex:45,
                     from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4/G4Types.hh:67,
                     from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4/G4ios.hh:39,
                     from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4/globals.hh:49,
                     from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4/G4ThreeVector.hh:39,
                     from /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh:4,
                     from ../src/PMTEfficiencyCheck.cc:3:
    /usr/include/c++/4.8.2/bits/stl_algobase.h:1198:5: note:   'std::mismatch'
         mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
         ^
    ../src/PMTEfficiencyCheck.cc: In member function 'void PMTEfficiencyCheck::SaveRecords(int)':
    ../src/PMTEfficiencyCheck.cc:311:41: error: 'm_parcat_mismatch_count' was not declared in this scope
             << " parcat_mismatch_count " << m_parcat_mismatch_count
                                             ^
    ../src/PMTEfficiencyCheck.cc:312:41: error: 'm_simcat_mismatch_count' was not declared in this scope
             << " simcat_mismatch_count " << m_simcat_mismatch_count
                                             ^




::

    O[blyth@localhost cmt]$ svn log ../include/PMTEfficiencyCheck.hh
    ------------------------------------------------------------------------
    r4751 | qianzhen | 2021-07-01 10:36:16 +0800 (Thu, 01 Jul 2021) | 1 line

    updated the PMT Parameter Svc to new version & modified some relevant interfaces
    ------------------------------------------------------------------------
    r4464 | blyth | 2021-04-12 17:59:34 +0800 (Mon, 12 Apr 2021) | 1 line

    make PMTEfficiencyCheck only within WITH_G4OPTICKS 
    ------------------------------------------------------------------------
    r4460 | blyth | 2021-04-12 04:01:30 +0800 (Mon, 12 Apr 2021) | 1 line

    save PMTEfficiencyCheck records once record_limit reached rather than waiting for EndOfEvent as high energy muon events for example take so long when comparing with Geant4
    ------------------------------------------------------------------------
    r4459 | blyth | 2021-04-11 23:38:25 +0800 (Sun, 11 Apr 2021) | 1 line

    add PMTEfficiencyCheck mismatch bitfield to simplify analysis with ~/j/PMTEfficiencyCheck.py 
    ------------------------------------------------------------------------
    r4458 | blyth | 2021-04-11 21:42:19 +0800 (Sun, 11 Apr 2021) | 1 line

    envvar control for PMTEfficiencyCheck assert_match and dump to investigate j/issues/PMTEfficiencyCheck_addHitRecord_assert.rst : needs latest Opticks for SStr::Save
    ------------------------------------------------------------------------
    r4353 | blyth | 2021-03-05 22:01:27 +0800 (Fri, 05 Mar 2021) | 1 line

    update Offline-Opticks bridging code and split it off into separate files for clarity
    ------------------------------------------------------------------------
    O[blyth@localhost cmt]$ 






    O[blyth@localhost cmt]$ svn log ../src/PMTEfficiencyCheck.cc
    ------------------------------------------------------------------------
    r4751 | qianzhen | 2021-07-01 10:36:16 +0800 (Thu, 01 Jul 2021) | 1 line

    updated the PMT Parameter Svc to new version & modified some relevant interfaces
    ------------------------------------------------------------------------
    r4468 | blyth | 2021-04-12 22:26:09 +0800 (Mon, 12 Apr 2021) | 1 line

    adjust ce_cat again to enumerate return from junoSD_PMT_v2::get_ce onto some other volname, almost entirely 3inch with some one-in-a-million others
    ------------------------------------------------------------------------
    r4465 | blyth | 2021-04-12 20:29:45 +0800 (Mon, 12 Apr 2021) | 1 line

    log hits onto unexpected volname in PMTEfficiencyCheck and adjust ce_cat in junoSD_PMT_v2::get_ce to enumerate all possible return categories, see j/issues/PMTEfficiencyCheck_addHitRecord_assert.rst 
    ------------------------------------------------------------------------



PMT categories overhaul 

* https://juno.ihep.ac.cn/trac/changeset/4751/offline
* do the miminum to PMTEfficiency and PMTEfficiencyCheck to get it to compile


::

    #--------------------------------------------------------------
    # Now trying [cmt make] in /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/cmt (118/126)
    #--------------------------------------------------------------



::

    /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/slice.hpp:61:9: warning: declaration of 'start' shadows a member of 'this' [-Wshadow]
    ../src/LSExpDetectorConstruction_Opticks.cc: In static member function 'static G4Opticks* LSExpDetectorConstruction_Opticks::Setup(const G4VPhysicalVolume*, const G4VSensitiveDetector*, int)':
    ../src/LSExpDetectorConstruction_Opticks.cc:123:26: error: 'const class junoSD_PMT_v2' has no member named 'getPMTCategory'
             int pmtcat = sd->getPMTCategory(pmtid); 
                              ^

::

    115     LOG(info) << "[ setSensorData num_sensor " << num_sensor ;
    116     for(unsigned i=0 ; i < num_sensor ; i++)
    117     {
    118         const G4PVPlacement* pv = sensor_placements[i] ; // i is 0-based unlike sensor_index
    119         unsigned sensor_index = 1 + i ; // 1-based 
    120         assert(pv);
    121         G4int copyNo = pv->GetCopyNo();
    122         int pmtid = copyNo ;
    123         int pmtcat = sd->getPMTCategory(pmtid);
    124         float efficiency_1 = sd->getQuantumEfficiency(pmtid);
    125         float efficiency_2 = sd->getEfficiencyScale() ;
    126 
    127         g4ok->setSensorData( sensor_index, efficiency_1, efficiency_2, pmtcat, pmtid );
    128     }



::

    epsilon:offline blyth$ svn log -l5 Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    ------------------------------------------------------------------------
    r4497 | blyth | 2021-04-27 19:25:32 +0100 (Tue, 27 Apr 2021) | 1 line

    junoSD_PMT_v2::getMergerOpticks in opticksMode 1 return the standard m_pmthitmerger 
    ------------------------------------------------------------------------
    r4464 | blyth | 2021-04-12 10:59:34 +0100 (Mon, 12 Apr 2021) | 1 line

    make PMTEfficiencyCheck only within WITH_G4OPTICKS 
    ------------------------------------------------------------------------
    r4452 | miaoyu | 2021-04-06 09:18:47 +0100 (Tue, 06 Apr 2021) | 1 line

    Fix bugs in junoSD: pmt_type and qe_type are not read from PMTSimParamSvc
    ------------------------------------------------------------------------
    r4353 | blyth | 2021-03-05 14:01:27 +0000 (Fri, 05 Mar 2021) | 1 line

    update Offline-Opticks bridging code and split it off into separate files for clarity
    ------------------------------------------------------------------------
    r4188 | caogf | 2020-11-19 07:42:10 +0000 (Thu, 19 Nov 2020) | 1 line

    add new pmt optical model, which is disabled by default.
    ------------------------------------------------------------------------
    epsilon:offline blyth$ 





::

     908 int junoSD_PMT_v2::getPMTCategory(int pmtID) const
     909 {
     910     return m_category_type == 'S' ? getSimCategory(pmtID) : getParCategory(pmtID) ;
     911 }
     912 const char* junoSD_PMT_v2::getPMTCategoryName(int cat) const
     913 {
     914     return m_category_type == 'S' ? getSimCategoryName(cat) : getParCategoryName(cat) ;
     915 }
     916 
     917 /**
     918 junoSD_PMT_v2::getSimCategory
     919 -------------------------------
     920 
     921 Returns enum value from: {kPMTType_Unknown, kPMTType_Hamamatsu, kPMTType_HiQENNVT, kPMTType_NormalNNVT, kPMTType_HZC }
     922 
     923 **/
     924 int junoSD_PMT_v2::getSimCategory(int pmtID) const
     925 {
     926     int simcat = pmtID<18000 ? m_PMTSimParsvc->getPMTCategory(pmtID) : ( pmtID >= 300000 ? kPMTType_HZC : kPMTType_Unknown )  ;
     927     return simcat ;
     928 }
     929 
     930 const char* junoSD_PMT_v2::getSimCategoryName(int simcat) const
     931 {
     932     return m_PMTSimParsvc->PMTCategoryName(simcat) ;
     933 }
     934 
     935 /**
     936 junoSD_PMT_v2::getParCategory
     937 -------------------------------
     938 
     939 Returns enum value from: {kPMT_Unknown,     kPMT_NNVT,          kPMT_Hamamatsu,    kPMT_HZC,            kPMT_NNVT_HighQE } 
     940 
     941 **/
     942 int junoSD_PMT_v2::getParCategory(int pmtID) const
     943 {
     944     int parcat = m_PMTParamsvc->getPMTCategory(pmtID) ;
     945     return parcat ;
     946 }
     947 
     948 const char* junoSD_PMT_v2::getParCategoryName(int parcat) const
     949 {
     950     return PMTParamSvc::PMTCategoryName(parcat) ;
     951 }
     952 
     953 



Bizarre no access to pmt cat::


    700 double PMTSimParamSvc::get_pde(int pmtId)
    701 {
    702     // FIXME: potting scale factor, should it be placed here?
    703     double scale_factor = 1.0;
    704     if (m_map_pmt_category[pmtId] == kPMT_Hamamatsu ) {  // hamamatsu pmt
    705         scale_factor = m_pde_scale_Hamamatsu;
    706     } else if (m_map_pmt_category[pmtId] == kPMT_NNVT or m_map_pmt_category[pmtId] == kPMT_NNVT_HighQE) {
    707         scale_factor = m_pde_scale_NNVT;
    708     }
    709     return pd_vector[pmtId].pde()*scale_factor /100.;
    710 }


    621 bool PMTSimParamSvc::init_PMTParamSvc()
    622 {
    623     SniperPtr<IPMTParamSvc> pmtParamSvc(*getParent(), "PMTParamSvc");
    624     if (pmtParamSvc.invalid())
    625     {
    626         LogError << "Can't Locate  PMTParamSvc." << std::endl;
    627             return false;
    628     }
    629 
    630     for (int i = CdID::module20inchMin(); i<CdID::module20inchMax(); i++)
    631     {
    632         m_map_pmt_category[i] = pmtParamSvc->getPMTCategory(i);
    633     }
    634 
    635     return true;
    636 
    637 }

::
  
     09 unsigned int CdID::MODULE_MAX = 65535;
     10 unsigned int CdID::MODULE_20INCH_MIN = 0;
     11 unsigned int CdID::MODULE_20INCH_MAX = 17612; // 17738; // 17745; // findPmt20inchNum()-1
     12 unsigned int CdID::MODULE_3INCH_MIN  = 17613; // 17739; // 17746; // findPmt20inchNum()
     13 unsigned int CdID::MODULE_3INCH_MAX  = 47485; // 54310; // 54317; // findPmt20inchNum()+findPmt3inchNum()-1
     14 



::

     74 /**
     75 PMTParamSvc::getPMTCategory
     76 ----------------------------
     77 
     78 WP PMTs (pmtID 30,000+) are not listed in pmtdata.txt so return category kPMT_Unknown -1 
     79 for them.
     80 
     81 **/
     82 int PMTParamSvc::getPMTCategory(int pmtID) const
     83 {
     84     //return m_pmt_categories.count(pmtID) == 1 ? m_pmt_categories.at(pmtID) : kPMT_Unknown  ; 
     85     return isWP(pmtID) ? kPMT_Unknown : m_pmt_categories.at(pmtID) ;
     86 }


