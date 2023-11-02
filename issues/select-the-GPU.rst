select-the-GPU
================

Conclude
------------

To select the GPU need to use CUDA_VISIBLE_DEVICES 
and metadata recording is handled with sdevice.h scontext.h 

* scontext.h needs updating to handle updated sdevice.h and
  metadata from scontext needs to be included into the SEvt run metadata 

* running sysrap/tests/sdevice_test.sh without CUDA_VISIBLE_DEVICES
  defined persists info on all GPUs into ~/.opticks/runcache/sdevice.bin



ntds3 using GPU 1 : with only 12G VRAM
-----------------------------------------

That will probably run out of GPU memory with full recording enabled
Actually it succeeded with 1M input photons.::

    N[blyth@localhost ~]$ nvidia-smi
    Mon Oct 30 12:34:37 2023       
    +-----------------------------------------------------------------------------+
    | NVIDIA-SMI 435.21       Driver Version: 435.21       CUDA Version: 10.1     |
    |-------------------------------+----------------------+----------------------+
    | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
    |===============================+======================+======================|
    |   0  TITAN RTX           Off  | 00000000:73:00.0  On |                  N/A |
    | 40%   32C    P8    15W / 280W |    421MiB / 24219MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+
    |   1  TITAN V             Off  | 00000000:A6:00.0 Off |                  N/A |
    | 35%   51C    P8    29W / 250W |    545MiB / 12066MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+
                                                                                   
    +-----------------------------------------------------------------------------+
    | Processes:                                                       GPU Memory |
    |  GPU       PID   Type   Process name                             Usage      |
    |=============================================================================|
    |    0     20865      G   /usr/bin/X                                    24MiB |
    |    0     21503      G   /usr/bin/gnome-shell                         102MiB |
    |    0     22134      G   /usr/bin/X                                   122MiB |
    |    0     22918      G   /usr/bin/gnome-shell                         159MiB |
    |    1      9854      C   ...p/ExternalLibs/Python/3.8.12/bin/python   533MiB |
    +-----------------------------------------------------------------------------+
    N[blyth@localhost ~]$ 


Looks like currently using GPU 1 (TITAN V) with only 12G.  
How to switch to GPU 0 (TITAL RTX) with 24G ?

First access to GPU probably the uploads done in CSGOptiX::Create 



QSimTest.sh also using GPU 1 (as enumerated by nvidia-smi)
------------------------------------------------------------

::

    N[blyth@localhost ~]$ MODE=0 ~/opticks/qudarap/tests/QSimTest.sh run
    === ephoton.sh : TEST smear_normal_sigma_alpha : unset environment : will use C++ defaults in quad4::ephoton for p0
    2023-10-30 20:31:50.032 INFO  [60779] [QSimTest::EventConfig@595] [ smear_normal_sigma_alpha
    2023-10-30 20:31:50.032 INFO  [60779] [QSimTest::EventConfig@610] ] smear_normal_sigma_alpha
    2023-10-30 20:31:50.032 INFO  [60779] [QSimTest::main@630]  num 100000 type 32 subfold smear_normal_sigma_alpha ni_tranche_size 100000 print_id -1
    //QSim_quad_launch sim 0x7f61e7c27600 quad 0x7f61e7c27800 num_quad 100000 dbg 0x7f61e7c02a00 type 32 name smear_normal_sigma_alpha 
    2023-10-30 20:31:50.037 INFO  [60779] [QU::copy_device_to_host_and_free@415] copy 100000 sizeof(T) 16 label QSim::quad_launch_generate:num_quad
    2023-10-30 20:31:50.042 INFO  [60779] [main@732]  qst.rc 0
    N[blyth@localhost ~]$ 


The below uses GPU 0 (as enumerated by nvidia-smi)
-----------------------------------------------------------

::

    N[blyth@localhost ~]$ MODE=0 CUDA_VISIBLE_DEVICES=1 ~/opticks/qudarap/tests/QSimTest.sh run

    
HMM : is that captured in metadata ? 

* sysrap/tests/sdevice_test.sh




