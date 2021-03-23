#!/bin/bash

#SBATCH --partition=gpu
#SBATCH --qos=debug
#SBATCH --account=junogpu
#SBATCH --job-name=gpujob
#SBATCH --ntasks=1
#SBATCH --output=/hpcfs/juno/junogpu/blyth/gpujob/%j.out
#SBATCH --error=/hpcfs/juno/junogpu/blyth/gpujob/%j.err
#SBATCH --mem-per-cpu=20480
#SBATCH --gres=gpu:v100:1

tds(){ 
    local opts="--opticks-mode 1 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 10"
    tds- $opts
}
tds0(){ 
    : run with opticks disabled
    local opts="--opticks-mode 0 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 10"
    tds- $opts
}
tds-label(){
    local label="tds";
    local arg;
    for arg in $*;
    do
        case $arg in 
            --no-guide_tube)           label="${label}_ngt"  ;;
            --pmt20inch-polycone-neck) label="${label}_pcnk" ;;
            --pmt20inch-simplify-csg)  label="${label}_sycg" ;;
        esac;
    done
    echo $label 
}

tds-(){ 
    local msg="=== $FUNCNAME :"
    local label=$(tds-label $*)
    local dbggdmlpath="$HOME/${label}_202103.gdml"
    echo $msg label $label dbggdmlpath $dbggdmlpath;
    export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="--dbggdmlpath $dbggdmlpath"
    local script=$JUNOTOP/offline/Examples/Tutorial/share/tut_detsim.py;
    local args="gun";
    local iwd=$PWD;
    local dir=$HOME/tds;
    mkdir -p $dir;
    cd $dir;
    local runline="python $script $* $args ";
    echo $runline;
    date;
    eval $runline;
    date;
    cd $iwd
}



gpujob-setup()
{
   local msg="=== $FUNCNAME:"
   echo $msg $USER
   export JUNOTOP=/hpcfs/juno/junogpu/blyth/junotop
   export HOME=/hpcfs/juno/junogpu/blyth   # avoid /afs and control where to put .opticks/rngcache/RNG/

   source $JUNOTOP/bashrc.sh
   source $JUNOTOP/sniper/SniperRelease/cmt/setup.sh
   source $JUNOTOP/offline/JunoRelease/cmt/setup.sh
   mkdir -p /hpcfs/juno/junogpu/blyth/gpujob
   [ -z "$OPTICKS_PREFIX" ] && echo $msg MISSING OPTICKS_PREFIX && return 1
   opticks-(){ . $JUNOTOP/opticks/opticks.bash && opticks-env  ; } 
   opticks-
   env | grep OPTICKS_
   env | grep TMP
}

gpujob-head(){ 
   hostname 
   nvidia-smi   
   opticks-info
   opticks-paths
   #UseOptiX  TODO:use an always built executable instead of this optional one
}
gpujob-body()
{
   #opticks-full-prepare  # create rngcache files
   #tds0
   tds
   #opticks-t
}
gpujob-tail(){
   local rc=$?    # capture the return code of prior command
   echo $FUNCNAME : rc $rc              
}

gpujob-setup
gpujob-head
gpujob-body
gpujob-tail

