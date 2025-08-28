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
[ -n "$BP" ] && defarg="env_info_run_ls"

arg=${1:-$defarg}

if [ "${arg/env}" != "$arg" ]; then

    ## see A:~/.bashrc oj_build + oj_local


    #envset=/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.3/el9_amd64_gcc11/2025_06_01/envset.sh
    #envset=/home/blyth/junosw/InstallArea/envset_Debug_custom4.sh   ## change paths to use /data1/blyth/local/custom4_Debug/0.1.8
    envset=/home/blyth/junosw/InstallArea/envset.sh

    if [ -f "$envset" ]; then
        source $envset
        export VIP_DESC="local OJ /home/blyth/junosw/InstallArea/envset.sh with release opticks python overridden"
    else
        echo $BASH_SOURCE - envset $envset does not exist -
        export VIP_DESC="local OJ BUT non-existing envset $envset - assume on laptop for analysis only"
        export GEOM=J25_4_0_opticks_Debug
    fi


    ASIS=0
    ZERO_HOLES=1
    MULTIUNION_HOLES=2
    HIERARCHY=3

    #export WaterPoolConstruction__CONFIG=$ASIS                # ASIS crashes in geometry conversion with enormous bt
    #export WaterPoolConstruction__CONFIG=$ZERO_HOLES          # same crash
    #export WaterPoolConstruction__CONFIG=$MULTIUNION_HOLES
    export WaterPoolConstruction__CONFIG=$HIERARCHY           # HIERARCHY is set by oj_geomsetup


    export U4Solid__IsFlaggedName=sDeadWater



    export VIP_DESC="local OJ /home/blyth/junosw/InstallArea/envset.sh with release opticks python overridden"

    cxtscript=$(which cxt_min.py)

    export CUDA_VISIBLE_DEVICES=0
    export OPTICKS_MAX_SLOT=M5
    export OPTICKS_EVENT_MODE=DebugLite
    export OPTICKS_HIT_MASK=EC   ## EC:EFFICIENCY_COLLECT / SD:SURFACE_DETECT

    export EVTMAX=1

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

    #test=UpperChimney
    #test=NNVT
    #test=Hama
    #test=Hama2
    #test=SPMT
    #test=CD
    #test=WP_PMT
    #test=WP_PMT_SIDE
    #test=WP_PMT_SEMI
    #test=POOLCOVER
    #test=POOLCOVER_REFINE
    TEST=WP_ATM_LPMT

    export TEST=${TEST:-$test}

    if [ "$TEST" == "UpperChimney" ]; then

       sevt__input_photon_dir=/data1/blyth/tmp/SGenerate__test
       #opticks_input_photon=SGenerate_ph_disc_K1.npy
       opticks_input_photon=SGenerate_ph_disc_M1.npy
       opticks_input_photon_frame=sChimneyLS:0:-2

    elif [ "$TEST" == "NNVT" ]; then

       #sevt__input_photon_dir=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
       sevt__input_photon_dir=/home/blyth/.opticks/InputPhotons
       #opticks_input_photon=RainXZ_Z230_10k_f8.npy
       opticks_input_photon=RainXZ_Z230_1M_f8.npy
       opticks_input_photon_frame=NNVT:0:1000
       #observation="junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 363159 hitCollectionAlt 362580 hcMuon 0 GPU YES"
       observation="junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 363183 hitCollectionAlt 362581 hcMuon 0 GPU YES"
       # SABHit  a_nhit : (  362581 +-  602 )  b_nhit:(   363183 +-  602 )  a/b: (  0.998 +-  0.003 )  b/a: (  1.002 +-  0.003)

    elif [ "$TEST" == "Hama" ]; then

       #sevt__input_photon_dir=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
       sevt__input_photon_dir=/home/blyth/.opticks/InputPhotons
       #opticks_input_photon=RainXZ_Z230_10k_f8.npy
       opticks_input_photon=RainXZ_Z230_1M_f8.npy
       opticks_input_photon_frame=Hama:0:0
       observation="junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 331746 hitCollectionAlt 331799 hcMuon 0 GPU YES"

    elif [ "$TEST" == "Hama2" ]; then

       #sevt__input_photon_dir=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
       sevt__input_photon_dir=/home/blyth/.opticks/InputPhotons
       #opticks_input_photon=RainXZ_Z230_10k_f8.npy
       opticks_input_photon=RainXZ_Z230_1M_f8.npy
       opticks_input_photon_frame=Hama:0:1000

    elif [ "$TEST" == "SPMT" ]; then

       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
       #opticks_input_photon=RainXZ_Z230_100k_f8.npy     # too long for tiny SPMT
       opticks_input_photon=RainXZ_Z230_X25_100k_f8.npy  # +-25mm in X to target tiny SPMT
       opticks_input_photon_frame=PMT_3inch:0:0
       observation="A and B now matching"

    elif [ "$TEST" == "CD" ]; then

       #sevt__input_photon_dir=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
       sevt__input_photon_dir=/home/blyth/.opticks/InputPhotons
       opticks_input_photon=RandomSpherical1M_f8.npy    ## assert < MAX_PARTICLES:10k when using GenEvtInfoAnaMgr::PostUserTrackingAction
       opticks_input_photon_frame=sTarget

       export OPTICKS_INPUT_PHOTON_CHANGE_TIME=0.1 ## because RandomSpherical had incrementing time for some past debug

    elif [ "$TEST" == "WP_PMT" ]; then

       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
       opticks_input_photon=RainXZ_Z230_100k_f8.npy
       opticks_input_photon_frame=PMT_20inch_veto:0:1000
       observation=""

       #export U4Recorder__EndOfRunAction_Simtrace=1
       #export U4Simtrace__level=2
       #export C4OpBoundaryProcess__PIDX_ENABLED=1
       #export PIDX=99999


    elif [ "$TEST" == "WP_PMT_SIDE" ]; then

       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
       opticks_input_photon=SideZX_X300_100k_f8.npy
       opticks_input_photon_frame=PMT_20inch_veto:0:1000
       observation=""

    elif [ "$TEST" == "WP_PMT_SEMI" ]; then

       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
       opticks_input_photon=SemiCircleXZ_R-500_100k_f8.npy
       opticks_input_photon_frame=PMT_20inch_veto:0:1000
       observation=""

    elif [ "$TEST" == "POOLCOVER" -o "$TEST" == "POOLCOVER_REFINE" ]; then

      sevt__input_photon_dir=$HOME/.opticks/InputPhotons
      #opticks_input_photon=UpXZ1000_f8.npy
      opticks_input_photon=CircleXZ_R500_100k_f8.npy
      #opticks_input_photon=CircleXZ_R10_361_f8.npy
      #opticks_input_photon_frame=3345.569,20623.73,21500
      opticks_input_photon_frame=3345.569,20623.73,21000
      #export PIDX=99999
      onservation="WP_PMT virtual clippers number of BT discrepant"

      if [ "${TEST/REFINE}" != "$TEST" ]; then
          export OPTICKS_PROPAGATE_REFINE=1
      else
          unset OPTICKS_PROPAGATE_REFINE
      fi

    elif [ "$TEST" == "WP_ATM_LPMT" ]; then

       sevt__input_photon_dir=$HOME/.opticks/InputPhotons

       ## BEFORE INSTANCING THE 348
       ##opticks_input_photon=SideZX_X300_100k_f8.npy
       ##opticks_input_photon_frame=PMT_20inch_pmt_solid_head:7:-2   ## EXPECTING TO HIT MOSTLY pmtid:52402 phi:179.25

       ## AFTER INSTANCING THE 348
       opticks_input_photon=RainXZ_Z230_100k_f8.npy
       opticks_input_photon_frame=PMT_20inch_pmt_solid_head:0:$(( 5 + 2 ))   ## EXPECTING TO HIT MOSTLY pmtid:52402 phi:179.25
       observation="one of the 12*29 = 348"
       #
       #  /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Identifier/pmt_20250422_WPATMLPMT.csv
       #  7 52402,1,0,4,1,3,2,0,1185,2,-21078.2,275.9287,20163,90,179.25,PA1801-1022,NNVT
       #   AT FAR -ve X POINT TOWARDS +X (APPROXIMATELY)

    fi

    export SEvt__INPUT_PHOTON_DIR=${SEvt__INPUT_PHOTON_DIR:-$sevt__input_photon_dir}
    export OPTICKS_INPUT_PHOTON=${opticks_input_photon}
    export OPTICKS_INPUT_PHOTON_FRAME=${opticks_input_photon_frame}
    export SEvt__transformInputPhoton_VERBOSE=1

    path=$SEvt__INPUT_PHOTON_DIR/$OPTICKS_INPUT_PHOTON
    if [ ! -f "$path" -a -f "$envset" ]; then
       echo $BASH_SOURCE : FATAL : INPUT PHOTONS MIS-CONFIGURED path $path
       return 1
    fi

    ## ] config input photon running


    ## below env adapts the output directory for .npy arrays
    ## OPTICKS_EVENT_NAME is required to contain strings such as "Debug" and "Philox"
    ## when those correspond to the build config as checked by sbuild::Matches
    export OPTICKS_SCRIPT=InputPhotonsCheck
    if [ -n "$OLDNAME" ]; then
        export OPTICKS_EVENT_NAME=DebugPhilox_${OPTICKS_INTEGRATION_MODE}_${OPTICKS_INPUT_PHOTON_FRAME}_${OPTICKS_INPUT_PHOTON/.npy}
    else
        export OPTICKS_EVENT_NAME=DebugPhilox_${OPTICKS_INTEGRATION_MODE}_${TEST}
    fi



    ## convenience vars for analysis

    oldtmp=/tmp/$USER/opticks
    newtmp=/usr/local/tmp/$USER/opticks
    # change tmp folder to one that does not get auto-deleted on reboots
    # and that can be easily be he same on macOS and Linux
    export TMP=$oldtmp
    #export TMP=$newtmp  # TODO: switch to newtmp

    export LOGDIR=$TMP/GEOM/$GEOM/$OPTICKS_SCRIPT/ALL${VERSION}_${OPTICKS_EVENT_NAME}
    export EVT=000
    export AFOLD=$LOGDIR/A$EVT
    export BFOLD=$LOGDIR/B$EVT
    export MFOLD=$LOGDIR/M998

    mkdir -p $LOGDIR
    cd $LOGDIR && pwd
