precision-cvmfs
==================

::

    Hi Simon,

    Yes, it would be much more easier if we maintain the same/similar environment.  
    Here is how I mount the CVMFS inside Docker container:

        https://juno.ihep.ac.cn/trac/browser/offline/trunk/installation/junoenv/docker/Dockerfile-cvmfs

    The IHEP public key and config should be installed, as shown in L29-30.
    Then the corresponding CVMFS repositories should be put in the cvmfs default.local.

    Tao


::

    FROM centos:7

    ARG PASSWORD

    RUN useradd juno
    RUN usermod -G wheel -a juno
    RUN echo -n "assumeyes=1" >> /etc/yum.conf

    RUN yum install -y sudo redhat-lsb wget subversion \
            git make gcc-c++ gcc binutils \
            libX11-devel libXpm-devel libXft-devel libXext-devel \
            gcc-gfortran openssl-devel pcre-devel  \
            mesa-libGL-devel glew-devel ftgl-devel mysql-devel \
            fftw-devel cfitsio-devel graphviz-devel \
            avahi-compat-libdns_sd-devel libldap-dev python-devel \
            libxml2-devel gsl-static gsl-devel \
            qt-devel \
            bzip2-devel imake patch ncurses-devel readline-devel \
            sqlite-devel tk-devel openldap-devel \
:            motif motif-devel openmotif openmotif-devel \
            wget curl libcurl-devel unzip bzip2 libicu-devel \
            libglvnd-devel libXmu-devel compat-db47

    RUN echo 'juno ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers

    RUN sudo yum install -y https://ecsft.cern.ch/dist/cvmfs/cvmfs-release/cvmfs-release-latest.noarch.rpm \
      && sudo yum install -y cvmfs \
      && sudo mkdir /etc/cvmfs/keys/ihep.ac.cn \
      && sudo curl -o /etc/cvmfs/keys/ihep.ac.cn/ihep.ac.cn.pub http://cvmfs-stratum-one.ihep.ac.cn/cvmfs/software/client_configure/ihep.ac.cn/ihep.ac.cn.pub \
      && sudo curl -o /etc/cvmfs/domain.d/ihep.ac.cn.conf http://cvmfs-stratum-one.ihep.ac.cn/cvmfs/software/client_configure/ihep.ac.cn.conf \
      && echo "CVMFS_REPOSITORIES='sft.cern.ch,juno.ihep.ac.cn,container.ihep.ac.cn'" | sudo tee    /etc/cvmfs/default.local \
      && echo "CVMFS_HTTP_PROXY=DIRECT"                                                 | sudo tee -a /etc/cvmfs/default.local \
      && cat /etc/cvmfs/default.local \
      && sudo mkdir -p /cvmfs/sft.cern.ch \
      && sudo mkdir -p /cvmfs/juno.ihep.ac.cn \
      && sudo mkdir -p /cvmfs/container.ihep.ac.cn;

    USER juno
    WORKDIR /home/juno



yum updates grabbed from installation/junoenv/docker/Dockerfile-cvmfs   in prep for cvmfs : seem to work
-----------------------------------------------------------------------------------------------------------

::


   sudo su

   yum install -y sudo redhat-lsb wget subversion \
        git make gcc-c++ gcc binutils \
        libX11-devel libXpm-devel libXft-devel libXext-devel \
        gcc-gfortran openssl-devel pcre-devel  \
        mesa-libGL-devel glew-devel ftgl-devel mysql-devel \
        fftw-devel cfitsio-devel graphviz-devel \
        avahi-compat-libdns_sd-devel libldap-dev python-devel \
        libxml2-devel gsl-static gsl-devel \
        qt-devel \
        bzip2-devel imake patch ncurses-devel readline-devel \
        sqlite-devel tk-devel openldap-devel \
        motif motif-devel openmotif openmotif-devel \
        wget curl libcurl-devel unzip bzip2 libicu-devel \
        libglvnd-devel libXmu-devel compat-db47


    yum install -y https://ecsft.cern.ch/dist/cvmfs/cvmfs-release/cvmfs-release-latest.noarch.rpm 

