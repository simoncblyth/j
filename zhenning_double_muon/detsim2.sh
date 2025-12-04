#!/bin/bash

usage(){ cat << EOU

  ~/j/zhenning_double_muon/detsim2.sh info
  ~/j/zhenning_double_muon/detsim2.sh run

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
#tests="hit hitmerged hitlite hitlitemerged"
tests="hit hitlite"
TESTS=${TESTS:-$tests}

for t in $TESTS ; do
  (
      TEST=$t ./detsim.sh $*
      [ $? -ne 0 ] && printf "$BASH_SOURCE ERROR FROM [TEST=$t ./detsim.sh $*]\n" && exit 1
  ) 
done

exit 0

