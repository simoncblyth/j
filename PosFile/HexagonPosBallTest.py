#!/usr/bin/env python
"""

"""

from collections import OrderedDict as odict 
import logging
log = logging.getLogger(__name__)
import numpy as np
import os 

class Radius(object):
    """
    jcv LSExpDetectorConstruction

    0116   m_rock_and_exphall = "RockAndExpHall";
     117     
     118   ball_r = 19.434*m; //19.5*m;
     119   ball_vetoPmt_r=20.55*m;
     120   //strut_r_acrylic =17820. *mm + 155.*mm + 600. *mm;  //17820. *mm + 165. *mm + 600. *mm + 35. *mm;
     121   strut_r_acrylic =17820. *mm + 256.9*mm + 1807.6/2. *mm;
     122   strut2_r_acrylic =17820. *mm + 256.9*mm + 1913.6/2 *mm;
     123   strutballhead_r_acrylic=17820. *mm + 256.9*mm-50.*mm;  
     124     
     125 
     126   strut_r_balloon =17715. *mm + 700 *mm + 5. *mm;
     127   fastener_r = 17820.*mm + 20.*mm; //17826. *mm;
     128   addition_r = 17820. *mm;
     129   upper_r = 17820.*mm + 140.*mm; 
     130   xjanchor_r = 17820.*mm ;
     131   xjfixture_r = 17820.*mm + 10.*mm + 13./2*mm; 
     132   sjclsanchor_r = 17699.938*mm;
     133   sjfixture_r = 17699.975*mm;
     134   sjreceiver_r = 17699.938*mm;
     135   sjreceiver_fastener_r = 17699.938*mm - 10.*mm - 13./2*mm;
     136   m_cd_name = "DetSim1";
     137   m_cd_enabled = true;
     138   m_wp_enabled = true;
     139   m_tt_enabled = true;
    """
    mm = 1. 
    strut_r_acrylic =17820. *mm + 256.9*mm + 1807.6/2. *mm;
    strut2_r_acrylic =17820. *mm + 256.9*mm + 1913.6/2 *mm;
    strutballhead_r_acrylic=17820. *mm + 256.9*mm-50.*mm;  
    strut_r_balloon =17715. *mm + 700 *mm + 5. *mm;
    fastener_r = 17820.*mm + 20.*mm; #//17826. *mm;
    addition_r = 17820. *mm;
    upper_r = 17820.*mm + 140.*mm; 
    xjanchor_r = 17820.*mm ;
    xjfixture_r = 17820.*mm + 10.*mm + 13./2*mm; 
    sjclsanchor_r = 17699.938*mm;
    sjfixture_r = 17699.975*mm;
    sjreceiver_r = 17699.938*mm;
    sjreceiver_fastener_r = 17699.938*mm - 10.*mm - 13./2*mm;
     


class PosFile(object):
    BASE = "$JUNOTOP/offline/Simulation/DetSimV2/DetSimOptions/data"

    @classmethod
    def Load(cls):
        confpath = os.path.expandvars("$JUNOTOP/offline/Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py")
        lines = list(filter(lambda line:line.find("data_load") > -1, open(confpath).read().splitlines() ))
        d = odict()    
        for line in lines:
            elem = line.split("\"")
            key = elem[1]
            name = elem[3] 
            base = os.path.expandvars(cls.BASE) 
            path = os.path.join(base, name)
            apath = path.replace(".csv", ".npy")
            assert os.path.exists(path)
            assert os.path.exists(apath)

            #print("%30s %30s " % (key, apath[len(base):]) )

            d[key] = cls(key, path, apath, base ) 
        pass
        return d 

    def __init__(self, key, path, apath, base ):
        t = np.genfromtxt(path, dtype=None, names=("copyNo","theta","phi") )
        a = np.load(apath)
        self.t = t 
        self.a = a
        self.path = path
        self.apath = apath
        self.base = base
        self.key = key 


    WID = (15,15,20,90) 
    FMT = "| %%%ds  | %%%ds | %%%ds | %%%ds |" % WID
    DFMT = FMT.replace("|","+").replace(" ","-")
    DIV  = DFMT % ( "-" * WID[0], "-" * WID[1], "-" * WID[2], "-" * WID[3] )
    TFMT = FMT.replace("|","+").replace(" ","=")
    TDIV  = TFMT % ( "=" * WID[0], "=" * WID[1], "=" * WID[2], "=" * WID[3] )
    TITLE = FMT % ( "csv", "npy", "key", "%s/" % BASE )

    def __repr__(self):
        lin = self.FMT  % ( str(self.t.shape), str(self.a.shape), self.key, self.path[len(self.base)+1:] )   
        return "\n".join( [lin, self.DIV,]) 


if __name__ == '__main__':
     logging.basicConfig(level=logging.INFO)
     pf = PosFile.Load()

     print(PosFile.DIV)
     print(PosFile.TITLE)
     print(PosFile.TDIV)
     for k in pf:
         print(pf[k])
     pass




