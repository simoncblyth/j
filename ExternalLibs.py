#!/usr/bin/env python
"""

N[blyth@localhost j]$ ./ExternalLibs.py 
                                 J22.1.x         J22.1.0-rc0         J22.1.0-rc1         J22.1.0-rc2         J22.1.0-rc3         J22.1.0-rc4
                 CMT               v1r26               v1r26               v1r26               v1r26               v1r26               v1r26
                 Git              2.34.1                NONE                NONE                NONE                NONE                NONE
                 gsl                 2.5                 2.5                 2.5                 2.5                 2.5                 2.5
                 tbb              2020.3              2020.3              2020.3              2020.3              2020.3              2020.3
                ROOT             6.24.06             6.24.06             6.24.06             6.24.06             6.24.06             6.24.06
               Boost              1.78.0              1.78.0              1.78.0              1.78.0              1.78.0              1.78.0
               CLHEP             2.4.1.0             2.4.1.0             2.4.1.0             2.4.1.0             2.4.1.0             2.4.1.0
               Cmake              3.22.1              3.22.1              3.22.1              3.22.1              3.22.1              3.22.1
               HepMC             2.06.09             2.06.09             2.06.09             2.06.09             2.06.09             2.06.09
               fftw3               3.3.8               3.3.8               3.3.8               3.3.8               3.3.8               3.3.8
               genie             3.00.06             3.00.06             3.00.06             3.00.06             3.00.06             3.00.06
               nuwro             19.02.2             19.02.2             19.02.2             19.02.2             19.02.2             19.02.2
               talys                1.95                1.95                1.95                1.95                1.95                1.95
              Geant4      10.04.p02.juno      10.04.p02.juno      10.04.p02.juno      10.04.p02.juno      10.04.p02.juno      10.04.p02.juno
              LHAPDF               6.3.0               6.3.0               6.3.0               6.3.0               6.3.0               6.3.0
              Python              3.8.12              3.8.12              3.8.12              3.8.12              3.8.12              3.8.12
              xrootd               5.3.4               5.3.4               5.3.4               5.3.4               5.3.4               5.3.4
             Xercesc               3.2.2               3.2.2               3.2.2               3.2.2               3.2.2               3.2.2
             libmore               0.8.3               0.8.3               0.8.3               0.8.3               0.8.3               0.8.3
             libxml2              2.9.12              2.9.12              2.9.12              2.9.12              2.9.12              2.9.12
             libyaml               0.2.4               0.2.4               0.2.4               0.2.4               0.2.4               0.2.4
             log4cpp               1.1.3               1.1.3               1.1.3               1.1.3               1.1.3               1.1.3
             pythia6              6.4.28              6.4.28              6.4.28              6.4.28              6.4.28              6.4.28
             sqlite3              3.35.5              3.35.5              3.35.5              3.35.5              3.35.5              3.35.5
            frontier               2.9.1               2.9.1               2.9.1               2.9.1               2.9.1               2.9.1
           pacparser               1.3.7               1.3.7               1.3.7               1.3.7               1.3.7               1.3.7
          python-pip              21.2.4              21.2.4              21.2.4              21.2.4              21.2.4              21.2.4
         python-yaml             5.4.1.1             5.4.1.1             5.4.1.1             5.4.1.1             5.4.1.1             5.4.1.1
        python-numpy              1.21.4              1.21.4              1.21.4              1.21.4              1.21.4              1.21.4
       python-cython             0.29.24             0.29.24             0.29.24             0.29.24             0.29.24             0.29.24
   mysql-connector-c               6.1.9               6.1.9               6.1.9               6.1.9               6.1.9               6.1.9
   python-setuptools              58.0.4              58.0.4              58.0.4              58.0.4              58.0.4              58.0.4
 mysql-connector-cpp              1.1.12              1.1.12              1.1.12              1.1.12              1.1.12              1.1.12
               gibuu            r2021_01            r2021_01            r2021_01            r2021_01            r2021_01            r2021_01
      libonnxruntime              1.11.1                NONE                NONE              1.11.1              1.11.1              1.11.1
N[blyth@localhost j]$ 



bash junoenv libs vlist 

function juno-ext-libs-git-version- { echo 2.37.3 ; }
function juno-ext-libs-cmake-version- { echo 3.24.1 ; }
function juno-ext-libs-python-version- { echo 3.9.14 ; }
function juno-ext-libs-python-setuptools-version- { echo 58.1.0 ; }
function juno-ext-libs-python-pip-version- { echo 22.2.2 ; }
function juno-ext-libs-python-cython-version- { echo 0.29.28 ; }
function juno-ext-libs-python-numpy-version- { echo 1.22.3 ; }
function juno-ext-libs-libyaml-version- { echo 0.2.4 ; }
function juno-ext-libs-python-yaml-version- { echo 5.4.1.1 ; }
function juno-ext-libs-boost-version- { echo 1.78.0 ; }
function juno-ext-libs-xercesc-version- { echo 3.2.3 ; }
function juno-ext-libs-gsl-version- { echo 2.7 ; }
function juno-ext-libs-fftw3-version- { echo 3.3.10 ; }
function juno-ext-libs-sqlite3-version- { echo 3.38.5 ; }
function juno-ext-libs-mysql-connector-c-version- { echo 6.1.9 ; }
function juno-ext-libs-mysql-connector-cpp-version- { echo 1.1.12 ; }
function juno-ext-libs-pacparser-version- { echo 1.3.7 ; }
function juno-ext-libs-frontier-version- { echo 2.9.1 ; }
function juno-ext-libs-log4cpp-version- { echo 1.1.3 ; }
function juno-ext-libs-libxml2-version- { echo 2.9.12 ; }
function juno-ext-libs-LHAPDF-version- { echo 6.3.0 ; }
function juno-ext-libs-pythia6-version- { echo 6.4.28 ; }
function juno-ext-libs-tbb-version- { echo 2020.3 ; }
function juno-ext-libs-clhep-version- { echo 2.4.1.0 ; }
function juno-ext-libs-xrootd-version- { echo 5.4.3 ; }
function juno-ext-libs-ROOT-version- { echo 6.26.06 ; }
function juno-ext-libs-hepmc-version- { echo 2.06.11 ; }
function juno-ext-libs-geant4-version- { echo 10.04.p02.juno ; }
function juno-ext-libs-genie-version- { echo 3.02.00 ; }
function juno-ext-libs-nuwro-version- { echo 19.02.2 ; }
function juno-ext-libs-talys-version- { echo 1.95 ; }
function juno-ext-libs-gibuu-version- { echo r2021_01 ; }
function juno-ext-libs-libmore-version- { echo 0.8.3 ; }
function juno-ext-libs-libmore-data-version- { echo 20140630 ; }
function juno-ext-libs-libonnxruntime-version- { echo 1.11.1 ; }



"""

