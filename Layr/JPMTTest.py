#!/usr/bin/env python

import os, numpy as np
from opticks.ana.fold import Fold
import matplotlib.pyplot as plt


if __name__ == '__main__':
    t = Fold.Load("/tmp/JPMTTest", symbol="t")
    print(repr(t))

    qe = t.jpmt_qe_shape   
    if not qe is None:
        njs = qe[:,-1,-1].view(np.int64) 
        ni = len(njs)
        names = t.jpmt_qe_shape_names.lines   

        sel = slice(None)

        fig, axs = plt.subplots(1, 5, figsize=[12.8, 7.2] )
        for i in range(ni):
            nj = njs[i]
            ax = axs[i]

            en = qe[i,:nj,0]
            qt = qe[i,:nj,1] 
            sel = np.where( en < 5 )
            ax.plot( en[sel], qt[sel], label=names[i] )  
            ax.legend()
        pass

        fig.show()
    pass




