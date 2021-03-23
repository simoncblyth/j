# ~/j/j.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/j.bash
[ "$DBG" == "1" ] && dbg_head $BASH_SOURCE

j-usage(){ cat << EOU
Common source for JUNO high level bash functions
====================================================

::

   cd ; git clone git@github.com:simoncblyth/j.git ; echo "source \$HOME/j/j.bash" >> .bash_profile 

Install Link
---------------

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation#install_offline_data

Offline Trac Links
---------------------

* https://juno.ihep.ac.cn/trac/changeset/4353/offline


* https://juno.ihep.ac.cn/trac/search?q=r4090
* https://juno.ihep.ac.cn/trac/browser/offline/trunk/Simulation/DetSimV2/PMTSim#src

* https://juno.ihep.ac.cn/trac/changeset/31/cmtlibs
* https://juno.ihep.ac.cn/trac/browser/cmtlibs#trunk

* https://juno.ihep.ac.cn/trac/timeline

Sniper Links
---------------

* https://github.com/SNiPER-Framework/sniper/releases/tag/v1.6
* https://github.com/SNiPER-Framework/sniper/commit/f66fafa399f7a46af5044b9a877b503277cdfb69
* https://juno.ihep.ac.cn/trac/browser/offline/trunk/installation/junoenv/junoenv-sniper.sh
* https://juno.ihep.ac.cn/trac/browser/cmtlibs/trunk/Externals/ROOT/cmt/requirements?rev=31

slack kanban
--------------

* https://juno-analysis.slack.com 
* https://juno.ihep.ac.cn/kanboard/

Example Paths
---------------

/junofs/users/lint/juno-release/J19v1r1-branch/jobs/geometry_acrylic.gdml

    still with torus 

Simon, this is Jilei's muon jobs: 

    /junofs/users/xujl/juno7/sim_results/J18v2r1/muon/twomu/optical/






Index
------

* https://bitbucket.org/simoncblyth/jnu/commits/
* http://juno.ihep.ac.cn/trac/timeline
* http://juno.ihep.ac.cn/mediawiki/index.php/InternalWeb
* http://juno.ihep.ac.cn/mediawiki/index.php/Offline_Software
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Detsimuserguide
* https://juno.ihep.ac.cn/~offline/Doc/detsim/quickstart.html

*  http://juno.ihep.ac.cn/~offline/Doxygen/offline/html/files


OPTICKS_TOP envvar : a trick for Opticks developers working in peer-to-peer fashion 
---------------------------------------------------------------------------------------------

When OPTICKS_TOP is defined it overrides the opticks installation used by junoenv.
This makes it possible to use a separately installed Opticks installation.
 

/home/blyth/junotop/junoenv/junoenv-external-libs.sh::

    819 function junoenv-external-libs-list {
    820     local mode=$1
    821 
    822     [ -n "$OPTICKS_TOP" ] && echo opticks
    823 
    ### Ahem : should be checking CMTEXTRATAGS for opticks, not checking OPTICKS_TOP ?
    ### switched to :  [ "${CMTEXTRATAGS/opticks}" != "$CMTEXTRATAGS" ] && echo opticks

::

    096 function juno-ext-libs-opticks-generate-sh {
     97     local msg="====== $FUNCNAME :"
     98     local prefix=$(juno-ext-libs-opticks-install-dir)
     99     echo $msg replacing bashrc 
    100 
    101     # When OPTICKS_TOP is defined it overrides the opticks installation used by junoenv.
    102     # This makes it possible to use a separately installed Opticks installation.
    103 
    104 cat <<EOF > bashrc
    105 if [ -n "\${OPTICKS_TOP}" ]; then 
    106    source \${OPTICKS_TOP}/bin/opticks-setup.sh
    107 else
    108    source $prefix/bin/opticks-setup.sh
    109 fi
    110 EOF
    111 }
    112 function juno-ext-libs-opticks-generate-csh {
    113     local msg="SCB $FUNCNAME :"
    114     local prefix=$(juno-ext-libs-opticks-install-dir)
    115     echo $msg replacing tcshrc 
    116 
    117 cat <<EOF > tcshrc
    118 if [ -n "\${OPTICKS_TOP}" ]; then 
    119    source \${OPTICKS_TOP}/bin/opticks-setup.csh 
    120 else
    121    source $prefix/bin/opticks-setup.sh
    122 fi
    123 EOF
    124 }


Opticks JunoENV Links
----------------------

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation#Install_Opticks_using_JunoENV
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation#building_the_offline_-DWITH_G4OPTICKS
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Detsimuserguide/UsingOpticks


CMT Refs
----------

* https://svn.lal.in2p3.fr/projects/CMT/CMT/v1r10p20011126/doc/CMTDoc.html#Defining%20the%20user%20tags


Simulation
---------------

* http://juno.ihep.ac.cn/~offline/Doc/detsim/

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Generator
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Detsimuserguide
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Detsimuserguide/UsefulCommands
* https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/DisplayMeeting?conferenceid=236
* https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/DisplayMeeting?sessionid=381

cmt introspection
------------------

::

    cd ~/juno-tutorial
    source bashrc 
    cmt show packages 




EOU
}

j-env(){  echo -n ; }
j-dir(){ echo $(dirname $BASH_SOURCE) ; }
j-cd(){  cd $(j-dir) && pwd && git remote -v && git status ; }
j(){ j-cd ; }

j-scp(){  
    local target=${1:-L7} 
    local cmd="scp $(j-dir)/j.bash $target:j/j.bash" 
    echo $cmd
    eval $cmd
}


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

################### INSTALLATION ###################################


j-install-url(){ echo https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation ; }
j-install-open(){ open $(j-install-url) ; }

j-install(){
    :   https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation
    j-install-junotop
    [ $? -ne 0 ] && return 1 
    j-install-junoenv
    [ $? -ne 0 ] && return 2
    j-install-preq 
    [ $? -ne 0 ] && return 3
    j-install-libs 
    [ $? -ne 0 ] && return 4
    j-install-runtime
    [ $? -ne 0 ] && return 5
    j-install-cmtlibs
    [ $? -ne 0 ] && return 6
    j-install-sniper
    [ $? -ne 0 ] && return 7
    j-install-offline
    [ $? -ne 0 ] && return 8
    j-install-offline-data
    [ $? -ne 0 ] && return 9

    j-install-opticks          ## does nothing without pre-requisite envvars
    [ $? -ne 0 ] && return 10

    return 0 
}

j-install-junotop(){ 
    local msg="=== $FUNCNAME :"
    echo $msg JUNOTOP $JUNOTOP 
    [ -z "$JUNOTOP" ] && echo $msg JUNOTOP is not defined && return 1 
    mkdir -p $JUNOTOP ; 
    [ ! -d "$JUNOTOP" ] && echo $msg failed to create JUNOTOP dir && return 2
    return 0 
}
j-install-junoenv(){
    local msg="=== $FUNCNAME :"
    echo $msg 
    cd $JUNOTOP
    if [ -d junoenv ]; then 
        echo junoenv directory already exists 
    else 
        svn co https://juno.ihep.ac.cn/svn/offline/trunk/installation/junoenv
    fi 
    [ ! -d junoenv ] && echo $msg failed to checkout junoenv && return 1 
    return 0
}
j-install-preq(){
    local msg="=== $FUNCNAME :"
    echo $msg 
    cd $JUNOTOP/junoenv
    case $(uname -n) in
     lxslc*) echo $msg assuming preq are satisfied on $(uname -n)  ;;
          *) bash junoenv preq  ;;
    esac
}

