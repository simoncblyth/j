# .local.bash
[ "$DBG" == "1" ] && dbg_head $BASH_SOURCE

export LC_ALL="en_US.UTF-8"
export LC_CTYPE="en_US.UTF-8"

usage(){ cat << EOU
j/lxslc7.bash
===============

0. Login with L7 or L708 
1. Use "afs" function to AFS authenticate : giving node pw
2. cd j ; git pull : giving rsa pw 

g 
   cd to \$G $G  
job
   path to the \$(job) $(job) 
so
   cd to outputs directory 
sj
   edit the job script
sr
   srun : interactively run the job script
sb 
   sbatch : submit job script
sq
   squeue



EOU
}
afs(){ type $FUNCNAME && kinit $USER && aklog -d ; }

ipy(){ HOME=$G PYTHONPATH= /cvmfs/juno.ihep.ac.cn/sw/anaconda/Anaconda3-2020.11-Linux-x86_64/envs/root622/bin/ipython $* ; }

g(){ cd $G ; }
#job(){ echo $G/j/gpujob.sh ; }
job(){ echo $G/j/okjob.sh ; }

#so(){ cd $G/gpujob ; }
so(){ cd $G/okjob ; }
sj(){ vim $(job) ; : ~/j/lxslc7.bash ; }
sc(){ cat $(job) ; : ~/j/lxslc7.bash ; }
sr(){ srun --partition=gpu --account=junogpu --gres=gpu:v100:1 $(job) ; }
sb(){ sbatch $(job) ; squeue  ; }
sq(){ squeue ; }
squ(){ squeue -u $USER ; }
sqw(){ watch squeue -u $USER ; }
sf(){
   typeset -f so
   typeset -f sj
   typeset -f sc
   typeset -f sr
   typeset -f sb
   typeset -f sq
   typeset -f squ
   typeset -f sqw
}

rmcore(){ rm core.* ; }
rmlog(){  rm *.log ; }

bes3_conda(){
  type $FUNCNAME 
  eval "$(/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/contrib/anaconda/2023.07/bin/conda shell.bash hook)"
}

dumb(){
  : tamagotchi tokens
  type $FUNCNAME 
  kinit $USER && aklog -d
}

[ "$DBG" == "1" ] && dbg_tail $BASH_SOURCE