import os 


class ExternalLib(object):
    @classmethod
    def ReadLink(cls, vdir):
        return os.readlink(vdir) if os.path.islink(vdir) else "loc"

    def __init__(self, base, name):
        """
        :param base:
        :param name:
        """
        fold = os.path.join(base, name)
        vers = os.listdir(fold) 

        smry = []
        for ver in vers:
            vdir = os.path.join(fold, ver)
            lnk = self.ReadLink(vdir) 
            if lnk.startswith(base):
                lnk = lnk[len(base):]
            pass
            #smry.append( "%20s:%s" % (ver, lnk))
            smry.append( "%20s" % (ver))
        pass
        self.fold = fold 
        self.name = name
        self.vers = vers 
        self.smry = smry 

    def __repr__(self):
        return "%20s : %s " % (self.name, " ".join(self.smry) )


class ExternalLibs(object):
    @classmethod
    def Compare(cls, relb, pfx=""):
        versions = os.listdir(relb)
        xlibs = []
        for vers in versions:
            if pfx is None or vers.startswith(pfx): 
                xlibdir = os.path.join(relb, vers, "ExternalLibs")
                if os.path.isdir(xlibdir):
                    xlib = ExternalLibs(xlibdir, vers=vers)
                    #print(xlib)
                    xlibs.append(xlib)
                pass
            pass
        pass
        cls.Tabulate(xlibs)

    @classmethod
    def Tabulate(cls, xlibs):
        vline = ""
        vline += "%20s" % ""  
        for xlib in xlibs:
            vline += "%20s" % (xlib.vers)
        pass
        print(vline)
        allnames = []   # using a set yields whacky ordering 
        for xlib in xlibs:
            for n in xlib.names:
                if not n in allnames:
                    allnames.append(n)
                pass
            pass
        pass
        for n in allnames:
            line = ""
            line += "%20s" % n
            for xlib in xlibs:
                v = xlib.get_version(n)
                line += "%20s" % v
            pass
            print(line)
        pass
        
    def __init__(self, base=None, vers=None):
        if base is None:
             base = os.path.expandvars("$JUNOTOP/ExternalLibs")
        pass
        libs = []

        names = os.listdir(base)
        for name in names:
            lib = ExternalLib(base,name)  
            libs.append(lib)
        pass
        self.base = base 
        self.vers = vers 
        self.libs = libs
        self.names = names

    def get_index(self, n):
        idx = self.names.index(n) if n in self.names else -1 
        return idx

    def get_version(self, n):
        idx = self.get_index(n)
        if idx == -1:
            v = "NONE"
        else:
            lib = self.libs[idx] 
            v = " ".join(lib.vers)
        pass
        return v

    def override(self):
        """
        function juno-ext-libs-git-version- { echo 2.37.3 ; }
        """
        return ""
   

    def __repr__(self):
        return "\n".join(["ExternalLibs:%s" % self.vers] + list(map(repr, self.libs)))


if __name__ == '__main__':
    relb = "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release"
    pfx = "J22.1"
    ExternalLibs.Compare(relb, pfx=pfx)

