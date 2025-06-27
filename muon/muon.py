#!/usr/bin/env python

import os, logging, textwrap, numpy as np
from opticks.ana.fold import Fold
from opticks.sysrap.sevt import SEvt, SAB 

if __name__ == '__main__':
    a = SEvt.Load("$AFOLD", symbol="a")
    print(repr(a))
pass

