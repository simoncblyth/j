review_creation_of_simoncblyth_cuda_runtimeplus_docker_image
=============================================================


High Level what was required for a JUNOSW+Opticks docker image
---------------------------------------------------------------

Effectively merged:

1. JUNOSW Dockerfile
2. NVIDIA standard CUDA 12.4 rockylinux9 image

This yielded an image from which docker containers
can be intanciated om which JUNOSW+Opticks can be
built and run.


.gitlab-ci.yml
---------------- 

::

    .opticks_build_job_template:
      extends: .job_template
      stage: build
      image: simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9
      variables:
        JUNO_CLANG_PREFIX:
        JUNO_OPTICKS_PREFIX: /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
        EXTRA_BUILD_FLAGS: JUNO_CMAKE_BUILD_TYPE=Debug
      script:





My dockerhub images
---------------------

* https://hub.docker.com/search?q=simoncblyth
* https://hub.docker.com/r/simoncblyth/cuda
* https://hub.docker.com/layers/simoncblyth/cuda/12.4.1-runtimeplus-rockylinux9/images/sha256-f3209ee05a2e128302f039bcbb4189a1fcc8bfc94d24763b40d39260756fa59a


nvidia/cuda images
---------------------

* https://hub.docker.com/r/nvidia/cuda

::

     12.4.1-runtime-rockylinux9   linux/amd64   1.42 GB
     12.4.1-devel-rockylinux9     linux/amd64   3.7 GB


check nvidia/cuda tags
-------------------------

::

    HTTPS_PROXY="socks5h://127.0.0.1:8080" skopeo list-tags docker://docker.io/nvidia/cuda

    HTTPS_PROXY="socks5h://127.0.0.1:8080" skopeo list-tags docker://docker.io/nvidia/cuda > /tmp/nvidia_cuda_docker_tags.json


    A[blyth@localhost ~]$ grep rockylinux9 /tmp/nvidia_cuda_docker_tags.json | grep 13.1
            "13.1.0-base-rockylinux9",
            "13.1.0-devel-rockylinux9",
            "13.1.0-runtime-rockylinux9",

            "13.1.1-base-rockylinux9",
            "13.1.1-cudnn-devel-rockylinux9",
            "13.1.1-cudnn-runtime-rockylinux9",
            "13.1.1-devel-rockylinux9",
            "13.1.1-runtime-rockylinux9",

            "13.1.2-base-rockylinux9",
            "13.1.2-cudnn-devel-rockylinux9",
            "13.1.2-cudnn-runtime-rockylinux9",
            "13.1.2-devel-rockylinux9",
            "13.1.2-runtime-rockylinux9",




GHA workaround docker failing to connect to dockerhub
----------------------------------------------------------

Recall at the time docker failed to work using CNAF ssh proxy 
(I assumed at time due to resource quotas on the CNAF gateway machine)
so I used a workaround of using "GHA" github-ci actions (NOT gitlab)
of my "sandbox" repo. That worked because it runs in the US.

So the devlopment was mostly done by changing yml files
and looking at github CI pipeline outputs.  

Recall there was a 10GB(?) quota that was problematic to stay within, 
so this approach should only be used if more normal ones do not work.

