#!/bin/bash -l 
usage(){ cat << EOU
ntds.sh : utilities related to the j/jx.bash:ntds bash function 
=================================================================

Arguments handled by this script
----------------------------------

grab_evt
   rsync SEvt from remote, base dir /tmp/$USER/opticks/GEOM/$geom
grab_geom
   rsync CSGFoundry folders from remote, geom dir .opticks/GEOM/$geom


ana
   default python analysis with ntds.py
   sensitive to CHECK envvar to control the type of plotting  
cf
   chi2 comparison simulation histories of of (A,B) SEvt 
cfh
   (A,B) compatison of histogram of final photon time  
cfmeta
   metadata comparison of NEVT (A,B) SEvt pairs  

tt
   CPU time comparison analysis of time stamps from (A,B) SEvt  


pvcap pvpub
    pyvista screen capture and publish 
mpcap mppub
    matplotlib screen capture and publish 

help
    usage method 



ana scatter plotting with W photon selection examples
--------------------------------------------------------

Plot step points for of photons with less_than (or more_than) 10 points::

    N=1 MODE=2 CHECK=all_point W=POINT_MAX POINT=10  ~/j/ntds/ntds.sh ana
    N=1 MODE=2 CHECK=all_point W=POINT_MIN POINT=10  ~/j/ntds/ntds.sh ana

Comma delimited W selection presents multiple selections together.
Selections after the first are highlighted with larger points. 
Highlight step points from a single photon::

    N=1 MODE=3 CHECK=all_point W=ALL,PID PID=9706 ~/j/ntds/ntds.sh ana
    N=1 MODE=3 CHECK=all_point W=ALL,PID PID=9801 ~/j/ntds/ntds.sh ana

Highlight photons with processing time greater than 1000 us, 
2D and 3D plotting::

    N=1 MODE=2 CHECK=all_point W=ALL,US_MIN US=1000  ~/j/ntds/ntds.sh ana
    N=1 MODE=3 CHECK=all_point W=ALL,US_MIN US=1000  ~/j/ntds/ntds.sh ana

Scanning US_MAX cuts, its apparent than after 200 us or so 
are not greatly changing the simulation (with input photons 
and a particular geometry NNVT:0:1000 target)::

    N=1 MODE=2 CHECK=all_point W=US_MAX US=100  ~/j/ntds/ntds.sh ana
    N=1 MODE=2 CHECK=all_point W=US_MAX US=200  ~/j/ntds/ntds.sh ana
    N=1 MODE=2 CHECK=all_point W=US_MAX US=300  ~/j/ntds/ntds.sh ana


Check photons without any ProcessHits calls::

    N=1 MODE=2 CHECK=all_point W=HC HC=0  ~/j/ntds/ntds.sh ana



Remote Running
----------------

::

     jxv        # laptop: review ntds bash function : check environment, IPHO, options etc.. 
     jxscp      # laptop: scp copies ~/j/jx.bash to workstation
     jxf        # workstation: update bash functions in session    
     ntds2_cf   # workstation: invokes ntds bash function for N=0 and N=1 : running tut_detsim.py 


Grabbing from remote
-----------------------

::

    jxn # cd ~/j/ntds 

    ./ntds.sh grab_evt     # rsync SEvt folders from remote ntds2_cf (default OPTICKS_MODE:2)
    OPTICKS_MODE=0 ./ntds.sh grab_evt   # grab metadata from ntds0_cf

    ./ntds.sh grab_geom    # rsync CSGFoundry geometry folders from remote


Plotting photon histories
----------------------------

ntds.py
    general analysis comparison of SEvt and plotting  

N defaults to -1 meaning both N=0 and N=1 are plotted into separate windows.
To pick one or other (as needed when doing screen captures) specify the N::

    jxn # cd ~/j/ntds 

    ./ntds.sh ana          # plotting SEvt for one event pair
    CHECK=all_point ./ntds.sh ana    
    CHECK=few_point ./ntds.sh ana    
    MODE=3 CHECK=few_point ./ntds.sh ana    

    N=0 MODE=3 ./ntds.sh ana
    N=1 GLOBAL=1 MODE=3 ./ntds.sh ana

    GLOBAL=1 MODE=3 ./ntds.sh ana   # 3D plotting 
    GLOBAL=1 CHECK=sd_point ./ntds.sh ana
    GLOBAL=1 CHECK=sa_point ./ntds.sh ana


    MODE=3 EDL=1 N=0 EYE=500,0,2300  CHECK=not_first ./ntds.sh ana

    MODE=3 EDL=1 N=0 EYE=500,0,2300 CHECK=hist HIST="TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD"  ./ntds.sh ana
    MODE=3 EDL=1 N=0 EYE=500,0,2300 CHECK=hist HIST="TO BT SA"  ./ntds.sh ana
    MODE=3 EDL=1 N=0 EYE=500,0,2300 CHECK=select  ./ntds.sh ana




History and metadata comparisons
-----------------------------------

ntds_cf.py
    chi2 comparison

ntds_cfmeta.py
    comparisons across NEVT pairs of evt 

::

    jxn # cd ~/j/ntds 
    ./ntds.sh cf           # chi2 compare SEvt for one event pair
    ./ntds.sh cfmeta       # chi2 compare SEvt for NEVT (eg 10) event pairs (default OPTICKS_MODE:2)
    OPTICKS_MODE=0 ./ntds.sh cfmeta     # compate metadata from ntds0_cf


EOU
}

DIR=$(dirname $BASH_SOURCE)

defarg="ana"
#defarg="cf"
arg=${1:-$defarg}

check=all_point
#check=few_point
#check=sd_point

evt=000

