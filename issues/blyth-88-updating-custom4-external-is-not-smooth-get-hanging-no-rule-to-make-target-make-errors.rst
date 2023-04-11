blyth-88-updating-custom4-external-is-not-smooth-get-hanging-no-rule-to-make-target-make-errors
=================================================================================================


::

    N[blyth@localhost ~]$ l  /data/blyth/junotop/ExternalLibs/custom4/
    total 4
    0 drwxrwxr-x.  4 blyth blyth   62 Apr  8 03:10 0.1.3
    0 drwxrwxr-x.  4 blyth blyth   32 Apr  8 03:10 .
    0 drwxrwxr-x.  4 blyth blyth   62 Mar 29 23:05 0.0.8
    4 drwxrwxr-x. 39 blyth blyth 4096 Mar 24 01:30 ..
    N[blyth@localhost ~]$ rm -rf /data/blyth/junotop/ExternalLibs/custom4/0.0.8


::

    [ 39%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/IGenTool.cc.o
    [ 39%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/PostGenTools.cc.o
    [ 39%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/binding.cc.o
    make[2]: *** No rule to make target `/data/blyth/junotop/ExternalLibs/custom4/0.0.8/lib64/libCustom4.so', needed by `lib/libGenTools.so'.  Stop.
    make[1]: *** [Simulation/GenTools/CMakeFiles/GenTools.dir/all] Error 2
    make: *** [all] Error 2
    N[blyth@localhost build]$ 


"cd build ; make clean" doesnt do enough.
To avoid the GenTools "No rule to make target" need to do nuclear re-build::

    N[blyth@localhost build]$ cd ..
    N[blyth@localhost junosw]$ rm -rf build
    N[blyth@localhost junosw]$ ./build_Debug.sh 



Same problem with Opticks::

    -- Generating done
    -- Build files have been written to: /data/blyth/junotop/ExternalLibs/opticks/head/build/u4
    Consolidate compiler generated dependencies of target U4
    make[2]: *** No rule to make target `/data/blyth/junotop/ExternalLibs/custom4/0.0.8/lib64/libCustom4.so', needed by `libU4.so'.  Stop.
    make[2]: *** Waiting for unfinished jobs....
    [  5%] Building CXX object CMakeFiles/U4.dir/U4Material.cc.o
    [  5%] Building CXX object CMakeFiles/U4.dir/U4SolidMaker.cc.o
    [  5%] Building CXX object CMakeFiles/U4.dir/U4_LOG.cc.o

Need::

     u4
     om-cleaninstall
     gx
     om-cleaninstall
     oo








