#!/bin/bash -l
name=PMT_test 
bin=/tmp/$name
opt=-Wtautological-overlap-compare
INCDIR=$JUNOTOP/junosw/Detector/Geometry/Geometry

pwd && gcc $name.cc -g $opt -std=c++11 -lstdc++ -I$INCDIR -o $bin && $bin

