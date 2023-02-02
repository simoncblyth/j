#!/bin/bash -l 

sdir=$(pwd)
bdir=/tmp/$USER/j/$(basename $sdir)/build 
idir=/tmp/$USER/j/$(basename $sdir)/install

rm -rf $bdir && mkdir -p $bdir && cd $bdir && pwd 
rm -rf $idir && mkdir -p $idir

cmake $sdir \
     -DCMAKE_BUILD_TYPE=Debug \
     -DCMAKE_INSTALL_PREFIX=$idir 

make
make install   

echo sdir $sdir
echo bdir $bdir
echo idir $idir


