#!/bin/bash -l 
usage(){ cat << EOU
stamp.sh
=========

The "./ntds.sh tt" sets up the environment that points to the 
SEvt to load while the analysis is implemented in 
python script $OPTICKS_HOME/sysrap/sevt_tt.py 

::

    jxn
    STAMP_TT=100k,2k ~/j/ntds/stamp.sh 
    STAMP_TT=102k,2k ~/j/ntds/stamp.sh 
    STAMP_TT=104k,2k ~/j/ntds/stamp.sh 

    STAMP_TT=100k,20k ~/j/ntds/stamp.sh 

The stamp.sh script reqires the STAMP_TT envvar to be set, 
try commandlines such as the above. 

EOU
}

if [ -z "$STAMP_TT" ]; then 
   usage
   exit 0 
fi 

stamp_tt=100k,2k
PLOT=STAMP STAMP_TT=${STAMP_TT:-$stamp_tt} STAMP_ANNO=1 ~/j/ntds/ntds.sh tt

