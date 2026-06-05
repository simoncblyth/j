gemini_opticks_build_suggestion.rst
========================================



compare versions on server and workstation
--------------------------------------------

::

    L[blyth@lxlogin001 ~]$ srun --partition=junogpu --qos=junoatmgpu --gres=gpu:pro6000:1 --cpus-per-task=16 --mem=64G --pty bash
    srun: job 3420397 queued and waiting for resources
    srun: job 3420397 has been allocated resources


    L[blyth@junogpu001 ~]$ export PATH=/usr/local/cuda/bin:$PATH
    L[blyth@junogpu001 ~]$ export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH

    L[blyth@junogpu001 ~]$ nvcc --version
    nvcc: NVIDIA (R) Cuda compiler driver
    Copyright (c) 2005-2025 NVIDIA Corporation
    Built on Tue_Dec_16_07:23:41_PM_PST_2025
    Cuda compilation tools, release 13.1, V13.1.115
    Build cuda_13.1.r13.1/compiler.37061995_0


    L[blyth@junogpu001 ~]$ cat /etc/almalinux-release
    AlmaLinux release 9.7 (Moss Jungle Cat)


    L[blyth@junogpu001 ~]$ which gcc
    /usr/lib64/ccache/gcc

    L[blyth@junogpu001 ~]$ gcc --version
    gcc (GCC) 11.5.0 20240719 (Red Hat 11.5.0-11)
    Copyright (C) 2021 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    L[blyth@junogpu001 ~]$ echo $PATH | tr ":" "\n"
    /usr/share/Modules/bin
    /usr/lib64/ccache
    /usr/local/bin
    /usr/bin
    /usr/local/sbin
    /usr/sbin
    /cvmfs/common.ihep.ac.cn/software/cctools
    /opt/puppetlabs/bin
    L[blyth@junogpu001 ~]$ 



Same as system gcc on workstation::

    A[blyth@localhost j]$ which gcc
    /usr/bin/gcc
    A[blyth@localhost j]$ gcc --version
    gcc (GCC) 11.5.0 20240719 (Red Hat 11.5.0-5)
    Copyright (C) 2021 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Almalinux on workstation 9.6 vs 9.7 on server::

    A[blyth@localhost j]$ cat /etc/almalinux-release 
    AlmaLinux release 9.6 (Sage Margay)


CUDA 13.1 on server::

    L[blyth@junogpu001 oj]$ ls -alst /usr/local/
    total 12
    0 drwxr-xr-x.  3 root  root    78 May 22 16:29 bin
    0 drwxr-xr-x   3 root  root    21 May 13 10:13 lib
    4 drwxr-xr-x. 16 root  root  4096 Apr 20 10:07 ..
    4 drwxr-xr-x. 19 root  root  4096 Apr 20 10:07 .
    0 drwxr-xr-x   3 root  root    17 Apr 20 10:07 lib64
    0 drwxr-xr-x.  5 root  root    49 Apr 20 10:07 share
    0 lrwxrwxrwx   1 root  root    25 Apr 20 09:58 cuda-13 -> /etc/alternatives/cuda-13
    4 drwxr-xr-x  14 root  root  4096 Apr 20 09:58 cuda-13.1
    0 lrwxrwxrwx   1 root  root    22 Apr 17 17:57 cuda -> /etc/alternatives/cuda
    0 lrwxrwxrwx   1 root  root    25 Apr 17 17:57 cuda-12 -> /etc/alternatives/cuda-12
    0 drwxr-xr-x  15 root  root   336 Apr 17 17:57 cuda-12.9
    0 drwxr-xr-x   3 root  root    20 Apr 17 17:53 cuda-12.7
    0 drwxr-xr-x   3 root  root    17 Apr 17 17:45 cuda-12.0
    0 drwxr-xr-x   4 root  root    29 Apr 17 17:07 cuda-12.4
    0 drwxr-xr-x   3 root  root    17 Apr 17 17:07 cuda-11.8
    0 drwxr-xr-x   2 slurm slurm   41 Apr 16 10:34 slurm
    0 drwxr-xr-x   2 root  root     6 Oct  3  2024 etc
    0 drwxr-xr-x   2 root  root     6 Oct  3  2024 games
    0 drwxr-xr-x   2 root  root     6 Oct  3  2024 include
    0 drwxr-xr-x.  3 root  root    19 Oct  3  2024 libexec
    0 drwxr-xr-x.  2 root  root    35 Oct  3  2024 sbin
    0 drwxr-xr-x   2 root  root     6 Oct  3  2024 src





