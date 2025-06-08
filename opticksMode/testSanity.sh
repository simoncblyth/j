#!/bin/bash   

gdb__ () 
{ 
    if [ -z "$BP" ]; then
        H="";
        B="";
        T="-ex r";
    else
        H="-ex \"set breakpoint pending on\"";
        B="";
        for bp in $BP;
        do
            B="$B -ex \"break $bp\" ";
        done;
        T="-ex \"info break\" -ex r";
    fi;
    local runline="gdb $H $B $T --args $* ";
    echo $runline;
    date;
    eval $runline;
    date
}

BASE=$(basename $BASH_SOURCE)
STEM=${BASE/.sh}

DIR=/tmp/$USER/j/$STEM
mkdir -p $DIR

source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/setup.sh


cd $DIR

gdb__ \
    $(which python) \
    $(which tut_detsim.py) \
    --output edm.root \
    --user-output user.root \
    --evtmax 1 \
    --seed 42 \
    gun \
    --momentums 1.0;

echo DIR $DIR

