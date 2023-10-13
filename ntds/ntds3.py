#!/usr/bin/env python
"""
ntds3.py
==========

Use via bash script::

    PICK=AB MODE=2 SEL=BOX ~/j/ntds/ntds3.sh 
    PICK=AB MODE=3 SEL=BOX ~/j/ntds/ntds3.sh 

"""
import os, logging, numpy as np

print("[from opticks.sysrap.sevt import SEvt, SAB")
from opticks.sysrap.sevt import SEvt, SAB
print("]from opticks.sysrap.sevt import SEvt, SAB")

from opticks.ana.p import cf  

log = logging.getLogger(__name__)

GLOBAL = int(os.environ.get("GLOBAL","0")) == 1
MODE = int(os.environ.get("MODE","3")) 
PICK = os.environ.get("PICK","A") 
SEL = os.environ.get("SEL","") 
BOX = float(os.environ.get("BOX","500")) 
H,O,V = 0,1,2  # horizontal, other, vertical  (X,Y,Z)


APID = int(os.environ.get("APID","0")) 
BPID = int(os.environ.get("BPID","0")) 

if MODE in [2,3]:
    from opticks.ana.pvplt import *   
    # HMM this import overrides MODE, so need to keep defaults the same 
pass



def onephotonplot(pl, e ):
    """
    :param pl: MODE 2/2 plotter objects
    :param e: SEvt instance
    """
    if e is None: return
    if e.pid < 0: return

    print("onephotonplot e.pid %d " % e.pid )

    if not hasattr(e,'l'): return
    if e.l is None: return
    print("onephotonplot e.pid %d PROCEED " % e.pid )

    rpos =  e.l[:,:3] + e.off

    if MODE == 2:
        fig, axs = pl
        assert len(axs) == 1
        ax = axs[0]
        if True:
            mpplt_add_contiguous_line_segments(ax, rpos, axes=(H,V), label=None )
            #self.mp_plab(ax, f)
        pass
        #if "nrm" in f.opt:
        #    self.mp_a_normal(ax, f)  
        #pass
    elif MODE == 3:
        pass
        pvplt_add_contiguous_line_segments(pl, rpos )
    pass



if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    print("GLOBAL:%d MODE:%d SEL:%s" % (GLOBAL,MODE, SEL))

    a = SEvt.Load("$AFOLD", symbol="a")
    b = SEvt.Load("$BFOLD", symbol="b")
    #print(repr(a))
    #print(repr(b))

    ab = SAB(a,b)
    print(repr(ab))


    ahit_ = a.f.hit[:,1,3].view(np.int32)   ## iindex
    bhit_ = b.f.hit[:,1,3].view(np.int32)  

    ahid_ = a.f.hit[:,3,1].view(np.int32)   ## identity
    bhid_ = b.f.hit[:,3,1].view(np.int32)

    ahit = np.c_[np.unique( ahit_, return_counts=True )] 
    bhit = np.c_[np.unique( bhit_, return_counts=True )] 

    ahid = np.c_[np.unique( ahid_, return_counts=True )]
    bhid = np.c_[np.unique( bhid_, return_counts=True )] 


    #sli="[:]"  allowing everything makes for big tables of low stat histories
    sli="[:15]"
    at = a.minimal_qtab(sli=sli)  
    bt = b.minimal_qtab(sli=sli)  

    #print("at\n",at)
    #print("bt\n",bt)


    assert PICK in ["A","B","AB","BA", "CF"]
    if PICK == "A":
        ee = [a,] 
    elif PICK == "B":
        ee = [b,]
    elif PICK == "AB":
        ee = [a,b,]
    elif PICK == "BA":
        ee = [b,a,]
    elif PICK == "CF":
        ee = []
    pass 




    context = "PICK=%s MODE=%d SEL=%s ~/j/ntds/ntds3.sh " % (PICK, MODE, SEL )
    print(context)

    for e in ee:

        elabel = "%s : %s " % ( e.symbol.upper(), e.f.base )
        label = context + " ## " + elabel 

        if MODE in [0,1]:
            print("not plotting as MODE %d in environ" % MODE )
        elif MODE == 2:
            pl = mpplt_plotter(label=label)
            fig, axs = pl
            assert len(axs) == 1
            ax = axs[0]
            ax.set_ylim( -250, 250 )
            ax.set_xlim( -300, 300 )

        elif MODE == 3:
            pl = pvplt_plotter(label)
            pvplt_viewpoint(pl)   # sensitive to EYE, LOOK, UP envvars
            pvplt_frame(pl, e.f.sframe, local=not GLOBAL )
        pass


        if "NO3" in os.environ:
            #ii = e.f.record[:,:,1,3].view(np.int32)
            ii = e.iir
            ii_sel = np.logical_and( ii > 0, ii <= 25600)      # (100000, 32) :  True at 3inch points  
            ii_selmax = np.max(ii_sel,axis=1)                  # (100000,)    :  True if any of the 32 points for the photon are True
            ii_nselmax = np.logical_not(ii_selmax)             # (100000,)    : 
            #wii = np.unique( np.where( ii_selmax )[0] )       # selecting records with points that touch 3inch 
            wii = np.unique( np.where( ii_nselmax )[0] )       # makes all 3-inch PMTs dissappear
        else:
            wii = slice(None)
        pass
       

        #pp = e.f.inphoton[:,0,:3]
        #pp = e.f.photon[:,0,:3]
        #pp = e.f.hit[:,0,:3]

        _pp = e.f.record[wii,:,0,:3]   # eg (100000, 32, 3)
        pp = _pp.reshape(-1,3)         # eg (3200000, 3)

        gpos = np.ones( [len(pp), 4 ] )
        gpos[:,:3] = pp
        lpos = np.dot( gpos, e.f.sframe.w2m ) # hmm unfilled global zeros are transformed somewhere

        # problem with selecting on gr is loss of the regular photon blocks
        #gr = np.sqrt(np.sum(gpos[:,:3]*gpos[:,:3], axis=1))    
        #_lpos = lpos.reshape(*e.f.record.shape[:2],4) 

        upos = gpos if GLOBAL else lpos

        _upos = upos.reshape(-1,32,4) 
        # HMM need to reshape upos.reshape(-1,32,4).shape before can apply photon level selections

        if len(SEL) == 0:
            spos = None
        elif SEL == "BOX": 
            sel = np.logical_and( np.logical_and( np.abs(upos[:,H]) < BOX, np.abs(upos[:,V]) < BOX ), np.abs(upos[:,O]) < BOX )
            spos = upos[sel]
        elif len(SEL) > 0:
            sel = e.q_startswith_or_(SEL) 
            spos = _upos[sel].reshape(-1,4) 
        else:
            spos = None
        pass

        if MODE == 2:
            ax.scatter( upos[:,H], upos[:,V], s=0.1 )
            if not spos is None:
                print("ax.scatter spos " )
                ax.scatter( spos[:,H], spos[:,V], s=0.1, c="r" )
            else:
                print("NOT:ax.scatter spos " )
            pass
        elif MODE == 3:
            pl.add_points(upos[:,:3])
            if not spos is None:
                ax.add_points( spos[:,H], spos[:,V], s=0.1, color="red" )
            pass
        else:
            pass
        pass

        if e.pid > -1: 
            onephotonplot(pl, e)
        pass 


        if MODE == 2:
            fig.show()
        elif MODE == 3:
            pl.show()
        pass
    pass   # over ee 
pass
   

