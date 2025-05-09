#!/bin/bash
source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.1/el9_amd64_gcc11/Mon/envset.sh
echo $OPTICKS_PREFIX
export HOME=/hpcfs/juno/junogpu/yangdingyong
export TMP=/hpcfs/juno/junogpu/yangdingyong/datas/test/2025_05_06/tmp
export C2CUT=200
export AFOLD=/hpcfs/juno/junogpu/yangdingyong/datas/test/2025_05_06/tmp/GEOM/J25_3_0_Opticks_v0_4_1/python3.11/ALL0_no_opticks_event_name/A000
export BFOLD=/hpcfs/juno/junogpu/yangdingyong/datas/test/2025_05_06/tmp/GEOM/J25_3_0_Opticks_v0_4_1/python3.11/ALL0_no_opticks_event_name/B000

$OPTICKS_PREFIX/bin/sseq_index_test.sh

