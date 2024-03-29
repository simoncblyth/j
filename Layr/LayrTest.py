#!/usr/bin/env python
"""
LayrTest.py
=============

Plot is too busy with everything visible. Use opt to restrict what is included::

    In [4]: ARTPlot(q,opt="Rxsp")
    Out[4]: ARTPlot(q,opt="Rxsp") # j/Layr/LayrTest scan__R12860__gpu_thr_float ni 900 wl 440  

    In [5]: ARTPlot(q,opt="Txsp")
    Out[5]: ARTPlot(q,opt="Txsp") # j/Layr/LayrTest scan__R12860__gpu_thr_float ni 900 wl 440  

    In [6]: ARTPlot(q,opt="Axsp")
    Out[6]: ARTPlot(q,opt="Axsp") # j/Layr/LayrTest scan__R12860__gpu_thr_float ni 900 wl 440  

Notice the very large difference between S and P polarizations.
Its crucial that use the values appropriate for the photon polatization.  

"""
import os, builtins, numpy as np
from opticks.ana.fold import Fold 
from opticks.ana.eget import eintarray_
from opticks.ana.rsttable import RSTTable
SIZE = np.array([1280, 720])
PMTIDX = int(os.environ.get("PMTIDX","0"))


class STR(str):__repr__ = lambda self:str(self) # subclass str : override repr to give str  

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

    def init_meta(self, f):
        assert not f is None
        symbol = f.symbol

        if not f is None and not f.art_meta is None:
            title = f.art_meta.d.get("title",["-"])[0] 
            brief = f.art_meta.d.get("brief",["-"])[0] 
            name = f.art_meta.d.get("name",["-"])[0] 
            label = f.art_meta.d.get("label",["-"])[0] 
            ExecutableName = f.art_meta.d.get("ExecutableName",["-"])[0] 
        else:
            title = "-"
            brief = "-"
            name = "-"
            label = "-"
            ExecutableName = "-"
        pass
        tag = self.Tag(name)

        self.symbol = symbol
        self.title = title
        self.brief = brief
        self.name = name
        self.label = label
        self.ExecutableName = ExecutableName
        self.tag = tag

    def init_lpmt(self, f):
        lpmtid = getattr(f, 'lpmtid', [] )
        if lpmtid is None:
            lpmtid = getattr(f, 'lpmtid_domain', [] ) # SPMT_test using _domain
        pass
        if lpmtid is None: lpmtid = []  

        lpmtcat = getattr(f, 'lpmtcat', [] )
        if lpmtcat is None:
            lpmtcat = getattr(f, 'lpmtcat_domain', [] )
        pass
        if lpmtcat is None: lpmtcat = []  

        assert len(lpmtid) == len(lpmtcat)
        self.lpmtid = lpmtid
        self.lpmtcat = lpmtcat


    def init_art(self, f):
        f_art_ = f.art.squeeze()
        if f_art_.ndim == 3:   # eg (900, 4, 4)
            f_art = f_art_
        elif f_art_.ndim == 4:  # eg (9, 900, 4, 4)
            f_art = f_art_[PMTIDX] 
        else:
            print("unexpected f_art_ shape %s " % str(f_art_.shape))
            assert 0 
        pass
        self.art = f_art
        self.mct =  f_art[:,3,3]

    def init_ll(self, f):
        f_ll_ = f.ll.squeeze()
        if f_ll_.ndim == 5:    # eg (900, 4, 4, 4, 2)
            f_ll = f_ll_
        elif f_ll_.ndim == 6:  # eg (9,900, 4, 4, 4, 2) 
            f_ll = f_ll_[PMTIDX] 
        else:    
            print("unexpected f_ll_ shape %s " % str(f_ll_.shape))
            assert 0
        pass
        self.ll = f_ll

    def init_comp(self, f):
        f_comp_ = f.comp.squeeze()
        if f_comp_.ndim == 4:    # eg (900, 4, 4, 2)
            f_comp = f_comp_
        elif f_comp_.ndim == 5:  # eg (9,900, 4, 4, 2) 
            f_comp = f_comp_[PMTIDX] 
        else:    
            print("unexpected f_comp_ shape %s " % str(f_comp_.shape))
            assert 0
        pass
        self.comp = f_comp

    def init_spec(self, f):

        lpmtid = self.lpmtid

        f_spec = f.spec.squeeze()
        if f_spec.ndim == 2:
            assert f_spec.shape == (4,4)
            nr_first = f_spec[0,0]  # Pyrex rindex
            nr_last = f_spec[3,0]  # Vacuum rindex 
            layr = str(f_spec)
        elif f_spec.ndim in (3,4):
            if f_spec.ndim == 3:
                assert f_spec.shape == (len(f_spec),4,4)
                layr = str(f_spec[0])
            elif f_spec.ndim == 4:
                assert f_spec.shape[0] == len(lpmtid)
                assert f.spec.shape[-2:] == (4,4)
                layr = str(f_spec[PMTIDX,0])
            pass
            nr_first_ = f_spec[...,0,0].ravel()
            nr_last_  = f_spec[...,3,0].ravel()
            assert np.all( nr_first_ == nr_first_[0] )  
            # all Pyrex rindex should be the same, no matter pmtcat or domain scanning  
            assert np.all( nr_last_ == 1. ) 
            # all Vacuum rindex should be 1. 
            nr_first = nr_first_[0]
            nr_last  = nr_last_[0]
        else:
            print("ABORT : unexpectd f_spec.shape %s " % str(f_spec.shape))
        pass
        self.nr_first = nr_first
        self.nr_last = nr_last
        self.layr = layr 
        self.spec = f_spec


    def init_critical(self):
        """
        """
        nr_first = self.nr_first
        nr_last = self.nr_last 
        nr_frac = np.array([nr_last/nr_first,nr_first/nr_last])
        assert nr_frac[0] < 1 
        assert nr_frac[1] > 1 

        brewster = np.array( [np.arctan(nr_frac[0]), np.pi - np.arctan(nr_frac[1]) ] )

        #critical = np.array( [np.arcsin(nr_frac[0]), np.pi - np.arcsin(nr_frac[1]) ] )  
        #self.critical = critical 
        #critical_theta = critical[~np.isnan(critical)][0]
        # one of these will be np.nan, looks like its always the 2nd ? 

        critical_theta = np.arcsin(nr_frac[0])
        critical_theta_degrees = critical_theta*180./np.pi  
        critical_mct = -np.cos(critical_theta)

        self.nr_frac = nr_frac   
        self.brewster = brewster 
        self.critical_theta = critical_theta
        self.critical_theta_degrees = critical_theta_degrees
        self.critical_mct = critical_mct

    def __init__(self, f):
        self.f = f  
        self.init_meta(f)
        self.init_lpmt(f)
        self.init_art(f)
        self.init_ll(f)
        self.init_comp(f)
        self.init_spec(f)
        self.init_critical()

    def __repr__(self):
        return "%s : %s" % (self.symbol, self.title)


