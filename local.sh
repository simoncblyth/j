#!/bin/bash

local_usage(){ cat << EOU
.bash_profile > .bashrc > local.sh : local_usage
==================================================

local.sh provides env + build + test bash functions developed on "A" (Ada GPU workstation).
Only minimal test/debug functions like "ljrt" are here.
Most test functions have been moved to the OJ repository, see ~/oj/oj.bash


Motivation for these OJ bash functions
---------------------------------------

The ~/j/local.sh local_oj bash functions follow the general approach
of ~/junosw/.gitlab-ci.yml and uses some of the same machinery
like ~/junosw/.gitlab-ci/oj_helper.sh to come close to replicating
the ci build locally.

The point of this is to allow developing the OJ machinery locally
with a faster development cycle than making lots of test MR
to the junosw gitlab instance.


OK : Opticks building functions
----------------------------------

+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| cmd     | primary functions                  |  notes                                                                                                                                 |
+=========+====================================+========================================================================================================================================+
| lob     | local_ok_build                     | env to build Opticks against JUNOSW externals manually setup from cvmfs : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy   |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| lo      | local_ok_build,lco                 | env to build Opticks (see lob) + python test and analysis using conda                                                                  |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
|         | local_ok_local                     | env to use local Opticks release, little used as typically need to keep rebuilding which requires "lob" or "lo"                        |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+


OJ : JUNOSW+Opticks building functions
---------------------------------------

+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| cmd     | primary functions                  |  notes                                                                                                                                 |
+=========+====================================+========================================================================================================================================+
| ljb     | local_oj_build                     | defines oj_build which locally mimics the Opticks+JUNOSW gitlab-ci build                                                               |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| ljbb    | local_oj_build,oj_build            | defines oj_build and runs it : update builds JUNOSW with ~/opticks                                                                     |
|         |                                    | [NORMALLY WOULD REBUILD OPTICKS BEFORE DOING THIS]                                                                                     |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| ljbb0   | local_oj_build,oj_build            | same as ljbb but with NOINIT=1 to disable geometry initialization                                                                      |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| ljbb0c  | local_oj_build,oj_build            | same as ljbb but with NOINIT=1 OJ_BUILD_CLEAN=1 to disable geometry initialization and do clean build                                  |
|         |                                    | [CLEAN BUILDS ARE NEEDED AFTER CHANGING EXTERNAL VERSIONS]                                                                             |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| ljbbc   | local_oj_build,oj_build            | same as ljbb but with OJ_BUILD_CLEAN=1 to do clean build                                                                               |
|         |                                    | [CLEAN BUILDS ARE NEEDED AFTER CHANGING EXTERNAL VERSIONS]                                                                             |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| loj     | local_oj                           | env to use local OJ                                                                                                                    |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| lji     | local_oj_init                      | [NOT COMMONLY USED, AS NOW PART OF ljb] defines oj_init which does test geometry conversions populating the geomdir                    |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| ljii    | local_oj_init,oj_init              | [NOT COMMONLY USED, AS NOW PART OF ljb] defines oj_init and runs it                                                                    |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| ljr     | local_oj_release,oj_release        | env to use OJ release (eg using libs scripts and geomdir from /cvmfs )                                                                 |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| lco     | local_conda_ok,conda_ok,activate   | local_conda_ok defines conda_ok, running that which sets up conda, then the ok conda env is activated                                  |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+


ljclient function : builds OJ against an OpticksClient installation
---------------------------------------------------------------------

Usage examples::

    ljclient ljbbc    # clean build, with geom init   -- FULL ENCHILADA
    ljclient ljbb0c   # clean build, no geom init
    ljclient ljbb     # update build, with geom init
    ljclient ljbb0    # update build, no geom init    -- QUICKEST


    JUNO_OPTICKS_CONFIG=Client ljbb  ## equivalent to the ljbb line above



NB when changing the version of an external, a clean build is required

ljclient invokes the function whose name is passed in the argument after setting::

   export JUNO_OPTICKS_CONFIG=Client


Q: How/where does JUNO_OPTICKS_CONFIG change things ?

A: In JUNOSW/oj_initialize.sh when JUNO_OFFLINE_BUILD_BRANCH is defined the JUNO_OPTICKS_CONFIG
   setting causes the reldir picking the envset.sh to be prefixed with the config string eg "Client_"
   prior to the branch name.

   JUNO_OPTICKS_CONFIG is thus fundamental, it controls which installations to use,
   by picking the envset.sh which sets the prefixes of OJ and Opticks.





Updating local OK build
------------------------

After making changes in ~/opticks update OK with:

1. open new tab with empty env and get into env and build::

    local_ok_build   ## "lob" OR "lo" which does conda setup too
    oo
    opticks-t


Updating local OJ build (equivalent of gitlab CI OJ build) : ljbb
--------------------------------------------------------------------

After making changes in ~/junosw eg to Examples/Tutorial/share/opticks_juno.sh
update OJ with:

* open new tab with empty env and setup and invoke the OJ build::

    local_oj_build # ljb
    oj_build
    ## alternatively use "ljbb" to do both the above


Initialize geomdir (equivalent of gitlab CI OJ test) : ljii
--------------------------------------------------------------

* open new tab with empty env and setup and invoke the OJ Opticks geom config::

    local_oj_init # lji
    oj_init
    ## alternatively use "ljii" to do both the above

EOU
}

