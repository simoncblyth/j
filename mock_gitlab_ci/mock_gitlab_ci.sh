#!/bin/sh

usage(){ cat << EOU

   source ~/j/mock_gitlab_ci/mock_gitlab_ci.sh

EOU
}


export JUNO_OFFLINE_BUILD_BRANCH=1  ## FOR LOCAL TESTING USE BRANCHED build and InstallArea


export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
export JUNO_OPTICKS_PREFIX=/cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
export EXTRA_BUILD_FLAGS="JUNO_CMAKE_BUILD_TYPE=Debug"
export JUNO_OFFLINE_OFF=1        # Disable JUNOSW setup prior to having built JUNOSW
export OPTICKS_SETUP_VERBOSE=1   # ~/j/gitlab-ci/mockbuild.sh shows this protects against "set -eo pipefail"
unset JUNO_OFFLINE_OFF

printf " -----------[source \$JUNOTOP/setup.sh \n"
source $JUNOTOP/setup.sh
printf " -----------]source \$JUNOTOP/setup.sh \n"


printf " -----------[source \$JUNO_OPTICKS_PREFIX/bashrc.sh \n"
source $JUNO_OPTICKS_PREFIX/bashrc
printf " -----------]source \$JUNO_OPTICKS_PREFIX/bashrc.sh \n"

cd ~/junosw



export CUDA_VISIBLE_DEVICES=""

printf " -----------[./oj_initialize.sh \n"
env $EXTRA_BUILD_FLAGS OJ_DEBUG=1 BP=cudaMalloc ./oj_initialize.sh
printf " -----------]./oj_initialize.sh \n"


