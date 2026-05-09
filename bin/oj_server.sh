#!/bin/bash
usage(){ cat << EOU

~/j/bin/oj_server.sh

This uses ~/j/local.sh bash functions:

lco
    provides "fastapi" from miniconda "ok" python virtual env


NOTE ENVIRONMENT SUBTLETY - USING lco MEANS DIFFERNT libcurl TO THE ONE USED TO BUILD
IN THIS CASE SHOULD NOT CAUSE ISSUE AS SERVER NOT USING LIBCURL AT C++ LEVEL ANYHOW
- THAT IS HANDLED BY FASTAPI/PYTHON


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

source $HOME/vip/vip.bash
vip-init-local-base

source $HOME/j/local.sh

lo    ## full opticks
lco   ## miniconda "ok" env with fastapi


defarg="info_run"
arg=${1:-$defarg}

vv="BASH_SOURCE PWD defarg arg"


if [[ "$arg" =~ info ]]; then
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [[ "$arg" =~ run ]]; then
   ~/opticks/CSGOptiX/tests/CSGOptiXService_FastAPI_test/CSGOptiXService_FastAPI_test.sh
   [ $? -ne 0 ] && echo $BASH_SOURCE - ERROR FROM run && exit 1
fi

exit 0

