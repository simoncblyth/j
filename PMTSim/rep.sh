#!/bin/bash -l

for i in $(seq 100) ; do
   echo $i 
   lldb__ PMTSolidTest 
   [ $? -ne 0 ] && echo ERROR && exit 1  
done

exit 0


