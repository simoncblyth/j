#!/usr/bin/env python

"""
In [9]: t.b[w1][:,1].min(), t.b[w1][:,1].max()
Out[9]: (0.8424670509593786, 1.2424223972287622)

In [10]: t.b[w0][:,1].min(), t.b[w0][:,1].max()
Out[10]: (1.0888638290385013, 1.5461794391925394)

In [11]: t.b[w1][:,1].min(), t.b[w1][:,1].max()
Out[11]: (0.8424670509593786, 1.2424223972287622)

In [12]: t.b[w3][:,1].min(), t.b[w3][:,1].max()
Out[12]: (1.0433244916003537, 1.5862681379922758)

"""

import numpy as np
from opticks.ana.fold import Fold

if __name__ == '__main__':
    t = Fold.Load(symbol="t")
    print(repr(t))
    print(np.unique(t.a[:,1], return_counts=True))

    w0 = np.where( t.a[:,1] == 0 )
    w1 = np.where( t.a[:,1] == 1 )
    w3 = np.where( t.a[:,1] == 3 )


pass
