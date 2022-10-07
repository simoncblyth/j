NTreeBalance_unable_to_balance
=================================


g4cx/tests/G4CXOpticks_setGeometry_Test.sh::

    export NTreeBalance__UnableToBalance_SIGINT=1

::

    frame #1: 0x00007fff5c3c7080 libsystem_pthread.dylib`pthread_kill + 333
    frame #2: 0x00007fff5c10a6fe libsystem_c.dylib`raise + 26
    frame #3: 0x000000010a18edb7 libNPY.dylib`NTreeBalance<nnode>::create_balanced(this=0x0000000112ef8ed0) at NTreeBalance.cpp:126
    frame #4: 0x000000010a19192b libNPY.dylib`NTreeProcess<nnode>::init(this=0x00007ffeefbf8450) at NTreeProcess.cpp:176
    frame #5: 0x000000010a19155c libNPY.dylib`NTreeProcess<nnode>::NTreeProcess(this=0x00007ffeefbf8450, root_=0x0000000112ef89c0, dump_=false) at NTreeProcess.cpp:131
    frame #6: 0x000000010a19140c libNPY.dylib`NTreeProcess<nnode>::NTreeProcess(this=0x00007ffeefbf8450, root_=0x0000000112ef89c0, dump_=false) at NTreeProcess.cpp:130
    frame #7: 0x000000010a190f6b libNPY.dylib`NTreeProcess<nnode>::Process(root_=0x0000000112ef89c0, soIdx=103, lvIdx=103) at NTreeProcess.cpp:87
    frame #8: 0x00000001004713ae libExtG4.dylib`X4PhysicalVolume::ConvertSolid_FromRawNode(ok=0x000000012f033600, lvIdx=103, soIdx=103, solid=0x000000010b9a5ff0, soname="solidXJfixture0x5931c90", lvname="lXJfixture0x5931eb0", balance_deep_tree=true, raw=0x0000000112ef89c0) at X4PhysicalVolume.cc:1163
    frame #9: 0x000000010047104c libExtG4.dylib`X4PhysicalVolume::ConvertSolid_(ok=0x000000012f033600, lvIdx=103, soIdx=103, solid=0x000000010b9a5ff0, soname="solidXJfixture0x5931c90", lvname="lXJfixture0x5931eb0", balance_deep_tree=true) at X4PhysicalVolume.cc:1141
    frame #10: 0x000000010047008d libExtG4.dylib`X4PhysicalVolume::ConvertSolid(ok=0x000000012f033600, lvIdx=103, soIdx=103, solid=0x000000010b9a5ff0, soname="solidXJfixture0x5931c90", lvname="lXJfixture0x5931eb0") at X4PhysicalVolume.cc:1039
    frame #11: 0x000000010046e955 libExtG4.dylib`X4PhysicalVolume::convertSolid(this=0x00007ffeefbfccc8, lv=0x000000011fb333a0) at X4PhysicalVolume.cc:984
    frame #12: 0x000000010046d875 libExtG4.dylib`X4PhysicalVolume::convertSolids_r(this=0x00007ffeefbfccc8, pv=0x000000011fb3c410, depth=6) at X4PhysicalVolume.cc:943
    frame #13: 0x000000010046d594 libExtG4.dylib`X4PhysicalVolume::convertSolids_r(this=0x00007ffeefbfccc8, pv=0x0000000121b17f20, depth=5) at X4PhysicalVolume.cc:937
    frame #14: 0x000000010046d594 libExtG4.dylib`X4PhysicalVolume::convertSolids_r(this=0x00007ffeefbfccc8, pv=0x0000000121b92020, depth=4) at X4PhysicalVolume.cc:937
    frame #15: 0x000000010046d594 libExtG4.dylib`X4PhysicalVolume::convertSolids_r(this=0x00007ffeefbfccc8, pv=0x0000000121be0930, depth=3) at X4PhysicalVolume.cc:937
    frame #16: 0x000000010046d594 libExtG4.dylib`X4PhysicalVolume::convertSolids_r(this=0x00007ffeefbfccc8, pv=0x0000000121be0980, depth=2) at X4PhysicalVolume.cc:937
    frame #17: 0x000000010046d594 libExtG4.dylib`X4PhysicalVolume::convertSolids_r(this=0x00007ffeefbfccc8, pv=0x0000000121be0c00, depth=1) at X4PhysicalVolume.cc:937
    frame #18: 0x000000010046d594 libExtG4.dylib`X4PhysicalVolume::convertSolids_r(this=0x00007ffeefbfccc8, pv=0x000000010b98d5b0, depth=0) at X4PhysicalVolume.cc:937
    frame #19: 0x000000010046895a libExtG4.dylib`X4PhysicalVolume::convertSolids(this=0x00007ffeefbfccc8) at X4PhysicalVolume.cc:895
    frame #20: 0x00000001004676a3 libExtG4.dylib`X4PhysicalVolume::init(this=0x00007ffeefbfccc8) at X4PhysicalVolume.cc:210
    frame #21: 0x000000010046731a libExtG4.dylib`X4PhysicalVolume::X4PhysicalVolume(this=0x00007ffeefbfccc8, ggeo=0x000000012f439190, top=0x000000010b98d5b0) at X4PhysicalVolume.cc:189
    frame #22: 0x00000001004664c5 libExtG4.dylib`X4PhysicalVolume::X4PhysicalVolume(this=0x00007ffeefbfccc8, ggeo=0x000000012f439190, top=0x000000010b98d5b0) at X4PhysicalVolume.cc:180
    frame #23: 0x0000000100461658 libExtG4.dylib`X4Geo::Translate(top=0x000000010b98d5b0) at X4Geo.cc:27
    frame #24: 0x0000000100100664 libG4CX.dylib`G4CXOpticks::setGeometry(this=0x00007ffeefbfe658, world=0x000000010b98d5b0) at G4CXOpticks.cc:218
    frame #25: 0x00000001001028fa libG4CX.dylib`G4CXOpticks::setGeometry(this=0x00007ffeefbfe658, gdmlpath="/tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/origin.gdml") at G4CXOpticks.cc:184
    frame #26: 0x0000000100101c24 libG4CX.dylib`G4CXOpticks::setGeometry(this=0x00007ffeefbfe658) at G4CXOpticks.cc:142
    frame #27: 0x000000010000fa34 G4CXOpticks_setGeometry_Test`main(argc=1, argv=0x00007ffeefbfe6f0) at G4CXOpticks_setGeometry_Test.cc:17