::

    A[blyth@localhost sandbox]$ git remote -v
    origin	git@github.com:simoncblyth/sandbox.git (fetch)
    origin	git@github.com:simoncblyth/sandbox.git (push)


    [lo] A[blyth@localhost sandbox]$ find . -name ".git" -prune -o -print
    .
    ./.github
    ./.github/workflows
    ./.github/workflows/learn-github-actions.yml
    ./.github/workflows/try-docker-build.yml
    ./.github/workflows/try-docker-container.yml
    ./.github/workflows/try-docker-pull.yml
    ./.github/workflows/try-docker-run-action.yml
    ./.github/workflows/try-vm-container.yml
    ./.github/workflows/build-docker-image-and-scp.yml
    ./.github/workflows/cvmfs-build-docker-image-and-scp.yml
    ./.github/workflows/nv-build-docker-image-and-scp.yml
    ./.github/workflows/pull-docker-image-and-inspect-and-scp.yml
    ./.github/workflows/pull-docker-image-and-inspect.yml
    ./.github/workflows/pull-docker-image-and-scp-2.yml
    ./.github/workflows/pull-docker-image-and-scp.yml
    ./.github/workflows/try-ssh-commands.yml
    ./.github/workflows/junosw-build-docker-image-and-scp.yml
    ./.github/workflows/simoncblyth-build-docker-image-and-push.yml
    ./.github/workflows/simoncblyth-pull-docker-image-and-scp.yml
    ./bb
    ./bb/Dockerfile
    ./cvmfs
    ./cvmfs/Dockerfile
    ./nv
    ./nv/Dockerfile
    ./junosw
    ./junosw/Dockerfile-junosw-cuda-runtimeplus-el9-check
    ./junosw/Dockerfile-junosw-cuda-runtime-el9
    ./junosw/Dockerfile-junosw-cuda-runtime-el9-check
    ./junosw/Dockerfile-junosw-cuda-runtimeplus-el9
    ./junosw/Dockerfile-junosw-base-el9
    ./docker-mock-gitlab-ci.sh
    [lo] A[blyth@localhost sandbox]$ 




    A[blyth@localhost sandbox]$ git lg -n100
    * 2025-03-24 90f35be - (HEAD -> master, origin/master, origin/HEAD) GHA if not working as expected (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-15 5921a73 - simoncblyth-pull-docker-image-and-scp.yml check TAR (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-15 01b4c66 - try with SRC label to Dockerfile with image label (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-15 25c2213 - try in steps.env (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-15 ff47883 - fix var (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-15 e1e35ff - check URL formation within GHA (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-15 6b1f3ca - try push (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-15 6bb90b6 - try docker/login-action@v3 (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-15 196a257 - change rl9 to el9 following RHEL standard (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 d4ba788 - rewrite Dockerfile more like base : perhaps more space efficient (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 420ba38 - remove the df, perhaps cause of wierd fail (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 6e6b648 - try to stay within quota (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 22374b5 - rejig docker build command and Dockerfile naming for sustainability, try runtimeplus picking only a little from devel (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 dbdce00 - split dnf install into single pkg lines and comment redhat-lsb-core (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 b010738 - split the dnf install into multiple lines to isolate issues (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 d195132 - try rocky-repos (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 31e3a0a - skip almalinux-release-devel (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 caf3f9c - try cuda_runtime recipe withing GHA (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-12 64398a0 - note on deprecation of gitlab-runner exec (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-11 a6f8065 - try building the junosw/base:el9 Dockerfile (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-11 2bee519 - pull-docker-image-and-inspect-and-scp (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-11 84e529c - pull j image (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-10 645b234 - uncomment the scp (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-10 668c870 - try cvmfs config within Dockerfile (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-10 461e914 - scp over the runtime for check (1 year, 3 months ago) <Simon C Blyth>
    * 2025-03-10 51a6419 - try build-arg ARG with runtime (1 year, 3 months ago) <Simon C Blyth>
    ....
    * 2025-03-07 38bdede - follow along tutorial on github actions (1 year, 3 months ago) <Simon C Blyth>




Review the Dockerfile
----------------------

Dockerfile-junosw-base-el9
    "FROM almalinux:9" with dnf setup of base externals for JUNOSW and cvmfs setup

Dockerfile-junosw-cuda-runtime-el9
    Very similar to above "Dockerfile-junosw-base-el9" but "FROM nvidia/cuda:12.4.1-runtime-rockylinux9" 
    with small changes for differences between almalinux:9 and rockylinux9

Dockerfile-junosw-cuda-runtime-el9-check
    As above but with dnf install lines split to allow identification of problems 

Dockerfile-junosw-cuda-runtimeplus-el9
    Documented Dockerfile inbetween the NVIDIA standard "runtime" and "devel" 
    together with the JUNOSW dnf setup basis packages and cvmfs config.

Dockerfile-junosw-cuda-runtimeplus-el9-check
    As above but with dnf install lines split to allow identification of problems 



