#!/usr/bin/env python

import numpy as np
from opticks.ana.fold import Fold
from opticks.ana.rsttable import RSTTable

if __name__ == '__main__':


    a = Fold.Load("$AFOLD", symbol="a")
    if not a is None:
        print(repr(a))
    
    b = Fold.Load("$BFOLD", symbol="b")
    if not b is None:
        print(repr(b))

    if not a is None and not b is None:
        assert a.stems == b.stems

        a_scantime = {}
        b_scantime = {}

        pick = []
        for stem in a.stems:
            if stem == "NPFold_index": continue
            if stem.endswith("_meta"): 
                aq = getattr(a, stem)
                bq = getattr(b, stem)
                xtem = stem[:-len("_meta")]
                a_scantime[xtem] =  float(aq.find("scantime"))
                b_scantime[xtem] =  float(bq.find("scantime"))
            else:
                pick.append(stem)
            pass
        pass

                
        num = len(pick)
        v = np.zeros( [num+1, 7], dtype=np.object )

        for i, stem in enumerate(pick):
            aq = getattr(a, stem)
            bq = getattr(b, stem)
            assert aq.shape == bq.shape 

            mq = np.all( aq == bq )
            md = np.abs( aq - bq).max() 
            at = a_scantime.get(stem, -1)
            bt = b_scantime.get(stem, -1)

            v[i][0] = stem 
            v[i][1] = str(aq.shape)
            v[i][2] = "YES" if mq else "NO"
            v[i][3] = md 
            v[i][4] = at 
            v[i][5] = bt 
            v[i][6] = bt/at

            print(" stem %25s : %20s : mq %s : at %10.3f : bt %10.3f" % (stem, str(aq.shape), mq, at, bt ))
            #assert(mq)
        pass 

        v[num][0] = "TOTAL"
        v[num][1] = "-"
        v[num][2] = "-"
        v[num][3] = v[:num,3].max()
        v[num][4] = v[:num,4].sum()
        v[num][5] = v[:num,5].sum()
        v[num][6] = v[num,5]/v[num,4]


        labels = ["scan", "shape", "exact", "maxdiff", "A_time", "B_time", "B/A" ] 

        wids = [ 20,     20    ,   10,     10,     10,     10,    10    ] 
        hfmt = [ "%20s", "%20s", "%10s", "%10s", "%10s", "%10s", "%10s" ]   # header format    
        rfmt = [ "%20s", "%20s", "%10s", "%10.4f","%10.4f", "%10.4f", "%10.4f" ]   # row
        pre  = [ "" ,    "   " ,   " " ,  " " ,    " ",   " ",   " "    ]
        post = [ "" ,    "   " ,   " " ,  " " ,    " ",   " ",   " "    ]

        rst = RSTTable.Render(v, labels, wids, hfmt, rfmt, pre, post )
        print(rst)
        print(" A: %s " % (a.base) )
        print(" B: %s " % (b.base) )
    pass


pass

