gitlab_runner_setup
====================

Thinking about integration with gitlab-CI
--------------------------------------------

I am using gitlab CI for opticks + JUNOSW build testing using non-GPU nodes.
For deeper testing I want to use the GPU workstation on my desk to run
scheduled gitlab-ci tests.  Can you give an overview of how tests on external
nodes can work with gitlab CI ? Or would it be easier to operate independently
of gitlab CI, and just run cron jobs based on code installed onto cvmfs ?


Gemini
~~~~~~


https://docs.gitlab.com/runner/install/
https://docs.gitlab.com/runner/install/linux-repository/

https://docs.gitlab.com/runner/faq/


::

    A[blyth@localhost oj]$ rpm -ql gitlab-runner
    /usr/bin/gitlab-ci-multi-runner
    /usr/bin/gitlab-runner
    /usr/lib/.build-id
    /usr/lib/.build-id/f3
    /usr/lib/.build-id/f3/f963eceba9c627280b66fc5abb0ba6536df9f2
    /usr/share/gitlab-runner/clear-docker-cache
    /usr/share/gitlab-runner/post-install
    /usr/share/gitlab-runner/pre-remove


    A[blyth@localhost oj]$ gitlab-runner -h
    NAME:
       gitlab-runner - a GitLab Runner

    USAGE:
       gitlab-runner [global options] command [command options] [arguments...]

    VERSION:
       18.3.1 (5a021a1c)

    AUTHOR:
       GitLab Inc. <support@gitlab.com>

    COMMANDS:
       list                  List all configured runners
       run                   run multi runner service
       register              register a new runner
       reset-token           reset a runner's token
       install               install service
       uninstall             uninstall service
       start                 start service
       stop                  stop service
       restart               restart service
       status                get status of a service
       run-single            start single runner
       unregister            unregister specific runner
       verify                verify all registered runners
       wrapper               start multi runner service wrapped with gRPC manager server
       fleeting              manage fleeting plugins
       artifacts-downloader  download and extract build artifacts (internal)
       artifacts-uploader    create and upload build artifacts (internal)
       cache-archiver        create and upload cache artifacts (internal)
       cache-extractor       download and extract cache artifacts (internal)
       cache-init            changed permissions for cache paths (internal)
       health-check          check health for a specific address
       proxy-exec            execute internal commands (internal)
       read-logs             reads job logs from a file, used by kubernetes executor (internal)
       help, h               Shows a list of commands or help for one command

    GLOBAL OPTIONS:
       --cpuprofile value           write cpu profile to file [$CPU_PROFILE]
       --debug                      debug mode [$RUNNER_DEBUG]
       --log-format value           Choose log format (options: runner, text, json) [$LOG_FORMAT]
       --log-level value, -l value  Log level (options: debug, info, warn, error, fatal, panic) [$LOG_LEVEL]
       --help, -h                   show help
       --version, -v                print the version




::

    A[blyth@localhost oj]$ systemctl status gitlab-runner.service
    ● gitlab-runner.service - GitLab Runner
         Loaded: loaded (/etc/systemd/system/gitlab-runner.service; enabled; preset: disabled)
         Active: active (running) since Wed 2025-12-10 10:45:56 CST; 3 months 27 days ago
       Main PID: 2289 (gitlab-runner)
          Tasks: 27 (limit: 1638992)
         Memory: 87.4M (peak: 102.0M)
            CPU: 24min 59.761s
         CGroup: /system.slice/gitlab-runner.service
                 └─2289 /usr/bin/gitlab-runner run --config /etc/gitlab-runner/config.toml --working-directory /home/gitlab-runner --service gitlab-runner --user gitlab-runner

    Dec 10 10:45:56 localhost.localdomain systemd[1]: Started GitLab Runner.
    Dec 10 10:45:57 localhost.localdomain gitlab-runner[2289]: Runtime platform                                    arch=amd64 os=linux pid=2289 revision=5a021a1c version=18.3.1
    Dec 10 10:45:57 localhost.localdomain gitlab-runner[2289]: Starting multi-runner from /etc/gitlab-runner/config.toml...  builds=0 max_builds=0
    Dec 10 10:45:57 localhost.localdomain gitlab-runner[2289]: Running in system-mode.                           
    Dec 10 10:45:57 localhost.localdomain gitlab-runner[2289]:                                                   
    Dec 10 10:45:57 localhost.localdomain gitlab-runner[2289]: Usage logger disabled                               builds=0 max_builds=1
    Dec 10 10:45:57 localhost.localdomain gitlab-runner[2289]: Configuration loaded                                builds=0 max_builds=1
    Dec 10 10:45:57 localhost.localdomain gitlab-runner[2289]: listen_address not defined, metrics & debug endpoints disabled  builds=0 max_builds=1
    Dec 10 10:45:57 localhost.localdomain gitlab-runner[2289]: [session_server].listen_address not defined, session endpoints disabled  builds=0 max_builds=1
    Dec 10 10:45:57 localhost.localdomain gitlab-runner[2289]: Initializing executor providers                     builds=0 max_builds=1
    A[blyth@localhost oj]$ 




