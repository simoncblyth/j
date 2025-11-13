#!/bin/bash

local_usage(){ cat << EOU
.bash_profile > .bashrc > local.sh : local_usage
==================================================

local.sh is the environment control script developed on Ada workstation (A).

summary of functions
----------------------

+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| cmd     | primary functions                  |  notes                                                                                                                                 |
+=========+====================================+========================================================================================================================================+
| lob     | local_ok_build                     | env to build Opticks against JUNOSW externals manually setup from cvmfs : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy   |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| lo      | local_ok_build,lco                 | env to build Opticks (see lob) + python test and analysis using conda                                                                  |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
|         | local_ok_local                     | env to use local Opticks release, little used as typically need to keep rebuilding which requires "lob" or "lo"                        |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| ljb     | local_oj_build                     | defines oj_build which locally mimics the Opticks+JUNOSW gitlab-ci build                                                               |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| ljbb    | local_oj_build,oj_build            | defines oj_build and runs it : update builds JUNOSW with ~/opticks                                                                     |
|         |                                    | [NORMALLY WOULD REBUILD OPTICKS BEFORE DOING THIS]                                                                                     |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+
| ljbb0   | local_oj_build,oj_build            | same as ljbb but with NOINIT=1 to disable geometry initialization                                                                      |
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
| ojet    | oj_envset,oj_envset_test           | quick dbg__ tests of the release configured via Opticks ENVSET bash function                                                           |
+---------+------------------------------------+----------------------------------------------------------------------------------------------------------------------------------------+


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



BUILD ORDER WHEN CHANGING CUSTOM4 VERSION : C4, OK, OJ
-------------------------------------------------------


Check C4 branch::

    cd ~/customgeant4
    git status  # check are on the 0.1.8_transient branch

NB do not want to make major changes in the transient branch, as may be
problematic to get into main. But changing debug output is acceptable.


Do each of the below setup and build in separate clean tabs:

1. local_c4_build ; c4_build   ## does nothing when using default c4
2. local_ok_build ; ok_build
3. local_oj_build ; oj_build
4. local_oj_init  ; oj_init


EOU
}



local_vip()
{
   : ~/local.sh
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
   : ~/local.sh
   unset CMAKE_PREFIX_PATH
   unset PKG_CONFIG_PATH
}

local_none()
{
   : ~/local.sh
   export VIP_MODE=none
   export VIP_DESC="empty env"
}


local_c4_prefix_default()
{
    echo /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8
}
local_c4_prefix()
{
    echo $(local_c4_prefix_default)
    #echo /data1/blyth/local/custom4_Debug/0.1.8
}


local_c4_build()
{
   : ~/local.sh
   : setup externals needed to c4_build
   : using J25.4.0 standard versions of externals copied from JUNOTOP/bashrc.sh
   : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/bashrc.sh

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Xercesc/3.2.4/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/CLHEP/2.4.7.1/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/bashrc

   if [ "$(local_c4_prefix)" == "$(local_c4_prefix_default)" ]; then
       c4_build()
       {
          : ~/local.sh
          echo $BASH_SOURCE $FUNCNAME - NO BUILD NEEDED AS PREFIX IS DEFAULT
          local ff="local_c4_prefix local_c4_prefix_default"
          for f in $ff ; do printf "%30s : %s\n" "$f" $(eval $f) ; done
       }
   else
       c4_build()
       {
          : ~/local.sh

          : NB returned v0.1.8 in transient branch with
          :
          :      git checkout -b v0.1.8_transient v0.1.8
          :


          echo $BASH_SOURCE $FUNCNAME - BUILD NEEDED AS PREFIX IS NOT DEFAULT
          local ff="local_c4_prefix local_c4_prefix_default"
          for f in $ff ; do printf "%30s : %s\n" "$f" $(eval $f) ; done

          cd $HOME/customgeant4
          export CUSTOM4_PREFIX=$(local_c4_prefix)
          ./build_Debug.sh

          source ~/j/JUNOTOP/JUNOTOP_generate_custom4_bashrc.sh
          JUNOTOP_generate_custom4_bashrc > ${CUSTOM4_PREFIX}/bashrc
       }

   fi
   type c4_build
}

local_ok_externals()
{
   : ~/local.sh
   : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy versions matching JUNOSW
   : NB versions need to match those used by gitlab-ci build when using the gitlab cvmfs release

   local_unset

   local_c4_build  # setup c4 externals
   source $(local_c4_prefix)/bashrc

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Python/3.11.10/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/python-numpy/1.26.4/bashrc

   export VIP_MODE=ok_externals
   export VIP_DESC="Opticks JUNOSW externals in common manually setup from cvmfs : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy"
}


