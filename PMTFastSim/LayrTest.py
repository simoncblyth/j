#!/usr/bin/env python
"""
LayrTest.py
=============




"""

import numpy as np
from opticks.ana.fold import Fold 

if __name__ == '__main__':
    a = Fold.Load("/tmp/LayrTest0", symbol="a")
    b = Fold.Load("/tmp/LayrTest2", symbol="b")
    a_brief = a.arts_meta.d["brief"] 
    b_brief = b.arts_meta.d["brief"] 

    print(a_brief)
    print(repr(a))

    print(b_brief)
    print(repr(b))



    if not a is None and not b is None:
        print("compare a and b") 
        #assert  np.all( a.lls == b.lls ) 
        #assert  np.all( a.comps == b.comps ) 
        #assert  np.all( a.arts == b.arts ) 

        ab_lls = a.lls - b.lls
        ab_comps = a.comps - b.comps
        ab_arts = a.arts - b.arts

        print( "a_brief  : %s " % a_brief )
        print( "b_brief  : %s " % b_brief )
        print( "ab_lls   : %s " % ab_lls.max() )  
        print( "ab_comps : %s " % ab_comps.max() )  
        print( "ab_arts  : %s " % ab_arts.max() )  
    pass

    



    R_s = a.arts[:,0,0]
    R_p = a.arts[:,0,1]
    T_s = a.arts[:,0,2]
    T_p = a.arts[:,0,3]

    A_s = a.arts[:,1,0]
    A_p = a.arts[:,1,1]
    R = a.arts[:,1,2]
    T = a.arts[:,1,3]

    A = a.arts[:,2,0]
    A_R_T = a.arts[:,2,1]
    wl = a.arts[:,2,2] 
    th = a.arts[:,2,3]


    dd_nn = str(np.c_[a.lls[0,:,0,0,0],a.lls[0,:,0,1]])
    title = [a_brief, b_brief, dd_nn]

    SIZE = np.array([1280, 720])
    fig, ax = plt.subplots(1, figsize=SIZE/100.)
    fig.suptitle("\n".join(title))   

    ax.plot(th, R, label="R")
    ax.plot(th, T, label="T")
    ax.plot(th, A, label="A")
    ax.plot(th, A_R_T, label="A_R_T")

    ax.legend() 
    fig.show()                


pass

