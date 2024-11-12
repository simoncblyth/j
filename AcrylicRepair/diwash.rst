Hi Diwash, Ziyan, Akira, 

Ziyan mentioned the G4MultiUnion issue that I observed with Geant4 10.4.2

The FastenerAcrylicConstruction solid (part of the support sticks) 
has 8 cylindrical screws plus a tube (cylinder with non-zero rmin). 
For convenience of Opticks translation I tried using a G4MultiUnion 
for the screws and combining that into a union with the tube.
That initially appears to work and can be polygonized
and is convenient for translation into Opticks list-node direct 
from the G4MultiUnion.

However, when running a simulation with input photons I immediately 
get a SIGSEGV from G4Voxelizer::GetCandidatesVoxelArray coming 
from the G4MultiUnion within the G4UnionSolid. 

::

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc651c260 in G4Voxelizer::GetCandidatesVoxelArray(CLHEP::Hep3Vector const&, std::vector<int, std::allocator<int> >&, G4SurfBits*) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    (gdb) bt
    #0  0x00007fffc651c260 in G4Voxelizer::GetCandidatesVoxelArray(CLHEP::Hep3Vector const&, std::vector<int, std::allocator<int> >&, G4SurfBits*) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #1  0x00007fffc644f3d0 in G4MultiUnion::InsideWithExclusion(CLHEP::Hep3Vector const&, G4SurfBits*) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #2  0x00007fffc644742d in G4DisplacedSolid::Inside(CLHEP::Hep3Vector const&) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #3  0x00007fffc6455e37 in G4UnionSolid::Inside(CLHEP::Hep3Vector const&) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #4  0x00007fffc641cbc3 in G4Navigator::LocateGlobalPointAndSetup(CLHEP::Hep3Vector const&, CLHEP::Hep3Vector const*, bool, bool) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #5  0x00007fffc77b8ccb in G4Transportation::PostStepDoIt(G4Track const&, G4Step const&) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #6  0x00007fffcc0ab679 in G4SteppingManager::InvokePSDIP(unsigned long) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #7  0x00007fffcc0aba7b in G4SteppingManager::InvokePostStepDoItProcs() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffcc0a92b4 in G4SteppingManager::Stepping() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffcc0b487f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffcc0f056d in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #11 0x00007fffbe3f568e in G4SvcRunManager::SimulateEvent (this=0x6554510, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #12 0x00007fffbdabdd3e in DetSimAlg::execute (this=0x6c046d0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112


Due to this issue I am implementing a way for the Opticks translation 
to create a geometry with the list-node without needing the 
G4MultiUnion in the source geometry. All that is needed is 
changing the names of the primitives to be included into 
the listnode to contain a hint string.  



Geant4 handles complex geometry much better using separate volumes 
rather than with with complex solids. 

Constructive solid geometry, the technique behind Geant4 solids can easily 
be misused leading to poor performance and incorrect intersects. 
Unfortunately boolean abuse is extremely common in Geant4 geometries.

To find an intersect with a CSG solid often requires finding intersects with all 
of its constituents as well as traversing all the operator nodes. 
G4MultiUnion helps by eliminating lots of operator nodes. 
But it is almost certainly not going to be as fast as using separate volumes, 
because those give more information for the voxelization which allows
getting to the intersect faster because many intersects can be skipped.  

Look at the forum, you will see many expressing the same experience. 
For example "evc" advises to use separate volumes rather than complex solids, 
even G4MultiUnion.

* https://geant4-forum.web.cern.ch/search?q=G4MultiUnion
* https://geant4-forum.web.cern.ch/t/creating-a-g4unionsolid-with-10-different-components/9906/7

Regarding the plan in your slides

* https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/ShowDocument?docid=12624

I suggest that you implement cracks and repairs using separate volumes. 
In addition you could also implement using G4MultiUnion and compare
performance plus check if you meet the issue I did above with the G4MultiUnion.

In your backup you mention "Reuse SJCLS Anchors" and 
"May cause hierarchical issues". Could you elaborate ? 
How/why reuse them ? 

Simon







Greetings,

Thank you so much for the advise. Yes, indeed I can see multiple instances where people emphasize using separate volumes instead of union and multiunion in the Geant4 forum. I am now trying to implement the cracks using separate volumes for the inner surface. acrylic being the mother volume can be done easily.

But I am still divided on how to implement on the outer surface where I have to place the inverted-cones in acrylic but a portion of the cones' base will extend out to the waterpool because of spherical shell and planar base of cone. What will be the efficient approach to carryout this in your view.

And regarding the "hierarchical issues" that I wrote, it was my belief looking into the geometry that SJCLS anchors are the daughter volume of LS but we need to place it out of LS into Acrylic vessel. That means we just can't use the hierarchy as is but needs climbing up one level of hierarchy. I cold be wrong, haven't gone deep into that route.

I am very new to this and still learning, appreciate your help.
Have a great day. 

Sincerely, 
Diwash




