#!/usr/bin/env python
"""
LayrTest.py
=============

Plot is too busy with everything visible. Use incl to restrict what is included::

    In [4]: ARTPlot(q,incl="Rxsp")
    Out[4]: ARTPlot(q,incl="Rxsp") # j/Layr/LayrTest scan__R12860__gpu_thr_float ni 900 wl 440  

    In [5]: ARTPlot(q,incl="Txsp")
    Out[5]: ARTPlot(q,incl="Txsp") # j/Layr/LayrTest scan__R12860__gpu_thr_float ni 900 wl 440  

    In [6]: ARTPlot(q,incl="Axsp")
    Out[6]: ARTPlot(q,incl="Axsp") # j/Layr/LayrTest scan__R12860__gpu_thr_float ni 900 wl 440  

Notice the very large difference between S and P polarizations.
Its crucial that use the values appropriate for the photon polatization.  

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
            title = f.art_meta.d.get("title",["-"])[0] 
            brief = f.art_meta.d.get("brief",["-"])[0] 
            name = f.art_meta.d.get("name",["-"])[0] 
            tag = self.Tag(name)
            label = f.art_meta.d.get("label",["-"])[0] 
            symbol = f.symbol

            if not getattr(f, "lls", None) is None:
                layr = str(np.c_[f.ll[0,:,0,0,0],f.ll[0,:,0,1]])
            else:
                layr = "?" 
            pass
        else:
            title = "-"
            brief = "-"
            name = "-"
            tag = "?"
            label = "-"
            symbol = "?"
            layr = "?" 
        pass

        if f.spec.shape == (4,4):
            nr_first = f.spec[0,0]  # Pyrex rindex
            nr_last = f.spec[3,0]  # Vacuum rindex 
        else:
            # SPMT has f.spec.shape (1, 1, 900, 1, 4, 4)
            f_spec = f.spec.squeeze()
            assert np.all( f_spec[:,0,0] == f_spec[0,0,0] )   
            assert np.all( f_spec[:,3,0] == f_spec[0,3,0] )   
            nr_first = f_spec[0,0,0] 
            nr_last  = f_spec[0,3,0] 
        pass
        nr_frac = np.array([nr_last/nr_first,nr_first/nr_last])

        brewster = np.array( [np.arctan(nr_frac[0]), np.pi - np.arctan(nr_frac[1]) ] )
        critical = np.array( [np.arcsin(nr_frac[0]), np.pi - np.arcsin(nr_frac[1]) ] )  # one of these will be np.nan

        self.nr_first = nr_first
        self.nr_last = nr_last
        self.nr_frac = nr_frac
        self.brewster = brewster 
        self.critical = critical 

        self.title = title
        self.brief = brief
        self.name = name
        self.tag = tag
        self.label = label
        self.symbol = symbol
        self.layr = layr
        self.art = f.art
        self.ll = f.ll
        self.comp = f.comp

    def __repr__(self):
        return "%s : %s" % (self.symbol, self.title)




def getdirnames(base, prefix="xscan"):
    return list(sorted(list(filter(lambda name:name.startswith("xscan"),os.listdir(base)))) )


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
    MODE = os.environ.get("LAYRTEST_MODE", "4")
    NAMES = sorted(list(filter(lambda name:name.startswith("scan_"),os.listdir(os.path.join(BASE, MODE))))) 
    SYMBOLS = "abcdefghijklmnopqrstuvwxyz"


    def __init__(self, symbol="ts"):

        self.symbol = symbol
        self.xbase = os.path.expandvars("$SFOLD/get_ARTE") 
        self.xnames = getdirnames( self.xbase, "xscan" )
        self.ALL_NAMES = self.NAMES + self.xnames 
        assert len(self.ALL_NAMES) < len(self.SYMBOLS) 

        print(" %s.xbase     : %s " % (self.symbol, str(self.xbase)))
        print(" %s.xnames    : %s " % (self.symbol, str(self.xnames)))
        print(" %s.ALL_NAMES : %s " % (self.symbol, str(self.ALL_NAMES)))

        names = [] 
        labels = [] 
        symbols = []
        folds = [] 
        tests = []

        for idx in range(len(self.ALL_NAMES)):
            name = self.ALL_NAMES[idx]
            symbol = self.SYMBOLS[idx]

            is_extra = idx >= len(self.NAMES) 


            if is_extra:
                fold = Fold.Load(self.xbase, name,  symbol=symbol)
            else:
                fold = Fold.Load(self.BASE, self.MODE, name,  symbol=symbol)
            pass

            test = LayrTest(fold)
            test.name = name 

            if is_extra:
                test.label = "R12860"
                print("kludge the label of is_extra ")
            pass 


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
        """ 
        :param q_label: str
        :return list: of LayrTest instances with t.label matching the argument 
        """
        return list(filter(lambda t:t.label == label, self.tests))

    def cf_table(self, tt, label, qwns="art comp".split(), excl=0 ):
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
        :param A:
        :param B:
        :param excl:  Can be used to exclude a band around mct=0 
        """
        self.A = A 
        self.B = B 
        self.excl = excl

        if A is None or B is None or A.f is None or B.f is None:
            self.ll = None
            self.comp = None
            self.art = None
        else:

            a_mct = A.art.squeeze()[:,2,3]
            b_mct = B.art.squeeze()[:,2,3]
            ab_mct = np.abs(a_mct-b_mct)
            assert ab_mct.max() < 1e-6

            mct = a_mct 
            sel = np.abs(mct) > excl     

            _ll = A.f.ll.squeeze() - B.f.ll.squeeze()
            _comp = A.f.comp.squeeze() - B.f.comp.squeeze()
            _art = A.f.art.squeeze() - B.f.art.squeeze()

            ll = _ll[sel]
            comp = _comp[sel]
            art = _art[sel]

            self._ll   = _ll
            self._comp = _comp
            self._art  = _art

            self.ll = ll
            self.comp = comp
            self.art = art
        pass

    def __repr__(self):
        A = self.A
        B = self.B 
        excl = self.excl

        ll = self.ll
        comp = self.comp
        art = self.art

        if A is None or B is None or A.f is None or B.f is None:
             return "CANNOT COMPARE"
        pass


        CF_brief = "CF(%s,%s,%s) : %s vs %s " % (A.symbol, B.symbol, excl, A.name, B.name ) 
        lines = [CF_brief]
        lines += [A.brief]
        lines += [B.brief]

        ffmt = "%10.3g"
        fmt = "%%10s : %(ffmt)s : %(ffmt)s : %(ffmt)s" % locals()  

        lines += [ fmt % ("lls",   np.abs(ll).max(),   ll.max(),   ll.min()) ]
        lines += [ fmt % ("comps", np.abs(comp).max(), comp.max(), comp.min()) ]  
        lines += [ fmt % ("arts",  np.abs(art).max(),  art.max(),  art.min()) ]  

        return "\n".join(lines)



