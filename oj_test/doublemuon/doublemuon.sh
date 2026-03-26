#!/bin/bash 

doublemuon_usage(){ cat << EOU
doublemuon.sh
==============

::

    ~/j/oj_test/doublemuon/doublemuon.sh run
    ~/j/oj_test/doublemuon/doublemuon.sh dbg

Or use shortcut::

     ojdm run
     ojdm dbg



EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
SDIR=$PWD
SNAM=$(basename $BASH_SOURCE)
SNAM=${SNAM/.sh}
SREL=${SDIR/$HOME\/}/$SNAM
SREL_NOTE="SREL is HOME relative folder/name of a script used for output folders"


vvp(){ local v ; for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done ; } 
vv=""
vv="$vv BASH_SOURCE SDIR SNAM SREL SREL_NOTE PWD"

defarg=info
allarg=info_help_run
arg=${1:-$defarg}
vv="$vv defarg arg allarg"


source ~/.opticks/GEOM/ENVSET.sh  # sets ENVSET, ENVSET_NAME
ENVSET_NOTE="NB ENVSET.sh script DOES NOT source the envset.sh script that it points to"
vv="$vv ENVSET_NAME ENVSET ENVSET_NOTE"

source ~/.opticks/TEST/TEST.sh    ## sets TEST envvar
vv="$vv TEST"


if [[ "$arg" =~ help ]]; then
    doublemuon_usage
    exit 0
fi


topcmd=time
opticks_mode=1
opt=""
evtmax=1
seed=42
genmuon=$HOME/j/zhenning_double_muon/j__zhenning_double_muon_seed_42_evtmax_1.txt

source ~/j/oj_test/oj_test.sh   ## define common bash functions - requires TEST and ENVSET_NAME
oj_test_TEST_into_options

qq="pmt_hit_type pmtsd_merge_twindow opticks_mode_merge_override opticks_max_slot"
for q in $qq ; do
   if [ -z "${!q}" ] ; then
       echo $BASH_SOURCE - FATAL MISSING $q ${!q} 
       type oj_test_TEST_into_options
       exit 1
   fi 
done

export OPTICKS_MODE_MERGE_OVERRIDE=$opticks_mode_merge_override
export OPTICKS_MAX_SLOT=$opticks_max_slot

IDENTITY=${ENVSET_NAME}_ok${opticks_mode}_${TEST}_seed${seed}_evtmax${evtmax}_${arg}   
# The appended arg prevents "dbg" running stomping on "run" running

OLD_LOGBASE=/data1/blyth/tmp

logbase=/data1/$USER     # skip the tmp
LOGBASE=${LOGBASE:-$logbase}
LOGROOT=$LOGBASE/$SREL       # LOGROOT contains all outputs from this script
LOGDIR=$LOGROOT/$IDENTITY    # IDENTITY distinguishes between different invokations of this script
LOGNAME=$IDENTITY.log
ENVNAME=$IDENTITY.env
LOGFILE=$LOGDIR/$LOGNAME
vv="$vv LOGBASE SREL LOGROOT LOGDIR LOGNAME ENVNAME LOGFILE"


if [[ "$arg" =~ env|run|dbg ]]; then


   if [ -n "$ENVSET" -a -f "$ENVSET" ]; then
        source $ENVSET
    else
        echo $BASH_SOURCE - ERROR - MISSING ENVSET $ENVSET
        exit 1
    fi

    if [ -n "$OPTICKS_PREFIX" ]; then
        MSG="OPTICKS RUNNING"

        export SEvt__MINTIME=1            # dump kernel launch times
        export OPTICKS_MAX_BOUNCE=63      # MaxBounceDefault is 31
        export SProf__WRITE=1             # enable the time and memory profiling
        export U4Solid__IsFlaggedLVID=87

        opt="$opt --opticks-mode ${opticks_mode}"
    else
        MSG="NON OPTICKS RUNNING"
    fi
    vv="$vv MSG"

fi

if [[ "$arg" =~ info ]]; then
    vvp
fi


if [[ "$arg" =~ run|dbg ]]; then

    [ -z "$OPTICKS_PREFIX" ] && echo $BASH_SOURCE - FATAL - MISSING OPTICKS_PREFIX && exit 1

    if [[ "$arg" =~ dbg ]]; then
       source dbg__.sh
       topcmd=dbg__
    fi

    mkdir -p $LOGDIR
    pushd $LOGDIR

        d0=$(date)
        vv="$vv d0"
        rm -f $LOGNAME
        touch $LOGNAME
        vvp | tee -a $LOGNAME
        env > $ENVNAME

        $topcmd \
            $(which python) \
            $(which tut_detsim.py) \
            $opt \
            --evtmax ${evtmax} \
            --seed ${seed} \
            --no-gdml \
            --pmt-hit-type $pmt_hit_type \
            --pmtsd-merge-twindow $pmtsd_merge_twindow \
            --replace-param "Material.LS.scale.AbsorptionLenAfter:86.5,Material.Water.scale.abs_after:133.6*m" \
            --event-split \
            --anamgr-muon \
            --anamgr-tt \
            --output output.root \
            --user-output user_output.root \
            hepevt \
            --exe Muon \
            --file $genmuon \
            2>&1 | tee -a $LOGNAME


        [ $? -ne 0 ] && echo $BASH_SOURCE - ERROR FROM tut_detsim.py && exit 1

        d1=$(date)
        dt=$(seconds_between "$d0" "$d1")
        vv="$vv d1 dt"

        vvp | tee -a $LOGNAME
    popd
fi

exit 0