j-install-libs-list(){          cd $JUNOTOP/junoenv ; bash junoenv libs list ; }
j-install-libs-all(){           j-install-libs-list | perl -ne 'm, (\S*)@, && print "$1\n"' - ; }
j-install-libs-installed(){     j-install-libs-list | perl -ne 'm, \[x\]\s*(\S*)@, && print "$1\n"' - ; }
j-install-libs-uninstalled(){   j-install-libs-list | perl -ne 'm, \[ \]\s*(\S*)@, && print "$1\n"' - ; }
j-install-lib-deps(){           j-install-libs-list | grep ${1}@ | perl -ne 'm,-\> (.*)$, && print "$1\n"' - ; }

j-install-item-in-list(){
    local item=$1 ; shift 
    local list=$*
    local x 
    for x in $list ; do  [ "$item" == "$x" ] && return 0  ; done
    return 1 
}

j-install-lib-canbuild(){
    : hmm need to accomodate the plus meaning optional perhaps ?
    local lib=$1
    local installed=$(j-install-libs-installed)
    local deps=$(j-install-lib-deps $lib)
    local dep
    for dep in $deps ; do 
        if [ "${dep:0:1}" != "+" ]; then     # skippin the + : is that appropriate 
            j-install-item-in-list $dep $installed 
            [ $? -eq 1 ] && echo $msg missing dependency $dep to build lib $lib && return 1 
        fi 
    done
    return 0 
}

