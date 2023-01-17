#!/usr/bin/env python

import numpy as np
from opticks.ana.fold import Fold

if __name__ == '__main__':
    t = Fold.Load(symbol="t")
    print(repr(t))

    assert np.all( t.PMTSimParamData == t.IPMTSimParamSvc )

     
    for i, name in enumerate(t.scantime_names):
        print(" %40s : %10.2f s " % (name, t.scantime[i] ))
    pass
    factor = t.scantime[0]/t.scantime[1]
    print(" %40s : %10.2f " % ("factor", factor ))

    pass
pass

