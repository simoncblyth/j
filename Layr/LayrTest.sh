#!/bin/bash -l 
usage(){ cat << EOU
LayrTest.sh
=============


::

    OPT=Axspa PIDX=0,2,4 ./LayrTest.sh ana

    PIDX=0,2,4  ./LayrTest.sh ana   # pick one of each lpmtcat to plot 

    In[1]:f.lpmtid
    Out[1]:array([0,10,55,98,100,137,1000,10000,17611],dtype=int32)

    In[2]:f.lpmtcat
    Out[2]:array([1,1,0,0,2,0,1,2,1],dtype=int32)



::

   OPT=ARTQspx ./LayrTest.sh ana



SysRap lib only needed for WITH_THRUST GPU running
but the NP.hh header is needed in both cases

HMM : it seems out of proportion that need to wheel in the SysRap lib 
just for SU.cc functionality ... TODO: header only su.h ? 

EOU
}

name="LayrTest"

defarg=info_build_run_ana
arg=${1:-$defarg}

opt="-std=c++11 -I. -I/usr/local/cuda/include -I$OPTICKS_PREFIX/include/SysRap"
c4opt="-I$HOME/customgeant4"
linkflags="-lstdc++"

WITH_THRUST=1     # comment for CPU only test
WITH_STACKSPEC=1

if [ -n "$WITH_THRUST" ]; then 
    opt="$opt -DWITH_THRUST"
    linkflags="$linkflags -L$OPTICKS_PREFIX/lib -lSysRap"
    echo $BASH_SOURCE : WITH_THRUST config  
else
    echo $BASH_SOURCE : not WITH_THRUST config 
fi

if [ -n "$WITH_STACKSPEC" ]; then
    opt="$opt -DWITH_STACKSPEC"
    echo $BASH_SOURCE : WITH_STACKSPEC config  
else
    echo $BASH_SOURCE : not WITH_STACKSPEC config 
fi 


fold=/tmp/$USER/opticks/$name/4

# Formerly had separate LAYRTEST_MODE holding 4 OR 2 
# Now combining that MODE with the BASE to make more standard.

export FOLD=$fold
export LAYRTEST_BASE=$fold

export SFOLD=/tmp/SPMT_test
export QFOLD=/tmp/QPMTTest
export PFOLD=/tmp/QPMT_Test
export MFOLD=/tmp/QPMT_MockTest

#export LAYRTEST_HALF=1

pmtcat=R12860
#pmtcat=NNVTMCP 
#pmtcat=NNVTMCP_HiQE
#pmtcat=EGet

excl=0.05
#excl=0


export LAYRTEST_PMTCAT=$pmtcat
export LAYRTEST_WL=440
export LAYRTEST_EXCL=$excl

vars="LAYRTEST_PMTCAT LAYRTEST_WL LAYRTEST_EXCL LAYRTEST_BASE FOLD SFOLD QFOLD" 

if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/clean}" != "$arg" ]; then
    rm -rf $fold
fi 

if [ "${arg/build}" != "$arg" ]; then

    mkdir -p $fold
    if [ "${opt/WITH_THRUST}" != "$opt" ]; then

        cmds=( "gcc  -c $name.cc $opt $c4opt -o $fold/$name.o"
               "nvcc -c $name.cu $opt -o $fold/${name}_cu.o"
               "nvcc -o $fold/$name $linkflags $fold/$name.o $fold/${name}_cu.o " 
               "rm $fold/$name.o $fold/${name}_cu.o "
            )
    else
        cmds=( "gcc   $name.cc $opt $c4opt $linkflags -o  $fold/$name" )
    fi 

    for cmd in "${cmds[@]}"; do
        echo "$cmd"
        eval "$cmd" 
        [ $? -ne 0 ] && echo $BASH_SOURCE :  error with : $cmd  && exit 1
    done
fi

if [ "${arg/run}" != "$arg" ]; then
    $fold/$name
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/ana}" != "$arg" ]; then
    ${IPYTHON:-ipython} --pdb -i $name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3
fi 

if [ "$arg" == "mpcap" -o "$arg" == "mppub" ]; then
    export CAP_BASE=$FOLD/figs
    export CAP_REL=LayrTest
    export CAP_STEM=LayrTest_${LAYRTEST_INCL}_${LAYRTEST_PMTCAT}
    # /Users/blyth/env/bin/mpcap.sh
    case $arg in
       mpcap) source mpcap.sh cap  ;;   
       mppub) source mpcap.sh env  ;;  
    esac
        
    if [ "$arg" == "mppub" ]; then
        source epub.sh 
    fi      
fi              

exit 0 

