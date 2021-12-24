Fixing the conflict is easy : the issue is why did it happen ? What did I do wrong to cause it ? 
====================================================================================================



N[blyth@localhost offline]$ jo
/data/blyth/junotop/offline
C       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
?       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py.mine
?       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py.r5183
?       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py.r5222
M       Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
M       Simulation/DetSimV2/PMTSim/include/Hamamatsu_R12860_PMTSolid.hh
M       Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh




N[blyth@localhost offline]$ cp Examples/Tutorial/python/Tutorial/JUNODetSimModule.py* ~/jdsm/
N[blyth@localhost offline]$ l ~/jdsm/
total 428
  0 drwxrwxr-x.  2 blyth blyth    131 Dec 23 04:43 .
100 -rw-rw-r--.  1 blyth blyth 102062 Dec 23 04:43 JUNODetSimModule.py.r5183
104 -rw-rw-r--.  1 blyth blyth 103462 Dec 23 04:43 JUNODetSimModule.py.r5222
108 -rw-rw-r--.  1 blyth blyth 107649 Dec 23 04:43 JUNODetSimModule.py
104 -rw-rw-r--.  1 blyth blyth 104044 Dec 23 04:43 JUNODetSimModule.py.mine
 12 drwx--x--x. 54 blyth blyth   8192 Dec 23 04:43 ..
N[blyth@localhost offline]$ 


N[blyth@localhost offline]$ svn resolve --accept=theirs-full Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
Resolved conflicted state of 'Examples/Tutorial/python/Tutorial/JUNODetSimModule.py'


N[blyth@localhost offline]$ svn st 
M       Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
M       Simulation/DetSimV2/PMTSim/include/Hamamatsu_R12860_PMTSolid.hh
M       Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
M       Simulation/DetSimV2/PMTSim/include/NNVT_MCPPMT_PMTSolid.hh
M       Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
M       Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc
M       Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
M       Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc
?       Simulation/DetSimV2/PMTSim/src/ZCanvas.h
?       Simulation/DetSimV2/PMTSim/src/ZSolid.cc
?       Simulation/DetSimV2/PMTSim/src/ZSolid.h
M       build.sh
?       build_Debug.sh
?       build_RelWithDebInfo.sh
N[blyth@localhost offline]$ 


N[blyth@localhost offline]$ diff Examples/Tutorial/python/Tutorial/JUNODetSimModule.py ~/jdsm/JUNODetSimModule.py.mine
1715c1715
<     --pmt20inch-polycone-neck 
---
>     FORMER OPTION --pmt20inch-polycone-neck IS NOW THE DEFAULT 
1718c1718
<     --pmt20inch-simplify-csg 
---
>     FORMER OPTION --pmt20inch-simplify-csg IS NOW THE DEFAULT
1720a1721
> 
1722c1723,1731
<         Simplify CSG modelling used in AdditionAcrylicConstruction, avoiding CSG subtraction for daughters
---
>         Simplify CSG modelling avoiding CSG subtraction for daughters, see AdditionAcrylicConstruction
> 
> 
> 
>     --pmt20inch-obsolete-torus-neck
>         USE ONLY FOR DEBUGGING : Revert to the obsolete torus neck which has spurious intersects, bad performance and no Opticks support
> 
>     --pmt20inch-profligate-tail-cut
>         USE ONLY FOR DEBUGGING : Revert to profligate G4IntersectionSolid "cutting" that substantially adds complexity and breaks Opticks 
1725c1734,1737
<         Change CD geometry by skipping the sticks. USE ONLY FOR DEBUGGING, see LSExpDetectorConstruction::setupCentralDetector
---
>         USE ONLY FOR DEBUGGING : Changes CD geometry by skipping the sticks, see LSExpDetectorConstruction::setupCentralDetector
> 
>     --pmt20inch-plus-dynode
>         USE ONLY FOR DEBUGGING : Adds PMT dynode geometry even when not using new PMT optical model, eg to check dynode does not impinge
N[blyth@localhost offline]$ 



epsilon:offline blyth$ jo
/Users/blyth/junotop/offline
M       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
?       ungrab.sh
epsilon:offline blyth$ 




* https://juno.ihep.ac.cn/trac/changeset/5183/offline

  PRIOR to SWITCH machinery   

* https://juno.ihep.ac.cn/trac/changeset/5187/offline

  Added the SWITCH machinery  


* https://juno.ihep.ac.cn/trac/browser/offline/trunk/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py  

  Last change on this file was 5187, checked in by blyth, 2 weeks ago



N[blyth@localhost ~]$ cd ~/jdsm
N[blyth@localhost jdsm]$ l


