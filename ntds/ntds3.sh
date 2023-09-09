#!/bin/bash -l 
usage(){ cat << EOU
ntds3.sh
==========

::

    ~/j/ntds/ntds3.sh info

    PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh 
    PICK=AB MODE=3 SEL=1 ~/j/ntds/ntds3.sh 


EOU
}

defarg="info_ana"
arg=${1:-$defarg}

name=ntds3
SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
source $HOME/.opticks/GEOM/GEOM.sh 
export BASE=/tmp/$USER/opticks/GEOM/$GEOM/ntds3/ALL1
export AFOLD=$BASE/p001
export BFOLD=$BASE/n001
script=$SDIR/$name.py 

vars="BASH_SOURCE arg name SDIR GEOM BASE AFOLD BFOLD script"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/ana}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script 
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 1 
fi

if [ "$arg" == "pvcap" -o "$arg" == "pvpub" -o "$arg" == "mpcap" -o "$arg" == "mppub" ]; then
    case $PICK in
      A) cap_base=$AFOLD/figs ; cap_stem=ntds3_${GEOM}_A${APID} ;;
      B) cap_base=$BFOLD/figs ; cap_stem=ntds3_${GEOM}_B${BPID} ;;
    esac
    if [ -z "$cap_base" -o -z "$cap_stem" ]; then 
       echo $BASH_SOURCE : ERROR :  pvcap/pvpub/mpcap/mppub require PICK=A or PICK=B : AB OR BA are not allowed 
       exit 2 
    fi
    export CAP_STEM=$cap_stem   # stem of the .png screencapture
    export CAP_BASE=$cap_base
    export CAP_REL=ntds3
    case $arg in  
       pvcap) source pvcap.sh cap  ;;  
       mpcap) source mpcap.sh cap  ;;  
       pvpub) source pvcap.sh env  ;;  
       mppub) source mpcap.sh env  ;;  
    esac
    if [ "$arg" == "pvpub" -o "$arg" == "mppub" ]; then 
        source epub.sh 
    fi  
fi 

exit 0 