cvmfs installation targetting CUDA 13.1 ?
--------------------------------------------

For Opticks releases I commonly build on workstation and install to
/cvmfs/opticks.ihep.ac.cn  for general usage.  Would installing a CUDA 13
version on the Workstation allow me to build there ?


Current Workstation driver version tops out at 13.0 - not new enough for CUDA 13.1::

    A[blyth@localhost ~]$ /usr/local/cuda/bin/nvcc --version
    nvcc: NVIDIA (R) Cuda compiler driver
    Copyright (c) 2005-2024 NVIDIA Corporation
    Built on Thu_Mar_28_02:18:24_PDT_2024
    Cuda compilation tools, release 12.4, V12.4.131
    Build cuda_12.4.r12.4/compiler.34097967_0
    A[blyth@localhost ~]$ 

    A[blyth@localhost ~]$ nvidia-smi
    Mon Jun  1 16:53:49 2026       
    +-----------------------------------------------------------------------------------------+
    | NVIDIA-SMI 580.82.07              Driver Version: 580.82.07      CUDA Version: 13.0     |
    +-----------------------------------------+------------------------+----------------------+
    | GPU  Name                 Persistence-M | Bus-Id          Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |
    |                                         |                        |               MIG M. |
    |=========================================+========================+======================|
    |   0  NVIDIA RTX 5000 Ada Gene...    Off |   00000000:AC:00.0 Off |                  Off |
    | 30%   41C    P8             16W /  250W |     793MiB /  32760MiB |      0%      Default |
    |                                         |                        |                  N/A |
    +-----------------------------------------+------------------------+----------------------+

    +-----------------------------------------------------------------------------------------+
    | Processes:                                                                              |
    |  GPU   GI   CI              PID   Type   Process name                        GPU Memory |
    |        ID   ID                                                               Usage      |
    |=========================================================================================|
    |    0   N/A  N/A            4226      G   /usr/bin/gnome-shell                    294MiB |
    |    0   N/A  N/A           18279      G   /usr/bin/Xwayland                        11MiB |
    |    0   N/A  N/A         2168065      G   ...ersion=20260126-170117.420000         94MiB |
    |    0   N/A  N/A         3401174      G   /usr/lib64/firefox/firefox              270MiB |
    +-----------------------------------------------------------------------------------------+
    A[blyth@localhost ~]$ 




Want single Opticks release that works on all relevant GPUs and CUDA versions
-------------------------------------------------------------------------------

Using CVMFS changes things completely. Since your goal is to maintain a single,
centrally deployed Opticks installation that works cleanly across both your
local workstation and the new junogpu cluster nodes, cross-compiling from
your workstation is highly efficient.

Yes, **installing CUDA 13.1 on your workstation will absolutely allow you to
build there**, with two crucial caveats you need to watch out for to ensure
binary compatibility.

---

### 1. Match the Exact Minor Version (CUDA 13.1)

Your workstation's local NVIDIA driver currently supports up to **CUDA 13.0**.
The cluster compute node is running **CUDA 13.1**.

If you install the **CUDA 13.1 Toolkit** on your workstation, you can use it to
compile your binaries for CVMFS. Because OptiX and CUDA inline a lot of code,
the generated binary will target 13.1 features.

* **On the Cluster:** It will run flawlessly because the cluster has the 13.1
toolkit runtime and a 13.2-capable driver.

* **On your Workstation:** You *might* be able to build it, but you won't be
able to local-test run it unless you also update your workstation's NVIDIA
driver (`580.82.07`) to a newer version that supports CUDA 13.1+ API execution.


