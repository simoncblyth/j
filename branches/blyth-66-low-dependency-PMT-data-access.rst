blyth-66-low-dependency-PMT-data-access.rst
=============================================


DONE
------

1. check the serialized PMT Data looks OK : DONE
2. check that the PMT Svc operate normally and give same results as low dependency data API : DONE
3. complete the PMT data collection and serialization : DECIDED TO FOCUS ON API USED BY junoPMTOpticalModel only 
4. make the MR 


   DONE : https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/126


Create the MR
----------------

::

    remote: 
    remote: To create a merge request for blyth-66-low-dependency-PMT-data-access, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-66-low-dependency-PMT-data-access
    remote: 

    N[blyth@localhost junosw]$ git add . 
    N[blyth@localhost junosw]$ git commit -m "branch blyth-66 is ready for merge as it addresses the problem outlined in issue 66" 
    [blyth-66-low-dependency-PMT-data-access 4a9d093] branch blyth-66 is ready for merge as it addresses the problem outlined in issue 66
     1 file changed, 1 insertion(+), 4 deletions(-)
    N[blyth@localhost junosw]$ git push 
    Enumerating objects: 12, done.
    Counting objects: 100% (12/12), done.
    Delta compression using up to 48 threads
    Compressing objects: 100% (7/7), done.
    Writing objects: 100% (7/7), 827 bytes | 827.00 KiB/s, done.
    Total 7 (delta 4), reused 0 (delta 0), pack-reused 0
    remote: 
    remote: To create a merge request for blyth-66-low-dependency-PMT-data-access, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-66-low-dependency-PMT-data-access
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw
       3fe6f7e..4a9d093  blyth-66-low-dependency-PMT-data-access -> blyth-66-low-dependency-PMT-data-access
    N[blyth@localhost junosw]$ 





Workflow overview for getting changes into junosw
----------------------------------------------------

0. update and test building of current main
1. make issue in web interface
2. make branch in web interface
3. checkout the branch (on workstation, also on laptop if have changes there)
4. commit changes into the branch

   * when there are lots of working copy changes decide on how to group the
     changes into multiple easily understood focussed commits

   * make commits with the commit message prefixed with "WIP:" 


Checkout the Branch on workstation and laptop
------------------------------------------------

Workstation::

    N[blyth@localhost junosw]$ git checkout -b blyth-66-low-dependency-PMT-data-access
    Switched to a new branch 'blyth-66-low-dependency-PMT-data-access'

Laptop::

    epsilon:junosw blyth$ jo
    /Users/blyth/junotop/junosw
    On branch main
    Your branch is up-to-date with 'origin/main'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Detector/Geometry/Geometry/IPMTParamSvc.h
        modified:   Detector/Geometry/Geometry/PMTParamSvc.h
        modified:   Detector/Geometry/src/PMTParamSvc.cc
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
        modified:   Simulation/SimSvc/IPMTSimParamSvc/IPMTSimParamSvc/IPMTSimParamSvc.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h

    Untracked files:
      (use "git add <file>..." to include in what will be committed)

        Detector/Geometry/Geometry/PMT.h
        Detector/Geometry/Geometry/PMTCategory.h
        Detector/Geometry/Geometry/PMTParamData.h
        Detector/Geometry/Geometry/PMTParamData_test.cc
        Detector/Geometry/Geometry/PMTParamData_test.py
        Detector/Geometry/Geometry/PMTParamData_test.sh
        Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData.h
        Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData_test.cc
        Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData_test.py
        Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData_test.sh
        Simulation/SimSvc/PMTSimParamSvc/src/PmtSimData_LPMT.h
        Simulation/SimSvc/PMTSimParamSvc/src/PmtSimData_SPMT.h

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ git checkout -b blyth-66-low-dependency-PMT-data-access
    M	Detector/Geometry/Geometry/IPMTParamSvc.h
    M	Detector/Geometry/Geometry/PMTParamSvc.h
    M	Detector/Geometry/src/PMTParamSvc.cc
    M	Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    M	Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
    M	Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    M	Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    M	Simulation/SimSvc/IPMTSimParamSvc/IPMTSimParamSvc/IPMTSimParamSvc.h
    M	Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc
    M	Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h
    Switched to a new branch 'blyth-66-low-dependency-PMT-data-access'
    epsilon:junosw blyth$ 


Review the changes to decide on how to split into commits
---------------------------------------------------------------

::

    epsilon:junosw blyth$ jo
    /Users/blyth/junotop/junosw
    On branch blyth-66-low-dependency-PMT-data-access
    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Detector/Geometry/Geometry/IPMTParamSvc.h
        Detector/Geometry/Geometry/PMT.h
        Detector/Geometry/Geometry/PMTCategory.h

        ## enumerations repositioned into PMT.h PMTCategory.h no-dependency headers 

        modified:   Detector/Geometry/Geometry/PMTParamSvc.h
        modified:   Detector/Geometry/src/PMTParamSvc.cc
        Detector/Geometry/Geometry/PMTParamData.h
        Detector/Geometry/Geometry/PMTParamData_test.cc
        Detector/Geometry/Geometry/PMTParamData_test.py
        Detector/Geometry/Geometry/PMTParamData_test.sh

        ## separate PMTParamData.h struct from PMTParamSvc.h for low dependency access


        modified:   Simulation/SimSvc/IPMTSimParamSvc/IPMTSimParamSvc/IPMTSimParamSvc.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h

        Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData.h
        Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData_test.cc
        Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData_test.py
        Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData_test.sh
        Simulation/SimSvc/PMTSimParamSvc/src/PmtSimData_LPMT.h
        Simulation/SimSvc/PMTSimParamSvc/src/PmtSimData_SPMT.h

        ## separate PMTSimParamData.h struct from PMTSimParamSvc.h, splitting data container from collection 

        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc

        ## use the new low level PMT data access from the opticks setup 


    Untracked files:
      (use "git add <file>..." to include in what will be committed)



