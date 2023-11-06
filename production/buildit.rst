buildit
=========

::

    cat /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b/build-tools/build.sh  


::

    ...

    function buildit() {
        check-writable

        prepare-workdir
        goto-workdir

        prepare-envvar

        checkout-offline

        build-offline

        prepare-setupscripts

        goback-from-workdir

        create-latest-link
    }

    ##############################################################################
    # DEPLOY IN CVMFS PUBLISHER
    ##############################################################################
    #
    # Note:
    #      It turns out that the script could not be invoked at deploy stage.
    #      Because when cvmfs_server publish the repositoy, the files under this
    #      repository can not be opened. 
    #
    #      In order to solve this problem, the solution is creating the commands
    #      on the fly, then use bash to invoke it:
    #
    #          bash <<< "$(bash /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b/build-tools/build.sh deployit)"
    #
    #-----------------------------------------------------------------------------

    function deployit() {
    cat <<EOF
        cvmfs_server transaction juno_nightlies.ihep.ac.cn
        /cvmfs/container.ihep.ac.cn/bin/hep_container exec CentOS7 $self
        cvmfs_server publish -m "nightly build $(date)" juno_nightlies.ihep.ac.cn
    EOF
    }

    ##############################################################################
    # MAIN
    ##############################################################################

    if [ -z "$*" ]; then
        buildit
    else
        $*
    fi

