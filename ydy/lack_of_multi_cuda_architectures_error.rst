lack_of_multi_cuda_architectures_error
========================================


Workstation A::

    A[blyth@localhost ~]$ nvidia-smi
    Fri Apr 18 20:20:07 2025       
    +-----------------------------------------------------------------------------------------+
    | NVIDIA-SMI 570.124.06             Driver Version: 570.124.06     CUDA Version: 12.8     |
    |-----------------------------------------+------------------------+----------------------+
    | GPU  Name                 Persistence-M | Bus-Id          Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |
    |                                         |                        |               MIG M. |
    |=========================================+========================+======================|
    |   0  NVIDIA RTX 5000 Ada Gene...    Off |   00000000:AC:00.0 Off |                  Off |
    | 30%   39C    P8             15W /  250W |     193MiB /  32760MiB |      0%      Default |
    |                                         |                        |                  N/A |
    +-----------------------------------------+------------------------+----------------------+
                                                                                             
    +-----------------------------------------------------------------------------------------+
    | Processes:                                                                              |
    |  GPU   GI   CI              PID   Type   Process name                        GPU Memory |
    |        ID   ID                                                               Usage      |
    |=========================================================================================|
    |    0   N/A  N/A            3562      G   /usr/bin/gnome-shell                    141MiB |
    |    0   N/A  N/A            9079      G   /usr/bin/Xwayland                        17MiB |
    +-----------------------------------------------------------------------------------------+
    A[blyth@localhost ~]$ 


Cluster::

    0040 Fri Apr 18 19:28:07 2025
      41 +-----------------------------------------------------------------------------------------+
      42 | NVIDIA-SMI 555.42.06              Driver Version: 555.42.06      CUDA Version: 12.5     |
      43 |-----------------------------------------+------------------------+----------------------+
      44 | GPU  Name                 Persistence-M | Bus-Id          Disp.A | Volatile Uncorr. ECC |
      45 | Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |
      46 |                                         |                        |               MIG M. |
      47 |=========================================+========================+======================|
      48 |   0  Tesla V100-SXM2-32GB           On  |   00000000:1F:00.0 Off |                    0 |
      49 | N/A   37C    P0             67W /  300W |       1MiB /  32768MiB |      0%      Default |
      50 |                                         |                        |                  N/A |
      51 +-----------------------------------------+------------------------+----------------------+
      52 
      53 +-----------------------------------------------------------------------------------------+
      54 | Processes:                                                                              |
      55 |  GPU   GI   CI        PID   Type   Process name                              GPU Memory |
      56 |        ID   ID                                                               Usage      |
      57 |=========================================================================================|
      58 |  No running processes found                                                             |
      59 +-----------------------------------------------------------------------------------------+




OPTIX_ERROR_INVALID_INPUT from optixModuleCreate done by PIP.cc
-------------------------------------------------------------------


::

    4768 == ROOT IO Svc ==
    4769 == Buffer Memory Management ==
    4770 == Random Svc ==
    4771 == Root Writer ==
    4772  == PMTSimParamSvc ==
    4773 GENTOOL MODE:  gun
    4774 [(0, 0, 0)] None
    4775 3inch PMT type:  Tub3inchV3
    4776 WARNING: mac file run.mac does not exist.
    4777 Traceback (most recent call last):
    4778   File "/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.3.6/el9_amd64_gcc11/Wed/bin/tut_detsim.py", line 53, in <module>
    4779     juno_application.run()
    4780   File "/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.3.6/el9_amd64_gcc11/Wed/python/Tutorial/JUNOApplication.py", line 224, in run
    4781     self.toptask.run()
    4782 RuntimeError: OPTIX_ERROR_INVALID_INPUT: Optix call 'optixModuleCreate( Ctx::context, &module_compile_options, &pipeline_compile_options, ptx.c_str(), ptx.size(), log, &sizeof_log, &module )' failed: /home/blyth/opticks/CSGOptiX/PIP.cc:296)
    4783 Log:
    4784 
    4785 
    4786 junotoptask:detsimiotask.terminate  WARN: invalid state tranform ((StartUp)) => ((EndUp))
    4787 junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    4788 junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names:
    4789 junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries:
    4790 junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements:  *** Break *** segmentation violation



::

     395 CSGOptiX::CSGOptiX(const CSGFoundry* foundry_)
     396     :
     397     sglm(new SGLM),
     398     flight(SGeoConfig::FlightConfig()),
     399     foundry(foundry_),
     400     outdir(SEventConfig::OutFold()),
     401 #if OPTIX_VERSION < 70000
     402     ptxpath(spath::Resolve("$OPTICKS_PREFIX/ptx/CSGOptiX_generated_CSGOptiX6.cu.ptx")),
     403     geoptxpath(spath::Resolve("OPTICKS_PREFIX/ptx/CSGOptiX_generated_CSGOptiX6geo.cu.ptx")),
     404 #else
     405     ptxpath(spath::Resolve("$OPTICKS_PREFIX/ptx/CSGOptiX_generated_CSGOptiX7.cu.ptx")),
     406     geoptxpath(nullptr),
     407 #endif
     408     tmin_model(ssys::getenvfloat("TMIN",0.1)),    // CAUTION: tmin very different in rendering and simulation
     409     kernel_count(0),
     410     raygenmode(SEventConfig::RGMode()),
     411     params(InitParams(raygenmode,sglm)),



     476 void CSGOptiX::initPIP()
     477 {
     478     LOG(LEVEL) << "["  ;
     479 #if OPTIX_VERSION < 70000
     480 #else
     481     LOG(LEVEL)
     482         << " ptxpath " << ( ptxpath ? ptxpath : "-" )
     483         ;
     484 
     485     pip = new PIP(ptxpath, ctx->props ) ;
     486 #endif
     487     LOG(LEVEL) << "]" ;
     488 }




::

    U[blyth@lxlogin002 ydy]$ echo $OPTICKS_PREFIX
    /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.3.6

    U[blyth@lxlogin002 ydy]$ ls -alst $OPTICKS_PREFIX/ptx/CSGOptiX_generated_CSGOptiX7.cu.ptx
    2008 -rw-r--r-- 1 cvmfs cvmfs 2055724 Apr 16 20:04 /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.3.6/ptx/CSGOptiX_generated_CSGOptiX7.cu.ptx
    U[blyth@lxlogin002 ydy]$ 





    4780 2025-04-18 20:09:35.359 INFO  [3274591] [PIP::CreateModule@254]
    4781  ptx_path /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.3.6/ptx/CSGOptiX_generated_CSGOptiX7.cu.ptx
    4782  ptx.size 2055724
    4783  ptx_ok YES
    4784 


* https://forums.developer.nvidia.com/t/optix-error-optix-error-invalid-input/286602




