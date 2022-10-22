#!/usr/bin/env python

import numpy as np
from opticks.ana.fold import Fold 

if __name__ == '__main__':
    a = Fold.Load("/tmp/LayrTest0", symbol="a")
    b = Fold.Load("/tmp/LayrTest1", symbol="b")
    print(repr(a))
    print(repr(b))
pass