local_JUNOTOP_override()
{

   : change PATH LD_LIBRARY_PATH PKG_CONFIG_PATH CPATH MANPATH CMAKE_PREFIX_PATH
   : in order to use different prefix of an external

   source ~/j/JUNOTOP/JUNOTOP_change_paths.sh
   JUNOTOP_change_paths custom4 $(local_c4_prefix)

   : HMM when building JUNOSW against different Custom4 will need to
   : also build Opticks against that same Custom4 FIRST
}


local_cuda()
{
    : ~/local.sh using vip-path from ~/vip/vip.bash
    local cuda_prefix=/usr/local/cuda-12.4
    vip-path append PATH            $cuda_prefix/bin  # for nvcc
    vip-path append LD_LIBRARY_PATH $cuda_prefix/lib64
}



local_ok_build()
{
   : ~/local.sh
   local_ok_externals  # Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy

   source ~/.opticks_config  # CUDA OptiX COMPUTE_CAPABILITY ARCHITECTURES
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
   : ~/local.sh
   local_ok_build
}

lo()
{
   : ~/local.sh  env for Opticks build test and analysis
   local_ok_build
   lco

   export GEOMBASE=$HOME/junosw/InstallArea/.opticks/GEOM
   ## liteweight for GEOM bash function navigation eg "GEOM cf"
}



local_ok_local()
{
   : ~/local.sh
   local_ok_externals    # Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy
   source /data1/blyth/local/opticks_Debug/bashrc

   export VIP_MODE=ok_local
   export VIP_DESC="pure Opticks usage from OPTICKS_PREFIX $OPTICKS_PREFIX"
}







ljb()
{
   : ~/local.sh
   : use this in fresh tab to setup env ready to perform oj_build
   local_oj_build
}
ljbb()
{
   : ~/local.sh
   : use this in fresh tab to setup env and perform the build
   local_oj_build
   oj_build
}

ljbb0()
{
   : ~/local.sh
   : same as ljbb but using NOINIT=1 which prevents geometry initialization
   NOINIT=1 ljbb
}





local_oj_build()
{
   : ~/local.sh
   export VIP_MODE=oj_build
   export VIP_DESC="local OJ build adapting .gitlab-ci.yml Opticks+JUNOSW build, see oj_build func"


   : JUNOTOP defines the versions of externals used by both JUNOSW
   : Opticks grabs the same versions of those externals it needs
   :
   : 2025/06/04
   :    JLatest symbolic link no longer latest - currently J25.3.0
   :    so follow .gitlab-ci.yml and change the below JUNOTOP to J25.4.0

   #export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
   export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0
   source $JUNOTOP/setup.sh

   local_JUNOTOP_override


   #export JUNO_OPTICKS_PREFIX=/cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
   export JUNO_OPTICKS_PREFIX=/data1/blyth/local/opticks_Debug
   : WIP: want to build agaist here built ok external rather than the cvmfs release
   : HMM : despite the prefix change still building against the cvmfs release of opticks
   : try ./build_Debug.sh after nuclear removal of build InstallConfig and InstallArea

   export JUNO_OFFLINE_OFF=1
   export OPTICKS_SETUP_VERBOSE=1

   if [ -n "$JUNO_OPTICKS_PREFIX" ]; then source $JUNO_OPTICKS_PREFIX/bashrc; fi

   oj_build_info(){
       : ~/local.sh
       local vv="JUNOTOP JUNO_OPTICKS_PREFIX JUNO_OFFLINE_OFF OPTICKS_SETUP_VERBOSE"
       for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done
   }

   oj_build_clean()
   {
      : when changing externals need nuclear rebuild
      cd $HOME/junosw
      rm -rf InstallArea build InstallConfig
   }

   oj_build_pre(){
       : ~/local.sh
       cd $HOME/junosw
       source .gitlab-ci/oj_helper.sh EMIT_ENV_CHECK
       mkdir -p InstallConfig
       source .gitlab-ci/oj_helper.sh EMIT_ENV    > InstallConfig/ENV.bash
       source .gitlab-ci/oj_helper.sh EMIT_ENVSET > InstallConfig/envset.sh
   }

   oj_build_(){
       : ~/local.sh
       cd $HOME/junosw ;
       ./build_Debug.sh ;
       [ $? -ne 0 ] && echo $FUNCNAME ERROR DURING BUILD && return 1
       return 0
   }

   oj_build_post(){
       : ~/local.sh
       cd $HOME/junosw
       cp InstallConfig/ENV.bash  InstallArea/ENV.bash
       cp InstallConfig/envset.sh InstallArea/envset.sh
   }

   oj_build_initialize(){
       : ~/local.sh
       : needs to be run once only to prepare the geometry inputs configuring tesselation solids and framespec

       cd $HOME/junosw
       ./oj_initialize.sh
   }

   oj_build(){
       : ~/local.sh
       [ -n "$OJ_BUILD_CLEAN" ] && oj_build_clean
       oj_build_info
       oj_build_pre
       oj_build_
       [ $? -ne 0 ] && echo $FUNCNAME ERROR DURING BUILD - EXITING && return 1

       oj_build_post
       [ -z "$NOINIT" ] && oj_build_initialize
       return 0
   }

   type oj_build
}