::

    Installed:
      cvmfs-release.noarch 0:2-6
    Complete!


::

    Installed:
      cvmfs.x86_64 0:2.9.0-1.el7

    Dependency Installed:
      cvmfs-config-default.noarch 0:2.0-1

    Complete!
    [root@localhost junoenv]# 



getting it started 
----------------------


::

    O[blyth@localhost junoenv]$ sudo cvmfs_config chksetup
    [sudo] password for blyth: 
    Warning: CernVM-FS map is not referenced from autofs maps (/etc/auto.master)
    Warning: autofs service is not running
    Warning: failed to use Geo-API with cvmfs-stratum-one.ihep.ac.cn
    Warning: failed to use Geo-API with cvmfs-stratum-one.ihep.ac.cn
    Warning: failed to access http://cvmfs-egi.gridpp.rl.ac.uk:8000/cvmfs/container.ihep.ac.cn/.cvmfspublished through proxy DIRECT
    O[blyth@localhost junoenv]$ 

    O[blyth@localhost junoenv]$ sudo cvmfs_config setup
    O[blyth@localhost junoenv]$ sudo cvmfs_config chksetup
    Warning: failed to use Geo-API with cvmfs-stratum-one.ihep.ac.cn
    Warning: failed to use Geo-API with cvmfs-stratum-one.ihep.ac.cn
    Warning: failed to use Geo-API with cvmfs-stratum-one.ihep.ac.cn
    Warning: failed to access http://cvmfs-egi.gridpp.rl.ac.uk:8000/cvmfs/container.ihep.ac.cn/.cvmfspublished through proxy DIRECT
    O[blyth@localhost junoenv]$ 


    O[blyth@localhost junoenv]$  l /cvmfs/juno.ihep.ac.cn/
    total 12
    1 drwxrwxr-x.  4 cvmfs cvmfs   33 Dec  1 11:18 centos7_amd64_gcc830
    1 drwxr-xr-x.  9 cvmfs cvmfs   90 Apr 11  2021 docutil
    1 -rw-rw-r--.  1 cvmfs cvmfs   32 Mar 27  2021 .cvmfsdirtab
    1 -rw-rw-r--.  1 cvmfs cvmfs   28 Mar 27  2021 .cvmfsdirtab~
    1 drwxrwxr-x.  4 cvmfs cvmfs   30 Jan  7  2021 sw
    1 drwxrwxr-x.  3 cvmfs cvmfs   34 Nov 21  2020 singularity
    1 drwxrwxr-x.  3 cvmfs cvmfs   33 Jun  4  2020 sl7_amd64_gcc485
    1 drwxrwxr-x.  4 cvmfs cvmfs   28 Jun  2  2020 ci
    1 drwxrwxr-x.  4 cvmfs cvmfs   52 May 13  2020 sl6_amd64_gcc447
    1 drwxrwxr-x.  4 cvmfs cvmfs   25 Apr 28  2020 sl6_amd64_gcc830
    1 drwxrwxr-x.  4 cvmfs cvmfs   52 Nov 27  2019 sl6_amd64_gcc494
    1 drwxrwxr-x.  9 cvmfs cvmfs  162 Jun 28  2019 sl6_amd64_gcc44
    1 drwxrwxr-x.  3 cvmfs cvmfs   29 Jun 25  2019 sl7_amd64_gcc48
    1 drwxrwxr-x.  4 cvmfs cvmfs   58 Mar 22  2017 sl5_amd64_gcc41
    1 -rw-r--r--.  1 cvmfs cvmfs   45 Mar 27  2015 new_repository
    5 drwxr-xr-x. 14 cvmfs cvmfs 4096 Mar 27  2015 .
    O[blyth@localhost junoenv]$ 


