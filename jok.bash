#!/bin/bash 
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
   #export GEOM=J23_1_0_rc3_ok0         # replace . and - with _ to make valid bash identifier
   #export GEOM=J_2024may20
   #export GEOM=J_2024jun14
   #export GEOM=J_2024aug27
   #export GEOM=J_2024nov27
   export GEOM=J_2025jan08

   ## Opticks environment setup picks the opticks install to use setting OPTICKS_PREFIX
   ## hence that is where the Debug/Release selection happens

   local ctx
   case $(uname) in
      Darwin) ctx=Debug_Philox ;;
       Linux) ctx=$(TEST=ContextString sbuild_test) ;;  ## eg Debug_Philox see sbuild.h
   esac

   local test=GUN0
   #local test=GUN1
   #local test=GUN2
   #local test=GUN3
   export TEST=${TEST:-$test}

   export OPTICKS_EVENT_NAME=${ctx}_$TEST   # used by SEventConfig::EventReldir "OPTICKS_EVENT_RELDIR"

   local opticks_event_reldir=ALL${VERSION:-0}_${OPTICKS_EVENT_NAME:-none}   
   export OPTICKS_EVENT_RELDIR='ALL${VERSION:-0}_${OPTICKS_EVENT_NAME:-none}'  ## this is the default in SEventConfig
   ## above two lines match SEventConfig::_DefaultEventReldir 
   ## resolution of first line happens here for bash consumption, resolution of 2nd done in SEventConfig

   local logdir=${TMP:-/data/$USER/opticks}/GEOM/$GEOM/jok-tds/$opticks_event_reldir
   mkdir -p $logdir
   cd $logdir     # log files are dropped in invoking directory 
   echo === $FUNCNAME  

   pwd
   #ls -alst
}

