#!/bin/bash -l 

usage(){ cat << EOU
month.sh
===========

::

    j 
    ./month.sh   1    # Jan this year
    ./month.sh -12    # Dec last year
    ./month.sh -11    # Nov last year

EOU
}

~/opticks/month.sh $*



