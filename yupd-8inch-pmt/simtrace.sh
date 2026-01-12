
usage(){ cat << EOU

lo  # get into opticks OJ env
. simtrace.sh

EOU
}

(

   export EYE=0,-700,0 
   export NOXGEOM=1 
   export CIRCLE=-65.5,0,-82.5,22.999,65.5,0,-82.5,22.999 

   export LINE=-65.5,0,-82.5,0,0,0
   export LINE2=65.5,0,-82.5,0,0,0
   export LINE3=-65.5,0,-82.5,65.5,0,-82.5

   export POINT=-65.5,0,-82.5,65.5,0,-82.5
   export BBOX=-51.19,0,-82.4999,51.19,0,-64.48764,-51.19,0,-64.48764,51.19,0,-82.4999
   export POINTSIZE=5
   export KLUDGE=1 

   cxt_min.sh pdb

)

