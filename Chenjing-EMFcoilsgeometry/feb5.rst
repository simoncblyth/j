feb5
=====

Comments
---------

* your commit messages are uninformative, all having the form "Update 5 files".
  In future please provide a brief one sentence description of the changes made.
  If there are too many changes to describe in one sentence, then you should split
  your commits to make that possible.



There is only one reflectivity, so why do you need the below.
There is no need for the cache or the singleton, just create one in your
WaterPoolConstucionEMF ctor. Also no need for 4 energy points as the
reflectivity is flat with energy.  You just need 2 : 1.55eV, 15.5eV::


    294 static G4OpticalSurface* CreateEMFSteelSurfaceSingleton()
    295 {
    296     const int key = static_cast<int>(std::lround(g_emf_reflectivity * 1000.0));
    297 
    298     static std::map<int, G4OpticalSurface*> cache;
    299     auto it = cache.find(key);
    300     if (it != cache.end()) return it->second;
    301 
    302     LogInfo << "[EMF][Optical] Create EMFSteelOpticalSurface (cache miss): "
    303             << "reflectivity=" << g_emf_reflectivity
    304             << ", key=" << key
    305             << std::endl;
    306 
    307     auto* optSurface = new G4OpticalSurface(
    308         ("EMFSteelOpticalSurface_R" + std::to_string(key)).c_str()
    309     );
    310     optSurface->SetModel(unified);
    311     optSurface->SetType(dielectric_metal);
    312     optSurface->SetFinish(ground);
    313     optSurface->SetSigmaAlpha(0.2);
    314 
    315     auto* mpt = new G4MaterialPropertiesTable();
    316     const int N = 4;
    317     double E[N] = { 1.55 * eV, 6.20 * eV, 10.33 * eV, 15.5 * eV };
    318     double R[N] = { g_emf_reflectivity, g_emf_reflectivity, g_emf_reflectivity, g_emf_reflectivity };
    319     mpt->AddProperty("REFLECTIVITY", E, R, N);
    320     optSurface->SetMaterialPropertiesTable(mpt);
    321 
    322     cache[key] = optSurface;
    323     return optSurface;
    324 }





Names
------

::

    (ok) A[blyth@localhost CSGFoundry]$ grep EMF meshname.txt  | wc -l
    119

    (ok) A[blyth@localhost CSGFoundry]$ echo 23+9+87 | bc
    119


    (ok) A[blyth@localhost CSGFoundry]$ grep EMFsupport meshname.txt 
    s_EMFsupport_ring1
    s_EMFsupport_ring2
    ...
    s_EMFsupport_ring22
    s_EMFsupport_ring23
    (ok) A[blyth@localhost CSGFoundry]$ grep EMFsupport meshname.txt  | wc -l
    23


    (ok) A[blyth@localhost CSGFoundry]$ grep EMF_bar meshname.txt 
    s_EMF_bar_box_810mm
    s_EMF_bar_box_920mm
    s_EMF_bar_box_930mm
    s_EMF_bar_box_900mm
    s_EMF_bar_box_890mm
    s_EMF_bar_box_880mm
    s_EMF_bar_box_860mm
    s_EMF_bar_box_760mm
    s_EMF_bar_box_830mm
    (ok) A[blyth@localhost CSGFoundry]$ grep EMF_bar meshname.txt  | wc -l
    9



    (ok) A[blyth@localhost CSGFoundry]$ grep EMFcoil_holder meshname.txt
    s_EMFcoil_holder_ring1_seg1
    s_EMFcoil_holder_ring2_seg1
    s_EMFcoil_holder_ring3_seg1
    s_EMFcoil_holder_ring4_seg1
    s_EMFcoil_holder_ring5_seg1
    s_EMFcoil_holder_ring6_seg1
    s_EMFcoil_holder_ring7_seg1

    s_EMFcoil_holder_ring8_seg1
    s_EMFcoil_holder_ring8_seg2
    s_EMFcoil_holder_ring8_seg3

    s_EMFcoil_holder_ring9_seg1
    s_EMFcoil_holder_ring9_seg2
    s_EMFcoil_holder_ring9_seg3
    s_EMFcoil_holder_ring9_seg4
    s_EMFcoil_holder_ring9_seg5

    s_EMFcoil_holder_ring10_seg1
    s_EMFcoil_holder_ring10_seg2
    s_EMFcoil_holder_ring10_seg3

    s_EMFcoil_holder_ring11_seg1
    s_EMFcoil_holder_ring11_seg2
    s_EMFcoil_holder_ring11_seg3
    s_EMFcoil_holder_ring11_seg4
    s_EMFcoil_holder_ring11_seg5

    s_EMFcoil_holder_ring12_seg1
    s_EMFcoil_holder_ring12_seg2
    s_EMFcoil_holder_ring12_seg3
    s_EMFcoil_holder_ring12_seg4
    s_EMFcoil_holder_ring12_seg5

    s_EMFcoil_holder_ring13_seg1
    s_EMFcoil_holder_ring13_seg2
    s_EMFcoil_holder_ring13_seg3
    s_EMFcoil_holder_ring13_seg4
    s_EMFcoil_holder_ring13_seg5

    s_EMFcoil_holder_ring14_seg1
    s_EMFcoil_holder_ring14_seg2
    s_EMFcoil_holder_ring14_seg3

    s_EMFcoil_holder_ring15_seg1

    s_EMFcoil_holder_ring16_seg1
    s_EMFcoil_holder_ring16_seg2
    s_EMFcoil_holder_ring16_seg3
    s_EMFcoil_holder_ring16_seg4
    s_EMFcoil_holder_ring16_seg5

    s_EMFcoil_holder_ring17_seg1

    s_EMFcoil_holder_ring18_seg1
    s_EMFcoil_holder_ring18_seg2
    s_EMFcoil_holder_ring18_seg3
    s_EMFcoil_holder_ring18_seg4

    s_EMFcoil_holder_ring19_seg1
    s_EMFcoil_holder_ring19_seg2
    s_EMFcoil_holder_ring19_seg3

    s_EMFcoil_holder_ring20_seg1
    s_EMFcoil_holder_ring20_seg2
    s_EMFcoil_holder_ring20_seg3

    s_EMFcoil_holder_ring21_seg1
    s_EMFcoil_holder_ring21_seg2
    s_EMFcoil_holder_ring21_seg3

    s_EMFcoil_holder_ring22_seg1
    s_EMFcoil_holder_ring22_seg2
    s_EMFcoil_holder_ring22_seg3

    s_EMFcoil_holder_ring23_seg1
    s_EMFcoil_holder_ring23_seg2
    s_EMFcoil_holder_ring23_seg3

    s_EMFcoil_holder_ring24_seg1
    s_EMFcoil_holder_ring24_seg2
    s_EMFcoil_holder_ring24_seg3

    s_EMFcoil_holder_ring25_seg1
    s_EMFcoil_holder_ring25_seg2
    s_EMFcoil_holder_ring25_seg3
    s_EMFcoil_holder_ring25_seg4

    s_EMFcoil_holder_ring26_seg1
    s_EMFcoil_holder_ring26_seg2

    s_EMFcoil_holder_ring27_seg1
    s_EMFcoil_holder_ring27_seg2
    s_EMFcoil_holder_ring27_seg3

    s_EMFcoil_holder_ring28_seg1
    s_EMFcoil_holder_ring29_seg1

    s_EMFcoil_holder_ring30_seg1
    s_EMFcoil_holder_ring30_seg2
    s_EMFcoil_holder_ring30_seg3

    s_EMFcoil_holder_ring31_seg1
    s_EMFcoil_holder_ring31_seg2
    s_EMFcoil_holder_ring31_seg3

    s_EMFcoil_holder_ring32_seg1
    s_EMFcoil_holder_ring32_seg2
    s_EMFcoil_holder_ring32_seg3
    s_EMFcoil_holder_ring32_seg4
    s_EMFcoil_holder_ring32_seg5


    (ok) A[blyth@localhost CSGFoundry]$ grep EMFcoil_holder meshname.txt | wc -l
    87




