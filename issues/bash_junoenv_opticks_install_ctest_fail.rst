bash_junoenv_opticks_install_ctest_fail
========================================


* opticks-full/opticks-install-extras/opticks-install-tests FAILing 

::

    2005 opticks-full()
    2006 {
    2007     local msg="=== $FUNCNAME :"
    2008     local rc
    2009 
    2010     opticks-info
    2011     [ $? -ne 0 ] && echo $msg ERR from opticks-info && return 1
    2012 
    2013     opticks-full-externals
    2014     [ $? -ne 0 ] && echo $msg ERR from opticks-full-externals && return 2
    2015 
    2016     opticks-full-make
    2017     [ $? -ne 0 ] && echo $msg ERR from opticks-full-make && return 3
    2018 
    2019     opticks-install-extras
    2020     [ $? -ne 0 ] && echo $msg ERR from opticks-install-extras && return 4
    2021 
    2022     opticks-cuda-capable
    2023     rc=$?
    2024     if [ $rc -eq 0 ]; then
    2025         echo $msg detected GPU proceed with opticks-full-prepare
    2026         opticks-full-prepare
    2027         rc=$?
    2028         [ $rc -ne 0 ] && echo $msg ERR from opticks-full-prepare && return 5
    2029     else
    2030         echo $msg detected no CUDA cabable GPU - skipping opticks-full-prepare
    2031         rc=0
    2032     fi
    2033     return 0
    2034 }


    2091 opticks-install-extras()
    2092 {
    2093    local msg="=== $FUNCNAME :"
    2094    local iwd=$PWD
    2095 
    2096    opticks-cd  ## install directory 
    2097 
    2098    echo $msg install cmake/Modules 
    2099    opticks-install-cmake-modules
    2100    [ $? -ne 0 ] && echo $msg ERROR after opticks-install-cmake-modules && return 1
    2101 
    2102    echo $msg install ctest 
    2103    opticks-install-tests
    2104    [ $? -ne 0 ] && echo $msg ERROR after opticks-install-tests && return 1
    2105 
    2106    cd $iwd
    2107    return 0
    2108 }


    2112 opticks-install-tests()
    2113 {
    2114    : formerly this was okdist-install-tests
    2115 
    2116    local msg="=== $FUNCNAME :"
    2117    local bdir=$(opticks-bdir)
    2118    local dest=$(opticks-dir)/tests
    2119    echo $msg bdir $bdir dest $dest
    2120 
    2121    : using the source tree for PYTHONPATH as this is needed
    2122    : as part of the installation
    2123 
    2124    PYTHONPATH=$(opticks-fold) CTestTestfile.py $bdir --dest $dest
    2125    local script=$dest/ctest.sh
    2126 
    2127    cat << EOT > $script
    2128 #!/bin/bash -l 
    2129 #ctest -N 
    2130 ctest --output-on-failure
    2131 EOT
    2132 
    2133    chmod ugo+x $script
    2134 }


source /home/blyth/junotop/ExternalLibs/opticks/v0.2.3/bin/opticks-setup.sh 





::

    === opticks-full-make : DONE Mon Dec 18 16:39:04 CST 2023
    === opticks-install-extras : install cmake/Modules
    === opticks-install-cmake-modules : home /home/blyth/junotop/opticks dest /home/blyth/junotop/ExternalLibs/opticks/v0.2.3
    [2023-12-18 16:39:05,288] p320232 {/home/blyth/junotop/ExternalLibs/opticks/v0.2.3/bin/CMakeModules.py:53} INFO - Copying from src /home/blyth/junotop/opticks/cmake/Modules to dst /home/blyth/junotop/ExternalLibs/opticks/v0.2.3/cmake/Modules 
    === opticks-install-extras : install ctest
    === opticks-install-tests : bdir /home/blyth/junotop/ExternalLibs/opticks/v0.2.3/build dest /home/blyth/junotop/ExternalLibs/opticks/v0.2.3/tests
    [2023-12-18 16:39:05,698] p320278 {/home/blyth/junotop/opticks/bin/CMakeLists.py:177} INFO - home $OPTICKS_HOME 
    [2023-12-18 16:39:05,699] p320278 {/home/blyth/junotop/ExternalLibs/opticks/v0.2.3/bin/CTestTestfile.py:68} INFO - root /home/blyth/junotop/ExternalLibs/opticks/v0.2.3/build 
    [2023-12-18 16:39:05,699] p320278 {/home/blyth/junotop/ExternalLibs/opticks/v0.2.3/bin/CTestTestfile.py:69} INFO - projs [] 
    [2023-12-18 16:39:05,699] p320278 {/home/blyth/junotop/ExternalLibs/opticks/v0.2.3/bin/CTestTestfile.py:136} INFO - Copying CTestTestfile.cmake files from buildtree /home/blyth/junotop/ExternalLibs/opticks/v0.2.3/build into a new destination tree /home/blyth/junotop/ExternalLibs/opticks/v0.2.3/tests 
    [2023-12-18 16:39:05,699] p320278 {/home/blyth/junotop/ExternalLibs/opticks/v0.2.3/bin/CTestTestfile.py:137} INFO - write testfile to /home/blyth/junotop/ExternalLibs/opticks/v0.2.3/tests/CTestTestfile.cmake 
    Traceback (most recent call last):
      File "/home/blyth/junotop/ExternalLibs/opticks/v0.2.3/bin/CTestTestfile.py", line 138, in <module>
        ok.write_testfile( top )
      File "/home/blyth/junotop/opticks/bin/CMakeLists.py", line 225, in write_testfile
        fp = sys.stdout if path is None else open(path, "w") 
    FileNotFoundError: [Errno 2] No such file or directory: '/home/blyth/junotop/ExternalLibs/opticks/v0.2.3/tests/CTestTestfile.cmake'
    /home/blyth/junotop/opticks/opticks.bash: line 2127: /home/blyth/junotop/ExternalLibs/opticks/v0.2.3/tests/ctest.sh: No such file or directory
    chmod: cannot access '/home/blyth/junotop/ExternalLibs/opticks/v0.2.3/tests/ctest.sh': No such file or directory
    === opticks-install-extras : ERROR after opticks-install-tests
    === opticks-full : ERR from opticks-install-extras
    ==== junoenv-opticks-command: from opticks-git clone /cvmfs/opticks.ihep.ac.cn/opticks_download_cache/plog rc 4
    ==== junoenv-opticks-command: error from function opticks-git clone /cvmfs/opticks.ihep.ac.cn/opticks_download_cache/plog
    === junoenv-opticks: junoenv-opticks-full rc 2
    === junoenv-opticks: junoenv-opticks-full rc 2
    === junoenv-opticks: rc 2
    N[blyth@localhost junoenv]$ 



