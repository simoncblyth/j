#!/usr/bin/env python
"""
LayrTest.py
=============

LayrTest<double,4> WITH_THRUST  dir /tmp/blyth/opticks/LayrTest/scan_gpu_double ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
[[  0.     1.     0.  ]
 [500.     1.     0.01]
 [500.     1.     0.01]
 [  0.     1.5    0.  ]]
compare : (a,b) cpu vs gpu (float) 
LayrTest<float,4> WITH_THRUST  dir /tmp/blyth/opticks/LayrTest/scan_cpu_float ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
LayrTest<float,4> WITH_THRUST  dir /tmp/blyth/opticks/LayrTest/scan_gpu_float ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
       lls : 7.56979e-05 : -7.6532364e-05  
     comps : 0.0006427765 : -0.00062179565 
      arts : 3.4868717e-06 : -3.9339066e-06 
compare : (c,d) cpu vs gpu (double) 
LayrTest<double,4> WITH_THRUST  dir /tmp/blyth/opticks/LayrTest/scan_cpu_double ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
LayrTest<double,4> WITH_THRUST  dir /tmp/blyth/opticks/LayrTest/scan_gpu_double ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
       lls : 4.030109579389318e-14 : -3.930189507173054e-14  
     comps : 3.090860900556436e-13 : -3.019806626980426e-13 
      arts : 1.887379141862766e-15 : -1.8318679906315083e-15 
compare : (a,c) float vs double (cpu) 
LayrTest<float,4> WITH_THRUST  dir /tmp/blyth/opticks/LayrTest/scan_cpu_float ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
LayrTest<double,4> WITH_THRUST  dir /tmp/blyth/opticks/LayrTest/scan_cpu_double ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
       lls : 4.6210350117981136e-05 : -4.854695527356512e-05  
     comps : 0.0003904741595874839 : -0.00036779132400965864 
      arts : 2.4826195538230067e-06 : -2.7918790206360455e-06 
compare : (b,d) float vs double (gpu) 
LayrTest<float,4> WITH_THRUST  dir /tmp/blyth/opticks/LayrTest/scan_gpu_float ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
LayrTest<double,4> WITH_THRUST  dir /tmp/blyth/opticks/LayrTest/scan_gpu_double ni 90 wl 500 theta[0] 0 theta[ni-1] 1.55334
       lls : 5.049636018605863e-05 : -4.970539873583313e-05  
     comps : 0.0003161468029624359 : -0.00032503921397619706 
      arts : 3.8496625794082195e-06 : -3.141641908288584e-06 


"""

import os, builtins, numpy as np
from opticks.ana.fold import Fold 
SIZE = np.array([1280, 720])


def both(x,y):
    return not x is None and not y is None

class LayrTest(object):
    def __init__(self, f):
        self.f = f  
        if not f is None:
            label = f.arts_meta.d["brief"] 
            x_dd_nn = str(np.c_[f.lls[0,:,0,0,0],f.lls[0,:,0,1]])
            title = "\n".join([f.symbol, label, x_dd_nn])
        else:
            label = "-"
            title = "None" 
        pass
        self.label = label
        self.title = title
    def __repr__(self):
        return self.title


class LayrTestSet(object):
    BASE = os.environ.get("LAYRTEST_BASE", "/tmp/LayrTest")
    NAMES = list(filter(lambda name:name.startswith("scan_"),os.listdir(BASE))) 
    SYMBOLS = "abcdefghijklmnopqrstuvwxyz"

    def __init__(self):

        tests = []
        names = [] 
        symbols = []

        for idx in range(len(self.NAMES)):
            name = self.NAMES[idx]
            symbol = self.SYMBOLS[idx]
            test = LayrTest(Fold.Load(self.BASE, name,  symbol=symbol))
            setattr(builtins, symbol, test)
            setattr(self, symbol, test) 

            tests.append(test)
            names.append(name)
            symbols.append(symbol) 
        pass
        self.tests = tests
        self.symbols = symbols
        self.names = names

    def __repr__(self):
        lines = []
        lines.append("CFLayrTest")
        for idx in range(len(self.tests)):
            symbol = self.symbols[idx]
            name = self.names[idx]
            lines.append("%2s : %s " % (symbol, name))    
        pass
        return "\n".join(lines)



class AB(object):
    def __init__(self, A, B):

        self.A = A 
        self.B = B 

    def __repr__(self):
        A = self.A
        B = self.B 

        if A is None or B is None or A.f is None or B.f is None:
             return "CANNOT COMPARE"
        pass

        lines = ["AB"]
        lines += [A.label]
        lines += [B.label]

        xy_lls   = A.f.lls - B.f.lls
        xy_comps = A.f.comps - B.f.comps
        xy_arts  = A.f.arts - B.f.arts

        lines += [ "%10s : %s : %s  " % ("lls",   xy_lls.max(),   xy_lls.min()) ]
        lines += [ "%10s : %s : %s "  % ("comps", xy_comps.max(), xy_comps.min()) ]  
        lines += [ "%10s : %s : %s "  % ("arts",  xy_arts.max(),  xy_arts.min()) ]  

        return "\n".join(lines)


class ARTPlot(object):
    def __init__(self, test):

        f = test.f
        title = test.title 

        R_s = f.arts[:,0,0]
        R_p = f.arts[:,0,1]
        T_s = f.arts[:,0,2]
        T_p = f.arts[:,0,3]

        A_s = f.arts[:,1,0]
        A_p = f.arts[:,1,1]
        R = f.arts[:,1,2]
        T = f.arts[:,1,3]

        A = f.arts[:,2,0]
        A_R_T = f.arts[:,2,1]
        wl = f.arts[:,2,2] 
        th = f.arts[:,2,3]

        fig, ax = plt.subplots(1, figsize=SIZE/100.)
        fig.suptitle(title)   

        ax.plot(th, R, label="R")
        ax.plot(th, T, label="T")
        ax.plot(th, A, label="A")
        ax.plot(th, A_R_T, label="A_R_T")

        ax.legend() 
        fig.show()                




if __name__ == '__main__':


    ts = LayrTestSet()  
    print(repr(ts))

    print(repr(AB(a,b)))

pass

