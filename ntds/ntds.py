#!/usr/bin/env python
"""
ntds.py : scatter plotting in 2D or 3D of (A,B) SEvt in separate windows
==========================================================================

Control the selection of what to scatter plot with the CHECK envvar. 



::

    MODE=2 ./ntds.sh ana
    MODE=3 ./ntds.sh ana


Exiting PyVista Windows
-------------------------

Deleting pyvista windows with the red dot at top left seems to work fine, 
but it causes subsequent exits from ipython to take 10s or more. 
Instead simply cmd-Q whilst the pyvista window is frontmost to exit 
the window cleanly and avoid the slow ipython exit.  


Flickering Overlayed Plot Point Issue
---------------------------------------

Problem with pyvista plotting all points (cyan) and then 
last point on top with different (red) color is that the 
red photon point is degenerate with the cyan points so 
the appearance flickers as viewpoint changes. 
 
Want to exclude the last point in the cyan step point records so the 
final red photon point is not degenerate with the last cyan step point.
BUT trying the below doesnt work::

      t.f.record[:,1:t.n,0,:3].reshape(-1,3) 

HMM could do it with where and selections according to n but thats not convenient 
trying to do this with arrays of indices (or with tuple indices) 
is slow and consumes lots of memory and is prone to crashing and dumping huge files
... maybe need to do it with a general C extension to NumPy or less general ufunc ?  

TODO : see if simply increasing the size of the last point that want to win 
       can avoid the issue without any complicated point selection


"""
import os, textwrap, numpy as np, re
from collections import defaultdict
tree = lambda: defaultdict(tree)
# dd = tree()

from opticks.ana.fold import Fold
from opticks.ana.p import * 
from opticks.sysrap.sevt import SEvt
from opticks.ana.base import PhotonCodeFlags

pcf = PhotonCodeFlags() 
fln = pcf.fln
fla = pcf.fla

color_ptn = re.compile("#(\S*)\s")  # single char color codes in ppos string, eg "#c "  c:cyan
size_ptn = re.compile("@(\S*)\s")  # size float string within ppos string, eg "@2 "  

ENVOUT = os.environ.get("ENVOUT", None)
N = int(os.environ.get("VERSION", "1"))
GLOBAL = int(os.environ.get("GLOBAL","0")) == 1 
SLIM = float(os.environ.get("SLIM","1.0"))
CHECK = os.environ.get("CHECK", "all_point" )
W = os.environ.get("W", "ALL" )
UTID = os.environ.get("UTID", CHECK )


MODE =  int(os.environ.get("MODE", "2"))
if MODE in [2,3]:
    from opticks.ana.pvplt import * 
pass


