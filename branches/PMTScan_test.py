#!/usr/bin/env python

import numpy as np
from opticks.ana.fold import Fold

if __name__ == '__main__':
    t = Fold.Load(symbol="t")
    print(repr(t))

    assert np.all( t.PMTSimParamData == t.IPMTSimParamSvc )

    for i, name in enumerate(t.times_names):
        print(" %40s : %10.2f s " % (name, t.times[i] ))
    pass
    name = "/".join(t.times_names)
    factor = t.times[0]/t.times[1]
    print(" %40s : %10.2f " % (name, factor ))

    pass
pass