::

    2022-10-05 19:29:35.311 ERROR [22325129] [NTreeProcess<nnode>::init@181]  unable_to_balance treeidx 103 NTreeAnalyse::Desc 
    NTreeAnalyse height 6 count 17
                                                  un                    

                                          un                    in di    

                                  un        bo solidXJfixture_down30x5931120_box3          un        !bo solidXJfixture_up30x59319e0_box3

                          un        bo solidXJfixture_down30x5931120_box3            bo solidXJfixture_up10x5931660_box3    bo solidXJfixture_up20x5931700_box3        

                  un        bo solidXJfixture_down20x5930c60_box3                                        

        in solidXJfixture_down10x592de20_difference        bo solidXJfixture_down20x5930c60_box3                                                

    cy solidXJfixture_down10x592de20_outer    !cy solidXJfixture_down10x592de20_inner                                                        



Improve layout by using a separate list of the labels::

    2022-10-05 20:21:22.886 ERROR [22406264] [NTreeProcess<nnode>::init@181]  unable_to_balance treeidx 103 NTreeAnalyse::Desc 
    NTreeAnalyse height 6 count 17


       0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F   G

       .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .

                                                  un                    

                                          un                      in    

                                  un          bo          un         !bo

                          un          bo              bo      bo        

                  un          bo                                        

          in          bo                                                

      cy     !cy                                                        



       .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .

       0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F   G

       0 solidXJfixture_down10x592de20_outer
       1 solidXJfixture_down10x592de20_difference
       2 solidXJfixture_down10x592de20_inner
       3 un
       4 solidXJfixture_down20x5930c60_box3
       5 un
       6 solidXJfixture_down20x5930c60_box3
       7 un
       8 solidXJfixture_down30x5931120_box3
       9 un
       A solidXJfixture_down30x5931120_box3
       B un
       C solidXJfixture_up10x5931660_box3
       D un
       E solidXJfixture_up20x5931700_box3
       F di
       G solidXJfixture_up30x59319e0_box3





