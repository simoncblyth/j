#!/usr/bin/env python
"""
PMTEfficiencyCheck.py
=======================

The arrays that this script analyses are created by:

* $JUNOTOP/offline/Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc 

Grab the arrays using scp/rsync::

    ./PMTEfficiencyCheck.sh grab 


"""

import os
import numpy as np
from glob import glob 
from collections import OrderedDict as odict 

try:
    import matplotlib.pyplot as plt 
except ImportError:
    plt = None
pass
#plt = None # disable plotting 

try:
    import pyvista as pv
except ImportError:
    pv = None
pass

def plot3d(pos, grid=False):
    pl = pv.Plotter()
    pl.add_points(pos, color='#FFFFFF', point_size=2.0 )   
    if grid:
        pl.show_grid()
    pass
    cp = pl.show()
    return cp

def print_shapes(qty):
    for q in qty.split():
         print(" %20s : %15s " % (q,str(eval(q+".shape"))))
    pass



class Mismatch(object):
    """
    unsigned mismatch = 
        ( unsigned(!qe_match)       << 0 ) | 
        ( unsigned(!ce_match)       << 1 ) | 
        ( unsigned(!de_match)       << 2 ) | 
        ( unsigned(parcat_mismatch) << 3 ) | 
        ( unsigned(simcat_mismatch) << 4 ) 
        ;   
    """
    qe_ = ( 0x1 << 0 )
    ce_ = ( 0x1 << 1 )
    de_ = ( 0x1 << 2 )
    pc_ = ( 0x1 << 3 )
    sc_ = ( 0x1 << 4 )

    def __init__(self, a):
        self.a = a 

        u, c = np.unique(a, return_counts=True)

        n = []
        for field in self.fields:
            q = getattr(self, field)
            n.append(np.count_nonzero(q))
        pass 

        self.tot = len(a)  
        self.u = u 
        self.c = c
        self.n = n  

    qe = property(lambda self:self.a & self.qe_) 
    ce = property(lambda self:self.a & self.ce_) 
    de = property(lambda self:self.a & self.de_) 
    pc = property(lambda self:self.a & self.pc_) 
    sc = property(lambda self:self.a & self.sc_) 

    fields = ["qe","ce","de","pc","sc"]

    def unique_smry(self):
       fmt = "i {0:2d}   mismatch (dec) {1:5d} (hex) {1:5x} (bin) {1:10b}  mismatch_count {2:6d} "
       return "\n".join([fmt.format(i, self.u[i], self.c[i]) for i in range(len(self.u))])

    def nonzero_smry(self):
       fmt = " {0:2s} {1:6d} {2:8.3f}" 
       return "\n".join([fmt.format(self.fields[i], self.n[i], float(self.n[i])/float(self.tot)) for i in range(len(self.n))])

    def __str__(self):
       return "\n".join([
                         "Mismatch", 
                         "total:%d" % self.tot,
                         "bitfield unique_smry",self.unique_smry(), 
                         "bitwise nonzero_smry",self.nonzero_smry()
                        ]) 

    __repr__ = __str__