def getdirnames(base, prefix="xscan"):
    """
    :param base:
    :param prefix:
    :return sorted list of str: names of directories inside base that start with prefix
    """
    return list(sorted(list(filter(lambda name:name.startswith(prefix),os.listdir(base)))) )


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
    SYMBOLS = "abcdefghijklmnopqrstuvwxyz"


    @classmethod
    def GetNames(cls, ekey, dirpfx ):
        """
        :param ekey: eg "SFOLD", "QFOLD", "MFOLD", "PFOLD"
        :param dirpfx: eg "scan_" "sscan" "qscan"
        """
        base = os.environ.get(ekey, None) 
        names = getdirnames( base, dirpfx ) if not base is None else []
        return base, names


    def __init__(self, symbol="ts"):
        self.symbol = symbol


        l_base, l_names = self.GetNames("LAYRTEST_BASE", "scan_" )
        s_base, s_names = self.GetNames("SFOLD", "sscan")
        q_base, q_names = self.GetNames("QFOLD", "qscan")
        m_base, m_names = self.GetNames("MFOLD", "qscan")
        p_base, p_names = self.GetNames("PFOLD", "qscan")

        # record the base for each name 
        all_bases = []
        for name in l_names:all_bases.append(l_base)
        for name in s_names:all_bases.append(s_base)
        for name in q_names:all_bases.append(q_base)
        for name in m_names:all_bases.append(m_base)
        for name in p_names:all_bases.append(p_base)

        all_names = l_names + s_names + q_names + m_names + p_names
        assert len(all_names) < len(self.SYMBOLS) 
        assert len(all_names) == len(all_bases)

        self.l_base = l_base
        self.l_names = l_names

        self.s_base = s_base
        self.s_names = s_names

        self.q_base = q_base
        self.q_names = q_names

        self.m_base = m_base
        self.m_names = m_names

        self.p_base = p_base
        self.p_names = p_names

        self.all_names = all_names
        self.all_bases = all_bases

        print(" %s.l_base     : %s " % (self.symbol, str(self.l_base)))
        print(" %s.l_names    : %s " % (self.symbol, str(self.l_names)))
        print(" %s.s_base     : %s " % (self.symbol, str(self.s_base)))
        print(" %s.s_names    : %s " % (self.symbol, str(self.s_names)))
        print(" %s.q_base     : %s " % (self.symbol, str(self.q_base)))
        print(" %s.q_names    : %s " % (self.symbol, str(self.q_names)))
        print(" %s.m_base     : %s " % (self.symbol, str(self.m_base)))
        print(" %s.m_names    : %s " % (self.symbol, str(self.m_names)))
        print(" %s.p_base     : %s " % (self.symbol, str(self.p_base)))
        print(" %s.p_names    : %s " % (self.symbol, str(self.p_names)))


        print(" %s.all_names : %s " % (self.symbol, str(self.all_names)))
        print(" %s.all_bases : %s " % (self.symbol, str(self.all_bases)))

        names = [] 
        labels = [] 
        symbols = []
        folds = [] 
        tests = []

        num = len(self.all_names)

        for idx in range(num):
            base = self.all_bases[idx]
            name = self.all_names[idx]
            symbol = self.SYMBOLS[idx]

            fold = Fold.Load(base, name,  symbol=symbol)
            test = LayrTest(fold)
            test.name = name 

            # TODO: examine tea leaves to find actual pmtcat, not guess 
            # HMM: qscan has lpmtid, lpmtcat already, need to add 
            # those to sscan so can treat them together
           
            # NOW : that scan over lpmtid this test label makes no sense  
            if base == s_base:
                test.label = "R12860"
                print("kludge s_base label to %s " % test.label )
            elif base == q_base:
                test.label = "R12860"
                print("kludge q_base label to %s " % test.label )
            elif base == m_base:
                test.label = "R12860"
                print("kludge m_base label to %s " % test.label )
            elif base == p_base:
                test.label = "R12860"
                print("kludge p_base label to %s " % test.label )
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
        tab = np.zeros( [ntt,1+ntt], dtype=np.object )

        for i in range(ntt):
            ti = tt[i]
            label = "%s:%s" % (ti.symbol, ti.tag)
            labels.append(label)
            tab[i,0] = label
            for j in range(ntt):
                if i == j: continue
                tj = tt[j]
                cf = CF(ti,tj,excl)
                qwn = qwns[0] if i > j else qwns[1]   # "art" or "comp"
                cfv = np.abs( getattr(cf, qwn) ).max() 
                pass
                tab[i,j+1] = cfv
            pass
        pass
        rst = RSTTable.Rdr(tab, labels, rfm="%10.4g", left_wid=30, hfm="%10s", left_rfm="%30s", left_hfm="%30s" )
        return tab, STR(rst) 

    def __repr__(self):
        lines = []
        lines.append("CFLayrTest")
        for idx in range(len(self.tests)):
            test = self.tests[idx]
            symbol = self.symbols[idx]
            label = self.labels[idx]
            name = self.names[idx]
            lines.append("%2s : %15s : %20s : %s " % (symbol, label, test.ExecutableName, name))    
        pass
        return "\n".join(lines)



