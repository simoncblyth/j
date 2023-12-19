#!/bin/bash -l
# ~/j/jok.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/jok.bash
jok-source(){ echo $BASH_SOURCE ; }
jok-vi(){ vi $BASH_SOURCE ; }
jok-(){ source $BASH_SOURCE ; }
jok-notes(){ cat << EON
~/j/jok.bash
============

Aim is for minimal bash functions to test junosw+opticks
as the jx.bash funcs have grown into monsters. 

Usage::

   source ~/j/jok.bash 
   jok-tds 

TODO: test the modes
--------------------------

OPTICKS_INTEGRATION_MODE=0
    Do nothing mode

OPTICKS_INTEGRATION_MODE=1 
    Opticks only : check writing hits

OPTICKS_INTEGRATION_MODE=3
    A:Opticks vs B:Geant4 : comparison in different running modes

OPTICKS_INTEGRATION_MODE=2
    Instrumented B:Geant4 only 


EON
}

jok-script(){ echo $JUNOTOP/junosw/Examples/Tutorial/share/tut_detsim.py ; }


jok-init()
{
   export GEOM=J23_1_0_rc3_ok0         # replace . and - with _ to make valid bash identifier
   local logdir=${TMP:-/data/$USER/opticks}/GEOM/$GEOM/jok-tds/ALL0 
   mkdir -p $logdir
   cd $logdir     # log files are dropped in invoking directory 
   pwd
   ls -alst
}

jok-info()
{
   jok-init 
   local vars="0 BASH_SOURCE FUNCNAME GEOM PWD"  
   local var
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 
}

jok-srm-unused-so-far()
{
    : input photons within embedded running has worked previously 
    : torch running within embedded needs development

    local srm
    #srm=SRM_DEFAULT
    srm=SRM_TORCH
    #srm=SRM_INPUT_PHOTON
    #srm=SRM_INPUT_GENSTEP    ## NOT IMPLEMENTED FOR GEANT4
    #srm=SRM_GUN
    export OPTICKS_RUNNING_MODE=$srm

    echo $BASH_SOURCE OPTICKS_RUNNING_MODE $OPTICKS_RUNNING_MODE

    if [ "$OPTICKS_RUNNING_MODE" == "SRM_TORCH" ]; then 
        export SEvent_MakeGenstep_num_ph=$NUM
        #src="rectangle"
        #src="disc"
        src="sphere"

        if [ "$src" == "rectangle" ]; then
            export storch_FillGenstep_pos=0,0,0
            export storch_FillGenstep_type=rectangle
            export storch_FillGenstep_zenith=-20,20
            export storch_FillGenstep_azimuth=-20,20
        elif [ "$src" == "disc" ]; then
            export storch_FillGenstep_type=disc
            export storch_FillGenstep_radius=50      
            export storch_FillGenstep_zenith=0,1       # radial range scale
            export storch_FillGenstep_azimuth=0,1      # phi segment twopi fraction 
            export storch_FillGenstep_mom=1,0,0
            export storch_FillGenstep_pos=-80,0,0
        elif [ "$src" == "sphere" ]; then
            export storch_FillGenstep_type=sphere
            export storch_FillGenstep_radius=100    # +ve for outwards    
            export storch_FillGenstep_pos=0,0,0
            export storch_FillGenstep_distance=1.00 # frac_twopi control of polarization phase(tangent direction)
        fi 

    elif [ "$OPTICKS_RUNNING_MODE" == "SRM_INPUT_PHOTON" ]; then 
        echo -n 
        #export OPTICKS_INPUT_PHOTON=RainXZ_Z230_1M_f8.npy 
        export OPTICKS_INPUT_PHOTON=RainXZ_Z230_10k_f8.npy 
        export OPTICKS_INPUT_PHOTON_FRAME=NNVT:0:1000

    elif [ "$OPTICKS_RUNNING_MODE" == "SRM_INPUT_GENSTEP" ]; then 
        echo -n 

    elif [ "$OPTICKS_RUNNING_MODE" == "SRM_GUN" ]; then 
        echo -n 
    fi 
}




