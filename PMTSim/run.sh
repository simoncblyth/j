#!/bin/bash -l 

export JUNO_PMT20INCH_POLYCONE_NECK=ENABLED 

if [ "$(uname)" == "Darwin" ]; then
   #lldb__ PMTSimTest 
   PMTSimTest 
else
   gdb -r ex --args PMTSimTest 
fi 

#ipython -i ZSolids.py 


