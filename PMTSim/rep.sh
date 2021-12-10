#!/bin/bash -l

for i in $(seq 1000) ; do
   echo $i 
   PMTSolidTest 
   [ $? -ne 0 ] && echo ERROR && exit 1  
done

exit 0


