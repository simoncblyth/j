#!/usr/bin/env python

import os, logging, numpy as np
from opticks.sysrap.sevt import SEvt, SAB
from opticks.ana.p import cf  

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

    print("[--- ab = SAB(a,b) ----")
    ab = SAB(a,b)
    print("]--- ab = SAB(a,b) ----")

    print("[----- repr(ab) ")
    print(repr(ab))
    print("]----- repr(ab) ")

 