Python
-------

::

    2267         # === Wire EMF coils System into WaterPoolConstruction ===
    2268         wp = sim_conf.tool("WaterPoolConstruction")
    2269         wp.property("EMFcoilsSystem").set(args.emf_coils_system_enabled)
    2270         wp.property("EMFSupportBars").set(args.emf_support_bars_enabled)
    2271 
    2272         # === Wire EMF steel reflectivity into WaterPoolConstruction ===
    2273         wp.property("EMFSteelReflectivity").set(args.emf_steel_reflectivity)
    2274 




::

    A[blyth@localhost junosw]$ cat InstallArea/Chenjing-EMFcoilsgeometry/local_envset.sh
    #  InstallArea/Chenjing-EMFcoilsgeometry/local_envset.sh
    #
    # OJ Opticks+JUNOSW installations include an envset.sh file
    # within the top level of the installation prefix.
    # The oj_initialize.sh from the top level of the source tree
    # sources the envset.sh and if it exists the local_envset.sh 
    # sibling to the envset.sh.
    #
    # NB local_envset.sh settings are because they are not part of
    # the installation local and temporary changes to the geometry.
    # Once settings have been decided they need to be added 
    # to the opticks_juno.sh repository file in order for the 
    # settings to become a standard part of the geometry.
    # 
    #
    ## settings for Chenjing-EMFcoilsgeometry branch with EMF enabled
    export OJ_INITIALIZE_TUT_DETSIM_OPTION="--emf-coils-system --emf-support-bars"

    ## even when using triangulated for the phicut solids
    ## the below analytic settings are still
    ## needed to avoid asserts from the conversion

    export U4Polycone__ENABLE_PHICUT=1
    export sn__PhiCut_PACMAN_ALLOWED=1


    export U4Mesh__NumberOfRotationSteps_solidName_STARTING_pfx_0=s_EMFcoil_holder_ring
    export U4Mesh__NumberOfRotationSteps_solidName_STARTING_val_0=480

    export U4Mesh__NumberOfRotationSteps_solidName_STARTING_pfx_1=s_EMFsupport_ring
    export U4Mesh__NumberOfRotationSteps_solidName_STARTING_val_1=480


    ##############################################
    ## logging controls are better to not commit
    export U4Mesh__NumberOfRotationSteps_DUMP=1
    #unset U4Mesh__NumberOfRotationSteps_DUMP

    A[blyth@localhost junosw]$ 