j-install-lib(){
    local msg="=== $FUNCNAME :"
    local lib=$1


    local mkr=$JUNOTOP/junoenv/.j-libs/$lib
    mkdir -p $(dirname $mkr)
    if [ -f "$mkr" ]; then 
        printf "$msg skipping %-20s as mkr exists : $mkr \n" $lib 
    else
        j-install-lib-canbuild $lib
        [ $? -ne 0 ] && echo $msg cannot build lib $lib due to missing dependency && return 1

        bash junoenv libs all $lib 
        [ $? -ne 0 ] && echo $msg ERROR with lib $lib && return 1
        touch $mkr
    fi
}

j-install-libs(){
    local msg="=== $FUNCNAME :"
    echo $msg 
    cd $JUNOTOP/junoenv
    local libs=$(j-install-libs-all)
    for lib in $libs ; do 
        j-install-lib $lib
    done  
    return 0
}    

j-install-runtime-()
{
    local runtime=$JUNOTOP/bashrc.sh
    cd $JUNOTOP/junoenv
    bash junoenv env
    [ ! -s "$runtime" ] && echo $msg failed to create runtime env file $runtime && return 1
    return 0  
}
j-install-runtime()
{
    : setup the runtime environment script JUNOTOP/bashrc.sh 
    local runtime=$JUNOTOP/bashrc.sh
    if [ ! -s "$runtime" ]; then 
        j-install-runtime-
        [ $? -ne 0 ] && return 1 
    fi 
    source $runtime
    return 0 
}

j-install-runtime-resetup()
{
    : create JUNOTOP/bashrc.sh script that sets up the runtime environment usage of the externals
    local msg="=== $FUNCNAME :"

    cd $JUNOTOP/junoenv
    bash junoenv env resetup
    [ $? -ne 0 ] && echo $msg FAIL at env && return 1

    local runtime=$JUNOTOP/bashrc.sh
    source $runtime
}


j-install-cmtlibs()
{
    : building the interface between cmt and external libraries
    : checks out https://juno.ihep.ac.cn/svn/cmtlibs/trunk into $JUNOTOP/ExternalInterface
    :
    : https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation
    :
    : http://juno.ihep.ac.cn/svn/cmtlibs/trunk
    :    EIRelease/
    :    Externals/
    :    cmt/
    :

    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv
    bash junoenv cmtlibs
    [ $? -ne 0 ] && echo $msg failed cmtlibs && return 1 

    cd $JUNOTOP/ExternalInterface/EIRelease/cmt/ && source setup.sh
    [ $? -ne 0 ] && echo $msg failed EIRelease setup && return 2 

    cd $JUNOTOP/junoenv

    return 0 
}

j-install-sniper()
{
    : building the sniper

    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv
    bash junoenv sniper
    [ $? -ne 0 ] && echo $msg failed && return 1 

    cd $JUNOTOP/sniper/SniperRelease/cmt/ && source setup.sh
    [ $? -ne 0 ] && echo $msg failed && return 2

    return 0 
}


j-install-offline()
{
    : building the offline
    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv

    bash junoenv offline
    [ $? -ne 0 ] && echo $msg failed && return 1 

    return 0 
}

