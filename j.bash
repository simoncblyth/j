# ~/j/j.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/j.bash

[ "$DBG" == "1" ] && echo $BASH_SOURCE && dbg 

j-usage(){ cat << EOU
Common source for JUNO high level bash functions
====================================================

::

   cd 
   git clone git@github.com:simoncblyth/j.git
   # Add "source $HOME/j/j.bash" to .bash_profile 



EOU
}

j-env(){  echo -n ; }
j-(){ . $HOME/j/j.bash && j-env $* ; }
j(){  cd ~/j && pwd && git status ; }

jvi(){ vi $BASH_SOURCE && jfu ; }
jfu(){ source $BASH_SOURCE ; }

################### NAVIGATING  ###################################

# -false to end sequence of ors 
jcl(){ local f="" ; for name in $* ; do f="$f -name $name.* -o " ; done ; find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' ; } 
jfi(){ local f="" ; for name in $* ; do f="$f -name $name   -o " ; done ; find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' ; } 

jcv-(){ local fi=$(jcl $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }
jfv-(){ local fi=$(jfi $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }

jcv(){ cd $JUNOTOP/offline ; jcv- $* ; : edit files identified by stem ;  } 
jfv(){ cd $JUNOTOP/offline ; jfv- $* ; : list files identified by wildcard ; } 

jgr-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -a ! -path '*.sh' -a ! -path '*.csh'  -type f -exec grep -H "${1:-G4OPTICKS}" {} \; ; } 
jgr(){ cd $JUNOTOP/offline ; jgr- $* ; : search files with the query string and show matches - skips are made to avoid cmt garbage ;  } 

jgl-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -a ! -path '*.sh' -a ! -path '*.csh'  -type f -exec grep -l "${1:-G4OPTICKS}" {} \; ; }
jgl(){ cd $JUNOTOP/offline ; jgl- $* ; : search files with the query string and list matched paths - skips are made to avoid cmt garbage ; } 
 
jt(){ cd $JUNOTOP ; } 
je(){ cd $JUNOTOP/junoenv && pwd ; } 
jo(){ cd $JUNOTOP/offline && pwd && svn status ; } 
js(){ cd $JUNOTOP/offline/Simulation/DetSimV2/$1 && pwd ; } 
psi(){ js PMTSIM/src ; }
jb(){ cd $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge/cmt && pwd ; } 
jp(){ cd $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge/src/phys && pwd ; } 
td(){ vi $JUNOTOP/offline/Examples/Tutorial/share/tut_detsim.py ; }
jsd(){ jcv junoSD_PMT_v2 ; }

#jcvv(){ jcv NNVT_MCPPMT_PMTSolid Hamamatsu_R12860_PMTSolid ; }
#jcvv(){ jcv Hamamatsu_R12860_PMTSolid ; }
jcvv(){ jcv NNVTMCPPMTManager NNVT_MCPPMT_PMTSolid HamamatsuR12860PMTManager Hamamatsu_R12860_PMTSolid ; }

gb(){ cd $JUNOTOP/ExternalLibs/Build/geant4.10.04.p02 && pwd ; } 

jf(){
   type jt
   type je
   type jo
   type js
   type psi
   type jb  
   type jp
   type td
   type gb  
}


jokc(){
    : list offline .cc WITH_G4OPTICKS
    cd $JUNOTOP/offline
    find . -name '*.cc' -exec grep -l WITH_G4OPTICKS {} \+  
}

################### BUILDING  ###################################


jeb(){ cd $JUNOTOP/junoenv ; bash junoenv ${1:-dummy} ; }
jsniper(){ jeb sniper ; }
joffline(){ jeb offline ; }


jlibs(){
    cd $JUNOTOP/junoenv
    local libs=$(bash junoenv libs list | perl -ne 'm, (\S*)@, && print "$1\n"' -)
    for lib in $libs ; do 
        echo $lib 
        bash junoenv libs all $lib || return 1 
    done  
}    



jck(){
   [ -z "$JUNOTOP" ] && echo ERROR no JUNOTOP && return 1
   [ ! -d "$JUNOTOP" ] && echo ERROR no JUNOTOP $JUNOTOP dir && return 2
   cd $JUNOTOP 
   [ ! -d "junoenv" ] && svn co http://juno.ihep.ac.cn/svn/offline/trunk/installation/junoenv

   cd $JUNOTOP/junoenv
}

jpq(){
   jck
   [ $? -ne 0 ] && echo $msg FAIL at jck && return 1

   bash junoenv preq
   [ $? -ne 0 ] && echo $msg FAIL at preq && return 1
}

jex-all(){ 
   cd $JUNOTOP/junoenv
   bash junoenv libs list | perl -ne 'm, (\S*)@, && print "$1\n"' 
}
jex-uninstalled(){
   cd $JUNOTOP/junoenv
   bash junoenv libs list | perl -ne 'm, \[ \] (\S*)@, && print "$1\n"'
}

jex()
{ 
   : install externals  
   local msg="=== $FUNCNAME :"

   local libs=$(jex-uninstalled)
   local lib
   for lib in $libs ; do
       bash junoenv libs all $lib
       [ $? -ne 0 ] && echo $msg FAIL at $lib && return 1
   done
}

jen(){
   : create JUNOTOP/bashrc.sh script that sets up the runtime environment for usage of the externals
   local msg="=== $FUNCNAME :"
   jck
   [ $? -ne 0 ] && echo $msg FAIL at jck && return 1

   cd $JUNOTOP/junoenv
   bash junoenv env resetup
   [ $? -ne 0 ] && echo $msg FAIL at env && return 1

   cd $JUNOTOP
   source bashrc.sh
}

joko(){
   local path=ExternalInterface/Externals/OpticksG4OK/cmt/requirements
   local dir=$(dirname $path)

   cd $JUNOTOP
   mkdir -p $dir
   echo "v0" > $dir/version.cmt

   cat << EOR > $path
package OpticksG4OK

macro OpticksG4OK_home "${OPTICKS_TOP}"

macro OpticksG4OK_cppflags " \`opticks-config --cflags G4OK\` "
macro OpticksG4OK_linkopts " \`opticks-config --libs G4OK\` " 
   
EOR
   echo $msg path $path 
   cat -n $path 
}

jor(){
   cd $JUNOTOP

   local pkg=OpticksG4OK
   local path=ExternalInterface/EIRelease/cmt/requirements
   grep $pkg $path > /dev/null
   [ $? -eq 0 ] && echo $msg path $path already has $pkg && return 0

   cat << EOT >> $path

use $pkg    v* Externals
EOT
   echo path $path
   cat -n $path
}

jei(){   
   : https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation
   : building the interface between cmt and external libraries
   : http://juno.ihep.ac.cn/svn/cmtlibs/trunk
   :    EIRelease/
   :    Externals/
   :    cmt/
   :

   cd $JUNOTOP/junoenv
   bash junoenv cmtlibs

   cd $JUNOTOP/ExternalInterface/EIRelease/cmt/
   source setup.sh  
}

jes(){
   cd $JUNOTOP/junoenv
   bash junoenv sniper
   cd $JUNOTOP/sniper/SniperRelease/cmt/
   source setup.sh
}

jep(){
   cd $JUNOTOP/offline
   local path=Simulation/DetSimV2/DetSimPolicy/cmt/requirements
   local pkg=OpticksG4OK
   grep $pkg $path
   [ $? -eq 0 ] && echo path $path already has pkg $pkg && return 0

   cat << EOP >> $path

use $pkg v* Externals
EOP

   cat -n $path
}

jeo(){ 
   : building the offline
   cd $JUNOTOP/junoenv
   bash junoenv offline

   #cd $JUNOTOP/offline/JunoRelease/cmt/
   #cmt br cmt config
   #source setup.sh
   #cmt br cmt make  
}

jeda(){
   cd $JUNOTOP/junoenv 
   bash junoenv offline-data
}

mak(){
   cmt br cmt config
   source setup.sh
   cmt make 
}

jenv(){ 
   source $HOME/juno-tutorial/bashrc 
}








joc(){
   # from junoenv-offline.sh:junoenv-offline-compile which is called by "bash junoenv offline"
   cd $JUNOTOP/offline/JunoRelease/cmt
   cmt br cmt config
   source setup.sh
   cmt br cmt make   
}

jbc(){
    cd $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge/cmt
    cmt br cmt config
    source setup.sh
    #cmt br cmt make
    make
}












jokc(){
    : list offline .cc WITH_G4OPTICKS
    cd $JUNOTOP/offline
    find . -name '*.cc' -exec grep -l WITH_G4OPTICKS {} \+  
}



jokp0-(){ cat << EOP
Simulation/DetSimV2/DetSimPolicy/cmt
Simulation/DetSimV2/PhysiSim/cmt
Simulation/DetSimV2/DetSimAlg/cmt
Simulation/DetSimV2/DetSimOptions/cmt
Simulation/DetSimV2/PMTSim/cmt
Simulation/DetSimV2/G4OpticksBridge/cmt
EOP
}


joc-list(){
   : list cmt directories in dependency order without the usual cmt guff
   cd $JUNOTOP/offline/JunoRelease/cmt
   cmt br pwd | grep -v ^#
}

jokdirs--eg(){ cat << EOX
Simulation/DetSimV2/PhysiSim/cmt
Simulation/DetSimV2/PMTSim/cmt
Simulation/DetSimV2/DetSimOptions/cmt
EOX
}

jokdirs--(){
   local cache="$HOME/.jokdirs"
   if [ -f "$cache" ]; then 
       cat $cache
       return 0
   fi 
   local dirs=$(joc-list)
   local dir

   : directories in CMT dependency order with files that contain WITH_G4OPTICKS
   local sel=() 
   for dir in $dirs ; do 
       local ncc=$(find $dir/.. -name '*.cc' -exec grep -l WITH_G4OPTICKS {} \+ | wc -l)
       if [ $ncc -gt 0 ]; then 
           local rel=${dir/$JUNOTOP\/offline\/}
           sel+=($rel)
       fi
   done 

   local s 
   for s in ${sel[@]}; do echo $s ; done

   if [ ! -f "$cache" ]; then 
      for s in ${sel[@]}; do echo $s >> $cache ; done
   fi
}


jokp--(){
    : list relative cmt dirs of projects having .cc WITH_G4OPTICKS : caution the order is arbitrary
    cd $JUNOTOP/offline
    find . -name '*.cc' -exec grep -l WITH_G4OPTICKS {} \+  | xargs -n1 dirname | xargs -n1 dirname | sort | uniq | perl -ne 'm,\./(\S*), && print "$1/cmt\n"' - 
}  

jokp-(){
   jokp-- | grep -v Examples  | grep -v DetSimMTUtil
}



jokp(){
   : in all projects touch sources WITH_G4OPTICKS and rebuild using cmt Makefile

   local msg="=== $FUNCNAME :"
   echo $msg CMTEXTRATAGS : $CMTEXTRATAGS
   [ -z "$JFU_JRE" ] && echo $msg MUST RUN jre BEFORE jokp && return 2

   local dir
   local rel
   echo $msg jokdirs-- 
   jokdirs--
   for rel in $(jokdirs--) ; do 
       local dir=$JUNOTOP/offline/$rel
       [ ! -d "$dir" ] && echo $msg ERROR no such dir $dir && return 1
       cd $dir
       pwd
   done
 

   for rel in $(jokdirs--) ; do 

       local dir=$JUNOTOP/offline/$rel
       [ ! -d "$dir" ] && echo $msg ERROR no such dir $dir && continue
       cd $dir
       printf "\n\n\n ================== $(pwd) ==============\n\n\n" 

       : cmt dependency check doesnt notice change in CMTEXTRATAGS so must touch to force recompile
       : somehow clean is not working to force recompile

       cmt config
       source setup.sh

       touch $(grep -l WITH_G4OPTICKS ../src/*.cc) 
       # touching files as staleness checking doesnt work with macro changes

       #make clean
       make  
       [ $? -ne 0 ] && echo $msg make ERROR && break        
   done
   echo $msg CMTEXTRATAGS : $CMTEXTRATAGS

}

jmak(){
   local rel 
   while read rel ; do  
       local dir=$JUNOTOP/offline/$rel
       [ ! -d "$dir" ] && echo $msg ERROR no such dir $dir && return 1
       cd $dir
       pwd
       printf "\n\n\n ================== $(pwd) ==============\n\n\n" 

       : cmt dependency check doesnt notice change in CMTEXTRATAGS so must touch to force recompile
       : somehow clean is not working to force recompile

       cmt config
       source setup.sh

       touch $(grep -l WITH_G4OPTICKS ../src/*.cc) 
       # touching files as staleness checking doesnt work with macro changes

       #make clean
       make  
       [ $? -ne 0 ] && echo $msg make ERROR && break        
   done
}

jdso(){ echo Simulation/DetSimV2/DetSimOptions/cmt | jmak ; }



################### ENVIRONMENT ###################################

jg4(){ echo $JUNOTOP/ExternalLibs/Build/geant4.10.04.p02 ; } 
jok(){ echo $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge ; }

jre()
{
   : setup the runtime environment CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, LD_LIBRARY_PATH

   local ok=$(jok)
   export JFU_JRE=1 

   echo jre [ 
   source $JUNOTOP/bashrc.sh
   source $JUNOTOP/sniper/SniperRelease/cmt/setup.sh
   source $JUNOTOP/offline/JunoRelease/cmt/setup.sh
   echo jre.gob [ 
   source $ok/cmt/setup.sh  # result of : cmt br cmt config
   echo jre.gob ] 
   echo jre ]
}


jre-notes(){ cat << EON

$JUNOTOP/bashrc.sh
    invokes bashrc of all the externaks including ~/junotop/ExternalLibs/Opticks/0.1.0/bashrc
    that contains only::

        source ${OPTICKS_TOP}/bin/opticks-setup.sh    

     TODO: avoid errors when have no OPTICKS_TOP

EON
}


################### RUNNING ###################################

elog(){
   : hmm opticks logging control - should be elsewhere ? no opticks is part of JUNO Offline - so it should be here
   export X4Solid=INFO
   export X4PhysicalVolume=INFO
   export GGeo=INFO
   export GMaterialLib=INFO
   export GPropertyLib=INFO
   export GGeoSensor=INFO
   export CGenstepCollector=INFO 
   export G4Opticks=INFO 
   export OKMgr=INFO
   export OKPropagator=INFO
   export OpMgr=INFO 
   export OpEngine=INFO 
   export OpticksRun=INFO 
   export OpticksGen=INFO
   export OEvent=INFO 
   export OPropagator=INFO 
   export OGeo=INFO
   export GMesh=INFO 
   export OContext=INFO
}

okt(){
   type $FUNCNAME
   [ -z "$OPTICKS_KEY" ] && echo $msg MISSING MANDATORY OPTICKS_KEY envvar && return 1 
   [ "$(which OKTest 2>/dev/null)" == "" ] && echo $msg missing opticks env use : oe- && return 2 
   #elog

   local args="OKTest --xanalytic --save --dbggsload --dumphit --dbggsdir /tmp/blyth/opticks/dbggs --printenabled --pindex ${P:-1000} "

   local iwd=$PWD
   local dir=/tmp/okt
   mkdir -p $dir
   cd $dir

   gdb_ $args 
}

gdb_(){
   : prepares and invokes gdb - sets up breakpoints based on BP envvar containing space delimited symbols 
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

   local runline="gdb $H $B $T --args $* "
   echo $runline
   date
   eval $runline 
   date
}



############################################# tds : tut_detsim.py runner #############################


#pyj(){ python $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge/share/pyjob_acrylic.py ; }

tds0(){
   local opts="--opticks-mode 0 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 10"  
   tds- $opts 
}

tds-logenv(){
   export GGeo=INFO
   export GParts=INFO
   #export X4MaterialTable=INFO
   #export GMaterialLib=INFO 
   export G4Opticks=INFO
   export OpticksAim=INFO
}

tds(){ 
   #local opts="--no-guide_tube --pmt20inch-polycone-neck --evtmax 2"
   #local opts="--opticks-mode 0 --no-guide_tube --pmt20inch-polycone-neck --evtmax 2"  
   #local opts="--opticks-mode 1 --no-guide_tube --pmt20inch-polycone-neck --evtmax 2"  
   local opts="--opticks-mode 1 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 10"  
   #local opts="--opticks-mode 1 --no-guide_tube --evtmax 2"  

   #export OPTICKS_EMBEDDED_COMMANDLINE="pro"   # default  
   #export OPTICKS_EMBEDDED_COMMANDLINE="dev"  
   #export OPTICKS_EMBEDDED_COMMANDLINE=" --compute --embedded --xanalytic --save --natural --printenabled --pindex 0"

   tds- $opts 
}
tds-(){ 
   local msg="=== $FUNCNAME :"

   if [ "${CMTEXTRATAGS/opticks}" != "${CMTEXTRATAGS}" ]; then 
       [ -z "$OPTICKS_TOP" ] && echo $msg OPTICKS_TOP is not defined && return 1
   fi

   [ -z "$JFU_JRE" ]  && echo $msg MUST RUN jre BEFORE tds && return 2 

   local label="tds" 
   local arg 
   for arg in $* ; do
       case $arg in  
           --no-guide_tube)           label="${label}_ngt" ;;
           --pmt20inch-polycone-neck) label="${label}_pcnk" ;;
           --pmt20inch-simplify-csg)  label="${label}_sycg" ;;
       esac 
   done
   
   local dbggdmlpath="$OPTICKS_TOP/${label}_202102.gdml"
   echo $msg label $label dbggdmlpath $dbggdmlpath 
   type $FUNCNAME

   #export OPTICKS_RESOURCE_LAYOUT=2
   export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="--dbggdmlpath $dbggdmlpath"  # --dbggssave --dumphit --layout 100 --savesensor
    
   local script=$JUNOTOP/offline/Examples/Tutorial/share/tut_detsim.py
   local args="gun"  

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
   local dir=/tmp/tds
   mkdir -p $dir
   cd $dir
   local runline="gdb $H $B $T --args python $script $* $args "
   echo $runline
   date
   eval $runline 
   date
   cd $iwd
}


############################## tds runners with various breakpoints #########################

tdsh-(){ cat << EOB
junoSD_PMT_v2::junoSD_PMT_v2
junoSD_PMT_v2::Initialize
junoSD_PMT_v2::ProcessHits
junoSD_PMT_v2::get_pmtid
junoSD_PMT_v2::EndOfEvent
EOB
}
tdsh(){ BP="$(tdsh-)" tds ; }

tds1(){ BP=R12860PMTManager::R12860PMTManager     tds ; } 

tds2-(){ cat << EOB
G4Torus::G4Torus
DetSim0Svc::createDetectorConstruction
R12860PMTManager::R12860PMTManager
EOB
}
tds2(){ BP="$(tds2-)" tds ; }

tds3-(){
   : breakpoint signatures of PMTSolid ctors
   local iwd=$PWD
   cd $JUNOTOP/offline/Simulation/DetSimV2/PMTSim/src
   ls -1 *_PMTSolid.cc | perl -p -e 's,(\S*).cc,$1::$1,' - 
   cd $iwd
}
tds3(){ BP="$(tds3-)" tds ; }


tds4-(){ cat << EOB
DsG4Scintillation::PostStepDoIt
G4VUserPhysicsList::Construct
LSExpPhysicsList::ConstructProcess
G4OpticksAnaMgr::BeginOfRunAction
EOB
}

tds4(){ BP="$(tds4-)" tds ; }




