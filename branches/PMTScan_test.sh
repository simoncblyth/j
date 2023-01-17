#!/bin/bash -l 

export GEOM=${GEOM:-J006}
name=PMTScan_test
export FOLD=$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/juno/PMTScan

${IPYTHON:-ipython} --pdb -i $name.py 
[ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 1 

exit 0 

