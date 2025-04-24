#!/bin/bash

#SBATCH --partition=gpu
#SBATCH --qos=debug
#SBATCH --account=junogpu
#SBATCH --job-name=okjob
#SBATCH --ntasks=1
#SBATCH --output=/hpcfs/juno/junogpu/%u/okjob/%j.out
#SBATCH --error=/hpcfs/juno/junogpu/%u/okjob/%j.err
#SBATCH --mem-per-cpu=20480
#SBATCH --gres=gpu:v100:1

okjob-notes(){ cat << EON
okjob-notes
=============

EON
}

okjob-paths()
{
    local vars="BASH_SOURCE FUNCNAME CMAKE_PREFIX_PATH PKG_CONFIG_PATH PATH LD_LIBRARY_PATH DYLD_LIBRARY_PATH PYTHONPATH MANPATH CPATH";
    local var;
    for var in $vars;
    do
        echo $var;
        echo ${!var} | tr ":" "\n";
        echo;
    done
}



okjob-setup-ok()
{
    : Q. Does it make sense to incorporate the below into the OK bashrc ? 
    : A. NO - as opticks must work with expt frameworks which need to depend on these same externals
    :    so they must be done separately - this could be done within OJ however as that
    :    collapses the generality to the JUNO framework and geometry

    type $FUNCNAME

    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Xercesc/3.2.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/CLHEP/2.4.7.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/custom4/0.1.8/bashrc

    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Python/3.9.19/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/python-numpy/1.23.5/bashrc

    #local v=0.3.8
    local v=0.3.9
    source /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v$v/bashrc
}

okjob-setup-oj()
{
    : OJ setup much simpler than OK as OJ collapses the generality  
    type $FUNCNAME
    source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.3.6/el9_amd64_gcc11/Fri/envset.sh  
    #source $HOME/junotop/bashrc.sh
}



okjob-setup()
{
    local home=/hpcfs/juno/junogpu/$USER
    [ -d "$home" ] && export HOME=$home   
    export TMP=$HOME/tmp   ## override default /tmp/$USER/opticks as /tmp is blackhole (not same filesystem on GPU cluster and gateway)  
    mkdir -p $TMP          ## whether override or not, need to create 
    mkdir -p $HOME/okjob

    unset CMAKE_PREFIX_PATH
    unset PKG_CONFIG_PATH

    okjob-setup-ok
    #okjob-setup-oj
}

okjob-head(){ 
   hostname 
   nvidia-smi   
   local vars="0 HOSTNAME USER BASH_SOURCE HOME OPTICKS_PREFIX CUDA_VISIBLE_DEVICES"
   for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
   date 
}



okjob-ctest-tmp()
{
    : prior to this getting into release do it here 
    : workaround ctest not working from readonly dir by copying to tmp

    type $FUNCNAME

    local ttmp=/tmp/$USER/opticks/tests
    TTMP=${TTMP:-$ttmp}
    mkdir -p $TTMP
    cp -r $OPTICKS_PREFIX/tests/. ${TTMP}/

    cd $TTMP
    pwd

    ctest -N
    ctest --output-on-failure
}


okjob-ctest()
{
   : okjob.sh : caution this runs ctests installed by opticks-install-tests now called from okdist-install-update
   pwd
   echo === $BASH_SOURCE $FUNCNAME $PWD
   which ctest 
   cat $OPTICKS_PREFIX/tests/ctest.sh

   $OPTICKS_PREFIX/tests/ctest.sh 
}

okjob-body()
{
   local msg="=== $FUNCNAME:"
   echo $msg TMP $TMP

   okjob-ctest-tmp

   #okjob-ctest
   #opticks-t
   #jok-tds
   #tut_detsim.py --evtmax 1 gun

}

okjob-tail(){
   local rc=$?    # capture the return code of prior command
   echo $FUNCNAME : rc $rc              
   date  

   okjob-check-tmp   
}

okjob-main(){
   okjob-setup
   okjob-head
   okjob-body
   okjob-tail
}


okjob-check-tmp()
{
   : /tmp on gpu cluster is a black hole 
   : instead of using /tmp write to TMP $TMP

   echo $FUNCNAME : /tmp files belonging to $USER
   [ -d /tmp/$USER ] && echo "find /tmp/$USER -type f" && find /tmp/$USER -type f 
}



#source $HOME/j/jok.bash 

defarg="main"
arg=${1:-$defarg}

case $arg in 
   main) okjob-main ;; 
  ctest) okjob-ctest ;; 
  setup) okjob-setup ;; 
   head) okjob-head ;; 
   init) jok-init ;; 
  info)  jok-info ;;
   grab) jok-grab ;;
   scpmeta) jok-scpmeta ;;
   ana)  jok-ana ;;
report)  jok-report ;;
     *)  echo $BASH_SOURCE : arg $arg unhandled ;;
esac