commit and push first change to the branch : from laptop
-----------------------------------------------------------


::

    epsilon:junosw blyth$ git push 
    fatal: The current branch blyth-66-low-dependency-PMT-data-access has no upstream branch.
    To push the current branch and set the remote as upstream, use

        git push --set-upstream origin blyth-66-low-dependency-PMT-data-access

    epsilon:junosw blyth$ git push --set-upstream origin blyth-66-low-dependency-PMT-data-access
    Counting objects: 8, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (8/8), done.
    Writing objects: 100% (8/8), 1.35 KiB | 1.35 MiB/s, done.
    Total 8 (delta 5), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-66-low-dependency-PMT-data-access, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-66-low-dependency-PMT-data-access
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       9dc0807..812c400  blyth-66-low-dependency-PMT-data-access -> blyth-66-low-dependency-PMT-data-access
    Branch blyth-66-low-dependency-PMT-data-access set up to track remote branch blyth-66-low-dependency-PMT-data-access from origin.
    epsilon:junosw blyth$ 


pick up that first change on workstation
------------------------------------------


::

    N[blyth@localhost junosw]$ git pull 
    remote: Enumerating objects: 8, done.
    remote: Counting objects: 100% (8/8), done.
    remote: Compressing objects: 100% (8/8), done.
    remote: Total 8 (delta 0), reused 0 (delta 0), pack-reused 0
    Unpacking objects: 100% (8/8), 3.44 KiB | 586.00 KiB/s, done.
    From code.ihep.ac.cn:JUNO/offline/junosw
       9dc0807..812c400  blyth-66-low-dependency-PMT-data-access -> origin/blyth-66-low-dependency-PMT-data-access
    There is no tracking information for the current branch.
    Please specify which branch you want to rebase against.
    See git-pull(1) for details.

        git pull <remote> <branch>

    If you wish to set tracking information for this branch you can do so with:

        git branch --set-upstream-to=origin/<branch> blyth-66-low-dependency-PMT-data-access

    N[blyth@localhost junosw]$ git branch --set-upstream-to=origin/blyth-66-low-dependency-PMT-data-access blyth-66-low-dependency-PMT-data-access
    Branch 'blyth-66-low-dependency-PMT-data-access' set up to track remote branch 'blyth-66-low-dependency-PMT-data-access' from 'origin'.
    N[blyth@localhost junosw]$ 



    N[blyth@localhost junosw]$ git pull 
    Updating 0661c11..812c400
    Fast-forward
     Detector/Geometry/Geometry/IPMTParamSvc.h | 16 +++-------------
     Detector/Geometry/Geometry/PMT.h          | 33 +++++++++++++++++++++++++++++++++
     Detector/Geometry/Geometry/PMTCategory.h  | 58 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     3 files changed, 94 insertions(+), 13 deletions(-)
     create mode 100644 Detector/Geometry/Geometry/PMT.h
     create mode 100644 Detector/Geometry/Geometry/PMTCategory.h
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ 





2nd push from laptop
----------------------

::

    epsilon:junosw blyth$ git commit -m "WIP: separate PMTParamData.h struct from PMTParamSvc.h for low dependency access"
    [blyth-66-low-dependency-PMT-data-access 28d4f4d] WIP: separate PMTParamData.h struct from PMTParamSvc.h for low dependency access
     6 files changed, 173 insertions(+), 43 deletions(-)
     create mode 100644 Detector/Geometry/Geometry/PMTParamData.h
     create mode 100644 Detector/Geometry/Geometry/tests/PMTParamData_test.cc
     create mode 100644 Detector/Geometry/Geometry/tests/PMTParamData_test.py
     create mode 100755 Detector/Geometry/Geometry/tests/PMTParamData_test.sh
    epsilon:junosw blyth$ git push 
    Counting objects: 13, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (13/13), done.
    Writing objects: 100% (13/13), 2.36 KiB | 2.36 MiB/s, done.
    Total 13 (delta 7), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-66-low-dependency-PMT-data-access, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-66-low-dependency-PMT-data-access
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       812c400..28d4f4d  blyth-66-low-dependency-PMT-data-access -> blyth-66-low-dependency-PMT-data-access
    epsilon:junosw blyth$ 


pick up 2nd push on workstation
-------------------------------------


