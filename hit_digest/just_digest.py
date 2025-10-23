
import os, numpy as np
g = np.load(os.path.expandvars("$HITFOLD/hitdig_gpu.npy"))
c = np.load(os.path.expandvars("$HITFOLD/hitdig_cpu.npy"))
df = np.where(~(g == c).all(axis=1))[0]
print(len(df))  # Should be 0

expr=r"""
g.shape
c.shape
df
g[67108864].tobytes().hex()
g[0].tobytes().hex()
"""
for e in list(filter(None,expr.split("\n"))):
    print(e)
    print(eval(e))
pass


