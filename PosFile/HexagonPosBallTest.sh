#!/bin/bash -l 

msg="=== $BASH_SOURCE :"
name=HexagonPosBallTest

clhep_prefix=${OPTICKS_PREFIX}_externals/clhep
g4_prefix=${OPTICKS_PREFIX}_externals/g4_1042

gcc \
    ${name}.cc \
    ${name/Test}.cc \
    -std=c++11 \
    -I$g4_prefix/include/Geant4 \
    -I$clhep_prefix/include \
    -I$HOME/np \
    -DSTANDALONE \
    -lstdc++ \
    -L$g4_prefix/lib \
    -L$clhep_prefix/lib \
    -lCLHEP \
    -o $OPTICKS_PREFIX/lib/$name

[ $? -ne 0 ] && echo $msg compile error && exit 1 

which $name



convert_csv2npy()
{
    local datadir=$JUNOTOP/offline/Simulation/DetSimV2/DetSimOptions/data
    local paths=$(ls -1 $datadir/*.csv)
    local path 
    for path in $paths
    do 
        #echo $msg path $path 
        $name $path
        [ $? -ne 0 ] && echo $msg run error && exit 2
    done
}


$name

#convert_csv2npy
#${IPYTHON:-ipython} -i $name.py 



exit 0 
    

