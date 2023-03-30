#!/bin/bash -l
# ~/j/jx.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/jx.bash

jx-usage(){ cat << EOU
jx.bash : Started Sept 2022 : Updating to git junosw
=========================================================

Update of the former j/j.bash for the git+CMake based junosw environment 


Database/ParaDB/src/ParaPayload.cc

-    const ParaPayload& null_payload() {
+    const ParaPayload& ParaPayload::null_payload() {

::

   perl -pi -e 's/ null_payload/ ParaPayload::null_payload/' Database/ParaDB/src/ParaPayload.cc


Is dependency build order wrong ? junosw/Simulation/CMakeLists.txt::

    add_subdirectory (GenTools)
    add_subdirectory (GenDecay)


    add_subdirectory (DetSimV2)
    add_subdirectory (EvtMixing)
    add_subdirectory (ElecSimV3)

    add_subdirectory (SimSvc)

    add_subdirectory (SNMonitorSim)


Would have expected SimSvc needed by DetSimV2 ?

       




EOU
}

jxv(){ vi $BASH_SOURCE ~/j/j.bash && jxf ; }
jx-vi(){ vi $BASH_SOURCE ; }
jxf(){ source $BASH_SOURCE ; }
jxn(){ cd ~/j/ntds ; }
jxo(){  open -a "Firefox Developer Edition" https://code.ihep.ac.cn/JUNO/offline ;  }

jxp(){  cd ~/j/PMTSimParamSvcTest ; pwd ; }

jxscp(){ scp ~/j/jx.bash P:j/jx.bash ; }  ## as git ssh is often blocked 

jxcustom(){

   cd $JUNOTOP/junosw/Simulation/DetSimV2/PhysiSim 
   g4-
   local msg="$BASH_SOURCE :"
   local hh_source=$(g4-dir)/source/processes/optical/include/G4OpBoundaryProcess.hh
   local hh_target="include/CustomG4OpBoundaryProcess.hh"

   if [ ! -f "$hh_target" ]; then
       echo $msg copying to hh_target $hh_target 
       cp $hh_source $hh_target
   else
       echo $msg hh_target $hh_target exists already 
   fi 

   local cc_source=$(g4-dir)/source/processes/optical/src/G4OpBoundaryProcess.cc
   local cc_target="src/CustomG4OpBoundaryProcess.cc"

   if [ ! -f "$cc_target" ]; then
       echo $msg copying to cc_target $cc_target 
       cp $cc_source $cc_target
   else
       echo $msg cc_target $cc_target exists already 
   fi 


}



jproj(){ cat << EOL

Simulation/DetSimV2/PhysiSim
Simulation/GenTools
Simulation/DetSimV2/PMTSim
Simulation/DetSimV2/AnalysisCode
Simulation/DetSimV2/DetSimOptions

EOL
}

jx-util(){ jx-sub Utilities ; }

jx-sut(){ jx-sub Simulation/DetSimV2/SimUtil ; }
jx-phy(){ jx-sub Simulation/DetSimV2/PhysiSim ; }
jx-pmt(){ jx-sub Simulation/DetSimV2/PMTSim ; }
jx-dso(){ jx-sub Simulation/DetSimV2/DetSimOptions ; }

jx-gen(){ jx-sub Simulation/GenTools ; }
jx-ana(){ jx-sub Simulation/DetSimV2/AnalysisCode ; }


jx-touch(){
   jx-phy
   jx-gen
   jx-pmt
   jx-ana
   jx-dso
}
jx-up(){ 
   jx-phy
   jx-pmt
   jx-dso

}



jx-sub()
{
   local msg="=== $BASH_SOURCE $FUNCNAME :"
   local rel=${1:-Simulation/DetSimV2/PhysiSim} 

   [ -z "$JX_RUNTIME_ENV" ] && echo $msg MUST RUN jre BEFORE jx-sub $rel && return 1 

   local sdir=$JUNOTOP/junosw/$rel
   local bdir=$JUNOTOP/junosw/build/$rel

   if [ ! -d "$sdir" ]; then 
      echo $msg sdir $sdir for rel $rel does not exist
      return 1
   fi 
   if [ ! -d "$bdir" ]; then 
      echo $msg bdir $bdir for rel $rel does not exist
      return 1
   fi 

   cd $bdir ; pwd
   local njobs=-j$(nproc)

   cmake --build . $njobs 
   [ $? -ne 0 ] && echo $msg build fail && cd $sdir && pwd && return 1

   cmake --install . 
   [ $? -ne 0 ] && echo $msg install fail && cd $sdir && pwd && return 1

   cd $sdir ; pwd
}


jt(){ cd $JUNOTOP ; pwd ; } 
je(){ cd $JUNOTOP/junoenv && pwd ; } 
jo(){ cd $JUNOTOP/junosw && pwd && git status ; } 


# -false to end sequence of ors 
#
# HMM jcl jcld fails when the * shell expansion find the files in the invoking directory 
# as that messes up the find command
# double quoting the f gets some way but somehow messes up other things
# HENCE: use jcl jfi from top level where shell expansion will not find the files in the invoking directory 

jcld(){ local f="" ; for name in $* ; do f="$f -name $name.* -o " ; done ; echo find . \( $f -false \) -a ! -path './InstallArea/*' -a ! -path './build/*' ; } 
jcl(){  local f="" ; for name in $* ; do f="$f -name $name.* -o " ; done ;      find . \( $f -false \) -a ! -path './InstallArea/*' -a ! -path './build/*' ; } 
jfi(){  local f="" ; for name in $* ; do f="$f -name $name   -o " ; done ;      find . \( $f -false \) -a ! -path './InstallArea/*' -a ! -path './build/*' ; } 


jcv-(){ local fi=$(jcl $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }
jfv-(){ local fi=$(jfi $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }

jcv(){ cd $JUNOTOP/junosw ; jcv- $* ; : edit files identified by stem ;  } 
jfv(){ cd $JUNOTOP/junosw ; jfv- $* ; : list files identified by wildcard ; } 

#jgr-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -a ! -path '*.sh' -a ! -path '*.csh'  -type f -exec grep -H "${1:-G4OPTICKS}" {} \; ; } 
#jgl-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -a ! -path '*.sh' -a ! -path '*.csh'  -type f -exec grep -l "${1:-G4OPTICKS}" {} \; ; }

jgr-(){ find . -not -path "./build/*" -a -not -path "./InstallArea/*" -a -not -path "./.git/*" -type f -exec grep -H "${1:-G4CXOPTICKS}" {} \; ; } 
jgl-(){ find . -not -path "./build/*" -a -not -path "./InstallArea/*" -a -not -path "./.git/*" -type f -exec grep -l "${1:-G4CXOPTICKS}" {} \; ; } 

jgr(){ cd $JUNOTOP/junosw ; jgr- $* ; : search files with the query string and show matches - skips are made to avoid cmt garbage ;  } 
jgl(){ cd $JUNOTOP/junosw ; jgl- $* ; : search files with the query string and list matched paths - skips are made to avoid cmt garbage ; } 
 





jx-runtime-env-()
{
   : note that CMAKE_PREFIX_PATH and MANPATH keep appending on repeated running but the others dont
   local msg="=== $FUNCNAME: "
   echo $msg
   source $JUNOTOP/bashrc.sh   # sources the bashrc of the JUNOTOP/ExternalLibs
   source $JUNOTOP/sniper/InstallArea/bashrc
   source $JUNOTOP/sniper/InstallArea/share/sniper/setup.sh   
   source $JUNOTOP/mt.sniper/InstallArea/bashrc
   source $JUNOTOP/junosw/InstallArea/setup.sh
   echo $msg
}

jx-runtime-env()
{
   : setup the runtime environment CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, LD_LIBRARY_PATH, PATH, MANPATH
   local msg="=== $FUNCNAME: "
   local var=JX_RUNTIME_ENV
   if [ -n "${!var}" ]; then
       echo $msg skip as $var:${!var} use jre- or jx-runtime-env- to force it 
   else
       export $var=1
       jx-runtime-env-
   fi
}

jre(){  
   jx-runtime-env 
   jo 
   if [ -n "$OPTICKS_PREFIX" ]; then
       : TODO add these settings to standard environment
       opticks-
       export PYTHONPATH=$PYTHONPATH:$JUNOTOP
   fi   
}  
jre-(){ jx-runtime-env- ; }


jx-all()
{
   jx-extlib-oldtop
   jx-junoenv-latest
   jx-extlib-collection
   jx-extlib
   jx-env
   jx-sniper
   jx-sniper-env
   jx-offline
   jx-offline-data
   jx-opticks
}

jx-ccbase()
{
   local ccbase=$(dirname $(dirname $(dirname $(dirname $(dirname $CC)))))
   echo $ccbase
}

jx-extlib-oldtop()
{
   local ccbase=$(jx-ccbase)
   local oldtop
   case $ccbase in
       #/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830) oldtop=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs ;;
       /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830) oldtop=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs ;;
       /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120) oldtop=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs  ;;
   esac
   echo $msg CC $CC ccbase $ccbase oldtop $oldtop
   [ ! -d "$oldtop" ] && echo $msg oldtop $oldtop does not exist && return 3
   export JUNO_EXTLIB_OLDTOP=$oldtop
}

jx-junotop()
{
   local msg="=== $BASH_SOURCE $FUNCNAME "
   [ -z "$JUNOTOP" ] && echo $msg JUNOTOP is not defined && return 1 
   cd $JUNOTOP
}

jx-junoenv-latest()
{
   jx-junotop
   local msg="=== $BASH_SOURCE $FUNCNAME "
   [ ! -d "junoenv" ] && git clone git@code.ihep.ac.cn:JUNO/offline/junoenv.git 
   [ ! -d "junoenv" ] && echo $msg junoenv dir does not exist && return 2 
}

jx-junoenv-linked()
{
   local msg="=== $BASH_SOURCE $FUNCNAME "
   jx-junotop
   jx-extlib-oldtop 

   local oldtop=$(dirname $JUNO_EXTLIB_OLDTOP)
   ln -s $oldtop/junoenv junoenv
}

jx-extlib-collection()
{
   local ccbase=$(jx-ccbase)
   local collection
   case $ccbase in
       /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830) collection=22.1  ;;
       /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120) collection=22.2 ;;
   esac
   export JUNO_EXTLIB_COLLECTION=$JUNOTOP/junoenv/collections/$collection.sh
}

jx-extlib()
{
   local msg="=== $BASH_SOURCE $FUNCNAME "
   cd $JUNOTOP/junoenv

   if [ ! -d "$JUNOTOP/ExternalLibs" ]; then 
       bash junoenv libs reuse allpkgs
   else
       echo $msg JUNOTOP/ExternalLibs exists already 
   fi 
}

jx-env()
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -f "$JUNOTOP/bashrc.sh" ]; then
        bash junoenv env
    else
        echo $msg JUNOTOP/bashrc.sh exists already 
    fi
    source $JUNOTOP/bashrc.sh
}