> **Recommendation:** Update your workstation's host driver first, then install
the exact **CUDA 13.1 Toolkit** to perfectly match the cluster node.

---

### 2. Handle GPU Architecture Differences (`sm_90` vs `sm_89`)

This is the hidden trap for Opticks/OptiX. Your workstation and the cluster use
different hardware architectures:

* **Workstation:** RTX 5000 Ada Generation (**Ada Lovelace** architecture
$\rightarrow$ Compute Capability **`sm_89`**)

* **Cluster Node:** RTX Pro 6000 Blackwell (**Blackwell** architecture
$\rightarrow$ Compute Capability **`sm_90`** or **`sm_100`** depending on the
specific chip variant).

SCB : THIS IS WRONG LATER DETERMINE IT IS sm_120 OR aka compute capability 12.0


If your CMake setup for Opticks is configured to automatically detect the local
GPU architecture during compilation (e.g., using `native`), it will build an
optimized binary *only* for `sm_89`. When you attempt to run that CVMFS build
on the cluster, it will either fail or run sub-optimally.

#### The Fix: Force Fatbinary Compilation

When configuring the Opticks CMake build on your workstation, you must
explicitly tell `nvcc` to compile for both architectures. Look for the CMake
flags specifying CUDA architectures (often `CMAKE_CUDA_ARCHITECTURES`) and
specify both:

```bash
-DCMAKE_CUDA_ARCHITECTURES="89;90"

```

This instructs the compiler to generate a "fatbinary" containing embedded code
images for both Ada Lovelace and Blackwell. When the executable loads from
CVMFS, the NVIDIA driver will automatically select the correct code segment
matching the host machine's physical GPU.




PyTorch has easy way to check CC, but not installed::


    L[blyth@junogpu001 oj]$ python3 -c "import torch; print(torch.cuda.get_device_capability(0))"
    Traceback (most recent call last):
      File "<string>", line 1, in <module>
    ModuleNotFoundError: No module named 'torch'
    L[blyth@junogpu001 oj]$ 





Updating Workstation to CUDA 13.1 and corresponding NVIDIA Driver : USE OFFICIAL NVIDIA RHEL9 DNF REPO
--------------------------------------------------------------------------------------------------------


For the Workstation update of the NVIDIA Driver for CUDA 13.1 are there any
Linux kernel version compatibility issues ?::

    A[blyth@localhost ~]$ cat /etc/almalinux-release 
    AlmaLinux release 9.6 (Sage Margay)
    A[blyth@localhost ~]$ 
    A[blyth@localhost ~]$ uname -a
    Linux localhost.localdomain 5.14.0-570.37.1.el9_6.x86_64 #1 SMP PREEMPT_DYNAMIC Tue Aug 26 10:33:12 EDT 2025 x86_64 x86_64 x86_64 GNU/Linux
    A[blyth@localhost ~]$ 




Generally speaking, **no, you should not encounter any fundamental kernel
compatibility issues** when updating to the newer NVIDIA drivers (like the
595.x series you saw on the cluster) on your workstation.

Because you are running **AlmaLinux 9.6**, you are firmly within the Red Hat
Enterprise Linux (RHEL) 9 ecosystem. NVIDIA treats the RHEL/Enterprise Linux
platform as a first-class citizen, and they explicitly engineer their
proprietary driver to maintain strict compatibility with the RHEL 9 kernel
branch (`5.14.0-*`).

However, because Enterprise Linux distributions heavily backport features into
older kernel version strings (like `5.14.0`), there are two highly specific
workflow gotchas you must navigate when upgrading to support CUDA 13.1 on
AlmaLinux 9.6.

---

### 1. Use the Pre-compiled DKMS or KMOD Drivers (Crucial)

Do **not** download the raw `.run` installer file directly from NVIDIA's
website to do this upgrade. The raw installer compiles the kernel module
against your current header files on the fly, which can break when AlmaLinux
pushes a minor kernel update.

Instead, leverage the official NVIDIA CUDA RHEL9 repository. This repository
provides pre-compiled kernel modules (`kmod-nvidia`) or dynamic kernel module
support (`dkms-nvidia`) tailored specifically for the Enterprise Linux 9.6
kernel branch.