class CF(object):
    """
    Compare two LayrTest objects 
    """
    def __init__(self, A, B, mct_excl=0, exclude_pole=True, exclude_critical=True ):
        """
        :param A:
        :param B:
        :param mct_excl: center to edge size of exclusion bands
        :param exclude_pole: bool around mct zero (90 degrees theta) 
        :param exclude_critical: bool around critical_mct (close to 42.42 degrees for Pyrex->Vacuum)
        """
        self.A = A 
        self.B = B 
        self.mct_excl = mct_excl
        self.exclude_pole = exclude_pole
        self.exclude_critical = exclude_critical

        if A is None or B is None or A.f is None or B.f is None:
            self.ll = None
            self.comp = None
            self.art = None
        else:
            ab_mct = np.abs(A.mct-B.mct)
            assert ab_mct.max() < 1e-6

            mct = A.mct 
            mct_critical = A.critical_mct 

            mct_pole = np.abs(mct) < mct_excl  
            mct_critical = np.abs(mct - mct_critical) < mct_excl

            if exclude_pole == True and exclude_critical == False: 
                 mct_sel = ~mct_pole
            elif exclude_pole == False and exclude_critical == True: 
                 mct_sel = ~mct_critical
            elif exclude_pole == False and exclude_critical == False: 
                 mct_sel = np.abs(mct) >= 0.   # all True  
            elif exclude_pole == True and exclude_critical == True:
                 mct_sel = np.logical_and( ~mct_pole, ~mct_critical )
            pass  

            mct_pole_count = np.count_nonzero(mct_pole)   
            mct_critical_count = np.count_nonzero(mct_critical)   
            mct_sel_count = np.count_nonzero(mct_sel)

            self.mct_pole_count = mct_pole_count
            self.mct_critical_count = mct_critical_count
            self.mct_sel_count = mct_sel_count


            _ll = A.ll - B.ll
            _comp = A.comp - B.comp
            _art = A.art - B.art
            _mct = A.mct  # NOT diff for mct, as should be very matched 

            ll = _ll[mct_sel]
            comp = _comp[mct_sel]
            art = _art[mct_sel]
            mct = _mct[mct_sel]

            self._ll   = _ll
            self._comp = _comp
            self._art  = _art
            self._mct  = _mct 

            self.ll = ll
            self.comp = comp
            self.art = art
            self.mct = mct 
        pass

    def __repr__(self):
        A = self.A
        B = self.B 

        ll = self.ll
        comp = self.comp
        art = self.art

        if A is None or B is None or A.f is None or B.f is None:
             return "CANNOT COMPARE"
        pass
        args = (A.symbol, B.symbol, self.mct_excl, self.exclude_pole, self.exclude_critical, A.name, B.name ) 
        CF_brief = "CF(%s,%s,%s,exclude_pole=%s,exclude_critical=%s) : %s vs %s " % args
        lines = [CF_brief]
        lines += [A.brief]
        lines += [B.brief]

        ffmt = "%10.3g"
        fmt = "%%10s : %(ffmt)s : %(ffmt)s : %(ffmt)s" % locals()  

        lines += [ fmt % ("ll",   np.abs(ll).max(),   ll.max(),   ll.min()) ]
        lines += [ fmt % ("comp", np.abs(comp).max(), comp.max(), comp.min()) ]  
        lines += [ fmt % ("art",  np.abs(art).max(),  art.max(),  art.min()) ]  

        lines += [ "mct pole/critical/sel %d/%d/%d " % (self.mct_pole_count, self.mct_critical_count, self.mct_sel_count)] 

        return "\n".join(lines)