if __name__ == '__main__':

    #flavor = "SCB_KLUDGE_FIX"
    flavor = "ASIS"
    base = os.path.expandvars("/tmp/$USER/opticks/PMTEfficiencyCheck/%s" % flavor)
    name = os.path.basename(base)
    paths = sorted(glob("%s/*.npy" % base))
    #paths = paths[0:1]

    arrs = []
    for i,path in enumerate(paths):
        arr = np.load(path)
        print( " %15s : %s " % (str(arr.shape), path ))
        arrs.append(arr)  
    pass
    a = np.concatenate(tuple(arrs))  
    print( " %15s : %s " % (str(a.shape), "a.shape concatenated" ))
   

    pmtId  = a.view(np.uint32)[:,0,0]  
    parCat = a.view(np.uint32)[:,0,1]  
    ceCat  = a.view(np.uint32)[:,0,2]  
    volIdx = a.view(np.uint32)[:,0,3] ; assert volIdx.max() <= 2 
    qeff = a[:,0,2]
    qeff2 = a[:,0,3]

    ceff = a[:,1,0]
    ceff2 = a[:,1,1]
    deff = a[:,1,2]
    deff2 = a[:,1,3]

    local_pos = a[:,2,:3]
    local_theta = a[:,2,3]

    global_pos = a[:,3,:3]
    simCat = a.view(np.int32)[:,3,6]  
    mismatch = a.view(np.uint32)[:,3,7]
    #assert np.all( mismatch == 0 ) 

    mima = Mismatch(mismatch)
    print(mima)

    print_shapes("pmtId parCat simCat ceCat volIdx qeff qeff2 ceff ceff2 deff deff2 local_pos local_theta global_pos mismatch")

    global_radius = np.sqrt(np.sum(global_pos*global_pos, axis=1))
    local_radius = np.sqrt(np.sum(local_pos*local_pos, axis=1))


    ############################ TWO FLAVORS OF ENUMS ##############

    kPMT_Unknown = -1
    kPMT_NNVT = 0
    kPMT_Hamamatsu = 1
    kPMT_HZC = 2
    kPMT_NNVT_HighQE = 3

    parCatName={}
    parCatName[kPMT_Unknown]="kPMT_Unknown"
    parCatName[kPMT_NNVT]="kPMT_NNVT"
    parCatName[kPMT_Hamamatsu]="kPMT_Hamamatsu"
    parCatName[kPMT_HZC]="kPMT_HZC"
    parCatName[kPMT_NNVT_HighQE]="kPMT_NNVT_HighQE"

    print("\nparCatName")
    for cat in sorted(parCatName.keys()):
        print(" parCatName[%2d] : %s " % (cat, parCatName[cat]))
    pass

    kPMTType_Unknown = -1
    kPMTType_Hamamatsu = 0 
    kPMTType_HiQENNVT = 1
    kPMTType_NormalNNVT = 2
    kPMTType_HZC = 3 

    simCatName={}
    simCatName[kPMTType_Unknown]="kPMTType_Unknown"
    simCatName[kPMTType_NormalNNVT]="kPMTType_NormalNNVT"
    simCatName[kPMTType_Hamamatsu]="kPMTType_Hamamatsu"
    simCatName[kPMTType_HZC]="kPMTType_HZC"
    simCatName[kPMTType_HiQENNVT]="kPMTType_HiQENNVT"

    print("\nsimCatName")
    for cat in sorted(simCatName.keys()):
        print(" simCatName[%2d] : %s " % (cat, simCatName[cat]))
    pass

    #CATEGORY_TYPE = 'P'
    CATEGORY_TYPE = 'S'
    pmtCatName = simCatName if CATEGORY_TYPE == 'S' else parCatName
    pmtCat = simCat if CATEGORY_TYPE == 'S' else parCat


    print("\npmtCatName CATEGORY_TYPE : %s " % CATEGORY_TYPE )
    for cat in sorted(pmtCatName.keys()):
        print(" pmtCatName[%2d] : %s " % (cat, pmtCatName[cat]))
    pass


    #########################################################################

    volName = {}
    volName[0] = "HamamatsuR12860_PMT_20inch_body_phys"
    volName[1] = "NNVTMCPPMT_PMT_20inch_body_phys" 
    volName[2] = "PMT_3inch_body_phys"
    
    print("\nvolIdx counts : u_{sim,par}Cat_vol:list(np.unique({sim,par}Cat[volIdx==i]))  {par,sim}Cat for each volume")
    fmt0 = "%2s : %12s : %40s : %7s : %30s : %30s" 
    qty0 = "i u_volIdx[i] volName[u_volIdx[i]] u_volIdx_counts[i] u_parCat_vol u_simCat_vol"
    qty0 = qty0.split()
    u_volIdx, u_volIdx_counts = np.unique(volIdx, return_counts=True)
    print(fmt0 % tuple(qty0))
    print()
    for i in range(3):
        u_parCat_vol = list(np.unique(parCat[volIdx==i])) 
        u_simCat_vol = list(np.unique(simCat[volIdx==i])) 
        print( fmt0 % tuple(map(str,map(eval,qty0)))) 
    pass


if 1 and plt:
    def theta_efficiency_plot_cats( ax, th, ef, pmtCat, cats, catNames):
        for cat in cats:
            sel = pmtCat == cat
            ax.plot( th[sel], ef[sel], "o", markersize=2, label="%d:%s" % (cat, catNames[cat]))
            ax.legend()
        pass
    pass
    fig, axs = plt.subplots(2, sharex=True)
    fig.suptitle("~/j/PMTEfficiencyCheck.py : %s : theta_efficiency_plot_cats" % name) 
    theta_efficiency_plot_cats( axs[0], local_theta, ceff  , pmtCat, [0,1,2,3], pmtCatName ) 
    axs[0].set_ylabel("ceff")
    axs[0].set_xlabel("local_theta")
    axs[0].set_title("title")
    theta_efficiency_plot_cats( axs[1], local_theta, ceff2 , pmtCat, [0,1,2,3], pmtCatName )
    axs[1].set_ylabel("ceff2")
    axs[1].set_xlabel("local_theta")
    fig.show()                   


if 0 and plt:
    def theta_efficiency_plot( ax, th, ef, sel):
        ax.plot( th[sel], ef[sel], "o", markersize=0.5 )
    pass

    fig, axs = plt.subplots(2)
    fig.suptitle("theta_efficiency_plot ceff and ceff2") 
    theta_efficiency_plot( axs[0], local_theta, ceff , pmtCat > -1 )
    theta_efficiency_plot( axs[1], local_theta, ceff2 , pmtCat > -1 )
    fig.show()                   

if 0 and plt:
    def theta_efficiency_scatter( ax, th, ef, cat):
        ax.scatter( th, ef, s=1, c=cat, label=cat)
    pass

    fig, axs = plt.subplots(1)
    ax = axs
    theta_efficiency_scatter( ax, local_theta, ceff2, pmtCat )
    ax.legend()
    fig.show()                   


