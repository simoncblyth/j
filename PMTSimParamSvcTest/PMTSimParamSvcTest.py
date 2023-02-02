#!/usr/bin/env python

import numpy as np
from opticks.ana.fold import Fold

if __name__ == '__main__':


    a = Fold.Load("$AFOLD", symbol="a")
    if not a is None:
        print(repr(a))
    
    b = Fold.Load("$BFOLD", symbol="b")
    if not b is None:
        print(repr(b))

    if not a is None and not b is None:
        assert a.stems == b.stems
        for stem in a.stems:
            if stem == "NPFold_index": continue
            aq = getattr(a, stem)
            bq = getattr(b, stem)
            mq = np.all( aq == bq )
            print(" stem %25s : aq %20s : bq %20s : mq %s " % (stem, str(aq.shape), str(bq.shape), mq ))
            assert(mq)
        pass 
    pass


pass

