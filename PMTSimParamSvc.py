#!/usr/bin/env python
"""
PMTSimParamSvc.py
===================

::

    epsilon:junotop blyth$ jcv PMTSimParamSvc
    2 files to edit
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h

    epsilon:jnu blyth$ jcv IPMTSimParamSvc
    ./Simulation/SimSvc/IPMTSimParamSvc/IPMTSimParamSvc/IPMTSimParamSvc.h

See Also

* env-;rootnumpy-

::

    In [1]: run PMTSimParamSvc.py
    In [2]: psps.a
    Out[2]:
    array([(    0, b'PA1803-2326', 0, 1, 10475100.   , 0.29 , 32.81 , 57.1  ,  9.83 , 4.983, 1800.   , 7.98 , 4.25 , 0.074, 6.9  , 17.5  ,  7.49 , 72.562, 0.01 , 0.029, -930.298, -111.872,  19365.),
           (    1, b'EA1602', 1, 0, 10399500.   , 0.27 , 30.16 , 42.7  ,  5.8  , 0.885, 1805.   , 6.69 , 3.69 , 0.071, 7.09 , 10.07 , 12.01 , 38.723, 0.   , 0.096, -492.566, -797.087,  19365.),
           (    2, b'PA1803-2320', 0, 1, 10197300.   , 0.36 , 31.84 , 54.3  ,  9.44 , 5.214, 1859.   , 8.15 , 4.03 , 0.077, 4.37 , 12.56 ,  7.43 , 66.703, 0.007, 0.029,  316.078, -882.079,  19365.), ...,
           (17609, b'PA3454F', 0, 1, 10385355.854, 0.404, 29.328, 21.165, 10.536, 5.554, 1769.958, 7.324, 4.482, 0.069, 4.939, 16.043,  7.323, 64.944, 0.006, 0.028,  342.325,  872.229, -19365.),
           (17610, b'EA4F', 1, 0, 10070148.077, 0.264, 29.984, 11.892,  5.702, 0.829, 1905.321, 6.347, 3.287, 0.075, 5.825,  9.954, 11.592, 41.016, 0.   , 0.11 , -468.5  ,  811.466, -19365.),
           (17611, b'PA3455F', 0, 1, 10057712.094, 0.344, 31.008, 44.13 ,  9.022, 4.625, 1812.82 , 6.931, 2.556, 0.07 , 4.237, 18.276,  7.86 , 69.845, 0.002, 0.031, -926.534,  139.653, -19365.)],
          dtype=[('pmtID', '<i4'), ('SN', 'S19'), ('MCP_Hama', '<i4'), ('HiQE_MCP', '<i4'), ('Gain', '<f8'), ('Resolution', '<f8'), ('PDE', '<f8'), ('DCR', '<f8'), ('TTS', '<f8'), ('TTS_SS', '<f8'), ('HV', '<f8'), ('Amplitude', '<f8'), ('PvsV', '<f8'), ('SvsN', '<f8'), ('RiseTime', '<f8'), ('FallTime', '<f8'), ('FWHM', '<f8'), ('timeOffset', '<f8'), ('prePulseProb', '<f8'), ('afterPulseProb', '<f8'), ('pmtPosX', '<f8'), ('pmtPosY', '<f8'), ('pmtPosZ', '<f8')])

    In [3]: psps.shape
    Out[3]: (17612,)

    In [24]: np.unique(MCP_Hama, return_counts=True)
    Out[24]: (array([0, 1], dtype=int32), array([12612,  5000]))

    In [25]: np.unique(HiQE_MCP, return_counts=True)
    Out[25]: (array([0, 1], dtype=int32), array([ 7032, 10580]))

    In [40]: np.unique(simcat, return_counts=True)
    Out[40]: (array([0, 1, 2], dtype=int32), array([ 5000, 10580,  2032]))

    In [41]: 10580+2032
    Out[41]: 12612

    In [42]: 10580+2032+5000
    Out[42]: 17612

    In [5]: np.unique(cat, return_counts=True)                                                                                                                                                               
    Out[5]: (array([0, 1, 2], dtype=int32), array([ 5000, 10580,  2032]))
     

"""
import os, logging 
import numpy as np
from root_numpy import root2array
log = logging.getLogger(__name__)

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

