offline-opticks-oo-npy-boost-filesystem-missing-symbols
==========================================================

issue seems fixed by cleaninstall
---------------------------------------------

::

    npy
    om-cleaninstall



DONE : by modifying junoenv/junoenv-opticks.sh 
-------------------------------------------------

* HMM : this kinda issue could be made much less likely by 
  including the opticks precursor function in the standard 
  offline+opticks jre. 

* Then the dangerous practice of manually just having the 
  precursor without the rest of the jre would be avoided.   



oo : update build fails
-------------------------

The starting point was trying to run without jre ...
so that is clearly unwise.

Must remember to jre before opticks operations 
as otherwise the build will find the wrong boost.


* https://github.com/gnuradio/gnuradio/issues/2432

::

    [ 54%] Linking CXX executable NPriTest
    [ 54%] Linking CXX executable NRngDiffuseTest
    ../libNPY.so: undefined reference to `boost::filesystem::path::parent_path() const'
    collect2: error: ld returned 1 exit status
    ../libNPY.so: undefined reference to `boost::filesystem::path::parent_path() const'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/NSliceTest] Error 1
    make[1]: *** [tests/CMakeFiles/NSliceTest.dir/all] Error 2
    make[2]: *** [tests/EnvTest] Error 1
    make[1]: *** Waiting for unfinished jobs....
    make[1]: *** [tests/CMakeFiles/EnvTest.dir/all] Error 2
    ../libNPY.so: undefined reference to `boost::filesystem::path::parent_path() const'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/NTrisTest] Error 1
    make[1]: *** [tests/CMakeFiles/NTrisTest.dir/all] Error 2
    ../libNPY.so: undefined reference to `boost::filesystem::path::parent_path() const'
    collect2: error: ld returned 1 exit status
    ../libNPY.so: undefined reference to `boost::filesystem::path::parent_path() const'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/GLMFormatTest] Error 1
    make[1]: *** [tests/CMakeFiles/GLMFormatTest.dir/all] Error 2
    make[2]: *** [tests/NTreeToolsTest] Error 1
    make[1]: *** [tests/CMakeFiles/NTreeToolsTest.dir/all] Error 2
    ../libNPY.so: undefined reference to `boost::filesystem::path::parent_path() const'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/NCSGDataTest] Error 1


BUT ~/opticks/examples/UseBoostFS works
------------------------------------------

* Add example using parent_path.  But it works.  Maybe the oo build managing to find wrong boost ?
* the reason is that the jre was setup before trying this


::

    Install the project...
    -- Install configuration: "Debug"
    -- Installing: /data/blyth/junotop/ExternalLibs/opticks/head/lib/UseBoostFS
    -- Set runtime path of "/data/blyth/junotop/ExternalLibs/opticks/head/lib/UseBoostFS" to "$ORIGIN/../lib64:$ORIGIN/../externals/lib:$ORIGIN/../externals/lib64:$ORIGIN/../externals/OptiX/lib64"
    UseBoostFS::dump_file_size: "/data/blyth/junotop/ExternalLibs/opticks/head/lib/UseBoostFS" 382472
    UseBoostFS::dump_version 1.77.0
     path /data/blyth/junotop/ExternalLibs/opticks/head/lib/UseBoostFS p /data/blyth/junotop/ExternalLibs/opticks/head/lib/UseBoostFS pp /data/blyth/junotop/ExternalLibs/opticks/head/lib
    N[blyth@localhost UseBoostFS]$ 





