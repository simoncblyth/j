release_prep_detect_CUDA_available_and_VRAM
=============================================

::

    https://github.com/pytorch/pytorch/blob/main/torch/cuda/__init__.py


CUDA NVML
-----------

* https://developer.nvidia.com/management-library-nvml
* https://pypi.org/project/nvidia-ml-py/


pynvml
--------

::


    In [1]: import pynvml

    In [2]: pynvml.nvmlInit()

    In [3]: import pynvml as nv

    In [4]: nv.nvmlDeviceGetCount()
    Out[4]: 2

    In [5]: h0 = nv.nvmlDeviceGetHandleByIndex(0)

    In [6]: h0
    Out[6]: <pynvml.nvml.LP_struct_c_nvmlDevice_t at 0x7ff3cb0ec5f0>

    In [7]: nv.nvmlDeviceGetName(h0)
    Out[7]: 'NVIDIA TITAN RTX'

    In [8]: h1 = nv.nvmlDeviceGetHandleByIndex(1)

    In [9]: nv.nvmlDeviceGetName(h1)
    Out[9]: 'NVIDIA TITAN V'

    In [10]: i0 = nv.nvmlDeviceGetMemoryInfo(h0)

    In [11]: i1 = nv.nvmlDeviceGetMemoryInfo(h1)

    In [12]: i0
    Out[12]: <pynvml.nvml.c_nvmlMemory_t at 0x7ff3cb029170>

    In [13]: i0.total
    Out[13]: 25769803776

    In [14]: i0.free
    Out[14]: 25046941696

    In [15]: i0.used
    Out[15]: 722862080

    In [16]: i1.total
    Out[16]: 12884901888

    In [17]: i1.total/(1024*1024*1024)
    Out[17]: 12.0

    In [18]: i0.total/(1024*1024*1024)
    Out[18]: 24.0

    In [19]: 


::

    [blyth@localhost junosw]$ opticks-f nvml
    ./cudarap/CDevice.cu:Possibly NVML can provide a better solution, see nvml-
    ./sysrap/NVML_CHECK.h:        nvmlReturn_t result = call;                                            \
    ./sysrap/NVML_CHECK.h:               << nvmlErrorString( result )                                  \
    ./sysrap/NVML_CHECK.h:        nvmlReturn_t result = call;                                            \
    ./sysrap/NVML_CHECK.h:               << nvmlErrorString( result )                                  \
    ./sysrap/sdevice.h:Possibly NVML can provide a better solution, see nvml-
    ./sysrap/smonitor.cc:#include <nvml.h>
    ./sysrap/smonitor.cc:    NVML_CHECK( nvmlInit() );
    ./sysrap/smonitor.cc:    NVML_CHECK( nvmlDeviceGetCount(&device_count) ); 
    ./sysrap/smonitor.cc:        nvmlDevice_t device ; 
    ./sysrap/smonitor.cc:        NVML_CHECK( nvmlDeviceGetHandleByIndex_v2( index, &device )); 
    ./sysrap/smonitor.cc:        //NVML_CHECK( nvmlDeviceGetName(device, name, maxchar ) ); 
    ./sysrap/smonitor.cc:        nvmlMemory_t memory ; 
    ./sysrap/smonitor.cc:        NVML_CHECK( nvmlDeviceGetMemoryInfo(device, &memory ) ); 
    ./sysrap/smonitor.cc:        nvmlReturn_t rc = nvmlDeviceGetComputeRunningProcesses_v3(device, &proc_count, nullptr );
    ./sysrap/smonitor.cc:            nvmlProcessInfo_t* procs = new nvmlProcessInfo_t[proc_alloc] ; 
    ./sysrap/smonitor.cc:            NVML_CHECK( nvmlDeviceGetComputeRunningProcesses_v3(device, &proc_alloc, procs ) );
    ./sysrap/smonitor.cc:                const nvmlProcessInfo_t& proc = procs[p] ; 
    P[blyth@localhost opticks]$ 



env-;nvml-
--------------

* https://docs.nvidia.com/deploy/nvml-api/index.html


::

    P[blyth@localhost example]$ touch example.c
    P[blyth@localhost example]$ nvml-make
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/bin/gcc -I/usr/local/cuda-10.1/targets/x86_64-linux/include   -c -o example.o example.c
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/bin/gcc example.o -I/usr/local/cuda-10.1/targets/x86_64-linux/include -lnvidia-ml -L /lib64 -L ../lib/ -o example
    Found 2 devices

    Listing devices:
    0. NVIDIA TITAN RTX [00000000:73:00.0]
         Changing device's compute mode from 'Default' to 'Prohibited'
             Need root privileges to do that: Insufficient Permissions
    1. NVIDIA TITAN V [00000000:A6:00.0]
         Changing device's compute mode from 'Default' to 'Prohibited'
             Need root privileges to do that: Insufficient Permissions
    All done.
    Press ENTER to continue...




    P[blyth@localhost example]$ touch example.c
    P[blyth@localhost example]$ nvml-make
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/bin/gcc -I/usr/local/cuda-11.7/targets/x86_64-linux/include   -c -o example.o example.c
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/bin/gcc example.o -I/usr/local/cuda-11.7/targets/x86_64-linux/include -lnvidia-ml -L /lib64 -L ../lib/ -o example
    Found 2 devices

    Listing devices:
    0. NVIDIA TITAN RTX [00000000:73:00.0]
         Changing device's compute mode from 'Default' to 'Prohibited'
             Need root privileges to do that: Insufficient Permissions
    1. NVIDIA TITAN V [00000000:A6:00.0]
         Changing device's compute mode from 'Default' to 'Prohibited'
             Need root privileges to do that: Insufficient Permissions
    All done.
    Press ENTER to continue...

    P[blyth@localhost example]$ 




