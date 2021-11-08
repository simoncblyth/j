#!/bin/bash -l 

export JUNO_PMT20INCH_POLYCONE_NECK=ENABLED 

name=PMTSimTest
which $name

if [ -n "$DEBUG" ]; then
    if [ "$(uname)" == "Darwin" ]; then
        lldb__ $name
    else
        gdb -ex r --args $name
    fi 
else
    $name
fi


#ipython -i ZSolids.py 


