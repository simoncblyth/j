#!/usr/bin/env python
import os
import numpy as np


class GT(object):
    def __init__(self, path="$JUNOTOP/junosw/Simulation/DetSimV2/DetSimOptions/data/Guide_Tube.csv", symbol="gt"):
        p = os.path.expandvars(path)
        assert(os.path.exists(p))
        d = np.loadtxt(p)
        self.path = p
        self.symbol = symbol
        self.d = d

    def __repr__(self):
        return "\n".join([self.path, "%s.d" % self.symbol, repr(self.d)]) 


if __name__ == '__main__':
    gt = GT(symbol="gt")
    print(gt)

    sphi = gt.d[:,1]
    dphi = gt.d[:,2]
    ephi = sphi + dphi

    np.all( sphi[1:] == ephi[:-1] )


