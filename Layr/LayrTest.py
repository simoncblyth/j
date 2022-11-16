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
from opticks.ana.rsttable import RSTTable
SIZE = np.array([1280, 720])

def both(x,y):
    return not x is None and not y is None

class LayrTest(object):
    """
    Thin wrapper for a LayrTest output folder 
    """
    @classmethod
    def Tag(cls, name):
        """
        scan__NNVTMCP__gpu_thr_float
        """
        tag = ""
        if "gpu" in name: tag += "g" ; 
        if "cpu" in name: tag += "c" ; 
        if "thr" in name: tag += "t" ; 
        if "std" in name: tag += "s" ; 
        if "pom" in name: tag += "p" ; 
        if "double" in name: tag += "d" ; 
        if "float" in name: tag += "f" ; 
        return tag

    def __init__(self, f):
        self.f = f  
        if not f is None:
            title = f.arts_meta.d.get("title","-") 
            brief = f.arts_meta.d.get("brief","-") 
            name = f.arts_meta.d.get("name","-") 
            tag = self.Tag(name)
            label = f.arts_meta.d.get("label","-") 
            symbol = f.symbol

            if not getattr(f, "lls", None) is None:
                layrs = str(np.c_[f.lls[0,:,0,0,0],f.lls[0,:,0,1]])
            else:
                layrs = "?" 
            pass
        else:
            title = "-"
            brief = "-"
            name = "-"
            tag = "?"
            label = "-"
            symbol = "?"
            layrs = "?" 
        pass
        self.title = title
        self.brief = brief
        self.name = name
        self.tag = tag
        self.label = label
        self.symbol = symbol
        self.layrs = layrs
        self.arts = f.arts
        self.lls = f.lls
        self.comps = f.comps

    def __repr__(self):
        return "%s : %s" % (self.symbol, self.title)


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
        labels = [] 
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
            labels.append(test.label)
            symbols.append(symbol) 
            folds.append(fold)
            tests.append(test)
        pass
        self.names = names
        self.labels = labels
        self.symbols = symbols
        self.folds = folds
        self.tests = tests

    def select(self, label):
        return list(filter(lambda t:t.label == label, self.tests))

    def cf_table(self, tt, label, qwns="arts comps".split(), excl=0 ):
        """
        ::


            +------------------------------+----------+----------+----------+----------+
            |            R12860 arts\comps |     m:ctd|     n:ctf|     o:gtd|     p:gtf|
            +==============================+==========+==========+==========+==========+
            |                         m:ctd|         0|    0.0129| 4.547e-13|   0.01284|
            +------------------------------+----------+----------+----------+----------+
            |                         n:ctf| 6.101e-06|         0|    0.0129| 0.0001221|
            +------------------------------+----------+----------+----------+----------+
            |                         o:gtd| 1.321e-14| 6.101e-06|         0|   0.01284|
            +------------------------------+----------+----------+----------+----------+
            |                         p:gtf| 1.523e-06| 7.451e-06| 1.523e-06|         0|
            +------------------------------+----------+----------+----------+----------+


            +------------------------------+----------+----------+----------+----------+
            |           NNVTMCP arts\comps |     i:ctd|     j:ctf|     k:gtd|     l:gtf|
            +==============================+==========+==========+==========+==========+
            |                         i:ctd|         0|   0.01279| 4.547e-13|   0.01279|
            +------------------------------+----------+----------+----------+----------+
            |                         j:ctf| 5.154e-06|         0|   0.01279| 9.155e-05|
            +------------------------------+----------+----------+----------+----------+
            |                         k:gtd| 1.243e-14| 5.154e-06|         0|   0.01279|
            +------------------------------+----------+----------+----------+----------+
            |                         l:gtf| 1.403e-06| 6.557e-06| 1.403e-06|         0|
            +------------------------------+----------+----------+----------+----------+

            +------------------------------+----------+----------+----------+----------+
            |      NNVTMCP_HiQE arts\comps |     e:ctd|     f:ctf|     g:gtd|     h:gtf|
            +==============================+==========+==========+==========+==========+
            |                         e:ctd|         0|   0.01837| 2.416e-13|   0.01855|
            +------------------------------+----------+----------+----------+----------+
            |                         f:ctf| 7.528e-06|         0|   0.01837| 0.0001831|
            +------------------------------+----------+----------+----------+----------+
            |                         g:gtd| 1.754e-14| 7.528e-06|         0|   0.01855|
            +------------------------------+----------+----------+----------+----------+
            |                         h:gtf| 1.829e-06| 9.358e-06| 1.829e-06|         0|
            +------------------------------+----------+----------+----------+----------+

        """
        key = "%s %s %s" % (label, "\\".join(qwns), excl)

        ntt = len(tt)
        labels = [key] 
        tab= np.zeros( [ntt,1+ntt], dtype=np.object )

        for i in range(ntt):
            ti = tt[i]
            label = "%s:%s" % (ti.symbol, ti.tag)
            labels.append(label)
            tab[i,0] = label
            for j in range(ntt):
                if i == j: continue
                tj = tt[j]
                cf = CF(ti,tj,excl)
                qwn = qwns[0] if i > j else qwns[1]
                cfv = np.abs( getattr(cf, qwn) ).max()
                pass
                tab[i,j+1] = cfv
            pass
        pass
        rst = RSTTable.Rdr(tab, labels, rfm="%10.4g", left_wid=30, hfm="%10s", left_rfm="%30s", left_hfm="%30s" )
        return rst 

    def __repr__(self):
        lines = []
        lines.append("CFLayrTest")
        for idx in range(len(self.tests)):
            symbol = self.symbols[idx]
            label = self.labels[idx]
            name = self.names[idx]
            lines.append("%2s : %15s : %s " % (symbol, label, name))    
        pass
        return "\n".join(lines)