local_c4_branch_notes(){ cat << EON

ABOUT C4 BRANCHES
=================

Caution c4 repo is in a delicate branch situation, see ~/j/custom4/review_status.rst

v0.1.8
   old branch that has been in use for years : and includes the mistake
   of using templated track info that breaks interop opticksMode:0 (and 3)

v0.1.8_transient
    some fixes on top of the old v0.1.8 - mainly avoiding the templated track info mistake

v0.1.9_release
    2026 March attempt to combine v0.1.8_transient with cherry picked commits from main

main
    angular qe implementation changes not ready for release,
    as well as infrastructure updates that have been cherry-picked into v0.1.9_release


EON
}

local_c4_build_notes(){ cat << EON
BUILD ORDER WHEN CHANGING CUSTOM4 VERSION : C4, OK, OJ
-------------------------------------------------------

Check C4 branch::

    cd ~/customgeant4
    git status  # check are on the 0.1.8_transient branch



NB do not want to make major changes in the transient branch, as may be
problematic to get into main. But changing debug output is acceptable.

Actually, when using default v0.1.8 Custom4 prefix there is nothing to do


Do each of the below setup and build in separate clean tabs:

1. local_c4_build ; c4_build   ## does nothing when using default c4 v0.1.8

   * NB whatever customgeant4 branch the repo is at is what gets built
   * HMM: IT WOULD BE BETTER FOR THE BRANCH TO FEED INTO THE BUILD
   * current_branch=$(git -C $HOME/customgeant4 branch --show-current)
   * v0.1.9_release

2. local_ok_build ; ok_build

Normally the above is sufficient to build. But after changing the C4 prefix
an om-cleaninstall is needed::

    o
    om-cleaninstall
    opticks-t

* CAUTION : IN THIS STATE OF DEPENDING ON A LOCAL EXTERNAL CUSTOM4 CANNOT MAKE
  A VALID DISTRIBUTION : AS DISTRIBUTIONS NEED TO DEPEND ON EXTERNALS FROM CVMFS

There is a check for this already::

    (ok) A[blyth@localhost opticks]$ okdist--
    NON-STANDARD: /data1/blyth/local/custom4_Debug/0.1.9
    /home/blyth/opticks/bin/okdist.bash : ABORT AS om-cmake-prefix-path-check SHOWS THAT CMAKE_PREFIX_PATH CONTAINS NON-DISTRIBUTABLE PATHS



3. local_oj_build ; NOINIT=1 OJ_BUILD_CLEAN=1 oj_build

Function for that clean build without init is (initially NOINIT as the build may fail)::

    ljbb0c

Once build succeeds do init too with::

    ljbb


EON
}



