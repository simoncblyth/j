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
import matplotlib.pyplot as mp
from opticks.ana.fold import Fold

if __name__ == '__main__':
    t = Fold.Load(symbol="t")
    print(repr(t))
    print(np.unique(t.a[:,1], return_counts=True))

    w0 = np.where( t.b[:,1] == 0 )[0]
    w1 = np.where( t.b[:,1] == 1 )[0]
    w3 = np.where( t.b[:,1] == 3 )[0]

    p0 = t.b[w0,0]
    p1 = t.b[w1,0]
    p3 = t.b[w3,0]


    fig, axs = mp.subplots(3) 

    for i in range(100):
        for k,ax in enumerate(axs):        

            if k == 0:
                pmtid = p0[i]
            elif k == 1:
                pmtid = p1[i]
            elif k == 2:
                pmtid = p3[i]
            else:
                pmtid = -1 
            pass

            ax.plot( t.a[pmtid,:,0], t.a[pmtid, :,2] )
        pass
    pass

    fig.show()
     




pass
