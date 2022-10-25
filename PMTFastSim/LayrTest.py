#!/usr/bin/env python
"""
LayrTest.py
=============

compare : (a,b) cpu vs gpu (float) 
LayrTest<float,4> WITH_THRUST  dir /tmp/LayrTest/scan_cpu_float ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
LayrTest<float,4> WITH_THRUST  dir /tmp/LayrTest/scan_gpu_float ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
xy_lls   : 2.861023e-06 
xy_comps : 1.9073486e-05 
xy_arts  : 1.0728836e-06 
compare : (c,d) cpu vs gpu (double) 
LayrTest<double,4> WITH_THRUST  dir /tmp/LayrTest/scan_cpu_double ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
LayrTest<double,4> WITH_THRUST  dir /tmp/LayrTest/scan_gpu_double ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
xy_lls   : 4.030109579389318e-14 
xy_comps : 3.090860900556436e-13 
xy_arts  : 1.887379141862766e-15 
compare : (a,c) float vs double (cpu) 
LayrTest<float,4> WITH_THRUST  dir /tmp/LayrTest/scan_cpu_float ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
LayrTest<double,4> WITH_THRUST  dir /tmp/LayrTest/scan_cpu_double ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
xy_lls   : 4.6210350117981136e-05 
xy_comps : 0.0003904741595874839 
xy_arts  : 2.4826195538230067e-06 
compare : (b,d) float vs double (gpu) 
LayrTest<float,4> WITH_THRUST  dir /tmp/LayrTest/scan_gpu_float ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
LayrTest<double,4> WITH_THRUST  dir /tmp/LayrTest/scan_gpu_double ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
xy_lls   : 4.477983863893087e-05 
xy_comps : 0.0003714006731385666 
xy_arts  : 2.4826195538230067e-06 


"""

import numpy as np
from opticks.ana.fold import Fold 

def compare(x,y, label):
    lines = ["compare : %s " % label ]
    if not x is None and not y is None:
        lines += [x.brief, y.brief ] 

        xy_lls = x.lls - y.lls
        xy_comps = x.comps - y.comps
        xy_arts = x.arts - y.arts

        lines += [ "xy_lls   : %s " % xy_lls.max() ]
        lines += [ "xy_comps : %s " % xy_comps.max() ]  
        lines += [ "xy_arts  : %s " % xy_arts.max() ]  
    pass
    return "\n".join(lines)


if __name__ == '__main__':

    base= "/tmp/LayrTest"
    a = Fold.Load(base, "scan_cpu_float",  symbol="a")
    b = Fold.Load(base, "scan_gpu_float",  symbol="b")
    c = Fold.Load(base, "scan_cpu_double", symbol="c")
    #d = Fold.Load(base, "scan_gpu_double", symbol="d")

    a.brief = a.arts_meta.d["brief"] 
    b.brief = b.arts_meta.d["brief"] 
    c.brief = c.arts_meta.d["brief"] 
    #d.brief = d.arts_meta.d["brief"] 

    print(a.brief)
    print(repr(a))

    print(b.brief)
    print(repr(b))

    print(c.brief)
    print(repr(c))

    #print(d.brief)
    #print(repr(d))

    print(compare(a,b,"(a,b) cpu vs gpu (float)"))
    #print(compare(c,d,"(c,d) cpu vs gpu (double)"))
    print(compare(a,c,"(a,c) float vs double (cpu)"))
    #print(compare(b,d,"(b,d) float vs double (gpu)"))


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
    title = [a.brief, dd_nn]

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

