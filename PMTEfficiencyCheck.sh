#!/bin/bash 

name=$(basename $0)
stem=${name/.sh}

usage(){ cat << EOU
Grab inputs from remote note P with::

   ./PMTEfficiencyCheck.sh grab 

Using rsync options::

    r:recursive
    t:preserve modification times
    z:compress
    --progress   

EOU
}


if [ "$1" == "grab" ]; then
    dir=/tmp/$USER/opticks/$stem
    mkdir -p $dir
    cmd="rsync -rtz --progress P:/tmp/$USER/opticks/$stem/ /tmp/$USER/opticks/$stem/"
    echo $cmd
    eval $cmd
fi

cmd="ipython -i $stem.py"
echo $cmd
eval $cmd


