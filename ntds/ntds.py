#!/usr/bin/env python

import os, numpy as np
from opticks.ana.fold import Fold
from opticks.ana.p import * 
from opticks.u4.tests.U4SimulateTest import U4SimulateTest

MODE =  int(os.environ.get("MODE", "2"))
N = int(os.environ.get("N", "0"))

if MODE > 0:
    from opticks.ana.pvplt import * 
pass


if __name__ == '__main__':
    if N == -1: 
        a = U4SimulateTest.Load("$AFOLD",symbol="a")
        b = U4SimulateTest.Load("$BFOLD",symbol="b")
        syms = ['a','b']
    elif N == 0:
        a = U4SimulateTest.Load("$FOLD",symbol="a")
        b = None
        syms = ['a']
    elif N == 1:
        a = None
        b = U4SimulateTest.Load("$FOLD",symbol="b")
        syms = ['b']
    else:
        assert(0)
    pass

    if not a is None:print(repr(a))
    if not b is None:print(repr(b))

    t = a.f 


    #pos = t.record[:,:,0,:3].reshape(-1,3)   # xyz : all photons, all steps


    ppos_ = {}
    color = {}

    ppos_[0] = "None"
    #ppos_[0] = "t.record[:,0,0,:3] # 0-position   "
    color[0] = "r" 

    ppos_[1] = "None"
    #ppos_[1] = "t.record[:,1,0,:3] # 1-position   "
    color[1] = "g" 

    ppos_[2] = "None"
    #ppos_[2] = "t.record[:,2,0,:3] # 2-position   "
    color[2] = "b" 

    #ppos_[3] = "None"
    ppos_[3] = "t.photon[:,0,:3]"
    color[3] = "c" 
    num = 4 

    ppos = {}
    elem = []

    for i in range(num): 
        ppos[i] = eval(ppos_[i])
        if not ppos[i] is None: elem.append("%s:%s" % (color[i],ppos_[i]))
    pass
    label = "\n".join(elem)


    axes = 0, 2  # X,Z
    H,V = axes


    if MODE == 0:
        print("not plotting as MODE 0  in environ")
    elif MODE == 2:
        fig, axs = mpplt_plotter(label=label)
        assert len(axs) == 1
        ax = axs[0]

        #ax.set_ylim(-250,250)
        #ax.set_xlim(-500,500)

        for i in range(num): 
            if ppos[i] is None: continue
            ax.scatter( ppos[i][:,H], ppos[i][:,V], s=1, c=color[i] )
        pass

        fig.show()
    elif MODE == 3:
        pl = pvplt_plotter(label)
        os.environ["EYE"] = "0,100,165"
        os.environ["LOOK"] = "0,0,165"
        pvplt_viewpoint(pl)

        for i in range(num): 
            if ppos[i] is None: continue
            pl.add_points(ppos[i], color=color[i] )
        pass

        pl.show()
    pass




pass