local_vip()
{
   : ~/j/local.sh
   case ${VIP_MODE:-none} in
          none) local_none ;;

  ok_externals) local_ok_externals ;;
      ok_build) local_ok_build ;;
      ok_local) local_ok_local ;;

      oj_build) local_oj_build ;;
      oj_init)  local_oj_init ;;

    oj_release) local_oj_release ;;

         conda) local_conda ;;
      conda_ok) local_conda_ok ;;

             *) local_unhandled ;;
   esac
}


local_unset()
{
   : ~/j/local.sh
   unset CMAKE_PREFIX_PATH
   unset PKG_CONFIG_PATH
}

local_none()
{
   : ~/j/local.sh
   export VIP_MODE=none
   export VIP_DESC="empty env"
}


local_c4_prefix_default()
{
    : default path from cvmfs
    #echo /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8
    echo /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/custom4/0.1.8
}
local_c4_prefix()
{
    : function that enables switching to a non default c4 to check
    : SEE NOTES AT HEAD ABOUT THE ORDER OF BUILD OPERATIONS WHEN CHANGING C4 PREFIX

    #echo $(local_c4_prefix_default)
    #echo /data1/blyth/local/custom4_Debug/0.1.8
    echo /data1/blyth/local/custom4_Debug/0.1.9
}


local_c4_build_notes(){ cat << EON

* sources c4 dependencies (Xercesc, CLHEP, Geant4) from cvmfs - assumed to be same versions as those used by JUNOSW and Opticks
* if local_c4_prefix is the default 0.1.8 from cvmfs then c4_build is a no-build placeholder
* if local_c4_prefix is not the default then c4_build uses that prefix with ~/customgeant4/build_Debug.sh


EON
}


local_c4_build()
{
   : ~/j/local.sh
   : setup externals needed to c4_build
   : using J25.4.0 standard versions of externals copied from JUNOTOP/bashrc.sh
   : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/bashrc.sh

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Xercesc/3.2.4/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/CLHEP/2.4.7.1/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/bashrc

   if [ "$(local_c4_prefix)" == "$(local_c4_prefix_default)" ]; then
       c4_build()
       {
          : ~/j/local.sh
          echo $BASH_SOURCE $FUNCNAME - NO BUILD NEEDED AS PREFIX IS DEFAULT
          local ff="local_c4_prefix local_c4_prefix_default"
          for f in $ff ; do printf "%30s : %s\n" "$f" $(eval $f) ; done
       }
   else
       c4_build()
       {
          : ~/j/local.sh

          echo $BASH_SOURCE $FUNCNAME - BUILD NEEDED AS PREFIX IS NOT DEFAULT
          local ff="local_c4_prefix local_c4_prefix_default"
          for f in $ff ; do printf "%30s : %s\n" "$f" $(eval $f) ; done

          cd $HOME/customgeant4
          export CUSTOM4_PREFIX=$(local_c4_prefix)
          ./build_Debug.sh

          # source ~/j/JUNOTOP/JUNOTOP_generate_custom4_bashrc.sh
          # JUNOTOP_generate_custom4_bashrc > ${CUSTOM4_PREFIX}/bashrc
          # FROM 0.1.9 THIS IS DONE BY THE custom4 build.sh
       }
   fi
   type c4_build
}


local_ok_externals_notes(){ cat << EON

local_ok_externals is invoked by::

    lob < local_ok_build
    lo  < local_ok_build


EON
}

local_ok_externals()
{
   : ~/j/local.sh
   : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy versions matching JUNOSW
   : NB versions need to match those used by gitlab-ci build when using the gitlab cvmfs release

   local_unset

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Python/3.11.10/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/python-numpy/1.26.4/bashrc

   local_c4_build  # setup c4 externals : Xercesc + CLHEP + Geant4
   source $(local_c4_prefix)/bashrc

   export VIP_MODE=ok_externals
   export VIP_DESC="Opticks JUNOSW externals in common manually setup from cvmfs : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy"
   PS1_LABEL=$FUNCNAME  # do last to override other funcs that set the label
}


local_JUNOTOP_override()
{

   : change PATH LD_LIBRARY_PATH PKG_CONFIG_PATH CPATH MANPATH CMAKE_PREFIX_PATH
   : in order to use different prefix of an external

   source ~/j/JUNOTOP/JUNOTOP_change_paths.sh
   JUNOTOP_change_paths custom4 $(local_c4_prefix) $(local_c4_prefix_default)

   : HMM when building JUNOSW against different Custom4 will need to
   : also build Opticks against that same Custom4 FIRST
}