class ARTPlot(object):
    @classmethod
    def Plot(cls, ax, test, excl=0, incl="ARTQxsp", squeeze=True):
        f = test.f

        R_s = f.art[...,0,0]
        R_p = f.art[...,0,1]
        T_s = f.art[...,0,2]
        T_p = f.art[...,0,3]

        A_s = f.art[...,1,0]
        A_p = f.art[...,1,1]
        R   = f.art[...,1,2]
        T   = f.art[...,1,3]

        A     = f.art[...,2,0]
        A_R_T = f.art[...,2,1]
        wl    = f.art[...,2,2] 
        mct   = f.art[...,2,3]  # minus_cos_theta 

        if squeeze:
             R_s = R_s.squeeze()
             R_p = R_p.squeeze()
             T_s = T_s.squeeze()
             T_p = T_p.squeeze()
             A_s = A_s.squeeze()
             A_p = A_p.squeeze()
             R = R.squeeze()
             T = T.squeeze()
             A = A.squeeze()
             A_R_T = A_R_T.squeeze()
             wl = wl.squeeze()
             mct = mct.squeeze()
        pass


        th2mct_ = lambda th:-np.cos(th*np.pi/180.)
        mct2th_ = lambda mct:np.arccos(-mct)*180./np.pi

        th = mct2th_(mct)

        if "x" in incl:
            if "R" in incl: ax.plot(th, R, label="R", linestyle="dotted" )
            if "T" in incl: ax.plot(th, T, label="T", linestyle="dotted")
            if "A" in incl: ax.plot(th, A, label="A", linestyle="dotted")
            if "Q" in incl: ax.plot(th, A_R_T, label="A_R_T", linestyle="dotted")
        pass
        if "s" in incl:
            if "R" in incl:ax.plot(th, R_s, label="R_s")
            if "T" in incl:ax.plot(th, T_s, label="T_s")
            if "A" in incl:ax.plot(th, A_s, label="A_s")
        pass 
        if "p" in incl:
            if "R" in incl:ax.plot(th, R_p, label="R_p")
            if "T" in incl:ax.plot(th, T_p, label="T_p")
            if "A" in incl:ax.plot(th, A_p, label="A_p")
        pass 


        assert len(t.brewster) == 2 
        brewster_angle = t.brewster*180./np.pi

        brewster = np.zeros( (2, len(brewster_angle), 2) )
        brewster[0,:,0] = brewster_angle
        brewster[0,:,1] = 0. 
        brewster[1,:,0] = brewster_angle
        brewster[1,:,1] = 1. 
        brewster = brewster.reshape(-1,2)

        brewster_sz = 30 
        brewster_color = "red"
        brewster_label = "Brewster"

        ax.scatter( brewster[:,0], brewster[:,1], s=brewster_sz, color=brewster_color, label=brewster_label )

        for x in brewster_angle:
            ax.plot( [x,x], [0,1], linestyle="dashed", color=brewster_color )
        pass





        critical_angle = t.critical[np.isfinite( t.critical )] *180./np.pi
        critical = np.zeros( (2, len(critical_angle), 2 ) )
        critical[0,:,0] = critical_angle
        critical[0,:,1] = 0.
        critical[1,:,0] = critical_angle
        critical[1,:,1] = 1.
        critical = critical.reshape(-1,2)

        critical_sz = 30 
        critical_color = "blue"
        critical_label = "Critical"

        ax.scatter( critical[:,0], critical[:,1], s=critical_sz, color=critical_color, label=critical_label )

        for x in critical_angle:
            ax.plot( [x,x], [0,1], linestyle="dashed", color=critical_color )
        pass




        xx = [0,90,180] 

        edeg = [np.arccos(excl)*180/np.pi,np.arccos(-excl)*180/np.pi] if excl > 0 else []
        xx.extend(edeg)
        for x in xx:
            ax.plot( [ x,  x],   [0, 1], linestyle="dashed" )  
        pass

        extra_ = ["excl: %s " % excl, "incl: %s" % incl]
        for i in range(len(edeg)):
            extra_.append("edeg[%d] : %7.2f " % (i, edeg[i]))
        pass
        extra = "\n".join(extra_)

        ax.text( 125, 0.6, "\n".join([test.layr,extra]))

        sax = ax.secondary_xaxis('top', functions=(th2mct_, mct2th_))
        sax.set_xlabel('mct : -cos(theta) : dot(photon_momentum,surface_normal) ')
        ax.set_xlabel('aoi [degrees] ( 90:180 : reverse stack )' )



    def __init__(self, test, **kwa):
        self.test = test
        self.kwa = kwa
        xtitle = kwa.pop("xtitle", None)

        fig, ax = plt.subplots(1, figsize=SIZE/100.)

        title = test.title 
        if not xtitle is None:
            title = "%s %s" % (title, xtitle)
        pass 
        fig.suptitle(title)   

        self.Plot(ax, test, **kwa)  

        ax.legend(loc=os.environ.get("LOC", "upper right")) 
        fig.show()                

    def __repr__(self):
        kwa = ", ".join(list(map( lambda kv:"%s=\"%s\"" % kv, list(self.kwa.items()) )))   
        return "ARTPlot(%s,%s) # %s  " % (self.test.symbol, kwa, self.test.title ) 


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
    ts = LayrTestSet(symbol="ts")  
    print(repr(ts))
    print(repr(CF(a,b))) # LayrTestSet instanciation populates scope with a,b,c,...

    pmtcat = os.environ.get("LAYRTEST_PMTCAT", "EGet")
    excl = float(os.environ.get("LAYRTEST_EXCL", "0.05"))
    incl = os.environ.get("LAYRTEST_INCL", "ARTQxsp")
    xtitle = "LAYRTEST_INCL %s " % incl

    tt = ts.select(pmtcat)

    t = tt[-1] if len(tt) > 0 else None
    print("pmtcat:%s tt:%d t:%s " % (pmtcat, len(tt), t ))
      
    if not t is None:
       ap = ARTPlot(t, excl=excl, incl=incl, xtitle=xtitle )
    pass 

    if len(tt) > 0:
        rst = ts.cf_table(tt, pmtcat, excl=excl)
        print(rst)
    pass
pass

