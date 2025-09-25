#!/bin/bash

cd $(dirname $(realpath $BASH_SOURCE))
source InstallArea/envset.sh

export U4Tree__SOLID_DEBUG=1
export U4Solid__IsFlaggedName=WaterDistributer


source dbg__.sh

dbg__ $(which python) $(which tut_detsim.py) --opticks-mode 1 --evtmax 0 gun



