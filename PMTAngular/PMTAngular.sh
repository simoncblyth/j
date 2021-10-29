#!/bin/bash -l 

name=PMTAngular

notes(){ cat << EON
Using DYLD_FALLBACK_LIBRARY_PATH rather than DYLD_LIBRARY_PATH avoids vecLib libLAPACK.dylib incompatibility issue
--------------------------------------------------------------------------------------------------------------------

::

    DYLD_LIBRARY_PATH=/Users/blyth/miniconda3/lib /tmp/PMTAngular/PMTAngular
    dyld: Library not loaded: /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/libLAPACK.dylib
      Referenced from: /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/vecLib
      Reason: Incompatible library version: vecLib requires version 1.0.0 or later, but libLAPACK.dylib provides version 0.0.0
    ./PMTAngular.sh: line 45: 22118 Abort trap: 6           DYLD_LIBRARY_PATH=/Users/blyth/miniconda3/lib /tmp/PMTAngular/PMTAngular


* https://stackoverflow.com/questions/3146274/is-it-ok-to-use-dyld-library-path-on-mac-os-x-and-whats-the-dynamic-library-s

EON
}


if [ "$(uname)" == "Darwin" ]; then 
   #var=DYLD_LIBRARY_PATH
   var=DYLD_FALLBACK_LIBRARY_PATH 
   ROOT_PREFIX=$HOME/miniconda3
else
   var=LD_LIBRARY_PATH
   ROOT_PREFIX=$JUNOTOP/ExternalLibs/ROOT/6.22.08
fi 

mkdir -p /tmp/$name
gcc $name.cc \
    -std=c++11 \
    -I$HOME/np \
    -I$ROOT_PREFIX/include \
    -L$ROOT_PREFIX/lib \
    -lstdc++ \
    -lCore \
    -lHist \
    -o /tmp/$name/$name

[ $? -ne 0 ] && echo compile error && exit 1 


runcmd(){ cat << EOC
$var=$ROOT_PREFIX/lib /tmp/$name/$name
EOC
}


runcmd
eval $(runcmd)
[ $? -ne 0 ] && echo run error && exit 2


ipython -i PMTAngular.py 


exit 0 
   