::

    N[blyth@localhost junosw]$ git pull 
    remote: Enumerating objects: 13, done.
    remote: Counting objects: 100% (13/13), done.
    remote: Compressing objects: 100% (13/13), done.
    remote: Total 13 (delta 0), reused 13 (delta 0), pack-reused 0
    Unpacking objects: 100% (13/13), 8.77 KiB | 691.00 KiB/s, done.
    From code.ihep.ac.cn:JUNO/offline/junosw
       812c400..28d4f4d  blyth-66-low-dependency-PMT-data-access -> origin/blyth-66-low-dependency-PMT-data-access
    Updating 812c400..28d4f4d
    Fast-forward
     Detector/Geometry/Geometry/PMTParamData.h             | 87 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     Detector/Geometry/Geometry/PMTParamSvc.h              | 16 +++++++--------
     Detector/Geometry/Geometry/tests/PMTParamData_test.cc | 19 ++++++++++++++++++
     Detector/Geometry/Geometry/tests/PMTParamData_test.py | 10 ++++++++++
     Detector/Geometry/Geometry/tests/PMTParamData_test.sh | 37 ++++++++++++++++++++++++++++++++++
     Detector/Geometry/src/PMTParamSvc.cc                  | 47 ++++++++++++-------------------------------
     6 files changed, 173 insertions(+), 43 deletions(-)
     create mode 100644 Detector/Geometry/Geometry/PMTParamData.h
     create mode 100644 Detector/Geometry/Geometry/tests/PMTParamData_test.cc
     create mode 100644 Detector/Geometry/Geometry/tests/PMTParamData_test.py
     create mode 100755 Detector/Geometry/Geometry/tests/PMTParamData_test.sh
    N[blyth@localhost junosw]$ 





3rd major push
-----------------

::

    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ git commit -m "WIP: separate data carrier struct/classes from PMTSimParamSvc.h into low dependency headers : PMTSimParamData.h PmtSimData_LPMT.h PmtSimData_SPMT.h, make IPMTSimParamSvc.h accessors const correct "
    [blyth-66-low-dependency-PMT-data-access ed79552] WIP: separate data carrier struct/classes from PMTSimParamSvc.h into low dependency headers : PMTSimParamData.h PmtSimData_LPMT.h PmtSimData_SPMT.h, make IPMTSimParamSvc.h accessors const correct
     9 files changed, 861 insertions(+), 268 deletions(-)
     create mode 100644 Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData.h
     create mode 100644 Simulation/SimSvc/PMTSimParamSvc/src/PmtSimData_LPMT.h
     create mode 100644 Simulation/SimSvc/PMTSimParamSvc/src/PmtSimData_SPMT.h
     create mode 100644 Simulation/SimSvc/PMTSimParamSvc/src/tests/PMTSimParamData_test.cc
     create mode 100644 Simulation/SimSvc/PMTSimParamSvc/src/tests/PMTSimParamData_test.py
     create mode 100755 Simulation/SimSvc/PMTSimParamSvc/src/tests/PMTSimParamData_test.sh
    epsilon:junosw blyth$ git push 
    Counting objects: 18, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (17/17), done.
    Writing objects: 100% (18/18), 9.03 KiB | 4.52 MiB/s, done.
    Total 18 (delta 6), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-66-low-dependency-PMT-data-access, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-66-low-dependency-PMT-data-access
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       a57033b..ed79552  blyth-66-low-dependency-PMT-data-access -> blyth-66-low-dependency-PMT-data-access
    epsilon:junosw blyth$ 




4th 
-----

::

    epsilon:junosw blyth$ git s
    On branch blyth-66-low-dependency-PMT-data-access
    Your branch is up-to-date with 'origin/blyth-66-low-dependency-PMT-data-access'.

    Changes to be committed:
      (use "git reset HEAD <file>..." to unstage)

        modified:   Detector/Geometry/Geometry/PMTParamData.h
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData.h

    epsilon:junosw blyth$ git commit -m "WIP: try passing the low dependency PMT data to Opticks"
    [blyth-66-low-dependency-PMT-data-access 51c4430] WIP: try passing the low dependency PMT data to Opticks
     6 files changed, 83 insertions(+), 19 deletions(-)
    epsilon:junosw blyth$ git push 
    Counting objects: 19, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (19/19), done.
    Writing objects: 100% (19/19), 2.37 KiB | 2.37 MiB/s, done.
    Total 19 (delta 17), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-66-low-dependency-PMT-data-access, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-66-low-dependency-PMT-data-access
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       aabdd3f..51c4430  blyth-66-low-dependency-PMT-data-access -> blyth-66-low-dependency-PMT-data-access
    epsilon:junosw blyth$ 



HMM : would be better for the data carriers not to need any opticks headers
-------------------------------------------------------------------------------

::


         ^~~~~
    In file included from /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NPFold.h:72,
                     from /data/blyth/junotop/junosw/Detector/Geometry/Geometry/PMTParamData.h:5,
                     from /data/blyth/junotop/junosw/Detector/Geometry/Geometry/PMTParamSvc.h:29,
                     from /data/blyth/junotop/junosw/Reconstruction/OECWFrec/src/OECWFrec.cc:11:
    /usr/include/fts.h:41:3: error: #error "<fts.h> cannot be used with -D_FILE_OFFSET_BITS==64"
     # error "<fts.h> cannot be used with -D_FILE_OFFSET_BITS==64"
       ^~~~~
    [ 83%] Building CXX object Simulation/ElecSimV3/ElecSimAlg/CMakeFiles/ElecSimAlg.dir/src/TriggerHandlerLpmt.cc.o
    In file included from /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NPFold.h:72,
                     from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData.h:61,
                     from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h:23,
                     from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:2:
    /usr/include/fts.h:41:3: error: #error "<fts.h> cannot be used with -D_FILE_OFFSET_BITS==64"
     # error "<fts.h> cannot be used with -D_FILE_OFFSET_BITS==64"
       ^~~~~



