#!/bin/bash

usage(){ cat << EOU


BP=G4VUserTrackInformation::SetUserInformation ~/j/zhenning_double_muon/detsim.sh dbg

BP=NormalTrackInfo::NormalTrackInfo ~/j/zhenning_double_muon/detsim.sh 
BP=NormalTrackInfo::~NormalTrackInfo  ~/j/zhenning_double_muon/detsim.sh 

BP=G4VUserTrackInformation::G4VUserTrackInformation ~/j/zhenning_double_muon/detsim.sh dbg

BP=C4OpBoundaryProcess::PostStepDoIt ~/j/zhenning_double_muon/detsim.sh



0. ~/j/zhenning_double_muon/genmuon.sh generate muon file
1. ENVSET bash function : pick an environment, with or without Opticks
2. ~/j/zhenning_double_muon/detsim.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
SDIR=$PWD


vvp(){ local v ; for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done ; }
vv=""
vv="$vv BASH_SOURCE SDIR PWD"

#defarg=run
defarg=info
allarg=info_run_dbg_prof_grep_logp
[ -n "$BP" ] && defarg=dbg
arg=${1:-$defarg}
vv="$vv BP defarg arg allarg"


source ~/.opticks/GEOM/ENVSET.sh   ## sets ENVSET and ENVSET_NAME envvars : DOES NOT SOURCE THE ENVSET
vv="$vv ENVSET_NAME ENVSET"

opticks_mode=0
evtmax=1
seed=42
output=output.root
user_output=user_output.root
genmuon=j__zhenning_double_muon_seed_${seed}_evtmax_${evtmax}.txt
pmt_hit_type=2
pmtsd_merge_twindow=1
IDENTITY=${ENVSET_NAME}_ok${opticks_mode}_hit${pmt_hit_type}_merge${pmtsd_merge_twindow}_seed${seed}_evtmax${evtmax}_${arg}
vv="$vv opticks_mode evtmax seed output user_output pmt_hit_type pmtsd_merge_twindow IDENTITY"


LOGBASE=/data1/blyth/tmp
LOGREL=j/zhenning_double_muon/detsim
LOGROOT=$LOGBASE/$LOGREL
LOGDIR=$LOGROOT/$IDENTITY
LOGNAME=$IDENTITY.log
LOGFILE=$LOGDIR/$LOGNAME
vv="$vv LOGBASE LOGREL LOGROOT LOGDIR LOGNAME LOGFILE"


seconds_between() {
    local d1="$1"
    local d2="$2"
    local ts1=$(date -d "$d1" +%s) || return 1
    local ts2=$(date -d "$d2" +%s) || return 1
    echo $(( ts2 - ts1 ))
}

gdb__ ()
{
    : j//detsim.sh
    if [ -z "$BP" ]; then
        H="";
        B="";
        T="-ex r";
    else
        H="-ex \"set breakpoint pending on\"";
        B="";
        for bp in $BP;
        do
            B="$B -ex \"break $bp\" ";
        done;
        T="-ex \"info break\" -ex r";
    fi;
    local runline="gdb $H $B $T --args $* ";
    echo $runline;
    date;
    eval $runline;
    date
}





if [ "${arg/info}" != "$arg" ]; then
    vvp
    vvp > vvp.log
fi



if [ "${arg/run}" != "$arg" -o "${arg/dbg}" != "$arg" ]; then

    topcmd=time
    if [ "${arg/run}" != "$arg" ]; then
       topcmd=time
    elif [ "${arg/dbg}" != "$arg" ]; then
       topcmd=gdb__
    fi
    vv="$vv topcmd"

    if [ -n "$ENVSET" -a -f "$ENVSET" ]; then
        source $ENVSET
    else
        echo $BASH_SOURCE - ERROR - MISSING ENVSET $ENVSET
        exit 1
    fi

    if [ -n "$OPTICKS_PREFIX" ]; then
        MSG="OPTICKS RUNNING"
        export SEvt__MINTIME=1    # dump kernel launch times
        export OPTICKS_MAX_BOUNCE=63
        export SProf__WRITE=1   # enable the time and memory profiling
    else
        MSG="NON OPTICKS RUNNING"
    fi
    vv="$vv MSG"


    date
    t0=$(date)
    vv="$vv t0 t1 dt"


    mkdir -p $LOGDIR
    pushd $LOGDIR
    rm -f $LOGNAME
    vvp > $LOGNAME

    $topcmd \
        $(which python) \
        $(which tut_detsim.py) \
        --opticks-mode ${opticks_mode} \
        --evtmax ${evtmax} \
        --seed ${seed} \
        --no-gdml \
        --pmt-hit-type $pmt_hit_type \
        --pmtsd-merge-twindow $pmtsd_merge_twindow \
        --replace-param "Material.LS.scale.AbsorptionLenAfter:86.5,Material.Water.scale.abs_after:133.6*m" \
        --event-split \
        --anamgr-muon \
        --anamgr-tt \
        --output $output \
        --user-output $user_output \
        hepevt \
        --exe Muon \
        --file $SDIR/$genmuon \
        2>&1 | tee -a $LOGNAME


    [ $? -ne 0 ] && echo $BASH_SOURCE - ERROR FOM tut_detsim.py && exit 1

    date
    t1=$(date)
    dt=$(seconds_between "$t0" "$t1")

    vvp
    vvp > vvp.log
    vvp >> $LOGNAME

    popd
fi


if [ "${arg/prof}" != "$arg" ]; then
    find "$LOGROOT" -name SProf.txt -exec bash -c 'echo "→ {}" && ~/o/bin/SProf.py "{}"' \;
fi

if [ "${arg/grep}" != "$arg" ]; then
    grep " @ "  $LOGFILE
fi

if [ "${arg/logp}" != "$arg" ]; then
    find "$LOGROOT" -type f \( -name 'OJ*.log' -o -name 'J*.log' \) -exec bash -c "echo {} " \;
    find "$LOGROOT" -type f \( -name 'OJ*.log' -o -name 'J*.log' \) -exec bash -c "echo {} && $SDIR/logparse.py {}" \;
fi



exit 0