class CF(object):
    """
    Compare two LayrTest objects 
    """
    def __init__(self, A, B, excl=0):
        """
        """
        self.A = A 
        self.B = B 
        self.excl = excl

        if A is None or B is None or A.f is None or B.f is None:
            self.lls = None
            self.comps = None
            self.arts = None
        else:

            assert np.abs( A.arts[:,-1,-1] - B.arts[:,-1,-1] ).max() < 1e-6

            mct = A.arts[:,-1,-1] 
            sel = np.abs(mct) > excl     

            _lls = A.f.lls - B.f.lls
            _comps = A.f.comps - B.f.comps
            _arts = A.f.arts - B.f.arts

            lls = _lls[sel]
            comps = _comps[sel]
            arts = _arts[sel]

            self._lls   = _lls
            self._comps = _comps
            self._arts  = _arts

            self.lls = lls
            self.comps = comps
            self.arts = arts
        pass

    def __repr__(self):
        A = self.A
        B = self.B 
        excl = self.excl

        lls = self.lls
        comps = self.comps
        arts = self.arts

        if A is None or B is None or A.f is None or B.f is None:
             return "CANNOT COMPARE"
        pass


        CF_brief = "CF(%s,%s,%s) : %s vs %s " % (A.symbol, B.symbol, excl, A.name, B.name ) 
        lines = [CF_brief]
        lines += [A.brief]
        lines += [B.brief]

        ffmt = "%10.3g"
        fmt = "%%10s : %(ffmt)s : %(ffmt)s : %(ffmt)s" % locals()  

        lines += [ fmt % ("lls",   np.abs(lls).max(),   lls.max(),   lls.min()) ]
        lines += [ fmt % ("comps", np.abs(comps).max(), comps.max(), comps.min()) ]  
        lines += [ fmt % ("arts",  np.abs(arts).max(),  arts.max(),  arts.min()) ]  

        return "\n".join(lines)



class ARTPlot(object):
    @classmethod
    def Plot(cls, ax, test, excl=0):
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

        th2mct_ = lambda th:-np.cos(th*np.pi/180.)
        mct2th_ = lambda mct:np.arccos(-mct)*180./np.pi

        #th = np.arccos(-mct)*180./np.pi  
        th = mct2th_(mct)

        #s = mct <= 0. 
        #s = mct >= 0. 
        s = slice(None)

        ax.plot(th[s], R[s], label="R")
        ax.plot(th[s], T[s], label="T")
        ax.plot(th[s], A[s], label="A")
        ax.plot(th[s], A_R_T[s], label="A_R_T")
        #ax.set_title( test.label )

        xx = [0,90,180] 

        edeg = [np.arccos(excl)*180/np.pi,np.arccos(-excl)*180/np.pi] if excl > 0 else []
        xx.extend(edeg)
        for x in xx:
            ax.plot( [ x,  x],   [0, 1], linestyle="dashed" )  
        pass

        extra_ = ["excl: %s " % excl]
        for i in range(len(edeg)):
            extra_.append("edeg[%d] : %7.2f " % (i, edeg[i]))
        pass
        extra = "\n".join(extra_)

        ax.text( 125, 0.6, "\n".join([test.layrs,extra]))

        sax = ax.secondary_xaxis('top', functions=(th2mct_, mct2th_))
        sax.set_xlabel('mct : -cos(theta) : dot(photon_momentum,surface_normal) ')
        ax.set_xlabel('aoi [degrees] ( 90:180 : reverse stack )' )



    def __init__(self, test, excl=0):

        fig, ax = plt.subplots(1, figsize=SIZE/100.)

        title = test.title 
        fig.suptitle(title)   

        self.Plot(ax, test, excl=excl)  

        ax.legend(loc=os.environ.get("LOC", "upper right")) 
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

    pmtcat = os.environ.get("LAYRTEST_PMTCAT", "EGet")
    excl = float(os.environ.get("LAYRTEST_EXCL", "0.05"))

    tt = ts.select(pmtcat)

    lt = tt[-1] if len(tt) > 0 else None
    print("pmtcat:%s tt:%d lt:%s " % (pmtcat, len(tt), lt ))

      
    if not lt is None:
       ap = ARTPlot(lt, excl=excl)
    pass 

    if len(tt) > 0:
        rst = ts.cf_table(tt, pmtcat, excl=excl)
        print(rst)
    pass






pass