local_cuda()
{
    : ~/j/local.sh using vip-path from ~/vip/vip.bash
    local cuda_prefix=/usr/local/cuda-12.4
    vip-path append PATH            $cuda_prefix/bin  # for nvcc
    vip-path append LD_LIBRARY_PATH $cuda_prefix/lib64
}



local_ok_build()
{
   : ~/j/local.sh
   : ~/.opticks_config which sets OPTICKS_CONFIG was formerly sourced after local_ok_externals
   : BUT now with the Client config which changes the required externals
   : the ordering is switched

   source ~/.opticks_config  # CUDA OptiX COMPUTE_CAPABILITY ARCHITECTURES

   local_ok_externals  # Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy


   om-
   export VIP_MODE=ok_build
   export VIP_DESC="env to build Opticks against JUNOSW externals manually setup from cvmfs : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy"


   ok_build()
   {
       cd ~/opticks
       #om-clean
       #om-conf
       om
   }
   type ok_build

  :  noticed that need to  om- to get setup
}
lob()
{
   : ~/j/local.sh
   local_ok_build
   export OPTICKS_ENVNOTE=$BASH_SOURCE:$FUNCNAME
   PS1_LABEL=$FUNCNAME  # do last to override other funcs that set the label
}

lo()
{
   : ~/j/local.sh  env for Opticks build test and analysis
   local_ok_build
   #lco   ## THIS BRINGS IN CONDA : WHICH IS NOW CURL COMPLICATED

   export GEOMBASE=$(local_srcdir)/InstallArea/$(local_reldir)/.opticks/GEOM   ## liteweight for GEOM bash function navigation eg "GEOM cf"
   export OPTICKS_ENVNOTE=$BASH_SOURCE:$FUNCNAME
   PS1_LABEL=$FUNCNAME  # do last to override other funcs that set the label
}

lo_client ()
{
   export OPTICKS_CONFIG=Client
   export OPTICKS_MODE_CLIENT=1  # controls type of simulator created by G4CXOpticks::CreateSimulator

   lo   #  local_ok_build/local_ok_externals
   export OPTICKS_ENVNOTE=$BASH_SOURCE:$FUNCNAME
   PS1_LABEL=$FUNCNAME  # do last to override other funcs that set the label
}


local_ok_local()
{
   : ~/j/local.sh
   local_ok_externals    # Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy

   source /data1/blyth/local/opticks_Debug/bashrc   ## HMM: FIXED OPTICKS_PREFIX assumption

   export VIP_MODE=ok_local
   export VIP_DESC="pure Opticks usage from OPTICKS_PREFIX $OPTICKS_PREFIX"
}







ljb()
{
   : ~/j/local.sh
   : use this in fresh tab to setup env ready to perform oj_build
   local_oj_build
}
ljbb()
{
   : ~/j/local.sh
   : use this in fresh tab to setup env and perform the build
   [ -z "$CMD" ] && export CMD=$FUNCNAME  ## capture top level command for logging
   local_oj_build
   oj_build
}


ljclient()
{
   : see notes above
   local fn=${1:-ljbb}

   if [[ "$fn" =~ ljbb|ljbb0|ljbb0c|ljbbc ]]; then
       export JUNO_OPTICKS_CONFIG=Client
       echo $BASH_SOURCE $FUNCNAME running fn $fn with JUNO_OPTICKS_CONFIG $JUNO_OPTICKS_CONFIG
       $fn
   else
       echo $BASH_SOURCE $FUNCNAME running fn $fn - NOT SUPPORTED
       return 1
   fi

}

ljbb0()
{
   : ~/j/local.sh
   : same as ljbb but using NOINIT=1 which prevents geometry initialization
   [ -z "$CMD" ] && export CMD=$FUNCNAME  ## capture top level command for logging
   NOINIT=1 ljbb
}

