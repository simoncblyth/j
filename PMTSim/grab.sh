#!/bin/bash -l 
usage(){ cat << EOU

jcopy grabs classes into j/PMTsim for standalone testing
EOU
}


cd $HOME/j/PMTSim


grab_0()
{
    : these where used to develop ZSolid cutting of the PMTs

    jcopy \
        HamamatsuR12860PMTManager \
        Hamamatsu_R12860_PMTSolid \
        ellipse_intersect_circle  \
                          \
        NNVTMCPPMTManager \
        NNVT_MCPPMT_PMTSolid  

}

grab_1()
{
    : look into possible issue with PMT masks or Opticks translation 

    jcopy \
        HamamatsuMaskManager 
 

}

grab_1



