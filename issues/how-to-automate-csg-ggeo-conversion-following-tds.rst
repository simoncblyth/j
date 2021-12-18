how-to-automate-csg-ggeo-conversion-following-tds
=====================================================

After a tds run that changes geometry, eg a different skipsolidname option
need to update the CSG too.

* unclear how to automate that 
* or at least to provide some reassurance are converting the just updated geocache 

  


::

    N[blyth@localhost CSGOptiX]$ cg
    /data/blyth/junotop/opticks/CSG_GGeo
    N[blyth@localhost CSG_GGeo]$ ./run.sh 
    # mo .bashrc VIP_MODE:non N : plain environment for debug CMTEXTRATAGS:
    /data/blyth/junotop/ExternalLibs/opticks/head/lib/CSG_GGeoTest
    change directory to logdir /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/logs
    SPath::chdir /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/logs
    2021-12-18 04:13:53.521 ERROR [69560] [main@24] [ load ggeo from idpath /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    2021-12-18 04:13:54.376 INFO  [69560] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  1
    ...
    2021-12-18 04:13:54.855 INFO  [69560] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  3000
    2021-12-18 04:13:55.270 ERROR [69560] [main@26] ] load ggeo 
    2021-12-18 04:13:55.271 ERROR [69560] [main@32] [ convert ggeo 
    2021-12-18 04:13:55.271 INFO  [69560] [CSG_GGeo_Convert::convertGeometry@121] convert all solids (default)
    2021-12-18 04:13:55.271 ERROR [69560] [CSG_GGeo_Convert::convertAllSolid@135] proceeding with convert for repeatIdx 0
    2021-12-18 04:13:55.306 ERROR [69560] [CSG_GGeo_Convert::convertAllSolid@135] proceeding with convert for repeatIdx 1
    ...
    2021-12-18 04:13:55.317 ERROR [69560] [CSG_GGeo_Convert::convertAllSolid@135] proceeding with convert for repeatIdx 8
    2021-12-18 04:13:55.317 ERROR [69560] [CSG_GGeo_Convert::convertAllSolid@135] proceeding with convert for repeatIdx 9
    2021-12-18 04:13:55.349 ERROR [69560] [main@35] ] convert ggeo 
    2021-12-18 04:13:55.349 ERROR [69560] [main@54] [ write foundry to CFBASE /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo rel CSGFoundry
    2021-12-18 04:13:55.349 INFO  [69560] [CSGFoundry::write@1127] /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry
    NP::Write dtype <i4 ni       10 nj  3 nk  4 nl  -1 nm  -1 path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry/solid.npy
    NP::Write dtype <f4 ni     3237 nj  4 nk  4 nl  -1 nm  -1 path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry/prim.npy
    NP::Write dtype <f4 ni    17623 nj  4 nk  4 nl  -1 nm  -1 path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry/node.npy
    NP::Write dtype <f4 ni     8184 nj  4 nk  4 nl  -1 nm  -1 path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry/tran.npy
    NP::Write dtype <f4 ni     8184 nj  4 nk  4 nl  -1 nm  -1 path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry/itra.npy
    NP::Write dtype <f4 ni    48477 nj  4 nk  4 nl  -1 nm  -1 path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry/inst.npy
    NP::save_meta metapath [/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry/bnd_meta.txt]
    NP::save_meta metapath [/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry/icdf_meta.txt]
    2021-12-18 04:13:55.504 ERROR [69560] [main@56] ] write foundry 
    2021-12-18 04:13:55.504 ERROR [69560] [main@58] [ load foundry 
    2021-12-18 04:13:55.504 INFO  [69560] [CSGFoundry::load@1148] /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/CSGFoundry
    2021-12-18 04:13:55.504 INFO  [69560] [CSGFoundry::loadArray@1211]  ni    10 nj 3 nk 4 solid.npy
    2021-12-18 04:13:55.505 INFO  [69560] [CSGFoundry::loadArray@1211]  ni  3237 nj 4 nk 4 prim.npy
    2021-12-18 04:13:55.506 INFO  [69560] [CSGFoundry::loadArray@1211]  ni 17623 nj 4 nk 4 node.npy
    2021-12-18 04:13:55.507 INFO  [69560] [CSGFoundry::loadArray@1211]  ni  8184 nj 4 nk 4 tran.npy
    2021-12-18 04:13:55.508 INFO  [69560] [CSGFoundry::loadArray@1211]  ni  8184 nj 4 nk 4 itra.npy
    2021-12-18 04:13:55.510 INFO  [69560] [CSGFoundry::loadArray@1211]  ni 48477 nj 4 nk 4 inst.npy
    2021-12-18 04:13:55.518 ERROR [69560] [main@60] ] load foundry 
    2021-12-18 04:13:55.533 INFO  [69560] [main@64] CSGFoundry saved to cfbase /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo
    2021-12-18 04:13:55.533 INFO  [69560] [main@65] logs are written to logdir /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/CSG_GGeo/logs
    === ./run.sh : geocache_sh /home/blyth/.opticks/geocache/geocache.sh sourcing
    # Opticks::writeGeocacheScript
    # 20211215_043327
    export OPTICKS_KEY=DetSim0Svc.X4PhysicalVolume.pWorld.3dbec4dc3bdef47884fe48af781a179d



