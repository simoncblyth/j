#!/bin/bash
usage(){ cat << EOU
ResolveTest.sh
===============

A[blyth@localhost junosw]$ ~/j/ResolveTest/ResolveTest.sh /data/Detector/Geometry/PMTPos_CD_LPMT.csv
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Geometry/PMTPos_CD_LPMT.csv

A[blyth@localhost junosw]$ ~/j/ResolveTest/ResolveTest.sh /data/Detector/Geometry/PMTPos_WP_LPMT.csv
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv

EOU
}


cd $(dirname $(realpath $BASH_SOURCE))
name=ResolveTest
bin=/tmp/$name

DPH=$HOME/junosw/Utilities/DataPathHelper

[ ! -f $bin ] && gcc $name.cc $DPH/src/Path.cc -I$DPH -std=c++17 -lstdc++ -o $bin 

$bin $*


