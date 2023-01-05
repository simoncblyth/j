#!/usr/bin/env python

import os, numpy as np

if __name__ == '__main__':
    path = os.path.expandvars("$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root")
    a = np.fromfile(path, dtype=np.uint8 )
    print(repr(a))



