#!/usr/bin/env python

import os, logging, numpy as np

print("[from opticks.sysrap.sevt import SEvt, SAB")
from opticks.sysrap.sevt import SEvt, SAB
print("]from opticks.sysrap.sevt import SEvt, SAB")

from opticks.ana.p import cf  

log = logging.getLogger(__name__)

GLOBAL = int(os.environ.get("GLOBAL","0")) == 1
MODE = int(os.environ.get("MODE","3")) 
PICK = os.environ.get("PICK","CF") 
SEL = int(os.environ.get("SEL","0")) 

AIDX = int(os.environ.get("AIDX","0")) 
BIDX = int(os.environ.get("BIDX","0")) 



if MODE in [2,3]:
    from opticks.ana.pvplt import *   
    # HMM this import overrides MODE, so need to keep defaults the same 
pass

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    print("GLOBAL:%d MODE:%d SEL:%d" % (GLOBAL,MODE, SEL))

    a = SEvt.Load("$AFOLD", symbol="a")
    b = SEvt.Load("$BFOLD", symbol="b")

    print(repr(a))
    print(repr(b))

    ahit_ = a.f.hit[:,1,3].view(np.int32)   ## iindex
    bhit_ = b.f.hit[:,1,3].view(np.int32)  

    ahid_ = a.f.hit[:,3,1].view(np.int32)   ## identity
    bhid_ = b.f.hit[:,3,1].view(np.int32)

    ahit = np.c_[np.unique( ahit_, return_counts=True )] 
    bhit = np.c_[np.unique( bhit_, return_counts=True )] 

    ahid = np.c_[np.unique( ahid_, return_counts=True )]
    bhid = np.c_[np.unique( bhid_, return_counts=True )] 


    #sli="[:]"  allowing everything makes for big tables of low stat histories
    sli="[:15]"
    at = a.minimal_qtab(sli=sli)  
    bt = b.minimal_qtab(sli=sli)  

    print("at\n",at)
    print("bt\n",bt)

    #ab = SAB(a,b)
    #print(repr(ab))

    assert PICK in ["A","B","AB","BA", "CF"]
    if PICK == "A":
        ee = [a,] 
    elif PICK == "B":
        ee = [b,]
    elif PICK == "AB":
        ee = [a,b,]
    elif PICK == "BA":
        ee = [b,a,]
    elif PICK == "CF":
        ee = []
    pass 

    context = "PICK=%s MODE=%d SEL=%d ./ntds3.sh " % (PICK, MODE, SEL )
    print(context)

    for e in ee:

        elabel = "%s : %s " % ( e.symbol.upper(), e.f.base )
        label = context + " ## " + elabel 

        if MODE in [0,1]:
            print("not plotting as MODE %d in environ" % MODE )
        elif MODE == 2:
            pl = mpplt_plotter(label=label)
            fig, axs = pl
            assert len(axs) == 1
            ax = axs[0]
            ax.set_ylim( -250, 250 )
            ax.set_xlim( -300, 300 )

        elif MODE == 3:
            pl = pvplt_plotter(label)
            pvplt_viewpoint(pl)   # sensitive to EYE, LOOK, UP envvars
            pvplt_frame(pl, e.f.sframe, local=not GLOBAL )
        pass


        #pp = e.f.inphoton[:,0,:3]
        #pp = e.f.photon[:,0,:3]
        #pp = e.f.hit[:,0,:3]
        pp = e.f.record[:,:,0,:3].reshape(-1,3)

        gpos = np.ones( [len(pp), 4 ] )
        gpos[:,:3] = pp
        lpos = np.dot( gpos, e.f.sframe.w2m )
        upos = gpos if GLOBAL else lpos


        H,V = 0,2  # X, Z

        if SEL == 1:
            sel = np.logical_and( np.abs(upos[:,H]) < 500, np.abs(upos[:,V]) < 500 )
            spos = upos[sel]
        else:
            spos = upos
        pass

        if MODE == 2:
            ax.scatter( spos[:,H], spos[:,V], s=0.1 )
        elif MODE == 3:
            pl.add_points(spos[:,:3])
        else:
            pass
        pass

        if MODE == 2:
            fig.show()
        elif MODE == 3:
            pl.show()
        pass
    pass   # over ee 
pass
   

