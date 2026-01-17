#!/bin/sh
usage(){ cat << EOU

  c4  
  ~/j/Custom4/vdif.sh  C4CustomART.h

EOU
}


path=$1
echo "vimdiff <(git show main:$path) <(git show v0.1.8_transient:$path)"
vimdiff <(git show main:$path) <(git show v0.1.8_transient:$path)

