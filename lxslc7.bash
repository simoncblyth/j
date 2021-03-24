# .local.bash
[ "$DBG" == "1" ] && dbg_head $BASH_SOURCE

export LC_ALL="en_US.UTF-8"
export LC_CTYPE="en_US.UTF-8"

usage(){ cat << EOU
After login use afs function to AFS authenticate 
EOU
}
afs(){ type $FUNCNAME && kinit $USER && aklog -d ; }


g(){ cd $G ; }
job(){ echo $G/j/gpujob.sh ; }

so(){ cd $G/gpujob ; }
sj(){ vim $(job) ; }
sc(){ cat $(job) ; }
sr(){ srun --partition=gpu --account=junogpu --gres=gpu:v100:1 $(job) ; }
sb(){ sbatch $(job) ; squeue  ; }
sq(){ squeue ; }
sf(){
   type so
   type sj
   type sc
   type sr
   type sb
   type sq
}

rmcore(){ rm core.* ; }
rmlog(){  rm *.log ; }



[ "$DBG" == "1" ] && dbg_tail $BASH_SOURCE
