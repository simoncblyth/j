#!/bin/bash -l 
usage(){ cat << EOU
build.sh
=========



EOU
}


SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)

name=main_v3
TEXINPUTS=$SDIR

vars="BASH_SOURCE name TEXINPUTS"

defarg="info_build_open"
arg=${1:-$defarg}

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done
fi 

if [ "${arg/tex}" != "$arg" ]; then
   vi $name.tex
   [ $? -ne 0 ] && echo $BASH_SOURCE : tex error && exit 1 
fi



if [ "${arg/build}" != "$arg" ]; then
   pdflatex $name
   [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 
fi


if [ "${arg/open}" != "$arg" ]; then
   open $name.pdf
   [ $? -ne 0 ] && echo $BASH_SOURCE : open error && exit 2
fi

exit 0 

