#!/bin/bash -l 
usage(){ cat << EOU
GetPVMultiTest.sh 
==================

EOU
}

geoms=$(cat << EOG
tub3BodyPhys
tub3Inner1Phys
tub3Inner2Phys
tub3CntrPhys
EOG
)

bin=GetPVTest

for geom in $geoms ; do 
   echo $geom 
   GEOM=$geom $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : run $bin error : WITH GEOM $geom  && exit 1 
done 

exit 0 


