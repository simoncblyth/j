#!/bin/bash -l 

usage(){ cat << EOU
grab_back.sh
==============

Emits to stdout the commands to copy files from PWD inside j 
back into offline SVN.

*jcopyback* works only for classes that are already present in 
the offline


EOU
}




cd $HOME/j/PMTSim

jcopyback \
    HamamatsuR12860PMTManager \
    Hamamatsu_R12860_PMTSolid \
    ellipse_intersect_circle  \
                      \
    NNVTMCPPMTManager \
    NNVT_MCPPMT_PMTSolid  



jps_add \
     ZSolid.hh \
     ZSolid.cc \
     ZCanvas.hh 



