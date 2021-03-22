#!/usr/bin/env python
"""
PMTParamSvc.py 
=================


::

    epsilon:offline blyth$ jcv PMTParamSvc
    4 files to edit
    ./Detector/Geometry/Geometry/PMTParamSvc.h
    ./Detector/Geometry/src/PMTParamSvc.cc
    epsilon:offline blyth$

    In [48]: np.unique(o[:,1], return_counts=True)
    Out[48]:
    (array(['HZC', 'Hamamatsu', 'HighQENNVT', 'NNVT'], dtype=object),
     array([25600,  5000, 10580,  2033]))


    In [19]: np.unique(a[:,1], return_counts=True)
    Out[19]: (array([0, 1, 2, 3], dtype=int32), array([ 2033,  5000, 25600, 10580]))

    In [20]: 2033+5000+10580
    Out[20]: 17613




    ## boolean arrays

    NNVT =        a[:,1] == 0
    Hamamatsu =   a[:,1] == 1
    HZC =         a[:,1] == 2
    NNVT_HighQE = a[:,1] == 3


    In [73]: np.count_nonzero(NNVT)
    Out[73]: 2033

    In [74]: np.count_nonzero(Hamamatsu)
    Out[74]: 5000

    In [75]: np.count_nonzero(HZC)
    Out[75]: 25600

    In [76]: np.count_nonzero(NNVT_HighQE)
    Out[76]: 10580


    In [77]: np.where(NNVT)
    Out[77]: (array([   21,    24,    39, ..., 17594, 17595, 17609]),)

    In [78]: np.where(Hamamatsu)
    Out[78]: (array([    1,     4,     8, ..., 17603, 17607, 17610]),)

    In [79]: np.where(HZC)
    Out[79]: (array([17613, 17614, 17615, ..., 43210, 43211, 43212]),)

    In [80]: np.where(NNVT_HighQE)
    Out[80]: (array([    0,     2,     3, ..., 17608, 17611, 17612]),)


    In [81]: pmtid = a[:,0]

    In [82]: pmtid[NNVT]
    Out[82]: array([   21,    24,    39, ..., 17594, 17595, 17609], dtype=int32)

    In [83]: pmtid[Hamamatsu]
    Out[83]: array([    1,     4,     8, ..., 17603, 17607, 17610], dtype=int32)

    In [84]: pmtid[HZC]
    Out[84]: array([300000, 300001, 300002, ..., 325597, 325598, 325599], dtype=int32)

    In [85]: pmtid[NNVT_HighQE]
    Out[85]: array([    0,     2,     3, ..., 17608, 17611, 17612], dtype=int32)


"""
import os
import logging
log = logging.getLogger(__name__)
import numpy as np


try:
    import matplotlib.pyplot as plt
except ImportError:
    plt = None
pass
try:
    import pyvista as pv
except ImportError:
    pv = None
pass

def plot3d(*args, grid=False):
    pl = pv.Plotter()
    colors = ['#FFFFFF', '#FF0000', '#00FF00', '#0000FF']
    for i, pos in enumerate(args):
        pl.add_points(pos, color=colors[i % len(colors)], point_size=2.0 )
    pass
    if grid:
        pl.show_grid()
    pass
    cp = pl.show()
    return cp
pass


"""
jcv PMTParamSvc epsilon:jnu blyth$ jcv PMTParamSvc
2 files to edit
./Detector/Geometry/Geometry/PMTParamSvc.h
./Detector/Geometry/src/PMTParamSvc.cc
"""

kOFFSET_CD_LPMT=0
kOFFSET_WP_PMT=30000
kOFFSET_CD_SPMT=300000

kPMT_Unknown     = -1
kPMT_NNVT        = 0
kPMT_Hamamatsu   = 1
kPMT_HZC         = 2
kPMT_NNVT_HighQE = 3

## CAUTION : THESE ARE NOT THE SAME AS THOSE OF PMTSimParamSvc PMTSimParamSvc.py






