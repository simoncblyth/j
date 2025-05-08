#!/bin/bash

lscpu

mkdir j_clu
pushd j_clu

export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0
pushd $JUNOTOP &> /dev/null;
source setup.sh;
popd &> /dev/null

time python $TUTORIALROOT/share/tut_detsim.py \
    --output jsw_edm.root \
    --user-output jsw_user.root \
    --evtmax 1000 \
    --seed 42 \
    gun \
    --momentums 1.0;

touch done_flag
popd
