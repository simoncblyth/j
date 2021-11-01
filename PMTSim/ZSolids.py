#!/usr/bin/env python 

import numpy as np
import matplotlib.pyplot as plt 


class ZSolids(object):
    def __init__(self, path="/tmp/ZSolids.npy"):
        a = np.load(path)

        fig,ax = plt.subplots() 
        for i in range(len(a)):
            az0 = a[i,1,0] 
            az1 = a[i,1,1] 


            x0 = i*100.
            x1 = (i+1)*100.
            ax.plot( [x0, x0], [az0, az1], label=str(i) )


            if i < len(a) - 1:
                az0next = a[i+1,1,0] 
                az1next = a[i+1,1,1] 
                ax.plot( [x0, x1], [az0, az1next] )
            pass

        pass
        ax.legend()
        fig.show()




if __name__ == '__main__':
    zs = ZSolids()





