#!/usr/bin/env python
"""
qty.py
=========

Used from qty.sh 

"""

import os, logging, numpy as np, textwrap
log = logging.getLogger(__name__)

np.set_printoptions(suppress=True, edgeitems=5, linewidth=200,precision=3)

try:
    import matplotlib.pyplot as mp  
except ImportError:
    mp = None
pass


s_conv = lambda s:float(s) if s.find("*") == -1 else float(s[0:s.find("*")])


class Qty(object):
   @classmethod
   def Path(cls, name):
       return os.path.join(os.path.expandvars("$JUNOTOP/data/Simulation/DetSim"), name.replace(".","/"))      

   @classmethod
   def LoadArray(cls, path, kv=False, delimiter="\t"):
       if kv:
           dtype = [('key',"|S50"), ('value',"f8")]
           delimiter = None 
           converters = {1:s_conv}
           encoding = "latin1"
       else:
           dtype = np.float64
           converters = {0:s_conv,1:s_conv}
           encoding = "latin1"
       pass
       log.info(path) 
       a = np.genfromtxt(path, dtype=dtype, delimiter=delimiter, converters=converters, encoding=encoding )
       return a 

   @classmethod
   def Load(cls, name, kv=False, scale=1., delimiter="\t" ):
       path = cls.Path(name)
       log.info("name %s path %s " % (name, path))

       try:
           a = cls.LoadArray(path, kv=kv, delimiter=delimiter )
       except IndexError:
           a = None
           log.fatal("failed to load from path %s " % path )
       pass 
       return cls(name, path, a, scale, kv )

   def __init__(self, name, path, a, scale, kv=False):
       self.name = name
       self.path = path
       self.a = a
       self.scale = scale 
       self.kv = dict(zip(a["key"], a["value"])) if kv else {}

   def __repr__(self):
       ashape = "-" if self.a is None else str(self.a.shape) 
       return "%15s : %20s : %10.4f : %s " % ( ashape, self.name, self.scale, self.path )   


class QDir(object):
   def __init__(self, name):
       path = Qty.Path(name)
       names = os.listdir(path)

       self.name = name
       self.path = path
       self.names = names 

   def __repr__(self):
        return "%20s : %3d : %s " % ( self.name, len(self.names), self.path )

   def qty(self, rel):
       qname = "%s.%s" % (self.name, rel)
       return Qty.Load(qname)


class Plt(object):
    size = np.array([1280, 720])
    outdir = os.path.expandvars("/tmp/$USER/j/qty")

    @classmethod
    def save(cls, fig, figname):
        if not os.path.isdir(cls.outdir):
            os.makedirs(cls.outdir)
        pass
        outpath = os.path.join(cls.outdir,figname+"_mpplt.png")
        print("saving %s " % outpath)
        fig.savefig(outpath)

    @classmethod
    def make(cls, figname, qq, opt="", xlim=None): 

        label = "https://github.com/simoncblyth/j/blob/main/qty.py"
        title = [label, figname] 
        reps = list(map(repr, qq )) 
        if len(qq) < 3:
            title += reps    
        pass       
        suptitle = "\n".join(title)

        print("suptitle\n",suptitle)
        print("reps\n", "\n".join(reps) )

        fig, ax = mp.subplots(figsize=Plt.size/100.)
        fig.suptitle(suptitle)

        for q in qq:
            a = q.a 
            if a is None: continue
            ax.plot( a[:,0], a[:,1]*q.scale, label=q.name )
        pass
        if "logy" in opt:
            ax.set_yscale('log')
        pass
        if not xlim is None:
            ax.set_xlim(*xlim)
        pass

        ax.legend()
        fig.show()
        Plt.save(fig, figname)
 

class Material_LS_ABSLENGTH(object):
    def __init__(self):
        figname = "Material_LS_ABSLENGTH"

        s = Qty.Load("Material.LS.scale", kv=True )
        scale_abslength = s.kv[b'AbsorptionLenAfter']/s.kv[b'AbsorptionLenBefore'] 

        a = Qty.Load("Material.LS.ABSLENGTH_v1", scale=scale_abslength )
        b = Qty.Load("Material.LS.ABSLENGTH_v2", scale=1. )
        c = Qty.Load("Material.LS.PPOABSLENGTH", scale=1. )
        d = Qty.Load("Material.LS.bisMSBABSLENGTH", scale=1. )

        qq = [a,b,c,d]

        Plt.make(figname, qq, opt="logy", xlim=[1,8]  )

        self.a = a 
        self.b = b 
        self.c = c 
        self.d = d 
 

