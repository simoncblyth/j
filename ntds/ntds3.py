#!/usr/bin/env python

import numpy as np
from opticks.sysrap.sevt import SEvt

if __name__ == '__main__':
    a = SEvt.Load("$AFOLD", symbol="a")
    b = SEvt.Load("$BFOLD", symbol="b")

    print(repr(a))
    print(repr(b))
pass
   

