initialize_geom
==================



::

    191 .opticks_test_job_template:
    192   stage: test
    193   image: simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9
    194   script:
    195     - for repo in juno.ihep.ac.cn opticks.ihep.ac.cn; do if [ ! -d /cvmfs/$repo ]; then sudo mkdir /cvmfs/$repo; fi; sudo mount -t cvmfs $repo /cvmfs/$repo; done
    196     - source InstallArea/envset.sh
    197     - oj_initialize_meshname_tessname
    198     - oj_initialize_framespec
    199     - oj_initialize_geomdir
    200     - source .gitlab-ci/oj_helper.sh MAKE_TAR
    201     - source .gitlab-ci/oj_helper.sh DEPLOY_TAR
    202 


::

    A[blyth@localhost junosw]$ cp Examples/Tutorial/share/opticks_juno.sh InstallArea/bin/

    set -eo pipefail

    source InstallArea/envset.sh


    A[blyth@localhost junosw]$ cp Examples/Tutorial/share/opticks_juno.sh InstallArea/bin/
    A[blyth@localhost junosw]$ set -eo pipefail
    A[blyth@localhost junosw]$ source InstallArea/envset.sh
    Setup Official junosw (CMake version)
    Connection to 192.168.185.246 closed.
    P[blyth@localhost ~]$ 


    