class Material_LS_COMPONENT(object):
    def __init__(self):
        figname = "Material_LS_COMPONENT"

        a = Qty.Load("Material.LS.FASTCOMPONENT",   delimiter="*eV")
        b = Qty.Load("Material.LS.SLOWCOMPONENT",   delimiter="*eV")
        c = Qty.Load("Material.LS.PPOCOMPONENT",    delimiter="\t" )     
        d = Qty.Load("Material.LS.bisMSBCOMPONENT", delimiter="*eV" )

        qq = [a,b,c,d]

        Plt.make(figname, qq, opt="logy", xlim=[1.5,4.5] )

        self.a = a 
        self.b = b 
        self.c = c 
        self.d = d 


class Material_LS_REEMISSIONPROB(object):
    def __init__(self):
        figname = "Material_LS_REEMISSIONPROB"

        a = Qty.Load("Material.LS.REEMISSIONPROB",   delimiter="*eV")
        b = Qty.Load("Material.LS.PPOREEMISSIONPROB",   delimiter="*eV")
        c = Qty.Load("Material.LS.bisMSBREEMISSIONPROB",   delimiter="*eV")

        qq = [a,b,c]

        Plt.make(figname, qq  )

        self.a = a 
        self.b = b 
        self.c = c 


class Material_RINDEX(object):
    def __init__(self):
        figname = "Material_RINDEX"
        symbols = "abcdefghijklmnopqrstuvqxyz"
        names = "LS Water vetoWater Pyrex Acrylic".split()

        qq = []
        for i, name in enumerate(names):
            q = Qty.Load("Material.%s.RINDEX" % name, delimiter="*eV" )
            symbol = symbols[i] 
            locals()[symbol] = q 
            qq.append(q)
        pass
        Plt.make(figname, qq  )


class Material_RAYLEIGH(object):
    def __init__(self):
        figname = "Material_RAYLEIGH"
        symbols = "abcdefghijklmnopqrstuvqxyz"
        names = "LS".split()

        qq = []
        for i, name in enumerate(names):
            q = Qty.Load("Material.%s.RAYLEIGH" % name, delimiter="*eV" )
            symbol = symbols[i] 
            locals()[symbol] = q 
            qq.append(q)
        pass
        Plt.make(figname, qq  )


class Material_ABSLENGTH(object):
    def __init__(self):
        figname = "Material_ABSLENGTH"
        symbols = "abcdefghijklmnopqrstuvqxyz"
        names = textwrap.dedent("""
        Acrylic
        AcrylicMask
        Air
        CDInnerReflector
        ESR
        ETFE
        FEP
        LatticedShellSteel
        MineralOil
        Mylar
        PA
        PE_PA
        Pyrex
        Rock
        StainlessSteel
        Steel
        StrutSteel
        Tyvek
        #Vacuum
        #VacuumT
        Water
        vetoWater
        """).split()

        names = list(filter(lambda name:not name.startswith("#"), names))


        qq = []
        for i, name in enumerate(names):
            q = Qty.Load("Material.%s.ABSLENGTH" % name, delimiter="*eV" )
            symbol = symbols[i] 
            locals()[symbol] = q 
            qq.append(q)
        pass
        Plt.make(figname, qq , xlim=[1,8] )

 





if __name__ == '__main__':

    logging.basicConfig(level=logging.INFO)


    qd = QDir("Material.LS") 

    #lsa = Material_LS_ABSLENGTH()
    #lsc = Material_LS_COMPONENT()
    #lsr = Material_LS_REEMISSIONPROB()
    #rid = Material_RINDEX()
    #ray = Material_RAYLEIGH()
    abl = Material_ABSLENGTH()

    #a = Qty.Load("Material.LS.FASTCOMPONENT", delimiter="*eV") 


    


