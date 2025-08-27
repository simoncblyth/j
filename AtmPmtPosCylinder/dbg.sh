#!/bin/bash

usage(){ cat << EOU

~/j/AtmPmtPosCylinder/dbg.sh

Needs OJ env such as from : loj/local_oj


HMM : EASIER TO USE ipc

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

which gdb
which python
which tut_detsim.py

gdb \
    $(which python)  \
    $(which tut_detsim.py) 