export EVT=${EVT:-$evt}
n=-1  # 0,1,-1
export VERSION="${N:-$n}"


export OPTICKS_MODE=${OPTICKS_MODE:-2}
export SCRIPT=ntds$OPTICKS_MODE
export GEOMDIR=/tmp/$USER/opticks/GEOM
export CHECK=${CHECK:-$check}

#gpfx=V  # V:Debug
gpfx=R   # R:Relase
export GPFX=${GPFX:-$gpfx}  # follow gpfx from ntds2_cf

export AGEOM=${GPFX}0J008
export BGEOM=${GPFX}1J008
export ABASE=$GEOMDIR/$AGEOM/$SCRIPT
export BBASE=$GEOMDIR/$BGEOM/$SCRIPT
export NEVT=${NEVT:-0}

if [ "$arg" == "cfmeta" -o $NEVT -gt 1 ]; then 
    EVT="%0.3d"
fi 

export AFOLD=$ABASE/ALL0/$EVT
export BFOLD=$BBASE/ALL1/$EVT

## ENVOUT is used to communicate from some python scripts back into this bash script 
## this only makes sense when a single invokation corresponds to a single plot
export ENVOUT=/tmp/$USER/opticks/$SCRIPT/envout.sh
mkdir -p $(dirname $ENVOUT)


if [ "$VERSION" == "0" -o "$VERSION" == "1" ]; then
    case $VERSION in 
      0) UBASE=$AFOLD ;;
      1) UBASE=$BFOLD ;;
    esac   
    export UBASE
fi 


vars="BASH_SOURCE CHECK arg defarg DIR OPTICKS_MODE SCRIPT BASE EVT AGEOM ABASE AFOLD BGEOM BBASE BFOLD N VERSION UBASE"
for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done  

case $VERSION in 
   -1) echo $BASH_SOURCE VERSION:$VERSION load both AFOLD and BFOLD  ;;
    0) echo $BASH_SOURCE VERSION:$VERSION load only AFOLD $AFOLD ;; 
    1) echo $BASH_SOURCE VERSION:$VERSION load only BFOLD $BFOLD ;; 
esac

geoms="$AGEOM $BGEOM"
if [ "$arg" == "grab_evt" ]; then 
   for geom in $geoms ; do 
       base=/tmp/$USER/opticks/GEOM/$geom
       echo rsync geom $geom base $base
       source $OPTICKS_HOME/bin/rsync.sh $base
       [ $? -ne 0 ] && echo $BASH_SOURCE grab_evt error grabbing base $base && exit 2 
   done
elif [ "$arg" == "grab_geom" ]; then 
   for geom in $geoms ; do 
       base=.opticks/GEOM/$geom
       echo rsync geom $geom base $base
       source $OPTICKS_HOME/bin/rsync.sh $base
       [ $? -ne 0 ] && echo $BASH_SOURCE grab_geom error grabbing base $base && exit 2 
   done  
elif [ "$arg" == "ana" ]; then 
    pyscript=$DIR/ntds.py 
elif [ "$arg" == "cf" ]; then
    pyscript=$DIR/ntds_cf.py 
elif [ "$arg" == "cfh" ]; then
    pyscript=$DIR/ntds_cfh.py 
elif [ "$arg" == "cfmeta" ]; then
    pyscript=$DIR/ntds_cfmeta.py 
elif [ "$arg" == "tt" ]; then
    pyscript=$OPTICKS_HOME/sysrap/sevt_tt.py
elif [ "$arg" == "help" ]; then
    usage
fi

export QLIM=0:10
  
echo $BASH_SOURCE : anascript : $anascript
 
if [ -n "$pyscript"  -a -f "$pyscript" ]; then 
    ${IPYTHON:-ipython} --pdb -i $pyscript
    [ $? -ne 0 ] && echo $BASH_SOURCE pyscript $pyscript error && exit 1
else
    echo $BASH_SOURCE no pyscript for arg $arg 
fi

if [ "$arg" == "pvcap" -o "$arg" == "pvpub" -o "$arg" == "mpcap" -o "$arg" == "mppub" ]; then

    if [ -f "$ENVOUT" ]; then 
        echo $BASH_SOURCE : detected that another instance of this script python wrote ENVOUT $ENVOUT : sourcing this
        cat $ENVOUT
        source $ENVOUT
        env | grep ENVOUT 
    fi 

    if [ -n "$ENVOUT_CAP_STEM" -a -n "$ENVOUT_CAP_BASE" ]; then
        echo $BASH_SOURCE picking up ENVOUT_CAP_STEM $ENVOUT_CAP_STEM ENVOUT_CAP_BASE $ENVOUT_CAP_BASE 
        export CAP_STEM=$ENVOUT_CAP_STEM
        export CAP_BASE=$ENVOUT_CAP_BASE/figs
        export CAP_REL=${ENVOUT_CAP_REL:-$SCRIPT}
        case $arg in  
           pvcap) source pvcap.sh cap  ;;  
           mpcap) source mpcap.sh cap  ;;  
           pvpub) source pvcap.sh env  ;;  
           mppub) source mpcap.sh env  ;;  
        esac
        if [ "$arg" == "pvpub" -o "$arg" == "mppub" ]; then
            source epub.sh
        fi
    else
        echo $BASH_SOURCE : ERROR pvcap/pvpub/mpcap/mppub ENVOUT non-existing or incomplete
        echo $BASH_SOURCE : ENVOUT          : $ENVOUT
        echo $BASH_SOURCE : ENVOUT_CAP_STEM : $ENVOUT_CAP_STEM
        echo $BASH_SOURCE : ENVOUT_CAP_BASE : $ENVOUT_CAP_BASE
    fi 
fi

exit 0 

