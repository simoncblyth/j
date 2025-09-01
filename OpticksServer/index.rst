j/OpticksServer
===================



Presentations with server ideas
---------------------------------

::

    zeta:presentation blyth$ grep server *.txt | grep -v dae

    gpu_optical_photon_simulation.txt:   :description: (2014 Apr) 200x Faster Optical Photon Propagation with NuWa + Chroma ? Intro Chroma, Tris, DAE Export, Chroma Fixes, UDP, server
    gpu_optical_photon_simulation.txt:   .. [#topology] Workaround for a network blockage, server/client or threaded also possible     

    optical_photon_simulation_with_nvidia_optix.txt:         * 7 classes : numpydelegate, udp_server, ... 
    optical_photon_simulation_with_nvidia_optix.txt:   https://bitbucket.org/simoncblyth/env/src/tip/boost/basio/numpyserver/

    opticks_20240606_ihep_panel_30min.txt:   * :r:`(*)` :b:`try server/client Opticks : for non-GPU nodes`
    opticks_20240606_ihep_panel_30min.txt:        |                     | 180k  | rack mount GPU server with 2 NVIDIA L20 RTX GPU (or similar) :b:`[CC managed]` |

    opticks_gpu_optical_photon_simulation_jul2018_ihep.txt:    * performance testing on GPU server, workstation
    opticks_gpu_optical_photon_simulation_jul2018_ihep.txt:      * need recent NVIDIA GPU workstation or server 
    opticks_gpu_optical_photon_simulation_jul2018_ihep.txt:         "salvage part" from *Tesla V100* server, same GV100

    opticks_jan2021_juno_sim_review.txt:        * :red:`np_server/np_client operational`  
    opticks_jan2021_juno_sim_review.txt:    **General compute server structure:**
    opticks_jan2021_juno_sim_review.txt:    * needs network/MQ/server/multi-threading experience~interest

    opticks_may2020_hsf.txt:        * Linux servers
    opticks_may2020_hsf.txt:   * RTX performance, RT cores ~not available in server GPUs[1,2] 


Compression of NumPy arrays
----------------------------

Sending compressed data over network might be beneficial.
Trade off between faster transfer for smaller data and
compress/decompress overhead.


C-Blosc2 library
~~~~~~~~~~~~~~~~~~

* https://www.blosc.org/c-blosc2/c-blosc2.html

