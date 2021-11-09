#!/bin/bash -l 

rel=data/Simulation/DetSim/Material
src=P:junotop/$rel
dst=$JUNOTOP/$rel
mkdir -p $dst 

scp -r $src/* $dst/


