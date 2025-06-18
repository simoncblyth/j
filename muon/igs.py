#!/usr/bin/env python

import os, numpy as np
np.set_printoptions(suppress=True, precision=3)

igs = np.load(os.path.expandvars("$IGS_PATH"))
igs_idx = list(map(int,os.environ.get("IGS_IDX", "0,1,2" ).split(",")))

print("igs.shape %s" % str(igs.shape) )
print("igs_idx %s" % str(igs_idx))
print("igs\n", igs)

for idx in igs_idx:
    expr = "igs[%d]" % idx
    print(expr)
    print(repr(eval(expr)))
pass
    





