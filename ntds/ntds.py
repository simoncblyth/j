#!/usr/bin/env python

import os, numpy as np
from opticks.ana.fold import Fold
from opticks.ana.p import * 
from opticks.u4.tests.U4SimulateTest import U4SimulateTest

MODE =  int(os.environ.get("MODE", "2"))
N = int(os.environ.get("VERSION", "1"))

if MODE > 0:
    from opticks.ana.pvplt import * 
pass


if __name__ == '__main__':
    if N == -1: 
        a = U4SimulateTest.Load("$AFOLD",symbol="a")
        b = U4SimulateTest.Load("$BFOLD",symbol="b")
        t = b
        syms = ['a','b']
    elif N == 0:
        a = U4SimulateTest.Load("$AFOLD",symbol="a")
        b = None
        syms = ['a']
        t = a 
    elif N == 1:
        a = None
        b = U4SimulateTest.Load("$BFOLD",symbol="b")
        syms = ['b']
        t = b 
    else:
        assert(0)
    pass

    if not a is None:print(repr(a))
    if not b is None:print(repr(b))


    #pos = t.record[:,:,0,:3].reshape(-1,3)   # xyz : all photons, all steps


    num = 4 

    ppos_ = {}
    color = { 0:'r', 1:'g', 2:'b', 3:'c' } 

    for i in range(num): ppos_[i] = "None" ; 

    ppos_[0] = "t.f.record[:,0,0,:3] # 0-position   "
    ppos_[1] = "t.f.record[:,1,0,:3] # 1-position   "
    ppos_[2] = "t.f.record[:,2,0,:3] # 2-position   "
    ppos_[3] = "t.f.photon[:,0,:3]  # final photon position "


    elem = []
    for i in range(num): 
        if not ppos_[i] == "None": elem.append("%s:%s" % (color[i],ppos_[i]))
    pass

    ppos = {'a':{}, 'b':{} }
    for i in range(num): 
        for sym in syms:
            if sym == 'a':
                t = a
            elif sym == 'b':
                t = b
            else:
                t = None
            pass 
            ppos[sym][i] = eval(ppos_[i])
        pass
    pass



    axes = 0, 2  # X,Z
    H,V = axes


    if MODE == 0:
        print("not plotting as MODE 0  in environ")
    elif MODE == 2:

        for sym in syms:

            label = "\n".join( ["sym:%s" % sym] + elem )
            fig, axs = mpplt_plotter(label=label)
            assert len(axs) == 1
            ax = axs[0]

            #ax.set_ylim(-250,250)
            #ax.set_xlim(-500,500)

            for i in range(num): 
                if ppos[sym][i] is None: continue
                ax.scatter( ppos[sym][i][:,H], ppos[sym][i][:,V], s=1, c=color[i] )
                pass
            pass
            fig.show()
        pass



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
