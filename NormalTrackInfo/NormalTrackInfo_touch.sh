#!/bin/bash

usage(){ cat << EOU

Moved here from top level of JUNOSW

EOU
}


defarg=touch_ls
arg=${1:-$defarg}

if [ "${arg/touch}" != "$arg" ]; then

    find . -type f \( -name "*.cc" -o -name "*.cpp" \) \
    -exec grep -lq "NormalTrackInfo\.hh" {} \; -print | \
    xargs touch

fi

if [ "${arg/ls}" != "$arg" ]; then

    find . -type f \( -name "*.cc" -o -name "*.cpp" \) \
    -exec grep -lq "NormalTrackInfo\.hh" {} \; -print | \
    xargs ls -alst

    date
fi


