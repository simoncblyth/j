#!/usr/bin/env python
"""
ntds.py : plotting two SEvt
============================

::

    MODE=2 ./ntds.sh ana
    MODE=3 ./ntds.sh ana

"""
import os, textwrap, numpy as np, re
from opticks.ana.fold import Fold
from opticks.ana.p import * 
from opticks.sysrap.sevt import SEvt
from opticks.ana.base import PhotonCodeFlags

pcf = PhotonCodeFlags() 
fln = pcf.fln
fla = pcf.fla

color_ptn = re.compile("#(\S*)\s")  # single char color codes in ppos string  "#c "  
ENVOUT = os.environ.get("ENVOUT", None)
MODE =  int(os.environ.get("MODE", "2"))
N = int(os.environ.get("VERSION", "1"))
GLOBAL = int(os.environ.get("GLOBAL","0")) == 1 
SLIM = float(os.environ.get("SLIM","1.0"))
CHECK = os.environ.get("CHECK", "all_point" )
UTID = os.environ.get("UTID", CHECK )



if MODE in [2,3]:
    from opticks.ana.pvplt import * 
pass

if __name__ == '__main__':
    axes = 0,2  # X,Z
    H,V = axes
    lim = np.array([[-500.,500.],[-250.,250.],[-250.,250.]])
    lim *= SLIM

    if N == -1: 
        a = SEvt.Load("$AFOLD",symbol="a")
        b = SEvt.Load("$BFOLD",symbol="b")
        t = b
        syms = ['a','b']
        evts = [ a, b ]
    elif N == 0:
        a = SEvt.Load("$AFOLD",symbol="a")
        b = None
        syms = ['a']
        evts = [ a,]
        t = a 
    elif N == 1:
        a = None
        b = SEvt.Load("$BFOLD",symbol="b")
        syms = ['b']
        evts = [ b,]
        t = b 
    else:
        assert(0)
    pass
    assert len(syms) == len(evts)

    if not a is None:print(repr(a))
    if not b is None:print(repr(b))

    w_ = "np.where(np.logical_and( t.eph == 4, t.qq == 4 ))"


    defhist = "SI BT BT BT SD"  
    hist = os.environ.get("HIST", defhist).encode("utf-8")

    EXPL = ""

    if CHECK == "EPH_NBOUND_PYREX_AB":
        w_ = "np.where(np.logical_and( t.eph == 4, t.qq == 4 ))"
        EXPL = "N=1 needs pmt_log sensitive -> more ProcessHits:false Pyrex AB" 
    elif CHECK == "EPH_NEDEP":
        w_ = "np.where(t.eph == 3)"
        EXPL = "Lots of edep 0. N=0,1 as multiple volumes have to be sensitive"
    elif CHECK == "NOSC":
        w_ = "np.where(t.nosc)[0]" 
        EXPL = "Photons without scatter SC, should stay in plane "
    elif CHECK == "hist":
        w_ = "np.where(np.char.startswith(t.q,hist))"
        EXPL = "Photons with histories starting with HIST [%s] " % hist.decode("utf-8")   
    pass

    exprs = r"""
    np.c_[np.unique(t.eph,return_counts=True)]   # point level ProcessHits EPH enum 
    np.c_[np.unique(t.ep,return_counts=True)]    # photon level ProcessHits EPH enum 
    np.unique(t.ep,return_counts=True)[1].sum()  # t.ep count total 


    len(t.ep[t.ep >= 7])               # 7:EPH_NDECULL, 8:EPH_YMERGE, 9:EPH_YSAVE
    len(np.where(t.qq == pcf.SD)[0])   # photons with SD in history 

    np.c_[np.unique(t.qq[np.where(t.eph == 9)], return_counts=True)] # EPH_YSAVE all SD
    np.c_[np.unique(t.qq[np.where(t.eph == 7)], return_counts=True)] # EPH_NDECULL all SD
    np.c_[np.unique(t.qq[np.where(t.eph == 4)], return_counts=True)] # EPH_NBOUND a:none b:all AB
    np.c_[np.unique(t.qq[np.where(t.eph == 3)], return_counts=True)] # EPH_NEDEP ?

    """
    exprs_ = list(filter(None,textwrap.dedent(exprs).split("\n")))

    num = 4 
    ppos_ = {}
    for i in range(num): ppos_[i] = "None" ; 

    if CHECK == "all_point0":
        ppos_[0] = "t.f.record[:,:,0,:3].reshape(-1,3)  #r all points "
    elif CHECK == "all_point":
        ppos_[0] = "t.f.record[:,:,0,:3].reshape(-1,3)  #c : all points "
        ppos_[1] = "t.f.record[:,0,0,:3].reshape(-1,3)  #g : first "
        ppos_[2] = "t.f.photon[:,0,:3]                  #r : last "
    elif CHECK == "few_point":
        ppos_[0] = "t.f.record[:,0,0,:3] #r 0-position   "
        ppos_[1] = "t.f.record[:,1,0,:3] #g 1-position   "
        ppos_[2] = "t.f.record[:,2,0,:3] #b 2-position   "
        ppos_[3] = "t.f.photon[:,0,:3]  #c final photon position "
    elif CHECK == "sd_point":
        ppos_[0] = "t.f.record[np.where(t.qq == pcf.SD)][:,0,:3]  #g SD position "    
    elif CHECK == "sa_point":
        ppos_[0] = "t.f.record[np.where(t.qq == pcf.SA)][:,0,:3]  #g SA position "    
    elif CHECK in ["EPH_NBOUND_PYREX_AB", "EPH_NEDEP", "w_point"]:
        ppos_[0] = "t.f.record[w][:,0,:3] #y %s " % w_
    elif CHECK in ["NOSC"]:
        ppos_[0] = "t.f.record[np.where(t.nosc)][:,:,0,:3].reshape(-1,3) "
    elif CHECK in ["NOSCAB"]:
        ppos_[0] = "t.f.record[np.where(t.noscab)][:,:,0,:3].reshape(-1,3) "
    elif CHECK == "hist":
        ppos_[0] = "t.f.record[w][:,0,:3]  #y %s " % w_ 
    pass 

    ppos = {'a':{}, 'b':{} }
    uppos = {'a':{}, 'b':{} }
    color = {'a':{}, 'b':{} }
    version = {'a':0, 'b':1 }

    for i in range(len(syms)):
        sym = syms[i]
        w = eval(w_)

        for j in range(num): 
            expr = ppos_[j]
            if expr == "None": continue
            uexpr = expr.replace("t.","%s." % sym)
            vexpr = eval(uexpr)

            m = color_ptn.search(expr)
            col = m.groups()[0] if not m is None else "black"

            ppos[sym][j] = vexpr
            uppos[sym][j] = uexpr
            color[sym][j] = col
        pass
    pass

    dump_expr = True
    if dump_expr:
        for expr in exprs_: 
            for i in range(len(syms)):
                sym = syms[i]
                uexpr = expr.replace("t.","%s." % sym)
                vexpr = eval(uexpr)
                isint = np.issubdtype(type(vexpr), np.integer)  
                fmt = "%(vexpr)9d : %(uexpr)s " if isint else "\n%(uexpr)s\n\n%(vexpr)r\n"
                print(fmt % locals() )
            pass
        pass
    pass

    tid = {}
    base = {}
    print("[i syms loop syms:%s " % str(syms) )
    for i in range(len(syms)):
        sym = syms[i]
        evt = evts[i]
        tid[sym] = evt.ID
        base[sym] = evt.f.base

        elem = []
        for j in range(num): 
            expr = ppos_[j]
            if expr == "None": continue
            elem.append("%s:%s" % (color[sym][j],uppos[sym][j]))
        pass

        label = "\n".join( ["(%s) %s : %s " % (sym, tid[sym], EXPL)] + elem )

        if MODE in [0,1]:
            print("not plotting as MODE %d in environ" % MODE )
        elif MODE == 2:            
            pl = mpplt_plotter(label=label)
            fig, axs = pl
            assert len(axs) == 1
            ax = axs[0]
        elif MODE == 3:
            pl = pvplt_plotter(label)
            os.environ["EYE"] = "0,100,165"
            os.environ["LOOK"] = "0,0,165"
            pvplt_viewpoint(pl)
            pvplt_frame(pl, evt.f.sframe )
        pass

        if not GLOBAL:
            if MODE == 2:
                ax.set_xlim(*lim[H]) 
                ax.set_ylim(*lim[V])
            elif MODE == 3:
                pass
            pass
        pass

        print("[j qwn loop num:%d " % num )
        for j in range(num): 
            expr = ppos_[j]
            if expr == "None": continue

            vexpr = ppos[sym][j]
            col = color[sym][j]

            gpos = np.ones( [len(vexpr), 4 ] )
            gpos[:,:3] = vexpr
            lpos = np.dot( gpos, evt.f.sframe.w2m ) 
            upos = gpos if GLOBAL else lpos

            if "ALT" in os.environ:  ## checking alternative way to do the global to local transform
                gpos_alt = evt.f.record[:,:,0].copy()          # (NUM,32,4) : all point "post" (position, time)
                gpos_alt[...,3] = 1                          # 1. for position transform
                lpos_alt = np.dot( gpos_alt, evt.f.sframe.w2m ) 
                upos_ = gpos_alt if GLOBAL else lpos_alt 
                upos = upos_.reshape(-1,4)
            pass

            if MODE in [0,1]:
                print("expr  : %s " % expr )
                print("vexpr :\n%s " % vexpr )
                print("gpos  :\n%s " % gpos )
                print("lpos  :\n%s " % lpos )
                print("upos  :\n%s " % upos )
            elif MODE == 2:
                ax.scatter( upos[:,H], upos[:,V], s=1, c=col )
            elif MODE == 3:
                pl.add_points(upos[:,:3], color=col )
            pass
        pass
        print("]j qwn num loop num:%d " % num )

        if MODE == 2:
            fig.show()
        elif MODE == 3:
            pl.show()
        pass

        if MODE == 2 and not ENVOUT is None:
            ## associate metadata with a plot, used for figure naming back in bash 
            envout = "\n".join([
                           "export ENVOUT_PATH=%s" % ENVOUT,
                           "export ENVOUT_SYM=%s" % sym,
                           "export ENVOUT_CAP_STEM=%s" % tid[sym],
                           "export ENVOUT_CAP_BASE=%s" % base[sym],
                           "export ENVOUT_VERSION=%s" % version[sym],
                           ""  
                           ])  
            open(ENVOUT, "w").write(envout)
            print(envout)
        pass
    pass
    print("]i syms loop syms:%s " % str(syms) )
pass