100 -rw-rw-r--.  1 blyth blyth 102062 Dec 23 04:43 JUNODetSimModule.py.r5183  ## without textwrap or SWITCH : an old version  
104 -rw-rw-r--.  1 blyth blyth 103462 Dec 23 04:43 JUNODetSimModule.py.r5222  ## SWITCH machinery present but old version of SWITCH string 
104 -rw-rw-r--.  1 blyth blyth 104044 Dec 23 04:43 JUNODetSimModule.py.mine   ## looks like the latest 


108 -rw-rw-r--.  1 blyth blyth 107649 Dec 23 04:43 JUNODetSimModule.py        ## with one great big conflict block starting at SWITCH



N[blyth@localhost jdsm]$ diff JUNODetSimModule.py.r5222 JUNODetSimModule.py.mine     

        ## difference only in the SWITCH test updates 
        ## I can understand this, does that means that someone committed an old version of my switches causing he conflict 

      
N[blyth@localhost jdsm]$ diff -y JUNODetSimModule.py JUNODetSimModule.py.mine

       ## this one is mystifying 
       ## thats because is comparing JUNODetSimModule.py with the conflict markers in it with the latest
       ## .. doesnt make much sense to compare a file with conflict markers in it 





epsilon:offline blyth$ scp P:jdsm/JUNODetSimModule.py.mine Examples/Tutorial/python/Tutorial/JUNODetSimModule.py




Try again::


    epsilon:offline blyth$ svn up
    Updating '.':
    A    build_Debug.sh
    A    build_RelWithDebInfo.sh
    U    build.sh
    Updated to revision 5223.
    epsilon:offline blyth$ 
    epsilon:offline blyth$ 
    epsilon:offline blyth$ 
    epsilon:offline blyth$ scp P:jdsm/JUNODetSimModule.py.mine Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    JUNODetSimModule.py.mine                                                                                                                                                100%  102KB  21.1KB/s   00:04    
    epsilon:offline blyth$ 
    epsilon:offline blyth$ svn st 
    M       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    ?       ungrab.sh
    epsilon:offline blyth$ 
    epsilon:offline blyth$ 
    epsilon:offline blyth$ svn diff Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    Index: Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    ===================================================================
    --- Examples/Tutorial/python/Tutorial/JUNODetSimModule.py	(revision 5223)
    +++ Examples/Tutorial/python/Tutorial/JUNODetSimModule.py	(working copy)
    @@ -1712,18 +1712,30 @@
     
         SWITCH = textwrap.dedent("""
     
    -    --pmt20inch-polycone-neck 
    +    FORMER OPTION --pmt20inch-polycone-neck IS NOW THE DEFAULT 
             Use economical polycone 20inch PMT neck shape replacing cylinder-torus.
     
    -    --pmt20inch-simplify-csg 
    +    FORMER OPTION --pmt20inch-simplify-csg IS NOW THE DEFAULT
             Simplify CSG modelling of 20inch PMTs, avoiding Inner_Separator anti-pattern, see HamamatsuR12860PMTManager + NNVTMCPPMTManager 
     
    +
         --additionacrylic-simplify-csg 
    -        Simplify CSG modelling used in AdditionAcrylicConstruction, avoiding CSG subtraction for daughters
    +        Simplify CSG modelling avoiding CSG subtraction for daughters, see AdditionAcrylicConstruction
     
    +
    +
    +    --pmt20inch-obsolete-torus-neck
    +        USE ONLY FOR DEBUGGING : Revert to the obsolete torus neck which has spurious intersects, bad performance and no Opticks support
    +
    +    --pmt20inch-profligate-tail-cut
    +        USE ONLY FOR DEBUGGING : Revert to profligate G4IntersectionSolid "cutting" that substantially adds complexity and breaks Opticks 
    +
         --debug-disable-sticks         
    -        Change CD geometry by skipping the sticks. USE ONLY FOR DEBUGGING, see LSExpDetectorConstruction::setupCentralDetector
    +        USE ONLY FOR DEBUGGING : Changes CD geometry by skipping the sticks, see LSExpDetectorConstruction::setupCentralDetector
     
    +    --pmt20inch-plus-dynode
    +        USE ONLY FOR DEBUGGING : Adds PMT dynode geometry even when not using new PMT optical model, eg to check dynode does not impinge
    +
         """)
     
         def register_SWITCH_options(self, group):
    epsilon:offline blyth$ 


No conflict::

    epsilon:offline blyth$ svn up
    Updating '.':
    At revision 5223.
    epsilon:offline blyth$ 
