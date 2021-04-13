#!/usr/bin/env python
"""
PMTEffCheck.py
===============

See also PMTEfficiencyCheck for more 
wide open access to the same data arrays
that is complementary to the more encapsulated approach here
which is suitable for limited usage in integration 
with other plots rather than wide-open debugging/investigation. 
"""

import os, numpy as np

class PMTEfficiencyCheck_(object):
    base = os.path.expandvars("/tmp/$USER/opticks/PMTEfficiencyCheck/ASIS")
    def __init__(self):
        path = os.path.join(self.base, "0.npy")
        a = np.load(path)
        self.a = a 

        idx = np.where(self.volIdx == 3)[0][0]  
        self.idx = idx


    pmtId = property(lambda self:self.a.view(np.uint32)[:,0,0])
    parCat = property(lambda self:self.a.view(np.uint32)[:,0,1])
    ceCat = property(lambda self:self.a.view(np.uint32)[:,0,2])  
    volIdx = property(lambda self:self.a.view(np.uint32)[:,0,3])
    qeff = property(lambda self:self.a[:,0,2])
    qeff2 = property(lambda self:self.a[:,0,3])

    ceff = property(lambda self:self.a[:,1,0])
    ceff2 = property(lambda self:self.a[:,1,1])
    deff = property(lambda self:self.a[:,1,2])
    deff2 = property(lambda self:self.a[:,1,3])

    local_pos = property(lambda self:self.a[:,2,:3])
    local_theta = property(lambda self:self.a[:,2,3])

    global_pos = property(lambda self:self.a[:,3,:3])
    simCat = property(lambda self:self.a.view(np.int32)[:,3,6])
    mismatch = property(lambda self:self.a.view(np.uint32)[:,3,7])

    rcyl = property(lambda self:np.sqrt( np.sum( self.local_pos[:,:2]*self.local_pos[:,:2], axis=1 )))
    zcyl = property(lambda self:self.local_pos[:,2])

    def rz(self):
        rcyl = self.rcyl
        zcyl = self.zcyl
        idx = self.idx
        return np.array([rcyl[idx], zcyl[idx]])

    def rz_plot(self, axs, i, sli):
        if hasattr(axs, 'flat'):
            for ax in axs.flat: 
                self._rz_plot(ax, i, sli)
            pass
        else:
            ax = axs
            self._rz_plot(ax, i, sli)
        pass


    def _rz_plot(self, ax, i, sli):
        """
        i:0 HamamatsuR12860_PMT_20inch_body_phys
        i:1 NNVTMCPPMT_PMT_20inch_body_phys
        i:2 PMT_3inch_body_phys
        i:3 unexpected-other-volume 
        """
        rcyl = self.rcyl
        zcyl = self.zcyl
        volIdx = self.volIdx
        idx = self.idx

        c = "rgb"[i] 
        v_rcyl = rcyl[volIdx == i]
        v_zcyl = zcyl[volIdx == i]


        if type(sli) in [slice, type(None)]: 
            pass
        elif type(sli) is int:
            sli = slice(0,sli)
        else:
            sli = "SKIP"  
        pass

        if not sli == "SKIP":
            ax.scatter(v_rcyl[sli], v_zcyl[sli], s=1, c=c ) 
        pass
        ax.scatter(rcyl[idx], zcyl[idx], c="r" )

    

if __name__ == '__main__':

    pec = PMTEfficiencyCheck_()
    print(pec.idx)


   






