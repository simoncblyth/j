#!/bin/bash

######## Part 1 #########
#SBATCH --partition=gpu
#SBATCH --qos=debug
#SBATCH --account=junogpu
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=16000
#SBATCH --gpus=v100:1
#SBATCH --job-name=test_ok_clu

######## Part 2 #########
# Replace the following lines with your real workload

usage(){ cat << EOU

This is adapted from YDY test script::

  /hpcfs/juno/junogpu/yangdingyong/datas/test/2025_04_18/test/test.sh
 
Submit from L with::
 
    sbatch test.sh 

TODO: output directory control

EOU
}


lscpu
nvidia-smi

vv="0 PWD BASH_SOURCE CUDA_VISIBLE_DEVICES OPTICKS_PREFIX"
vvp(){ for v in $* ; do printf "%20s : %s\n" "$v" "${!v}" ; done ; }
vvp $vv 

export CUDA_VISIBLE_DEVICES=0
export PIP=INFO

mkdir ok_clu
pushd ok_clu
source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.3.6/el9_amd64_gcc11/Wed/envset.sh;



knobs()
{
   type $FUNCNAME 

   local exceptionFlags
   local debugLevel
   local optLevel

   #exceptionFlags=STACK_OVERFLOW   
   exceptionFlags=NONE

   debugLevel=DEFAULT
   #debugLevel=NONE
   #debugLevel=FULL    ## FULL now causes an exception with OptiX 7.5 Driver Version: 515.43.04  CUDA Version: 11.7

   optLevel=DEFAULT
   #optLevel=LEVEL_0
   #optLevel=LEVEL_3

   #export PIP__max_trace_depth=1
   export PIP__CreatePipelineOptions_exceptionFlags=$exceptionFlags # NONE/STACK_OVERFLOW/TRACE_DEPTH/USER/DEBUG
   export PIP__CreateModule_debugLevel=$debugLevel  # DEFAULT/NONE/MINIMAL/MODERATE/FULL   (DEFAULT is MINIMAL)
   export PIP__linkPipeline_debugLevel=$debugLevel  # DEFAULT/NONE/MINIMAL/MODERATE/FULL   
   export PIP__CreateModule_optLevel=$optLevel      # DEFAULT/LEVEL_0/LEVEL_1/LEVEL_2/LEVEL_3  

   env | grep PIP__ 


   rm /var/tmp/OptixCache_$USER/optix7cache.db    ## delete the cache to see the compilation output every time 
   export Ctx=INFO
   export PIP=INFO
   #export CSGOptiX=INFO
}
knobs


vvp $vv 

ls -alst $OPTICKS_PREFIX/ptx/CSGOptiX_generated_CSGOptiX7.cu.ptx

which tut_detsim.py

tut_detsim.py \
    --evtmax 10 \
    --seed 42 \
    --output "ok_clu.root" \
    --user-output "ok_clu_user_.root" \
    --anamgr-normal-hit \
    gun \
    --momentums 10.0;

touch done_flag
popd
