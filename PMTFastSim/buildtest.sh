#!/bin/bash -l

name=${1:-Matrix}
case $name in 
   Matrix)   srcs="$name.cc ${name}Test.cc" ;;
   Material) srcs="$name.cc ${name}Test.cc" ;;
   Layer)    srcs="$name.cc ${name}Test.cc Matrix.cc Material.cc" ;;
esac

echo $BASH_SOURCE name $name srcs $srcs


gcc $srcs -std=c++11 -lstdc++ -I. -o /tmp/${name}Test && /tmp/${name}Test 
