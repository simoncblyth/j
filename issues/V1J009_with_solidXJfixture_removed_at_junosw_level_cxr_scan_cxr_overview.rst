V1J009_with_solidXJfixture_removed_at_junosw_level_cxr_scan_cxr_overview
===========================================================================

V1J009 created with *ntds2_noxj*::

    ntds_noxj()
    {
       #local gpfx=R           # R:Release builds of junosw+custom4   
       local gpfx=V          # V:Debug builds of junosw+custom4  
       GPFX=${GPFX:-$gpfx}    # need to match with j/ntds/ntds.sh  AGEOM, BGEOM

       export EVTMAX=1

       NOXJ=1 GEOM=${GPFX}1J009 OPTICKS_INTEGRATION_MODE=${OPTICKS_INTEGRATION_MODE:-0} ntds 

       ## HMM: INPUT PHOTONS WILL NOT WORK IN OPTICKS MODE 0 HOW AND WHERE TO RAISE AN ERROR FOR THAT ?
    }

    ntds0_noxj(){ OPTICKS_INTEGRATION_MODE=0 ntds_noxj ; }
    ntds2_noxj(){ OPTICKS_INTEGRATION_MODE=2 ntds_noxj ; }


Via NOXJ this geometry skips the xj fixture::

      t ntds

      case ${NOXJ:-0} in 
      0)
          opts="$opts"
      ;;
      1)
          opts="$opts --debug-disable-xj"
      ;;
      esac;




presentation of scan renders in image grids
----------------------------------------------

::

    epsilon:opticks blyth$ mdfind image_grid.sh
    /Users/blyth/env/presentation/opticks_20220329_progress_towards_production.txt
    /Users/blyth/env/presentation/opticks_20220329_progress_towards_production_TALK.txt
    /Users/blyth/simoncblyth.bitbucket.io/env/presentation/opticks_20220329_progress_towards_production.html
    /Users/blyth/simoncblyth.bitbucket.io/env/presentation/opticks_20220329_progress_towards_production.txt
    /Users/blyth/opticks/CSGOptiX/image_grid.sh
    /Users/blyth/opticks/CSGOptiX/openline.sh
    /Users/blyth/env/doc/image_grid.py
    /Users/blyth/env/presentation/image_grid.sh


For cxr_view.sh scan_elv reate a manual list of 9 jpg with visible diffs::

    vi $HOME/j/issues/scan_elv_jpg_select.txt  ## manually prepare list of 9 jpg with visible diffs
    export JPGLIST=$HOME/j/issues/scan_elv_jpg_select.txt
    open -n $(cat $JPGLIST)
    cx
    JPGLIST=$JPGLIST ./image_grid.sh 


    cx 
    JPGLIST=$HOME/j/issues/scan_emm_jpg_select.txt ./image_grid.sh 



cxr_view elv exclusions
------------------------

Other than the targetting fail when exclude 131 sWaterTube (which gives blank render) not much variation in render times

Notice that lots of the exclusions are changing geometry that is not visible from that viewpoint, so the 
level of variation (~10%) gives some idea of reproducibility with essentially the same geometry::

    N[blyth@localhost CSGOptiX]$ ./cxr_scan.sh 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t0_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0105 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t1_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0104 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t2_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t3_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t4_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t5_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0101 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t6_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t7_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t8_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t9_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t10_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t11_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t12_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0101 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t13_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t14_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t15_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0099 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t16_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0146 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t17_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0099 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t18_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t19_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t20_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0108 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t21_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t22_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0099 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t23_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t24_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t25_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0104 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t26_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t27_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t28_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t29_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t30_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t31_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t32_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0101 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t33_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0111 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t34_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t35_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t36_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t37_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t38_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t39_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t40_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t41_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t42_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t43_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t44_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0114 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t45_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t46_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0113 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t47_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0113 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t48_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0113 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t49_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0111 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t50_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t51_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t52_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t53_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t54_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t55_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0112 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t56_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t57_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t58_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0099 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t59_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t60_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t61_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t62_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0112 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t63_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t64_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0101 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t65_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t66_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0111 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t67_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0101 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t68_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t69_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t70_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t71_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t72_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t73_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t74_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t75_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t76_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0111 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t77_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0111 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t78_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0102 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t79_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0106 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t80_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t81_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t82_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t83_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t84_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t85_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t86_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t87_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t88_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t89_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t90_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0099 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t91_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0117 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t92_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t93_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t94_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0108 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t95_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0111 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t96_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0118 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t97_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t98_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0101 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t99_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t100_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t101_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t102_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0097 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t103_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0108 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t104_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0099 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t105_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t106_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t107_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t108_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t109_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t110_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t111_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0097 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t112_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0097 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t113_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t114_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0097 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t115_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0106 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t116_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t117_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t118_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0099 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t119_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t120_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0097 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t121_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0097 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t122_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0102 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t123_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t124_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t125_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t126_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t127_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t128_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t129_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t130_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 

    CSGFoundry::getMeshPrim@1824:  midx 131 mord 0 select_prim.size 0 mord_in_range 0
    CSGTarget::getInstanceTransform@365: Foundry::getMeshPrim failed for (midx mord) (131 0)
    CSGTarget::getGlobalCenterExtent@263:  failed to get InstanceTransform (midx mord iidx) (131 0 0)
    CSGTarget::getGlobalCenterExtent@266:  failed Tran<double>::Invert 
    CSGFoundry::getFrame@3093: Failed to lookup frame with frs [sWaterTube] looks_like_moi 1

    CSGFoundry::getMeshPrim@1824:  midx 131 mord 0 select_prim.size 0 mord_in_range 0
    CSGTarget::getInstanceTransform@365: Foundry::getMeshPrim failed for (midx mord) (131 0)
    CSGTarget::getGlobalCenterExtent@263:  failed to get InstanceTransform (midx mord iidx) (131 0 0)
    CSGTarget::getGlobalCenterExtent@266:  failed Tran<double>::Invert 
    CSGFoundry::getFrame@3093: Failed to lookup frame with frs [sWaterTube] looks_like_moi 1

    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t131_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0029 1:TITAN_RTX 

    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t132_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0094 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t133_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0104 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t134_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0099 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t135_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t136_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0100 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t137_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t138_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t139_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t140_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t141_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0109 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t142_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0098 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t143_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0125 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t144_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    V1J009/CSGOptiXRenderTest/CVD1/70000/sWaterTube/scan-elv/cxr_view_emm_t0_elv_t145_eye_-1,-1,-1,1__zoom_1__tmin_0.4__sWaterTube.jpg :     0.0110 1:TITAN_RTX 
    N[blyth@localhost CSGOptiX]$ 


