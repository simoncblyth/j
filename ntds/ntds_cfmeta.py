#!/usr/bin/env python
"""
ntds_cfmeta.py : Comparing Metadata such as history frequencies across multiple SEvt pairs
============================================================================================

Comparisons are more powerful (within reasonable statistics)
when using common input photons. 

"""
import os, numpy as np
from opticks.sysrap.sevt import SEvt, SAB, MSAB

if __name__ == '__main__':
    NEVT = int(os.environ.get("NEVT","10"))
    AFOLD = os.path.expandvars("$AFOLD")
    BFOLD = os.path.expandvars("$BFOLD")
    msab = MSAB(NEVT, AFOLD, BFOLD, symbol="msab")
    print(msab)