jx-sniper()
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -d "$JUNOTOP/sniper" ]; then
        bash junoenv sniper 
    else
        echo $msg JUNOTOP/sniper exists already 
    fi

    cd $JUNOTOP/junoenv
}

jx-sniper-env()
{
    cd $JUNOTOP/sniper/InstallArea
    source bashrc 
    cd $JUNOTOP/junoenv
}

jx-offline()
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -d "$JUNOTOP/junosw" ]; then
        bash junoenv offline 
    else
        echo $msg JUNOTOP/junosw exists already 
    fi  

    cd $JUNOTOP/junoenv
}

jx-offline-config()
{
    cd $JUNOTOP/junosw/build
    local installprefix=$JUNOTOP/junosw/InstallArea
    cmake .. -DCMAKE_INSTALL_PREFIX=$installprefix -DCMAKE_CXX_STANDARD=17  
}
jx-offline-build()
{
    : HUH bash junoenv offline is not rerunnable so use this

    jx-offline-config || return 1  

    local njobs=-j$(nproc)
    cmake --build . $njobs || return 1 
    cmake --install . || return 1

    return 0 
}

jx-offline-data() 
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -d "$JUNOTOP/data" ]; then
        bash junoenv offline-data 
    else
        echo $msg JUNOTOP/data exists already 
    fi  

    cd $JUNOTOP/junoenv
}


