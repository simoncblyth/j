gitlab_ci_issue_after_cuda_update_for_blackwell
=================================================

Issue : Gitlab JUNOSW+Opticks build fail due to lack of "/usr/local/cuda-13.1/targets/x86_64-linux/include"
------------------------------------------------------------------------------------------------------------

Gitlab CI pipelines failing with::

    Make Error in Simulation/GenTools/CMakeLists.txt:
  Imported target "Opticks::G4CX" includes non-existent path
    "/usr/local/cuda-13.1/targets/x86_64-linux/include"
  in its INTERFACE_INCLUDE_DIRECTORIES.  Possible reasons include:
  * The path was deleted, renamed, or moved to another location.
  * An install or uninstall procedure did not complete successfully.
  * The installation package was faulty and references files it does not
  provide.
    CMake Error in Simulation/DetSimV2/PMTSim/CMakeLists.txt:
      Imported target "Opticks::G4CX" includes non-existent path
        "/usr/local/cuda-13.1/targets/x86_64-linux/include"
      in its INTERFACE_INCLUDE_DIRECTORIES.  Possible reasons include:
      * The path was deleted, renamed, or moved to another location.
      * An install or uninstall procedure did not complete successfully.
      * The installation package was faulty and references files it does not
      provide.
    ...
    -- Generating done (26.1s)
    CMake Generate step failed.  Build files cannot be regenerated correctly.


Cause
-------

Opticks releases onto cvmfs of v0.6.4 and beyond jumped to CUDA 13.1 
in order to support Blackwell GPUs but the docker image being used by gitlab-ci
is based off CUDA 12.4::

     54 .opticks_build_job_template:
     55   extends: .job_template
     56   stage: build
     57   image: simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9
     58   variables:
     59     JUNO_CLANG_PREFIX:
     60     JUNO_OPTICKS_PREFIX: /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
     61     EXTRA_BUILD_FLAGS: JUNO_CMAKE_BUILD_TYPE=Debug
     62   script:
     63     - printf "[ ================ BUILD PHASE OF BUILD JOB =========================\n"
     64     - for repo in juno.ihep.ac.cn opticks.ihep.ac.cn; do if [ ! -d /cvmfs/$repo ]; then sudo mkdir /cvmfs/$repo; fi; sudo mount -t cvmfs $repo /cvmfs/$repo; done
     65     - source .gitlab-ci/oj_helper.sh EMIT_ENV_CHECK
     66     - mkdir InstallConfig
     67     - source .gitlab-ci/oj_helper.sh EMIT_ENV    > InstallConfig/ENV.bash
     68     - cat InstallConfig/ENV.bash
     69     - source .gitlab-ci/oj_helper.sh EMIT_ENVSET > InstallConfig/envset.sh
     70     - cat InstallConfig/envset.sh
     71     - export JUNO_OFFLINE_OFF=1        # Disable JUNOSW setup prior to having built JUNOSW
     72     - export OPTICKS_SETUP_VERBOSE=1   # ~/j/gitlab-ci/mockbuild.sh shows this protects against "set -eo pipefail"
     73     - source $JUNOTOP/setup.sh
     74     - if [ -n "$JUNO_CLANG_PREFIX" ]; then source $JUNO_CLANG_PREFIX/bashrc; fi
     75     - if [ -n "$JUNO_OPTICKS_PREFIX" ]; then source $JUNO_OPTICKS_PREFIX/bashrc; fi
     76     - env $EXTRA_BUILD_FLAGS ./build.sh
     77     - cp InstallConfig/ENV.bash  InstallArea/ENV.bash
     78     - cp InstallConfig/envset.sh InstallArea/envset.sh
     79     - unset JUNO_OFFLINE_OFF # now that it has been built the below needs the JUNOSW environment for tut_detsim.py running
     80     - printf "] ================ BUILD PHASE OF BUILD JOB =========================\n"
     81     - printf "[ ================ TEST PHASE OF BUILD JOB =========================\n"
     82     - env $EXTRA_BUILD_FLAGS ./oj_initialize.sh
     83     - printf "] ================ TEST PHASE OF BUILD JOB =========================\n"
     84 
     

Review : How did I create the docker image : "simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9" ?
-----------------------------------------------------------------------------------------------------

:doc:`review_creation_of_simoncblyth_cuda_runtimeplus_docker_image`






Fix Approach 1 : Create docker image for CUDA 13.1
----------------------------------------------------- 