sudo gitlab-runner list
------------------------

::

    A[blyth@localhost oj]$ sudo gitlab-runner list
    [sudo] password for blyth: 
    Runtime platform                                    arch=amd64 os=linux pid=3704414 revision=5a021a1c version=18.3.1
    Listing configured runners                          ConfigFile=/etc/gitlab-runner/config.toml
    A[blyth@localhost oj]$ 


    A[blyth@localhost oj]$ sudo cat /etc/gitlab-runner/config.toml
    concurrent = 1
    check_interval = 0
    shutdown_timeout = 0

    [session_server]
      session_timeout = 1800
    A[blyth@localhost oj]$ 


gitlab runner token
---------------------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/settings/ci_cd



register gitlab runner with organization instance
--------------------------------------------------

::

    sudo gitlab-runner register



GitLab instance URL:  https://code.ihep.ac.cn

Authentication Token: Paste the glrt-... token you just generated.

Description: Give it a name like YourName-GPU-Desk.

Executor: Type shell (since you need direct access to your local CUDA/CVMFS environment).




::

    A[blyth@localhost junosw]$ sudo gitlab-runner register  --url https://code.ihep.ac.cn  --token glrt-t3_yy1N_pfwY7sbJHBjsgYQ
    [sudo] password for blyth: 
    Runtime platform                                    arch=amd64 os=linux pid=3705643 revision=5a021a1c version=18.3.1
    Running in system-mode.                            
                                                       
    Enter the GitLab instance URL (for example, https://gitlab.com/):
    [https://code.ihep.ac.cn]: 
    Verifying runner... is valid                        correlation_id=01KNP41028MW28Y38Z27X4EPJY runner=yy1N_pfwY
    Enter a name for the runner. This is stored only in the local config.toml file:
    [localhost.localdomain]: Opticks GPU
    Enter an executor: docker, docker+machine, instance, shell, ssh, parallels, docker-windows, kubernetes, docker-autoscaler, custom, virtualbox:
    shell
    Runner registered successfully. Feel free to start it, but if it's running already the config should be automatically reloaded!
     
    Configuration (with the authentication token) was saved in "/etc/gitlab-runner/config.toml" 
    A[blyth@localhost junosw]$ 





    A[blyth@localhost junosw]$ sudo cat /etc/gitlab-runner/config.toml
    concurrent = 1
    check_interval = 0
    connection_max_age = "15m0s"
    shutdown_timeout = 0

    [session_server]
      session_timeout = 1800

    [[runners]]
      name = "Opticks GPU"
      url = "https://code.ihep.ac.cn"
      id = 1647
      token = "glrt-t3_yy1N_pfwY7sbJHBjsgYQ"
      token_obtained_at = 2026-04-08T08:40:59Z
      token_expires_at = 0001-01-01T00:00:00Z
      executor = "shell"
      [runners.cache]
        MaxUploadedArchiveSize = 0
        [runners.cache.s3]
        [runners.cache.gcs]
        [runners.cache.azure]
    A[blyth@localhost junosw]$ 



* https://code.ihep.ac.cn/JUNO/offline/junosw/-/runners/1647


::

    A[blyth@localhost junosw]$ sudo gitlab-runner list
    [sudo] password for blyth: 
    Runtime platform                                    arch=amd64 os=linux pid=3706186 revision=5a021a1c version=18.3.1
    Listing configured runners                          ConfigFile=/etc/gitlab-runner/config.toml
    Opticks GPU                                         Executor=shell Token=glrt-t3_yy1N_pfwY7sbJHBjsgYQ URL=https://code.ihep.ac.cn
    A[blyth@localhost junosw]$ 


check "gitlab-runner" user privileges
---------------------------------------

::

    A[blyth@localhost junosw]$ sudo -U gitlab-runner -l
    [sudo] password for blyth: 
    User gitlab-runner is not allowed to run sudo on localhost.

    A[blyth@localhost junosw]$ sudo -u gitlab-runner touch /data1/blyth/hello
    touch: cannot touch '/data1/blyth/hello': Permission denied


    [blyth@localhost oj]$ sudo -u gitlab-runner ls -l /dev/nvidia*
    [sudo] password for blyth: 
    crw-rw-rw-. 1 root root 195,   0 Dec 10 10:45 /dev/nvidia0
    crw-rw-rw-. 1 root root 195, 255 Dec 10 10:45 /dev/nvidiactl
    crw-rw-rw-. 1 root root 195, 254 Dec 10 10:46 /dev/nvidia-modeset
    crw-rw-rw-. 1 root root 508,   0 Dec 10 10:51 /dev/nvidia-uvm
    crw-rw-rw-. 1 root root 508,   1 Dec 10 10:51 /dev/nvidia-uvm-tools

    /dev/nvidia-caps:
    total 0
    cr--------. 1 root root 511, 1 Dec 10 10:51 nvidia-cap1
    cr--r--r--. 1 root root 511, 2 Dec 10 10:51 nvidia-cap2
    A[blyth@localhost oj]$ 



    A[blyth@localhost junosw]$ sudo -u gitlab-runner ls -alst /cvmfs/opticks.ihep.ac.cn/
    total 8
    1 drwxrwxr-x. 6 cvmfs cvmfs  231 Jun  6  2025 external
    1 drwxrwxr-x. 3 cvmfs cvmfs   30 Jun  6  2025 oj
    1 drwxrwxr-x. 3 cvmfs cvmfs   30 Jun  6  2025 ok
    1 drwxrwxr-x. 5 cvmfs cvmfs   35 Jun  6  2025 .opticks
    1 drwxrwxr-x. 6 cvmfs cvmfs  111 Jun  6  2025 opticks_download_cache
    1 -rw-rw-r--. 1 cvmfs cvmfs   24 Jun  6  2025 .cvmfsdirtab
    1 -rw-r--r--. 1 cvmfs cvmfs   48 Apr 25  2019 new_repository
    5 drwxr-xr-x. 7 cvmfs cvmfs 4096 Apr 25  2019 .
    A[blyth@localhost junosw]$ sudo -u gitlab-runner ls -alst /cvmfs/juno.ihep.ac.cn/
    total 15
    1 drwxrwxr-x.  4 cvmfs cvmfs   29 Jan 17 19:16 el9_amd64_gcc15
    1 drwxrwxr-x.  3 cvmfs cvmfs   26 Dec 25 19:22 tao-dbdata
    1 -rw-rw-r--.  1 cvmfs cvmfs  128 Jul 10  2025 .cvmfsdirtab
    1 drwxrwxr-x.  5 cvmfs cvmfs   29 Jul 10  2025 el9_amd64_gcc11
    1 drwxrwxr-x.  4 cvmfs cvmfs   28 Jun 28  2025 singularity
    1 drwxrwxr-x.  3 cvmfs cvmfs   26 Feb  3  2025 dbdata
    1 drwxr-xr-x.  9 cvmfs cvmfs   75 Dec 11  2024 docutil
    1 drwxrwxr-x.  5 cvmfs cvmfs   29 Jun 13  2024 centos7_amd64_gcc1120
    1 drwxrwxr-x.  7 cvmfs cvmfs   30 Jan  5  2024 sw
    1 drwxrwxr-x.  3 cvmfs cvmfs   33 Dec 18  2023 centos7_amd64_gcc1120_opticks
    1 drwxrwxr-x.  4 cvmfs cvmfs   29 Dec  1  2021 centos7_amd64_gcc830
    1 drwxrwxr-x.  3 cvmfs cvmfs   33 Jun  4  2020 sl7_amd64_gcc485
    1 drwxrwxr-x.  4 cvmfs cvmfs   28 Jun  2  2020 ci
    1 drwxrwxr-x.  4 cvmfs cvmfs   52 May 13  2020 sl6_amd64_gcc447
    1 drwxrwxr-x.  4 cvmfs cvmfs   29 Apr 28  2020 sl6_amd64_gcc830
    1 drwxrwxr-x.  4 cvmfs cvmfs   29 Nov 27  2019 sl6_amd64_gcc494
    1 drwxrwxr-x.  9 cvmfs cvmfs  162 Jun 28  2019 sl6_amd64_gcc44
    1 drwxrwxr-x.  3 cvmfs cvmfs   29 Jun 25  2019 sl7_amd64_gcc48
    1 drwxrwxr-x.  4 cvmfs cvmfs   58 Mar 22  2017 sl5_amd64_gcc41
    1 -rw-r--r--.  1 cvmfs cvmfs   45 Mar 27  2015 new_repository
    5 drwxr-xr-x. 20 cvmfs cvmfs 4096 Mar 27  2015 .
    A[blyth@localhost junosw]$ 





setup .gitlab-ci.yml
------------------------

::

    gpu_test_job:
      tags:
        - gpu-workstation  # Only runs on your desk machine
      script:
        - source /cvmfs/juno.ihep.ac.cn/sl6/setup.sh  # Setup environment
        - opticks-test                                # Run your GPU tests
      only:
        - schedules                                   # Only run when scheduled




    stages:
      - test

    gpu_hello_world:
      stage: test
      tags:
        - opticks-gpu  # Matches the tag you registered
      script:
        - hostname
        - whoami
        - nvidia-smi   # Verify GPU visibility
        - nvcc --version || echo "CUDA compiler not in PATH"
        - echo "Opticks environment check..."
        - if [ -n "$OPTICKS_HOME" ]; then echo "Opticks is at $OPTICKS_HOME"; else echo "Opticks not found"; fi




actually : makes more sense to do this in OJ repo
----------------------------------------------------

* https://code.ihep.ac.cn/blyth/oj
* https://code.ihep.ac.cn/blyth/oj/-/settings/ci_cd#js-runners-settings
* https://docs.gitlab.com/ci/



getting oj.bash to work in .gitlab-ci.yml
--------------------------------------------

HMM: for gitlab artifacts to worl the LOGDIR needs to be inside build directory ?

artifacts:
  paths:
    - $LOGDIR/  # Note: This only works if LOGDIR is inside the build directory.
  when: always



actually decide best to directly use the TESTSCRIPT
-----------------------------------------------------


OJ with gitlab-runner shakedown
--------------------------------

::

    sdirectory::DirList FAILED TO OPEN DIR /home/gitlab-runner/.opticks/rngcache/RNG



    ok) A[blyth@localhost oj]$ opticks-f sdirectory::Dir
    ./sysrap/SCurandChunk.h:    sdirectory::DirList( names, dir, PREFIX, EXT ); 
    ./sysrap/tests/sdirectory_test.cc:    sdirectory::DirList(names, path, pfx, ext ); 
    ./sysrap/sdirectory.h:inline std::string sdirectory::DirName( const char* filepath )
    ./sysrap/sdirectory.h:sdirectory::DirList
    ./sysrap/sdirectory.h:inline void sdirectory::DirList( std::vector<std::string>& names, const char* path, const char* pfx, const char* ext)
    ./sysrap/sdirectory.h:    if(!dir) std::cout << "sdirectory::DirList FAILED TO OPEN DIR " << ( path ? path : "-" ) << std::endl ; 
    ./sysrap/sdirectory.h:        << "sdirectory::DirList" 
    (ok) A[blyth@localhost opticks]$ 


    (ok) A[blyth@localhost opticks]$ opticks-f sdirectory.h
    ./CSG/CSGGeometry.cc:#include "sdirectory.h"
    ./qudarap/QRng.cc:#include "sdirectory.h"
    ./qudarap/QU.cc:#include "sdirectory.h"
    ./sysrap/CMakeLists.txt:    sdirectory.h
    ./sysrap/SEventConfig.cc:#include "sdirectory.h"
    ./sysrap/SEvt.cc:#include "sdirectory.h"
    ./sysrap/SIMG.h:#include "sdirectory.h"
    ./sysrap/SCurandChunk.h:#include "sdirectory.h"
    ./sysrap/sdevice.h:#include "sdirectory.h"
    ./sysrap/spath.h:#include "sdirectory.h"
    ./sysrap/tests/SPPMTest.cc:#include "sdirectory.h"
    ./sysrap/tests/S_freopen_redirect_test.cc:#include "sdirectory.h"
    ./sysrap/tests/sdirectory_test.cc:#include "sdirectory.h"
    ./sysrap/tests/SEvtTest.cc:#include "sdirectory.h"
    ./sysrap/tests/spath_test.cc:#include "sdirectory.h"
    ./sysrap/SCurandStateMonolithic.cc:#include "sdirectory.h"
    ./u4/U4GDML.h:#include "sdirectory.h"
    (ok) A[blyth@localhost opticks]$ 

See ~/opticks/notes/issues/fix_unexpected_empty_SEvt_dir_creation.rst


OJ3 with gitlab-runner shakedown
-----------------------------------

Probably will fail to load input photons ?::

    A[gitlab-runner@localhost oj]$ export TESTSCRIPT=oj3/oj3.sh TEST=inputphoton ENVSET_NAME=OJ_LOCAL ENVSET_VERBOSE=1 SEvt__MINIMAL=1 ; $TESTSCRIPT dbg

YEP, but fixed with envvar.


OJ3/chi2 using the LAST link ?
--------------------------------

::

    A[gitlab-runner@localhost oj]$ export TESTSCRIPT=oj3/oj3.sh TEST=inputphoton ENVSET_NAME=OJ_LOCAL ENVSET_VERBOSE=1 SEvt__INPUT_PHOTON_DIR=/home/blyth/.opticks/InputPhotons ; $TESTSCRIPT chi2

twas bug in TEST.sh plus need to set ISTAMP=LAST, worked::

    A[gitlab-runner@localhost oj]$ export TESTSCRIPT=oj3/oj3.sh TEST=inputphoton ENVSET_NAME=OJ_LOCAL ENVSET_VERBOSE=1 ISTAMP=LAST ; $TESTSCRIPT chi2

TODO: check that bad chi2 causes the test to fail when run under gitlab-ci

run_chi2 doesnt need ISTAMP::

    export TESTSCRIPT=oj3/oj3.sh TEST=inputphoton ENVSET_NAME=OJ_LOCAL ENVSET_VERBOSE=1 ; $TESTSCRIPT run_chi2




how to monitor gitlab-ci pipeline metrics
------------------------------------------

* https://docs.gitlab.com/ci/testing/metrics_reports/
* https://prometheus.io/docs/specs/om/open_metrics_spec/


::

    # HELP sim_duration_seconds Time spent in the C++ simulation loop
    # TYPE sim_duration_seconds gauge
    sim_duration_seconds{test="gun_shakedown"} 42.5



gitlab-ci artifacts/reports/junit
------------------------------------

::

    artifacts:
      reports:
        junit: report.xml



junit
------

* https://docs.gitlab.com/ci/testing/unit_test_reports/



gitlab-ci artifacts/reports/metrics
------------------------------------

* Your script should create a file (e.g., metrics.txt) using the Prometheus line protocol:

::

    opticks_test:
      script:
        - ./run_sim.sh > raw_output.log
        - # Extract time from log and format into metrics.txt
        - SIM_TIME=$(grep "Total Time" raw_output.log | awk '{print $3}')
        - echo "simulation_time_seconds $SIM_TIME" > metrics.txt
      artifacts:
        reports:
          metrics: metrics.txt




