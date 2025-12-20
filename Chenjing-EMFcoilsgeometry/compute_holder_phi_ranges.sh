#!/bin/bash

usage(){ cat << EOU

~/j/Chenjing-EMFcoilsgeometry/compute_holder_phi_ranges.sh

EOU
}


cd $(dirname $(realpath $BASH_SOURCE))

name=compute_holder_phi_ranges
bin=/tmp/$name

g++ -std=c++11 $name.cpp -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE g++ error && exit 1 


$bin
[ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2

exit 0