You can set it up on your workstation like this:

```bash
sudo dnf config-manager --add-repo https://developer.download.nvidia.com/compute/cuda/repos/rhel9/x86_64/cuda-rhel9.repo
sudo dnf clean all
sudo dnf install nvidia-driver-latest-dkms # Automatically rebuilds on kernel updates

```

---

### 2. The Modern RHEL 9 `gcc` Trap

When `dkms` or the NVIDIA installer attempts to glue the new driver module to
your `5.14.0-570` kernel, it checks the version of the System Compiler (`gcc`).

* **The Rule:** The `gcc` version used to compile the driver module *must*
match the exact major version of `gcc` that Red Hat/AlmaLinux used to compile
your running kernel.

* **The Context:** AlmaLinux 9.6 defaults to **GCC 11.5**.

* **The Action:** Ensure your system has the development tools properly aligned
before running the upgrade:

```bash
sudo dnf groupinstall "Development Tools"
sudo dnf install kernel-devel-$(uname -r) kernel-headers-$(uname -r)

```


If `kernel-devel` does not match your exact running kernel version
(`5.14.0-570.37.1.el9_6.x86_64`), the module compilation will fail. If you run
into a mismatch, simply update your whole system via `sudo dnf update` and
reboot into the latest kernel before installing the driver.


### Summary

Your AlmaLinux 9.6 platform is completely capable of handling the 595+ driver
series needed for CUDA 13.1/13.2. As long as you install the matching
`kernel-devel` headers and stick to the managed package manager repositories,
the transition should be smooth!




nvidia-driver:latest-dkms OR open-dkms ?  GOING WITH open-dkms - WHICH ARE ON ALREADY
---------------------------------------------------------------------------------------


::

   sudo dnf module enable nvidia-driver:latest-dkms -y



What are implications of open-dkms vs latest-dkms ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

    A[blyth@localhost ~]$ sudo dnf module enable nvidia-driver:latest-dkms -y
    Last metadata expiration check: 0:01:32 ago on Mon 01 Jun 2026 05:47:03 PM CST.
    Dependencies resolved.
    The operation would result in switching of module 'nvidia-driver' stream 'open-dkms' to stream 'latest-dkms'
    Error: It is not possible to switch enabled streams of a module unless explicitly enabled via configuration option module_stream_switch.
    It is recommended to rather remove all installed content from the module, and reset the module using 'dnf module reset <module_name>' command. After you reset the module, you can install the other stream.
    A[blyth@localhost ~]$ 



The choice between **`open-dkms`** and **`latest-dkms`** comes down to whether
you are using NVIDIA's newer **open-source kernel modules** or their
traditional **proprietary (closed-source) kernel modules**.

NVIDIA has transitioned their default stream to the open-source flavor for
modern GPUs. Since your workstation has an **RTX 5000 Ada** and the cluster has
an **RTX Pro 6000 Blackwell**, both of your systems fall squarely into the
architecture bracket (Turing and newer) where the open-source driver is fully
supported and recommended.

Here are the practical implications of both, followed by how to fix your DNF error.

---

### Key Differences & Implications

| Feature | `open-dkms` (Open-Source) | `latest-dkms` (Proprietary) |
| --- | --- | --- |
| **Source Code** | Open-source kernel space components (GPL compliant). User-space (CUDA, OpenGL) remains closed. | Completely closed-source binary blob. |
| **Linux Integration** | Much tighter integration with modern kernels. Tends to handle kernel security patches better. | Can occasionally lag behind bleeding-edge kernel updates. |
| **GPU Architecture** | **Only supports Turing (RTX 2000) and newer.** Legacy GPUs (Pascal/GTX 1000 and older) will not work. | Supports all architectures, including older legacy enterprise GPUs. |
| **Performance** | Equivalent for compute (CUDA) and heavy workloads like Opticks/OptiX. | Identical performance. |

#### Which one should you choose?