if 1:
    print("\n pmtId ranges for each pmtCat,   pmtId_cat = pmtId[pmtCat == cat]  ")
    print("\n unique ceCat for each pmtCat    u_ceCat_cat = list(np.unique(ceCat[pmtCat==cat])) ")

    f_ = lambda _:"%12.3f" % _

    fmt1 = "%3s : %15s : %20s : %15s %15s : %12s : %20s : %20s"
    qty1 = "cat len(pmtId_cat) pmtCatName[cat] pmtId_cat.min() pmtId_cat.max() u_ceCat_cat f_(ceff_cat.min()) f_(ceff_cat.max())"
    print(fmt1 % tuple(qty1.split()))
    print()
    for cat in range(4):
        pmtId_cat = pmtId[pmtCat == cat]
        u_ceCat_cat = list(np.unique(ceCat[pmtCat==cat]))  
        ceff_cat = ceff[pmtCat == cat]  
        print( fmt1 % tuple(map(str,map(eval,qty1.split())))) 
    pass


    epsilon = 1e-9

    print("\n ceff and ceff2 comparisons for different pmtCat : epsilon %s " % epsilon)
    fmt2 = "%3s : %15s : %20s : %50s"
    qty2 = "cat len(ceff[sel]) pmtCatName[cat] num_ce_mismatch"  
    print(fmt2 % tuple(qty2.split()))
    print()
    for cat in range(4):
        sel = pmtCat == cat
        ce_mismatch = np.abs(ceff[sel]-ceff2[sel]) > epsilon
        num_ce_mismatch = np.count_nonzero(ce_mismatch)
        print( fmt2 % tuple(map(str,map(eval,qty2.split())))) 
    pass

    print("\n ceff and ceff2 comparisons for all unique ce_cat : epsilon %s " % epsilon)
    fmt3 = "%3s : %15s : %50s : %15s : %15s %15s"
    qty3 = "ce_cat len(ceff[sel]) num_ce_mismatch u_pmtCat_ce_cat pmtId_min pmtId_max"  
    u_ceCat = np.unique(ceCat)
    print(fmt3 % tuple(qty3.split()))
    print()
    for ce_cat in u_ceCat:
        sel = ceCat == ce_cat
        ce_mismatch = np.abs(ceff[sel]-ceff2[sel]) > epsilon
        num_ce_mismatch = np.count_nonzero(ce_mismatch)
        pmtId_min = pmtId[sel].min()   
        pmtId_max = pmtId[sel].max()   
        u_pmtCat_ce_cat = list(np.unique(pmtCat[sel]))  
        print( fmt3 % tuple(map(str,map(eval,qty3.split())))) 
    pass

    epsilon = 0.0
    print("\n deff and deff2 comparisons for different pmtCat : epsilon %s " % epsilon)
    fmt4 = "%3s : %15s : %20s : %50s"
    qty4 = "cat len(deff[sel]) pmtCatName[cat] num_de_mismatch"  
    print(fmt4 % tuple(qty4.split()))
    print()
    for cat in range(4):
        sel = pmtCat == cat
        de_mismatch = np.abs(deff[sel]-deff2[sel]) > epsilon
        num_de_mismatch = np.count_nonzero(de_mismatch)
        print( fmt2 % tuple(map(str,map(eval,qty2.split())))) 
    pass

    #################################################################################################

    #ssel = "pmtCat == kPMT_HZC"
    #ssel = "pmtCat == kPMT_NNVT" 
    #ssel = "pmtCat > -2"
    ssel = "ceCat == 5"
    
    print() 
    print("CAUTION applying selection : %s : to shorthand qtys: lp,lt,gp,lp,qe,qe2,ce,ce2,de,de2 " % ssel)
    sel = eval(ssel)

    lp = local_pos[sel]  
    lt = local_theta[sel]
    gp = global_pos[sel]  
    lp = local_pos[sel]  

    qe = qeff[sel]
    qe2 = qeff2[sel]
    ce = ceff[sel]
    ce2 = ceff2[sel]
    de = deff[sel]
    de2 = deff2[sel]

    print_shapes("lp lt gp lp qe qe2 ce ce2 de de2")
        
    #plot3d(lp)  # easily distinguish small from large with this   
    #plot3d(gp)

if 0 and plt:
    ncat = 4
    fig, axs = plt.subplots(ncat, sharex=True)
    title = "local_theta"
    #title = "global_radius"
    #title = "local_radius"
    fig.suptitle(title)
    for i in range(ncat):
        ax = axs[i]
        if title == "local_theta":
            ax.hist(local_theta[pmtCat == i], bins=100)
        elif title == "global_radius":
            ax.hist(global_radius[pmtCat == i], bins=100)
        elif title == "local_radius":
            ax.hist(local_radius[pmtCat == i], bins=100)
        else:
            pass
        pass
        ax.text( 0.99, 0.8, pmtCatName[i], ha='right', transform=ax.transAxes )
    pass
    fig.show()
 

