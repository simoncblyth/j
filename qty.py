#!/usr/bin/env python
"""

"""

import os, logging, numpy as np

np.set_printoptions(suppress=True, edgeitems=5, linewidth=200,precision=3)

try:
    import matplotlib.pyplot as mp  
except ImportError:
    mp = None
pass

log = logging.getLogger(__name__)


s_conv = lambda s:float(s) if s.find("*") == -1 else float(s[0:s.find("*")])

class Qty(object):
   @classmethod
   def Path(cls, name):
       return os.path.join(os.path.expandvars("$JUNOTOP/data/Simulation/DetSim"), name.replace(".","/"))      

   @classmethod
   def Load(cls, path, kv=False):
       if kv:
           dtype = [('key',"|S50"), ('value',"f8")]
           delimiter = None 
           converters = {1:s_conv}
           encoding = "latin1"
       else:
           dtype = np.float64
           delimiter = "\t"
           converters = {0:s_conv,1:s_conv}
           encoding = "latin1"
       pass

       a = np.genfromtxt(path, dtype=dtype, delimiter=delimiter, converters=converters, encoding=encoding )
       return a 

   def __init__(self, name, kv=False, scale=1. ):
       path = self.Path(name)
       a = self.Load(path, kv=kv)
       self.name = name
       self.path = path
       self.a = a
       self.scale = scale 
       self.kv = dict(zip(a["key"], a["value"])) if kv else {}

   def __repr__(self):
       return "%15s : %20s : %10.4f : %s " % ( str(self.a.shape), self.name, self.scale, self.path )   


class Plt(object):
    size = np.array([1280, 720])
    outdir = os.path.expandvars("/tmp/$USER/j/qty")

    @classmethod
    def Material_LS_ABSLENGTH(cls):
        figname = "Material_LS_ABSLENGTH"

        s = Qty("Material.LS.scale", kv=True )
        scale_abslength = s.kv[b'AbsorptionLenAfter']/s.kv[b'AbsorptionLenBefore'] 

        a = Qty("Material.LS.ABSLENGTH_v1", scale=scale_abslength )
        b = Qty("Material.LS.ABSLENGTH_v2", scale=1. )

        label = "https://github.com/simoncblyth/j/blob/main/qty.py"
        title = "\n".join( [label] + list(map(repr, [a,b] )) )

        print(title)

        fig, ax = mp.subplots(figsize=Plt.size/100.)
        fig.suptitle(title)

        for q in [a, b]:
            ax.plot( q.a[:,0], q.a[:,1]*q.scale, label=q.name )
        pass
        ax.legend()
        fig.show()
        cls.save(fig, figname)

    @classmethod
    def save(cls, fig, figname):
        if not os.path.isdir(cls.outdir):
            os.makedirs(cls.outdir)
        pass
        outpath = os.path.join(cls.outdir,figname+"_mpplt.png")
        print("saving %s " % outpath)
        fig.savefig(outpath)



if __name__ == '__main__':

    logging.basicConfig(level=logging.INFO)

    Plt.Material_LS_ABSLENGTH()






    