jok-tds(){
   jok-init

   local oim=1     # 1:opticks optical simulation only
   #local oim=3    # 3:both geant4 and opticks optical simulation 
   local OIM=${OIM:-$oim}
   export OPTICKS_INTEGRATION_MODE=$OIM   
   export OPTICKS_SCRIPT=$FUNCNAME        # avoid default sproc::_ExecutableName of python3.9 

   export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10            # default 1.e-3 
   export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10  # default 0.05 
   export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10       # default 0.05

   #local mode=DebugLite
   #local mode=Nothing     # GPU leak debug 
   #local mode=Minimal
   local mode=Hit

   export OPTICKS_EVENT_MODE=$mode  ## see SEventConfig::Initialize SEventConfig::EventMode
   export OPTICKS_MAX_BOUNCE=31
   export OPTICKS_MAX_PHOTON=M1
   export OPTICKS_NUM_EVENT=1000

   if [ "$OPTICKS_EVENT_MODE" == "DebugLite" ]; then
       export G4CXOpticks__SaveGeometry_DIR=$HOME/.opticks/GEOM/$GEOM
   fi 

   local opts="" 
   opts="$opts --evtmax $OPTICKS_NUM_EVENT"
   opts="$opts --opticks-mode $OPTICKS_INTEGRATION_MODE "   
   opts="$opts --no-guide_tube"
   opts="$opts --additionacrylic-simplify-csg"
   opts="$opts --no-toptask-show"

   NOXJ=${NOXJ:-1}
   case $NOXJ in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-xj" ;; 
   esac

   NOSJ=${NOSJ:-1}
   case $NOSJ in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-sj" ;; 
   esac

   NOFA=${NOFA:-1}
   case $NOFA in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-fa" ;; 
   esac

   opts="$opts $(jok-anamgr) "

   local gun1="gun"
   local gun2="gun --particles gamma --momentums 2.223 --momentums-interp KineticEnergy --positions 0 0 0"
   local gun3="gun --particles gamma --momentums 22.23 --momentums-interp KineticEnergy --positions 0 0 0"
   local trgs=""     
   : "trgs" are the arguments after the opts : eg "gun" or "opticks" 

   local gun=1 
   local GUN=${GUN:-$gun}
   case $GUN in  
     0) trgs="$trgs opticks" ;;
     1) trgs="$trgs $gun1" ;;
     2) trgs="$trgs $gun2"  ;;
     3) trgs="$trgs $gun3"  ;;
   esac


   logging()
   {
       : jok.bash 
       type $FUNCNAME 
       ## for SEvt::setFoldVerbose NPFold::set_verbose frm A and B SEvt
       ##export QEvent__SEvt_NPFold_VERBOSE=1  
       ##export U4Recorder__SEvt_NPFold_VERBOSE=1  
       ##export SEvt__LIFECYCLE=1  ## sparse SEvt debug output, works well alone  

       #export QEvent=INFO
       #export junoSD_PMT_v2_Opticks=INFO
       #export junoSD_PMT_v2=INFO
       #export SEvt__GATHER=1   ## gather_component debug 

       export QEvent__LIFECYCLE=1 
   }
   if [ -n "$LOG" ]; then 
       echo $BASH_SOURCE - $FUNCNAME - logging enabled
       logging
   else
       echo $BASH_SOURCE - $FUNCNAME - logging NOT enabled - use LOG=1 to enable 
   fi   

   local root="sample_detsim_user.root"
   if [ -f "$root" ]; then
       echo === $BASH_SOURCE : deleting $root from PWD $PWD HOME $HOME
       rm -f $root
   else
       echo === $BASH_SOURCE : no $root in PWD $PWD
   fi 


   local runline="python $(jok-script) $opts $trgs"

   if [ -n "$GDB" -o -n "$BP" ]; then
       runline="jok-gdb $runline"
   elif [ -n "$CUDA_MEMCHECK" ]; then 
       runline="cuda-memcheck --leak-check full $runline"
   fi 

   local vars="BASH_SOURCE mode NOXJ NOSJ NOFA GUN opts trgs jokdir PWD runline"
   for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
   env | grep OPTICKS
   env | grep __

   eval $runline
   
   jok-report
}

jok-report(){
   : ~/j/jok.bash summarize+present SEvt/NPFold timestamp and memory profile metadata 

   jok-init

   local bin=$OPTICKS_PREFIX/lib/sreport 
   echo $bin
   $bin

}

jok-tds-gdb(){ GDB=1 jok-tds ; }


jok-anamgr(){ cat << EOU
$(: --opticks-anamgr)
--no-anamgr-normal
--no-anamgr-genevt
--no-anamgr-edm-v2
$(: --anamgr-edm-v2)
--no-anamgr-grdm
--no-anamgr-deposit
--no-anamgr-deposit-tt
--no-anamgr-interesting-process
--no-anamgr-optical-parameter
--no-anamgr-timer
EOU
   : --opticks-anamgr attempts to switch on U4RecorderAnaMgr - BUT THAT NEEDS opticksMode 2 or 3 
}


jok-grab(){ ~/j/jtds/jtds.sh grab ; }
jok-ana(){  ~/j/jtds/jtds.sh $* ; }


jok-gdb() 
{ 
    : ~/j/jok.bash :  invokes gdb - sets up breakpoints based on BP envvar containing space delimited symbols;
    if [ -z "$BP" ]; then
        H="";
        B="";
        T="-ex r";
    else
        H="-ex \"set breakpoint pending on\"";
        B="";
        for bp in $BP;
        do
            B="$B -ex \"break $bp\" ";
        done;
        T="-ex \"info break\" -ex r";
    fi;
    local runline="gdb $H $B $T --args $* ";
    echo $runline;
    date;
    eval $runline;
    date
}