jx-opticks()
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -d "$JUNOTOP/opticks" ]; then
        bash junoenv opticks 
    else
        echo $msg JUNOTOP/opticks exists already 
    fi  
    cd $JUNOTOP/junoenv
}




tds-dir(){ echo ${TDS_DIR:-/tmp/$USER/opticks/tds} ; }
tds-cd(){  cd $(tds-dir) ; }

tds-notes(){ cat << EON

N[blyth@localhost ntds2]$ pwd
/tmp/u4debug/ntds2

EON
}


tds-(){ 
   type $FUNCNAME
   local msg="=== $FUNCNAME :"

   [ -n "$DRY" ] && echo $msg DRY $DRY && return 0
   [ -z "$JX_RUNTIME_ENV" ]  && echo $msg MUST RUN jre BEFORE tds && return 2 
 
   local script=$JUNOTOP/junosw/Examples/Tutorial/share/tut_detsim.py
   if [ -z "$BP" ]; then
      H="" 
      B="" 
      T="-ex r" 
   else
      H="-ex \"set breakpoint pending on\""
      B="" 
      for bp in $BP ; do B="$B -ex \"break $bp\" " ; done
      T="-ex \"info break\" -ex r" 
   fi

   local iwd=$PWD
   local dir=$(tds-dir)
   mkdir -p $dir
   cd $dir



   local runline
   if [ -n "$PDB" ]; then 
       runline="ipython --pdb $script $*"
   else
       runline="gdb $H $B $T --args python $script $*"
   fi 

   export DIRECTORY="$PWD"
   export COMMANDLINE="$runline"

   vars="iwd dir DIRECTORY COMMANDLINE"
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 

   echo $COMMANDLINE
   date
   eval $COMMANDLINE
   date
   cd $iwd


}

