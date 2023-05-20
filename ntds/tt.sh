#!/bin/bash -l 

usage(){ cat << EOU
tt.sh
======

NEVT=0 
   ordinary single event handling, controlled by EVT
NEVT>0
   concatenated SEvt handling 

EOU
}

nevt=3   

plot=PHO_AVG
#plot=PHO_N

PLOT=${PLOT:-$plot} NEVT=${NEVT:-$nevt}  ./ntds.sh tt

