#!/bin/bash -l 

pfx=$JUNOTOP/data/Simulation/DetSim
paths=$(find $pfx/Material -type f)

for path in $paths 
do 
    rel=${path/$pfx\/}
    rel=${rel//\//.} 
    echo $rel
    MaterialTest $rel 
done


