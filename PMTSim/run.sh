#!/bin/bash -l 

# setenv done in the executable
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