class ARTPlot(object):
    @classmethod
    def PlotBrewster(cls, ax, test, **kwa ):

        assert len(test.brewster) == 2 
        brewster_angle = test.brewster*180./np.pi

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

    @classmethod
    def PlotCritical(cls, ax, test, **kwa):

        #critical_angle = test.critical[np.isfinite( test.critical )] *180./np.pi
        critical_angle = np.array( [test.critical_theta_degrees, test.critical_theta_degrees] ) 
          
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

    @classmethod
    def PlotVertical(cls, ax, test, **kwa ):
        verticals = kwa.pop("verticals", [])
        for x in verticals:
            ax.plot( [ x,  x],   [0, 1], linestyle="dashed" )  
        pass

    @classmethod
    def PlotAnnotate(cls, ax, test, **kwa ):
        excl = kwa.pop("excl", 0)
        opt = kwa.pop("opt", "")
        excl_deg = kwa.pop("excl_deg", [])

        extra_ = ["excl: %s " % excl, "opt: %s" % opt]
        for i in range(len(excl_deg)):
            extra_.append("edeg[%d] : %7.2f " % (i, excl_deg[i]))
        pass
        extra = "\n".join(extra_)

        ax.text( 125, 0.6, "\n".join([test.layr,extra]))


    @classmethod
    def Plot(cls, ax, test, **kwa ):

        excl = kwa.pop("excl", 0)
        opt = kwa.pop("opt", "ARTQxsp")
        pidx = kwa.pop("pidx", None)

        #art = test.f.art  ## multiple lpmtid 
        #art = test.art    ## one PMTIDX 

        art = test.art if pidx is None else  test.f.art[pidx] 

        # rationalized layout 
        As   = art[:,0,0]
        Ap   = art[:,0,1]
        Aa   = art[:,0,2]
        A_   = art[:,0,3]

        Rs   = art[:,1,0]
        Rp   = art[:,1,1]
        Ra   = art[:,1,2]
        R_   = art[:,1,3]

        Ts   = art[:,2,0]
        Tp   = art[:,2,1]
        Ta   = art[:,2,2]
        T_   = art[:,2,3]

        SF   = art[:,3,0]  ## S-pol-power-fraction 
        wl   = art[:,3,1]  ## wavelength 
        ARTa = art[:,3,2]  ## ? probably Aa+Ra+Ta which should be 1  
        mct  = art[:,3,3]  ## minus_cos_theta 

        th2mct_ = lambda th:-np.cos(th*np.pi/180.)
        mct2th_ = lambda mct:np.arccos(-mct)*180./np.pi

        th = mct2th_(mct)

        if "x" in opt:
            if "R" in opt: ax.plot(th, R_, label="R" )
            if "T" in opt: ax.plot(th, T_, label="T" )
            if "A" in opt: ax.plot(th, A_, label="A" )
            if "Q" in opt: ax.plot(th, ARTa, label="ARTa", linestyle="dotted")
        pass
        if "s" in opt:
            if "R" in opt:ax.plot(th, Rs, label="Rs")
            if "T" in opt:ax.plot(th, Ts, label="Ts")
            if "A" in opt:ax.plot(th, As, label="As")
        pass 
        if "p" in opt:
            if "R" in opt:ax.plot(th, Rp, label="Rp")
            if "T" in opt:ax.plot(th, Tp, label="Tp")
            if "A" in opt:ax.plot(th, Ap, label="Ap")
        pass 
        if "a" in opt:
            if "R" in opt:ax.plot(th, Ra, label="Ra", linestyle="dotted")
            if "T" in opt:ax.plot(th, Ta, label="Ta", linestyle="dotted")
            if "A" in opt:ax.plot(th, Aa, label="Aa", linestyle="dotted")
        pass 

        sax = ax.secondary_xaxis('top', functions=(th2mct_, mct2th_))
        sax.set_xlabel('mct : -cos(theta) : dot(photon_momentum,surface_normal) ')
        ax.set_xlabel('aoi [degrees] ( 90:180 : reverse stack )' )
        cls.AddLabel(ax, opt)

    @classmethod
    def AddLabel(cls, ax, label ):
        ax.text(0.0, 1.0, label, 
           verticalalignment='bottom', 
           horizontalalignment='right',
           transform=ax.transAxes,
           bbox={'facecolor': 'red', 'alpha': 0.1, 'pad': 10},
           fontsize=30
          )


    def __init__(self, test, **kwa):
        """
        :param test: LayrTest instance 
        """
        self.test = test
        self.kwa = kwa
        xtitle = kwa.pop("xtitle", None)
        excl = kwa.pop("excl", 0)

        verticals = [0,90,180] 
        edeg = [np.arccos(excl)*180/np.pi,np.arccos(-excl)*180/np.pi] if excl > 0 else []
        verticals.extend(edeg)
        kwa["verticals"] = verticals
        kwa["pidx"] = None


        fig, ax = plt.subplots(1, figsize=SIZE/100.)

        title = test.title 
        if not xtitle is None:
            title = "%s %s" % (title, xtitle)
        pass 
        fig.suptitle(title)   

        PIDX = eintarray_("PIDX", "0")  # comma delimited list of pidx to use
        self.PIDX = PIDX 

        for pidx in PIDX:
            kwa["pidx"] = pidx 
            self.Plot(ax, test, **kwa)  
        pass

        self.PlotBrewster(ax, test, **kwa)  
        self.PlotCritical(ax, test, **kwa)  
        self.PlotAnnotate(ax, test, **kwa)  
        self.PlotVertical(ax, test, **kwa)  

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

    pmtcat = os.environ.get("LAYRTEST_PMTCAT", "EGet")
    excl = float(os.environ.get("LAYRTEST_EXCL", "0.05"))
    opt = os.environ.get("OPT", "ARTQxsp")
    xtitle = "OPT %s " % opt

    print("## ts = LayrTestSet(symbol=\"ts\") " ) 
    ts = LayrTestSet(symbol="ts")  

    print("## repr(ts) ")
    print(repr(ts))

    print("## cf_ab  = CF(a,b,excl)   # excl: %s " % excl )
    cf_ab  = CF(a,b,excl) # LayrTestSet instanciation populates scope with a,b,c,...

    print("## repr(cf_ab) ")
    print(repr(cf_ab)) 
    print("## ts.select(pmtcat)  # pmtcat: %s  " % pmtcat)
    tt = ts.select(pmtcat)

    t = tt[-1] if len(tt) > 0 else None
    print("## pmtcat:%s tt:%d t:%s " % (pmtcat, len(tt), t ))
      
    if not t is None:
       print("## ARTPlot ")
       ap = ARTPlot(t, excl=excl, opt=opt, xtitle=xtitle )
    pass 

    if len(tt) > 0:
        print("## repr(ts) ")
        print(repr(ts))
        print("## tab, rst = ts.cf_table(tt, pmtcat, excl=excl) # excl %s " % excl ) 
        tab, rst = ts.cf_table(tt, pmtcat, excl=excl)
        print("## rst ")
        print(rst)
    pass
pass

