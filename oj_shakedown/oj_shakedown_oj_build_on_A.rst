DONE oj_shakedown_oj_build_on_A
=================================

Following the .gitlab-ci.yml build environment added oj_build and oj_local::

     41 elif [ "$VIP_MODE" == "oj_build" ]; then
     42 
     43    # follow .gitlab-ci.yml
     44    export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
     45    export JUNO_OPTICKS_PREFIX=/cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
     46    export JUNO_OFFLINE_OFF=1
     47    export OPTICKS_SETUP_VERBOSE=1
     48 
     49    source $JUNOTOP/setup.sh
     50    if [ -n "$JUNO_OPTICKS_PREFIX" ]; then source $JUNO_OPTICKS_PREFIX/bashrc; fi
     51 
     52    # needed to "rm -rf build" to remove the docker container build dir
     53    oj_build(){  cd $HOME/junosw ; ./build_Debug.sh ; }
     54 


Initially got CMake cache error, related to a /home/juno build (from the Docker container build testing).
Avoided that with::

    cd ~/junosw
    rm -rf build 

Lots of cling warnings::

    Warning in cling::IncrementalParser::CheckABICompatibility():
      Possible C++ standard library mismatch, compiled with __GLIBCXX__ '20231218'
      Extraction of runtime standard library version was: '20240719'
    Warning in cling::IncrementalParser::CheckABICompatibility():
      Possible C++ standard library mismatch, compiled with __GLIBCXX__ '20231218'
      Extraction of runtime standard library version was: '20240719'





