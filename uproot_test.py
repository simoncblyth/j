#!/usr/bin/env python
"""

* https://uproot.readthedocs.io/en/latest/index.html

* http://scikit-hep.org/root_numpy/index.html

::

    In [25]: pmtPosX
    Out[25]: array([-930.298, -492.566,  316.078, ...,  342.325, -468.5  , -926.534])

    In [26]: MCP_Hama
    Out[26]: array([0, 1, 0, ..., 0, 1, 0], dtype=int32)

    In [27]: np.unique(MCP_Hama )
    Out[27]: array([0, 1], dtype=int32)

    In [28]: np.unique(MCP_Hama, return_counts=True)
    Out[28]: (array([0, 1], dtype=int32), array([12612,  5000]))

    In [29]: np.unique(HiQE_MCP, return_counts=True)
    Out[29]: (array([0, 1], dtype=int32), array([ 7032, 10580]))

    In [30]: HiQE_MCP[MCP_Hama == 0]
    Out[30]: array([1, 1, 1, ..., 1, 1, 1], dtype=int32)

    In [31]: np.unique(HiQE_MCP[MCP_Hama == 0], return_counts=True )
    Out[31]: (array([0, 1], dtype=int32), array([ 2032, 10580]))

    In [32]: np.unique(HiQE_MCP[MCP_Hama == 1], return_counts=True )
    Out[32]: (array([0], dtype=int32), array([5000]))

"""

import os, numpy as np
import uproot

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
pass



if __name__ == '__main__':
    path = os.path.expandvars("$JUNOTOP/data/Simulation/ElecSim/PmtData_Lpmt.root") 
    name = "PmtData_Lpmt"

    if uproot.version.version_info[0] == '3':
        tt = uproot.open(path)[name]
        aa = tt.arrays()
        for k, a in aa.items():
            print("%20s : %s " % (k,str(a.shape)))
        pass
        pmtID = aa[b'pmtID']
        pmtPosX = aa[b'pmtPosX']
        pmtPosY = aa[b'pmtPosY']
        pmtPosZ = aa[b'pmtPosZ']
        MCP_Hama = aa[b'MCP_Hama']
        HiQE_MCP = aa[b'HiQE_MCP']

    elif uproot.version.version_info[0] == '4':

        # uproot 4 has new capabilities and API
        tt = uproot.open("%s:%s" % (path, name))
        aa = tt.arrays(library='np')  
        pmtID = aa["pmtID"]
        pmtPosX = aa["pmtPosX"]   
        pmtPosY = aa["pmtPosY"]   
        pmtPosZ = aa["pmtPosZ"]   
        MCP_Hama = aa["MCP_Hama"]
        HiQE_MCP = aa["HiQE_MCP"]
 
    else:
        pass
    pass

    x_pmtID = np.arange( 17612, dtype=np.int32 ) 
    assert np.all( pmtID == x_pmtID )

    assert len(pmtPosX) == len(pmtPosY) == len(pmtPosZ)
    pos = np.empty( (len(pmtPosX),3) )
    pos[:,0] = pmtPosX
    pos[:,1] = pmtPosY
    pos[:,2] = pmtPosZ

    plot3d(pos)




