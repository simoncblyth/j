#!/usr/bin/env python
"""
ntds_cf.py : Comparing history frequencies of two SEvt
========================================================

For the comparison to be meaningful (within reasonable statistics)
requires common input photons. 

"""
import os, numpy as np
from opticks.sysrap.sevt import SEvt, SAB

if __name__ == '__main__':
    a = SEvt.Load("$AFOLD",symbol="a")
    b = SEvt.Load("$BFOLD",symbol="b")
    ab = SAB(a,b)
    print(repr(ab))


