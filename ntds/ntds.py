#!/usr/bin/env python
"""
ntds.py : plotting two SEvt
============================

::

    MODE=2 ./ntds.sh ana
    MODE=3 ./ntds.sh ana

"""
import os, numpy as np
from opticks.ana.fold import Fold
from opticks.ana.p import * 

from opticks.ana.base import PhotonCodeFlags
pcf = PhotonCodeFlags() 
fln = pcf.fln
fla = pcf.fla


from opticks.sysrap.sevt import SEvt
## HMM: when using to plot results of ntds the U4SimulateTest name seems inappropriate 
## Its really a higher level wrapper for an Opticks SEvt folder of arrays (CHECK THIS)
## MAYBE call it opticks.sysrap.SEvt ?

MODE =  int(os.environ.get("MODE", "2"))
N = int(os.environ.get("VERSION", "1"))
GLOBAL = int(os.environ.get("GLOBAL","0")) == 1 
SLIM = float(os.environ.get("SLIM","1.0"))
CHECK = os.environ.get("CHECK", "all_point" )

if MODE > 0:
    from opticks.ana.pvplt import * 
pass


if __name__ == '__main__':
    axes = 0,2  # X,Z
    H,V = axes
    lim = np.array([[-500.,500.],[-250.,250.],[-250.,250.]])
    lim *= SLIM

    if N == -1: 
        a = SEvt.Load("$AFOLD",symbol="a")
        b = SEvt.Load("$BFOLD",symbol="b")
        t = b
        syms = ['a','b']
        u4st = [ a, b ]
    elif N == 0:
        a = SEvt.Load("$AFOLD",symbol="a")
        b = None
        syms = ['a']
        u4st = [ a,]
        t = a 
    elif N == 1:
        a = None
        b = SEvt.Load("$BFOLD",symbol="b")
        syms = ['b']
        u4st = [ b,]
        t = b 
    else:
        assert(0)
    pass

    if not a is None:print(repr(a))
    if not b is None:print(repr(b))


    # B: SD that are EPH_NEDEP and hence not included into hit collection
    w =  np.where(np.logical_and( b.eph == 3, b.qq == 7 ))

    w_gpos = np.ones( [len(w[0]), 4])  
    w_gpos[:,:3] = b.f.record[w][:,:,0][:,:3] 
    w_lpos = np.dot( w_gpos, b.f.sframe.w2m ) 

    
    z_gpos = np.ones( [b.n[0], 4])  
    z_gpos[:,:3] = b.f.record[0,:b.n[0],0][:,:3] 
    z_lpos = np.dot( z_gpos, b.f.sframe.w2m ) 




    num = 4 
    color = { 0:'r', 1:'g', 2:'b', 3:'c' } 

    ppos_ = {}

    for i in range(num): ppos_[i] = "None" ; 

    if CHECK == "all_point":
        ppos_[0] = "t.f.record[:,:,0,:3].reshape(-1,3)  # all points "
    elif CHECK == "few_point":
        ppos_[0] = "t.f.record[:,0,0,:3] # 0-position   "
        ppos_[1] = "t.f.record[:,1,0,:3] # 1-position   "
        ppos_[2] = "t.f.record[:,2,0,:3] # 2-position   "
        ppos_[3] = "t.f.photon[:,0,:3]  # final photon position "
    pass 

    elem = []
    for j in range(num): 
        if not ppos_[j] == "None": elem.append("%s:%s" % (color[j],ppos_[j]))
    pass

    ppos = {'a':{}, 'b':{} }
    for i in range(len(syms)):
        u4s = u4st[i]
        sym = syms[i]
        t = u4s 
        for j in range(num): 
            ppos[sym][j] = eval(ppos_[j])
        pass
    pass

    assert len(syms) == len(u4st)
    for i in range(len(syms)):
        u4s = u4st[i]
        sym = syms[i]
        label = "\n".join( ["sym:%s CHECK:%s" % (sym, CHECK)] + elem )

        if MODE == 0:
            print("not plotting as MODE 0  in environ")
        elif MODE in [2,3]:

            if MODE == 2:            
                pl = mpplt_plotter(label=label)
                fig, axs = pl
                assert len(axs) == 1
                ax = axs[0]
            elif MODE == 3:
                pl = pvplt_plotter(label)
                os.environ["EYE"] = "0,100,165"
                os.environ["LOOK"] = "0,0,165"
                pvplt_viewpoint(pl)
            pass

            if not GLOBAL:
                if MODE == 2:
                    ax.set_xlim(*lim[H]) 
                    ax.set_ylim(*lim[V])
                elif MODE == 3:
                    pass
                pass
            pass

            for i in range(num): 
                if ppos[sym][i] is None: continue
                gpos = np.ones( [len(ppos[sym][i]), 4 ])
                gpos[:,:3] = ppos[sym][i] 
                lpos = np.dot( gpos, u4s.f.sframe.w2m ) 
                upos = gpos if GLOBAL else lpos

                if MODE == 2:
                    ax.scatter( upos[:,H], upos[:,V], s=1, c=color[i] )
                elif MODE == 3:
                    pl.add_points(upos[:,:3], color=color[i] )
                pass
            pass

            if MODE == 2:
                fig.show()
            elif MODE == 3:
                pl.show()
            pass
        pass
    pass
pass