ljbb0c()
{
   : ~/j/local.sh
   : same as ljbb but using NOINIT=1 which prevents geometry initialization
   : and OJ_BUILD_CLEAN=1 which deletes the build dirs and redoes everything
   [ -z "$CMD" ] && export CMD=$FUNCNAME  ## capture top level command for logging
   NOINIT=1 OJ_BUILD_CLEAN=1 ljbb
}

ljbbc()
{
   : ~/j/local.sh
   : same as ljbb but with OJ_BUILD_CLEAN=1 which deletes the build dirs and redoes everything
   [ -z "$CMD" ] && export CMD=$FUNCNAME  ## capture top level command for logging
   OJ_BUILD_CLEAN=1 ljbb
}


oj_log()
{
    : ~/j/local.sh
    : logfile LOGSTEM.log in invoking directory is appended to
    : LOGSTEM should be the name of the principal bash function eg oj_build_
    local logstem=$1
    shift
    local stamp=$(date +"%Y-%m-%d %H:%M:%S")
    printf "$stamp $*\n" >> $logstem.log
}

local_srcdir(){ echo $HOME/junosw ; }
local_branch(){ git -C $(local_srcdir) branch --show-current ; }
local_reldir()
{
    : ~/j/local.sh
    : local_reldir generalizes local_branch to distinguish building against different JUNO_OPTICKS_CONFIG like Client
    local branch=$(local_branch)
    local reldir
    if [ -n "$JUNO_OPTICKS_CONFIG" -a "$JUNO_OPTICKS_CONFIG" != "Debug" ]; then
        reldir=${JUNO_OPTICKS_CONFIG}_$branch
    else
        reldir=$branch
    fi
    echo $reldir
}


local_seconds_between() {
    : ~/j/local.sh
    : convert d1 d2 string arguments into seconds from the epoch
    : then subtract to give seconds between those
    local d1="$1"
    local d2="$2"
    local ts1=$(date -d "$d1" +%s) || return 1
    local ts2=$(date -d "$d2" +%s) || return 1
    echo $(( ts2 - ts1 ))
}

local_client_setup_no_longer_needed()
{
    : now does nothing following NP_CURL.h additions to work with libcurl 7.76.1
    : see ~/opticks/externals/openssl.bash
    : see ~/opticks/externals/libcurl.bash
    : used from local_oj_release and local_ok_externals

    #source /usr/local/ExternalLibs/openssl/openssl-3.2.0/bashrc
    #source /usr/local/ExternalLibs/libcurl/curl-8.12.1/bashrc

    echo -n
}


