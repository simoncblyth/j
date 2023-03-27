#!/usr/bin/env python

import os, numpy as np
from opticks.ana.fold import Fold
from opticks.ana.p import * 
from opticks.u4.tests.U4SimulateTest import U4SimulateTest
from opticks.ana.qcf import QU,QCF,QCFZero

if __name__ == '__main__':
    a = U4SimulateTest.Load("$AFOLD",symbol="a")
    b = U4SimulateTest.Load("$BFOLD",symbol="b")

    # HMM: different photon counts ?
    aq = a.q[:8000] 
    bq = b.q[:8000] 

    qcf = QCF(aq,bq, symbol="qcf")

    print(qcf.aqu)
    print(qcf.bqu)
    print(qcf)

    #qcf0 = QCFZero(qcf)
    #print(qcf0)





