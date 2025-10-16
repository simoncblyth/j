"""
hit_density.py

Impossibly coarse approach : would need far too many bins 

"""

import numpy as np
import pyvista as pv


def hit_density(f):
    # Extract positions
    pos = f.hit[:, 0, :3]
    mins, maxs = np.nanmin(pos, axis=0), np.nanmax(pos, axis=0)
    print("mins %s " % repr(mins))
    print("maxs %s " % repr(maxs))

    # Compute 3D histogram
    nx, ny, nz = 100, 100, 100
    hist, edges = np.histogramdd(pos, bins=(nx, ny, nz), range=[(mins[0], maxs[0]), (mins[1], maxs[1]), (mins[2], maxs[2])])
    print("hist %s " % repr(hist))

    hist = np.log1p(hist)  # Optional: log scale for visualization


    # formerly UniformGrid
    grid = pv.ImageData(
        dimensions=(nx, ny, nz),
        spacing=((maxs[0] - mins[0]) / nx, (maxs[1] - mins[1]) / ny, (maxs[2] - mins[2]) / nz),
        origin=mins
    )
    grid["density"] = hist.ravel(order="F")
    plotter = pv.Plotter()
    plotter.add_volume(grid, scalars="density", opacity="sigmoid")
    plotter.show()