def plot3d_(pos, grid=False):
    pl = pv.Plotter()
    pl.add_points(pos, color='#FFFFFF', point_size=2.0 )
    if grid:
        pl.show_grid()
    pass
    cp = pl.show()
    return cp
pass

def plot3d(*args, grid=False, point_size=5.):
    pl = pv.Plotter()
    #colors = ['#FFFFFF', '#FF0000', '#00FF00', '#0000FF']
    colors = ['#FFFFFF',]
    for i, pos in enumerate(args):
        pl.add_points(pos, color=colors[i % len(colors)], point_size=point_size )
    pass
    if grid:
        pl.show_grid()
    pass
    cp = pl.show()
    return cp
pass


"""
epsilon:jnu blyth$ jcv IPMTSimParamSvc
./Simulation/SimSvc/IPMTSimParamSvc/IPMTSimParamSvc/IPMTSimParamSvc.h
"""

kOFFSET_CD_LPMTID = 0
kOFFSET_WP_PMTID = 30000
kOFFSET_CD_SPMTID = 300000

kPMTType_Unknown = -1
kPMTType_Hamamatsu = 0
kPMTType_HiQENNVT = 1
kPMTType_NormalNNVT = 2
kPMTType_HZC = 3

PMTType={}
PMTType[kPMTType_Unknown] = "kPMTType_Unknown"
PMTType[kPMTType_Hamamatsu] = "kPMTType_Hamamatsu"
PMTType[kPMTType_HiQENNVT] = "kPMTType_HiQENNVT"
PMTType[kPMTType_NormalNNVT] = "kPMTType_NormalNNVT"
PMTType[kPMTType_HZC] = "kPMTType_HZC"


