[ "$DBG" == "1" ] && echo $BASH_SOURCE && dbg 

j-(){      [ -r $HOME/j/j.bash ] && . $HOME/j/j.bash && j-env $* ; }
j-env(){  echo -n ; }
j(){  cd ~/j && pwd && git status ; }

jvi(){ vi $BASH_SOURCE && jfu ; }
jfu(){ source $BASH_SOURCE ; }

# -false to end sequence of ors 
jcl(){ local f="" ; for name in $* ; do f="$f -name $name.* -o " ; done ; find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' ; } 
jfi(){ local f="" ; for name in $* ; do f="$f -name $name   -o " ; done ; find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' ; } 

jcv-(){ local fi=$(jcl $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }
jfv-(){ local fi=$(jfi $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }

jsd(){ jcv junoSD_PMT_v2 ; }
jcv(){ cd $JUNOTOP/offline ; jcv- $* ; } 
jfv(){ cd $JUNOTOP/offline ; jfv- $* ; } 

#jcvv(){ jcv NNVT_MCPPMT_PMTSolid Hamamatsu_R12860_PMTSolid ; }
jcvv(){ jcv NNVTMCPPMTManager NNVT_MCPPMT_PMTSolid HamamatsuR12860PMTManager Hamamatsu_R12860_PMTSolid ; }

#jcvv(){ jcv Hamamatsu_R12860_PMTSolid ; }


jgr-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -type f -exec grep -H "${1:-NNVT_MCPPMT_PMTSolid}" {} \; ; } 
jgr(){ cd $JUNOTOP/offline ; jgr- $* ; } 

jgl-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -type f -exec grep -l "${1:-NNVT_MCPPMT_PMTSolid}" {} \; ; } 
jgl(){ cd $JUNOTOP/offline ; jgl- $* ; } 
 
jt(){ cd $JUNOTOP ; } 
je(){ cd $JUNOTOP/junoenv && pwd ; } 
jo(){ cd $JUNOTOP/offline && pwd && svn status ; } 
js(){ cd $JUNOTOP/offline/Simulation/DetSimV2/$1 && pwd ; } 
psi(){ js pmtsim/src ; }
jb(){ cd $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge/cmt && pwd ; } 
jp(){ cd $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge/src/phys && pwd ; } 
td(){ vi $JUNOTOP/offline/Examples/Tutorial/share/tut_detsim.py ; }

gb(){ cd $JUNOTOP/ExternalLibs/Build/geant4.10.04.p02 && pwd ; } 

jf(){
   type jt
   type je
   type jo
   type js
   type ps
   type jb  
   type jp
   type td
   type gb  
}

okt(){
   type $FUNCNAME
   [ -z "$OPTICKS_KEY" ] && echo $msg MISSING MANDATORY OPTICKS_KEY envvar && return 1 


   export OKMgr=INFO
   export OpticksGen=INFO
   export OKPropagator=INFO

   OKTest --xanalytic --dbggsload --dumphit
}

jokc(){
    : list offline .cc WITH_G4OPTICKS
    cd $JUNOTOP/offline
    find . -name '*.cc' -exec grep -l WITH_G4OPTICKS {} \+  
}

####################
# keep the content above the line the same on laptop and P 


jtds(){ 
   local opts="--opticks-mode 1 --no-guide_tube --pmt20inch-polycone-neck --evtmax 2"  
   jtds- $opts 
}
jtds-(){ 
   local label="tds" 
   local arg
   for arg in $* ; do
       case $arg in 
           --pmt20inch-polycone-neck) label="${label}_pcnk" ;;
       esac 
   done
   echo $label 
}


