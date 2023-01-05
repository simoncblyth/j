#!/bin/bash -l 

usage(){ cat << EOU
read_rootfile_without_root.sh
==============================

* see also np/tests/RootCheck which depends on ROOT 

build,run
   uses c++ NP::LoadVec to read the bytes of a .root file for examination
py
   uses numpy np.fromfile to load the bytes of a root file into an array.  

BUT: Interpreting the bytes without using ROOT TFile/TTree etc.. 
is not straightforward as compression is in use, see root source TFile.h etc.. 

For PMT info in standalone usage need only make a small modification 
to PMTSimParamSvc giving access to the pd_vector contiguous data
to avoid these complications.

The most appropriate juncture to do this is during geometry translation 
when it can be stored into the SSim NPFold under some experiment specific
key.  This then makes the data accessible for standalone and GPU usage:: 

    jcv PMTSimParamSvc


EOU
}


name=read_rootfile_without_root

defarg=build_run
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -std=c++11 -lstdc++ -I$HOME/np  -o /tmp/$name 
   [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1
fi 
if [ "${arg/run}" != "$arg" ]; then
   /tmp/$name
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi 


if [ "${arg/py}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $name.py 
   [ $? -ne 0 ] && echo $BASH_SOURCE py error && exit 10
fi 