def get_w_(_, sym):
    """
    :param W: string picking photon selection
    :param sym: "a" or "b" symbol of SEvt 
    :return w_, EXPL: w_ string is evaluated to where expression w which is used as a selection by some of the CHECK 
    """

    if _ == "EPH_NBOUND_PYREX_AB":
        w_ = "np.where(np.logical_and( t.eph == 4, t.qq == 4 ))"
        EXPL = "N=1 needs pmt_log sensitive -> more ProcessHits:false Pyrex AB" 
    elif _ == "EPH_NEDEP":
        w_ = "np.where(t.eph == 3)"
        EXPL = "Lots of edep 0. N=0,1 as multiple volumes have to be sensitive"
    elif _ == "NOSC":
        w_ = "np.where(t.nosc)[0]" 
        EXPL = "Photons without scatter SC, should stay in plane "
    elif _ == "NOIIX":
        w_ = "np.where(t.iix < 0)[0]" 
        EXPL = "Photons with iix < 0 "
    elif _ == "IIX":
        w_ = "np.where(t.iix > -1)[0]" 
        EXPL = "Photons with iix > -1 "
    elif _ == "IIX_EQ":
        IIX_EQ = int(os.environ.get("IIX_EQ","0"))
        w_ = "np.where(t.iix == %(IIX_EQ)d)[0]" % locals() 
        EXPL = "IIX_EQ : Photons with iix ==  %(IIX_EQ)d " % locals()
    elif _ == "IIX_NEQ":
        IIX_NEQ = int(os.environ.get("IIX_NEQ","0"))
        w_ = "np.where(t.iix != %(IIX_NEQ)d)[0]" % locals() 
        EXPL = "IIX_NEQ : Photons with iix != %(IIX_NEQ)d " % locals()
    elif _ == "hist":
        defhist = "TO BT BT BT BT SA"  
        hist = os.environ.get("HIST", defhist).encode("utf-8")
        w_ = "np.where(np.char.startswith(t.q,%(hist)s))[0]" % locals()
        EXPL = "Photons with histories starting with HIST [%s] " % hist.decode("utf-8")   
    elif _ == "POINT_MIN":
        POINT = int(os.environ.get("POINT","25"))
        w_ = "np.where(t.n > %(POINT)d)" % locals()
        EXPL = "POINT_MIN photons with more than POINT:%(POINT)d step points" % locals()
    elif _ == "POINT_MAX":
        POINT = int(os.environ.get("POINT","25"))
        w_ = "np.where(t.n < %(POINT)d)" % locals()
        EXPL = "POINT_MAX photons with less than POINT:%(POINT)d step points" % locals()
    elif _ == "PID":
        PID = int(os.environ.get("PID","9706"))
        w_ = "np.where(t.f.photon.view(np.int32)[:,3,2] == %(PID)s)" % locals()
        EXPL = "select single photon by PID %(PID)s " % locals()
    elif _ == "OTHER":
        w_ = "np.where(np.logical_and( t.eph == 4, t.qq == 4 ))"
        EXPL = ""
    elif _ == "ALL":
        w_ = "np.where(t.n > -1)" 
        EXPL = "placeholder select everything"
    elif _ == "US_MAX":
        US = int(os.environ.get("US","1000"))
        w_ = "np.where(t.ss < %(US)d)" % locals()
        EXPL = "US_MAX : photons with processing time less than US:%(US)d (microsecond)" % locals()
    elif _ == "US_MIN":
        US = int(os.environ.get("US","1000"))
        w_ = "np.where(t.ss > %(US)d)" % locals()
        EXPL = "US_MIN : photons with processing time greater than US:%(US)d (microsecond)" % locals()
    elif _ == "HC":
        HC = int(os.environ.get("HC","0"))
        w_ = "np.where(t.hc == %(HC)d)" % locals()
        EXPL = "HC : photons with HC:%(HC)d ProcessHits calls" % locals()
    else:
        w_ = "np.where(t.n > -1)" 
        EXPL = "placeholder select everything"
    pass
    ew_ = w_.replace("t.","%s."% sym)
    return ew_, EXPL



