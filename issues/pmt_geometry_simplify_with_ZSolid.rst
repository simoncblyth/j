pmt_geometry_simplify_with_ZSolid
====================================


* hmm ZSolid and ZCanvas should be private headers, so change to .h to signify that 

::

    epsilon:PMTSim blyth$ ./grab_back.sh 
    cp /Users/blyth/j/PMTSim/HamamatsuR12860PMTManager.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
    cp /Users/blyth/j/PMTSim/Hamamatsu_R12860_PMTSolid.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/Hamamatsu_R12860_PMTSolid.hh
    cp /Users/blyth/j/PMTSim/NNVTMCPPMTManager.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
    cp /Users/blyth/j/PMTSim/NNVT_MCPPMT_PMTSolid.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/NNVT_MCPPMT_PMTSolid.hh
    cp /Users/blyth/j/PMTSim/ellipse_intersect_circle.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.cc
    cp /Users/blyth/j/PMTSim/ellipse_intersect_circle.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.hh
    cp /Users/blyth/j/PMTSim/HamamatsuR12860PMTManager.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    cp /Users/blyth/j/PMTSim/Hamamatsu_R12860_PMTSolid.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc
    cp /Users/blyth/j/PMTSim/NNVTMCPPMTManager.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    cp /Users/blyth/j/PMTSim/NNVT_MCPPMT_PMTSolid.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc
    cp ZSolid.h /Users/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/ZSolid.h
    cp ZSolid.cc /Users/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/ZSolid.cc
    cp ZCanvas.h /Users/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/ZCanvas.h
    epsilon:PMTSim blyth$ 


* DONE : STANDALONE is too generic, swited to PMTSIM_STANDALONE 

* TODO: replace python switches JUNO_PMT20INCH_POLYCONE_NECK -> JUNO_PMT20INCH_OBSOLETE_TORUS_NECK 



Smoking gan for the SEGV : somehow handling -ve args code got removed
------------------------------------------------------------------------

* result was memcpy Jackson Pollocking that causes crashes sometimes 

::

    inline void ZCanvas::_draw(int ix, int iy, int dx, int dy, const char* txt)   // 0,0 is at top left 
    {
    -    bool expect = ix < int(width) && iy < int(height) && dx < int(xscale) &&  dy < int(yscale) ; 
    +    if( ix < 0 ) ix += width ; 
    +    if( iy < 0 ) iy += height ;
    +    if( dx < 0 ) dx += xscale ; 
    +    if( dy < 0 ) dy += yscale ; 
    + 



Incorporation : switch on debug
--------------------------------- 

::

    N[blyth@localhost offline]$ JUNO_CMAKE_BUILD_TYPE=Debug ./build.sh 


Incorporation : ZSolid segv
-------------------------------------------


Switch back to Debug build::

    epsilon:PMTSim blyth$ OPTICKS_BUILDTYPE=Debug om-conf
    epsilon:PMTSim blyth$ om


::

    (lldb) f 3
    frame #3: 0x000000010011c9e3 libPMTSim.dylib`ZSolid::draw_r(this=0x0000000109300000, node_=0x00000001093000d0, mode=0) at ZSolid.cc:819
       816 	        double z0, z1 ; 
       817 	        ZRange(z0, z1, node);  
       818 	
    -> 819 	        canvas->draw(   ix, -1, 0,0,  zdelta ); 
       820 	        canvas->draw(   ix, -1, 0,2,  z1+zdelta ); 
       821 	        canvas->draw(   ix, -1, 0,3,  z0+zdelta ); 
       822 	    }
    (lldb) p ix
    (int) $1 = 0
    (lldb) p zdelta
    (double) $2 = 0
    (lldb) p z1
    (double) $3 = 190

    (lldb) f 2
    frame #2: 0x000000010011cc57 libPMTSim.dylib`ZCanvas::draw(this=0x0000000109301e00, ix=0, iy=-1, dx=0, dy=0, val=0) at ZCanvas.h:95
       92  	    assert( expect );
       93  	    if(!expect) exit(EXIT_FAILURE) ; 
       94  	
    -> 95  	    _draw(ix, iy, dx, dy, tmp); 
       96  	}
       97  	
       98  	inline void ZCanvas::drawch(int ix, int iy, int dx, int dy, char ch)  


    (lldb) f 1
    frame #1: 0x0000000100126667 libPMTSim.dylib`ZCanvas::_draw(this=0x0000000109301e00, ix=0, iy=-1, dx=0, dy=0, txt="0") at ZCanvas.h:134
       131 	        return ; 
       132 	    }
       133 	
    -> 134 	    memcpy( c + offset , txt, l );
       135 	}
       136 	
       137 	inline void ZCanvas::print(const char* msg) const 
    (lldb) 

    (lldb) p offset
    (int) $5 = -645
    (lldb) p txt
    (const char *) $6 = 0x00007ffeefbfde46 "0"
    (lldb) p l
    (int) $7 = 1
    (lldb) p c
    (char *) $8 = 0x0000000109800000 "                                                                                                                                \n                                                                                                                                \n                                                                                                                                \n                                                                                                                                \n                                                                                                                                \n                                                                                                                                \n                                                                                                                                \n                                                                                                                         "...
    (lldb) 




