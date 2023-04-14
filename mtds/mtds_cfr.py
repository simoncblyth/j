#!/usr/bin/env python
"""
mtds_cfm.py : Comparing random consumption across multiple evt 
================================================================

"""
import os, numpy as np
from opticks.ana.fold import Fold

if __name__ == '__main__':
    AFOLD = os.path.expandvars("$AFOLD")
    BFOLD = os.path.expandvars("$BFOLD")

    efmt = "%0.3d"
    assert efmt in AFOLD and efmt in BFOLD

    NEVT = int(os.environ.get("NEVT","10"))

    ab = np.zeros( (NEVT, 2) )
    aa = []
    bb = []

    for i in range(NEVT):
        af = Fold.Load(AFOLD % i,symbol="a", quiet=True)
        bf = Fold.Load(BFOLD % i,symbol="b", quiet=True)

        a = af.S4RandomArray.reshape(-1)  
        b = bf.S4RandomArray.reshape(-1)  
        aa.append(a)
        bb.append(b)

        na = a.shape[0]
        nb = b.shape[0]
        ab[i, 0] = na 
        ab[i, 1] = nb 
    pass
    print(ab)

    A = np.concatenate( aa )  
    B = np.concatenate( bb )  

    print("A:%s " % str(A.shape))
    print("B:%s " % str(B.shape))

    BB = B[:len(A)] 
    assert np.all( BB == A ), "expect all common randoms to be the same "