if __name__ == '__main__':
    axes = 0,2  # X,Z
    H,V = axes

    ## thats a PMT-ish sized box
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


    ## ppos_ strings choose the point coordinates to scatter plot  
    num = 4 
    ppos_ = {}
    for i in range(num): ppos_[i] = "None" ; 

    if CHECK == "all_point0":
        ppos_[0] = "t.f.record[:,:,0,:3].reshape(-1,3)  #r all points "
    elif CHECK == "all_point":
        ppos_[0] = "t.f.record[w][:,:,0,:3].reshape(-1,3)  #c @2 : all points "
        ppos_[1] = "t.f.record[w][:,0,0,:3].reshape(-1,3)  #g @5 : first "
        ppos_[2] = "t.f.photon[w][:,0,:3]                  #r @4 : last "
    elif CHECK == "not_first":
        ppos_[0] = "t.f.record[:,1:,0,:3].reshape(-1,3)  #c : not first "
        ppos_[1] = "t.f.photon[:,0,:3]                  #r : last "
    elif CHECK == "not_first_only":
        ppos_[0] = "t.f.record[:,1:,0,:3].reshape(-1,3)  #c : not first "
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
        ppos_[0] = "t.f.record[np.where(t.noscab)][:,:,0,:3].reshape(-1,3)  #w "
    elif CHECK in ["hist", "select", "PID"]:
        ppos_[0] = "t.f.record[w][:,:,0,:3].reshape(-1,3)  #c %s " % w_ 
    pass 

    ppos = tree()
    uppos = tree()
    color = tree()
    version = tree()
    size = tree()
    high = tree()
    wsel_ = tree()

    version['a'] = 0  
    version['b'] = 1 
    # HMM: thats an assumption, TODO: extract version from evt metadata

    WW = W.split(",")

    for i in range(len(syms)):
        sym = syms[i]
        for j in range(len(WW)):
            w_, EXPL = get_w_(WW[j], sym)
            wsel_[sym][j] = w_
            w = eval(w_)

            # over potential sets of points to scatter plot 
            for k in range(num): 
                expr = ppos_[k]
                if expr == "None": continue
                uexpr = expr.replace("t.","%s." % sym)
                vexpr = eval(uexpr)

                cm = color_ptn.search(expr)  # match single char following hash 
                col = cm.groups()[0] if not cm is None else "black"

                sm = size_ptn.search(expr)  # match single char following @
                sz = float(sm.groups()[0]) if not sm is None else 1

                ppos[sym][j][k] = vexpr
                uppos[sym][j][k] = uexpr
                color[sym][j][k] = col
                size[sym][j][k] = sz 
                high[sym][k][k] = j > 0 
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
        for j in range(len(WW)):
            w_, EXPL = get_w_(WW[j], sym)
            elem = []
            for k in range(num): 
                expr = ppos_[k]
                if expr == "None": continue
                if j == 0:
                    elem.append("%s:%s" % (color[sym][j][k],uppos[sym][j][k]))
                pass
            pass
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
            pvplt_viewpoint(pl)   # sensitive to EYE, LOOK, UP envvars
            pvplt_frame(pl, evt.f.sframe, local=not GLOBAL )
        pass

        if not GLOBAL:
            if MODE == 2:
                ax.set_xlim(*lim[H]) 
                ax.set_ylim(*lim[V])
            elif MODE == 3:
                pass
            pass
        pass
        for j in range(len(WW)):
            print("[k qwn loop num:%d " % num )
            for k in range(num): 
                expr = ppos_[k]
                if expr == "None": continue

                pp = ppos[sym][j][k]
                col = color[sym][j][k]
                siz = size[sym][j][k]

                rpp = np.sqrt(np.sum(pp*pp, axis=1 ))  # global distance to origin 
                if not "NO_SUPPRESS" in os.environ:
                    pp = pp[rpp > 0]   # suppress points at origin (typically unfilled)
                pass

                gpos = np.ones( [len(pp), 4 ] )
                gpos[:,:3] = pp
                lpos = np.dot( gpos, evt.f.sframe.w2m ) 
                upos = gpos if GLOBAL else lpos

                if "ALT" in os.environ:  ## checking alternative way to do the global to local transform
                    gpos_alt = evt.f.record[:,:,0].copy()          # (NUM,32,4) : all point "post" (position, time)
                    gpos_alt[...,3] = 1                          # 1. for position transform
                    lpos_alt = np.dot( gpos_alt, evt.f.sframe.w2m ) 
                    upos_ = gpos_alt if GLOBAL else lpos_alt 
                    upos = upos_.reshape(-1,4)
                pass


                EDL = "EDL" in os.environ
                RPS = "RPS" in os.environ
                SIZ = float(os.environ.get("SIZ",siz))
                print(" MODE:%s EDL:%d RPS:%d SIZ:%s siz:%s " % (MODE,EDL,RPS,SIZ,siz))

                if MODE in [0,1]:
                    print("expr  : %s " % expr )
                    print("pp    :\n%s " % pp )
                    print("gpos  :\n%s " % gpos )
                    print("lpos  :\n%s " % lpos )
                    print("upos  :\n%s " % upos )
                elif MODE == 2:
                    ax.scatter( upos[:,H], upos[:,V], s=SIZ, c=col )
                elif MODE == 3:
                    pl.add_points(upos[:,:3], color=col, point_size=SIZ, render_points_as_spheres=RPS )
                    if EDL: pl.enable_eye_dome_lighting()
                pass
            pass
            print("]k qwn num loop num:%d " % num )
        pass

        if MODE == 2:
            fig.show()
        elif MODE == 3:
            pl.show()
        pass

        if MODE in [2,3] and not ENVOUT is None:
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