Because both your local Ada GPU and the cluster's Blackwell GPU are modern
architectures, **`open-dkms` is perfectly fine and arguably better for your
AlmaLinux system.** You do not actually need to switch to `latest-dkms` to get
CUDA 13.1 capability.

---

### How to Resolve Your DNF Error

AlmaLinux is protecting you from accidentally breaking your current driver by
blocking an on-the-fly stream switch. You have two paths forward:

#### Path A: Stick with `open-dkms` (Recommended & Easiest)

Since `open-dkms` supports CUDA 13.1 perfectly on your hardware, you don't
actually need to change streams. Simply skip the stream switch and directly
install the packages. DNF will use your existing `open-dkms` stream to pull the
matching driver.

```bash
sudo dnf install nvidia-driver-cuda cuda-toolkit-13-1 -y

```

*(Note: In the open stream, `nvidia-driver-cuda` or just letting `cuda-toolkit` pull the driver dependency is the standard convention).*

#### Path B: Force the switch to `latest-dkms` (Proprietary)

If you specifically want the traditional proprietary driver to match a specific
corporate or cluster policy, you must safely reset the module tracking as the
error message suggested:

```bash
# 1. Reset the module stream tracking
sudo dnf module reset nvidia-driver -y

# 2. Enable the proprietary stream
sudo dnf module enable nvidia-driver:latest-dkms -y

# 3. Proceed with your original installation command
sudo dnf install nvidia-driver-latest-dkms cuda-toolkit-13-1 -y

```

Either path will get you to your goal of compiling Opticks against CUDA 13.1!





Toolkit install::

    sudo dnf install nvidia-driver-cuda cuda-toolkit-13-1 -y




Which OptiX version is appropriate together with CUDA 13.1
------------------------------------------------------------


NVIDIA OptiX 9.0 or OptiX 9.1 are the most appropriate versions to use together
with CUDA 13.1. [1, 2] 

Because OptiX is a header-only API backed by user-mode driver runtimes
(nvoptix), compatibility is mostly driven by your NVIDIA display driver.
However, matching the OptiX SDK version to your CUDA Toolkit generation ensures
full support for newer language features, GPU architectures, and pipeline
tools. [2, 3, 4, 5] 

## Version Compatibility Breakdown

| OptiX SDK Version [1, 2, 3, 6, 7, 8, 9, 10] | Minimum Required CUDA | Recommended / Target CUDA | Matching Hardware Generation |
|---|---|---|---|
| OptiX 9.1 | CUDA 11.8+ | CUDA 13.1 / 13.2 | Blackwell (RTX 50-Series), Ada Lovelace, Ampere |
| OptiX 9.0 | CUDA 11.8+ | CUDA 13.0 / 13.1 | Blackwell (RTX 50-Series), Ada Lovelace, Ampere |
| OptiX 8.1 | CUDA 11.0+ | CUDA 12.x | Ada Lovelace (RTX 40-Series), Ampere |
| OptiX 8.0 | CUDA 11.0+ | CUDA 12.0 | Ada Lovelace, Ampere |

## Why OptiX 9.x Pairs Best with CUDA 13.1

* Cooperative Vectors Support: OptiX 9 introduces an API to execute tiny AI
networks directly within ray-tracing shaders using Tensor Cores. This feature
depends heavily on modern cooperative matrix instructions exposed in the CUDA
13.x compilation toolchain. [2, 3, 11, 12, 13] 

* PTX ISA Target Compatibility: Shaders in OptiX are compiled into PTX
intermediate code. OptiX 9.x natively understands the newer PTX ISA versions
generated by the CUDA 13.1 compiler (nvcc), avoiding compilation bottlenecks or
translation failures. [14] 

* Driver Alignment: OptiX 9.1 requires an R590 or newer display driver. These
driver branches are paired directly with the CUDA 13.x ecosystem to fully
unlock Blackwell and Ada Lovelace hardware features. [2, 3, 11] 


## Important Implementation Caveat

