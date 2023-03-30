#!/usr/bin/env python
"""
ntds_cf.py : Comparing history frequencies of two SEvt
========================================================

For the comparison to be meaningful (within reasonable statistics)
requires common input photons. 

"""
import os, numpy as np
from opticks.ana.fold import Fold
from opticks.ana.p import * 
from opticks.ana.qcf import QU,QCF,QCFZero
from opticks.sysrap.sevt import SEvt

if __name__ == '__main__':
    a = SEvt.Load("$AFOLD",symbol="a")
    b = SEvt.Load("$BFOLD",symbol="b")

    print(a)
    print(repr(a.f))
    print(b)
    print(repr(b.f))

    aq = a.q
    bq = b.q 
    assert aq.shape == bq.shape

    qcf = QCF( aq, bq, symbol="qcf")

    print(qcf.aqu)
    print(qcf.bqu)
    print(qcf)

    #qcf0 = QCFZero(qcf)
    #print(qcf0)