fi


logging(){
   type $FUNCNAME
   : export SSim__stree_level=1
   : export SEvt__EPH=1
}
[ -n "$LOG" ] && logging

[ -n "$EOR_SIMTRACE" ] && export U4Recorder__EndOfRunAction_Simtrace=1


if [ "${arg/info}" != "$arg" ]; then
   vv=""
   vv="$vv BASH_SOURCE defarg arg TMP GEOM TEST LOGDIR AFOLD BFOLD MFOLD IPYTHON PYTHON SEvt__INPUT_PHOTON_DIR"
   vv="$vv OPTICKS_INPUT_PHOTON OPTICKS_INPUT_PHOTON_FRAME OPTICKS_MAX_BOUNCE OPTICKS_PREFIX"
   vv="$vv OPTICKS_INTEGRATION_MODE"
   vv="$vv anascript cxtscript"
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
            --evtmax $EVTMAX \
            --seed 42 \
            opticks

         #  --pmt-dbtype File \

    elif [ "$OPTICKS_INTEGRATION_MODE" == "0" -o "$OPTICKS_INTEGRATION_MODE" == "1" ]; then

        dbg__ \
            $(which python) \
            $(which tut_detsim.py) \
            --opticks-mode $OPTICKS_INTEGRATION_MODE \
            --evtmax $EVTMAX \
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
if [ "${arg/sab}" != "$arg" ]; then
   SAB=1 PICK=X ${IPYTHON:-ipython} --pdb -i $anascript
   [ $? -ne 0 ] && echo $BASH_SOURCE sab error
