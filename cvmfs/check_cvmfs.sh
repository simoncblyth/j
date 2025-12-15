#!/bin/bash 



repos="juno.ihep.ac.cn opticks.ihep.ac.cn"

for repo in $repos 
do

    echo ls /cvmfs/$repo
    ls /cvmfs/$repo

    echo curl -I http://cvmfs-stratum-one.ihep.ac.cn:8000/cvmfs/$repo/
    curl -I http://cvmfs-stratum-one.ihep.ac.cn:8000/cvmfs/$repo/

done 







