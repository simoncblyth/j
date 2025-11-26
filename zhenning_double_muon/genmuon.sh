#!/usr/bin/env bash

usage(){ cat << EOU

~/j/zhenning_double_muon/genmuon.sh


A[blyth@localhost ~]$ Muon.exe -h
./Muon.exe [-seed seed] 
           [-o outputfilename] 
           [-n nevents] 
           [-s juno (juno, juno_original)] 
           [-v volume (Rock, TT, WP)]
           [-r rotating mountain(Yes, No)] 
           [-mult single or real muon (0, 1)] 
           [-ntrks events of n tracks selection] 
           [-wpo only the muon events whose track pass through water pool] 
           [-cdls only the muon events whose track pass through CD LS] 
           [-rocko only the muon events whose track traverse rock and avoid WP] 
           [-stop only the muon events whose energy is less than 20 GeV] 
           [-cdWater only the muon events whose track pass through the CD water buffer] 
           [-use-elecroom] [-no-elecroom]  (default: ElecRoom ON; adds two full-size ElecRoom wings to envelope)] 
           [-rockThickness <millimeters> (rock thickness T; default 10000 mm)] 
           [-music_dir <path of music files relative to this dir>] 
A[blyth@localhost ~]$ 


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


