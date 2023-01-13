blyth-66-low-dependency-PMT-data-access.rst
=============================================


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




PMTSimParamData
-----------------

TODO:

1. remove G4SystemOfUnits
2. split off PMTQty.h 