class PMTParamSvc(object):
    """
    ::

        epsilon:jnu blyth$ head -5 $JUNOTOP/data/Simulation/ElecSim/pmtdata.txt
        0 HighQENNVT 0.2569
        1 Hamamatsu 0.3229
        2 HighQENNVT 0.2737
        3 HighQENNVT 0.3428
        4 Hamamatsu 0.358
        epsilon:jnu blyth$ tail -5 $JUNOTOP/data/Simulation/ElecSim/pmtdata.txt
        325595 HZC 0.255526
        325596 HZC 0.241442
        325597 HZC 0.24868
        325598 HZC 0.248741
        325599 HZC 0.258522
        epsilon:jnu blyth$ wc -l $JUNOTOP/data/Simulation/ElecSim/pmtdata.txt
           43213 /Users/blyth/junotop/data/Simulation/ElecSim/pmtdata.txt

    """
    path = "$JUNOTOP/data/Simulation/ElecSim/pmtdata.txt"
    cat = {
       'Unknown':-1,
       'NNVT':0,
       'Hamamatsu':1,
       'HZC':2,
       'HighQENNVT':3,
       'NNVT_HighQE':3,
    }
    rcat = dict(zip(cat.values(),cat.keys()))

    offset = {
      'CD_LPMT':0,
      'WP_PMT':30000,
      'CD_SPMT':300000
    }

    @classmethod
    def IsCD(cls, pmtid):
        """
        122 bool PMTParamSvc::isCD(int pmtid) {
        123   return (kOFFSET_CD_SPMT<=pmtid and pmtid<kOFFSET_WP_PMT)
        124       or (kOFFSET_CD_SPMT<=pmtid);
        125 }
        """      ## looks wrong : no pmtid can fulful the bracket clause
        return (cls.offset['CD_SPMT']<=pmtid and pmtid<cls.offset['WP_PMT']) or cls.offset['CD_SPMT']<=pmtid

    @classmethod
    def IsWP(cls, pmtid):      ## looks right
        return cls.offset['WP_PMT']<=pmtid and pmtid<cls.offset['CD_SPMT']

    @classmethod
    def Is20inch(cls, pmtid):  ## looks wrong : should be < CD_SPMT  :  WP_PMT are 20inch too ?
        return pmtid<cls.offset['WP_PMT']

    @classmethod
    def Is3inch(cls, pmtid):   ## looks right
        return cls.offset['CD_SPMT'] <= pmtid

    @classmethod
    def IsHZC(cls, pmtid):
        return cls.Is3inch(pmtid)

    mask = {
            'CD':0x1 << 0,
            'WP':0x1 << 1,
        '20inch':0x1 << 2,
         '3inch':0x1 << 3,
           'HZC':0x1 << 4,
          'NNVT':0x1 << 5,
     'Hamamatsu':0x1 << 6,
        'HighQE':0x1 << 7,
          }

    def pmtbitfield(self, pmtid):
        bf = 0
        if self.IsCD(pmtid):
            bf |= self.mask['CD']
        pass
        if self.IsWP(pmtid):
            bf |= self.mask['WP']
        pass
        if self.Is20inch(pmtid):
            bf |= self.mask['20inch']
        pass
        if self.Is3inch(pmtid):
            bf |= self.mask['3inch']
        pass
        if self.IsHZC(pmtid):
            bf |= self.mask['HZC']
        pass
        if self.isNNVT(pmtid):
            bf |= self.mask['NNVT']
        pass
        if self.isHamamatsu(pmtid):
            bf |= self.mask['Hamamatsu']
        pass
        if self.isHighQE(pmtid):
            bf |= self.mask['HighQE']
        pass
        return bf

    def pmtdesc(self, pmtbf):
        desc = []
        for k in self.mask.keys():
            if pmtbf & self.mask[k] != 0:
                desc.append(k)
            pass
        pass
        return " ".join(desc)

    @classmethod
    def parse(cls, cat, path):
        """

        0 HighQENNVT 0.2569
        1 Hamamatsu 0.3229
        2 HighQENNVT 0.2737
        3 HighQENNVT 0.3428
        4 Hamamatsu 0.358
        ...
        325595 HZC 0.255526
        325596 HZC 0.241442
        325597 HZC 0.24868
        325598 HZC 0.248741
        325599 HZC 0.258522

        """
        path = os.path.expandvars(path)
        o = np.loadtxt(path, dtype=np.object)
        a = np.zeros( (len(o),4), dtype=np.int32 )
        a.fill(cat["Unknown"])

        a[:,0] = list(map(int, o[:,0]))  # pmtID column
        for k,v in cat.items():
            a[np.where(o[:,1] == k),1] = v   # cat column integers from the names
        pass
        a.view(np.float32)[:,2] = list(map(float, o[:,2]))  # qe column float
        log.info("parsing %s yielded array %s " % (path,repr(a.shape)) )

        cats = a[:,1]
        cls.summary(cats)
        return a

    @classmethod
    def summary(cls, cats):
        ucats, ucounts = np.unique(cats, return_counts=True)
        cc = dict(zip(ucats,ucounts))
        ucsum = ucounts.sum()
        fmt0 = " %2d : %20s : %5d "
        fmt1 = " %2s : %20s : %5d "
        for k,v in cc.items():
            print(fmt0 % (k,cls.rcat[k], v ))
        pass
        print(fmt1 % ("","SUM", ucsum ))
        assert len(cats) == ucsum


    def __init__(self):
        a = self.parse(self.cat, self.path)
        pc = {}
        for i in range(len(a)):
            pmtid, typ = a[i,:2]
            pc[pmtid] = typ
        pass
        self.pmt_categories = pc  # dict from pmtid->type
        self.categories = a[:,1]

        self.sli = slice(0, 10)

        for i in range(len(a)):
            a[i,3] = self.pmtbitfield(a[i,0])
        pass
        self.a = a

    def desc(self, i):
        a = self.a
        return " i:%6d pmtid:%8d typ:%1d qe:%10.4f bf:%-4d bfx:%-4x  %s " % (i, a[i,0], a[i,1], a[i,2].view(np.float32), a[i,3],a[i,3], self.pmtdesc(a[i,3]) )

    def __repr__(self):
        a = self.a
        return "\n".join(map(lambda i:self.desc(i), range(len(a))[self.sli]))

    def save(self, path="/tmp/pmtdata.txt"):
        open(path, "w").write(repr(self[slice(None)]))

    def __getitem__(self, v):
        self.sli = v
        return self

    def isNNVT(self, pmtid):
        return self.Is20inch(pmtid) and (self.pmt_categories[pmtid] == self.cat['NNVT'] or self.pmt_categories[pmtid] == self.cat['NNVT_HighQE'])

    def isHamamatsu(self, pmtid):
        return self.Is20inch(pmtid) and self.pmt_categories[pmtid] == self.cat['Hamamatsu']

    def isHighQE(self, pmtid):
        return not self.isHamamatsu(pmtid) and self.pmt_categories[pmtid] == self.cat['NNVT_HighQE']

    def getPMTCategory(self, pmtid):
        return self.categories[pmtid]



if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)

    path = os.path.expandvars("$JUNOTOP/data/Simulation/ElecSim/pmtdata.txt")
    o = np.loadtxt(path, dtype=np.object)


if 0:
    pps = PMTParamSvc()
    a = pps.a

    assert np.all( a[:17613,0] == np.arange(17613, dtype=np.int32)  ) 
    assert np.all( a[17613:,0] >= 300000 )   

    NNVT = a[:,1] == 0
    Hamamatsu = a[:,1] == 1
    HZC = a[:,1] == 2
    NNVT_HighQE = a[:,1] == 3


