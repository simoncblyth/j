#!/bin/bash
usage(){ cat << EOU
InputPhotonsCheck.sh
=====================

This uses tut_detsim.py with opticks-mode 3 and 
input photons to do bi-simulation saving into 
AFOLD and BFOLD.

WIP: try using input photons with opticks-mode 0 

From laptop connect to workstation with empty env "A"::

    ipc   # source this script and invoke default commands

More cautious usage from laptop OR workstation::

    ipc env_info
    ipc run       ## tut_detsim.py --opticks-mode 3 with opticks input photons
    ipc chi2      ## C++ A:B compare photon histories AFOLD/seq.npy BFOLD/seq.npy
    ipc pdb
    SAB=1 ipc pdb


On workstation directly 3D(pyvista) GUI visualize photon step point positions::

     ctrl-alt-T        # open terminal with empty env
     local_conda_ok    # setup conda env

     ipc env_info                                # need env to set AFOLD BFOLD
     PICK=AB EYE=0,10000,0 INCPOI=-5  ipc pdb    # viz the points


Using::

     ipc(){ source ~/j/InputPhotonsCheck/InputPhotonsCheck.sh $* ; : .bashrc ;  }
     ipcv(){ vi ~/j/InputPhotonsCheck/InputPhotonsCheck.sh ; : .bashrc ; }


Looks like there is no CE scaling for the EYE inputs. Thus for example offset
the EYE position in Y to avoid starting viewpoint a few mm from center
of geometry frames which is awkward.

NB while it is convenient for debug to inhabit some
sourced env setup in .bashrc etc.. for reproducibility/longevity of
scripts it is better to use an almost empty login env and do
all setup in the script.

But do not let that objective stop you using "source" during development
of the script to avoid repeating time consuming env setup
for example.


env
   environment setup which also sets LOGDIR and cd to it
info
   emit envvars
run
   tut_detsim.py --opticks-mode 3 : NB must invoke from LOGDIR
ls
   list output npy
pdb
   run anascript with IPYTHON --pdb
ana
   run anascript with
chi2
   run sseq_index_test.sh comparing seq.npy photon histories
dhi2
   development run sseq_index_test.sh comparing seq.npy photon histories



EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
anascript=$(realpath InputPhotonsCheck.py)

defarg="env_info_run_ls_chi2_pdb"
arg=${1:-$defarg}

if [ "${arg/env}" != "$arg" ]; then

    ## see A:~/.bashrc oj_build + oj_local
    source /home/blyth/junosw/InstallArea/envset.sh
    #PYTHONPATH=/data1/blyth/local/opticks_Debug/py:$PYTHONPATH
    export VIP_DESC="local OJ /home/blyth/junosw/InstallArea/envset.sh with release opticks python overridden"

    export CUDA_VISIBLE_DEVICES=0
    export OPTICKS_MAX_SLOT=M5
    export OPTICKS_EVENT_MODE=DebugLite

    #opticks_integration_mode=0    ## added geometry convertion with zero in G4CXOpticks::SetGeometry_JUNO
    #opticks_integration_mode=1
    #opticks_integration_mode=2
    opticks_integration_mode=3
    export OPTICKS_INTEGRATION_MODE=$opticks_integration_mode

    #version=0
    version=1
    export VERSION=$version

    case $version in
       0) opticks_max_bounce=31 ;;
       1) opticks_max_bounce=63 ;;
    esac
    export OPTICKS_MAX_BOUNCE=$opticks_max_bounce



    ## [ config input photon running

    #test=CD
    test=PMT
    export TEST=${TEST:-$test}

    if [ "$TEST" == "UpperChimney" ]; then

       sevt__input_photon_dir=/data1/blyth/tmp/SGenerate__test
       #opticks_input_photon=SGenerate_ph_disc_K1.npy  
       opticks_input_photon=SGenerate_ph_disc_M1.npy
       opticks_input_photon_frame=sChimneyLS:0:-2

    elif [ "$TEST" == "PMT" ]; then

       #sevt__input_photon_dir=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
       sevt__input_photon_dir=/home/blyth/.opticks/InputPhotons
       #opticks_input_photon=RainXZ_Z230_10k_f8.npy
       opticks_input_photon=RainXZ_Z230_1M_f8.npy
       opticks_input_photon_frame=NNVT:0:1000

    elif [ "$TEST" == "CD" ]; then

       #sevt__input_photon_dir=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
       sevt__input_photon_dir=/home/blyth/.opticks/InputPhotons
       opticks_input_photon=RandomSpherical1M_f8.npy    ## assert < MAX_PARTICLES:10k when using GenEvtInfoAnaMgr::PostUserTrackingAction
       opticks_input_photon_frame=sTarget

    fi

    export SEvt__INPUT_PHOTON_DIR=${SEvt__INPUT_PHOTON_DIR:-$sevt__input_photon_dir}
    export OPTICKS_INPUT_PHOTON=${opticks_input_photon}
    export OPTICKS_INPUT_PHOTON_FRAME=${opticks_input_photon_frame}
    export SEvt__transformInputPhoton_VERBOSE=1

    path=$SEvt__INPUT_PHOTON_DIR/$OPTICKS_INPUT_PHOTON
    if [ ! -f "$path" ]; then
       echo $BASH_SOURCE : FATAL : INPUT PHOTONS MIS-CONFIGURED path $path 
       return 1 
    fi 

    ## ] config input photon running


    ## below env adapts the output directory for .npy arrays
    ## OPTICKS_EVENT_NAME is required to contain strings such as "Debug" and "Philox"
    ## when those correspond to the build config as checked by sbuild::Matches
    export OPTICKS_SCRIPT=InputPhotonsCheck
    export OPTICKS_EVENT_NAME=DebugPhilox_${OPTICKS_INTEGRATION_MODE}_${OPTICKS_INPUT_PHOTON_FRAME}_${OPTICKS_INPUT_PHOTON/.npy}

    ## convenience vars for analysis
    export TMP=/tmp/$USER/opticks
    export LOGDIR=$TMP/GEOM/$GEOM/$OPTICKS_SCRIPT/ALL${VERSION}_${OPTICKS_EVENT_NAME}
    export EVT=000
    export AFOLD=$LOGDIR/A$EVT
    export BFOLD=$LOGDIR/B$EVT

    mkdir -p $LOGDIR
    cd $LOGDIR && pwd