local_oj_build()
{
   : ~/j/local.sh
   export VIP_MODE=oj_build
   export VIP_DESC="local OJ build adapting .gitlab-ci.yml Opticks+JUNOSW build, see oj_build func"


   : JUNOTOP defines the versions of externals used by both JUNOSW
   : Opticks grabs the same versions of those externals it needs
   :
   : 2025/06/04
   :    JLatest symbolic link no longer latest - currently J25.3.0
   :    so follow .gitlab-ci.yml and change the below JUNOTOP to J25.4.0

   export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
   #export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0
   source $JUNOTOP/setup.sh

   : sourcing of JUNOTOP/setup.sh leads to sourcing of JUNOTOP/bashrc.sh
   : which results in the sourcing of around 40 bashrc like ExternalLibs/name/name-version/bashrc

   local_JUNOTOP_override  ## potentially changing paths to build against different custom4

   local BASE=/data1/blyth/local

   local juno_opticks_config=Debug
   export JUNO_OPTICKS_CONFIG=${JUNO_OPTICKS_CONFIG:-$juno_opticks_config}

   : JUNO_OPTICKS_CONFIG is input which controls which JUNO_OPTICKS_PREFIX to build against
   unset JUNO_OPTICKS_PREFIX
   case $JUNO_OPTICKS_CONFIG in
     vLatest) export JUNO_OPTICKS_PREFIX=/cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest ;;
       Debug) export JUNO_OPTICKS_PREFIX=$BASE/opticks_${JUNO_OPTICKS_CONFIG}  ;;
      Client) export JUNO_OPTICKS_PREFIX=$BASE/opticks_${JUNO_OPTICKS_CONFIG}  ;;
     Release) export JUNO_OPTICKS_PREFIX=$BASE/opticks_${JUNO_OPTICKS_CONFIG}  ;;
   esac
   : NB JUNO_OPTICKS_PREFIX is only used in this function and in the .gitlab-ci.yml and associated helper scripts


   if [ -z "$JUNO_OPTICKS_PREFIX" ]; then
       echo $BASH_SOURCE $FUNCNAME - FATAL - UNDEF JUNO_OPTICKS_PREFIX $JUNO_OPTICKS_PREFIX - JUNO_OPTICKS_CONFIG $JUNO_OPTICKS_CONFIG
       return 1
   fi

   if [ ! -d "$JUNO_OPTICKS_PREFIX" ]; then
       echo $BASH_SOURCE $FUNCNAME - FATAL - NON EXISTING JUNO_OPTICKS_PREFIX $JUNO_OPTICKS_PREFIX BASE $BASE
       return 1
   fi



   : WIP: want to build agaist here built ok external rather than the cvmfs release
   : HMM : despite the prefix change still building against the cvmfs release of opticks
   : try ./build_Debug.sh after nuclear removal of build InstallConfig and InstallArea

   export JUNO_OFFLINE_OFF=1
   export OPTICKS_SETUP_VERBOSE=1
   export JUNO_OFFLINE_BUILD_BRANCH=1  # suffix operating directories with the branch eg: InstallArea/main build/main

   # prior to https://code.ihep.ac.cn/JUNO/offline/junosw/-/tree/blyth-add-optional-branch-name-after-InstallArea-and-build-dirs-plus-ci-JUNOTOP-to-JLatest


   PREFIX_RELDIR_WITH_JUNO_OPTICKS_CONFIG=1
   if [ "$JUNO_OFFLINE_BUILD_BRANCH" == "1" -a -n "$PREFIX_RELDIR_WITH_JUNO_OPTICKS_CONFIG" ]; then
       SOURCE_DIR=$HOME/junosw

       ## HMM: duplication with local_reldir ???
       BRANCH=$(git -C $SOURCE_DIR branch --show-current)
       if [ "$JUNO_OPTICKS_CONFIG" == "Debug" ]; then
           RELDIR=$BRANCH
       else
           RELDIR=${JUNO_OPTICKS_CONFIG}_${BRANCH}
       fi

       export JUNO_OFFLINE_RELDIR=$RELDIR   # SCB invention
       export JUNO_OFFLINE_BLDDIR=$SOURCE_DIR/build/$JUNO_OFFLINE_RELDIR
       export JUNO_OFFLINE_INSTALLDIR=$SOURCE_DIR/InstallArea/$JUNO_OFFLINE_RELDIR
       mkdir -p $JUNO_OFFLINE_BLDDIR
       mkdir -p $JUNO_OFFLINE_INSTALLDIR

       echo $BASH_SOURCE : PREFIX_RELDIR_WITH_JUNO_OPTICKS_CONFIG $PREFIX_RELDIR_WITH_JUNO_OPTICKS_CONFIG
       echo $BASH_SOURCE : JUNO_OPTICKS_CONFIG                    $JUNO_OPTICKS_CONFIG
       echo $BASH_SOURCE : JUNO_OFFLINE_RELDIR                    $JUNO_OFFLINE_RELDIR
       echo $BASH_SOURCE : JUNO_OFFLINE_BLDDIR                    $JUNO_OFFLINE_BLDDIR
       echo $BASH_SOURCE : JUNO_OFFLINE_INSTALLDIR                $JUNO_OFFLINE_INSTALLDIR

   fi


   export SPMT__init_pmtNum_FAKE_WHEN_MISSING=1  # transient backward compat for junosw branches without pmtNum


   if [ -n "$JUNO_OPTICKS_PREFIX" ]; then
       source $JUNO_OPTICKS_PREFIX/bashrc
       : here OPTICKS_PREFIX OPTICKS_CONFIG are defined and paths are appended
   fi

   oj_build_info(){
       : ~/j/local.sh
       local vv="JUNOTOP JUNO_OPTICKS_PREFIX JUNO_OFFLINE_OFF OPTICKS_SETUP_VERBOSE OPTICKS_PREFIX OPTICKS_CONFIG"
       for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done
   }

   oj_build_clean()
   {
      : when changing externals need nuclear rebuild

      cd $(local_srcdir)
      local reldir=$(local_reldir)

      if [ -n "$JUNO_OFFLINE_BUILD_BRANCH" ]; then
          rm -rf InstallArea/$reldir
          rm -rf build/$reldir
      else
          rm -rf InstallArea
          rm -rf build
      fi
      rm -rf InstallConfig
   }

   oj_build_pre(){
       : ~/j/local.sh this is invoked by oj_build
       cd $(local_srcdir)
       source .gitlab-ci/oj_helper.sh EMIT_ENV_CHECK
       mkdir -p InstallConfig
       source .gitlab-ci/oj_helper.sh EMIT_ENV    > InstallConfig/ENV.bash
       source .gitlab-ci/oj_helper.sh EMIT_ENVSET > InstallConfig/envset.sh
       ## HMM: should InstallConfig use reldir too ?
   }

   oj_build_(){
       : ~/j/local.sh this is invoked by oj_build
       cd $(local_srcdir)

       ##rm -f $FUNCNAME.log  ## retaining log to follow progression of build time is useful
       oj_log $FUNCNAME START $CMD

       ./build_Debug.sh ;

       [ $? -ne 0 ] && echo $FUNCNAME ERROR DURING BUILD && return 1

       oj_log $FUNCNAME FINISH $CMD
       return 0
   }

   oj_build_post(){
       : ~/j/local.sh this is invoked by oj_build
       cd $(local_srcdir)
       local reldir=$(local_reldir)

      if [ -n "$JUNO_OFFLINE_BUILD_BRANCH" ]; then
           cp InstallConfig/ENV.bash  InstallArea/$reldir/ENV.bash
           cp InstallConfig/envset.sh InstallArea/$reldir/envset.sh
      else
           cp InstallConfig/ENV.bash  InstallArea/ENV.bash
           cp InstallConfig/envset.sh InstallArea/envset.sh
      fi
   }

   oj_build_initialize(){
       : ~/j/local.sh
       : needs to be run once only to prepare the geometry inputs configuring tesselation solids and framespec

       cd $(local_srcdir)
       ./oj_initialize.sh
   }

   oj_build(){
       : ~/j/local.sh

       local vv=""
       local d0=$(date)
       vv="$vv d0"

       [ -n "$OJ_BUILD_CLEAN" ] && oj_build_clean
       oj_build_info
       oj_build_pre
       oj_build_
       [ $? -ne 0 ] && echo $FUNCNAME ERROR DURING BUILD - EXITING && return 1

       local d1=$(date)
       local s1=$(local_seconds_between "$d0" "$d1")
       vv="$vv d1 s1"
       for v in $vv ; do printf "%30s : %s \n" "$v" "${!v}" ; done

       oj_build_post
       [ -z "$NOINIT" ] && oj_build_initialize

       local d2=$(date)
       local s2=$(local_seconds_between "$d1" "$d2")
       vv="$vv d2 s2"
       for v in $vv ; do printf "%30s : %s \n" "$v" "${!v}" ; done

       return 0
   }

   type oj_build
}



