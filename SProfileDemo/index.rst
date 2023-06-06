Collecting here the changes that did not make it into the branch.

::

    epsilon:junosw blyth$ jo
    /Users/blyth/junotop/junosw
    On branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    Your branch is up-to-date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Detector/Geometry/Geometry/PMT.h
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:junosw blyth$ cp Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh ~/j/SProfileDemo/
    epsilon:junosw blyth$ cp Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc ~/j/SProfileDemo/
    epsilon:junosw blyth$ cp Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc ~/j/SProfileDemo/
    epsilon:junosw blyth$ 

    epsilon:j blyth$ git commit -m "scratch collect the changes such as SProfile-ing  that did not include into the branch"
    [main fe49b1c] scratch collect the changes such as SProfile-ing  that did not include into the branch
     5 files changed, 1930 insertions(+), 1 deletion(-)
     create mode 100644 SProfileDemo/index.rst
     create mode 100644 SProfileDemo/junoSD_PMT_v2.cc
     create mode 100644 SProfileDemo/junoSD_PMT_v2.hh
     create mode 100644 SProfileDemo/junoSD_PMT_v2_Opticks.cc
    epsilon:j blyth$ 


Get back to clean branch::

    epsilon:junosw blyth$ git checkout Detector/Geometry/Geometry/PMT.h
    epsilon:junosw blyth$ git checkout Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    epsilon:junosw blyth$ jo
    /Users/blyth/junotop/junosw
    On branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    Your branch is up-to-date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.

    nothing to commit, working tree clean
    epsilon:junosw blyth$ 

Jump to main, delete the branch, update main to latest includong the merged branch::

    epsilon:junosw blyth$ git branch 
    * blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
      main
    epsilon:junosw blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ git branch -d blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    warning: deleting branch 'blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess' that has been merged to
             'refs/remotes/origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess', but not yet merged to HEAD.
    Deleted branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess (was 9869e7d).
    epsilon:junosw blyth$ git branch 
    * main
    epsilon:junosw blyth$ 


    epsilon:junosw blyth$ git pull 


