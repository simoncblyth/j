unexpected-py-fail : CONFIRMED DUE TO "export JUNO_OFFLINE_OFF=1" 
====================================================================

From gitlab::

    $ oj_initialize_meshname_tessname
    oj_initialize_meshname_tessname is a function
    oj_initialize_meshname_tessname () 
    { 
        : opticks_juno.sh;
        if [ -n "$OJ_VERBOSE" ]; then
            type $FUNCNAME;
        fi;
        echo [ $FUNCNAME;
        export G4CXOpticks__SaveGeometry_DIR=${OJ_GEOMDIR};
        export CSGFoundry__SAVE_OPT=meshname;
        tut_detsim.py --opticks-mode 1 --evtmax 0 gun;
        unset CSGFoundry__SAVE_OPT;
        local meshname=${OJ_GEOMDIR}/CSGFoundry/meshname.txt;
        if [ -f "$meshname" ]; then
            echo $FUNCNAME - created meshname $meshname;
            ls -alst $meshname;
        else
            echo $FUNCNAME - FAILED TO CREATE meshname $meshname;
        fi;
        if [ -f "$meshname" -a -n "${stree__force_triangulate_solid}" ]; then
            local tessname=${stree__force_triangulate_solid/filepath:};
            cat $meshname | oj_tessname_from_meshname > $tessname;
            wc -l $meshname $tessname;
        else
            echo $FUNCNAME - MISSING meshname $meshname OR stree__force_triangulate_solid;
        fi;
        echo ] $FUNCNAME;
        return 0
    }
    [ oj_initialize_meshname_tessname
    **************************************************
    Welcome to SNiPER v2.1.0
    Running @ runner-t2mxyrv-project-1910-concurrent-0c4rwr on Tue Aug 19 03:11:38 2025
    **************************************************
    Traceback (most recent call last):
      File "/builds/JUNO/offline/junosw/InstallArea/bin/tut_detsim.py", line 46, in <module>
        detsim_module = JUNODetSimModule()
                        ^^^^^^^^^^^^^^^^^^
      File "/builds/JUNO/offline/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py", line 58, in __init__
        self.init_yaml_conf()
      File "/builds/JUNO/offline/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py", line 101, in init_yaml_conf
        self.DATA_MATERIALS = load_config_from_cmd("--config-gen-materials", "GtPosGeoMapping.yaml")
                              ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
      File "/builds/JUNO/offline/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py", line 73, in load_config_from_cmd
        path_data = os.path.join(
                    ^^^^^^^^^^^^^
      File "<frozen posixpath>", line 76, in join
    TypeError: expected str, bytes or os.PathLike object, not NoneType
    **************************************************
    Terminating @ runner-t2mxyrv-project-1910-concurrent-0c4rwr on Tue Aug 19 03:11:39 2025
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    Cleaning up project directory and file based variables 00:00
    ERROR: Job failed: command terminated with exit code 1




Looks like TUTORIALROOT envvar not defined::

  62     def init_yaml_conf(self):
  63         import yaml
  64 
  65         # helpers
  66         def load_config(config_file):
  67             with open(config_file) as f:
  68                 return yaml.safe_load(f)
  69 
  70         def load_config_from_cmd(option, default_filename):
  71             data = None
  72 
  73             path_data = os.path.join(
  74                 os.environ.get("TUTORIALROOT"),
  75                 "share/mac",
  76                 default_filename
  77             )
  78 
  79             # override if user specify a new config
  80             if option in sys.argv:
  81                 i = sys.argv.index(option)
  82                 path_data = sys.argv[i+1]
  83 
  84             if os.path.exists(path_data):
  85                 log.debug("Loading data from %s"%path_data)
  86                 data = load_config(path_data)
  87             else:
  88                 log.fatal("Can't find %s"%path_data)
  89                 sys.exit(-1)
  90 
  91             if data is None:
  92                 log.fatal("Can't load any data. Please check the file %s. "%path_data)
  93                 sys.exit(-1)
  94 
  95             return data
  96 
  97 
  98         ######################################################################
  99         # = GenTool =
 100         # == materials ==
 101         self.DATA_MATERIALS = load_config_from_cmd("--config-gen-materials", "GtPosGeoMapping.yaml")
 102         log.debug("DATA_MATERIALS: %s"%self.DATA_MATERIALS)
 103         # == generator execs ==
 104         self.GENERATOR_EXEC = load_config_from_cmd("--config-gen-exec", "GtGenExecMapping.yaml")
 105         log.debug("GENERATOR_EXEC: %s"%self.GENERATOR_EXEC)
 106         log.info("end of init_yaml_conf")





Suspect JUNO_OFFLINE_OFF is preventing setup
------------------------------------------------

.gitlab-ci.yml::

     54 .opticks_build_job_template:
     55   extends: .job_template
     56   stage: build
     57   image: simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9
     58   variables:
     59     JUNO_CLANG_PREFIX:
     60     JUNO_OPTICKS_PREFIX: /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
     61     EXTRA_BUILD_FLAGS: JUNO_CMAKE_BUILD_TYPE=Debug
     62   script:
     63     - printf "[ ================ BUILD PHASE OF BUILD JOB =========================\n"
     64     - for repo in juno.ihep.ac.cn opticks.ihep.ac.cn; do if [ ! -d /cvmfs/$repo ]; then sudo mkdir /cvmfs/$repo; fi; sudo mount -t cvmfs $repo /cvmfs/$repo; done
     65     - source .gitlab-ci/oj_helper.sh EMIT_ENV_CHECK
     66     - mkdir InstallConfig
     67     - source .gitlab-ci/oj_helper.sh EMIT_ENV    > InstallConfig/ENV.bash
     68     - cat InstallConfig/ENV.bash
     69     - source .gitlab-ci/oj_helper.sh EMIT_ENVSET > InstallConfig/envset.sh
     70     - cat InstallConfig/envset.sh
     71     - export JUNO_OFFLINE_OFF=1        # Disable JUNOSW setup prior to having built JUNOSW
     72     - export OPTICKS_SETUP_VERBOSE=1   # ~/j/gitlab-ci/mockbuild.sh shows this protects against "set -eo pipefail"
     73     - source $JUNOTOP/setup.sh
     74     - if [ -n "$JUNO_CLANG_PREFIX" ]; then source $JUNO_CLANG_PREFIX/bashrc; fi
     75     - if [ -n "$JUNO_OPTICKS_PREFIX" ]; then source $JUNO_OPTICKS_PREFIX/bashrc; fi
     76     - env $EXTRA_BUILD_FLAGS ./build.sh
     77     - cp InstallConfig/ENV.bash  InstallArea/ENV.bash
     78     - cp InstallConfig/envset.sh InstallArea/envset.sh
     79     - unset JUNO_OFFLINE_OFF # now that it has been built the below needs the JUNOSW environment 
     80     - printf "] ================ BUILD PHASE OF BUILD JOB =========================\n"
     81     - printf "[ ================ TEST PHASE OF BUILD JOB =========================\n"
     82     - env $EXTRA_BUILD_FLAGS ./oj_initialize.sh
     83     - printf "] ================ TEST PHASE OF BUILD JOB =========================\n"


oj_initialize.sh::

     31 source InstallArea/envset.sh
     32 
     33 vv="BASH_SOURCE PWD OPTICKS_PREFIX JUNO_OFFLINE_OFF TUTORIALROOT"
     34 for v in $vv ; do printf "%30s : %s\n " "$v" "${!v}" ; done
     35 
     36 oj_initialize_framespec
     37 oj_initialize_meshname_tessname
     38 oj_initialize_geomdir
     39 
     40 source .gitlab-ci/oj_helper.sh MAKE_TAR
     41 source .gitlab-ci/oj_helper.sh DEPLOY_TAR
     42 


trace from InstallArea/envset.sh::

     01 #!/bin/bash
      2 # generated from .gitlab-ci.yml of 
      3 # .gitlab-ci/oj_helper.sh EMIT_ENVSET
      4 
      5 HERE=$(dirname $(realpath $BASH_SOURCE))
      6 DEFAULT_PREFIX=$HERE
      7 PREFIX=${OJ_PREFIX:-$DEFAULT_PREFIX}
      8 
      9 source $PREFIX/ENV.bash             ## define JUNOTOP and JUNO_OPTICKS_PREFIX 
     10 source $JUNOTOP/setup.sh            ## hookup many JUNOSW externals excluding Opticks
     11 source $JUNO_OPTICKS_PREFIX/bashrc  ## hookup for Opticks and its externals
     12 
     13 source $PREFIX/bin/opticks_juno.sh  ## oj bash functions 
     14 oj_geomsetup
     15 
     16 export CMAKE_PREFIX_PATH=$PREFIX:${CMAKE_PREFIX_PATH}
     17 export PATH=$PREFIX/bin:${PATH}
     18 export LD_LIBRARY_PATH=$PREFIX/lib64:${LD_LIBRARY_PATH}
     19 export PYTHONPATH=$PREFIX/lib64:${PYTHONPATH}
     20 export PYTHONPATH=$PREFIX/python:${PYTHONPATH}



    A[blyth@localhost junosw]$ cat InstallArea/ENV.bash 
    #!/bin/bash
    # generated from .gitlab-ci.yml of 
    # .gitlab-ci/oj_helper.sh EMIT_ENV
    #
    # This is used to emit InstallArea/ENV.bash in the build job
    # which is subsequently sourced in the test/deploy job to pass
    # the needed environment between jobs.
    # Also the captured prefixes are needed when using
    # the expanded tarball OJ distribution.
    #
    # NB basename of the realpath JUNOTOP and JUNO_OPTICKS_PREFIX
    # so generic prefixes from .gitlab-ci.yml are runtime changed into latest prefix
    #
    export J_ARCH=el9_amd64_gcc11
    export J_VER=J25.4.0   # eg J25.2.3 NB
    export O_VER=opticks_Debug  # eg Opticks-v0.3.3
    export OJ_VER=J25.4.0_opticks_Debug  # eg J25.2.3_Opticks-v0.3.3
    export OJ_SLUG=J25_4_0_opticks_Debug  # eg J25_2_3_Opticks_v0_3_3
    export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0
    export JUNO_OPTICKS_PREFIX=/data1/blyth/local/opticks_Debug

    export OJ_DIST=J25.4.0_opticks_Debug.tar
    export OJ_RELP=J25.4.0_opticks_Debug/el9_amd64_gcc11/Mon
    export OJ_VERBOSE=1
    export OPTICKS_SETUP_VERBOSE=1  # protects against : set -eo pipefail 

    export CI_PROJECT_PATH=
    export CI_JOB_NAME_SLUG=
    export CI_JOB_STARTED_AT=
    export CI_JOB_IMAGE=
    export CI_PIPELINE_SOURCE=
    export CI_PIPELINE_URL=



/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/setup.sh::

     01 export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0
      2 export JUNOSW_NAME=junosw
      3 pushd $JUNOTOP >& /dev/null
      4     source bashrc.sh
      5 
      6     # ================== SNiPER ==================
      7     if [ -f "sniper/InstallArea/bashrc" ]; then
      8         pushd sniper/InstallArea >& /dev/null
      9         source bashrc
     10         popd >& /dev/null
     11     fi
     12 
     13     if [ -f "mt.sniper/InstallArea/bashrc" ]; then
     14         pushd mt.sniper/InstallArea >& /dev/null
     15         source bashrc
     16         popd >& /dev/null
     17     fi
     18     # ================== SNiPER ==================
     19 
     20 
     21     # setup tutorial 
     22     if [ -z "${JUNO_OFFLINE_OFF:-}" ];
     23     then
     24         if [ -f "${JUNOSW_NAME}/InstallArea/setup.sh" ]; then
     25             echo "Setup Official $JUNOSW_NAME (CMake version)"
     26             pushd $JUNOSW_NAME/InstallArea >& /dev/null
     27             source setup.sh
     28             popd >& /dev/null
     29         fi
     30     fi
     31 popd >& /dev/null


/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/InstallArea/setup.sh::

     01 #!/bin/bash
      2 # Generated by cmake 
      3 export JUNO_OFFLINE_VERSION=J25.4.0
      4 export CMAKE_PREFIX_PATH=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/InstallArea:${CMAKE_PREFIX_PATH}
      5 export PATH=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/InstallArea/bin:${PATH}
      6 export LD_LIBRARY_PATH=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/InstallArea/lib64:${LD_LIBRARY_PATH}
      7 export PYTHONPATH=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/InstallArea/lib64:${PYTHONPATH}
      8 export PYTHONPATH=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/InstallArea/python:${PYTHONPATH}
      9 
     10 export XMLOBJDESCROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/XmlObjDesc
     11 export EDMPATHROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/EDMPath
     12 export BASEEVENTROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/BaseEvent
     13 export EDMUTILROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/EDMUtil
     14 export CLHEPDICTROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/Dict/CLHEPDict
     15 export HEPMCDICTROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/Dict/HepMCDict
     16 export CONTEXTROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/Context
     17 export EVTNAVIGATORROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/EvtNavigator
     18 export GENEVENTROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/GenEvent
     19 export SIMEVENTROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/SimEvent
     20 export ELECEVENTROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/ElecEvent
     21 export ELECTRUTHROOT=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junosw/DataModel/ElecTruth
     ...