fi
if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $anascript
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error
fi


if [ "${arg/cxt}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $cxtscript
   [ $? -ne 0 ] && echo $BASH_SOURCE cxt error
fi


if [ "${arg/chi2}" != "$arg" ] ; then
   sseq_index_test.sh info_run_ana
fi

if [ "${arg/lhi2}" != "$arg" ] ; then
   ## version of "chi2" with longer table
   sseq_index_ab__desc_NUM_MAX=100 sseq_index_test.sh info_run_ana
fi

if [ "${arg/dhi2}" != "$arg" ] ; then
   # development version of "chi2"
   unset sseq_index_test__DEBUG
   #export sseq_index_test__DEBUG=1
   DEV=1 $HOME/opticks/sysrap/tests/sseq_index_test.sh info_build_run_ana
fi


if [ "${arg/gevt}" != "$arg" ]; then
   ## HMM: even restricting to AFOLD BFOLD is several G when have record.npy included, so add below ghit
   source $HOME/opticks/bin/rsync.sh $AFOLD
   source $HOME/opticks/bin/rsync.sh $BFOLD
fi

if [ "${arg/ghit}" != "$arg" ]; then
   source $HOME/opticks/bin/rsync.sh $AFOLD/hit.npy
   source $HOME/opticks/bin/rsync.sh $BFOLD/hit.npy
fi




