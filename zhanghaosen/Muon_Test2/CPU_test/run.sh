#!/bin/bash

usage(){ cat << EOU

~/j/zhanghaosen/Muon_Test2/CPU_test/run.sh

EOU
}

path=$(realpath $BASH_SOURCE)
fold=$(dirname $path)
relfold=${fold:$(( 1+${#HOME} ))}

tm=/tmp/$USER
export TM=${TM:-$tm}
DIR=$TM/$relfold
mkdir -p $DIR
cd $DIR

vv=""
vv="$vv BASH_SOURCE BASH_VERSION path fold relfold tm TM DIR PWD"
pvv(){ for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done ; } 

defarg=run
arg=${1:-$defarg}

vv="$vv defarg arg"
pvv

if [ "${arg/run}" != "$arg" ]; then

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/setup.sh

   gdb \
    -ex r \
    --args \
    $(which python) \
    $(which tut_detsim.py) \
    --no-gdml \
    --pmtsd-merge-twindow 1.0 \
    --event-split \
    --output oj_edm_2.root \
    --user-output oj_user_2.root \
    --evtmax 1 \
    --seed 1 \
    hepevt \
    --exe Muon \
    --file $fold/file2

   touch done_flag_2

fi

pvv

