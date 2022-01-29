#!/usr/bin/env python
"""
RadiusTest.py
===============

::

   from j.PosFile.RadiusTest import RadiusTest
   rt = RadiusTest()
   print(rt.d["sjreceiver_fastener_r"])

"""
from collections import OrderedDict as odict
import numpy as np

class RadiusTest(object):
    STUB = "/tmp/RadiusTest"
    FMT = "%7.4f : %s"
    def __init__(self, stub=STUB):
        r = np.load("%s.npy" % stub)
        _n = open("%s_meta.txt" % stub).read().splitlines()
        n = np.array( _n, dtype="|S100" ) 

        assert len(r) == len(n)
        d = dict(zip(n,r))

        i = np.argsort(r) 
        rs = r[i][::-1]
        ns = n[i][::-1]

        ns = map(lambda s:s.decode("utf-8") ,ns)
        ds = odict(zip(ns,rs))

        self.r = rs
        self.n = ns  
        self.d = ds

    def __repr__(self):
        return "RadiusTest %s " % (str(self.d))   

    def __str__(self):
        return "\n".join([self.FMT % (self.d[k], k) for k in self.d])

    def mpplot(self, ax, xlim=(0,1)):
        pass
        for k, v in self.d.items():
            label = self.FMT % (v,k)
            ax.plot( xlim, [v, v], label=label )
        pass
        ax.legend()



import matplotlib.pyplot as mp

if __name__ == '__main__':
    rt = RadiusTest()
    print(rt)

    SIZE = np.array([1280, 720])
    fig, ax = mp.subplots(figsize=SIZE/100.)
    rt.mpplot(ax)
    fig.show()



