#!/usr/bin/env python

import os 


class ExternalLib(object):

    @classmethod
    def Dump(cls):
        cfg = dict(ptop=os.environ["PREVIOUS_JUNO_EXTLIB_OLDTOP"], otop=os.environ["JUNO_EXTLIB_OLDTOP"])
        exdir = os.path.expandvars("$JUNOTOP/ExternalLibs")
        for libname in os.listdir(exdir):
            lib = ExternalLib(exdir,libname, cfg)  
            print(lib)
        pass

    @classmethod
    def ClassifyVersionDir(cls, vdir, cfg):
        if os.path.islink(vdir):
            lnk = os.readlink(vdir)
            for k, v in cfg.items():
                if lnk.startswith(v):
                   lnk = k
                pass 
        else: 
            lnk = "loc"
        pass
        return lnk

    def __init__(self, base, name, cfg):
        fold = os.path.join(base, name)
        vers = os.listdir(fold) 

        smry = []
        for ver in vers:
            vdir = os.path.join(fold, ver)
            lnk = self.ClassifyVersionDir(vdir, cfg) 
            smry.append( "%s:%s" % (ver, lnk))
        pass

        self.fold = fold 
        self.name = name
        self.vers = vers 
        self.smry = smry 
        self.cfg = cfg

    def __repr__(self):
        return "%20s : %s " % (self.name, " ".join(self.smry) )


if __name__ == '__main__':
    ExternalLib.Dump()

