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

jxn(){ cd ~/j/ntds ; pwd ; }
jxm(){ cd ~/j/mtds ; pwd ; } # minimalist variant 
jxp(){ cd ~/j/PMTSimParamSvcTest ; pwd ; }

jxo(){  open -a "Firefox Developer Edition" https://code.ihep.ac.cn/JUNO/offline ;  }

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
je(){ cd $JUNOTOP/junoenv && pwd && git status ; } 
jo(){ cd $JUNOTOP/junosw && pwd && git status ; } 
jd(){ cd $JUNOTOP/junosw_dirty && pwd && git status ; } 




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


  


tds-(){ 
   type $FUNCNAME
   local msg="=== $FUNCNAME :"

   [ -n "$DRY" ] && echo $msg DRY $DRY && return 0
   [ -z "$JX_RUNTIME_ENV" ]  && echo $msg MUST RUN jre BEFORE tds && return 2 
   [ -z "$SCRIPT" ] && echo $msg SCRIPT envvar is required to set logfile name  && return 3

 
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

   ## SCRIPT envvar overrides the opticks executable name based logname  
   TDS_LOG=$SCRIPT.log 
   TDS_TLOG=$SCRIPT.tlog 

   local klogs="TDS_LOG TDS_TLOG"
   local vlog 

   for klog in $klogs  ; do 
       vlog=${!klog}
       if [ -f "$vlog" ]; then 
           echo $msg removing $klog : $vlog before run
           rm "$vlog"
       fi 
   done  


   local runline=""
   if [ -n "$PDB" ]; then 
       runline="ipython --pdb $script $*"
   elif [ -n "$NODBG" ]; then 
       runline="python $script $*"
   else
       runline="gdb $H $B $T --args python $script $*"
   fi 

   runline="$runline 2>&1 | tee $TDS_TLOG "


   export DIRECTORY="$PWD"
   export COMMANDLINE="$runline"

   local vars="iwd dir DIRECTORY COMMANDLINE SCRIPT TDS_LOG TDS_TLOG TDS_LOG_COPYDIR"
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 

   for klog in $klogs  ; do 
       vlog=${!klog}
       if [ -f "$vlog" ]; then 
           date >> $vlog 
           for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" >> $vlog ; done 
       fi 
   done

   date
   eval $COMMANDLINE
   date

   for klog in $klogs  ; do 
       vlog=${!klog}
       if [ -f "$vlog" ]; then 
          date >> $vlog 
       fi 
   done

   for klog in $klogs  ; do 
       vlog=${!klog}
       if [ -f "$vlog" ]; then 
          if [ -n "$TDS_LOG_COPYDIR" -a -d "$TDS_LOG_COPYDIR" ]; then 
              echo $msg copy $klog : $vlog into TDS_LOG_COPYDIR $TDS_LOG_COPYDIR
              cp $vlog ${TDS_LOG_COPYDIR}/
          else
              echo $msg TDS_LOG_COPYDIR : $TDS_LOG_COPYDIR does not exist 
          fi 
       fi
   done

   local tlog="${TDS_TLOG}"
   local nlog="${TDS_TLOG}.npy" 
   if [ -f "$tlog" ]; then 
      TLOG_PATH=$tlog $HOME/j/bin/tlog.py 
      if [ -n "$TDS_LOG_COPYDIR" -a -d "$TDS_LOG_COPYDIR" ]; then 
          if [ -f "$nlog" ]; then 
              echo $msg copy $nlog into TDS_LOG_COPYDIR $TDS_LOG_COPYDIR
              cp $nlog ${TDS_LOG_COPYDIR}/
          else
              echo $msg FAILED TO CONVERT tlog $tlog into nlog $nlog 
          fi 
      else
          echo $msg TDS_LOG_COPYDIR : $TDS_LOG_COPYDIR does not exist 
      fi 
   else
      echo $msg nlog $nlog  
   fi  

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

anamgr-normal(){ cat << EOU
--anamgr-normal
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

anamgr-none(){ cat << EOU
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





ntds0(){ OPTICKS_INTEGRATION_MODE=0 ntds ; }  #0b00 Geant4 running with only minimal Opticks instrumentation 
ntds2(){ OPTICKS_INTEGRATION_MODE=2 ntds ; }  #0b10 Geant4 only with Opticks U4Recorder instrumentation 

ntds1(){ OPTICKS_INTEGRATION_MODE=1 ntds ; }  #0b01 Only Opticks GPU optical simulation 
ntds3(){ OPTICKS_INTEGRATION_MODE=3 ntds ; }  #0b11 Both Geant4 and Opticks GPU optical simulation  

ntds0_dbg(){ OPTICKS_INTEGRATION_MODE=0 ntds_dbg ; }
ntds2_dbg(){ OPTICKS_INTEGRATION_MODE=2 ntds_dbg ; }

ntds_dbg()
{
   #local bp=junoSD_PMT_v2::ProcessHits
   #local bp=C4OpBoundaryProcess::PostStepDoIt
   local bp=TaskWatchDog::setErr
   export BP=${BP:-$bp}

   local evtmax=3
   export EVTMAX=${EVTMAX:-$evtmax}

   echo $FUNCNAME BP $BP EVTMAX $EVTMAX

   N=0 GEOM=V0J008 ntds
   return 0
}


detect_cmake_build_type()
{
   : detect Debug or Release of last build by perl oneliner applied to build/CMakeCache.txt 
   perl -ne 'm/CMAKE_BUILD_TYPE:STRING=(.*)/ && print $1' $JUNOTOP/junosw/build/CMakeCache.txt 
}

ntds2_cf()
{
   : this function runs simulation with N:0 and N:1 geometries allowing comparison of histories
   : the logs are copied into event dir from TDS_LOG_COPYDIR setting by ntds

   local evtmax=1
   export EVTMAX=${EVTMAX:-$evtmax}
   export NODBG=1 

   local btype=$(detect_cmake_build_type)
   local gpfx=V          # V:Debug builds of junosw+custom4  
   case $btype in 
     Debug)   gpfx=V ;;    # V:Debug builds of junosw+custom4
     Release) gpfx=R ;;    # R:Release builds of junosw+custom4
   esac

   GPFX=${GPFX:-$gpfx}    # need to match with j/ntds/ntds.sh  AGEOM, BGEOM
   echo $BASH_SOURCE btype $btype gpfx $gpfx GPFX $GPFX

   N=0 GEOM=${GPFX}0J008 ntds2
   [ $? -ne 0 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 0 && return 1

   N=1 GEOM=${GPFX}1J008 ntds2
   [ $? -ne 1 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 1 && return 2

   return 0
}

ntds0_cf()
{
   : ntds0:not-WITH_G4CXOPTICKS 
   :    Geant4 running bare 
   :
   : ntds0:WITH_G4CXOPTICKS 
   :    minimal Opticks instrumentation : just event timing  
   :
   : this function runs simulations with N:0 and N:1 geometries allowing comparisons
   : of event timings without the U4Recorder overheads
   : the logs are copied into event dir from TDS_LOG_COPYDIR setting by ntds
   :
   : HMM: input photons will not work in this mode

   export EVTMAX=10
   export NODBG=1 

   #local gpfx=V          # V:Debug builds of junosw+custom4  
   local gpfx=R           # R:Release builds of junosw+custom4   
   GPFX=${GPFX:-$gpfx}    # need to match with j/ntds/ntds.sh  AGEOM, BGEOM


   N=0 GEOM=${GPFX}0J008 ntds0
   [ $? -ne 0 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 0 && return 1

   N=1 GEOM=${GPFX}1J008 ntds0
   [ $? -ne 1 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 1 && return 2

   return 0
}


ntds_noxj()
{
   [ -z "$OPTICKS_INTEGRATION_MODE" ] && echo $BASH_SOURCE : FATAL : ABORT AS OPTICKS_INTEGRATION_MODE IS NOT DEFINED && return 1 

   #local gpfx=R           # R:Release builds of junosw+custom4   
   local gpfx=V          # V:Debug builds of junosw+custom4  
   GPFX=${GPFX:-$gpfx}    # need to match with j/ntds/ntds.sh  AGEOM, BGEOM

   export EVTMAX=1

   export U4Tree__DISABLE_OSUR_IMPLICIT=1   
   ## currently disabling OSUR implicit is needed to avoid scrambling CSGNode border 

   NOXJ=1 GEOM=${GPFX}1J009 OPTICKS_INTEGRATION_MODE=${OPTICKS_INTEGRATION_MODE:-0} ntds

   ## HMM: INPUT PHOTONS WILL NOT WORK IN OPTICKS MODE 0 HOW AND WHERE TO RAISE AN ERROR FOR THAT ?
}

ntds_noxjsjfa()
{
   [ -z "$OPTICKS_INTEGRATION_MODE" ] && echo $BASH_SOURCE : FATAL : ABORT AS OPTICKS_INTEGRATION_MODE IS NOT DEFINED && return 1 

   #local gpfx=R           # R:Release builds of junosw+custom4   
   local gpfx=V          # V:Debug builds of junosw+custom4  
   GPFX=${GPFX:-$gpfx}    # need to match with j/ntds/ntds.sh  AGEOM, BGEOM

   export EVTMAX=1
   
   ## export U4Tree__DISABLE_OSUR_IMPLICIT=1   
   ## unset U4Tree__DISABLE_OSUR_IMPLICIT
   ## WHEN REMOVING AN ENVVAR MUST REMEMBER TO unset
   ## disabling OSUR implicit was needed previously to avoid scrambling CSGNode border 
   ## but the move to the new workflow should avoid that issue 
   ##
   ##
   ## C++ DEFAULTS IN THE blyth-122 BRANCH ARE NOW SET AS SHOWN  
   ## export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.1
   ## export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.1 
   ## export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.1
   ##   
   ##
   # NB setting OPTICKS_INPUT_PHOTON_FRAME or OPTICKS_INPUT_PHOTON here is ignored
   # as its unset then set in ntds

   NOXJ=1 NOSJ=1 NOFA=1 GEOM=${GPFX}1J011 OPTICKS_INTEGRATION_MODE=${OPTICKS_INTEGRATION_MODE:-0} ntds

   # this will fail for lack of input photon for OPTICKS_INTEGRATION_MODE=0 
}




ntds0_noxj(){ OPTICKS_INTEGRATION_MODE=0 ntds_noxj ; }
ntds1_noxj(){ OPTICKS_INTEGRATION_MODE=1 ntds_noxj ; }
ntds2_noxj(){ OPTICKS_INTEGRATION_MODE=2 ntds_noxj ; }
ntds3_noxj(){ OPTICKS_INTEGRATION_MODE=3 ntds_noxj ; }

ntds0_noxjsjfa(){ OPTICKS_INTEGRATION_MODE=0 ntds_noxjsjfa ; }
ntds1_noxjsjfa(){ OPTICKS_INTEGRATION_MODE=1 ntds_noxjsjfa ; }
ntds2_noxjsjfa(){ OPTICKS_INTEGRATION_MODE=2 ntds_noxjsjfa ; }
ntds3_noxjsjfa(){ OPTICKS_INTEGRATION_MODE=3 ntds_noxjsjfa ; }


ntds()  # see j.bash for ntds3_old  #0b11   Running with both Geant4 and Opticks optical propagation
{
   local args=$*     
   local msg="=== $FUNCNAME :"
   local evtmax=${EVTMAX:-1}
   local mode=${OPTICKS_INTEGRATION_MODE:-3}

   local ACTIVE_MODES="123" 
   if [ "${ACTIVE_MODES/$mode}" != "$ACTIVE_MODES" ]; then
        if [ -n "$OPTICKS_PREFIX" -a -d "$OPTICKS_PREFIX" ]; then 
            echo $msg OPTICKS_INTEGRATION_MODE $OPTICKS_INTEGRATION_MODE is active and OPTICKS_PREFIX $OPTICKS_PREFIX is detected  
        else
            echo $msg OPTICKS_INTEGRATION_MODE $OPTICKS_INTEGRATION_MODE REQUIRES OPTICKS_PREFIX $OPTICKS_PREFIX : ABORT 
            return 1 
        fi 
   fi 
   env | grep =INFO

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

   export G4CXOpticks=INFO   ## dump frame 

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
       export G4CXOpticks__saveGeometry_saveGGeo=1 
       export G4CXOpticks=INFO   # to see the directory 
   else
       echo $msg GEOM not defined : set GEOM to save the geometry to $HOME/.opticks/GEOM/$GEOM
   fi 

   export GBndLib__SENSOR_BOUNDARY_LIST=$(cat << EOL
    Pyrex/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/Vacuum
    Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/Vacuum
    Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum
    Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum
EOL
)


   gun=0   # 0/1/2: opticks input photons/gun_default/gun_wangyg
   GUN=${GUN:-$gun} 

   local gun_default="gun"
   local gun_wangyg="gun --particles gamma --momentums 2.223 --momentums-interp KineticEnergy --positions 0 0 0"
   local trgs=""     ## arguments after the opts : eg "gun" or "opticks" 

   case $GUN in  
     0) trgs="$trgs opticks"  ;;
     1) trgs="$trgs $gun_default" ;;
     2) trgs="$trgs $gun_wangyg" ;;
   esac

   unset MOI 
   unset OPTICKS_INPUT_PHOTON
   unset OPTICKS_INPUT_PHOTON_FRAME

   layout=""
   if [ "$GUN" == "0" ]; then 

       #ipho=RainXZ_Z230_100_f8.npy        
       #ipho=RainXZ_Z230_1000_f8.npy
       #ipho=RainXZ_Z230_10k_f8.npy        
       ipho=RainXZ_Z230_100k_f8.npy
       #ipho=RainXZ_Z230_X700_10k_f8.npy  ## X700 to illuminate multiple PMTs
       #ipho=GridXY_X700_Z230_10k_f8.npy 
       #ipho=GridXY_X1000_Z1000_40k_f8.npy

       export OPTICKS_INPUT_PHOTON=$ipho

       #oipf=Hama:0:1000
       #oipf=Hama:0:0
       oipf=NNVT:0:1000 
       #oipf=PMT_20inch_veto:0:1000

       export OPTICKS_INPUT_PHOTON_FRAME=$oipf

       layout="OIPF_$OPTICKS_INPUT_PHOTON_FRAME"

       if [ -n "$OPTICKS_PREFIX" -a -d "$OPTICKS_PREFIX" ]; then
           echo $msg : proceed with GtOpticksTool input photons : using Opticks functionality 
       else
           echo $msg : Opticks not-configured : CANNOT PROCEED with GtOpticksTool input photons : fallback to gun running  
           trgs="$trgs gun"
           export BP=TaskWatchDog::setErr
       fi
   fi 




   vars="BASH_SOURCE FUNCNAME OPTICKS_PREFIX IPHO OPTICKS_INPUT_PHOTON OPTICKS_INPUT_PHOTON_FRAME MOI trgs"
   for var in $vars ; do printf " %30s : %s \n" "$var" "${!var}" ; done 

   export OPTICKS_EVENT_MODE=StandardFullDebug
   export OPTICKS_MAX_BOUNCE=31
   #export OPTICKS_MAX_PHOTON=10000
   export OPTICKS_MAX_PHOTON=100000

   export POM=${POM:-1}
   export VERSION=${N:-1}
   export LAYOUT=$layout
   export TDS_LOG_COPYDIR=/tmp/$USER/opticks/GEOM/$GEOM/$SCRIPT/ALL$VERSION

   
   vars="NOXJ NOSJ NOFA POM N VERSION LAYOUT TDS_LOG_COPYDIR"
   for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done 


   #export U4Recorder__EndOfRunAction_Simtrace=1
   ## experimental simtrace, that could be very expensive : maybe only when frame set ?

   #export U4Recorder__UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft=1  
   ## above setting makes possible to random align, but changes events and consumes 20-30% more randoms


   ## HMM: NOTE THAT WITHOUT THESE UNSETS THEN 
   ## THE N=0 RUN SETTING FOR FIRST FUNCTION INVOKATIONS 
   ## WILL LEAK INTO THE SECOND N=1 INVOKATION OF THE FUNCTION
   ##
   ## NOTICE THIS PROBLEM ONLY EFFECTS CONDITIONAL SETTINGS 
   ## THAT ARE NOT ALWAYS SET 
   ##
   ## HENCE TO AVOID SETTING CONFUSION FROM ENV POLLUTION 
   ## NEED THE UNSETS : OR COULD USE A SCRIPT TO CALL THE BASH FUNCTION 
   ## SO START FROM FRESH ENV 

   #unset U4Recorder__FAKES_SKIP
   #unset U4Recorder__ClassifyFake_FindPV_r
   #
   #if [ "$VERSION" == "0" ]; then 
   #if [ "$VERSION" == "0" -o "$VERSION" == "1" ]; then    ## UNNECESSARILY SKIP FAKES IN B FOR FAIRNESS
   #
   #    if [ -n "$NOFAKESKIP" ]; then 
   #        echo $BASH_SOURCE : NOFAKESKIP SWITCH : NOT ENABLING U4Recorder__FAKES_SKIP : $U4Recorder__FAKES_SKIP 
   #    else
   #        export U4Recorder__FAKES_SKIP=1
   #        export U4Recorder__ClassifyFake_FindPV_r=1 
   #        ## FindPV_r is needed to make fake skipping work : but its slow
   #
   #        echo $BASH_SOURCE : ENABLED U4Recorder__FAKES_SKIP : $U4Recorder__FAKES_SKIP 
   #    fi 
   #fi 

   local opts="" 
   opts="$opts --opticks-mode $mode"   
   opts="$opts --no-guide_tube"
   opts="$opts --additionacrylic-simplify-csg"
   opts="$opts --no-toptask-show"

   #case $LSM in   ## pass into UseLSOpticalModel : NOT YET EXPLORED
   #   0) opts="$opts --old-optical-model"  ;;
   #   1) opts="$opts --new-optical-model"  ;;
   #esac 

   case $POM in     ## passed into UsePMTOpticalModel
      0) opts="$opts --no-pmt-optical-model"  ;;
      1) opts="$opts --pmt-optical-model"     ;;
   esac 

   #case $VERSION in  ## passed into UsePMTNaturalGeometry
   #   0) opts="$opts --pmt-unnatural-geometry" ;; 
   #   1) opts="$opts --pmt-natural-geometry"   ;;
   #esac
   # no need to act on VERSION as now default 

   case ${NOXJ:-0} in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-xj" ;; 
   esac

   case ${NOSJ:-0} in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-sj" ;; 
   esac

   case ${NOFA:-0} in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-fa" ;; 
   esac




   opts="$opts --evtmax $evtmax"

   if [ "$mode" == "0" ]; then 
       opts="$opts $(anamgr-none) "
       #opts="$opts"
   else
       opts="$opts $(anamgr) "
   fi 

   if [ -n "$DEBUG_DISABLE_STICKS" ]; then
       opts="$opts --debug-disable-sticks"
   fi 

   echo $msg opts : $opts 
   echo $msg trgs : $trgs 
   echo $msg args : $args 

   if [ "$(uname)" == "Linux" ]; then 
       tds- $opts $trgs $args 
   else
       echo tds- $opts $trgs $args 
   fi  

   env | grep =INFO
}


mtds_0v2_grab()
{
   : grabbing now done by ~/j/mtds/mtds.sh grab_evt 
   source $OPTICKS_HOME/bin/rsync.sh /tmp/$USER/opticks/GEOM/mtds0
   source $OPTICKS_HOME/bin/rsync.sh /tmp/$USER/opticks/GEOM/mtds2
}


mtds_0v2(){  

  local logdir=/tmp/$FUNCNAME
  mkdir -p $logdir
 
  export TDS_LOG_COPYDIR=$logdir
  export EVTMAX=10

  mtds0
  mtds2

  : initial thought was to keep the logs together with event 
  : BUT is rather convenient to keep them separate as grabbing logs 
  : only is typically much faster than the full event when using U4Recorder 
}


mtds_bp(){
   BP=CLHEP::MixMaxRng::flat mtds0 
   BP=CLHEP::MixMaxRng::flat mtds2
}



mtds0(){ OPTICKS_INTEGRATION_MODE=0 mtds ; }
mtds2(){ OPTICKS_INTEGRATION_MODE=2 mtds ; }

mtds()
{
   : minimal launch to look into unexpected opticksMode:0 vs opticksMode:2 difference
   local args=$*     
   local msg="=== $FUNCNAME :"
   local evtmax=${EVTMAX:-1}
   local mode=${OPTICKS_INTEGRATION_MODE:-3}
   local script=mtds$mode
   local base=/tmp/u4debug
   local tmpdir=$base/$script

   export SCRIPT=$script       ## SCRIPT controls name of logfile 
   export TDS_DIR=$tmpdir      ## controls running directory where logfile and outputs are written

   export POM=${POM:-1}
   export VERSION=${N:-1}

   local vars="POM N VERSION"
   local var 
   for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done 

   local opts=""     
   local trgs=""     ## arguments after opts : eg "gun" or "opticks" 
   local args=$*     ## arguments after trgs usually none

   trgs="$trgs gun"

   opts="$opts --opticks-mode $mode"   
   opts="$opts --no-guide_tube"
   opts="$opts --additionacrylic-simplify-csg"

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

   tds- $opts $trgs $args 

}






ninfo(){ env | grep =INFO ; }

getgeomtmp(){ source $OPTICKS_HOME/bin/rsync.sh /tmp/$USER/opticks/GEOM/${GEOM:-J005} ; : j/jx.bash ;  }

getgeom(){    source $OPTICKS_HOME/bin/rsync.sh .opticks/GEOM/${GEOM:-J005} ; : j/jx.bash ; }  