local_oj_info(){ cat << EOI

    local_srcdir   : $(local_srcdir)
    local_reldir   : $(local_reldir)
    envset         : $(local_srcdir)/InstallArea/$(local_reldir)/envset.sh

EOI

: JUNO_OPTICKS_CONFIG=Client local_oj_info

}

local_oj()
{
    source $(local_srcdir)/InstallArea/$(local_reldir)/envset.sh
}
loj(){
   : ~/j/local.sh
   : setup environment of OJ running
   local_oj
}

lji()
{
   : ~/j/local.sh
   : setup environment to prepare geomdir with oj_init
   local_oj_init
}

ljii()
{
   : ~/j/local.sh
   : setup environment to prepare geomdir and then invoke oj_local doing so
   local_oj_init
   oj_init
}


local_oj_init()
{
   : ~/j/local.sh
   : THIS IS NOW NORMALLY DONE AS PART OF oj_build
   local desc="usage of oj_build created envset.sh adapting .gitlab-ci.yml Opticks+JUNOSW test, use oj_local func to prep geomdir"
   local mode=oj_init

   export VIP_MODE="${VIP_MODE},$mode"
   export VIP_DESC="${VIP_DESC},$desc"
   export VIP_FUNC="${VIP_FUNC},$FUNCNAME"

   oj_init(){
       : follow .gitlab-ci.yml
       : needs to be run once only to prepare the geometry inputs configuring tesselation solids and framespec

       cd $(local_srcdir)
       ./oj_initialize.sh
   }
   type oj_init
}




