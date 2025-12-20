Chenjing-EMFcoilsgeometry/observation
=========================================


TODO: improve on this by sourcing an optional file to config non-default settings
that might set the OJ_INITIALIZE_OPTION



Had to add option for non default tut_detsim commandline::


    (ok) A[blyth@localhost junosw]$ git diff 
    diff --git a/Examples/Tutorial/share/opticks_juno.sh b/Examples/Tutorial/share/opticks_juno.sh
    index 29c32255..ea63fec4 100644
    --- a/Examples/Tutorial/share/opticks_juno.sh
    +++ b/Examples/Tutorial/share/opticks_juno.sh
    @@ -30,6 +30,9 @@ oj_geomsetup()
        export OJ_PREFIX=$(dirname $(dirname $(realpath $BASH_SOURCE))) # one above bin dir
        export OJ_GEOMDIR=$OJ_PREFIX/.opticks/GEOM/${GEOM}
     
    +   export OJ_INITIALIZE_OPTION=--emf-coils-system   # NON default detsim option under test
    +
    +
        export ${GEOM}_CFBaseFromGEOM=${OJ_GEOMDIR}  ## for viz, eg CSGOptiXRenderInteractiveTest
        export CSGOptiXRenderInteractiveTest__FRAME_HOP=1
     
    @@ -162,6 +165,9 @@ oj_initialize_framespec()
     }
     
     
    +oj_initialize_option(){ echo ${OJ_INITIALIZE_OPTION} ; }
    +
    +
     oj_initialize_meshname_tessname()
     {
        : opticks_juno.sh
    @@ -170,7 +176,7 @@ oj_initialize_meshname_tessname()
     
        export G4CXOpticks__SaveGeometry_DIR=${OJ_GEOMDIR}
        export CSGFoundry__SAVE_OPT=meshname
    -   tut_detsim.py --opticks-mode 1 --evtmax 0 gun
    +   tut_detsim.py $(oj_initialize_option) --opticks-mode 1 --evtmax 0 gun
        unset CSGFoundry__SAVE_OPT
     
        local meshname=${OJ_GEOMDIR}/CSGFoundry/meshname.txt
    @@ -203,7 +209,7 @@ oj_initialize_geomdir()
     
        export G4CXOpticks__SaveGeometry_DIR=${OJ_GEOMDIR}
     
    -   tut_detsim.py --opticks-mode 1 --evtmax 0 gun
    +   tut_detsim.py $(oj_initialize_option) --opticks-mode 1 --evtmax 0 gun
     
        echo $FUNCNAME - ls -alst ${OJ_GEOMDIR}/CSGFoundry
        ls -alst ${OJ_GEOMDIR}/CSGFoundry
    (ok) A[blyth@localhost junosw]$ 


309 solids, 7 with duplicated name
----------------------------------

::

    (ok) A[blyth@localhost CSGFoundry]$ grep EMF meshname.txt | wc -l
    309

    (ok) A[blyth@localhost CSGFoundry]$ grep EMF meshname.txt | grep _0
    EMFholder_LShape_L127mm_0
    EMFholder_LShape_L1278mm_0
    EMFholder_LShape_L725mm_0
    EMFholder_LShape_L117mm_0
    EMFholder_LShape_L1235mm_0
    EMFholder_LShape_L1228mm_0
    EMFholder_LShape_L1120mm_0

    (ok) A[blyth@localhost CSGFoundry]$ grep EMF meshname.txt | grep _1
    EMFholder_LShape_L1278mm_1
    EMFholder_LShape_L127mm_1
    EMFholder_LShape_L1235mm_1
    EMFholder_LShape_L1228mm_1
    EMFholder_LShape_L1120mm_1
    EMFholder_LShape_L725mm_1
    EMFholder_LShape_L117mm_1



Overuse of icc
------------------

::

     744 // -----------------------------------------------------------------------------
     745 void WaterPoolConstruction::makeEMFSupport_LAngles()
     746 {
     747     // -------------------------------------------------------------------------
     748     // Tool lookup: LAngleConstruction / EMFsupport
     749     // -------------------------------------------------------------------------
     750     SniperPtr<DetSimAlg> detsimalg(*getParent(), "DetSimAlg");
     751     if (detsimalg.invalid()) {
     752         LogError << "[EMFsupport] Cannot load DetSimAlg." << std::endl;
     753         assert(0);
     754     }
     755 
     756     // Get tool instance and cast to LAngleConstruction
     757     ToolBase* tbase = detsimalg->findTool("EMFsupport");
     758     if (!tbase) {
     759         tbase = detsimalg->createTool("LAngleConstruction/EMFsupport");
     760         if (!tbase) {
     761             tbase = detsimalg->createTool("EMFsupport");
     762         }
     763     }
     764     if (!tbase) {
     765         LogError << "[EMFsupport] Cannot create/find tool 'EMFsupport'." << std::endl;
     766         assert(0);
     767     }
     768 
     769     auto* de  = dynamic_cast<IDetElement*>(tbase);
     770     auto* ltc = dynamic_cast<LAngleConstruction*>(tbase);
     771     if (!de || !ltc) {
     772         LogError << "[EMFsupport] tool 'EMFsupport' is not LAngleConstruction." << std::endl;
     773         assert(0);
     774     }
     775 
     776     if (!logicWaterPool) {
     777         LogError << "[EMFsupport] logicWaterPool is null." << std::endl;
     778         assert(0);
     779     }




