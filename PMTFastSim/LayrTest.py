#!/usr/bin/env python

import numpy as np
from opticks.ana.fold import Fold 

if __name__ == '__main__':
    a = Fold.Load("/tmp/LayrTest0", symbol="a")
    b = Fold.Load("/tmp/LayrTest1", symbol="b")
    print(repr(a))
    print(repr(b))

    assert  np.all( a.lls == b.lls ) 
    assert  np.all( a.comps == b.comps ) 
    assert  np.all( a.arts == b.arts ) 


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

    

    title = "LayrTest.py wl:%s " % wl[0] 
    dd_nn = str(np.c_[a.lls[0,:,0,0,0],a.lls[0,:,0,1]])

    SIZE = np.array([1280, 720])
    fig, ax = plt.subplots(1, figsize=SIZE/100.)
    fig.suptitle("\n".join([title,dd_nn]))   

    ax.plot(th, R, label="R")
    ax.plot(th, T, label="T")
    ax.plot(th, A, label="A")
    ax.plot(th, A_R_T, label="A_R_T")

    ax.legend() 
    fig.show()                


pass