oj_envset_notes(){ cat << EON
oj_envset_notes
===============

0. change release via Opticks "ENVSET" bash function

Example commandlines for quick tests of release::

    ojet
    BP=SEvt::addGenstep SProf__WRITE=1 U4=INFO ojet

    TEST=hit2 ojet


EON
}

oj_envset()
{
   : ~/j/local.sh
   source ~/.opticks/GEOM/ENVSET.sh
   echo $BASH_SOURCE - ENVSET_NAME $ENVSET_NAME ENVSET $ENVSET

   if [ -n "$ENVSET" -a -f "$ENVSET" ]; then
       source $ENVSET
   else
       echo $BASH_SOURCE - ERROR MISSING ENVSET $ENVSET
       return 1
   fi
   return 0
}



seconds_between() {
    local d1="$1"
    local d2="$2"
    local ts1=$(date -d "$d1" +%s) || return 1
    local ts2=$(date -d "$d2" +%s) || return 1
    echo $(( ts2 - ts1 ))
}


local_oj_release()
{
   : ~/j/local.sh
   local desc="TODO: cvmfs release"
   local mode=oj_release

   export VIP_MODE="${VIP_MODE},$mode"
   export VIP_DESC="${VIP_DESC},$desc"
   export VIP_FUNC="${VIP_FUNC},$FUNCNAME"

   oj_release()
   {
       : ~/j/local.sh

       source ~/.opticks/GEOM/ENVSET.sh
       if [ -n "$ENVSET" -a -f "$ENVSET" ]; then
           source $ENVSET
       else
           echo $BASH_SOURCE - ERROR - MISSING ENVSET $ENVSET
       fi
   }

   oj_release_test()
   {
       : ~/local.sh
       source dbg__.sh

       local evtmax=1
       local EVTMAX=${EVTMAX:-$evtmax}
       echo $BASH_SOURCE $FUNCNAME EVTMAX $EVTMAX evtmax $evtmax
       dbg__ \
          $(which python) \
          $(which tut_detsim.py) \
          --evtmax $EVTMAX \
          gun
   }
}

ljr()
{
   : ~/j/local.sh
   : setup environment to check a release
   local_oj_release
   oj_release
}

ljrt()
{
   : ~/j/local.sh
   : setup environment to check a release
   local_oj_release
   oj_release
   oj_release_test
}





local_conda_base()
{
   : ~/local.sh
   local desc="conda with the ok analysis environment activated including matplotlib and pyvista"
   local mode=conda_ok

   export VIP_MODE="${VIP_MODE},$mode"
   export VIP_DESC="${VIP_DESC},$desc"
   export VIP_FUNC="${VIP_FUNC},$FUNCNAME"

   conda_base()
   {
       : ~/local.sh
       : below was appended by running : conda init --all
       __conda_setup="$('/home/blyth/miniconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
       if [ $? -eq 0 ]; then
           eval "$__conda_setup"
       else
           if [ -f "/home/blyth/miniconda3/etc/profile.d/conda.sh" ]; then
               . "/home/blyth/miniconda3/etc/profile.d/conda.sh"
           else
               export PATH="/home/blyth/miniconda3/bin:$PATH"
           fi
       fi
       unset __conda_setup
   }
}

lco()
{
   : ~/local.sh
   local_conda_base
   conda_base
   conda activate ok
}


local_unhandled()
{
   : ~/local.sh
   echo $BASH_SOURCE - ERROR VIP_MODE $VIP_MODE is UNHANDLED
}


