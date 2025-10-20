#!/usr/bin/env bash

usage(){ cat << EOU


~/j/hit_digest/md5_test.sh

From ~/cuda-hashing-algos/md5_test.sh

Using:  git@github.com:simoncblyth/cuda-hashing-algos.git



The digest of "hello" matches the one from:

* ~/opticks/sysrap/tests/sdigest_test.sh


EOU
}


nam=md5
name=${nam}_test
bin=/tmp/$name

cd $(dirname $(realpath $BASH_SOURCE))

vv="BASH_SOURCE PWD nam name bin"
for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done

cmd="nvcc ${nam}.cu ${name}.cu -I. -o $bin"
echo $cmd
eval $cmd
[ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2

exit 0 