j-install-offline-data()
{
    : install offline data to $JUNOTOP/data

    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv

    bash junoenv offline-data
    [ $? -ne 0 ] && echo $msg failed && return 1 

    return 0 
}


j-install-opticks-()
{
    : building the opticks

    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv
    bash junoenv opticks
    [ $? -ne 0 ] && echo $msg failed && return 1 

    return 0 
}

j-install-opticks-envdump()
{
    local vars="OPTICKS_CUDA_PREFIX OPTICKS_OPTIX_PREFIX OPTICKS_COMPUTE_CAPABILITY"
    local var
    for var in $vars ; do printf "%-30s : %s \n" $var ${!var} ; done 
}

j-install-opticks()
{
    local msg="=== $FUNCNAME: "
    if 
        [ -n "$OPTICKS_CUDA_PREFIX" -a -d "$OPTICKS_CUDA_PREFIX" ] &&
        [ -n "$OPTICKS_OPTIX_PREFIX" -a -d "$OPTICKS_OPTIX_PREFIX" ] &&
        [ -n "$OPTICKS_COMPUTE_CAPABILITY" ] 
    then 
        echo $msg environment looks ready to install opticks   
        j-install-opticks-envdump
        j-install-opticks-
    else
        echo $msg environment is not ready to install opticks
        j-install-opticks-envdump
    fi 
}



j-install-issues(){ cat << EOI

EOI
}


#####################  OFFLINE UPDATING ##################

j-offline(){ 
    : building the offline
    cd $JUNOTOP/junoenv
    bash junoenv offline
}

j-opticks(){ 
    : controlling opticks
    cd $JUNOTOP/junoenv
    bash junoenv opticks $* 
}



j-offline-alt(){ 
    : from junoenv-offline.sh:junoenv-offline-compile which is called by "bash junoenv offline"
    cd $JUNOTOP/offline/JunoRelease/cmt
    cmt br cmt config
    source setup.sh
    cmt br cmt make   
}

j-make(){
   cmt br cmt config
   source setup.sh
   #cmt br cmt make 
   cmt make 
}

j-cmtdirs-(){
   : list cmt directories in dependency order without the usual cmt guff
   cd $JUNOTOP/offline/JunoRelease/cmt
   cmt br pwd | grep -v ^#
}
j-cmtdirs(){ 
   : list cmt directories in dependency order with package not found warnings elided 
   j-cmtdirs- 2>/dev/null 
}


################# jok : juno-opticks functions ##################