jok-info()
{
   jok-init 
   local vars="0 BASH_SOURCE FUNCNAME GEOM PWD TEST"  
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


jok-tds-inputphoton()
{
    : this is invoked from jok-tds when GUN is zero
    type $FUNCNAME
    export OPTICKS_RUNNING_MODE=SRM_INPUT_PHOTON
    export OPTICKS_INPUT_PHOTON=RainXZ_Z230_10k_f8.npy 
    export OPTICKS_INPUT_PHOTON_FRAME=NNVT:0:1000
}

jok-tds-inputphoton-unset()
{
    : this is invoked from jok-tds when GUN is non-zero
    type $FUNCNAME
    unset OPTICKS_RUNNING_MODE
    unset OPTICKS_INPUT_PHOTON
    unset OPTICKS_INPUT_PHOTON_FRAME
}





jok-tds(){
   echo === $FUNCNAME  
   jok-init  # set GEOM, creates logdir and cd to it


   export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10            # default 1.e-3 
   export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10  # default 0.05 
   export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10       # default 0.05



   local WPC_ASIS=0              # no change : Opticks translation will assert with CSG tree height < MAX_TREE_DEPTH 
   local WPC_ZERO_HOLES=1        # adhoc just dont subtract the 30+30+1+1=62 holes : translation expected to succeed 
   local WPC_MULTIUNION_HOLES=2  # instead of subtracting the 62 holes one by one, collect into multiunion and subtract together
   local WPC_HIERARCHY=3         # major simplification of WaterPoolConstruction : natural hierarchy removes need for the 62 subtractions 

   #export WaterPoolConstruction__CONFIG=$WPC_MULTIUNION_HOLES
   export WaterPoolConstruction__CONFIG=$WPC_HIERARCHY



   unset ConfAcrylic__data_pillar_remove_bottom_angled_cross_piece
   unset HBeamConstruction__try_init_model_pillar_shortleg_LSCALE

   #if [ "$WaterPoolConstruction__CONFIG" == "$HIERARCHY" ]; then
   #    export ConfAcrylic__data_pillar_remove_bottom_angled_cross_piece=1 
   #    export HBeamConstruction__try_init_model_pillar_shortleg_LSCALE=0.95
   #fi 


   unset FastenerConstruction__CONFIG
   ## REMOVED AS FC_LISTNODE_DISCONTIGUOUS IS NOW DEFAULT
   ## local FC_ASIS=0                       ## geometry present but does not render
   ## local FC_MULTIUNION_CONTIGUOUS=1
   ## local FC_MULTIUNION_DISCONTIGUOUS=2   ## G4MultiUnion SEGV with input photons
   ## local FC_LISTNODE_DISCONTIGUOUS=3     ## avoid the G4MultiUnion but still translate to listnode
   ## local FC_LISTNODE_CONTIGUOUS=4
   ## export FastenerConstruction__CONFIG=$FC_ASIS
   ## export FastenerConstruction__CONFIG=$FC_MULTIUNION_DISCONTIGUOUS  
   ## export FastenerConstruction__CONFIG=$FC_LISTNODE_DISCONTIGUOUS      


   ## REMOVED AS FORMER APPROACH IS A BUG
   ## unset LSExpDetectorConstruction__setupCD_Sticks_Fastener_CONFIG
   ## local AAF_ASIS=0
   ## local AAF_HIERARCHY=1
   ## export LSExpDetectorConstruction__setupCD_Sticks_Fastener_CONFIG=$AAF_HIERARCHY


   unset LSExpDetectorConstruction__setupCD_Sticks_Fastener_Hierarchy_DELTA_MM 
   ## local FC_DELTA_MM_DEFAULT=0.10
   ## local FC_DELTA_MM_ENLARGED_FOR_VISIBILITY=2
   ## export LSExpDetectorConstruction__setupCD_Sticks_Fastener_Hierarchy_DELTA_MM=$FC_DELTA_MM_ENLARGED_FOR_VISIBILITY

   unset AdditionAcrylicConstruction__rdelta_mm
   #export AdditionAcrylicConstruction__rdelta_mm=1   ## set it big to see something 

   #export U4Solid__IsFlaggedType=G4MultiUnion



   export stree__force_triangulate_solid='filepath:$HOME/.opticks/GEOM/${GEOM}_meshname_stree__force_triangulate_solid.txt'

   unset U4Mesh__NumberOfRotationSteps_DUMP
   export U4Mesh__NumberOfRotationSteps_DUMP=1

   export U4Mesh__NumberOfRotationSteps_entityType_G4Torus=480

   export U4Tree__MATERIAL_DEBUG=1


   ## TODO : AVOID DUPLICATION OF GEOMETRY CHANGING ENVIRONMENT SETUP BETWEEN HERE AND OTHER SCRIPTS LIKE gxt G4CXTest_GEOM.sh

   


   #local oim=1     # 1:opticks optical simulation only
   local oim=3    # 3:both geant4 and opticks optical simulation 
   local OIM=${OIM:-$oim}
   export OPTICKS_INTEGRATION_MODE=$OIM   
   export OPTICKS_SCRIPT=$FUNCNAME        # avoid default sproc::_ExecutableName of python3.9 



   #local mode=DebugLite
   #local mode=Nothing     # GPU leak debug 
   #local mode=Minimal
   local mode=Hit

   export OPTICKS_EVENT_MODE=$mode  ## see SEventConfig::Initialize SEventConfig::EventMode


   local opticks_max_slot
   local opticks_max_photon 
   case $OPTICKS_EVENT_MODE in 
       DebugLite) opticks_max_slot=M1 ; opticks_max_photon=M1  ;;  ## need to be reasonable when debug arrays enabled
             Hit) opticks_max_slot=0  ; opticks_max_photon=G1  ;;
               *) opticks_max_slot=0  ; opticks_max_photon=G1  ;;  
   esac
   ## max_slot:0 uses VRAM heuristic calc to set actual max_slot for each launch

   export OPTICKS_MAX_SLOT=$opticks_max_slot
   export OPTICKS_MAX_PHOTON=$opticks_max_photon    
   ## with multi-launch and Philox running max_photon default is G1 : one billion

   export OPTICKS_MAX_BOUNCE=31
   export OPTICKS_NUM_EVENT=1

   if [ "$OPTICKS_EVENT_MODE" == "DebugLite" ]; then
       export G4CXOpticks__SaveGeometry_DIR=$HOME/.opticks/GEOM/$GEOM
       export SScene__initFromTree_addFrames=$HOME/.opticks/GEOM/${GEOM}_framespec.txt
   fi 

   local opts="" 
   opts="$opts --evtmax $OPTICKS_NUM_EVENT"
   opts="$opts --opticks-mode $OPTICKS_INTEGRATION_MODE "   
   opts="$opts --no-toptask-show"

   # opts="$opts --additionacrylic-simplify-csg"
   ## have removed this, it is now the default 


   NOGT=0      # dont --no-guide_tube
   NOXJ=0      # dont --debug-disable-xj
   NOSJ=0      # dont --debug-disable-sj
   NOFA=0      # dont --debug-disable-fa

   ## NB not skipping problem geometry requires careful config of force triangulation 
   ## to avoid missing and broken geometry 


   NOGT=${NOGT:-0}
   case $NOGT in 
      0) opts="$opts" ;; 
      1) opts="$opts --no-guide_tube" ;; 
   esac

   NOXJ=${NOXJ:-0}
   case $NOXJ in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-xj" ;; 
   esac

   NOSJ=${NOSJ:-0}
   case $NOSJ in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-sj" ;; 
   esac

   NOFA=${NOFA:-0}
   case $NOFA in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-fa" ;; 
   esac




   opts="$opts $(jok-anamgr) "
   case $OPTICKS_INTEGRATION_MODE in 
       2|3) opts="$opts --opticks-anamgr " ;;   
       ## --opticks-anamgr switches on U4RecorderAnaMgr recording Geant4 propagation into Opticks SEvt "B000,.." 
   esac

   local gun0="opticks"   ## input photons
   local gun1="gun"
   local gun2="gun --particles gamma --momentums 2.223 --momentums-interp KineticEnergy --positions 0 0 0"
   local gun3="gun --particles gamma --momentums 22.23 --momentums-interp KineticEnergy --positions 0 0 0"
   local gun4="gun --particles mu- --momentums 214000 --positions 0 0 0"   ## 214 GeV
   local gun5="gun --particles mu- --momentums  50000 --positions 0 0 0"   ##  50 GeV
   ## --momentums in MeV 

   jok-tds-inputphoton-unset 

   local trgs=""     ## "trgs" are arguments after the opts : eg "gun" or "opticks" 
   case $TEST in  
     GUN0) trgs="$trgs $gun0" ;  jok-tds-inputphoton ;;
     GUN1) trgs="$trgs $gun1"  ;;
     GUN2) trgs="$trgs $gun2"  ;;
     GUN3) trgs="$trgs $gun3"  ;;
     GUN4) trgs="$trgs $gun4"  ;;
     GUN5) trgs="$trgs $gun5"  ;;
   esac


   unlogging()
   {
       unset U4Recorder__SEvt_NPFold_VERBOSE
       unset U4Recorder
       unset SEvt__LIFECYCLE
       unset CSGFoundry
       unset QEvent
       unset junoSD_PMT_v2_Opticks
       unset junoSD_PMT_v2   
       unset SEvt__GATHER
       unset sn__level
       unset QEvent__LIFECYCLE
   }


   logging()
   {
       : jok.bash 
       type $FUNCNAME 
       ## for SEvt::setFoldVerbose NPFold::set_verbose frm A and B SEvt
       ##export QEvent__SEvt_NPFold_VERBOSE=1  
       export U4Recorder__SEvt_NPFold_VERBOSE=1  
       export U4Recorder=INFO       

       export SEvt__LIFECYCLE=1  ## sparse SEvt debug output, works well alone  
       export CSGFoundry=INFO
       export QEvent=INFO
       export junoSD_PMT_v2_Opticks=INFO
       export junoSD_PMT_v2=INFO
       #export SEvt__GATHER=1   ## gather_component debug 
       #export sn__level=2  

       export QEvent__LIFECYCLE=1 
   }

   unlogging
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

   local vars="BASH_SOURCE TEST mode NOXJ NOSJ NOFA GUN opts trgs jokdir PWD runline"
   for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
   env | grep OPTICKS
   env | grep __

   eval $runline
   
   if [ -z "$NOREPORT" ]; then
      echo === $BASH_SOURCE no NOREPORT detected proceed with jok-report
      jok-report
   else
      echo === $BASH_SOURCE NOREPORT detected skipping jok-report
   fi 
}

