#!/usr/bin/env python
"""
ntds_cfh.py : Comparing history frequencies of two SEvt
========================================================

For the comparison to be meaningful (within reasonable statistics)
requires common input photons. 

"""
import os, numpy as np
from opticks.sysrap.sevt import SEvt, SAB

MODE =  int(os.environ.get("MODE", "2"))
if MODE in [2,3]:
    from opticks.ana.pvplt import * 
pass


if __name__ == '__main__':
    a = SEvt.Load("$AFOLD",symbol="a")
    b = SEvt.Load("$BFOLD",symbol="b")
    ab = SAB(a,b)
    print(repr(ab))


    syms = ['a','b']

    qwn_ = "%(sym)s.f.photon[:,0,3]  # all photons "  
    bins_ = "np.linspace(3, 15, 50)"    

    bins = eval(bins_)

    lab = dict()
    qwn = dict()
    his = dict()

    for sym in syms:
        lab[sym] = qwn_ % locals()
        qwn[sym] = eval( qwn_ % locals() )
        his[sym] = np.histogram(qwn[sym],bins ) 
    pass

    label = qwn_ % dict(sym="".join(syms)) 
    pl = mpplt_plotter(label=label, equal=False)
    fig, axs = pl
    assert len(axs) == 1
    ax = axs[0]

    for sym in syms:
        ax.plot( bins[:-1], his[sym][0], label=lab[sym], drawstyle="steps-post" )
    pass

    ax.legend()
    fig.show()
    
  


