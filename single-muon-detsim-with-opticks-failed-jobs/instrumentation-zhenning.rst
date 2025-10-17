instrumentation-zhenning
=========================


+-----------------------+-----------------------------------+
|  stage                |  OJ extra                         |
+=======================+===================================+
|  initialization       | Opticks geometry conversion       |   
+-----------------------+-----------------------------------+
|  non-optical sim      | genstep collection                |
+-----------------------+-----------------------------------+
|  end of event         | 1. upload gensteps                | 
|                       | 2. kernel execution               |
|                       | 3. download hits                  |
|                       | 4. convert hits into G4 coll.     | 
+-----------------------+-----------------------------------+


To understand bottlenecks and plan where to optimize it would
be good to perform test simulations of the same events (single and double muons) 
in J and OJ runs in order to make an apple-to-apple comparison. 

For each event in the J and OJ runs, need:

* timings of the stages of the simulation 
* photon, genstep and hit counts



