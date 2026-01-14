#!/bin/bash

usage(){ cat << EOU
oj_initialize.sh
=================

This is invoked from the root of junosw git repo
to configure and perform a test geometry conversion
and write geometry directory which is used by visualization
and debugging.

Canonical usage by gitlab runner is configured
within .gitlab-ci.yml

Note that the MAKE_TAR and DEPLOY_TAR commands
will do nothing unless the below envvars are defined
configuring the target node, folder, user ssh key etc::

    OPTICKS_DEPLOY_HOST
    OPTICKS_DEPLOY_USER
    OPTICKS_DEPLOY_FOLD
    OPTICKS_DEPLOY_KEY

These envvars are configured via the gitlab secrets
mechanism when this is run under gitlab-ci.

EOU
}


if [ -n "$JUNO_OFFLINE_BUILD_BRANCH" ]; then
    branch=$(git branch --show-current)
    envset=InstallArea/$branch/envset.sh
else
    envset=InstallArea/envset.sh
fi

source $envset

local_envset=$(dirname $envset)/local_envset.sh

if [ -f "$local_envset" ]; then
    source $local_envset
fi



vv="BASH_SOURCE PWD branch envset local_envset OPTICKS_PREFIX JUNO_OFFLINE_OFF JUNO_OFFLINE_VERSION CMAKE_PREFIX_PATH TUTORIALROOT OJ_DEBUG"
for v in $vv ; do printf "%30s : %s\n " "$v" "${!v}" ; done

if [ -z "$OJ_DEBUG" ]; then

    oj_initialize_framespec
    oj_initialize_meshname_tessname
    oj_initialize_geomdir

    source .gitlab-ci/oj_helper.sh MAKE_TAR
    source .gitlab-ci/oj_helper.sh DEPLOY_TAR

else
    oj_initialize_debug
fi



