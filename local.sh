#!/bin/bash

local_usage(){ cat << EOU
.bash_profile > .bashrc > local.sh : local_usage
==================================================

local.sh is the environment control script developed on Ada workstation (A). 


Updating local OK build
------------------------

After making changes in ~/opticks update OK with:

1. open new tab with empty env and get into env and build::

    local_ok_build   # lob
    oo
    opticks-t



Updating local OJ build
------------------------

After making changes in ~/junosw eg to Examples/Tutorial/share/opticks_juno.sh
update OJ with:

1. open new tab with empty env and setup and invoke the OJ build::

    local_oj_build # ljb
    oj_build

2. open new tab with empty env and setup and invoke the OJ Opticks geom config::

    local_oj_local # ljl
    oj_local


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
      oj_local) local_oj_local ;;
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

local_ok_externals()
{
   : ~/local.sh
   : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy versions matching JUNOSW
   : NB versions need to match those used by gitlab-ci build when using the gitlab cvmfs release

   local_unset

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Xercesc/3.2.4/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/CLHEP/2.4.7.1/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/custom4/0.1.8/bashrc

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Python/3.9.19/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/python-numpy/1.23.5/bashrc

   export VIP_MODE=ok_externals
   export VIP_DESC="Opticks JUNOSW externals in common manually setup from cvmfs : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy"
}

local_ok_build()
{
   : ~/local.sh
   local_ok_externals  # Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy
   source ~/.opticks_config  # CUDA OptiX COMPUTE_CAPABILITY ARCHITECTURES
   om-

   export VIP_MODE=ok_build
   export VIP_DESC="env to build Opticks against JUNOSW externals manually setup from cvmfs : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy"

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
   local_conda_ok
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
   local_oj_build
}

local_oj_build()
{
   : ~/local.sh
   export VIP_MODE=oj_build
   export VIP_DESC="local OJ build adapting .gitlab-ci.yml Opticks+JUNOSW build, see oj_build func"


   : JUNOTOP defines the versions of externals used by both JUNOSW and Opticks
   : 2025/06/04 
   :    JLatest symbolic link no longer latest - currently J25.3.0
   :    so follow .gitlab-ci.yml and change the below JUNOTOP to J25.4.0 

   #export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest  
   export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0

   #export JUNO_OPTICKS_PREFIX=/cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
   export JUNO_OPTICKS_PREFIX=/data1/blyth/local/opticks_Debug
   : WIP: want to build agaist here built ok external rather than the cvmfs release
   : HMM : despite the prefix change still building against the cvmfs release of opticks
   : try ./build_Debug.sh after nuclear removal of build InstallConfig and InstallArea

   export JUNO_OFFLINE_OFF=1
   export OPTICKS_SETUP_VERBOSE=1

   source $JUNOTOP/setup.sh
   if [ -n "$JUNO_OPTICKS_PREFIX" ]; then source $JUNO_OPTICKS_PREFIX/bashrc; fi

   oj_build_info(){
       : ~/local.sh
       local vv="JUNOTOP JUNO_OPTICKS_PREFIX JUNO_OFFLINE_OFF OPTICKS_SETUP_VERBOSE"
       for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done
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
   }

   oj_build_post(){
       : ~/local.sh
       cd $HOME/junosw
       cp InstallConfig/ENV.bash  InstallArea/ENV.bash
       cp InstallConfig/envset.sh InstallArea/envset.sh
   }

   oj_build(){
       : ~/local.sh
       oj_build_info
       oj_build_pre
       oj_build_
       oj_build_post
   }
}


ljl()
{
   : ~/local.sh
   local_oj_local
}
local_oj_local()
{
   : ~/local.sh
   local desc="usage of oj_build created envset.sh adapting .gitlab-ci.yml Opticks+JUNOSW test, use oj_local func to prep geomdir"
   local mode=oj_local

   export VIP_MODE="${VIP_MODE},$mode"
   export VIP_DESC="${VIP_DESC},$desc"
   export VIP_FUNC="${VIP_FUNC},$FUNCNAME"

   source /home/blyth/junosw/InstallArea/envset.sh
   oj_local(){
       : follow .gitlab-ci.yml
       : needs to be run once only to prepare the geometry inputs configuring tesselation solids and framespec
       oj_initialize_meshname_tessname   ## "tut_detsim.py --opticks-mode 1 --evtmax 0 gun" to get meshname.txt and create tessname.txt from that
       oj_initialize_framespec           ## write the framespec bookmark strings
       oj_initialize_geomdir             ## "tut_detsim.py --opticks-mode 1 --evtmax 0 gun" to persist the OJ_GEOMDIR geometry dir with chosen tesselation
   }
}


local_oj_release()
{
   : ~/local.sh
   local desc="TODO: cvmfs release"
   export VIP_MODE=oj_release
   export VIP_DESC=$desc
   export VIP_FUNC=$FUNCNAME
}

local_conda()
{
   : ~/local.sh

   local desc="miniconda3 hookup"
   local mode="conda"

   export VIP_MODE="${VIP_MODE},$mode"
   export VIP_DESC="${VIP_DESC},$desc"
   export VIP_FUNC="${VIP_FUNC},$FUNCNAME"




   ## below was appended by running : conda init --all
   # >>> conda initialize >>>
   # !! Contents within this block are managed by 'conda init' !!
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
   # <<< conda initialize <<<
}

local_conda_ok()
{
   : ~/local.sh
   local desc="conda with the ok analysis environment activated including matplotlib and pyvista"
   local mode=conda_ok

   export VIP_MODE="${VIP_MODE},$mode"
   export VIP_DESC="${VIP_DESC},$desc"
   export VIP_FUNC="${VIP_FUNC},$FUNCNAME"

   local_conda
   conda activate ok
}
lco()
{
   : ~/local.sh
   local_conda_ok
}


local_unhandled()
{
   : ~/local.sh
   echo $BASH_SOURCE - ERROR VIP_MODE $VIP_MODE is UNHANDLED
}