Extreme approach at keeping data carriers as simple as possible
------------------------------------------------------------------

::

    epsilon:tests blyth$ jo
    /Users/blyth/junotop/junosw
    On branch blyth-66-low-dependency-PMT-data-access
    Your branch is up-to-date with 'origin/blyth-66-low-dependency-PMT-data-access'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Detector/Geometry/Geometry/PMTParamData.h
        modified:   Detector/Geometry/Geometry/tests/PMTParamData_test.cc
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/tests/PMTSimParamData_test.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/tests/PMTSimParamData_test.sh

    Untracked files:
      (use "git add <file>..." to include in what will be committed)

        Detector/Geometry/Geometry/_PMTParamData.h
        Simulation/SimSvc/PMTSimParamSvc/src/_PMTSimParamData.h

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:junosw blyth$ git add . 
    epsilon:junosw blyth$ git commit -m "WIP: take an extreme approach to keeping the data carriers as simple as possible by moving persist machinery into paired structs _PMTParamData.h _PMTSimParamData.h" 
    [blyth-66-low-dependency-PMT-data-access 1ab0919] WIP: take an extreme approach to keeping the data carriers as simple as possible by moving persist machinery into paired structs _PMTParamData.h _PMTSimParamData.h
     9 files changed, 258 insertions(+), 224 deletions(-)
     create mode 100644 Detector/Geometry/Geometry/_PMTParamData.h
     create mode 100644 Simulation/SimSvc/PMTSimParamSvc/src/_PMTSimParamData.h
    epsilon:junosw blyth$ git push 
    Counting objects: 24, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (24/24), done.
    Writing objects: 100% (24/24), 3.04 KiB | 3.04 MiB/s, done.
    Total 24 (delta 21), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-66-low-dependency-PMT-data-access, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-66-low-dependency-PMT-data-access
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       51c4430..1ab0919  blyth-66-low-dependency-PMT-data-access -> blyth-66-low-dependency-PMT-data-access
    epsilon:junosw blyth$ 



DSO U4 dependency
------------------

::

    [ 61%] Built target PMTSimParamSvc
    Consolidate compiler generated dependencies of target DetSimOptions
    [ 61%] Building CXX object Simulation/DetSimV2/DetSimOptions/CMakeFiles/DetSimOptions.dir/src/LSExpDetectorConstruction_Opticks.cc.o
    In file included from /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:7:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:5:10: fatal error: U4MaterialPropertyVector.h: No such file or directory
     #include "U4MaterialPropertyVector.h"
              ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
    compilation terminated.
    make[2]: *** [Simulation/DetSimV2/DetSimOptions/CMakeFiles/DetSimOptions.dir/src/LSExpDetectorConstruction_Opticks.cc.o] Error 1
    make[1]: *** [Simulation/DetSimV2/DetSimOptions/CMakeFiles/DetSimOptions.dir/all] Error 2


From Physisim::

     28     DEPENDS
     29         DetSimAlg
     30         MCParamsSvc
     31         EGet
     32         $<$<BOOL:${Opticks_FOUND}>:${Opticks_TARGET}>
     33 


python level error : was due to m_insertVersion being a string not an int
-------------------------------------------------------------------------

::

    == Root Writer ==
     == PMTSimParamSvc == 
    Traceback (most recent call last):
      File "/data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py", line 149, in run
        self.module_container_default.init(self.toptask, self.args)
      File "/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOModule.py", line 68, in init
        module.init(task, args)
      File "/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py", line 155, in init
        self.init_geometry_and_parameters(toptask, args)
      File "/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py", line 1084, in init_geometry_and_parameters
        pmt_sim_param_svc = task.createSvc("PMTSimParamSvc")
    RuntimeError: basic_string::_M_construct null not valid
    junotoptask.terminate           WARN: invalid state tranform ((Invalid)) => ((EndUp))

    **************************************************
    Terminating @ localhost.localdomain on Fri Jan 13 04:27:32 2023


::

    1082         import PMTSimParamSvc
    1083         print(" == PMTSimParamSvc == ")
    1084         pmt_sim_param_svc = task.createSvc("PMTSimParamSvc")
    1085         pmt_sim_param_svc.property("DBType").set(args.dbtype)


next need to check the saved data
------------------------------------

Should put it here::

    epsilon:notes blyth$ l $HOME/.opticks/GEOM/
    total 0
    0 drwxr-xr-x  18 blyth  staff  576 Nov 20 16:43 ..
    0 drwxr-xr-x   7 blyth  staff  224 Nov  5 12:11 example_pet
    0 drwxr-xr-x   4 blyth  staff  128 Nov  4 20:29 .
    0 drwxr-xr-x   8 blyth  staff  256 Oct 11 16:24 J004
    epsilon:notes blyth$ 




::

     23 #ifdef WITH_G4CXOPTICKS
     24 void LSExpDetectorConstruction_Opticks::Setup(
     25           int opticksMode,
     26           const G4VPhysicalVolume* world,
     27           const G4VSensitiveDetector* sd,
     28           PMTParamData* ppd, 
     29           PMTSimParamData* psd
     30           )
     31 {         
     32     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     33     if( opticksMode == 0 ) return ;
     34 
     35     G4CXOpticks::SetGeometry(world) ; 
     36 
     37     _PMTParamData    _ppd(*ppd) ; 
     38     _PMTSimParamData _psd(*psd) ; 
     39 
     40     NPFold* j = new NPFold ; 
     41     j->add_subfold( "PMTParamData",    _ppd.serialize() );
     42     j->add_subfold( "PMTSimParamData", _psd.serialize() );
     43 
     44     SSim::AddSubfold("juno", j );
     45 
     46     LOG(info) << "] WITH_G4CXOPTICKS " ; 
     47 }



