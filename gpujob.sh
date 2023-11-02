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

gpujob-setup-old()
{
   local msg="=== $FUNCNAME:"
   echo $msg $USER

   rm -rf /tmp/blyth

   export JUNOTOP=/hpcfs/juno/junogpu/$USER/junotop
   export HOME=/hpcfs/juno/junogpu/$USER   # avoid /afs and control where to put .opticks/rngcache/RNG/
   # TODO: adopt OPTICKS_USERHOME that defaults to HOME in order to avoid having to change HOME to avoid AFS
   # TODO: changes relative to invoking env cause problems eg for geocache-kcd  

   source $JUNOTOP/bashrc.sh
   CMTEXTRATAGS= source $JUNOTOP/sniper/SniperRelease/cmt/setup.sh  # avoid CMT warning about unused tag opticks
   source $JUNOTOP/offline/JunoRelease/cmt/setup.sh
   mkdir -p /hpcfs/juno/junogpu/blyth/gpujob

   [ -z "$OPTICKS_PREFIX" ] && echo $msg MISSING OPTICKS_PREFIX && return 1
   # [ -n "$TMP" -a ! -d "$TMP" ] && echo $msg creating TMP $TMP && mkdir -p $TMP
   # dont do this here : try in opticks setup

   opticks-(){ . $JUNOTOP/opticks/opticks.bash && opticks-env  ; } 
   opticks-
   env | grep OPTICKS_
   env | grep TMP
}

gpujob-setup()
{
   echo $FUNCNAME
   export HOME=/hpcfs/juno/junogpu/$USER   # avoid /afs and control where to put .opticks/rngcache/RNG/

}


gpujob-head(){ 
   hostname 
   nvidia-smi   
   #opticks-info
   #opticks-paths
}
gpujob-body()
{
   local msg="=== $FUNCNAME:"
   echo $msg TMP $TMP
   #opticks-full-prepare  # create rngcache files
   #tds0
   #tds
   #opticks-t
   #ls -alst /tmp/blyth/opticks/
 
   ls -l /tmp | grep blyth
}
gpujob-tail(){
   local rc=$?    # capture the return code of prior command
   echo $FUNCNAME : rc $rc              
}

gpujob-setup
gpujob-head
gpujob-body
gpujob-tail

