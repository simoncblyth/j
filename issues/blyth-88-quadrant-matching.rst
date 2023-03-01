blyth-88-quadrant-matching.rst
=================================

* from :doc:`blyth-88-incorporation-notes`


WIP : Comparing U4SimulateTest.sh between corresponding N=0,1 quadrants for both hama and nnvt PMTs
------------------------------------------------------------------------------------------------------


+----------------+------------------------+--------------------------+
|                | PMT:0  (unnatural)     | PMT:1  (natural)         |  
+================+========================+==========================+
| POM:0          |                        |  #CustomG4OpBoundary     |
| (traditional)  |                        |                          | 
|                |                        |                          |   
+----------------+------------------------+--------------------------+
| POM:1          |     FastSim            |  @CustomG4OpBoundary     | 
| (ph in PMT)    |                        |                          | 
|                |          A             |           B              |   
+----------------+------------------------+--------------------------+


A vs B : manual statistical comparison (still with pmtid -1, pmtcat 0)
--------------------------------------------------------------------------

* A has many fake extras, which are expected and which complicate the comparison  

* Most prolific "A:TO BT BT SA" "B:TO BT SA"  

::

    In [8]: t.base,np.c_[qn,qi,qu][quo][:10]
    Out[8]: 
    ('/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL0',
     array([[b'595', b'0', b'TO BT BT SA                                                                                     '],
            [b'105', b'3', b'TO BT BT BR BT BT SA      reflect from cathode and gets absorbed on the wall (B:TO BT BR BT SA) 
            [b'105', b'5', b'TO BT BT BT BT SR SA      enter PMT reflect off inside of back hemi and get absorbed on red collar (B:TO BT BT SR SA)
            [b'46', b'13', b'TO BT BT BT BT SR SR SR BT SA                                                                   '],
            [b'38', b'41', b'TO BT BT BT BT SR SR SR BT BT BT BT SA                                                          '],
            [b'27', b'48', b'TO BT BT BT BT SR SR SR BT BR BT SR SA                                                          '],
            [b'22', b'17', b'TO BT BT BT BT SA                                                                               '],
            [b'13', b'201', b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT SA                                                 '],
            [b'9', b'336', b'TO BT BT BT BT SR SR SA                                                                         '],
            [b'8', b'203', b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BR BT SR SR BT BT BT BT SA                         ']], dtype='|S96'))

Visualize A:"TO BT BT BR BT BT SA" by using the "qi" first index column of the above::
     
    APID=3 N=1 ./U4SimtraceTest.sh ana

Find photon with corresponding history in B:"TO BT BR BT SA" with fakes skipped, using "qi" first index from B below::

    BPID=2 N=1 ./U4SimtraceTest.sh ana

    APID=3 BPID=2 N=1 ./U4SimtraceTest.sh ana       ## both together shows they are on top of each other, as expected 

    APID=3 BPID=2 AOFF=0,0,10 N=1 ./U4SimtraceTest.sh ana   ## use AOFF to offset A so can distinguish A and B  


Visualize A:"TO BT BT BT BT SR SA" (enter PMT reflect off inside of back hemi and get absorbed on red collar)::

    APID=5 N=1 ./U4SimtraceTest.sh ana
    APID=5 N=0 ./U4SimtraceTest.sh ana    # because of the vacuum fakes use the N=0 geometry 

    ## that should correspond to B:"TO BT BT SR SA"  

    APID=5 AOFF=0,0,10 BPID=13 N=0 ./U4SimtraceTest.sh ana    

    ## yep but  


    In [1]:  t.base,np.c_[qn,qi,qu][quo][:10]
    Out[1]: 
    ('/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1',
     array([[b'584', b'0', b'TO BT SA                                                                                        '],
            [b'295', b'2', b'TO BT BR BT SA                                                                                  '],
            [b'28', b'13', b'TO BT BT SR SA                                                                                  '],
            (only 28 vs 105 above, TODO: pump up the stats to 1M see if significant)

            [b'16', b'49', b'TO BT BT SR SR SR SA                                                                            '],
            [b'12', b'78', b'TO BT BT SR SR SR BT BT SA                                                                      '],
            [b'11', b'84', b'TO BT BT SR SR SR BR SR SR SR SA                                                                '],
            [b'9', b'125', b'TO BT AB                                                                                        '],
            [b'9', b'20', b'TO BT BT SR SR SR BR SR SA                                                                      '],
            [b'8', b'38', b'TO BT BT SA                                                                                     '],
            [b'5', b'75', b'TO BT BT SR SR SA                                                                               ']], dtype='|S96'))