class PMTSimParamSvc(object):
    """
       if(m_isHamamatsu) {
            m_pmt_categories[m_pmtId] = kPMTType_Hamamatsu;
        } else if ( !m_isHamamatsu and m_isHiQEMCP ) {
            m_pmt_categories[m_pmtId] = kPMTType_HiQENNVT;
        } else if ( !m_isHamamatsu and !m_isHiQEMCP ) {
            m_pmt_categories[m_pmtId] = kPMTType_NormalNNVT;
        } else {
            LogError << "Unknown PMT category name !" << std::endl;
        }

    """
    def __init__(self): 
        path = os.path.expandvars("$JUNOTOP/data/Simulation/ElecSim/PmtData_Lpmt.root")
        log.info("root2array %s " % path )
        a = root2array(path)

        num_pmt = len(a)
        pmtID = a["pmtID"]
        assert np.all(pmtID == np.arange(len(pmtID), dtype=np.int32))

        MCP_Hama = a["MCP_Hama"]
        HiQE_MCP = a["HiQE_MCP"]
        SN = a["SN"]

        isHamamatsu = MCP_Hama
        isHiQEMCP = HiQE_MCP

        pos = np.empty( (len(a),3) )
        pos[:,0] = a["pmtPosX"]
        pos[:,1] = a["pmtPosY"]
        pos[:,2] = a["pmtPosZ"]

        pmt_categories_ = np.zeros(num_pmt, dtype=np.int32) - 10
        pmt_categories_[isHamamatsu == 1] = kPMTType_Hamamatsu
        pmt_categories_[np.logical_and(isHamamatsu == 0, isHiQEMCP == 1)] = kPMTType_HiQENNVT
        pmt_categories_[np.logical_and(isHamamatsu == 0, isHiQEMCP == 0)] = kPMTType_NormalNNVT

        top_category = np.zeros( 1, dtype=np.int32 )
        top_category[0] = kPMTType_Unknown 
        pmt_categories = np.concatenate( (pmt_categories_, top_category) )

        assert np.all( pmt_categories > -10 )

        self.num_pmt = num_pmt
        self.path = path 
        self.a = a 
        self.pmt_categories_ = pmt_categories_
        self.pmt_categories = pmt_categories
        self.pos = pos

    def getPMTCategory(self, pmtid ):
        """
        int PMTSimParamSvc::getPMTCategory(int pmtID) const
        {
            return isWP(pmtID) ? kPMTType_Unknown : m_pmt_categories.at(pmtID);
        }

        # this way is restricted to pmtid less than num_pmt 
        return np.where( self.isWP(pmtid), kPMTType_Unknown, self.pmt_categories[pmtid] )    


        using take with clip mode returns the top category kPMTType_Unknown for pmtid of num_pmt and beyond
        that might be a bit different to the C++ which will raise a map.at error for SPMT pmtid
        """
        return np.take(self.pmt_categories, pmtid, mode="clip")    


    def plot(self):
        cat = self.pmt_categories_
        pos = self.pos
        #args = (pos[cat == 0], pos[cat == 1],pos[cat == 2])
        #args = (pos[cat == 0], ) # Hama
        args = (pos[cat == 1], ) # 
        plot3d(*args)

    def isCD(self, pmtid): 
        """
        0->30,000 or > 300,000

        0       :  kOFFSET_CD_LPMTID       
        30,000  :  kOFFSET_WP_PMTID 
        300,000 :  kOFFSET_CD_SPMTID       


        bool PMTSimParamSvc::isCD(int pmtid) const {
            return (kOFFSET_CD_LPMTID<=pmtid and pmtid<kOFFSET_WP_PMTID)
                or (kOFFSET_CD_SPMTID<=pmtid);
        }
        """
        return np.logical_or(np.logical_and(kOFFSET_CD_LPMTID<=pmtid, pmtid<kOFFSET_WP_PMTID), kOFFSET_CD_SPMTID<=pmtid)

    def isWP(self, pmtid):
        """
        more than 30,000 and less than 300,000

        bool PMTSimParamSvc::isWP(int pmtid) const {
            return (kOFFSET_WP_PMTID<=pmtid and kOFFSET_CD_SPMTID>pmtid) ;
        }
        """
        return np.logical_and( kOFFSET_WP_PMTID<=pmtid, kOFFSET_CD_SPMTID>pmtid )  

    def isCD20inch(self, pmtid):
        """
        up to and including 30,000

        bool PMTSimParamSvc::isCD20inch(int pmtid) const {
            return (kOFFSET_WP_PMTID>=pmtid);
        }
        """
        return (kOFFSET_WP_PMTID>=pmtid)

    def is3inch(self, pmtid):
        """
        300,000 and above 

        bool PMTSimParamSvc::is3inch(int pmtid) const {
            return (kOFFSET_CD_SPMTID<=pmtid);
        }
        """
        return (kOFFSET_CD_SPMTID<=pmtid)

    def isHiQENNVT(self, pmtid):
        """
        bool PMTSimParamSvc::isHiQENNVT(int pmtid) const {
            int pmt_type_no = getPMTCategory(pmtid);
            if ( pmt_type_no == 1 )
                return true;
            else
                return false;
        }
        """
        return 1 == self.getPMTCategory(pmtid)
        
    def isNormalNNVT(self, pmtid):
        """
        bool PMTSimParamSvc::isNormalNNVT(int pmtid) const {
            int pmt_type_no = getPMTCategory(pmtid);
            if ( pmt_type_no == 2 )
                return true;
            else
                return false;
        }
        """
        return 2 == self.getPMTCategory(pmtid)

    def isHamamatsu(self, pmtid):
        """
        bool PMTSimParamSvc::isHamamatsu(int pmtid) const {
            int pmt_type_no = getPMTCategory(pmtid);
            if ( pmt_type_no == 0 )
                return true;
            else
                return false;
        }
        """
        return 0 == self.getPMTCategory(pmtid)


if __name__ == '__main__':
    psps = PMTSimParamSvc()
    pmtid = np.arange(psps.num_pmt)  
    cat = psps.getPMTCategory(pmtid) 
    assert np.all( cat == psps.pmt_categories[:-1] )
    ucat, ucat_counts = np.unique(cat, return_counts=True) 

    pmtid = np.arange(kOFFSET_CD_SPMTID+10)
    cat = psps.getPMTCategory(pmtid) 
    #psps.plot()



