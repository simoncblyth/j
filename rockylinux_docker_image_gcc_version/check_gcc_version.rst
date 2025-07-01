check_gcc_version
===================

Check gcc version by running the docker image simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9::

    A[blyth@localhost ~]$ docker images
    REPOSITORY                                     TAG                              IMAGE ID       CREATED         SIZE
    junosw/cuda                                    12.4.1-el9                       8c10f253f281   3 months ago    7.89GB
    simoncblyth/cuda                               12.4.1-runtimeplus-rockylinux9   8c10f253f281   3 months ago    7.89GB
    junosw/cuda                                    12.4.1-runtimeplus-rockylinux9   3d505c100ea8   3 months ago    7.89GB
    junosw/cuda                                    12.4.1-runtime-rockylinux9       3b3a3332ae87   3 months ago    5.81GB
    junosw/base                                    el9                              987e8bddae3e   3 months ago    2.51GB
    al9-cvmfs                                      latest                           ebccb0ed032b   3 months ago    451MB
    nvidia_cuda_12_4_1_runtime_rockylinux9_amd64   latest                           72c9d5a2da10   3 months ago    2.47GB
    bb42                                           latest                           c9d2aec48d25   9 months ago    4.27MB
    nvidia/cuda                                    12.4.1-devel-rockylinux9         ab9135746936   14 months ago   7.11GB
    <none>                                         <none>                           9cc24f05f309   19 months ago   176MB
    <none>                                         <none>                           0fed15e4f2a2   19 months ago   2.69GB

    A[blyth@localhost ~]$ docker images simoncblyth/cuda
    REPOSITORY         TAG                              IMAGE ID       CREATED        SIZE
    simoncblyth/cuda   12.4.1-runtimeplus-rockylinux9   8c10f253f281   3 months ago   7.89GB


    A[blyth@localhost ~]$ docker run -it simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9 /bin/bash

    ==========
    == CUDA ==
    ==========

    CUDA Version 12.4.1

    Container image Copyright (c) 2016-2023, NVIDIA CORPORATION & AFFILIATES. All rights reserved.

    This container image and its contents are governed by the NVIDIA Deep Learning Container License.
    By pulling and using the container, you accept the terms and conditions of this license:
    https://developer.nvidia.com/ngc/nvidia-deep-learning-container-license

    A copy of this license is made available in this container at /NGC-DL-CONTAINER-LICENSE for your convenience.

    WARNING: The NVIDIA Driver was not detected.  GPU functionality will not be available.
       Use the NVIDIA Container Toolkit to start this container with GPU support; see
       https://docs.nvidia.com/datacenter/cloud-native/ .

    [juno@70fc5a25f906 ~]$ which gcc
    /usr/bin/gcc

    [juno@70fc5a25f906 ~]$ gcc --version
    gcc (GCC) 11.5.0 20240719 (Red Hat 11.5.0-5)
    Copyright (C) 2021 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    [juno@70fc5a25f906 ~]$ 


