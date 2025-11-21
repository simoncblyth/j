#!/usr/bin/env bash

usage(){ cat << EOU

~/j/zhenning_double_muon/genmuon.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

vv="BASH_SOURCE PWD evtmax seed genmuon"
vvp(){ local v ; for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done ; }


seed=42
evtmax=1
genmuon=j__zhenning_double_muon_seed_${seed}_evtmax_${evtmax}.txt


source ~/.opticks/GEOM/ENVSET.sh
if [ -n "$ENVSET" -a -f "$ENVSET" ]; then
    source $ENVSET
else
    echo $BASH_SOURCE - ERROR - MISSING ENVSET $ENVSET
    exit 1
fi



Muon.exe \
     -seed ${seed} \
     -o ${genmuon} \
     -n ${evtmax} \
     -s juno -v WP -r Yes -cdls -mult 1 -ntrks 2 \
     -music_dir /cvmfs/juno-wg.ihep.ac.cn/Simulation/data/sandbox/MC25A/dbdata/offline-data/Generator/Muon/conf2507a