If your project uses legacy texture or surface memory mapping, remember that
the [CUDA 13.1 Programming
Guide](https://forums.developer.nvidia.com/t/using-cuda-texture-apis-with-optix-and-the-legacy-cuda-programming-guide/354581)
officially deprecates the use of traditional texture APIs. For texture mapping
inside your OptiX 9.x programs, it is recommended to use CUDA Texture Objects
via the cudaTextureObject_t handles or integrate the DemandLoading library from
the [NVIDIA OptiX Toolkit](https://github.com/NVIDIA/optix-subd). [2, 15] 

If you're upgrading an existing codebase, let me know:

* Are you migrating your project from an older OptiX version (like 7.x or 8.x)?
* Do you need help verifying your CMake configuration to correctly link the CUDA 13.1 and OptiX paths?

[10] 

[1] [https://github.com](https://github.com/NVIDIA/optix-dev/releases)
[2] [https://github.com](https://github.com/NVIDIA/optix-toolkit/releases)
[3] [https://forums.developer.nvidia.com](https://forums.developer.nvidia.com/t/optix-9-0-release/322842)
[4] [https://developer.download.nvidia.com](https://developer.download.nvidia.com/compute/cuda/repos/debian13/x86_64/Packages)
[5] [https://forums.developer.nvidia.com](https://forums.developer.nvidia.com/t/maximizing-gpu-utilization/259989)
[6] [https://en.wikipedia.org](https://en.wikipedia.org/wiki/OptiX)
[7] [https://help.altair.com](https://help.altair.com/feko/topics/feko/release_notes/2025_1/release_notes_intro_feko_winprop_r.htm)
[8] [https://github.com](https://github.com/NVIDIA/optix-dev/releases)
[9] [https://github.com](https://github.com/NVIDIA/optix-subd)
[10] [https://devtalk.blender.org](https://devtalk.blender.org/t/optix-says-my-gpu-driver-is-too-old-it-aint/44196)
[11] [https://github.com](https://github.com/NVIDIA/optix-sdk/releases)
[12] [https://developer.nvidia.com](https://developer.nvidia.com/blog/neural-rendering-in-nvidia-optix-using-cooperative-vectors/)
[13] [https://videocardz.com](https://videocardz.com/newz/nvidia-optix-9-1-0-released-r590-driver-required-optix-6-no-longer-supported)
[14] [https://developer.nvidia.com](https://developer.nvidia.com/downloads/optix/downloads/7.3.0/releasenotes)
[15] [https://forums.developer.nvidia.com](https://forums.developer.nvidia.com/t/using-cuda-texture-apis-with-optix-and-the-legacy-cuda-programming-guide/354581)





NVIDIA released OptiX 9.1 in December 2025, with the official SDK and source
code officially published to developers on December 10–12, 2025.This major SDK
update introduced new features like customizable compile caching, mid-module
creation cancellation, and required the R590 driver or newer.Would you like to
know more about the new features included in OptiX 9.1 (such as ARM platform
support or Shader Execution Reordering), or do you need help checking your
current driver requirements?






From OptiX 9.1 release notes::

    Version 9.1.0 October 2025
    Welcome to the 9.1.0 release of the NVIDIA OptiX SDK. Highlights of this release include:
    ● Module creation can now be cancelled midway
    ● New API enables customizable application-side compile caching
    ● Warning, support for OptiX 6 based applications has been removed from the driver
    Upgrading to OptiX 9.1.0 may require source code changes, though they should be minimal.
    Applications compiled with the 9.1.0 SDK headers will require driver version 590 or later. Applications
    compiled with earlier SDK headers will continue to work, but recompiling with 9.1.0 will expose new
    features and may also improve performance.
    System Requirements (for running binaries referencing NVIDIA OptiX)
    Hardware:
    ● All NVIDIA GPUs of Compute Capability 7.5 (Turing) or higher are supported. Support for Maxwell,
    Pascal, and Volta GPUs has been removed from R590+ drivers, and CUDA Toolkit 13.
    Software:
    ● NVIDIA OptiX 9.1.0 requires that you install an R590+ driver
    ● Windows 10/11 64-bit; Linux RHEL 4.8+ or Ubuntu 10.10+ 64-bit
    ● It is not required to have any CUDA toolkit installed to run NVIDIA OptiX-based applications
    Development Environment Requirements (for compiling with NVIDIA OptiX)
    ● CUDA Toolkit 12+
    This release has been tested with OptiX IR and PTX generated from CUDA Toolkit 12.0 and 12.9. Other
    toolkit versions should also work, but 12.9 is recommended.
    ● C/C++ Compiler
    A compiler compatible with the used CUDA Toolkit is required. Please see the CUDA Toolkit
    documentation for more information on supported compilers


From OptiX 9.0 release notes::

    Version 9.0.0 January 2025
    Welcome to the 9.0.0 release of the NVIDIA OptiX SDK. This release includes support for Blackwell, the
    newest generation of NVIDIA GPUs. Support for three major new features has been added:
    ● Clusters - API for dramatically accelerating BVH builds of massive dynamic triangle meshes
    ● Cooperative Vectors - API for executing small AI networks within OptiX shader programs,
    accelerated by NVIDIA Tensor Cores
    ● Hardware-accelerated linear curves on Blackwell GPUs, plus a new, faster software curve
    intersector called Rocaps.
    Upgrading to OptiX 9.0.0 may require source code changes, though they should be minimal.
    Applications compiled with the 9.0.0 SDK headers will require driver version 570 or later. Applications
    compiled with earlier SDK headers will continue to work, but recompiling with 9.0.0 will expose new
    features and may also improve performance.
    System Requirements (for running binaries referencing NVIDIA OptiX)
    Graphics Hardware:
    ● All NVIDIA GPUs of Compute Capability 5.0 (Maxwell) or higher are supported
    Graphics Driver:
    ● NVIDIA OptiX 9.0.0 requires that you install an R570+ driver
    ● Windows 8.1/10/11 64-bit; Linux RHEL 4.8+ or Ubuntu 10.10+ 64-bit
    CUDA Toolkit
    ● It is not required to have any CUDA toolkit installed to run NVIDIA OptiX-based applications
    Development Environment Requirements (for compiling with NVIDIA OptiX)
    ● CUDA Toolkit 12
    This release has been tested with OptiX IR and PTX generated from CUDA Toolkit 12.0, 12.7 and 12.8.
    Older toolkit versions should also work, but 12 is recommended.
    ● C/C++ Compiler
    A compiler compatible with the used CUDA Toolkit is required. Please see the CUDA Toolkit
    documentation for more information on supported compiler



Workstation Lookaround after update
------------------------------------


::

    A[blyth@localhost ~]$ nvidia-smi
    Tue Jun  2 10:23:27 2026       
    +-----------------------------------------------------------------------------------------+
    | NVIDIA-SMI 610.43.02              KMD Version: 610.43.02     CUDA UMD Version: 13.3     |
    +-----------------------------------------+------------------------+----------------------+
    | GPU  Name                 Persistence-M | Bus-Id          Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |
    |                                         |                        |               MIG M. |
    |=========================================+========================+======================|
    |   0  NVIDIA RTX 5000 Ada Gene...    Off |   00000000:AC:00.0  On |                  Off |
    | 30%   42C    P8              9W /  250W |     196MiB /  32760MiB |      4%      Default |
    |                                         |                        |                  N/A |
    +-----------------------------------------+------------------------+----------------------+

    +-----------------------------------------------------------------------------------------+
    | Processes:                                                                              |
    |  GPU   GI   CI              PID   Type   Process name                        GPU Memory |
    |        ID   ID                                                               Usage      |
    |=========================================================================================|
    |    0   N/A  N/A            3994      G   /usr/bin/gnome-shell                    168MiB |
    +-----------------------------------------------------------------------------------------+



::

    A[blyth@localhost ~]$ /usr/local/cuda/bin/nvcc --version
    nvcc: NVIDIA (R) Cuda compiler driver
    Copyright (c) 2005-2025 NVIDIA Corporation
    Built on Tue_Dec_16_07:23:41_PM_PST_2025
    Cuda compilation tools, release 13.1, V13.1.115
    Build cuda_13.1.r13.1/compiler.37061995_0
    A[blyth@localhost ~]$ 




