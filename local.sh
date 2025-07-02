#!/bin/bash

local_usage(){ cat << EOU
.bash_profile > .bashrc > local.sh : local_usage
==================================================

local.sh is the environment control script developed on Ada workstation (A).


Updating local OK build
------------------------

After making changes in ~/opticks update OK with:

1. open new tab with empty env and get into env and build::

    local_ok_build   ## lob
                     ## alternatively use "lo" which does conda setup too

    oo
    opticks-t


Updating local OJ build (equivalent of gitlab CI OJ build)
------------------------------------------------------------

After making changes in ~/junosw eg to Examples/Tutorial/share/opticks_juno.sh
update OJ with:

* open new tab with empty env and setup and invoke the OJ build::

    local_oj_build # ljb
    oj_build
    ## alternatively use "ljbb" to do both the above


Initialize geomdir (equivalent of gitlab CI OJ test)
-------------------------------------------------

* open new tab with empty env and setup and invoke the OJ Opticks geom config::

    local_oj_init # lji
    oj_init
    ## alternatively use "ljlb" to do both the above



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
   }

   oj_build_post(){
       : ~/local.sh
       cd $HOME/junosw
       cp InstallConfig/ENV.bash  InstallArea/ENV.bash
       cp InstallConfig/envset.sh InstallArea/envset.sh
   }

   oj_build(){
       : ~/local.sh
       [ -n "$OJ_BUILD_CLEAN" ] && oj_build_clean
       oj_build_info
       oj_build_pre
       oj_build_
       oj_build_post
   }

   type oj_build
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
   local mode=oj_local

   export VIP_MODE="${VIP_MODE},$mode"
   export VIP_DESC="${VIP_DESC},$desc"
   export VIP_FUNC="${VIP_FUNC},$FUNCNAME"

   source /home/blyth/junosw/InstallArea/envset.sh
   oj_init(){
       : follow .gitlab-ci.yml
       : needs to be run once only to prepare the geometry inputs configuring tesselation solids and framespec
       oj_initialize_meshname_tessname   ## "tut_detsim.py --opticks-mode 1 --evtmax 0 gun" to get meshname.txt and create tessname.txt from that
       oj_initialize_framespec           ## write the framespec bookmark strings
       oj_initialize_geomdir             ## "tut_detsim.py --opticks-mode 1 --evtmax 0 gun" to persist the OJ_GEOMDIR geometry dir with chosen tesselation
   }

   type oj_init

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


