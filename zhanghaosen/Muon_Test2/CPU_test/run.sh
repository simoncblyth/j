#!/bin/bash

source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/setup.sh

time python $TUTORIALROOT/share/tut_detsim.py \
    --no-gdml \
    --pmtsd-merge-twindow 1.0 \
    --event-split \
    --output oj_edm_2.root \
    --user-output oj_user_2.root \
    --evtmax 1 \
    --seed 1 \
    hepevt \
    --exe Muon \
    --file file2 >& log.txt

touch done_flag_2
