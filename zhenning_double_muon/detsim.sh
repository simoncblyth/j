#!/bin/bash

usage(){ cat << EOU
detsim.sh
==========


info
    output variables
run
    ordinary running


zhenning_double_muon/detsim.sh

T0="2025-12-04 16:00" zhenning_double_muon/detsim.sh prof





dbg
    under gdb__
db1
    under gdb__ with manually hacked genmuon input file with _db1.txt suffix
db2
    under gdb__ with setting of extra options such as --dryrun OR --no-optical


prof
    find all SProf.txt below LOGROOT and dump time tables using ~/o/bin/SProf.py
logp
    final all OJ*.log and J*.log below LOGROOT and dump times using SDIR/logparse.py
grep
    grep @ lines in current LOGFILE



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
allarg=info_run_dbg_db1_db2_prof_grep_logp
[ -n "$BP" ] && defarg=dbg
arg=${1:-$defarg}
vv="$vv BP defarg arg allarg"


source ~/.opticks/GEOM/ENVSET.sh   ## sets ENVSET and ENVSET_NAME envvars : DOES NOT SOURCE THE ENVSET
vv="$vv ENVSET_NAME ENVSET"

opticks_mode=0
#opticks_mode=1

evtmax=1
seed=42
output=output.root
user_output=user_output.root
genmuon=j__zhenning_double_muon_seed_${seed}_evtmax_${evtmax}

test=hitlitemerged
TEST=${TEST:-$test}
vv="$vv test TEST"


pmt_hit_type=1
pmtsd_merge_twindow=1  ## always merge but do it in on CPU or GPU depending on opticks_mode_merge


if [[ "$TEST" =~ ^hit(merged|lite|litemerged)?$ ]]; then


   opticks_mode_merge=0
   opticks_max_slot=M150  ## avoid modemerged just splitting into two slices from M136 heuristic

   case $TEST in
      hit)           pmt_hit_type=1 ; opticks_mode_merge=0 ;;
      hitmerged)     pmt_hit_type=1 ; opticks_mode_merge=1 ;;
      hitlite)       pmt_hit_type=2 ; opticks_mode_merge=0 ;;
      hitlitemerged) pmt_hit_type=2 ; opticks_mode_merge=1 ;;
   esac

   IDENTITY=${ENVSET_NAME}_ok${opticks_mode}_${TEST}_seed${seed}_evtmax${evtmax}_${arg}


   if [ "${ENVSET_NAME:0:1}" == "O" ]; then
       export OPTICKS_MODE_MERGE=$opticks_mode_merge
       export OPTICKS_MAX_SLOT=$opticks_max_slot
   fi

   vv="$vv opticks_mode evtmax seed output user_output pmt_hit_type pmtsd_merge_twindow IDENTITY"
   vv="$vv ENVSET_NAME OPTICKS_MODE_MERGE OPTICKS_MAX_SLOT"

else
   printf "$BASH_SOURCE TEST[$TEST] UNHANDLED\n"
   exit 0
fi


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
fi

if [ "${arg/run}" != "$arg" -o "${arg/dbg}" != "$arg" -o "${arg/db1}" != "$arg" -o "${arg/db2}" != "$arg" ]; then

    opt=""
    topcmd=time
    if [ "${arg/run}" != "$arg" ]; then
       topcmd=time
    elif [ "${arg/dbg}" != "$arg" ]; then
       topcmd=gdb__
    elif [ "${arg/db1}" != "$arg" ]; then
       topcmd=gdb__
       genmuon0=${genmuon}
       genmuon=${genmuon}_db1
       cmd="diff -y --width=200 ${genmuon0}.txt ${genmuon}.txt"
       echo $BASH_SOURCE WARNING USING HACKED _db1.txt genmuon [$cmd]
       eval $cmd
    elif [ "${arg/db2}" != "$arg" ]; then
       topcmd=gdb__
       #opt=--dryrun
       opt=--no-optical
    fi
    vv="$vv topcmd genmuon"


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
        opt="$opt --opticks-mode ${opticks_mode}"
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
        --output $output \
        --user-output $user_output \
        hepevt \
        --exe Muon \
        --file $SDIR/${genmuon}.txt \
        2>&1 | tee -a $LOGNAME


    [ $? -ne 0 ] && echo $BASH_SOURCE - ERROR FOM tut_detsim.py && exit 1

    date
    t1=$(date)
    dt=$(seconds_between "$t0" "$t1")

    vvp
    vvp >> $LOGNAME

    popd
fi



if [[ "$arg" =~ ^(prof|prof0|logp|grep)$ ]]; then

    t0="120 minutes ago"
    T0=${T0:-$t0}
    mt=$(date "+%Y-%m-%d %H:%M:%S" -d "$T0")
    tt="t0 T0 mt"
    for t in $tt ; do printf "%30s : %s\n" "$t" "${!t}" ; done

    if [ "${arg}" == "prof0" ]; then
        find "$LOGROOT" -name SProf.txt -newermt "$mt" -exec bash -c 'echo "→ {}" && ~/o/bin/SProf.py "{}"' \;
    fi

    if [ "${arg}" == "prof" ]; then

       : order found SProf.txt paths by their modification time before parsing
       find "$LOGROOT" -name SProf.txt -newermt "$mt" -printf '%T@ %p\0' | \
             sort -z -n | \
             cut -z -d ' ' -f2- | \
             xargs -0 -n1 bash -c 'echo "→ $1" && ~/o/bin/SProf.py "$1"' bash
    fi


    if [ "${arg}" == "logp" ]; then
       find "$LOGROOT" -type f \( -name 'OJ*.log' -o -name 'J*.log' \) -newermt "$mt" -exec bash -c "echo {} " \;
       find "$LOGROOT" -type f \( -name 'OJ*.log' -o -name 'J*.log' \) -newermt "$mt" -exec bash -c "echo {} && $SDIR/logparse.py {}" \;
    fi
    if [ "${arg}" == "grep" ]; then
       find "$LOGROOT" -type f \( -name 'OJ*.log' -o -name 'J*.log' \) -newermt "$mt" -exec bash -c "echo {} " \;
       find "$LOGROOT" -type f \( -name 'OJ*.log' -o -name 'J*.log' \) -newermt "$mt" -exec bash -c "grep \" @ \" {} " \;
    fi
fi


exit 0