fi


if [ "${arg/info}" != "$arg" ]; then
   vv=""
   vv="$vv BASH_SOURCE defarg arg TMP GEOM TEST LOGDIR AFOLD BFOLD IPYTHON PYTHON SEvt__INPUT_PHOTON_DIR"
   vv="$vv OPTICKS_INPUT_PHOTON OPTICKS_INPUT_PHOTON_FRAME OPTICKS_MAX_BOUNCE OPTICKS_PREFIX"
   vv="$vv OPTICKS_INTEGRATION_MODE"
   vv="$vv anascript"
   for v in $vv ; do printf "%30s :  %s\n" "$v" "${!v}" ; done
fi


if [ "${arg/run}" != "$arg" ]; then

    cd $LOGDIR && pwd
    source dbg__.sh

    if [ "$OPTICKS_INTEGRATION_MODE" == "3" -o "$OPTICKS_INTEGRATION_MODE" == "2" ]; then

        dbg__ \
            $(which python) \
            $(which tut_detsim.py) \
            --opticks-mode $OPTICKS_INTEGRATION_MODE \
            --opticks-anamgr \
            --no-anamgr-normal \
            --no-anamgr-genevt \
            --no-anamgr-edm-v2 \
            --no-anamgr-grdm \
            --no-anamgr-deposit \
            --no-anamgr-deposit-tt \
            --no-anamgr-interesting-process \
            --no-anamgr-optical-parameter \
            --no-anamgr-timer \
            --evtmax 1 \
            --seed 42 \
            opticks

         #  --pmt-dbtype File \

    elif [ "$OPTICKS_INTEGRATION_MODE" == "0" -o "$OPTICKS_INTEGRATION_MODE" == "1" ]; then

        dbg__ \
            $(which python) \
            $(which tut_detsim.py) \
            --opticks-mode $OPTICKS_INTEGRATION_MODE \
            --evtmax 1 \
            --seed 42 \
            opticks

        #  --pmt-dbtype File \
    fi 


    rc=$?
    echo DONE $rc
    pwd
fi

if [ "${arg/ls}" != "$arg" ]; then
    ff="LOGDIR AFOLD BFOLD"
    for f in $ff ; do echo $f ${!f} && ls -alst ${!f} ; done
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $anascript
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error
fi

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $anascript
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error
fi

if [ "${arg/chi2}" != "$arg" ] ; then
   sseq_index_test.sh info_run_ana
fi

if [ "${arg/dhi2}" != "$arg" ] ; then
   # development version of "chi2"
   unset sseq_index_test__DEBUG
   #export sseq_index_test__DEBUG=1
   DEV=1 $HOME/opticks/sysrap/tests/sseq_index_test.sh info_build_run_ana
fi