tds0(){
   : run without opticks 
   local opts="--opticks-mode 0 --no-guide_tube --evtmax 2 " ;   
   tds- $opts gun $*
}



anamgr(){ cat << EOU
--opticks-anamgr
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
}




ntds0(){ OPTICKS_MODE=0 ntds ; }  #0b00   Ordinary running without Opticks involved at all  
ntds1(){ OPTICKS_MODE=1 ntds ; }  #0b01   Running with only Opticks doing the optical propagation 
ntds2(){ OPTICKS_MODE=2 ntds ; }  #0b10   Geant4 only with Opticks instrumentation : revive for getting U4Recorder to run inside monolith
ntds3(){ OPTICKS_MODE=3 ntds ; }  #0b11   Both Geant4 and Opticks 

ntds2_cf()
{
   N=0 GEOM=V0J008 ntds2
   [ $? -ne 0 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 0 && return 1

   N=1 GEOM=V1J008 ntds2
   [ $? -ne 1 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 1 && return 2

   return 0
}

ntds_examples(){ cat << EON
Examples::

   N=0 GEOM=V0J008 ntds2    ## save old 4-volume PMT geometry 
   N=1 GEOM=V1J008 ntds2    ## save new 2-volume PMT geometry 

EON
}

ntds()  # see j.bash for ntds3_old  #0b11   Running with both Geant4 and Opticks optical propagation
{
   env | grep =INFO

   local args=$*     
   local msg="=== $FUNCNAME :"
   local evtmax=${EVTMAX:-1}
   local mode=${OPTICKS_MODE:-3}
   local script=ntds$mode
   local base=/tmp/u4debug
   local tmpdir=$base/$script

   export SCRIPT=$script       ## SCRIPT controls name of logfile 
   export TDS_DIR=$tmpdir      ## controls running directory where logfile and outputs are written
   export TDS_LOG=$TDS_DIR/$SCRIPT.log 
   export U4Debug_SaveDir=$tmpdir


   vars="FUNCNAME SCRIPT TDS_DIR TDS_LOG SCRIPT U4Debug_SaveDir" 
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 

   #DEBUG=1 
   if [ -n "$DEBUG" ]; then 
       export U4Scintillation_Debug=INFO
       export U4Cerenkov_Debug=INFO
       export U4Hit_Debug=INFO
       export U4Debug=INFO
       export U4Recorder=INFO

       export SOpticksResource=INFO
       export junoSD_PMT_v2_Opticks=INFO
       export junoSD_PMT_v2=INFO
       export DsG4Scintillation=INFO
       export G4Cerenkov_modified=INFO
       export SLOG=1

       export DsPhysConsOptical_verboseLevel=1
       echo $msg DEBUG enabled tmpdir $tmpdir
   else
       unset U4Scintillation_Debug
       unset U4Cerenkov_Debug
       unset U4Hit_Debug
       unset U4Debug
       unset U4Recorder

       unset SOpticksResource
       unset junoSD_PMT_v2_Opticks
       unset DsG4Scintillation
       unset G4Cerenkov_modified

       unset SLOG
       unset DsPhysConsOptical_verboseLevel 

       echo $msg DEBUG NOT-enabled 
   fi 

   if [ -n "$DISABLE" ]; then 
       export U4__CollectGenstep_DsG4Scintillation_r4695_DISABLE=1
       export U4__CollectGenstep_G4Cerenkov_modified_DISABLE=1
       echo $msg DISABLE-enabled
   else
       unset U4__CollectGenstep_DsG4Scintillation_r4695_DISABLE
       unset U4__CollectGenstep_G4Cerenkov_modified_DISABLE 
       echo $msg DISABLE-NOT-enabled
   fi 

   if [ -n "$ZEROPHO" ]; then 
       export U4__CollectGenstep_DsG4Scintillation_r4695_ZEROPHO=1
       export U4__CollectGenstep_G4Cerenkov_modified_ZEROPHO=1
       echo $msg ZEROPHO-enabled
   else
       unset U4__CollectGenstep_DsG4Scintillation_r4695_ZEROPHO
       unset U4__CollectGenstep_G4Cerenkov_modified_ZEROPHO 
       echo $msg ZEROPHO-NOT-enabled
   fi 

   if [ -n "$SAVE" ]; then
       export LSExpDetectorConstruction__setupOpticks_pmtscan=1
       export G4CXOpticks__simulate_saveEvent=1
       export G4CXOpticks=INFO  
   else
       echo $msg SAVE not defined 
   fi 

   if [ -n "$GEOM" ]; then 
       #export G4CXOpticks__setGeometry_saveGeometry=$HOME/.opticks/GEOM/$GEOM
       export G4CXOpticks__SaveGeometry_DIR=$HOME/.opticks/GEOM/$GEOM
       export G4CXOpticks=INFO   # to see the directory 
   else
       echo $msg GEOM not defined : set GEOM to save the geometry to $HOME/.opticks/GEOM/$GEOM
   fi 


   local trgs=""     ## arguments after the opts : eg "gun" or "opticks" 

   IPHO=RainXZ1000_f8.npy
   #IPHO=RainXZ100k_f8.npy

   if [ -n "$IPHO" ]; then 
       export OPTICKS_INPUT_PHOTON=$IPHO
       export MOI=Hama:0:1000
       echo $msg IPHO defined : configuring OPTICKS_INPUT_PHOTON $OPTICKS_INPUT_PHOTON
       trgs="$trgs opticks"
   else
       unset OPTICKS_INPUT_PHOTON
       echo $msg IPHO not defined : not configuring OPTICKS_INPUT_PHOTON
       trgs="$trgs gun"
   fi 

   vars="OPTICKS_INPUT_PHOTON MOI trgs"
   for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done 


   export OPTICKS_EVENT_MODE=StandardFullDebug
   export OPTICKS_MAX_BOUNCE=31

   export POM=${POM:-1}
   export VERSION=${N:-1}
   export LAYOUT="POM $POM VERSION $VERSION"
   export PREDICT_EVTDIR=/tmp/$USER/opticks/GEOM/$GEOM/$SCRIPT/ALL$VERSION

   vars="POM N VERSION LAYOUT PREDICT_EVTDIR"
   for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done 

   if [ "$VERSION" == "0" ]; then 
       export U4Recorder__FAKES_SKIP=1
       echo $BASH_SOURCE : ENABLED U4Recorder__FAKES_SKIP : $U4Recorder__FAKES_SKIP 
   fi 

   local opts="" 
   opts="$opts --opticks-mode $mode"   
   opts="$opts --no-guide_tube"
   opts="$opts --additionacrylic-simplify-csg"

   #case $LSM in   ## pass into UseLSOpticalModel : NOT YET EXPLORED
   #   0) opts="$opts --old-optical-model"  ;;
   #   1) opts="$opts --new-optical-model"  ;;
   #esac 

   case $POM in     ## passed into UsePMTOpticalModel
      0) opts="$opts --no-pmt-optical-model"  ;;
      1) opts="$opts --pmt-optical-model"     ;;
   esac 

   case $VERSION in  ## passed into UsePMTNaturalGeometry
      0) opts="$opts --pmt-unnatural-geometry" ;; 
      1) opts="$opts --pmt-natural-geometry"   ;;
   esac

   opts="$opts --evtmax $evtmax"
   opts="$opts $(anamgr) "

   if [ -n "$DEBUG_DISABLE_STICKS" ]; then
       opts="$opts --debug-disable-sticks"
   fi 

   echo $msg opts : $opts 
   echo $msg trgs : $trgs 
   echo $msg args : $args 


   if [ "$(uname)" == "Linux" ]; then 

       if [ -f "$TDS_LOG" ]; then 
          echo $msg removing TDS_LOG : $TDS_LOG before run
          rm "$TDS_LOG" 
       fi 

       tds- $opts $trgs $args 

       if [ -f "$TDS_LOG" ]; then 
          echo $msg copy TDS_LOG : $TDS_LOG into PREDICT_EVTDIR $PREDICT_EVTDIR
          if [ -d "$PREDICT_EVTDIR" ]; then 
              cp $TDS_LOG ${PREDICT_EVTDIR}/
          else
              echo $msg PREDICT_EVTDIR : $PREDICT_EVTDIR does not exist 
          fi 
       fi 

   elif [ "$(uname)" == "Darwin" ]; then 
       #BASE=/tmp/$USER/opticks/$SCRIPT   
       #BASE=.opticks/$SCRIPT   
       #BASE=$base
       #BASE=/tmp/$USER/opticks/GEOM/$SCRIPT
       #source $OPTICKS_HOME/bin/rsync.sh $BASE ;;
       echo $msg rsync now done by j/ntds/ntds.sh 
   fi  


   env | grep =INFO
}

ninfo(){ env | grep =INFO ; }

getgeomtmp(){ source $OPTICKS_HOME/bin/rsync.sh /tmp/$USER/opticks/GEOM/${GEOM:-J005} ; : j/jx.bash ;  }

getgeom(){    source $OPTICKS_HOME/bin/rsync.sh .opticks/GEOM/${GEOM:-J005} ; : j/jx.bash ; }  




