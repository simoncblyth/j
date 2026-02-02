overlap_check
===============

raytrace shows lots of overlaps
-------------------------------

::

    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:1:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:2:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:3:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:4:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:5:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:6:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:7:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:8:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:9:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:10:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:11:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:12:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:13:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:14:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:15:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:16:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:30:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:20:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:25:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:30:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:29:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:30:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:29:-2 EYE=1,1,0 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:29:-2 EYE=1,1,1 LOOK=0,0,1 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:28:-2 EYE=1,1,1 LOOK=0,0,1 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:27:-2 EYE=1,1,1 LOOK=0,0,1 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:26:-2 EYE=1,1,1 LOOK=0,0,1 cxr_min.sh 
    FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:25:-2 EYE=1,1,1 LOOK=0,0,1 cxr_min.sh 




"ring-radial-overlap-check"
------------------------------

Using simtrace 2dxy plots within the slanted (or horizontal) global frames
of the emf holders or supports yields plots with circles for intersects onto the EMF rings, 
when viewed from where z=0 within the relevant 23+32 frames.

To more systematically find overlaps it would be good to plot for each prim selection:

* global frame 3D radius vs local-frame-phi-angle 


::

    demonstrate an overlap between the slanted s_EMFcoil_holder_ring  GZ1.A03_04_FlangeI_Web_FlangeII using frame AXIS:56,-54,6729.0,20502.0,24.0















MOI::

    moi=AXIS:56,-54,6729.0,20502.0,24.0 # 11
    ## 20502.0 + 24.0 is along the (theta:56,phi:-54) slanted axis : corresponding to a middle ring


Adding global frame *gpts* to cxt_min.py:SimtracePlot shows the 3D global radius of the ring points to be ~21585::


    In [3]: yg = spl.gpts['yellowgreen']

    In [4]: np.sqrt(np.sum( yg*yg, axis=1 ))
    Out[4]: array([21583.625, 21583.627, 21583.625, 21583.627, 21583.627, ..., 21587.426, 21587.426, 21587.428, 21587.426, 21587.428], shape=(32499,), dtype=float32)

    In [5]: r_yg = np.sqrt(np.sum( yg*yg, axis=1 ))

    In [6]: r_yg.min(), r_yg.max()
    Out[6]: (np.float32(21583.625), np.float32(21587.43))

::

    In [7]: g_pos = spl.gpts['yellowgreen']

    In [8]: u_pos = spl.pts['yellowgreen']

    In [9]: u_pos
    Out[9]: 
    array([[-20477.836,   -952.957,      0.   ],
           [-18484.785,  -8863.557,      0.001],
           [-18856.836,  -8041.737,      0.   ],
           [-20469.842,  -1111.493,     -0.   ],
           [-18849.709,  -8058.431,      0.   ],
           ...,
           [ 15925.928,  12914.285,     -0.   ],
           [ 17820.912,  10140.462,     -0.   ],
           [ 13825.999,  15141.191,     -0.   ],
           [ 12510.367,  16245.141,     -0.001],
           [ 14724.867,  14268.574,      0.   ]], shape=(32499, 3), dtype=float32)

    In [10]: np.arctan2( u_pos[:,1], u_pos[:,2] )
    Out[10]: array([-1.571, -1.571, -1.571, -1.571, -1.571, ...,  1.571,  1.571,  1.571,  1.571,  1.571], shape=(32499,), dtype=float32)


::

    PRIMTAB=1 RADIAL=2 KEY=yellowgreen ./cxt_min.sh pdb





