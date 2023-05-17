#!/bin/bash -l 
usage(){ cat << EOU
stamp.sh
=========

::

    jxn
    STAMP_TT=100k,2k ~/j/ntds/stamp.sh 
    STAMP_TT=102k,2k ~/j/ntds/stamp.sh 
    STAMP_TT=104k,2k ~/j/ntds/stamp.sh 

    STAMP_TT=100k,20k ~/j/ntds/stamp.sh 

EOU
}

if [ -z "$STAMP_TT" ]; then 
   usage
   exit 0 
fi 

stamp_tt=100k,2k
PLOT=STAMP STAMP_TT=${STAMP_TT:-$stamp_tt} STAMP_ANNO=1 ~/j/ntds/ntds.sh tt

