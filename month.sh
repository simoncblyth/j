#!/bin/bash -l 
usage(){ cat << EOU
month.sh
===========

::

    ~/j/month.sh   1    # Jan this year
    ~/j/month.sh -12    # Dec last year
    ~/j/month.sh -11    # Nov last year

    LOG=l ~/j/month.sh 11

EOU
}

SDIR=$(dirname $(realpath $BASH_SOURCE)) ~/opticks/month.sh $*



