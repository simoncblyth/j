#!/bin/bash -l 

msg="=== $BASH_SOURCE :"
name=RadiusTest 

gcc $name.cc -std=c++11 -lstdc++ -o $OPTICKS_PREFIX/lib/$name
[ $? -ne 0 ] && echo $msg compile error && exit 1

which $name 
$name  
[ $? -ne 0 ] && echo $msg run error && exit 2

exit 0 