jok-report(){
   : ~/j/jok.bash summarize+present SEvt/NPFold timestamp and memory profile metadata 

   echo === $FUNCNAME PWD $PWD

   local bin=$OPTICKS_PREFIX/lib/sreport 
   echo $bin
   $bin

}

jok-tds-gdb(){ GDB=1 NOREPORT=1 jok-tds ; }


jok-anamgr-notes(){ cat << EON
--opticks-anamgr
--no-anamgr-edm-v2
$(: --anamgr-edm-v2)

EON
}


jok-anamgr(){ cat << EOU
--no-anamgr-normal
--no-anamgr-genevt
--no-anamgr-edm-v2
--no-anamgr-grdm
--no-anamgr-deposit
--no-anamgr-deposit-tt
--no-anamgr-interesting-process
--no-anamgr-optical-parameter
--no-anamgr-timer
EOU
   : --opticks-anamgr attempts to switch on U4RecorderAnaMgr - BUT THAT NEEDS opticksMode 2 or 3 
}


jok-grab(){    ~/j/jtds/jtds.sh grab ; }
jok-scpmeta(){ ~/j/jtds/jtds.sh scpmeta ; }
jok-ana(){     ~/j/jtds/jtds.sh $* ; }


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

        : changed BP delim to comma such that methods with spaces can be passed
        : such as BP="junoHit_PMT::operator new,junoHit_PMT::operator delete"

        IFS=',' read -ra bps <<< "$BP"
        for bp in "${bps[@]}"
        do
            B="$B -ex \"break $bp\" ";
        done
        T="-ex \"info break\" -ex r";
    fi;
    local runline="gdb $H $B $T --args $* ";
    echo $runline;
    date;
    eval $runline;
    date
}

