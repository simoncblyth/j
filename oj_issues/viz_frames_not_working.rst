viz_frames_not_working
=========================


Actually they are jumping with::

    export CSGOptiXRenderInteractiveTest__FRAME_HOP=1

But the viewpoints are not in expected positions. 



Testing with the oj release geometry on P with old executable
behaves as expected::

    P[blyth@localhost opticks]$ git diff 
    diff --git a/CSGOptiX/cxr_min.sh b/CSGOptiX/cxr_min.sh
    index cba88137f..be1cfc0d2 100755
    --- a/CSGOptiX/cxr_min.sh
    +++ b/CSGOptiX/cxr_min.sh
    @@ -254,6 +254,8 @@ Resolve_CFBaseFromGEOM()
        local A_CFBaseFromGEOM=$HOME/.opticks/GEOM/$GEOM
        local B_CFBaseFromGEOM=$TMP/G4CXOpticks_setGeometry_Test/$GEOM
        local C_CFBaseFromGEOM=/cvmfs/opticks.ihep.ac.cn/.opticks/GEOM/$GEOM
    +   local D_CFBaseFromGEOM=/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.3.5/el9_amd64_gcc11/Latest/.opticks/GEOM/J25_3_0_Opticks_v0_3_5
    +
     
        local TestPath=CSGFoundry/prim.npy
        local GDMLPathFromGEOM=$HOME/.opticks/GEOM/$GEOM/origin.gdml 
    @@ -267,6 +269,9 @@ Resolve_CFBaseFromGEOM()
         elif [ -d "$C_CFBaseFromGEOM" -a -f "$C_CFBaseFromGEOM/$TestPath" ]; then
             export ${GEOM}_CFBaseFromGEOM=$C_CFBaseFromGEOM
             echo $BASH_SOURCE : FOUND C_CFBaseFromGEOM $C_CFBaseFromGEOM containing $TestPath
    +    elif [ -d "$D_CFBaseFromGEOM" -a -f "$D_CFBaseFromGEOM/$TestPath" ]; then
    +        export ${GEOM}_CFBaseFromGEOM=$D_CFBaseFromGEOM
    +        echo $BASH_SOURCE : FOUND D_CFBaseFromGEOM $D_CFBaseFromGEOM containing $TestPath
         elif [ -f "$GDMLPathFromGEOM" ]; then 
             export ${GEOM}_GDMLPathFromGEOM=$GDMLPathFromGEOM
             echo $BASH_SOURCE : FOUND GDMLPathFromGEOM $GDMLPathFromGEOM 
    P[blyth@localhost opticks]$ 


So issue not with geometry or frames, somehow issue is with the executable
that was distributed. 




Frames not identical but close
--------------------------------


Frames::

    A[blyth@localhost frame]$ pwd
    /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.3.5/el9_amd64_gcc11/Mon/.opticks/GEOM/J25_3_0_Opticks_v0_3_5/CSGFoundry/SSim/scene/frame

::

    A[blyth@localhost frame]$ which python
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Python/3.11.10/bin/python
    A[blyth@localhost frame]$ python -i 

    >>> a = np.load("Hama_0_0.npy")

    >>> np.set_printoptions(suppress=True)
    >>> a
    array([[[    0.        ,     0.        ,     8.43770635,   264.1000061 ],
            [    0.        ,     0.        ,     0.        ,     0.        ],
            [    0.        ,     0.        ,     0.        ,     0.        ],
            [    0.        ,     0.        ,     0.        ,     0.        ]],

           [[    0.9917208 ,     0.11917904,     0.04781426,     0.        ],
            [    0.11931551,    -0.99285639,     0.        ,     0.        ],
            [    0.04747269,     0.00570498,    -0.99885624,     0.        ],
            [ -920.36102295,  -110.60299683, 19365.        ,     0.        ]],

           [[    0.9917208 ,     0.11931551,     0.04747269,     0.        ],
            [    0.11917904,    -0.99285639,     0.00570498,     0.        ],
            [    0.04781426,     0.        ,    -0.99885624,     0.        ],
            [   -0.00036891,     0.00044831, 19387.17417355,     0.        ]]])
    >>> import os
    >>> os.getcwd()
    '/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.3.5/el9_amd64_gcc11/Mon/.opticks/GEOM/J25_3_0_Opticks_v0_3_5/CSGFoundry/SSim/scene/frame'
    >>> 


    P[blyth@localhost frame]$ python -i 
    Python 3.9.19 (main, Mar 26 2024, 13:37:53) 
    [GCC 11.2.0] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import numpy as np
    >>> a = np.load("Hama_0_0.npy")
    >>> np.set_printoptions(suppress=True)
    >>> a
    array([[[    0.        ,     0.        ,     8.43770635,   264.1000061 ],
            [    0.        ,     0.        ,     0.        ,     0.        ],
            [    0.        ,     0.        ,     0.        ,     0.        ],
            [    0.        ,     0.        ,     0.        ,     0.        ]],

           [[    0.9917208 ,     0.11917904,     0.04781426,     0.        ],
            [    0.11931551,    -0.99285639,     0.        ,     0.        ],
            [    0.04747269,     0.00570498,    -0.99885624,     0.        ],
            [ -920.36151123,  -110.60279846, 19365.        ,     0.        ]],

           [[    0.9917208 ,     0.11931551,     0.04747269,     0.        ],
            [    0.11917904,    -0.99285639,     0.00570498,     0.        ],
            [    0.04781426,     0.        ,    -0.99885624,     0.        ],
            [    0.00009168,     0.00070352, 19387.1741956 ,     0.        ]]])
                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^

    >>> import os
    >>> os.getcwd()
    '/home/blyth/.opticks/GEOM/J_2025jan08/CSGFoundry/SSim/scene/frame'
    >>> 






