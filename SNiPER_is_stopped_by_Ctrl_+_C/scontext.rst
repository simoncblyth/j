scontext is likely source of the SIGINT
=========================================


scontext::initPersist
-----------------------

::

    089 inline void scontext::initPersist()
     90 {
     91     if(level > 0) std::cout << "[scontext::initPersist" << std::endl ;
     92 
     93     const char* _dirpath = "$HOME/.opticks/scontext" ;
     94     const char* dirpath = spath::Resolve(_dirpath) ;
     95 
     96     if(level > 0) std::cout << " scontext::scontext dirpath " << ( dirpath ? dirpath : "-" )  << std::endl ;
     97 
     98     int rc = sdirectory::MakeDirs(dirpath, 0);
     99 
    100     if(rc!=0) std::cerr
    101         << "scontext::initPersist "
    102         << " FAILED to create dir \n"
    103         << " _dirpath [" << ( _dirpath ? _dirpath : "-" ) << "]\n"
    104         << " dirpath [" << ( dirpath ? dirpath : "-" ) << "]\n"
    105         << " ABOUT TO RAISE SIGINT \n"
    106         ;
    107 
    108     if(rc!=0) std::raise(SIGINT);
    109     assert(rc == 0);
    110 
    111     // the below only saves when CUDA_VISIBLE_DEVICES envvar is not defined, so all dev visible
    112     bool nosave = false ;
    113     sdevice::Visible(visible_devices, dirpath, nosave );
    114 
    115     sdevice::Load(   all_devices, dirpath);
    116 
    117     if(level > 0) std::cout << "]scontext::initPersist" << std::endl ;
    118 }




::

   U[blyth@lxlogin004 ~]$ echo $HOME0
    /afs/ihep.ac.cn/users/b/blyth

    U[blyth@lxlogin004 ~]$ l $HOME0/.opticks/scontext/
    total 12
    4 -rw-r--r-- 1 blyth dyw  304 Nov 17  2023 sdevice.bin
    4 drwxr-xr-x 8 blyth dyw 4096 Nov  8  2023 ..
    4 drwxr-xr-x 2 blyth dyw 4096 Nov  8  2023 .


Further trickery::

    U[blyth@lxlogin004 j]$ l $HOME0/
    total 75
     6 drwxr-xr-x  2 bin   root  6144 Jun 17 15:13 ..
     4 drwxr-xr-x 14 blyth dyw   4096 May  7 10:26 .
    24 -rw-------  1 blyth dyw  23956 May  7 10:26 .bash_history
     2 drwxr-xr-x  3 blyth dyw   2048 Nov 13  2023 .local
     1 lrwxr-xr-x  1 blyth dyw     12 Nov 12  2023 .gitconfig -> g/.gitconfig
     1 lrwxr-xr-x  1 blyth dyw     33 Nov  8  2023 opticks -> /hpcfs/juno/junogpu/blyth/opticks
     1 lrwxr-xr-x  1 blyth dyw     34 Nov  8  2023 .opticks -> /hpcfs/juno/junogpu/blyth/.opticks
     1 lrwxr-xr-x  1 blyth dyw     30 Nov  8  2023 .ssh -> /hpcfs/juno/junogpu/blyth/.ssh


    U[blyth@lxlogin004 j]$ cd $HOME0
    U[blyth@lxlogin004 blyth]$ l .opticks
    1 lrwxr-xr-x 1 blyth dyw 34 Nov  8  2023 .opticks -> /hpcfs/juno/junogpu/blyth/.opticks
    U[blyth@lxlogin004 blyth]$ pwd
    /afs/ihep.ac.cn/users/b/blyth
    U[blyth@lxlogin004 blyth]$ rm .opticks
    rm: cannot remove '.opticks': Permission denied


BINGO I MANAGED TO REPRODUCE ISSUE::

    3582 junotoptask:DetSimAlg.DetSim1Construction.inject  WARN: Failed to get the next volume of guide tube.
    3583 Total Number of UnknownVolume in CD is 39
    3584 LSExpDetectorConstruction::setupOpticks completed construction of physiWorld  m_opticksMode 1 WITH_G4CXOPTICKS  proceeding to setup Opticks
    3585 LSExpDetectorConstruction::setupOpticks ekey LSExpDetectorConstruction__setupOpticks_pmtscan no pmtscan
    3586 U::Resolve token [MultiFilmLUTMakerSvc_DIR] does not resolve
    3587 NP::save failed to U::Resolve path_ $MultiFilmLUTMakerSvc_DIR/multifilm.npy
    3588 2025-07-17 10:16:20.356 INFO  [391966] [LSExpDetectorConstruction_Opticks::Setup@45] [ WITH_G4CXOPTICKS opticksMode 1 sd 0xa628a60
    3589 2025-07-17 10:16:20.376 INFO  [391966] [G4CXOpticks::SetGeometry_JUNO@89] [
    3590 2025-07-17 10:16:20.393 INFO  [391966] [SEvt::CreateOrReuse@1206]  integrationMode 1
    3591 SNiPER is stopped by Ctrl+C
    3592 
    3593 **************************************************
    3594 Terminating @ gpu015.ihep.ac.cn on Thu Jul 17 10:16:20 2025
    3595 SNiPER::Context Running Mode = { BASIC }
    3596 SNiPER::Context SNiPER is stopped by Ctrl+C



