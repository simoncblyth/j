#!/bin/bash

function gen_file(){
source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/setup.sh
Muon.exe -n $1 -o file$1 -seed $1 -cdWater
}

gen_file $1

