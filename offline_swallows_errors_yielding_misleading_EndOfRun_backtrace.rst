offline_swallows_errors_yielding_misleading_EndOfRun_backtrace
================================================================





::

    2021-06-14 20:05:29.371 ERROR [338836] [X4MaterialTable::init@117] PROCEEDING TO convert material with no mpt Aluminium
    2021-06-14 20:05:29.371 ERROR [338836] [X4MaterialTable::init@117] PROCEEDING TO convert material with no mpt Galactic
    2021-06-14 20:05:29.372 INFO  [338836] [X4PhysicalVolume::convertMaterials@303]  used_materials.size 17 num_material_with_efficiency 0
    2021-06-14 20:05:29.372 INFO  [338836] [GMaterialLib::dumpSensitiveMaterials@1230] X4PhysicalVolume::convertMaterials num_sensitive_materials 0
    2021-06-14 20:05:29.376 INFO  [338836] [X4PhysicalVolume::convertImplicitSurfaces_r@397]  parent_mtName Rock daughter_mtName Air
    2021-06-14 20:05:29.376 INFO  [338836] [X4PhysicalVolume::convertImplicitSurfaces_r@402]  RINDEX_NoRINDEX 1 NoRINDEX_RINDEX 0 pv1                       pExpHall pv2                       pTopRock bs 0 no-prior-border-surface-adding-implicit 
    Traceback (most recent call last):
      File "/home/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/home/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: basic_string::_S_construct null not valid
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully

    Program received signal SIGSEGV, Segmentation fault.
    0x00007fffce076ce8 in G4OpticksRecorder::EndOfRunAction (this=0x25257d0, run=0x0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:80
    80	    m_manager->EndOfRunAction(run); 
    (gdb) bt
    #0  0x00007fffce076ce8 in G4OpticksRecorder::EndOfRunAction (this=0x25257d0, run=0x0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:80
    #1  0x00007fffc0679640 in G4OpticksAnaMgr::EndOfRunAction (this=0x2525730, run=0x0) at ../src/G4OpticksAnaMgr.cc:30
    #2  0x00007fffc1e02160 in MgrOfAnaElem::EndOfRunAction (this=0x7fffc200d440 <MgrOfAnaElem::instance()::s_mgr>, run=0x0) at ../src/MgrOfAnaElem.cc:39
    #3  0x00007fffc264e6b2 in LSExpRunAction::EndOfRunAction (this=0x3249f40, aRun=0x0) at ../src/LSExpRunAction.cc:73
    #4  0x00007fffce2cb91d in G4RunManager::RunTermination() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4run.so
    #5  0x00007fffc289a7f9 in G4SvcRunManager::finalizeRM() () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #6  0x00007fffc1dfab91 in DetSimAlg::finalize (this=0x250d1b0) at ../src/DetSimAlg.cc:136
    #7  0x00007fffef12d745 in DleSupervisor::finalize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #8  0x00007fffef13810d in Task::finalize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #9  0x00007fffef13e111 in TaskWatchDog::finalize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so




Using geocache-create can find the problem location because the error is not caught and hidden::


    2021-06-14 13:54:28.059 INFO  [5443730] [X4PhysicalVolume::convertImplicitSurfaces_r@397]  parent_mtName Rock daughter_mtName Air
    2021-06-14 13:54:28.059 INFO  [5443730] [X4PhysicalVolume::convertImplicitSurfaces_r@402]  RINDEX_NoRINDEX 1 NoRINDEX_RINDEX 0 pv1              pExpHall0x32b9fa0 pv2              pTopRock0x32b9af0 bs 0x0 no-prior-border-surface-adding-implicit 
    Process 15155 stopped
    * thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x0)
        frame #0: 0x00007fff64338232 libsystem_c.dylib`strlen + 18
    libsystem_c.dylib`strlen:
    ->  0x7fff64338232 <+18>: pcmpeqb (%rdi), %xmm0
        0x7fff64338236 <+22>: pmovmskb %xmm0, %esi
        0x7fff6433823a <+26>: andq   $0xf, %rcx
        0x7fff6433823e <+30>: orq    $-0x1, %rax
    Target 0: (OKX4Test) stopped.

    Process 15155 launched: '/usr/local/opticks/lib/OKX4Test' (x86_64)
    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x0)
      * frame #0: 0x00007fff64338232 libsystem_c.dylib`strlen + 18
        frame #1: 0x00000001097e7c55 libGGeo.dylib`std::__1::char_traits<char>::length(__s=0x0000000000000000) at __string:215
        frame #2: 0x00000001098ec067 libGGeo.dylib`GSurfaceLib::addBorderSurface(GPropertyMap<float>*, char const*, char const*, bool) [inlined] std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::basic_string(this="", __s=0x0000000000000000) at string:1547
        frame #3: 0x00000001098ec02f libGGeo.dylib`GSurfaceLib::addBorderSurface(GPropertyMap<float>*, char const*, char const*, bool) [inlined] std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::basic_string(this="", __s=0x0000000000000000) at string:1545
        frame #4: 0x00000001098ec003 libGGeo.dylib`GSurfaceLib::addBorderSurface(this=0x00000001140d20b0, surf=0x0000000114746470, pv1=0x0000000000000000, pv2=0x0000000000000000, direct=false) at GSurfaceLib.cc:367
        frame #5: 0x00000001098ebf59 libGGeo.dylib`GSurfaceLib::add(this=0x00000001140d20b0, raw=0x0000000114746470, implicit=true) at GSurfaceLib.cc:352
        frame #6: 0x00000001098efe78 libGGeo.dylib`GSurfaceLib::addImplicitBorderSurface_RINDEX_NoRINDEX(this=0x00000001140d20b0, pv1="pExpHall0x32b9fa0", pv2="pTopRock0x32b9af0") at GSurfaceLib.cc:747
        frame #7: 0x00000001037f9806 libExtG4.dylib`X4PhysicalVolume::convertImplicitSurfaces_r(this=0x00007ffeefbfc610, parent_pv=0x00000001248a4ab0, depth=1) at X4PhysicalVolume.cc:414
        frame #8: 0x00000001037f9826 libExtG4.dylib`X4PhysicalVolume::convertImplicitSurfaces_r(this=0x00007ffeefbfc610, parent_pv=0x000000010e973340, depth=0) at X4PhysicalVolume.cc:418
        frame #9: 0x00000001037f740b libExtG4.dylib`X4PhysicalVolume::convertSurfaces(this=0x00007ffeefbfc610) at X4PhysicalVolume.cc:452
        frame #10: 0x00000001037f689f libExtG4.dylib`X4PhysicalVolume::init(this=0x00007ffeefbfc610) at X4PhysicalVolume.cc:187
        frame #11: 0x00000001037f658c libExtG4.dylib`X4PhysicalVolume::X4PhysicalVolume(this=0x00007ffeefbfc610, ggeo=0x00000001140cf130, top=0x000000010e973340) at X4PhysicalVolume.cc:172
        frame #12: 0x00000001037f56e5 libExtG4.dylib`X4PhysicalVolume::X4PhysicalVolume(this=0x00007ffeefbfc610, ggeo=0x00000001140cf130, top=0x000000010e973340) at X4PhysicalVolume.cc:163
        frame #13: 0x0000000100015717 OKX4Test`main(argc=10, argv=0x00007ffeefbfce20) at OKX4Test.cc:108
        frame #14: 0x00007fff642e8015 libdyld.dylib`start + 1
    (lldb) f 7
    frame #7: 0x00000001037f9806 libExtG4.dylib`X4PhysicalVolume::convertImplicitSurfaces_r(this=0x00007ffeefbfc610, parent_pv=0x00000001248a4ab0, depth=1) at X4PhysicalVolume.cc:414
       411 	
       412 	            if( bs == nullptr )
       413 	            {
    -> 414 	                m_slib->addImplicitBorderSurface_RINDEX_NoRINDEX(pv1, pv2); 
       415 	            }
       416 	           
       417 	        } 
    (lldb) p pv1
    (const char *) $0 = 0x0000000114744db0 "pExpHall0x32b9fa0"
    (lldb) p pv2
    (const char *) $1 = 0x0000000114745b70 "pTopRock0x32b9af0"
    (lldb) f 6
    frame #6: 0x00000001098efe78 libGGeo.dylib`GSurfaceLib::addImplicitBorderSurface_RINDEX_NoRINDEX(this=0x00000001140d20b0, pv1="pExpHall0x32b9fa0", pv2="pTopRock0x32b9af0") at GSurfaceLib.cc:747
       744 	    addPerfectProperties(bs, detect_, absorb_, reflect_specular_ , reflect_diffuse_ ); 
       745 	


