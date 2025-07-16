#!/bin/bash

#SBATCH --partition=gpu
#SBATCH --qos=debug
#SBATCH --account=junogpu
#SBATCH --job-name=muon_min
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=20480
#SBATCH --gres=gpu:v100:1


source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.0/el9_amd64_gcc11/2025_07_07/envset.sh


logging(){
   type $FUNCNAME
   export G4CXOpticks=INFO
   export SSim=INFO
   export SEvt=INFO
   export SEventConfig=INFO
}
logging  # add logging for debug of "SNiPER is stopped by Ctrl+C" ie SIGINT


export SEvt__MINTIME=1    # dump kernel launch times

export CUDA_VISIBLE_DEVICES=0

export OPTICKS_MAX_BOUNCE=63
#export OPTICKS_MAX_TIME=1000 # ns 



$(which python) \
     $(which tut_detsim.py) \
     --no-gdml \
     --pmtsd-merge-twindow 1.0 \
     --event-split \
     --output oj_edm.root \
     --user-output oj_user.root \
     --evtmax 10 \
     --seed 42 \
     hepevt \
     --exe Muon;

exit 0 


