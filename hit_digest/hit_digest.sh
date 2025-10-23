#!/usr/bin/env bash
usage(){ cat << EOU
~/j/hit_digest/hit_digest.sh
==============================



Checks a billion hit array (60 G) for duplicates



Many False positives seen only with large input array...

Digest: ed316f8b247fb8beaee33d58622c88 at indices: 917224521 984333385
Digest: ed316ec526d2d8d03b55161625caa17d at indices: 913909504 981018368
Digest: ed316def8cb3e2a0a1ba7132b7e8eb at indices: 915616894 982725758
Digest: ed316d73bbb24326d4cebe76d414ed8 at indices: 929348723 996457587
Digest: ed316aceae514d3e5bbd513b611f9f1 at indices: 928614562 995723426
Digest: ed316ab3f2c05f88fa2c93cf24d4c057 at indices: 901614797 968723661
Digest: ed3169da5f57135e2d1668acf2d0c525 at indices: 928534477 995643341


In [11]: md5(np.ascontiguousarray(f.hit[928534477].view(np.uint8))).hexdigest()
Out[11]: 'ed3169da5f57135e2d1668acf2d0c525'

In [12]: md5(np.ascontiguousarray(f.hit[995643341].view(np.uint8))).hexdigest()
Out[12]: 'a445d4bf500c76e1fe418b383df0e932'


EOU
}

if  [ -n "$SMALL" ]; then
    hitfold=/data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_ref1/A000
else
   #hitfold=/data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_vvvvvlarge_evt/A000  ## 60 G hit.npy
    hitfold=/data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_vvvvvvlarge_evt/A000   ## 99 G hit.npy
fi

export HITFOLD=${HITFOLD:-$hitfold}

#hitslice=[:1000000]     # 1M   no dupe
#hitslice=[:10000000]    # 10M  no dupe
#hitslice=[:50000000]    # 50M  no dupe
#hitslice=[:80000000]    # 80M
#hitslice=[:100000000]   # 100M
hitslice=[:1000000000]  # 1000M        ## 1 billion covers the full hit array
#hitslice=[]             # means no slice


export HITSLICE=${HITSLICE:-$hitslice}

#batch_size=67108864   # 67108864  0x1 << 26  : this was bandaid that avoiding input index unsigned int clocking : 64 = 0x1 << 6
batch_size=100000000  # 100M formerly gave wraparound issue

export BATCH_SIZE=${BATCH_SIZE:-$batch_size}


#name=hit_digest
name=just_digest



bin=/tmp/$name
script=$name.py

cd $(dirname $(realpath $BASH_SOURCE))

vv="BASH_SOURCE PWD name bin HITFOLD HITSLICE BATCH_SIZE"

defarg="info_build_run"
arg=${1:-$defarg}

if [ "${arg/info}" != "$arg" ]; then
    for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/build}" != "$arg" ]; then
    opt=--expt-relaxed-constexpr
    #opt=
    cmd="nvcc ${name}.cu md5.cu $opt -g -I. -I$HOME/opticks/sysrap -lssl -lcrypto  -o $bin"
    echo $cmd
    eval $cmd
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1
fi

if [ "${arg/dbg}" != "$arg" ]; then
    gdb -ex r --args $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 2
fi

if [ "${arg/run}" != "$arg" ]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/pdb}" != "$arg" -a -f "$script" ]; then
    ${IPYTHON:-ipython} --pdb -i $script
    [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 2
fi


exit 0


