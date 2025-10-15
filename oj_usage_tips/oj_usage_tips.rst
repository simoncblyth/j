oj_usage_tips
===============

* https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/ShowDocument?docid=14291
* https://juno.ihep.ac.cn/Dev_DocDB/0142/014291/001/opticks_20250727_kaiping.pdf

  Status of JUNOSW + Opticks : GPU ray trace accelerated optical photon simulation


Find an OJ release
--------------------

For reproducibility it is best to use a dated OJ release, not the daily
releases which may be from merge requests currently being tested.
As of today (Oct 15 2025) most recent dated release is *2025_09_30*::

    A[blyth@localhost 2025_09_30]$ cd /cvmfs/opticks.ihep.ac.cn/oj/releases
    A[blyth@localhost releases]$ find . -name LastRef -exec ls -l {} \;
    lrwxrwxrwx. 1 cvmfs cvmfs 10 Apr 14  2025 ./J25.3.0_Opticks-v0.3.5/el9_amd64_gcc11/LastRef -> 2025_04_14
    lrwxrwxrwx. 1 cvmfs cvmfs 10 Jun  3 17:05 ./J25.3.0_Opticks-v0.4.3/el9_amd64_gcc11/LastRef -> 2025_06_01
    lrwxrwxrwx. 1 cvmfs cvmfs 10 Jun 24 14:19 ./J25.4.0_Opticks-v0.4.6/el9_amd64_gcc11/LastRef -> 2025_06_24
    lrwxrwxrwx. 1 cvmfs cvmfs 10 Jun 25 16:37 ./J25.4.0_Opticks-v0.4.8/el9_amd64_gcc11/LastRef -> 2025_06_25
    lrwxrwxrwx. 1 cvmfs cvmfs 10 Jul  7 14:33 ./J25.4.0_Opticks-v0.5.0/el9_amd64_gcc11/LastRef -> 2025_07_07
    lrwxrwxrwx. 1 cvmfs cvmfs 10 Jul 17 16:32 ./J25.4.0_Opticks-v0.5.1/el9_amd64_gcc11/LastRef -> 2025_07_17
    lrwxrwxrwx. 1 cvmfs cvmfs 10 Sep 30 20:50 ./J25.4.0_Opticks-v0.5.4/el9_amd64_gcc11/LastRef -> 2025_09_30
    A[blyth@localhost releases]$

    A[blyth@localhost el9_amd64_gcc11]$ pwd
    /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.4/el9_amd64_gcc11
    A[blyth@localhost el9_amd64_gcc11]$ l
    total 7
    1 drwxrwxr-x. 10 cvmfs cvmfs  43 Oct 15 06:27 .
    1 lrwxrwxrwx.  1 cvmfs cvmfs   3 Oct 15 06:27 Latest -> Tue
    1 drwxr-xr-x.  7 cvmfs cvmfs 181 Oct 15 06:19 Tue
    1 drwxr-xr-x.  7 cvmfs cvmfs 181 Oct 14 01:35 Mon
    1 drwxr-xr-x.  7 cvmfs cvmfs 181 Oct 12 17:36 Sun
    1 drwxr-xr-x.  7 cvmfs cvmfs 181 Oct 11 17:34 Sat
    1 drwxr-xr-x.  7 cvmfs cvmfs 181 Oct 10 17:37 Fri
    1 drwxr-xr-x.  7 cvmfs cvmfs 181 Oct  9 23:25 Thu
    1 drwxr-xr-x.  7 cvmfs cvmfs 181 Oct  8 17:34 Wed
    1 lrwxrwxrwx.  1 cvmfs cvmfs  10 Sep 30 20:50 LastRef -> 2025_09_30
    1 drwxr-xr-x.  7 cvmfs cvmfs 181 Sep 30 17:36 2025_09_30
    1 -rw-r--r--.  1 cvmfs cvmfs   0 Sep 30 10:12 .cvmfscatalog
    1 drwxrwxr-x.  3 cvmfs cvmfs  37 Sep 30 10:12 ..
    A[blyth@localhost el9_amd64_gcc11]$

The commandline to setup the OJ environment is hence::

   source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.4/el9_amd64_gcc11/2025_09_30/envset.sh


SLURM OPTION : TO ENSURE SINGLE GPU
---------------------------------------

Normally exclusive GPU usage is required for sustained Opticks usage to prevent CUDA out-of-memory errors.
The below slurm option ensures exclusive access to a single GPU::

    --gpu-bind=single:1

Slurm probably implements this option by setting the CUDA_VISIBLE_DEVICES envvar
to control which GPUs each task can use.  Hence when using this option the manual
approach of setting the envvar should typically not be used.



Minimal script to start with
-----------------------------

::

    #!/bin/bash

    #SBATCH --partition=gpu
    #SBATCH --qos=normal
    #SBATCH --account=junogpu
    #SBATCH --job-name=muon_min
    #SBATCH --ntasks=1
    #SBATCH --mem-per-cpu=20480
    #SBATCH --gres=gpu:v100:1
    ##SBATCH --gpu-bind=single:1

    # for production usage will need --gpu-bind=single:1 not needed for small scale testing


    source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.4/el9_amd64_gcc11/2025_09_30/envset.sh


    logging(){
       type $FUNCNAME
       export G4CXOpticks=INFO
       export SSim=INFO
       export SEvt=INFO
       export SEventConfig=INFO
    }
    #logging  # add logging for debug of "SNiPER is stopped by Ctrl+C" ie SIGINT


    export SEvt__MINTIME=1    # dump kernel launch times

    export CUDA_VISIBLE_DEVICES=0
    ## CUDA_VISIBLE_DEVICES controls the GPU opticks will use
    ## its not appropriate to set this when using --gpu-bind=single:1

    export OPTICKS_MAX_BOUNCE=63
    #export OPTICKS_MAX_TIME=1000 # ns 


    ## detsim command line is up to you

    $(which python) \
         $(which tut_detsim.py) \
         --no-gdml \
         --pmtsd-merge-twindow 1.0 \
         --event-split \
         --output oj_edm.root \
         --user-output oj_user.root \
         --evtmax 10 \
         --seed 42 \
         hepevt \
         --exe Muon;

    exit 0 





