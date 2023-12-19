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

Notice the lack of "bash -l" above : to retain sanity 
it is preferable for job scripts to be somewhat isolated
from the invoking environment. 

Before submitting this job with "sb" check the script 
on gateway lxslc7 with::

   /hpcfs/juno/junogpu/blyth/j/okjob.sh
   ## around 20 ctest will fail from lack of GPU 

And on workstation::

    ~/j/okjob.sh 
    GDB=1 ~/j/okjob.sh 


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


okjob-setup-junosw-opticks-pre-release()
{
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/setup.sh
}

okjob-setup-standalone-opticks_manual()
{
    export OPTICKS_CUDA_PREFIX=/usr/local/cuda-11.7

    ## below duplicates .opticks_usage_config as its better for jobs to be self contained
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.x/ExternalLibs/Boost/1.78.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.x/ExternalLibs/Xercesc/3.2.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.x/ExternalLibs/CLHEP/2.4.1.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.x/ExternalLibs/Geant4/10.04.p02.juno/bashrc

    vers=Opticks-0.0.1_alpha/x86_64-CentOS7-gcc1120-geant4_10_04_p02-dbg

#   source /hpcfs/juno/junogpu/blyth/local/$vers/bashrc                   ## copied in tarball created on workstation 
#   source /hpcfs/juno/junogpu/blyth/local/opticks_release/$vers/bashrc   ## expanded locally built tarball
    source /hpcfs/juno/junogpu/blyth/local/opticks/bashrc                 ## local build 
}



okjob-setup-junosw-opticks()
{
    source $JUNOTOP/bashrc.sh;

    # for clarity the opticks sourcing is commented in bashrc.sh to make it more visible here 
    # source /cvmfs/opticks.ihep.ac.cn/ok/releases/Opticks-v0.2.1/x86_64-CentOS7-gcc1120-geant4_10_04_p02-dbg/bashrc
    source $HOME/junotop/ExternalLibs/opticks/head/bashrc

    source $JUNOTOP/sniper/InstallArea/share/sniper/setup.sh;
    source $JUNOTOP/mt.sniper/InstallArea/bashrc;
    source $JUNOTOP/junosw/InstallArea/setup.sh
}

okjob-setup()
{
    #export HOME=/hpcfs/juno/junogpu/$USER

    #okjob-setup-junosw-opticks-pre-release
    #okjob-setup-standalone-opticks
    okjob-setup-junosw-opticks

    #okjob-paths 

    ## HMM: WHERE ELSE TO PUT ? ## PROBLEMATIC BECAUSE THIS IS WORKSTATION SPECIFIC
    export CUDA_VISIBLE_DEVICES=1  

    export TMP=$HOME/tmp   ## override default /tmp/$USER/opticks as /tmp is blackhole (not same filesystem on GPU cluster and gateway)  
    mkdir -p $TMP          ## whether override or not, need to create 
    mkdir -p $HOME/okjob
}

okjob-head(){ 
   hostname 
   nvidia-smi   
   local vars="0 HOSTNAME USER BASH_SOURCE HOME OPTICKS_PREFIX CUDA_VISIBLE_DEVICES"
   for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
   date 
}

okjob-ctest()
{
   : okjob.sh : caution this runs ctests installed by opticks-full which 
   : can become outdated vs actual tests during development 
   cd $OPTICKS_PREFIX/tests
   pwd
   echo === $BASH_SOURCE $FUNCNAME $PWD
   which ctest 
   ctest -N 
   ctest --output-on-failure
}

okjob-body()
{
   local msg="=== $FUNCNAME:"
   echo $msg TMP $TMP

   #okjob-ctest
   jok-tds
}

okjob-tail(){
   local rc=$?    # capture the return code of prior command
   echo $FUNCNAME : rc $rc              
   date  
   
   ## /tmp on gpu cluster is a black hole 
   ## any tests still writing there need to be changed to use $TMP

   echo $FUNCNAME : /tmp files belonging to $USER
   ls -alst /tmp | grep $USER
   [ -d /tmp/$USER ] && echo "find /tmp/$USER -type f" && find /tmp/$USER -type f 

}

okjob-main(){
   okjob-setup
   okjob-head
   okjob-body
   okjob-tail
}



defarg="main"
arg=${1:-$defarg}

source $HOME/j/jok.bash 

case $arg in 
   main) okjob-main ;; 
   init) jok-init ;; 
  info)  jok-info ;;
   grab) jok-grab ;;
   ana)  jok-ana ;;
report)  jok-report ;;
     *)  echo $BASH_SOURCE : arg $arg unhandled ;;
esac