SEGV with Release build gives no symbols::

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x1097ffd7b)
      * frame #0: 0x00007fff7280bfe6 libsystem_platform.dylib`_platform_memmove$VARIANT$Haswell + 198
        frame #1: 0x00000001000e25af libPMTSim.dylib`ZCanvas::draw(int, int, int, int, int) + 207
        frame #2: 0x00000001000e235d libPMTSim.dylib`ZSolid::draw_r(G4VSolid const*, int) + 1517
        frame #3: 0x00000001000e1e07 libPMTSim.dylib`ZSolid::draw_r(G4VSolid const*, int) + 151
        frame #4: 0x00000001000e1e07 libPMTSim.dylib`ZSolid::draw_r(G4VSolid const*, int) + 151
        frame #5: 0x00000001000e1e07 libPMTSim.dylib`ZSolid::draw_r(G4VSolid const*, int) + 151
        frame #6: 0x00000001000e1e07 libPMTSim.dylib`ZSolid::draw_r(G4VSolid const*, int) + 151
        frame #7: 0x00000001000e1e07 libPMTSim.dylib`ZSolid::draw_r(G4VSolid const*, int) + 151
        frame #8: 0x00000001000e1e07 libPMTSim.dylib`ZSolid::draw_r(G4VSolid const*, int) + 151
        frame #9: 0x00000001000e1e07 libPMTSim.dylib`ZSolid::draw_r(G4VSolid const*, int) + 151
        frame #10: 0x00000001000db56d libPMTSim.dylib`ZSolid::draw(char const*, int) + 173
        frame #11: 0x000000010000af8f PMTSolidTest`main + 271
        frame #12: 0x00007fff724fa015 libdyld.dylib`start + 1
        frame #13: 0x00007fff724fa015 libdyld.dylib`start + 1
    (lldb) f 1
    frame #1: 0x00000001000e25af libPMTSim.dylib`ZCanvas::draw(int, int, int, int, int) + 207
    libPMTSim.dylib`ZCanvas::draw:
        0x1000e25af <+207>: jmp    0x1000e25d5               ; <+245>
        0x1000e25b1 <+209>: leaq   0x2a86f(%rip), %rdi       ; "ZCanvas::_draw error out of range x+l %d  nx %d  y %d ny %d \n"
        0x1000e25b8 <+216>: xorl   %eax, %eax
        0x1000e25ba <+218>: callq  0x10010017a               ; symbol stub for: printf
    (lldb) 




Incorporation : lots of unused variable warnings as assert is optimized away in Release mode 
-----------------------------------------------------------------------------------------------

Lots of ZSolid warnings because it looks like assert is being removed in Release mode.

* https://stackoverflow.com/questions/22140520/how-to-enable-assert-in-cmake-release-mode

Manage to reproduce many of the warnings in standalone j/PMTSim with::

    epsilon:PMTSim blyth$ OPTICKS_BUILDTYPE=Release om-conf
    epsilon:PMTSim blyth$ touch ZSolid.cc ; om



Incorporation : Runtime fail after adding new sources
--------------------------------------------------------

::

    [Ellipse_Intersect_Circle 
    ]Ellipse_Intersect_Circle (  139.6247,  -158.1783) 
    [ ZSolid::ApplyZCutTree zcut    183.225 pmt_delta      0.001 body_delta     -4.999 inner_delta     -5.000 zcut+pmt_delta    183.226 zcut+body_delta    178.226 zcut+inner_delta    178.225
    /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python: symbol lookup error: /data/blyth/junotop/offline/InstallArea/lib64/libPMTSim.so: undefined symbol: _ZN6ZSolid13ApplyZCutTreeEPK8G4VSoliddb
    [Inferior 1 (process 434128) exited with code 0177]


This is because offline PKG uses dirty listing of sources so CMake cannot detect added source files at make time, 
have to manually configure again in order for CMake to notice that there are new sources.




Review of Code Changes (using eg "jdiff Hamamatsu_R12860_PMTSolid")
----------------------------------------------------------------------

Hamamatsu_R12860_PMTSolid and NNVT_MCPPMT_PMTSolid

    Polycone neck now becomes the default, old obsolete torus neck can be 
    still be used via python option.  

    1. add ability to be compiled standalone with macro -DPMTSIM_STANDALONE 

    2. replace m_polycone_neck with the converse m_obsolete_torus_neck 

    3. factorize out methods : construct_polycone_neck construct_obsolete_torus_neck


HamamatsuR12860PMTManager and NNVTMCPPMTManager

    1. add ability to be compiled standalone with macro -DPMTSIM_STANDALONE 

    2. add debug interface providing access to consituent solids and volumes 

    3. add m_plus_dynode and m_profligate_tail_cut

    4. add member m_pmt_equator_to_bottom to allow splitting into methods

    5. reorganize helper_make_solid using ZSolid cutting 









TODO:

* review the code changes 

* add the python switches to control these:: 

  1. JUNO_PMT20INCH_PROFLIGATE_TAIL_CUT


* PMT geometry changes are not only relevant to opticks running 

  * so first check without opticks in the build  
  * :doc:`../docs/offline_opticks_cmake_usage`









