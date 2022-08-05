#!/bin/bash 

cat << EOC


svn revert Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
svn revert Simulation/DetSimV2/PMTSim/include/Hamamatsu_R12860_PMTSolid.hh
svn revert Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
svn revert Simulation/DetSimV2/PMTSim/include/NNVT_MCPPMT_PMTSolid.hh
svn revert Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
svn revert Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc
svn revert Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
svn revert Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc

rm Simulation/DetSimV2/PMTSim/src/ZCanvas.h
rm Simulation/DetSimV2/PMTSim/src/ZSolid.cc
rm Simulation/DetSimV2/PMTSim/src/ZSolid.h

EOC