jok-cmtdirs(){
   : cmtdirs relative to JUNOTOP/offline in JunoRelease dependency order with files that contain WITH_G4OPTICKS

   local cache="$HOME/.jokdirs"
   if [ -f "$cache" ]; then 
       cat $cache
       return 0
   fi 
   local dirs=$(j-cmtdirs)
   local dir
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

jok-cmtdirs-manual(){ cat << EOP
Simulation/DetSimV2/DetSimPolicy/cmt
Simulation/DetSimV2/PhysiSim/cmt
Simulation/DetSimV2/DetSimAlg/cmt
Simulation/DetSimV2/DetSimOptions/cmt
Simulation/DetSimV2/PMTSim/cmt
Simulation/DetSimV2/G4OpticksBridge/cmt
EOP
}

jok-cmtdirs-eg(){ cat << EOX
Simulation/DetSimV2/PhysiSim/cmt
Simulation/DetSimV2/PMTSim/cmt
Simulation/DetSimV2/DetSimOptions/cmt
EOX
}

jok-cc(){
    : list offline .cc WITH_G4OPTICKS
    cd $JUNOTOP/offline
    find . -name '*.cc' -exec grep -l WITH_G4OPTICKS {} \+  
}


jok-rebuild(){
   : in all projects touch sources WITH_G4OPTICKS and rebuild using cmt Makefile

   local msg="=== $FUNCNAME :"
   echo $msg CMTEXTRATAGS : $CMTEXTRATAGS
   [ -z "$JFU_JRE" ] && echo $msg MUST RUN jre BEFORE jokp && return 2

   local dir
   local rel
   echo $msg jok-cmtdirs 
   jok-cmtdirs
   for rel in $(jok-cmtdirs) ; do 
       local dir=$JUNOTOP/offline/$rel
       [ ! -d "$dir" ] && echo $msg ERROR no such dir $dir && return 1
       cd $dir
       pwd
   done

   for rel in $(jok-cmtdirs) ; do 

       local dir=$JUNOTOP/offline/$rel
       [ ! -d "$dir" ] && echo $msg ERROR no such dir $dir && continue
       cd $dir
       printf "\n\n\n ================== $(pwd) ==============\n\n\n" 

       : cmt dependency check doesnt notice CMTEXTRATAGS so must touch to force recompile
       : somehow clean is not working to force recompile

       cmt config
       source setup.sh

       touch $(grep -l WITH_G4OPTICKS ../src/*.cc) 

       #make clean
       make  
       [ $? -ne 0 ] && echo $msg make ERROR && break        
   done
   echo $msg CMTEXTRATAGS : $CMTEXTRATAGS

}

jok-make(){
   local rel 
   while read rel ; do  
       local dir=$JUNOTOP/offline/$rel
       [ ! -d "$dir" ] && echo $msg ERROR no such dir $dir && return 1
       cd $dir
       pwd
       printf "\n\n\n ================== $(pwd) ==============\n\n\n" 


       cmt config
       source setup.sh

       touch $(grep -l WITH_G4OPTICKS ../src/*.cc) 

       #make clean
       make  
       [ $? -ne 0 ] && echo $msg make ERROR && break        
   done
}

jok-dso(){ echo Simulation/DetSimV2/DetSimOptions/cmt | jok-make ; }



################### ENVIRONMENT ###################################

j-g4(){  echo $JUNOTOP/ExternalLibs/Build/geant4.10.04.p02 ; } 
j-okb(){ echo $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge ; }  # not currently used

j-runtime-env-()
{
   : note that CMAKE_PREFIX_PATH and MANPATH keep appending on repeated running but the others dont
   local msg="=== $FUNCNAME: "
   echo $msg
   source $JUNOTOP/bashrc.sh   # sources the bashrc of the JUNOTOP/ExternalLibs
   source $JUNOTOP/sniper/SniperRelease/cmt/setup.sh
   source $JUNOTOP/offline/JunoRelease/cmt/setup.sh
   echo $msg
}

j-runtime-env()
{
   : setup the runtime environment CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, LD_LIBRARY_PATH, PATH, MANPATH
   local msg="=== $FUNCNAME: "
   local var=J_RUNTIME_ENV
   if [ -n "${!var}" ]; then
       echo $msg skip as $var:${!var}
   else 
       export $var=1 
       j-runtime-env-
   fi

}
jre(){ j-runtime-env ; }


j-runtime-env-notes(){ cat << EON

$JUNOTOP/bashrc.sh
    invokes bashrc of all the externals including ~/junotop/ExternalLibs/Opticks/0.1.0/bashrc
    that contains only::

        source ${OPTICKS_TOP}/bin/opticks-setup.sh    

     TODO: avoid errors when have no OPTICKS_TOP

EON
}


################### RUNNING ###################################

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


tds0(){
   : run with opticks disabled
   local opts="--opticks-mode 0 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 10"  
   tds- $opts 
}

tds-elog(){
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
       echo $msg CMTEXTRATAGS $CMTEXTRATAGS contains opticks
       #[ -z "$OPTICKS_TOP" ] && echo $msg OPTICKS_TOP is not defined && return 1
   fi

   [ -z "$J_RUNTIME_ENV" ]  && echo $msg MUST RUN jre BEFORE tds && return 2 

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
   local dir=/tmp/$USER/opticks/tds
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

tds5-(){ cat << EOB
junoSD_PMT_v2::junoSD_PMT_v2
junoSD_PMT_v2::Initialize
junoSD_PMT_v2::ProcessHits
junoSD_PMT_v2::get_pmtid
junoSD_PMT_v2::EndOfEvent
EOB
}
tds5(){ BP="$(tds5-)" tds ; }


###########################################################################################

[ "$DBG" == "1" ] && dbg_tail $BASH_SOURCE
