#!/bin/bash -l 

DIR=$(dirname $BASH_SOURCE)

tlog_path=/tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/ntds2.tlog
export TLOG_PATH=${TLOG_PATH:-$tlog_path}

if [ -n "$DBG" ]; then 
   ${IPYTHON:-ipython} --pdb -i $DIR/tlog.py 
else
   ${PYTHON:-python}  $DIR/tlog.py 
fi


