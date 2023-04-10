#!/usr/bin/env python
"""
ntds_cf10.py : Comparing history frequencies
========================================================

For the comparison to be meaningful (within reasonable statistics)
requires common input photons. 

"""
import os, numpy as np
from opticks.sysrap.sevt import SEvt, SAB

if __name__ == '__main__':
    AFOLD = os.path.expandvars("$AFOLD")
    BFOLD = os.path.expandvars("$BFOLD")

    efmt = "%0.3d"
    assert efmt in AFOLD and efmt in BFOLD

    tabs = []
    tab = None
    skk = None 

    NEVT = int(os.environ.get("NEVT","10"))

    for i in range(NEVT):
        a = SEvt.Load(AFOLD % i,symbol="a", quiet=True)
        b = SEvt.Load(BFOLD % i,symbol="b", quiet=True)
        ab = SAB(a,b)

        if skk is None:
            kk = ab.jsdph.kk
            skk = ab.jsdph.skk
            tab = ab.jsdph.tab
        else:
            assert np.all( skk == ab.jsdph.skk )
            assert tab.shape == ab.jsdph.tab.shape
        pass

        tabs.append(ab.jsdph.tab)
        if "c2desc" in os.environ:
            fmt = " %s : %%s " % efmt 
            print( fmt % ( i, ab.qcf.c2desc))
        else:
            print(repr(ab))
        pass
    pass

    # HMM: this shape with evt up top is not so useful 
    mtab = np.zeros( (NEVT, tab.shape[0], tab.shape[1]) )
    for i in range(len(tabs)): mtab[i] = tabs[i]  

    # with evt down below much more useful 
    ytab = np.zeros( (tab.shape[0], tab.shape[1], NEVT ))
    for i in range(len(tabs)): ytab[:,:,i] = tabs[i]  

    #akk = np.array( list(skk)) 
    akk = np.array( list(kk)) 

    lines = repr(ytab).split("\n")
    for i, line in enumerate(lines):
        anno = akk[i//3] if i % 3 == 0 else ""
        print("%s       %s " % (line, anno ))
    pass

     


