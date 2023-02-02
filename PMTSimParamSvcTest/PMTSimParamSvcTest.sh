#!/bin/bash -l 
usage(){ cat << EOU
PMTSimParamSvcTest.sh
======================

Performs scans over all PMTs and saves .npy outputs 
into directories with the name of the branch in the path.

Workflow::

   cd $JUNOTOP/junosw
   git branch    # list the branches 

   # checkout one of the branches to test:
   git checkout main 

   ./build_Debug.sh    # build the branch 

   cd ~/j
   git pull

   cd PMTSimParamSvcTest
   ./PMTSimParamSvcTest.sh    # build against the junosw built above, and run  


Then repeat the above procedure for a different branch being tested, eg::

   cd $JUNOTOP/junosw
   git checkout blyth-66-low-dependency-PMT-data-access

NB make sure to rebuild both junosw and the test after checkout
of the different branch 

EOU
}

bin=PMTSimParamSvcTest
defarg="build_run_ana"
arg=${1:-$defarg}

sdir=$(pwd)

base=/tmp/$USER/j/$(basename $sdir)
bdir=$base/build 
idir=$base/install
odir=$base/output

export BRANCH=$(cd $JUNOTOP/junosw ; git rev-parse --abbrev-ref HEAD)   # git branch --show-current
export FOLD=$odir/$BRANCH
mkdir -p $FOLD

info(){ cat << EOI
PMTSimParamSvcTest.sh/info
----------------------------

   bin  $bin
   sdir $sdir
   bdir $bdir
   idir $idir
   odir $odir
   BRANCH $BRANCH
   FOLD $FOLD

EOI
}
info

if [ "${arg/usage}" != "$arg" ]; then
    usage
fi 

if [ "${arg/build}" != "$arg" ]; then

    rm -rf $bdir && mkdir -p $bdir && cd $bdir && pwd 
    rm -rf $idir && mkdir -p $idir

    cmake $sdir -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$idir 
    [ $? -ne 0 ] && echo $BASH_SOURCE cmake error && exit 1 

    make
    [ $? -ne 0 ] && echo $BASH_SOURCE make error && exit 2 

    make install   
    [ $? -ne 0 ] && echo $BASH_SOURCE install error && exit 3 
fi 

if [ "${arg/run}" != "$arg" ]; then 
    $idir/bin/$bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 4
fi 

if [ "${arg/ana}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $sdir/$bin.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 5 
fi 

info 

exit 0



