#!/usr/bin/env python
"""
   // Axis a（倾斜轴）：θ=56°, φ=-54°
    const double theta = 56.0 * PI / 180.0;
    const double phi   = -54.0 * PI / 180.0;

    const Vec3 axis_a(
        std::sin(theta) * std::cos(phi),
        std::sin(theta) * std::sin(phi),
        std::cos(theta)
    );
"""

import numpy as np

if __name__ == '__main__':

    theta = 56.*np.pi/180.
    phi = -54.*np.pi/180

    st,ct  = np.sin(theta),np.cos(theta)
    sp,cp  = np.sin(phi),np.cos(phi)

    ax = np.array( [st*cp,st*sp,ct] )


    # World Z
    world_z = np.array([0, 0, 1])

    # The 'Up' vector is the projection of World Z onto the holder plane
    # Formally: Up = World_Z - (World_Z dot ax) * ax
    up = world_z - np.dot(world_z, ax) * ax
    up = up / np.linalg.norm(up) # Normalize

    print(f"Look-at (Axis): {ax}")
    print(f"Up Vector:      {up}")



