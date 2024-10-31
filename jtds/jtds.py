#!/usr/bin/env python

import os, logging, numpy as np
from opticks.sysrap.sevt import SEvt, SAB
from opticks.ana.p import cf  

GLOBAL = int(os.environ.get("GLOBAL","0")) == 1
MODE = int(os.environ.get("MODE","3")) 
PICK = os.environ.get("PICK","A") 

if MODE in [2,3]:
    from opticks.ana.pvplt import *   
    # HMM this import overrides MODE, so need to keep defaults the same 
pass

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)

    INST_FRAME = int(os.environ.get("INST_FRAME","-1"))
    if INST_FRAME == -1:
        print("using default sframe saved with the sevt")
        M2W_OVERRIDE = None 
        W2M_OVERRIDE = None 
    else: 
        print("W2M_OVERRIDE obtained from cf.inst controlled by envvar INST_FRAME %d " % INST_FRAME )
        M2W_OVERRIDE = np.eye(4)  
        M2W_OVERRIDE[:,:3] = cf.inst[INST_FRAME][:,:3]  
        W2M_OVERRIDE = np.linalg.inv(M2W_OVERRIDE)
    pass

    a = SEvt.Load("$AFOLD", symbol="a", W2M=W2M_OVERRIDE)
    b = SEvt.Load("$BFOLD", symbol="b", W2M=W2M_OVERRIDE)
    print(repr(a))
    print(repr(b))

    if not a is None and b is None:
        PICK = "A"
    elif not b is None and a is None:
        PICK = "B"
    else:
        pass
    pass 

    if not a is None and not b is None:
        print("[--- ab = SAB(a,b) ----")
        ab = SAB(a,b)
        print("]--- ab = SAB(a,b) ----")

        print("[----- repr(ab) ")
        print(repr(ab))
        print("]----- repr(ab) ")
    pass

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

    context = "PICK=%s MODE=%d  ~/j/jtds/jtds.sh " % (PICK, MODE )
    print(context)


    for e in ee: 
        if e is None:continue
        elabel = "%s : %s " % ( e.symbol.upper(), e.f.base )

        if hasattr(e.f, 'photon'):
            pos = e.f.photon[:,0,:3]
        elif hasattr(e.f, 'hit'):
            pos = e.f.hit[:,0,:3]
        else:
            log.info("%s:sevt lacks photon or hit" % e.symbol)
            pos = None
        pass

        if hasattr(e.f, 'record'):
            sel = np.where(e.f.record[:,:,2,3] > 0) # select on wavelength to avoid unfilled zeros
            poi = e.f.record[:,:,0,:3][sel]
        else:
            log.info("%s:sevt lacks record" % e.symbol)
            poi = None
        pass

        if hasattr(e.f, 'sframe'):
            _W2M = e.f.sframe.w2m
        else:
            _W2M = np.eye(4)
            log.info("%s:sevt lacks sframe" % e.symbol)
        pass 

        W2M = _W2M if W2M_OVERRIDE is None else W2M_OVERRIDE
         
        print("W2M\n",W2M)

        if not pos is None:
            gpos = np.ones( [len(pos), 4 ] ) 
            gpos[:,:3] = pos
            lpos = np.dot( gpos, W2M )   # hmm unfilled global zeros getting transformed somewhere
            upos = gpos if GLOBAL else lpos
        else:
            upos = None
        pass 

        if not poi is None:
            gpoi = np.ones( [len(poi), 4 ] ) 
            gpoi[:,:3] = poi
            lpoi = np.dot( gpoi, W2M )
            upoi = gpoi if GLOBAL else lpoi
        else:
            upoi = None
        pass


        label = context + " ## " + elabel

        if MODE == 3 and not pv is None:
            pl = pvplt_plotter(label)
            pvplt_viewpoint(pl) # sensitive EYE, LOOK, UP, ZOOM envvars eg EYE=0,-3,0 

            if not upoi is None:
                pl.add_points( upoi[:,:3], color="green", point_size=3.0 )
            pass
            if not upos is None:
                pl.add_points( upos[:,:3], color="red", point_size=3.0 )
            pass
            pl.show_grid()
            cp = pl.show()
        pass
    pass

 