local_oj()
{
    source $HOME/junosw/InstallArea/envset.sh
}
loj(){
   : ~/local.sh
   : setup environment of OJ running
   local_oj
}



lji()
{
   : ~/local.sh
   : setup environment to prepare geomdir with oj_init
   local_oj_init
}

ljii()
{
   : ~/local.sh
   : setup environment to prepare geomdir and then invoke oj_local doing so
   local_oj_init
   oj_init
}


local_oj_init()
{
   : ~/local.sh
   local desc="usage of oj_build created envset.sh adapting .gitlab-ci.yml Opticks+JUNOSW test, use oj_local func to prep geomdir"
   local mode=oj_init

   export VIP_MODE="${VIP_MODE},$mode"
   export VIP_DESC="${VIP_DESC},$desc"
   export VIP_FUNC="${VIP_FUNC},$FUNCNAME"

   oj_init(){
       : follow .gitlab-ci.yml
       : needs to be run once only to prepare the geometry inputs configuring tesselation solids and framespec

       cd $HOME/junosw
       ./oj_initialize.sh
   }
   type oj_init
}


ljr()
{
   : ~/local.sh
   : setup environment to check a release
   local_oj_release
   oj_release
}

ljrt()
{
   : ~/local.sh
   : setup environment to check a release
   local_oj_release
   oj_release
   oj_release_test
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
   : ~/local.sh
   source ~/.opticks/GEOM/ENVSET.sh
   if [ -n "$ENVSET" -a -f "$ENVSET" ]; then
       source $ENVSET
   else
       echo $BASH_SOURCE - ERROR - MISSING ENVSET $ENVSET
       return 1
   fi
   return 0
}

oj_envset_test()
{
   : ~/local.sh
   : invoke oj_envset that sources the envset.sh picked via opticks ENVSET bash function
   : then runs a single event simulation under gdb debugger

   oj_envset
   [ $? -ne 0 ] && echo $FUNCNAME - ERROR WITH oj_envset && return 1


   source dbg__.sh
   source ~/.opticks/TEST/TEST.sh
   [ -z "$TEST" ] && echo $FUNCNAME - ERROR TEST NOT DEFINED && return 2

   local LOGDIR=/tmp/$USER/opticks/$FUNCNAME/$TEST
   local vv="BASH_SOURCE FUNCNAME test TEST LOGDIR PWD SProf__WRITE"
   vvp(){ for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done ; }


   mkdir -p $LOGDIR
   pushd $LOGDIR

   if [ "$TEST" == "default" ]; then

       vvp
       dbg__ \
          $(which python) \
          $(which tut_detsim.py) \
          --evtmax 1 \
          gun

   elif [ "$TEST" == "hit2" ]; then

       export SProf__WRITE=1
       export junoSD_PMT_v2_Opticks=INFO
       export SEvt=INFO
       export SEvt__SAVE=1
       export OPTICKS_EVENT_MODE=HitPhotonSeq  ## try some SEvt saving with OJ

       vvp
       dbg__ \
          $(which python) \
          $(which tut_detsim.py) \
          --evtmax 1 \
          --pmt-hit-type 2 \
          gun

       unset SProf__WRITE

   else
       printf "$FUNCNAME - ERROR TEST[$TEST] UNHANDLED \n"
   fi

   vvp
   popd

}


ojet(){ oj_envset_test $* ; }



local_oj_release()
{
   : ~/local.sh
   local desc="TODO: cvmfs release"
   local mode=oj_release

   export VIP_MODE="${VIP_MODE},$mode"
   export VIP_DESC="${VIP_DESC},$desc"
   export VIP_FUNC="${VIP_FUNC},$FUNCNAME"

   oj_release()
   {
       : ~/local.sh

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
       dbg__ \
          $(which python) \
          $(which tut_detsim.py) \
          --evtmax 1 \
          gun
   }



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


