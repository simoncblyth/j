#! /bin/bash

#================== Part 1 : job parameters =====================
#SBATCH --partition=gpu
#SBATCH --qos=normal
#SBATCH --account=junogpu
#SBATCH --job-name=detsim_muon
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=20480
#SBATCH --gpus=v100:1

source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.4/el9_amd64_gcc11/2025_09_30/envset.sh

i0=$1
i=$((i0+0))


if [ -d "/hpcfs/juno/junogpu" ]; then
    #BASE=/hpcfs/juno/junogpu/wangjiabin/opticks
    BASE=/hpcfs/juno/junogpu/$USER/opticks
else
    BASE=/tmp/juno/junogpu/$USER/opticks 
fi 

DetPath=$BASE/detsim
log_path=$BASE/log
GenPath=$BASE
odir=$BASE
mkdir -p "$log_path" "$DetPath" "$GenPath" "$odir"

inf="${DetPath}/detsim_user-${i}.root"

logging(){
   type "${FUNCNAME}" || true
   export G4CXOpticks=INFO
   export SSim=INFO
   export SEvt=INFO
   export SEventConfig=INFO
}

export SEvt__MINTIME=1     # dump kernel launch times
# export CUDA_VISIBLE_DEVICES=0

export OPTICKS_MAX_BOUNCE=63
evtmax=5
seed="${i}"

echo "Input (will be produced): $inf"
echo "Output dir: $odir"

echo "######--- Generator:"

gen="${GenPath}/gen-${i}.txt"
if [ ! -f "$gen" ]; then
    #srun -n 1 \
    Muon.exe -seed "${seed}" -o "$gen" -n "${evtmax}" -s juno -v WP -r Yes -wpo
else
    echo "Use preexisting gen[$gen] "
fi

echo "######--- detsim start"

#srun -n 1 \
#/usr/bin/time -vv \

source dbg__.sh

dbg__ \
  $(which python) \
   "${TUTORIALROOT}/share/tut_detsim.py" \
    --no-gdml --anamgr-tt --anamgr-muon \
    --EnableUserOutput --evtmax "${evtmax}" --seed "${i}" \
    --pmtsd-v2 --pmt-hit-type 2 --pmtsd-merge-twindow 1.0 \
    --event-split --event-split-maxhits 300 \
    --output "${DetPath}/detsim-${i}.root" \
    --user-output "${DetPath}/detsim_user-${i}.root" \
    --detoption Acrylic hepevt --exe Muon --file ${GenPath}/gen-${i}.txt \
  2>&1 | tee "${odir}/detsim_${i}.log"

echo "######--- detsim done"