abo
----

::

    X4Solid::convertPolycone@1724: all_z_descending detected, reversing PMT_3inch_cntr_solid
    X4Solid::convertPolycone@1724: all_z_descending detected, reversing PMT_3inch_pmt_solid_cyl
    GInstancer::dumpRepeatCandidates@464:  num_repcan 9 dmax 20
     pdig 159961bde1896fe286c02b4c3f05c8c9 ndig  25600 nprog      4 placements  25600 n PMT_3inch_log_phys
     pdig b82765dbe93381d08867b5bc550ceed3 ndig  12615 nprog      6 placements  12615 n pLPMT_NNVT_MCPPMT
     pdig 838cd73cc9dd9d9add66efd658630c12 ndig   4997 nprog      6 placements   4997 n pLPMT_Hamamatsu_R12860
     pdig 29c21c0b8afac0824902c82e6fbe3146 ndig   2400 nprog      5 placements   2400 n mask_PMT_20inch_vetolMaskVirtual_phys
     pdig ed3d2c21991e3bef5e069713af9fa6ca ndig    590 nprog      0 placements    590 n lSteel_phys
     pdig ac627ab1ccbdb62ec96e702f07f6425b ndig    590 nprog      0 placements    590 n lFasteners_phys
     pdig f899139df5e1059396431415e770c6dd ndig    590 nprog      0 placements    590 n lUpper_phys
     pdig 38b3eff8baf56627478ec76a704e9b52 ndig    590 nprog      0 placements    590 n lAddition_phys
     pdig 4c29bcd2a52a397de5036b415af92efe ndig    504 nprog    129 placements    504 n pPanel_0_f_
    G4CXOpticks::setGeometry@245: 
    NP::load Failed to load from path /tmp/blyth/opticks/GScintillatorLib/LS_ori/RINDEX.npy
    G4CXOpticks::setGeometry@276: [ G4CXOpticks__setGeometry_saveGeometry 
    G4CXOpticks::saveGeometry@499: [ /home/blyth/.opticks/GEOM/J005
    G4CXOpticks::saveGeometry@500: [ /home/blyth/.opticks/GEOM/J005
    G4CXOpticks::saveGeometry [ /home/blyth/.opticks/GEOM/J005
    python: /data/blyth/junotop/opticks/ggeo/GGeo.cc:767: void GGeo::save_to_dir(const char*, const char*): Assertion `idpath == nullptr' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-4.el7_9.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-59.el7_9.1.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libicu-50.2-4.el7_7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-25.el7_9.x86_64 openssl-libs-1.0.2k-25.el7_9.x86_64 pcre-8.32-17.el7.x86_64 readline-6.2-11.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd1e8dcec in GGeo::save_to_dir (this=0xc6548c0, base=0x1031b240 "/home/blyth/.opticks/GEOM/J005", reldir=0x7fffd2f07ec7 "GGeo")
        at /data/blyth/junotop/opticks/ggeo/GGeo.cc:767
    #5  0x00007fffd2ed3614 in G4CXOpticks::saveGeometry (this=0x7180250, dir_=0x7fffffffc300 "/home/blyth/.opticks/GEOM/J005")
        at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:504
    #6  0x00007fffd2ed1712 in G4CXOpticks::setGeometry (this=0x7180250, fd_=0x156c8ef20) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:277
    #7  0x00007fffd2ed15d9 in G4CXOpticks::setGeometry (this=0x7180250, gg_=0xc6548c0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:250
    #8  0x00007fffd2ed14b2 in G4CXOpticks::setGeometry (this=0x7180250, world=0x570c470) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:239
    #9  0x00007fffd2ecfd59 in G4CXOpticks::SetGeometry (world=0x570c470) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:64
    #10 0x00007fffce57a132 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=3, world=0x570c470, sd=0x58f9250, ppd=0x922ce0, 
        psd=0x9256e0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:26
    #11 0x00007fffce56ab01 in LSExpDetectorConstruction::setupOpticks (this=0x5525d00, world=0x570c470)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:394
    #12 0x00007fffce56a6dc in LSExpDetectorConstruction::Construct (this=0x5525d00)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:361
    #13 0x00007fffdbf5ecbe in G4RunManager::InitializeGeometry() ()





    G4CXOpticks::setGeometry@245: 
    NP::load Failed to load from path /tmp/blyth/opticks/GScintillatorLib/LS_ori/RINDEX.npy
    G4CXOpticks::setGeometry@276: [ G4CXOpticks__setGeometry_saveGeometry 
    G4CXOpticks::saveGeometry@499: [ /home/blyth/.opticks/GEOM/J005
    G4CXOpticks::saveGeometry@500: [ /home/blyth/.opticks/GEOM/J005
    G4CXOpticks::saveGeometry [ /home/blyth/.opticks/GEOM/J005
    GGeo::save_to_dir@768:  idpath expected nullptr at this juncture, but isnt [/tmp/blyth/opticks/GGeo]
    python: /data/blyth/junotop/opticks/ggeo/GGeo.cc:773: void GGeo::save_to_dir(const char*, const char*): Assertion `idpath == nullptr' failed.


    N[blyth@localhost opticks]$ env | grep G4CXOpticks
    G4CXOpticks=INFO
    G4CXOpticks__simulate_saveEvent=1
    G4CXOpticks__setGeometry_saveGeometry=/home/blyth/.opticks/GEOM/J005
    G4CXOpticks__SaveGeometry_DIR=/home/blyth/.opticks/GEOM/J005
    N[blyth@localhost opticks]$ 



idpath non-null in GGeo::save_to_dir
---------------------------------------

It is defaulting to::

  54 const char* BOpticksResource::IDPATH_TRANSITIONAL = SPath::Resolve("$CFBaseFromGEOM/GGeo", NOOP) ;

So can control the idpath via two envvars::

    epsilon:sysrap blyth$ GEOM=hello hello_CFBaseFromGEOM=/dbasjkdajd SPathTest 
    test_Resolve@204: 
                                                            $TMP :                                           /tmp/blyth/opticks
                                               $DefaultOutputDir :                      /tmp/blyth/opticks/GEOM/hello/SPathTest
                                                    $OPTICKS_TMP :                                           /tmp/blyth/opticks
                                             $OPTICKS_EVENT_BASE :                                           /tmp/blyth/opticks
                                                    $HOME/hello  :                                          /Users/blyth/hello 
                             $TMP/somewhere/over/the/rainbow.txt :            /tmp/blyth/opticks/somewhere/over/the/rainbow.txt
                            $NON_EXISTING_EVAR/elsewhere/sub.txt :                         /tmp/blyth/opticks/elsewhere/sub.txt
                                         $CFBase/CSGFoundry/SSim :                           /tmp/blyth/opticks/CSGFoundry/SSim
                                         $CFBASE/CSGFoundry/SSim :                           /tmp/blyth/opticks/CSGFoundry/SSim
                                             /just/some/path.txt :                                          /just/some/path.txt
                                                        stem.ext :                                                     stem.ext
                                                               / :                                                            /
                                                               $ :                                           /tmp/blyth/opticks
                                                         $RNGDir :                           /Users/blyth/.opticks/rngcache/RNG
                                            $CFBaseFromGEOM/GGeo :                                             /dbasjkdajd/GGeo
    epsilon:sysrap blyth$ 




::

    N[blyth@localhost junosw]$ GEOM=J005 SAVE=1 ntds3
    === ntds3 : TDS_DIR /tmp/u4debug/ntds3 SCRIPT ntds3 U4Debug_SaveDir /tmp/u4debug/ntds3
    === ntds3 : DEBUG NOT-enabled
    === ntds3 : DISABLE-NOT-enabled
    === ntds3 : ZEROPHO-NOT-enabled





::

    G4CXOpticks::setGeometry@245: 
    NP::load Failed to load from path /tmp/blyth/opticks/GScintillatorLib/LS_ori/RINDEX.npy
    G4CXOpticks::setGeometry@285: [ fd 0x156c62db0
    G4CXOpticks::setGeometry@287:  [ new SEvt 
    G4CXOpticks::setGeometry@289:  ] new SEvt 
    G4CXOpticks::setGeometry@294: [ CSGOptiX::Create 
    G4CXOpticks::setGeometry@296: ] CSGOptiX::Create 
    G4CXOpticks::setGeometry@298:  cx 0x15a19ca80 qs 0x159d18c40 QSim::Get 0x159d18c40
    G4CXOpticks::setGeometry@301: ] fd 0x156c62db0
    G4CXOpticks::SaveGeometry@541:  save to dir /home/blyth/.opticks/GEOM/J005 configured via envvar G4CXOpticks__SaveGeometry_DIR
    G4CXOpticks::saveGeometry@499: [ /home/blyth/.opticks/GEOM/J005
    G4CXOpticks::saveGeometry@500: [ /home/blyth/.opticks/GEOM/J005
    G4CXOpticks::saveGeometry [ /home/blyth/.opticks/GEOM/J005
    GGeo::save_to_dir@768:  default idpath : [/tmp/blyth/opticks/GGeo] is overridden : [/home/blyth/.opticks/GEOM/J005/GGeo]
    BFile::preparePath@837: created directory /home/blyth/.opticks/GEOM/J005/GGeo/GItemList
    python: /data/blyth/junotop/opticks/ggeo/GMeshLib.cc:171: void GMeshLib::saveAltReferences(): Assertion `unsigned(index) == i' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    (gdb) 

    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd1eb7fec in GMeshLib::saveAltReferences (this=0xca19200) at /data/blyth/junotop/opticks/ggeo/GMeshLib.cc:171
    #5  0x00007fffd1eb7621 in GMeshLib::save (this=0xca19200) at /data/blyth/junotop/opticks/ggeo/GMeshLib.cc:99
    #6  0x00007fffd1e8e654 in GGeo::save_ (this=0xc6296b0) at /data/blyth/junotop/opticks/ggeo/GGeo.cc:834
    #7  0x00007fffd1e8e253 in GGeo::save (this=0xc6296b0) at /data/blyth/junotop/opticks/ggeo/GGeo.cc:820
    #8  0x00007fffd1e8de0a in GGeo::save_to_dir (this=0xc6296b0, base=0x15aafa810 "/home/blyth/.opticks/GEOM/J005", 
        reldir=0x7fffd2f07ec7 "GGeo") at /data/blyth/junotop/opticks/ggeo/GGeo.cc:774
    #9  0x00007fffd2ed3614 in G4CXOpticks::saveGeometry (this=0x7155080, dir_=0x7fffffffc7fe "/home/blyth/.opticks/GEOM/J005")
        at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:504
    #10 0x00007fffd2ed3a6c in G4CXOpticks::SaveGeometry () at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:542
    #11 0x00007fffce57a1df in LSExpDetectorConstruction_Opticks::Setup (opticksMode=3, world=0x56e1300, sd=0x58ce0e0, ppd=0x922d80, 
        psd=0x925780) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:37
    #12 0x00007fffce56ab01 in LSExpDetectorConstruction::setupOpticks (this=0x54fabc0, world=0x56e1300)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:394
    #13 0x00007fffce56a6dc in LSExpDetectorConstruction::Construct (this=0x54fabc0)



    (gdb) f 4
    #4  0x00007fffd1eb7fec in GMeshLib::saveAltReferences (this=0xca19200) at /data/blyth/junotop/opticks/ggeo/GMeshLib.cc:171
    171	        assert( unsigned(index) == i );  // not expecting same GMesh instance more than once
    (gdb) list
    166	    {
    167	        const GMesh* mesh = m_meshes[i]; 
    168	        const NCSG* solid = m_solids[i];  
    169	
    170	        int index = findMeshIndex(mesh); 
    171	        assert( unsigned(index) == i );  // not expecting same GMesh instance more than once
    172	
    173	        const GMesh* altmesh = mesh->getAlt(); 
    174	        if(altmesh == NULL) continue ; 
    175	
    (gdb) p i 
    $1 = 141
    (gdb) p index
    $2 = 139
    (gdb) 
    (gdb) p m_meshes.size()
    $3 = 143

    (gdb) p *mesh
      ...
      m_name = 0xfd7bb20 "solidSJReceiverFastern", 
      m_shortname = 0xfd7bb40 "solidSJReceiverFastern", 
      m_version = 0x0, 
      m_geocode = 84 'T', 
      ...



Problem with a duplicate solid perhaps, causing saving gg to fail. 



Chase down the fail to load
-----------------------------

::

    (gdb) bt
    #0  0x00007ffff741e4fb in raise () from /lib64/libpthread.so.0
    #1  0x00007fffcf92f54d in NP::load (this=0x159180b20, path=0x10155810 "/tmp/blyth/opticks/GScintillatorLib/LS_ori/RINDEX.npy")
        at /data/blyth/junotop/opticks/sysrap/NP.hh:4116
    #2  0x00007fffcf92f2bd in NP::Load_ (path=0x10155810 "/tmp/blyth/opticks/GScintillatorLib/LS_ori/RINDEX.npy")
        at /data/blyth/junotop/opticks/sysrap/NP.hh:2158
    #3  0x00007fffcf92f13e in NP::Load (path_=0x1020f7e0 "/tmp/blyth/opticks/GScintillatorLib/LS_ori/RINDEX.npy")
        at /data/blyth/junotop/opticks/sysrap/NP.hh:2135
    #4  0x00007fffcf96acb1 in SProp::MockupCombination (path_=0x7fffd1edfcb8 "$IDPath/GScintillatorLib/LS_ori/RINDEX.npy")
        at /data/blyth/junotop/opticks/sysrap/SProp.cc:37
    #5  0x00007fffd1e97ae1 in GGeo::convertSim_Prop (this=0xc6299f0, sim=0x5e8bcd0) at /data/blyth/junotop/opticks/ggeo/GGeo.cc:2579
    #6  0x00007fffd1e972c7 in GGeo::convertSim (this=0xc6299f0) at /data/blyth/junotop/opticks/ggeo/GGeo.cc:2506
    #7  0x00007fffd216fcc2 in CSG_GGeo_Convert::convertSim (this=0x7fffffff4480) at /data/blyth/junotop/opticks/CSG_GGeo/CSG_GGeo_Convert.cc:200
    #8  0x00007fffd216efd9 in CSG_GGeo_Convert::convert (this=0x7fffffff4480) at /data/blyth/junotop/opticks/CSG_GGeo/CSG_GGeo_Convert.cc:120
    #9  0x00007fffd216e6a5 in CSG_GGeo_Convert::Translate (ggeo=0xc6299f0) at /data/blyth/junotop/opticks/CSG_GGeo/CSG_GGeo_Convert.cc:50
    #10 0x00007fffd2ed15bf in G4CXOpticks::setGeometry (this=0x7155450, gg_=0xc6299f0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:249
    #11 0x00007fffd2ed14b2 in G4CXOpticks::setGeometry (this=0x7155450, world=0x56e1640) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:239
    #12 0x00007fffd2ecfd59 in G4CXOpticks::SetGeometry (world=0x56e1640) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:64
    #13 0x00007fffce57a132 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=3, world=0x56e1640, sd=0x58ce420, ppd=0x922e20, 
        psd=0x925820) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:26
    #14 0x00007fffce56ab01 in LSExpDetectorConstruction::setupOpticks (this=0x54faed0, world=0x56e1640)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:394







/Users/blyth/.opticks/GEOM/J005/CSGFoundry/SSim/juno



HMM : dont need all Svc API in Data but do need the below API
-----------------------------------------------------------------

::

    123 void junoPMTOpticalModel::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
    124 {
    125     const G4Track* track = fastTrack.GetPrimaryTrack();
    126 
    127     int pmtid  = get_pmtid(track);
    128     int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
    129    
    130     _photon_energy  = energy;
    131     _wavelength     = twopi*hbarc/energy;
    132     n_glass         = _rindex_glass->Value(_photon_energy);
    133    
    134     _qe             = m_PMTSimParSvc->get_pmtid_qe(pmtid, energy);
    135 
    136     n_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_RINDEX", _photon_energy);
    137     k_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_KINDEX", _photon_energy);
    138     d_coating       = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "ARC_THICKNESS")/m;
    139 
    140     n_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_RINDEX", _photon_energy);
    141     k_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_KINDEX", _photon_energy);
    142     d_photocathode  = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "PHC_THICKNESS")/m;
    143 


::

    826 double PMTSimParamSvc::get_pmtid_qe(int pmtid, double energy){
    827 
    828   int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid) ;

    /// already have this DiscoMap 

    829   assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    830   double qe = get_pmtcat_qe(pmtcat, energy);
    831   double qe_scale = get_pmt_qe_scale(pmtid);
    832   qe = qe*qe_scale;
    833   assert(qe > 0 && qe < 1);
    834   return qe;
    835 }


    818 double PMTSimParamSvc::get_pmtcat_qe(int pmtcat, double energy){
    819     double qe = -1 ;
    820     G4MaterialPropertyVector* vec = get_pmtcat_qe_vs_energy(pmtcat);
    821     assert(vec);
    822     qe = vec->Value(energy);
    823     return qe;
    824 }


    898 G4MaterialPropertyVector*  PMTSimParamSvc::get_pmtcat_qe_vs_energy(int pmtcat)
    899 {
    900     assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    901     G4MaterialPropertyVector * vec = 0 ;
    902     switch(pmtcat)
    903     {   //FIXME:KPMT_Unknown represent WP pmt,which use normal NNVTMCP ?
    904         case kPMT_Unknown:     vec = m_QEshape_WP_PMT    ; break ;
    905         case kPMT_NNVT:        vec = m_QEshape_NNVT      ; break ;
    906         case kPMT_Hamamatsu:   vec = m_QEshape_R12860    ; break ;
    907         case kPMT_HZC:         vec = m_QEshape_HZC       ; break ;
    908         case kPMT_NNVT_HighQE: vec = m_QEshape_NNVT_HiQE ; break ;
    909     }
    910     assert(vec);
    911     return vec;
    912 }


    837 double PMTSimParamSvc::get_pmt_qe_scale(int pmtid){
    838       return get_real_qe_at420nm(pmtid)/get_shape_qe_at420nm(pmtid);
    839 }



Arghh : sniper or boost-python error capture drops the stack : so have to noddy debug
--------------------------------------------------------------------------------------------

::

    START TO construct Calibration Units. 
    /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:381 completed construction of physiWorld  m_opticksMode 3 WITH_G4CXOPTICKS  proceeding to setup Opticks 
    Traceback (most recent call last):
      File "/data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py", line 161, in run
        self.toptask.run()
    IndexError: map::at
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully


::

    _PMTSimParamData::Scan_pmtid_qe pmtid 17608
    _PMTSimParamData::Scan_pmtid_qe pmtid 17609
    _PMTSimParamData::Scan_pmtid_qe pmtid 17610
    _PMTSimParamData::Scan_pmtid_qe pmtid 17611
    _PMTSimParamData::Scan_pmtid_qe pmtid 30000
    Traceback (most recent call last):
      File "/data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py", line 161, in run
        self.toptask.run()
    IndexError: map::at
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################



::

    006 enum PMT_CATEGORY {
      7   kPMT_Unknown=-1,
      8   kPMT_NNVT,
      9   kPMT_Hamamatsu,
     10   kPMT_HZC,
     11   kPMT_NNVT_HighQE
     12 };
     13 



    c = t.pmtCat   

    In [13]: c[17612-10:17612+10]
    Out[13]: 
    array([[ 17602,      1],
           [ 17603,      1],
           [ 17604,      1],
           [ 17605,      1],
           [ 17606,      1],
           [ 17607,      1],
           [ 17608,      1],
           [ 17609,      1],
           [ 17610,      1],
           [ 17611,      1],
           [300000,      2],
           [300001,      2],
           [300002,      2],
           [300003,      2],
           [300004,      2],
           [300005,      2],
           [300006,      2],
           [300007,      2],
           [300008,      2],
           [300009,      2]], dtype=int32)




    In [12]: t.pmtTotal
    Out[12]: array([17612, 25600,  2400, 45612], dtype=int32)


Hmm : m_all_pmt_category missing the WP 2400::

    In [19]: 17612+25600+2400
    Out[19]: 45612

    In [20]: 17612+25600
    Out[20]: 43212


::

    PMTSimParamData::desc
                 m_all_pmtID.size 45612
        m_all_pmtID_qe_scale.size 45612
          m_map_pmt_category.size 17612
          m_all_pmt_category.size 43212
                 pd_map_SPMT.size 25600
                   pd_vector.size 17612
    pd_vector num_lpmt 17612


::

    GEOM=J006 SAVE=1 ntds3



