#!/usr/bin/env python

"""

// EMF_ZC_32 / EMF_RC_32:
//   32 tilted rings (holders) defined in cylindrical coordinates around
//   the tilted axis a (θ = 56°, φ = −54°).
//   - Zc : coordinate along axis a, measured from the world origin (m). 
//   - Rc : radial distance from axis a to the “neutral layer” of the ring (m). 
static const double EMF_ZC_32[32] = {
    21.271,  20.602,  19.554,  18.555,
    17.077,  15.600,  14.122,  12.644,
    11.163,   9.685,   8.207,   6.729,
     5.251,   3.773,   2.295,   0.817,
    -0.821,  -2.299,  -3.777,  -5.255,
    -6.733,  -8.210,  -9.688, -11.166,
   -12.644, -14.122, -15.600, -17.077,
   -18.555, -19.554, -20.602, -21.271
};


"""


import numpy as np
np.set_printoptions(suppress=True)

def create_model_to_world(ax, up, translation):
    """



            z
            |
            |
            |
            |
            +--------- y
           /
          /
         x


    """
    # 1. Calculate the 'Right' vector (X-axis)
    # Using cross product: Right = Up x Forward (ax)
    right = np.cross(up, ax)
    right /= np.linalg.norm(right)

    # 2. Re-calculate Up to ensure perfect perpendicularity
    # Up = Forward (ax) x Right
    up_rectified = np.cross(ax, right)

    # 3. Create the 4x4 Identity Matrix
    m2w = np.eye(4)

    # 4. Set the rotation columns (Basis vectors)
    m2w[:3, 0] = right       # X-axis
    m2w[:3, 1] = up_rectified # Y-axis
    m2w[:3, 2] = ax           # Z-axis

    # 5. Set the translation column
    m2w[:3, 3] = translation

    # transpose is lazy, without np.ascontiguousarray get unexpected fortran_order True
    return np.ascontiguousarray(m2w.T)



if __name__ == '__main__':
    # Your existing coordinate logic
    theta = 56. * np.pi / 180.
    phi = -54. * np.pi / 180.

    st, ct = np.sin(theta), np.cos(theta)
    sp, cp = np.sin(phi), np.cos(phi)

    # This is our local Forward (Z) axis
    ax = np.array([st * cp, st * sp, ct])

    # Projection to find Up (Y) axis
    world_z = np.array([0, 0, 1])
    up = world_z - np.dot(world_z, ax) * ax
    up /= np.linalg.norm(up)

    # Define your translation (tx, ty, tz)
    delta = -5

    translation = ax*-(21271+delta)
    #translation = ax*0

    # Generate the matrix
    m2w = create_model_to_world(ax, up, translation)   # my convention is transposed

    print("Model-to-World Matrix:")
    print(m2w)

    extent = 5000

    path = "/tmp/emf2.npy"
    path_meta = path.replace(".npy","_meta.txt")

    print("saving to %s %s " % ( path, path_meta ))
    np.save(path, m2w )
    open(path_meta,"w").write("extent:%s" % extent )


