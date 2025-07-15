
Hi Ziyan, Zhenning,

> Previously Dingyong and Haosen only test gamma and muon samples. Yesterday I
> discussed with Gaosong Li, one of the atmospheric neutrino group conveners,
> one of his student (Zhenning Qu)can join the test of the latest JUNOSW+Opticks
> release.

Excellent 

> To use the /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.0/el9_amd64_gcc11/2025_07_07, 
> produce some atmospheric neutrino MC data samples. If you recommend some other newer release, 
> please tell us.

Yes, I recommend that one at the moment. But there will be a new one soon that adds 
an envvar control which allows me to increase in OJ the clearance of the virtual wrapper from 0.05mm to 0.10mm. 
That does not need any change to Opticks. Once it is merged I will create another dated reference release
and let you know.

> BTW, I noticed that forJ25.4.0 There are several releasese corresponding to 
> different Opticks versions
> 
>     J25.4.0_Opticks-v0.4.5 
>     J25.4.0_Opticks-v0.4.6 
>     J25.4.0_Opticks-v0.4.8
>     J25.4.0_Opticks-v0.5.0
> 
> My understanding is that during the test, Opticks is updated to newer version, from 0.4.5 to 0.5.0.

That is correct.


> But why for J25.4.1 , it was still needed to be built based on Opticks v0.4.5?  
> Why just directly start from v0.5.0 ?


That was an "accidental" build from June 23rd (day after J25.4.1 was released).
From the ENV.bash in the release the CI envvars, as shown below, I can see
that the build was triggered by a merge request with build pipeline

https://code.ihep.ac.cn/JUNO/offline/junosw/-/pipelines/19828

That pipeline page reveals the MR was from user "lynn" 
with name "Skip 0 pulse amp brought by new MCP model".
My guess is that the merge request was using an older version of .gitlab-ci.yml
which specifies the J release to build against::

     27 ##############################################################################
     28 # Job Template
     29 ##############################################################################
     30 .job_template:
     31   image: junosw/base:el9
     32   variables:
     33     # JUNOTOP: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
     34     JUNOTOP: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0
     35     JUNO_CLANG_PREFIX:
     36     EXTRA_BUILD_FLAGS:
     37 

Previously JUNOTOP was using the JLatest symbolic link. But was fixed to 
J25.4.0 at the beginning of June.::

    A[blyth@localhost el9_amd64_gcc11]$ pwd
    /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.1_Opticks-v0.4.5/el9_amd64_gcc11

    A[blyth@localhost el9_amd64_gcc11]$ l
    total 3
    1 drwxrwxr-x. 3 cvmfs cvmfs  68 Jun 23 15:18 .
    1 drwxrwxr-x. 3 cvmfs cvmfs  62 Jun 23 15:18 ..
    1 -rw-r--r--. 1 cvmfs cvmfs   0 Jun 23 15:18 .cvmfscatalog
    1 lrwxrwxrwx. 1 cvmfs cvmfs   3 Jun 23 15:18 Latest -> Mon
    1 drwxr-xr-x. 7 cvmfs cvmfs 181 Jun 23 15:13 Mon


The ENV.bash captures metadata about the build::

    A[blyth@localhost el9_amd64_gcc11]$ cat Mon/ENV.bash
    #!/bin/bash
    # generated from .gitlab-ci.yml of JUNO/offline/junosw
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
    export J_VER=J25.4.1   # eg J25.2.3 NB
    export O_VER=Opticks-v0.4.5  # eg Opticks-v0.3.3
    export OJ_VER=J25.4.1_Opticks-v0.4.5  # eg J25.2.3_Opticks-v0.3.3
    export OJ_SLUG=J25_4_1_Opticks_v0_4_5  # eg J25_2_3_Opticks_v0_3_3
    export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.1
    export JUNO_OPTICKS_PREFIX=/cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.5

    export OJ_DIST=J25.4.1_Opticks-v0.4.5.tar
    export OJ_RELP=J25.4.1_Opticks-v0.4.5/el9_amd64_gcc11/Mon
    export OJ_VERBOSE=1
    export OPTICKS_SETUP_VERBOSE=1  # protects against : set -eo pipefail 

    export CI_PROJECT_PATH=JUNO/offline/junosw
    export CI_JOB_NAME_SLUG=opticks-build-job-gcc11-el9
    export CI_JOB_STARTED_AT=2025-06-23T06:37:04Z
    export CI_JOB_IMAGE=simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9
    export CI_PIPELINE_SOURCE=merge_request_event
    export CI_PIPELINE_URL=https://code.ihep.ac.cn/JUNO/offline/junosw/-/pipelines/19828

Simon 

 
