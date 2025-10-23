#!/usr/bin/env bash

usage(){ cat << EOU
scp_from_O.sh
=============

Primary home of these scripts is the cvmfs stratum-zero node for /cvmfs/opticks.ihep.ac.cn

This script scp them from there to here for safe keeping in j

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

scp O:peek.sh .
scp O:oj_deploy_to_cvmfs.sh .
scp O:ok_deploy_to_cvmfs.sh .
scp O:oj_reference_deploy_to_cvmfs.sh .





