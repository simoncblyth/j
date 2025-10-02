cxt_min_simtrace_OVERLAP_checking
====================================

::

    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew cxt_min.sh pdb


Adhoc python level offset (shifting the point cloud) is not the same a real offset in the geometry,
but it should give the ballpark of how much offset is needed to avoid overlap::

    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-10 cxt_min.sh pdb      ## overlap_pt 187
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-20 cxt_min.sh pdb      ## overlap_pt 61
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-25 cxt_min.sh pdb      ## overlap_pt 5

    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-27 cxt_min.sh pdb      ##  overlap_pt 1
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-28 cxt_min.sh pdb      ## NO OVERLAP

    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-30 cxt_min.sh pdb      ## NO OVERLAP
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-1000 cxt_min.sh pdb    ## NO OVERLAP
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-1000 cxt_min.sh pdb    ## NO OVERLAP

With a few mm safety margin, would suggest z-shift downwards of 30mm is needed to avoid overlap between Waterdistributor and the
virtual wrapper of Hama PMTs.


