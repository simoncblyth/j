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



Blowout at turnaround::

    In [15]: CF(a,b)
    Out[15]: 
    CF(a,b) : scan_NNVTMCP_HiQE_cpu_thr_double vs scan_NNVTMCP_HiQE_cpu_thr_float 
    LayrTest<double,4> WITH_THRUST  name scan_NNVTMCP_HiQE_cpu_thr_double ni 900 wl 400 mct[0] -1 mct[ni-1] 0.999994
    LayrTest<float,4> WITH_THRUST  name scan_NNVTMCP_HiQE_cpu_thr_float ni 900 wl 400 mct[0] -1 mct[ni-1] 0.999994
           lls : 6813571569456890.0 : -6813571569456890.0  
         comps : 1.6636561207996178e+16 : -1.6636561207996178e+16 
          arts : 1.40579499818827e-06 : -1.2922178646013194e-06 


    In [3]: abc = a.f.comps - b.f.comps   ## difference of composite layer objects
    In [4]: abc.shape
    Out[4]: (900, 4, 4, 2)

    In [14]: np.where( np.abs(abc) > 0.005 )   ## blowout at 90 degrees
    Out[14]: 
    (array([450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 451, 451]),
     array([2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2]),
     array([0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3, 0, 2]),
     array([0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0]))


    In [16]: abl = a.f.lls - b.f.lls     

    In [19]: abl.shape
    Out[19]: (900, 4, 4, 4, 2)

    In [18]: np.where(np.abs(abl) > 0.05 )
    Out[18]: 
    (array([450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450,
            450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450,
            450, 450, 450, 450, 450, 450, 450]),
     array([0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3,
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]),
     array([0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 0,
            0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3]),
     array([1, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3, 1,
            2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 2, 3, 3]),
     array([0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
            0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1]))



"""

import os, builtins, numpy as np
from opticks.ana.fold import Fold 
SIZE = np.array([1280, 720])


def both(x,y):
    return not x is None and not y is None

class LayrTest(object):
    """
    Thin wrapper for a LayrTest output folder 
    """
    def __init__(self, f):
        self.f = f  
        if not f is None:
            brief = f.arts_meta.d["brief"] 
            name = f.arts_meta.d["name"] 
            label = f.arts_meta.d["label"] 
            symbol = f.symbol
            x_dd_nn = str(np.c_[f.lls[0,:,0,0,0],f.lls[0,:,0,1]])
            title = "\n".join([symbol, brief, x_dd_nn])
        else:
            brief = "-"
            name = "-"
            label = "-"
            symbol = "?"
            title = "None" 
        pass
        self.brief = brief
        self.name = name
        self.label = label
        self.title = title
        self.symbol = symbol

    def __repr__(self):
        return self.title


class LayrTestSet(object):
    """
    Instanciation populates global scope with symbols a, b, c, ...  
    that point to LayrTest objects loaded from LAYRTEST_BASE /tmp/blyth/opticks/LayrTest.
    The order is obtained by lexical sorting the directory names, eg::

        ['scan_NNVTMCP_HiQE_cpu_thr_double',
         'scan_NNVTMCP_HiQE_cpu_thr_float',
         'scan_NNVTMCP_HiQE_gpu_thr_double',
         'scan_NNVTMCP_HiQE_gpu_thr_float']
     
    """
    BASE = os.environ.get("LAYRTEST_BASE", "/tmp/LayrTest")
    NAMES = sorted(list(filter(lambda name:name.startswith("scan_"),os.listdir(BASE)))) 
    SYMBOLS = "abcdefghijklmnopqrstuvwxyz"

    def __init__(self):
        assert len(self.NAMES) < len(self.SYMBOLS) 

        names = [] 
        symbols = []
        folds = [] 
        tests = []

        for idx in range(len(self.NAMES)):
            name = self.NAMES[idx]
            symbol = self.SYMBOLS[idx]
            fold = Fold.Load(self.BASE, name,  symbol=symbol)
            test = LayrTest(fold)
            test.name = name 

            setattr(builtins, symbol, test)
            setattr(self, symbol, test) 

            names.append(name)
            symbols.append(symbol) 
            folds.append(fold)
            tests.append(test)
        pass
        self.names = names
        self.symbols = symbols
        self.folds = folds
        self.tests = tests

    def __repr__(self):
        lines = []
        lines.append("CFLayrTest")
        for idx in range(len(self.tests)):
            symbol = self.symbols[idx]
            name = self.names[idx]
            lines.append("%2s : %s " % (symbol, name))    
        pass
        return "\n".join(lines)



class CF(object):
    """
    Compare two LayrTest objects 
    """
    def __init__(self, A, B):
        self.A = A 
        self.B = B 

    def __repr__(self):
        A = self.A
        B = self.B 

        if A is None or B is None or A.f is None or B.f is None:
             return "CANNOT COMPARE"
        pass

        CF_brief = "CF(%s,%s) : %s vs %s " % (A.symbol, B.symbol, A.name, B.name ) 
        lines = [CF_brief]
        lines += [A.brief]
        lines += [B.brief]

        xy_lls   = A.f.lls - B.f.lls
        xy_comps = A.f.comps - B.f.comps
        xy_arts  = A.f.arts - B.f.arts

        lines += [ "%10s : %s : %s  " % ("lls",   xy_lls.max(),   xy_lls.min()) ]
        lines += [ "%10s : %s : %s "  % ("comps", xy_comps.max(), xy_comps.min()) ]  
        lines += [ "%10s : %s : %s "  % ("arts",  xy_arts.max(),  xy_arts.min()) ]  

        return "\n".join(lines)



class ARTPlot(object):
    @classmethod
    def Plot(cls, ax, test):
        f = test.f

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
        mct = f.arts[:,2,3]  # minus_cos_theta 
        th = np.arccos(-mct)*180./np.pi  

        #s = mct <= 0. 
        #s = mct >= 0. 
        s = mct != np.nan 

        ax.plot(th[s], R[s], label="R %s" % test.label)
        ax.plot(th[s], T[s], label="T %s" % test.label)
        ax.plot(th[s], A[s], label="A %s" % test.label)
        ax.plot(th[s], A_R_T[s], label="A_R_T %s" % test.label )

        ax.plot( [90, 90],   [0, 1], linestyle="dashed" ) 
        ax.plot( [180, 180], [0, 1], linestyle="dashed" ) 

    def __init__(self, test):

        fig, ax = plt.subplots(1, figsize=SIZE/100.)

        title = test.title 
        fig.suptitle(title)   

        self.Plot(ax, test)  

        ax.legend(loc=os.environ.get("LOC", "lower right")) 
        fig.show()                


class MARTPlot(object):
    def __init__(self, *tests):
        for test in tests:
            print(test.label)
        pass 

        fig, ax = plt.subplots(1, figsize=SIZE/100.)

        title = "MARTPlot"
        fig.suptitle(title)   

        for test in tests:
            ARTPlot.Plot(ax, test)  
        pass

        ax.legend(loc=os.environ.get("LOC", "lower right")) 
        fig.show()                



if __name__ == '__main__':
    ts = LayrTestSet()  
    print(repr(ts))
    print(repr(CF(a,b)))
pass

