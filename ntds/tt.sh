#!/bin/bash -l 

usage(){ cat << EOU
tt.sh : ntds.sh does env setup, analysis with ~/opticks/sysrap/sevt_tt.py 
==========================================================================

NEVT=0 
   ordinary single event handling, controlled by EVT
NEVT>0
   concatenated SEvt handling 

EOU
}

#nevt=3
nevt=10
#nevt=0

plot=PHO_AVG
#plot=PHO_N

PLOT=${PLOT:-$plot} NEVT=${NEVT:-$nevt}  ./ntds.sh tt

