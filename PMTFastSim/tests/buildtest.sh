#!/bin/bash -l
usage(){ cat << EOU
buildtest.sh 
==============


EOU
}

#defkls=ALL
#defkls=MultiFilmModel
defkls=Layr
kls=${1:-$defkls}

get_srcs()
{
    local name=${1:-TComplex}
    local srcs
    case $name in 
                 Layr) srcs="${name}Test.cc" ;;
             TComplex) srcs="${name}Test.cc" ;;
               Matrix) srcs="../$name.cc ${name}Test.cc" ;;
             Material) srcs="../$name.cc ${name}Test.cc" ;;
                Layer) srcs="../$name.cc ${name}Test.cc ../Matrix.cc ../Material.cc" ;;
        OpticalSystem) srcs="../$name.cc ${name}Test.cc ../Layer.cc ../Matrix.cc ../Material.cc" ;;
       MultiFilmModel) srcs="../$name.cc ${name}Test.cc ../OpticalSystem.cc ../Layer.cc ../Matrix.cc ../Material.cc" ;; 
    esac
    echo $srcs
}

if [ "$kls" == "ALL" ]; then 
    klss="TComplex Matrix Material Layer OpticalSystem MultiFilmModel"
else
    klss="$kls"
fi 
          

for kls in $klss ; do 
    srcs=$(get_srcs $kls)
    echo $BASH_SOURCE kls $kls srcs $srcs
    gcc $srcs \
        -std=c++11 -lstdc++ \
          -I. \
          -I/usr/local/cuda/include \
          -I$HOME/np \
          -I..
          -DWITH_THRUST \
          -o /tmp/${kls}Test 

    [ $? -ne 0 ] && echo $BASH_SOURCE build error for kls $kls && exit 1

    /tmp/${kls}Test 
    [ $? -ne 0 ] && echo $BASH_SOURCE run error for kls $kls && exit 2

done


if [ "$kls" == "Layr" ]; then
    ${IPYTHON:-ipython} --pdb -i LayrTest.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error for kls $kls && exit 3
fi 

exit 0 