Targetting issue when excluding 131 which is sWaterTube::

    epsilon:CSGOptiX blyth$ ~/opticks/bin/lvn.sh 131
    /Users/blyth/.opticks/GEOM/V1J009/CSGFoundry/meshname.txt
    131  132  sWaterTube





cxr_overview elv exclusions
----------------------------

Now much variation with elv exclusions::

    N[blyth@localhost CSGOptiX]$ ./cxr_scan.sh 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t0_moi__ALL.jpg :     0.0105 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t1_moi__ALL.jpg :     0.0082 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t2_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t3_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t4_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t5_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t6_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t7_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t8_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t9_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t10_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t11_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t12_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t13_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t14_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t15_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t16_moi__ALL.jpg :     0.0100 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t17_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t18_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t19_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t20_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t21_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t22_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t23_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t24_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t25_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t26_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t27_moi__ALL.jpg :     0.0108 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t28_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t29_moi__ALL.jpg :     0.0088 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t30_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t31_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t32_moi__ALL.jpg :     0.0085 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t33_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t34_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t35_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t36_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t37_moi__ALL.jpg :     0.0079 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t38_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t39_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t40_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t41_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t42_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t43_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t44_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t45_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t46_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t47_moi__ALL.jpg :     0.0082 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t48_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t49_moi__ALL.jpg :     0.0086 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t50_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t51_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t52_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t53_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t54_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t55_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t56_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t57_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t58_moi__ALL.jpg :     0.0096 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t59_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t60_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t61_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t62_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t63_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t64_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t65_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t66_moi__ALL.jpg :     0.0086 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t67_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t68_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t69_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t70_moi__ALL.jpg :     0.0098 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t71_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t72_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t73_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t74_moi__ALL.jpg :     0.0079 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t75_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t76_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t77_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t78_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t79_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t80_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t81_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t82_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t83_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t84_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t85_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t86_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t87_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t88_moi__ALL.jpg :     0.0096 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t89_moi__ALL.jpg :     0.0096 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t90_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t91_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t92_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t93_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t94_moi__ALL.jpg :     0.0094 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t95_moi__ALL.jpg :     0.0088 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t96_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t97_moi__ALL.jpg :     0.0088 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t98_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t99_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t100_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t101_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t102_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t103_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t104_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t105_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t106_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t107_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t108_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t109_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t110_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t111_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t112_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t113_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t114_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t115_moi__ALL.jpg :     0.0096 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t116_moi__ALL.jpg :     0.0086 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t117_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t118_moi__ALL.jpg :     0.0082 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t119_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t120_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t121_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t122_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t123_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t124_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t125_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t126_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t127_moi__ALL.jpg :     0.0086 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t128_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t129_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t130_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t131_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t132_moi__ALL.jpg :     0.0088 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t133_moi__ALL.jpg :     0.0077 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t134_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t135_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t136_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t137_moi__ALL.jpg :     0.0082 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t138_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t139_moi__ALL.jpg :     0.0087 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t140_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t141_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t142_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t143_moi__ALL.jpg :     0.0111 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t144_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/GEOM/V1J009/CSGOptiXRenderTest/CVD1/70000/-1/scan-elv/cxr_overview_emm_t0_elv_t145_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    N[blyth@localhost CSGOptiX]$ 

::

    epsilon:CSGOptiX blyth$ ~/opticks/bin/lvn.sh 133,143
    /Users/blyth/.opticks/GEOM/V1J009/CSGFoundry/meshname.txt
    133  134  sReflectorInCD
    143  144  sWorld
    epsilon:CSGOptiX blyth$ 




