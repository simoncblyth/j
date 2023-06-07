cxr_scan_cxr_overview_ELV_scan_out_of_range_error
===================================================

FIXED : issue
--------------

ELV scanning giving SBT::getGAS out_of_range when including LV from the corresponding solid. 
I dont recall this mis-behaviour previously.  What has changed ? 

With the "only" scan when the only LV is from an instanced solid 
get gas_idx out of range errors for the corresponding solid. 


TODO : revive the coarser EMM scanning (ELV scanning is working)
------------------------------------------------------------------


TODO : check earlier skipping of XJFixtureConstruction
--------------------------------------------------------

::

    jcv XJfixtureConstruction




snap analysis of cxr_overview cxr_scan
-----------------------------------------

::

   CVD=1 SELECTSPEC=all SNAP_LIMIT=512 ./cxr_overview.sh jstab 

   CVD=1 SELECTSPEC=all SNAP_LIMIT=512 SNAP_ARGS="--jpg --out --outpath=/tmp/time_ordered_jpg.txt" ./cxr_overview.sh jstab
   CVD=1 SELECTSPEC=all SNAP_LIMIT=512 SNAP_ARGS="--txt --out --outpath=/tmp/time_ordered_txt.txt" ./cxr_overview.sh jstab

   open -n $(cat /tmp/time_ordered_jpg.txt)   ## open all jpg in time order 
   vim -R /tmp/time_ordered_txt.txt           ## view txt table to see the ELV exclusion names

   epsilon:~ blyth$ cp /tmp/time_ordered_txt.txt ~/j/issues/cxr_scan_cxr_overview_time_ordered_txt.txt
   epsilon:~ blyth$ cp /tmp/time_ordered_jpg.txt ~/j/issues/cxr_scan_cxr_overview_time_ordered_jpg.txt

Notable extracts from ~/j/issues/cxr_scan_cxr_overview_time_ordered_txt.txt::

    idx         -e        time(s)           relative         enabled geometry description
    . 0          3         0.0017             0.1129         ONLY: PoolCoversub       
      1         73         0.0017             0.1138         ONLY: GZ1.B05_06_FlangeI_Web_FlangeII
    ..
    .74         14         0.0029             0.1918         ONLY: sAirTT   
    ## perplexed by appearance of sAirTT render : looks like cylinder in middle of box 
    ...
    136         95         0.0041             0.2744         ONLY: sAcrylic
    137        135         0.0041             0.2763         ONLY: sReflectorInCD
    138          0         0.0041             0.2769         ONLY: sTopRock_domeAir
    139         94         0.0041             0.2788         ONLY: sTarget
    140        130         0.0042             0.2801         ONLY: sChimneyAcrylic
    141        124         0.0044             0.2983         ONLY: NNVTMCPPMTsMask_virtual
    142        116         0.0047             0.3145         ONLY: NNVTMCPPMTsMask
    ## notable time jump for the ONLY Tails  
    143        105         0.0067             0.4514         ONLY: HamamatsuR12860Tail
    144        117         0.0074             0.4991         ONLY: NNVTMCPPMTTail
    ##
    145     t103,1         0.0075             0.5072         EXCL: solidXJfixture sTopRock_dome
    146   t103,105         0.0078             0.5225         EXCL: solidXJfixture HamamatsuR12860Tail
    147    t103,29         0.0078             0.5237         EXCL: solidXJfixture GLw2.equ_bt01_FlangeI_Web_FlangeII
    ...
    173    t103,93         0.0081             0.5439         EXCL: solidXJfixture solidSJReceiverFastern
    174       t103         0.0081             0.5441         EXCL: solidXJfixture
    175    t103,20         0.0081             0.5442         EXCL: solidXJfixture GLw1.up08_up09_FlangeI_Web_FlangeII
    ...  
    291    t103,14         0.0097             0.6526         EXCL: solidXJfixture sAirTT
    292   t103,107         0.0098             0.6568         EXCL: solidXJfixture HamamatsuR12860_PMT_20inch_outer_edge_solid
    293   t103,145         0.0102             0.6849         EXCL: solidXJfixture sWorld
    ### excluding sWorld changes to closer viewpoint so the comparison is kinda invalidated for that one 
    294       t135         0.0135             0.9061         EXCL: sReflectorInCD
    295       t116         0.0136             0.9167         EXCL: NNVTMCPPMTsMask
    296        t29         0.0137             0.9190         EXCL: GLw2.equ_bt01_FlangeI_Web_FlangeII
    297        t95         0.0137             0.9191         EXCL: sAcrylic
    ###
    440        t89         0.0155             1.0436         EXCL: ZC2.A05_A05_FlangeI_Web_FlangeII
    441       t145         0.0198             1.3315         EXCL: sWorld
    ### excluding sWorld changes viewpoint so not really comparable with others 
    442        103         0.0255             1.7182         ONLY: solidXJfixture
    ### the really slow solidXJfixture looks blank 
    idx         -e        time(s)           relative         enabled geometry description
        


0-based 103 solidXJfixture culprit::

    epsilon:bin blyth$ ./lvn.sh 101,102,103,104
    /Users/blyth/.opticks/GEOM/V1J008/CSGFoundry/meshname.txt
    101  102  uni_acrylic1
    102  103  solidXJanchor
    103  104  solidXJfixture
    104  105  HamamatsuR12860sMask
    epsilon:bin blyth$ 

     


DONE : EMM scan 
----------------- 

::

    cx   
    SCAN=scan-emm CVD=1 ./cxr_scan.sh      # workstation
    SCAN=scan-emm CVD=1 ./cxr_overview.sh  # laptop


    SCAN=scan-emm SELECTSPEC=all SELECTMODE=all CVD=1 ./cxr_overview.sh jstab
    
    SCAN=scan-emm SELECTSPEC=all SELECTMODE=all CVD=1 SNAP_ARGS="--jpg --out --outpath=/tmp/emm_jpg.txt" ./cxr_overview.sh jstab


    CVD=1 SELECTSPEC=all SNAP_LIMIT=512 SNAP_ARGS="--jpg --out --outpath=/tmp/time_ordered_jpg.txt" ./cxr_overview.sh jstab
    CVD=1 SELECTSPEC=all SNAP_LIMIT=512 SNAP_ARGS="--txt --out --outpath=/tmp/time_ordered_txt.txt" ./cxr_overview.sh jstab



The offender is inside the remainder "3089:sWorld"


::

    [2023-06-06 16:19:35,387] p28007 {/Users/blyth/opticks/ana/snap.py:331} INFO - after selectmode:all selectspec:all snaps:32 
    idx         -e        time(s)           relative         enabled geometry description                                              
      0         5,         0.0029             0.0029         ONLY: 1:sStrutBallhead                                                    
      1         9,         0.0029             0.0029         ONLY: 130:sPanel                                                          
      2         7,         0.0030             0.0030         ONLY: 1:base_steel                                                        
      3         8,         0.0032             0.0032         ONLY: 1:uni_acrylic1                                                      
      4         6,         0.0032             0.0032         ONLY: 1:uni1                                                              
      5         1,         0.0035             0.0035         ONLY: 5:PMT_3inch_pmt_solid                                               
      6         4,         0.0051             0.0051         ONLY: 6:mask_PMT_20inch_vetosMask_virtual                                 
      7         2,         0.0076             0.0076         ONLY: 9:NNVTMCPPMTsMask_virtual                                           
      8         3,         0.0079             0.0079         ONLY: 12:HamamatsuR12860sMask_virtual                                     
      9       t8,0         0.0097             0.0097         EXCL: 1:uni_acrylic1 3089:sWorld                                          
     10        t0,         0.0100             0.0100         EXCL: 3089:sWorld                                                         
     11    1,2,3,4         0.0109             0.0109         ONLY PMT                                                                  
     12       t8,3         0.0135             0.0135         EXCL: 1:uni_acrylic1 12:HamamatsuR12860sMask_virtual                      
     13       t8,4         0.0136             0.0136         EXCL: 1:uni_acrylic1 6:mask_PMT_20inch_vetosMask_virtual                  
     14       t8,1         0.0137             0.0137         EXCL: 1:uni_acrylic1 5:PMT_3inch_pmt_solid                                
     15         t0         0.0139             0.0139         ALL                                                                       
     16         0,         0.0141             0.0141         ONLY: 3089:sWorld                                                         
     17        t2,         0.0144             0.0144         EXCL: 9:NNVTMCPPMTsMask_virtual                                           
     18       t8,2         0.0144             0.0144         EXCL: 1:uni_acrylic1 9:NNVTMCPPMTsMask_virtual                            
     19        t1,         0.0145             0.0145         EXCL: 5:PMT_3inch_pmt_solid                                               
     20        t3,         0.0146             0.0146         EXCL: 12:HamamatsuR12860sMask_virtual                                     
     21        t4,         0.0147             0.0147         EXCL: 6:mask_PMT_20inch_vetosMask_virtual                                 
     22        t9,         0.0149             0.0149         EXCL: 130:sPanel                                                          
     23        t5,         0.0149             0.0149         EXCL: 1:sStrutBallhead                                                    
     24        t6,         0.0149             0.0149         EXCL: 1:uni1                                                              
     25       t8,6         0.0149             0.0149         EXCL: 1:uni_acrylic1 1:uni1                                               
     26       t8,5         0.0150             0.0150         EXCL: 1:uni_acrylic1 1:sStrutBallhead                                     
     27       t8,9         0.0150             0.0150         EXCL: 1:uni_acrylic1 130:sPanel                                           
     28       t8,7         0.0150             0.0150         EXCL: 1:uni_acrylic1 1:base_steel                                         
     29       t8,8         0.0150             0.0150         EXCL: 1:uni_acrylic1 1:uni_acrylic1                                       
     30        t7,         0.0151             0.0151         EXCL: 1:base_steel                                                        
     31        t8,         0.0154             0.0154         EXCL: 1:uni_acrylic1                                                      
    idx         -e        time(s)           relative         enabled geometry description                                              

    In [1]:                                            




TODO : compare with the below presentation
-----------------------------------------------

https://simoncblyth.bitbucket.io/env/presentation/opticks_20220329_progress_towards_production.html

TODO : try taking out multiple of the crazy complex solids
-------------------------------------------------------------

::

    epsilon:CSGOptiX blyth$ ~/opticks/bin/lvn.sh 99,100,101,102,103
    /Users/blyth/.opticks/GEOM/V1J008/CSGFoundry/meshname.txt
    99   100  uni1
    100  101  base_steel
    101  102  uni_acrylic1
    102  103  solidXJanchor
    103  104  solidXJfixture
    epsilon:CSGOptiX blyth$ 




TITAN RTX only scan 
---------------------

::

    N[blyth@localhost CSGOptiX]$ CVD=1 ./cxr_scan.sh 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_0_moi__ALL.jpg :     0.0041 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_1_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_2_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_3_moi__ALL.jpg :     0.0017 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_4_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_5_moi__ALL.jpg :     0.0033 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_6_moi__ALL.jpg :     0.0034 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_7_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_8_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_9_moi__ALL.jpg :     0.0019 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_10_moi__ALL.jpg :     0.0019 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_11_moi__ALL.jpg :     0.0019 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_12_moi__ALL.jpg :     0.0019 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_13_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_14_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_15_moi__ALL.jpg :     0.0040 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_16_moi__ALL.jpg :     0.0032 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_17_moi__ALL.jpg :     0.0032 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_18_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_19_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_20_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_21_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_22_moi__ALL.jpg :     0.0019 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_23_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_24_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_25_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_26_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_27_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_28_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_29_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_30_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_31_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_32_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_33_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_34_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_35_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_36_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_37_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_38_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_39_moi__ALL.jpg :     0.0021 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_40_moi__ALL.jpg :     0.0032 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_41_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_42_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_43_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_44_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_45_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_46_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_47_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_48_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_49_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_50_moi__ALL.jpg :     0.0017 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_51_moi__ALL.jpg :     0.0017 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_52_moi__ALL.jpg :     0.0017 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_53_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_54_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_55_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_56_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_57_moi__ALL.jpg :     0.0017 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_58_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_59_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_60_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_61_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_62_moi__ALL.jpg :     0.0021 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_63_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_64_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_65_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_66_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_67_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_68_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_69_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_70_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_71_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_72_moi__ALL.jpg :     0.0017 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_73_moi__ALL.jpg :     0.0017 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_74_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_75_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_76_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_77_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_78_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_79_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_80_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_81_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_82_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_83_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_84_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_85_moi__ALL.jpg :     0.0027 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_86_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_87_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_88_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_89_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_90_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_91_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_92_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_93_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_94_moi__ALL.jpg :     0.0041 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_95_moi__ALL.jpg :     0.0041 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_96_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_97_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_98_moi__ALL.jpg :     0.0018 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_99_moi__ALL.jpg :     0.0020 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_100_moi__ALL.jpg :     0.0029 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_101_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_102_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_103_moi__ALL.jpg :    *0.0255* 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_104_moi__ALL.jpg :     0.0037 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_105_moi__ALL.jpg :     0.0067 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_106_moi__ALL.jpg :     0.0020 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_107_moi__ALL.jpg :     0.0032 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_108_moi__ALL.jpg :     0.0020 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_109_moi__ALL.jpg :     0.0020 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_110_moi__ALL.jpg :     0.0021 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_111_moi__ALL.jpg :     0.0028 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_112_moi__ALL.jpg :     0.0032 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_113_moi__ALL.jpg :     0.0027 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_114_moi__ALL.jpg :     0.0038 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_115_moi__ALL.jpg :     0.0036 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_116_moi__ALL.jpg :     0.0047 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_117_moi__ALL.jpg :     0.0074 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_118_moi__ALL.jpg :     0.0033 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_119_moi__ALL.jpg :     0.0033 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_120_moi__ALL.jpg :     0.0033 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_121_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_122_moi__ALL.jpg :     0.0023 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_123_moi__ALL.jpg :     0.0023 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_124_moi__ALL.jpg :     0.0044 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_125_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_126_moi__ALL.jpg :     0.0022 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_127_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_128_moi__ALL.jpg :     0.0020 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_129_moi__ALL.jpg :     0.0033 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_130_moi__ALL.jpg :     0.0042 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_131_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_132_moi__ALL.jpg :     0.0024 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_133_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_134_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_135_moi__ALL.jpg :     0.0041 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_136_moi__ALL.jpg :     0.0021 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_137_moi__ALL.jpg :     0.0032 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_138_moi__ALL.jpg :     0.0032 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_139_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_140_moi__ALL.jpg :     0.0031 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_141_moi__ALL.jpg :     0.0030 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_142_moi__ALL.jpg :     0.0022 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_143_moi__ALL.jpg :     0.0032 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_144_moi__ALL.jpg :     0.0021 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_145_moi__ALL.jpg :     0.0032 1:TITAN_RTX 
    CSGFoundry::upload@2829: FAILED TO UPLOAD
    CSGOptiXRenderTest: /data/blyth/junotop/opticks/CSG/CSGFoundry.cc:2830: void CSGFoundry::upload(): Assertion `is_uploaded_1 == true' failed.
    ./cxr.sh: line 160: 79799 Aborted                 (core dumped) CSGOptiXRenderTest
    CSGFoundry::upload@2829: FAILED TO UPLOAD
    CSGOptiXRenderTest: /data/blyth/junotop/opticks/CSG/CSGFoundry.cc:2830: void CSGFoundry::upload(): Assertion `is_uploaded_1 == true' failed.
    ./cxr.sh: line 160: 79854 Aborted                 (core dumped) CSGOptiXRenderTest
    N[blyth@localhost CSGOptiX]$ 




TITAN RTX exclusion scan : excluding the slowest LV:103 XJFixtureConstruction and then all one-by-one
--------------------------------------------------------------------------------------------------------

::

    N[blyth@localhost CSGOptiX]$ CVD=1 ./cxr_scan.sh 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,0_moi__ALL.jpg :     0.0088 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,1_moi__ALL.jpg :     0.0075 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,2_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,3_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,4_moi__ALL.jpg :     0.0096 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,5_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,6_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,7_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,8_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,9_moi__ALL.jpg :     0.0082 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,10_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,11_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,12_moi__ALL.jpg :     0.0094 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,13_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,14_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,15_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,16_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,17_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,18_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,19_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,20_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,21_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,22_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,23_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,24_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,25_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,26_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,27_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,28_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,29_moi__ALL.jpg :     0.0078 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,30_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,31_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,32_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,33_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,34_moi__ALL.jpg :     0.0095 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,35_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,36_moi__ALL.jpg :     0.0082 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,37_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,38_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,39_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,40_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,41_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,42_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,43_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,44_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,45_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,46_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,47_moi__ALL.jpg :     0.0087 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,48_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,49_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,50_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,51_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,52_moi__ALL.jpg :     0.0095 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,53_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,54_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,55_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,56_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,57_moi__ALL.jpg :     0.0086 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,58_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,59_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,60_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,61_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,62_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,63_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,64_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,65_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,66_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,67_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,68_moi__ALL.jpg :     0.0085 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,69_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,70_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,71_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,72_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,73_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,74_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,75_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,76_moi__ALL.jpg :     0.0086 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,77_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,78_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,79_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,80_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,81_moi__ALL.jpg :     0.0095 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,82_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,83_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,84_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,85_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,86_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,87_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,88_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,89_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,90_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,91_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,92_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,93_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,94_moi__ALL.jpg :     0.0088 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,95_moi__ALL.jpg :     0.0094 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,96_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,97_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,98_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,99_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,100_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,101_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,102_moi__ALL.jpg :     0.0082 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,103_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,104_moi__ALL.jpg :     0.0096 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,105_moi__ALL.jpg :     0.0078 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,106_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,107_moi__ALL.jpg :     0.0098 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,108_moi__ALL.jpg :     0.0093 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,109_moi__ALL.jpg :     0.0097 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,110_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,111_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,112_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,113_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,114_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,115_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,116_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,117_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,118_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,119_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,120_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,121_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,122_moi__ALL.jpg :     0.0079 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,123_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,124_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,125_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,126_moi__ALL.jpg :     0.0096 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,127_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,128_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,129_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,130_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,131_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,132_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,133_moi__ALL.jpg :     0.0086 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,134_moi__ALL.jpg :     0.0092 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,135_moi__ALL.jpg :     0.0086 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,136_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,137_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,138_moi__ALL.jpg :     0.0079 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,139_moi__ALL.jpg :     0.0090 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,140_moi__ALL.jpg :     0.0081 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,141_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,142_moi__ALL.jpg :     0.0085 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,143_moi__ALL.jpg :     0.0091 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,144_moi__ALL.jpg :     0.0089 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,145_moi__ALL.jpg :     0.0102 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,146_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103,147_moi__ALL.jpg :     0.0080 1:TITAN_RTX 
    N[blyth@localhost CSGOptiX]$ 




TITAN RTX exclusion scan
-------------------------

::

    N[blyth@localhost CSGOptiX]$ CVD=1 ./cxr_scan.sh 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t0_moi__ALL.jpg :     0.0145 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t1_moi__ALL.jpg :     0.0143 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t2_moi__ALL.jpg :     0.0145 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t3_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t4_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t5_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t6_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t7_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t8_moi__ALL.jpg :     0.0147 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t9_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t10_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t11_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t12_moi__ALL.jpg :     0.0155 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t13_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t14_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t15_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t16_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t17_moi__ALL.jpg :     0.0154 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t18_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t19_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t20_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t21_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t22_moi__ALL.jpg :     0.0137 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t23_moi__ALL.jpg :     0.0155 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t24_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t25_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t26_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t27_moi__ALL.jpg :     0.0137 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t28_moi__ALL.jpg :     0.0154 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t29_moi__ALL.jpg :     0.0137 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t30_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t31_moi__ALL.jpg :     0.0155 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t32_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t33_moi__ALL.jpg :     0.0144 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t34_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t35_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t36_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t37_moi__ALL.jpg :     0.0153 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t38_moi__ALL.jpg :     0.0147 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t39_moi__ALL.jpg :     0.0154 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t40_moi__ALL.jpg :     0.0151 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t41_moi__ALL.jpg :     0.0150 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t42_moi__ALL.jpg :     0.0140 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t43_moi__ALL.jpg :     0.0146 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t44_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t45_moi__ALL.jpg :     0.0150 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t46_moi__ALL.jpg :     0.0150 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t47_moi__ALL.jpg :     0.0143 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t48_moi__ALL.jpg :     0.0150 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t49_moi__ALL.jpg :     0.0147 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t50_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t51_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t52_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t53_moi__ALL.jpg :     0.0141 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t54_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t55_moi__ALL.jpg :     0.0147 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t56_moi__ALL.jpg :     0.0150 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t57_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t58_moi__ALL.jpg :     0.0150 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t59_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t60_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t61_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t62_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t63_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t64_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t65_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t66_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t67_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t68_moi__ALL.jpg :     0.0140 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t69_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t70_moi__ALL.jpg :     0.0142 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t71_moi__ALL.jpg :     0.0151 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t72_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t73_moi__ALL.jpg :     0.0153 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t74_moi__ALL.jpg :     0.0137 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t75_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t76_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t77_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t78_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t79_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t80_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t81_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t82_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t83_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t84_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t85_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t86_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t87_moi__ALL.jpg :     0.0151 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t88_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t89_moi__ALL.jpg :     0.0155 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t90_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t91_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t92_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t93_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t94_moi__ALL.jpg :     0.0147 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t95_moi__ALL.jpg :     0.0137 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t96_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t97_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t98_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t99_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t100_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t101_moi__ALL.jpg :     0.0151 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t102_moi__ALL.jpg :     0.0151 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t103_moi__ALL.jpg :    *0.0081* 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t104_moi__ALL.jpg :     0.0143 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t105_moi__ALL.jpg :     0.0146 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t106_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t107_moi__ALL.jpg :     0.0155 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t108_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t109_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t110_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t111_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t112_moi__ALL.jpg :     0.0155 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t113_moi__ALL.jpg :     0.0147 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t114_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t115_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t116_moi__ALL.jpg :     0.0136 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t117_moi__ALL.jpg :     0.0137 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t118_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t119_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t120_moi__ALL.jpg :     0.0153 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t121_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t122_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t123_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t124_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t125_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t126_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t127_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t128_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t129_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t130_moi__ALL.jpg :     0.0153 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t131_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t132_moi__ALL.jpg :     0.0144 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t133_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t134_moi__ALL.jpg :     0.0144 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t135_moi__ALL.jpg :     0.0135 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t136_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t137_moi__ALL.jpg :     0.0139 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t138_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t139_moi__ALL.jpg :     0.0147 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t140_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t141_moi__ALL.jpg :     0.0149 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t142_moi__ALL.jpg :     0.0153 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t143_moi__ALL.jpg :     0.0147 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t144_moi__ALL.jpg :     0.0138 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t145_moi__ALL.jpg :     0.0198 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t146_moi__ALL.jpg :     0.0147 1:TITAN_RTX 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/CVD1/70000/-1/cxr_overview_emm_t0_elv_t147_moi__ALL.jpg :     0.0148 1:TITAN_RTX 
    N[blyth@localhost CSGOptiX]$ 




TODO : better handling of a selection that selects no geometry
------------------------------------------------------------------

* currently get "FAILED TO UPLOAD"

::

    CSGOptiX::render_snap@970: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_144_moi__ALL.jpg :     0.0029
    CSGOptiX::render_snap@970: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_145_moi__ALL.jpg :     0.0029
    CSGFoundry::upload@2829: FAILED TO UPLOAD
    CSGOptiXRenderTest: /data/blyth/junotop/opticks/CSG/CSGFoundry.cc:2830: void CSGFoundry::upload(): Assertion `is_uploaded_1 == true' failed.
    ./cxr.sh: line 157: 372983 Aborted                 (core dumped) CSGOptiXRenderTest
    CSGFoundry::upload@2829: FAILED TO UPLOAD
    CSGOptiXRenderTest: /data/blyth/junotop/opticks/CSG/CSGFoundry.cc:2830: void CSGFoundry::upload(): Assertion `is_uploaded_1 == true' failed.
    ./cxr.sh: line 157: 373026 Aborted                 (core dumped) CSGOptiXRenderTest
    N[blyth@localhost CSGOptiX]$ 


confirmed cause and FIX
------------------------

The compound solid references in the instance transforms are not being 
updated to accomodate changes in the number of compound solids as a result
of the selecting CSGCopy.  

* DONE: find where the qat4 gas_idx references are formed ?

  * probably stree::add_inst

* DONE: work out how to effect a mapping from old to new gas refs

  * added FIX to CSGCopy::copySolidInstances


* HMM: while not guaranteed to work I expect for the single LV "only" 
  geometries there will almost always be only a single solid so the gas_idx 
  ref needs to be zero   

* HMM: for single exclusion geometries the problem is when the exclusion knocks
  out a compound solid, which will only happen for the single LV "compounds" :
  in those cases some of the gas_idx refs will need to be decremented while 
  most will stay the same : how to write code to do this mapping ?

  * need access to the src and dst CSGFoundry
  * traverse the IAS refs converting gas_idx into compound solid names ?



Review the creation of OptiX geometry IAS
-------------------------------------------

::

    331 void SBT::createIAS(unsigned ias_idx)
    332 {
    333     unsigned num_inst = foundry->getNumInst();
    334     unsigned num_ias_inst = foundry->getNumInstancesIAS(ias_idx, emm);
    335     LOG(LEVEL) << " ias_idx " << ias_idx << " num_inst " << num_inst ;
    336 
    337     std::vector<qat4> inst ;
    338     foundry->getInstanceTransformsIAS(inst, ias_idx, emm );
    339     assert( num_ias_inst == inst.size() );
    340 
    341     createIAS(inst);
    342     LOG(LEVEL) << descIAS(inst);
    343 }


    043 void IAS_Builder::CollectInstances(std::vector<OptixInstance>& instances, const std::vector<qat4>& ias_inst, const SBT* sbt ) //     static 
     44 {
     45     unsigned num_ias_inst = ias_inst.size() ;
     46     unsigned flags = OPTIX_INSTANCE_FLAG_DISABLE_ANYHIT ;
     47     unsigned prim_idx = 0u ;  // need sbt offset for the outer prim(aka layer) of the GAS 
     48 
     49     std::map<unsigned, unsigned> gasIdx_sbtOffset ;
     50 
     51     for(unsigned i=0 ; i < num_ias_inst ; i++)
     52     {
     53         const qat4& q = ias_inst[i] ;
     54         int ins_idx,  gasIdx, sensor_identifier, sensor_index ;
     55         q.getIdentity(ins_idx, gasIdx, sensor_identifier, sensor_index );
     56         const GAS& gas = sbt->getGAS(gasIdx);  // susceptible to out-of-range errors for stale gas_idx 
     57 


Where the Opticks inst come from
----------------------------------

::

    2567 inline void stree::add_inst()
    2568 {
    2569     glm::tmat4x4<double> tr_m2w(1.) ; 
    2570     glm::tmat4x4<double> tr_w2m(1.) ; 
    2571     add_inst(tr_m2w, tr_w2m, 0, 0 );   // global instance with identity transforms 
    2572 
    2573     unsigned num_factor = get_num_factor(); 
    2574     for(unsigned i=0 ; i < num_factor ; i++)
    2575     {
    2576         std::vector<int> nodes ; 
    2577         get_factor_nodes(nodes, i);  
    2578 
    2579         unsigned gas_idx = i + 1 ; // 0 is the global instance, so need this + 1  
    2580         std::cout 
    2581             << "stree::add_inst"
    2582             << " i " << std::setw(3) << i 
    2583             << " gas_idx " << std::setw(3) << gas_idx
    2584             << " nodes.size " << std::setw(7) << nodes.size()
    2585             << std::endl
    2586             ;
    2587 
    2588         for(unsigned j=0 ; j < nodes.size() ; j++)
    2589         {
    2590             int nidx = nodes[j]; 
    2591             //get_m2w_product(tr_m2w, nidx, false); 
    2592             //get_w2m_product(tr_w2m, nidx, true ); 
    2593 
    2594             bool local = false ; 
    2595             bool reverse = false ; 
    2596             get_node_product( tr_m2w, tr_w2m, nidx, local, reverse, nullptr  );
    2597 
    2598             add_inst(tr_m2w, tr_w2m, gas_idx, nidx ); 
    2599         }
    2600     }
    2601     narrow_inst();


::

    2860 unsigned CSGFoundry::getNumInstancesIAS(int ias_idx, unsigned long long emm) const
    2861 {
    2862     return qat4::count_ias(inst, ias_idx, emm );
    2863 }
    2864 void CSGFoundry::getInstanceTransformsIAS(std::vector<qat4>& select_inst, int ias_idx, unsigned long long emm ) const
    2865 {
    2866     qat4::select_instances_ias(inst, select_inst, ias_idx, emm ) ;
    2867 }
    2868 
    2869 
    2870 unsigned CSGFoundry::getNumInstancesGAS(int gas_idx) const
    2871 {
    2872     return qat4::count_gas(inst, gas_idx );
    2873 }
    2874 
    2875 void CSGFoundry::getInstanceTransformsGAS(std::vector<qat4>& select_qv, int gas_idx ) const
    2876 {
    2877     qat4::select_instances_gas(inst, select_qv, gas_idx ) ;
    2878 }



CSGCopy has a solid map already::

     47 CSGCopy::CSGCopy(const CSGFoundry* src_, const SBitSet* elv_)
     48     :
     49     src(src_),
     50     sNumSolid(src->getNumSolid()),
     51     solidMap(new int[sNumSolid]),
     52     sSolidIdx(~0u),
     53     elv(elv_),
     54     dst(new CSGFoundry)
     55 {
     56 }


::

    327 void CSGCopy::copySolidInstances()
    328 {
    329     unsigned sNumInst = src->getNumInst();
    330     for(unsigned i=0 ; i < sNumInst ; i++)
    331     {
    332         int sInstIdx = i ;
    333         const qat4* ins = src->getInst(sInstIdx) ;
    334 
    335         int ins_idx,  gas_idx, sensor_identifier, sensor_index ;
    336         ins->getIdentity(ins_idx,  gas_idx, sensor_identifier, sensor_index );
    337 
    338         assert( ins_idx == sInstIdx );
    339         assert( gas_idx < int(sNumSolid) );
    340 
    341         int sSolidIdx = gas_idx ;
    342         int dSolidIdx = solidMap[sSolidIdx] ;
    343 
    344         if( dSolidIdx > -1 )
    345         {
    346             const float* tr16 = ins->cdata();
    347             dst->addInstance(tr16,  gas_idx, sensor_identifier, sensor_index );
    348         }
    349     }
    350 }

Possible fix::

    344         if( dSolidIdx > -1 )
    345         {
    346             const float* tr16 = ins->cdata();
    347             //dst->addInstance(tr16,  gas_idx, sensor_identifier, sensor_index ); 
    348             dst->addInstance(tr16,  dSolidIdx, sensor_identifier, sensor_index );
    349             //                     ^^^^^^^^^^^  try to fix gas_refs going stale on selection 
    350 
    351         }
    352     }



reproduce the selecting CSGCopy on laptop
-------------------------------------------

::

    epsilon:tests blyth$ ELV=8 ./CSGFoundryLoadTest.sh



only scan after fix
----------------------

::

    N[blyth@localhost CSGOptiX]$ ./cxr_scan.sh   ## CSGOptiX::render_snap@970
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_0_moi__ALL.jpg :     0.0039
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_1_moi__ALL.jpg :     0.0036
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_2_moi__ALL.jpg :     0.0028
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_3_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_4_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_5_moi__ALL.jpg :     0.0028
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_6_moi__ALL.jpg :     0.0032
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_7_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_8_moi__ALL.jpg :     0.0026
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_9_moi__ALL.jpg :     0.0078
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_10_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_11_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_12_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_13_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_14_moi__ALL.jpg :     0.0034
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_15_moi__ALL.jpg :     0.0087
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_16_moi__ALL.jpg :     0.0032
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_17_moi__ALL.jpg :     0.0033
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_18_moi__ALL.jpg :     0.0028
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_19_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_20_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_21_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_22_moi__ALL.jpg :     0.0022
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_23_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_24_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_25_moi__ALL.jpg :     0.0074
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_26_moi__ALL.jpg :     0.0071
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_27_moi__ALL.jpg :     0.0074
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_28_moi__ALL.jpg :     0.0039
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_29_moi__ALL.jpg :     0.0075
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_30_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_31_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_32_moi__ALL.jpg :     0.0068
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_33_moi__ALL.jpg :     0.0073
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_34_moi__ALL.jpg :     0.0073
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_35_moi__ALL.jpg :     0.0022
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_36_moi__ALL.jpg :     0.0077
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_37_moi__ALL.jpg :     0.0076
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_38_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_39_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_40_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_41_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_42_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_43_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_44_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_45_moi__ALL.jpg :     0.0071
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_46_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_47_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_48_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_49_moi__ALL.jpg :     0.0073
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_50_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_51_moi__ALL.jpg :     0.0022
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_52_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_53_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_54_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_55_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_56_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_57_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_58_moi__ALL.jpg :     0.0022
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_59_moi__ALL.jpg :     0.0020
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_60_moi__ALL.jpg :     0.0020
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_61_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_62_moi__ALL.jpg :     0.0025
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_63_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_64_moi__ALL.jpg :     0.0020
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_65_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_66_moi__ALL.jpg :     0.0073
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_67_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_68_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_69_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_70_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_71_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_72_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_73_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_74_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_75_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_76_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_77_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_78_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_79_moi__ALL.jpg :     0.0023
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_80_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_81_moi__ALL.jpg :     0.0074
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_82_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_83_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_84_moi__ALL.jpg :     0.0022
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_85_moi__ALL.jpg :     0.0020
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_86_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_87_moi__ALL.jpg :     0.0020
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_88_moi__ALL.jpg :     0.0022
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_89_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_90_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_91_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_92_moi__ALL.jpg :     0.0021
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_93_moi__ALL.jpg :     0.0019
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_94_moi__ALL.jpg :     0.0036
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_95_moi__ALL.jpg :     0.0036
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_96_moi__ALL.jpg :     0.0042
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_97_moi__ALL.jpg :     0.0022
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_98_moi__ALL.jpg :     0.0020
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_99_moi__ALL.jpg :     0.0022
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_100_moi__ALL.jpg :     0.0075
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_101_moi__ALL.jpg :     0.0074
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_102_moi__ALL.jpg :     0.0020
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_103_moi__ALL.jpg :    *0.0314*
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_104_moi__ALL.jpg :     0.0036
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_105_moi__ALL.jpg :     0.0051
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_106_moi__ALL.jpg :     0.0026
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_107_moi__ALL.jpg :     0.0045
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_108_moi__ALL.jpg :     0.0066
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_109_moi__ALL.jpg :     0.0076
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_110_moi__ALL.jpg :     0.0073
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_111_moi__ALL.jpg :     0.0077
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_112_moi__ALL.jpg :     0.0079
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_113_moi__ALL.jpg :     0.0038
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_114_moi__ALL.jpg :     0.0091
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_115_moi__ALL.jpg :     0.0036
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_116_moi__ALL.jpg :     0.0067
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_117_moi__ALL.jpg :    *0.0102*
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_118_moi__ALL.jpg :     0.0027
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_119_moi__ALL.jpg :     0.0027
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_120_moi__ALL.jpg :     0.0027
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_121_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_122_moi__ALL.jpg :     0.0041
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_123_moi__ALL.jpg :     0.0041
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_124_moi__ALL.jpg :     0.0067
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_125_moi__ALL.jpg :     0.0026
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_126_moi__ALL.jpg :     0.0068
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_127_moi__ALL.jpg :     0.0026
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_128_moi__ALL.jpg :     0.0026
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_129_moi__ALL.jpg :     0.0028
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_130_moi__ALL.jpg :     0.0094
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_131_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_132_moi__ALL.jpg :     0.0029
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_133_moi__ALL.jpg :     0.0024
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_134_moi__ALL.jpg :     0.0034
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_135_moi__ALL.jpg :     0.0040
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_136_moi__ALL.jpg :     0.0081
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_137_moi__ALL.jpg :     0.0073
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_138_moi__ALL.jpg :     0.0080
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_139_moi__ALL.jpg :     0.0026
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_140_moi__ALL.jpg :     0.0064
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_141_moi__ALL.jpg :     0.0070
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_142_moi__ALL.jpg :     0.0029
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_143_moi__ALL.jpg :     0.0029
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_144_moi__ALL.jpg :     0.0029
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_145_moi__ALL.jpg :     0.0029
    CSGFoundry::upload@2829: FAILED TO UPLOAD
    CSGOptiXRenderTest: /data/blyth/junotop/opticks/CSG/CSGFoundry.cc:2830: void CSGFoundry::upload(): Assertion `is_uploaded_1 == true' failed.
    ./cxr.sh: line 157: 372983 Aborted                 (core dumped) CSGOptiXRenderTest
    CSGFoundry::upload@2829: FAILED TO UPLOAD
    CSGOptiXRenderTest: /data/blyth/junotop/opticks/CSG/CSGFoundry.cc:2830: void CSGFoundry::upload(): Assertion `is_uploaded_1 == true' failed.
    ./cxr.sh: line 157: 373026 Aborted                 (core dumped) CSGOptiXRenderTest
    N[blyth@localhost CSGOptiX]$ 


::

    epsilon:CSGOptiX blyth$ ~/opticks/bin/lvn.sh 103,117
    /Users/blyth/.opticks/GEOM/V1J008/CSGFoundry/meshname.txt
    103  104  solidXJfixture
    117  118  NNVTMCPPMTTail
    epsilon:CSGOptiX blyth$ 





DONE : get GPU control to work again SCVD.h no longer works, now use scontext.h
----------------------------------------------------------------------------------

::

    ./cxr_min.sh : run : delete prior LOG CSGOptiXRdrTest.log
    CSGOptiX::initCtx@349: 
    Ctx::desc
                                      device :          1
    Properties::desc
                          limitMaxTraceDepth :         31
               limitMaxTraversableGraphDepth :         16
                    limitMaxPrimitivesPerGas :  536870912  20000000
                     limitMaxInstancesPerIas :   16777216   1000000
                               rtcoreVersion :          a
                          limitMaxInstanceId :   16777215    ffffff
          limitNumBitsInstanceVisibilityMask :          8
                    limitMaxSbtRecordsPerGas :   16777216   1000000
                           limitMaxSbtOffset :   16777215    ffffff

    terminate called after throwing an instance of 'sutil::CUDA_Exception'
      what():  CUDA call (cudaFree( (void*)d_temp_buffer_gas ) ) failed with error: 'an illegal memory access was encountered' (/data/blyth/junotop/opticks/CSGOptiX/GAS_Builder.cc:239)

    ./cxr_min.sh: line 107: 393188 Aborted                 (core dumped) $bin





exclusion scan after fix
-------------------------------

::

    N[blyth@localhost CSGOptiX]$ ./cxr_scan.sh 
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t0_moi__ALL.jpg :     0.0248
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t1_moi__ALL.jpg :     0.0246
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t2_moi__ALL.jpg :     0.0246
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t3_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t4_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t5_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t6_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t7_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t8_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t9_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t10_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t11_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t12_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t13_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t14_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t15_moi__ALL.jpg :     0.0207
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t16_moi__ALL.jpg :     0.0252
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t17_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t18_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t19_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t20_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t21_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t22_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t23_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t24_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t25_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t26_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t27_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t28_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t29_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t30_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t31_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t32_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t33_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t34_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t35_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t36_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t37_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t38_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t39_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t40_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t41_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t42_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t43_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t44_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t45_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t46_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t47_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t48_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t49_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t50_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t51_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t52_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t53_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t54_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t55_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t56_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t57_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t58_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t59_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t60_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t61_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t62_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t63_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t64_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t65_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t66_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t67_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t68_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t69_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t70_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t71_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t72_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t73_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t74_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t75_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t76_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t77_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t78_moi__ALL.jpg :     0.0206
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t79_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t80_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t81_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t82_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t83_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t84_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t85_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t86_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t87_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t88_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t89_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t90_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t91_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t92_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t93_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t94_moi__ALL.jpg :     0.0207
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t95_moi__ALL.jpg :     0.0210
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t96_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t97_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t98_moi__ALL.jpg :     0.0207
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t99_moi__ALL.jpg :     0.0201
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t100_moi__ALL.jpg :     0.0224
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t101_moi__ALL.jpg :     0.0201
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t102_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t103_moi__ALL.jpg :    *0.0137*
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t104_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t105_moi__ALL.jpg :     0.0201
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t106_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t107_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t108_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t109_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t110_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t111_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t112_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t113_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t114_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t115_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t116_moi__ALL.jpg :     0.0200
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t117_moi__ALL.jpg :    *0.0197*
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t118_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t119_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t120_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t121_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t122_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t123_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t124_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t125_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t126_moi__ALL.jpg :     0.0202
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t127_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t128_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t129_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t130_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t131_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t132_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t133_moi__ALL.jpg :     0.0205
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t134_moi__ALL.jpg :     0.0208
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t135_moi__ALL.jpg :     0.0208
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t136_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t137_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t138_moi__ALL.jpg :     0.0201
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t139_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t140_moi__ALL.jpg :     0.0203
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t141_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t142_moi__ALL.jpg :     0.0227
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t143_moi__ALL.jpg :     0.0228
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t144_moi__ALL.jpg :     0.0242
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t145_moi__ALL.jpg :    *0.0305*
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t146_moi__ALL.jpg :     0.0204
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t147_moi__ALL.jpg :     0.0205
    N[blyth@localhost CSGOptiX]$ 



HMM failing to select GPU 0 ? TITAN RTX ? Always getting TITAN V ?
---------------------------------------------------------------------

TODO: GPU characteristics probing 

::

    Mon Jun  5 00:19:11 2023       
    +-----------------------------------------------------------------------------+
    | NVIDIA-SMI 435.21       Driver Version: 435.21       CUDA Version: 10.1     |
    |-------------------------------+----------------------+----------------------+
    | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
    |===============================+======================+======================|
    |   0  TITAN RTX           Off  | 00000000:73:00.0 Off |                  N/A |
    | 41%   51C    P8    24W / 280W |     10MiB / 24219MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+
    |   1  TITAN V             Off  | 00000000:A6:00.0 Off |                  N/A |
    | 38%   56C    P0    N/A /  N/A |     64MiB / 12066MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+
                                                                                   
    +-----------------------------------------------------------------------------+
    | Processes:                                                       GPU Memory |
    |  GPU       PID   Type   Process name                             Usage      |
    |=============================================================================|
    |    1    384191      C   CSGOptiXRenderTest                            53MiB |
    +-----------------------------------------------------------------------------+




scan log annotated for an inclusion "only" scan
---------------------------------------------------

::

    scan-elv-()
    {
        #for e in $(seq 0 $NLV) ; do echo "t$e" ; done    # disabling each midx one-by-one
        for e in $(seq 0 $NLV) ; do echo "$e" ; done     # enabling each midx one-by-one
    }


::

    N[blyth@localhost CSGOptiX]$ ./cxr_scan.sh 
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_0_moi__ALL.jpg :     0.0033
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_1_moi__ALL.jpg :     0.0036
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_2_moi__ALL.jpg :     0.0027
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_3_moi__ALL.jpg :     0.0024
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_4_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_5_moi__ALL.jpg :     0.0026
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_6_moi__ALL.jpg :     0.0026
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_7_moi__ALL.jpg :     0.0023

    SBT::getGAS@288:  no such gas_idx 9
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 320493 Aborted                 (core dumped) CSGOptiXRenderTest    #  8
    SBT::getGAS@288:  no such gas_idx 9
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 320553 Aborted                 (core dumped) CSGOptiXRenderTest    #  9
    SBT::getGAS@288:  no such gas_idx 9
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 320611 Aborted                 (core dumped) CSGOptiXRenderTest    # 10
    SBT::getGAS@288:  no such gas_idx 9
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 320676 Aborted                 (core dumped) CSGOptiXRenderTest    # 11


    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 8,9,10,11 $HOME/.opticks/GEOM/V1J008/CSGFoundry/meshname.txt 
    8    9    sBar
    9    10   sBar
    10   11   sPanelTape
    11   12   sPanel
    epsilon:CSGFoundry blyth$ 

    epsilon:CSGFoundry blyth$ cat mmlabel.txt
    3089:sWorld
    5:PMT_3inch_pmt_solid
    9:NNVTMCPPMTsMask_virtual
    12:HamamatsuR12860sMask_virtual
    6:mask_PMT_20inch_vetosMask_virtual
    1:sStrutBallhead
    1:uni1
    1:base_steel
    1:uni_acrylic1
    130:sPanel
    epsilon:CSGFoundry blyth$ 

    
::

    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_12_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_13_moi__ALL.jpg :     0.0022
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_14_moi__ALL.jpg :     0.0038
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_15_moi__ALL.jpg :     0.0038
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_16_moi__ALL.jpg :     0.0032
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_17_moi__ALL.jpg :     0.0030
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_18_moi__ALL.jpg :     0.0024
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_19_moi__ALL.jpg :     0.0024
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_20_moi__ALL.jpg :     0.0025
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_21_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_22_moi__ALL.jpg :     0.0022
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_23_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_24_moi__ALL.jpg :     0.0024
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_25_moi__ALL.jpg :     0.0073
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_26_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_27_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_28_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_29_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_30_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_31_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_32_moi__ALL.jpg :     0.0076
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_33_moi__ALL.jpg :     0.0024
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_34_moi__ALL.jpg :     0.0022
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_35_moi__ALL.jpg :     0.0022
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_36_moi__ALL.jpg :     0.0022
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_37_moi__ALL.jpg :     0.0025
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_38_moi__ALL.jpg :     0.0068
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_39_moi__ALL.jpg :     0.0024
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_40_moi__ALL.jpg :     0.0082
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_41_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_42_moi__ALL.jpg :     0.0022
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_43_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_44_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_45_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_46_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_47_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_48_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_49_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_50_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_51_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_52_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_53_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_54_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_55_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_56_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_57_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_58_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_59_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_60_moi__ALL.jpg :     0.0022
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_61_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_62_moi__ALL.jpg :     0.0027
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_63_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_64_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_65_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_66_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_67_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_68_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_69_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_70_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_71_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_72_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_73_moi__ALL.jpg :     0.0023
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_74_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_75_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_76_moi__ALL.jpg :     0.0031
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_77_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_78_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_79_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_80_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_81_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_82_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_83_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_84_moi__ALL.jpg :     0.0070
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_85_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_86_moi__ALL.jpg :     0.0020
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_87_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_88_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_89_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_90_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_91_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_92_moi__ALL.jpg :     0.0019
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_93_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_94_moi__ALL.jpg :     0.0036
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_95_moi__ALL.jpg :     0.0040
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_96_moi__ALL.jpg :     0.0022
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_97_moi__ALL.jpg :     0.0024


::

    SBT::getGAS@288:  no such gas_idx 5
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 325607 Aborted                 (core dumped) CSGOptiXRenderTest
    SBT::getGAS@288:  no such gas_idx 6
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 325667 Aborted                 (core dumped) CSGOptiXRenderTest
    SBT::getGAS@288:  no such gas_idx 7
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 325724 Aborted                 (core dumped) CSGOptiXRenderTest
    SBT::getGAS@288:  no such gas_idx 8
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 325781 Aborted                 (core dumped) CSGOptiXRenderTest


    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 98,99,100,101 meshname.txt 
    98   99   sStrutBallhead
    99   100  uni1
    100  101  base_steel
    101  102  uni_acrylic1

    epsilon:CSGFoundry blyth$ cat mmlabel.txt
    3089:sWorld                          # 0
    5:PMT_3inch_pmt_solid                # 1
    9:NNVTMCPPMTsMask_virtual            # 2
    12:HamamatsuR12860sMask_virtual      # 3
    6:mask_PMT_20inch_vetosMask_virtual  # 4
    1:sStrutBallhead                     # 5
    1:uni1                               # 6
    1:base_steel                         # 7 
    1:uni_acrylic1                       # 8 
    130:sPanel                           # 9 


    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_102_moi__ALL.jpg :     0.0021
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_103_moi__ALL.jpg :     0.0315
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 325950 Aborted                 (core dumped) CSGOptiXRenderTest       #104
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326007 Aborted                 (core dumped) CSGOptiXRenderTest       #105
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326067 Aborted                 (core dumped) CSGOptiXRenderTest       #106
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326125 Aborted                 (core dumped) CSGOptiXRenderTest       #107
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326182 Aborted                 (core dumped) CSGOptiXRenderTest       #108
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326241 Aborted                 (core dumped) CSGOptiXRenderTest       #109 
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326298 Aborted                 (core dumped) CSGOptiXRenderTest       #110
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326355 Aborted                 (core dumped) CSGOptiXRenderTest       #111
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326413 Aborted                 (core dumped) CSGOptiXRenderTest       #112
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326481 Aborted                 (core dumped) CSGOptiXRenderTest       #113 
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326538 Aborted                 (core dumped) CSGOptiXRenderTest       #114 
    SBT::getGAS@288:  no such gas_idx 3
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326595 Aborted                 (core dumped) CSGOptiXRenderTest       #115 




::

    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 104,105,106,107,108,109,110,111,112,113,114,115  meshname.txt 
    104  105  HamamatsuR12860sMask
    105  106  HamamatsuR12860Tail
    106  107  HamamatsuR12860_PMT_20inch_plate_solid
    107  108  HamamatsuR12860_PMT_20inch_outer_edge_solid
    108  109  HamamatsuR12860_PMT_20inch_inner_edge_solid
    109  110  HamamatsuR12860_PMT_20inch_inner_ring_solid
    110  111  HamamatsuR12860_PMT_20inch_dynode_tube_solid
    111  112  HamamatsuR12860_PMT_20inch_grid_solid
    112  113  HamamatsuR12860_PMT_20inch_shield_solid
    113  114  HamamatsuR12860_PMT_20inch_inner_solid_1_4
    114  115  HamamatsuR12860_PMT_20inch_pmt_solid_1_4
    115  116  HamamatsuR12860sMask_virtual
    epsilon:CSGFoundry blyth$ 

    epsilon:CSGFoundry blyth$ cat mmlabel.txt
    3089:sWorld
    5:PMT_3inch_pmt_solid
    9:NNVTMCPPMTsMask_virtual
    12:HamamatsuR12860sMask_virtual
    6:mask_PMT_20inch_vetosMask_virtual
    1:sStrutBallhead
    1:uni1
    1:base_steel
    1:uni_acrylic1
    130:sPanel



    SBT::getGAS@288:  no such gas_idx 2
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326652 Aborted                 (core dumped) CSGOptiXRenderTest    #116
    SBT::getGAS@288:  no such gas_idx 2
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326709 Aborted                 (core dumped) CSGOptiXRenderTest    #117
    SBT::getGAS@288:  no such gas_idx 2
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326766 Aborted                 (core dumped) CSGOptiXRenderTest    #118
    SBT::getGAS@288:  no such gas_idx 2
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326823 Aborted                 (core dumped) CSGOptiXRenderTest    #119
    SBT::getGAS@288:  no such gas_idx 2
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326883 Aborted                 (core dumped) CSGOptiXRenderTest    #120 
    SBT::getGAS@288:  no such gas_idx 2
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326940 Aborted                 (core dumped) CSGOptiXRenderTest    #121
    SBT::getGAS@288:  no such gas_idx 2
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 326997 Aborted                 (core dumped) CSGOptiXRenderTest    #122
    SBT::getGAS@288:  no such gas_idx 2
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327054 Aborted                 (core dumped) CSGOptiXRenderTest    #123
    SBT::getGAS@288:  no such gas_idx 2
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327111 Aborted                 (core dumped) CSGOptiXRenderTest    #124



::

    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 116,117,118,119,120,121,122,123,124  meshname.txt 
    116  117  NNVTMCPPMTsMask
    117  118  NNVTMCPPMTTail
    118  119  NNVTMCPPMT_PMT_20inch_edge_solid
    119  120  NNVTMCPPMT_PMT_20inch_plate_solid
    120  121  NNVTMCPPMT_PMT_20inch_tube_solid
    121  122  NNVTMCPPMT_PMT_20inch_mcp_solid
    122  123  NNVTMCPPMT_PMT_20inch_inner_solid_head
    123  124  NNVTMCPPMT_PMT_20inch_pmt_solid_head
    124  125  NNVTMCPPMTsMask_virtual

    epsilon:CSGFoundry blyth$ cat mmlabel.txt
    3089:sWorld
    5:PMT_3inch_pmt_solid
    9:NNVTMCPPMTsMask_virtual
    12:HamamatsuR12860sMask_virtual
    6:mask_PMT_20inch_vetosMask_virtual
    1:sStrutBallhead
    1:uni1
    1:base_steel
    1:uni_acrylic1
    130:sPanel


    SBT::getGAS@288:  no such gas_idx 1
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327168 Aborted                 (core dumped) CSGOptiXRenderTest   #125
    SBT::getGAS@288:  no such gas_idx 1
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327225 Aborted                 (core dumped) CSGOptiXRenderTest   #126
    SBT::getGAS@288:  no such gas_idx 1
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327285 Aborted                 (core dumped) CSGOptiXRenderTest   #127
    SBT::getGAS@288:  no such gas_idx 1
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327342 Aborted                 (core dumped) CSGOptiXRenderTest   #128
    SBT::getGAS@288:  no such gas_idx 1
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327399 Aborted                 (core dumped) CSGOptiXRenderTest   #129



    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 125,126,127,128,129  meshname.txt 
    125  126  PMT_3inch_inner1_solid_ell_helper
    126  127  PMT_3inch_inner2_solid_ell_helper
    127  128  PMT_3inch_body_solid_ell_ell_helper
    128  129  PMT_3inch_cntr_solid
    129  130  PMT_3inch_pmt_solid
    epsilon:CSGFoundry blyth$ 

    epsilon:CSGFoundry blyth$ cat mmlabel.txt
    3089:sWorld
    5:PMT_3inch_pmt_solid
    9:NNVTMCPPMTsMask_virtual
    12:HamamatsuR12860sMask_virtual
    6:mask_PMT_20inch_vetosMask_virtual
    1:sStrutBallhead
    1:uni1
    1:base_steel
    1:uni_acrylic1
    130:sPanel



::

    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_130_moi__ALL.jpg :     0.0038
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_131_moi__ALL.jpg :     0.0022
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_132_moi__ALL.jpg :     0.0027
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_133_moi__ALL.jpg :     0.0025
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_134_moi__ALL.jpg :     0.0040
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_135_moi__ALL.jpg :     0.0036


    SBT::getGAS@288:  no such gas_idx 4
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327803 Aborted                 (core dumped) CSGOptiXRenderTest    #136
    SBT::getGAS@288:  no such gas_idx 4
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327863 Aborted                 (core dumped) CSGOptiXRenderTest    #137
    SBT::getGAS@288:  no such gas_idx 4
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327921 Aborted                 (core dumped) CSGOptiXRenderTest    #138
    SBT::getGAS@288:  no such gas_idx 4
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 327978 Aborted                 (core dumped) CSGOptiXRenderTest    #139
    SBT::getGAS@288:  no such gas_idx 4
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 328035 Aborted                 (core dumped) CSGOptiXRenderTest    #140
    SBT::getGAS@288:  no such gas_idx 4
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 328092 Aborted                 (core dumped) CSGOptiXRenderTest    #141



    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 136,137,138,139,140,141  meshname.txt 
    136  137  mask_PMT_20inch_vetosMask
    137  138  PMT_20inch_veto_inner1_solid
    138  139  PMT_20inch_veto_inner2_solid
    139  140  PMT_20inch_veto_body_solid_1_2
    140  141  PMT_20inch_veto_pmt_solid_1_2
    141  142  mask_PMT_20inch_vetosMask_virtual
    epsilon:CSGFoundry blyth$ 

    epsilon:CSGFoundry blyth$ cat mmlabel.txt
    3089:sWorld
    5:PMT_3inch_pmt_solid
    9:NNVTMCPPMTsMask_virtual
    12:HamamatsuR12860sMask_virtual
    6:mask_PMT_20inch_vetosMask_virtual
    1:sStrutBallhead
    1:uni1
    1:base_steel
    1:uni_acrylic1
    130:sPanel






    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_142_moi__ALL.jpg :     0.0033
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_143_moi__ALL.jpg :     0.0027
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_144_moi__ALL.jpg :     0.0030
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_145_moi__ALL.jpg :     0.0029



    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 142,143,144,145  meshname.txt 
    142  143  sOuterWaterPool
    143  144  sPoolLining
    144  145  sBottomRock
    145  146  sWorld
    epsilon:CSGFoundry blyth$ 




::



    CSGFoundry::upload@2818: FAILED TO UPLOAD
    CSGOptiXRenderTest: /data/blyth/junotop/opticks/CSG/CSGFoundry.cc:2819: void CSGFoundry::upload(): Assertion `is_uploaded_1 == true' failed.
    ./cxr.sh: line 157: 328375 Aborted                 (core dumped) CSGOptiXRenderTest
    CSGFoundry::upload@2818: FAILED TO UPLOAD
    CSGOptiXRenderTest: /data/blyth/junotop/opticks/CSG/CSGFoundry.cc:2819: void CSGFoundry::upload(): Assertion `is_uploaded_1 == true' failed.
    ./cxr.sh: line 157: 328418 Aborted                 (core dumped) CSGOptiXRenderTest
    N[blyth@localhost CSGOptiX]$ 



    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 146,147  meshname.txt 
    146  147  solidSJReceiverFastern
    147  148  uni1
    epsilon:CSGFoundry blyth$ 




scan log for exclusion scan
-------------------------------


::

    N[blyth@localhost CSGOptiX]$ ./cxr_scan.sh 
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t0_moi__ALL.jpg :     0.0247
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t1_moi__ALL.jpg :     0.0246
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t2_moi__ALL.jpg :     0.0245
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t3_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t4_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t5_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t6_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t7_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t8_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t9_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t10_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t11_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t12_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t13_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t14_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t15_moi__ALL.jpg :     0.0205
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t16_moi__ALL.jpg :     0.0251
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t17_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t18_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t19_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t20_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t21_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t22_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t23_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t24_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t25_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t26_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t27_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t28_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t29_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t30_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t31_moi__ALL.jpg :     0.0205
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t32_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t33_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t34_moi__ALL.jpg :     0.0205
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t35_moi__ALL.jpg :     0.0201
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t36_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t37_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t38_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t39_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t40_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t41_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t42_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t43_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t44_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t45_moi__ALL.jpg :     0.0205
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t46_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t47_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t48_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t49_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t50_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t51_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t52_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t53_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t54_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t55_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t56_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t57_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t58_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t59_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t60_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t61_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t62_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t63_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t64_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t65_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t66_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t67_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t68_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t69_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t70_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t71_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t72_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t73_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t74_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t75_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t76_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t77_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t78_moi__ALL.jpg :     0.0206
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t79_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t80_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t81_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t82_moi__ALL.jpg :     0.0205
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t83_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t84_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t85_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t86_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t87_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t88_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t89_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t90_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t91_moi__ALL.jpg :     0.0201
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t92_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t93_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t94_moi__ALL.jpg :     0.0206
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t95_moi__ALL.jpg :     0.0208
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t96_moi__ALL.jpg :     0.0201
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t97_moi__ALL.jpg :     0.0202

    SBT::getGAS@288:  no such gas_idx 9
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 335433 Aborted                 (core dumped) CSGOptiXRenderTest      #  98
    SBT::getGAS@288:  no such gas_idx 9
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 335493 Aborted                 (core dumped) CSGOptiXRenderTest      #  99
    SBT::getGAS@288:  no such gas_idx 9
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 335551 Aborted                 (core dumped) CSGOptiXRenderTest      # 100
    SBT::getGAS@288:  no such gas_idx 9
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 157: 335608 Aborted                 (core dumped) CSGOptiXRenderTest      # 101


    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 98,99,100,101 meshname.txt
    98   99   sStrutBallhead
    99   100  uni1
    100  101  base_steel
    101  102  uni_acrylic1
    epsilon:CSGFoundry blyth$             

    ### curious these have nothing to do with gas 9 
    ### its as if the dynamic geometry is mixing between src and dst 
  


::

    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t102_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t103_moi__ALL.jpg :     0.0136
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t104_moi__ALL.jpg :     0.0200
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t105_moi__ALL.jpg :     0.0199
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t106_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t107_moi__ALL.jpg :     0.0205
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t108_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t109_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t110_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t111_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t112_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t113_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t114_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t115_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t116_moi__ALL.jpg :     0.0199
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t117_moi__ALL.jpg :     0.0197
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t118_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t119_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t120_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t121_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t122_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t123_moi__ALL.jpg :     0.0201
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t124_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t125_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t126_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t127_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t128_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t129_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t130_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t131_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t132_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t133_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t134_moi__ALL.jpg :     0.0208
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t135_moi__ALL.jpg :     0.0207
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t136_moi__ALL.jpg :     0.0201
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t137_moi__ALL.jpg :     0.0202
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t138_moi__ALL.jpg :     0.0200
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t139_moi__ALL.jpg :     0.0201
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t140_moi__ALL.jpg :     0.0201
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t141_moi__ALL.jpg :     0.0203
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t142_moi__ALL.jpg :     0.0226
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t143_moi__ALL.jpg :     0.0228
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t144_moi__ALL.jpg :     0.0240
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t145_moi__ALL.jpg :     0.0305
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t146_moi__ALL.jpg :     0.0204
    CSGOptiX::render_snap@959: /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1/cxr_overview_emm_t0_elv_t147_moi__ALL.jpg :     0.0203
    N[blyth@localhost CSGOptiX]$ 



::

    epsilon:CSGFoundry blyth$ ~/opticks/bin/cat.py -s 144,145,146,147 meshname.txt
    144  145  sBottomRock
    145  146  sWorld
    146  147  solidSJReceiverFastern
    147  148  uni1
    epsilon:CSGFoundry blyth$ 



debug it
----------

::

    N[blyth@localhost CSGOptiX]$ ELV=8 GDB=gdb ./cxr_overview.sh 
                   stamp : 2023-06-04 03:46 
                 version : 70000 
                 TOPLINE : ./cxr_overview.sh    # EYE -0.6,0,0,1 MOI -1 ZOOM 1.5 stamp 2023-06-04 03:46 version 70000 done 
                 BOTLINE :  GEOM V1J008 RELDIR cam_0_tmin_0.4 NAMEPREFIX cxr_overview_emm_t0_elv_8_moi_ SCANNER   
           CVD : 1 
           EMM : t0 
           MOI : -1 
           EYE : -0.6,0,0,1 
           TOP : i0 
           SLA :  
           CAM : perspective 
          TMIN : 0.4 
          ZOOM : 1.5 
    CAMERATYPE : 0 
    OPTICKS_GEOM : cxr_overview 
    OPTICKS_RELDIR : cam_0_tmin_0.4 
          SIZE : 1280,720,1 
     SIZESCALE : 1.5 
        CFBASE :  
    OPTICKS_OUT_FOLD : /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000 
    OPTICKS_OUT_NAME : -1 
    /data/blyth/junotop/ExternalLibs/opticks/head/lib/CSGOptiXRenderTest
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest
    ==== ./cxr.sh render : gdb CSGOptiXRenderTest
    GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-114.el7
      what():  map::at

    Program received signal SIGABRT, Aborted.
    0x00007ffff36fb387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libcom_err-1.42.9-13.el7.x86_64 libicu-50.2-4.el7_7.x86_64 libselinux-2.5-14.1.el7.x86_64 openssl-libs-1.0.2k-25.el7_9.x86_64 pcre-8.32-17.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #7  0x00007ffff7b31486 in std::map<unsigned int, GAS, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, GAS> > >::at (this=0x164a580, 
        __k=@0x7fffffff0f24: 9) at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/include/c++/8.3.0/bits/stl_map.h:548
    #8  0x00007ffff7b2dccc in SBT::getGAS (this=0x164a4d0, gas_idx=9) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:290
    #9  0x00007ffff7b27e09 in IAS_Builder::CollectInstances (instances=..., ias_inst=..., sbt=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/IAS_Builder.cc:70
    #10 0x00007ffff7b283cb in IAS_Builder::Build (ias=..., ias_inst=..., sbt=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/IAS_Builder.cc:113
    #11 0x00007ffff7b2e9c1 in SBT::createIAS (this=0x164a4d0, inst=...) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:551
    #12 0x00007ffff7b2df85 in SBT::createIAS (this=0x164a4d0, ias_idx=0) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:341
    #13 0x00007ffff7b2dda8 in SBT::createIAS_Standard (this=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:317
    #14 0x00007ffff7b2dd3a in SBT::createIAS (this=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:304
    #15 0x00007ffff7b2c70f in SBT::createGeom (this=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:111
    #16 0x00007ffff7b2c578 in SBT::setFoundry (this=0x164a4d0, foundry_=0x6bf830) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:91
    #17 0x00007ffff7ab4126 in CSGOptiX::initGeometry (this=0xd35be0) at /data/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:427
    #18 0x00007ffff7ab2f69 in CSGOptiX::init (this=0xd35be0) at /data/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:335
    #19 0x00007ffff7ab2ac5 in CSGOptiX::CSGOptiX (this=0xd35be0, foundry_=0x6bf830) at /data/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:305
    #20 0x00007ffff7ab259f in CSGOptiX::Create (fd=0x6bf830) at /data/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:230
    #21 0x0000000000419392 in CSGOptiXRenderTest::CSGOptiXRenderTest (this=0x7fffffff4c30) at /data/blyth/junotop/opticks/CSGOptiX/tests/CSGOptiXRenderTest.cc:101
    #22 0x0000000000419c59 in main (argc=1, argv=0x7fffffff51b8) at /data/blyth/junotop/opticks/CSGOptiX/tests/CSGOptiXRenderTest.cc:182
    (gdb) 



    (gdb) f 7
    #7  0x00007ffff7b31486 in std::map<unsigned int, GAS, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, GAS> > >::at (this=0x164a580, 
        __k=@0x7fffffff0f24: 9) at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/include/c++/8.3.0/bits/stl_map.h:548
    548		  __throw_out_of_range(__N("map::at"));


    (gdb) f 8
    #8  0x00007ffff7b2dccc in SBT::getGAS (this=0x164a4d0, gas_idx=9) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:290
    290	    return vgas.at(gas_idx); 
    (gdb) list
    285	const GAS& SBT::getGAS(unsigned gas_idx) const 
    286	{
    287	    unsigned count = vgas.count(gas_idx); 
    288	    LOG_IF(fatal, count == 0) << " no such gas_idx " << gas_idx ; 
    289	    assert( count < 2 ); 
    290	    return vgas.at(gas_idx); 
    291	}

    (gdb) f 9
    #9  0x00007ffff7b27e09 in IAS_Builder::CollectInstances (instances=..., ias_inst=..., sbt=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/IAS_Builder.cc:70
    70	        const GAS& gas = sbt->getGAS(gasIdx); 
    (gdb) list
    65	    for(unsigned i=0 ; i < num_ias_inst ; i++)
    66	    {
    67	        const qat4& q = ias_inst[i] ;   
    68	        int ins_idx,  gasIdx, sensor_identifier, sensor_index ; 
    69	        q.getIdentity(ins_idx, gasIdx, sensor_identifier, sensor_index );
    70	        const GAS& gas = sbt->getGAS(gasIdx); 
    71	        
    72	        bool found = gasIdx_sbtOffset.count(gasIdx) == 1 ; 
    73	        unsigned sbtOffset = found ? gasIdx_sbtOffset.at(gasIdx) : sbt->getOffset(gasIdx, prim_idx ) ;
    74	        if(!found) 
    (gdb) p num_ias_inst
    $1 = 504
    (gdb) p ins_idx
    $2 = 0
    (gdb) p gasIdx
    $3 = 9
    (gdb) 


    (gdb) f 10
    #10 0x00007ffff7b283cb in IAS_Builder::Build (ias=..., ias_inst=..., sbt=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/IAS_Builder.cc:113
    113	    CollectInstances( instances, ias_inst, sbt ); 
    (gdb) list
    108	    assert( num_ias_inst > 0); 
    109	 
    110	    std::vector<OptixInstance> instances ;  
    111	
    112	    LOG(LEVEL) << "[ collect OptixInstance " ;  
    113	    CollectInstances( instances, ias_inst, sbt ); 
    114	    LOG(LEVEL) << "] collect OptixInstance " ;  
    115	
    116	    LOG(LEVEL) << "[ build ias " ;  
    117	    Build(ias, instances); 
    (gdb) 

    (gdb) f 11
    #11 0x00007ffff7b2e9c1 in SBT::createIAS (this=0x164a4d0, inst=...) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:551
    551	    IAS_Builder::Build(ias, inst, this );
    (gdb) list
    546	
    547	void SBT::createIAS(const std::vector<qat4>& inst )
    548	{
    549	    LOG(LEVEL) << "[ inst.size " << inst.size() ; 
    550	    IAS ias = {} ;  
    551	    IAS_Builder::Build(ias, inst, this );
    552	    vias.push_back(ias);  
    553	    LOG(LEVEL) << "] inst.size " << inst.size() ; 
    554	}
    555	
    (gdb) 


    (gdb) f 12
    #12 0x00007ffff7b2df85 in SBT::createIAS (this=0x164a4d0, ias_idx=0) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:341
    341	    createIAS(inst); 
    (gdb) list
    336	
    337	    std::vector<qat4> inst ; 
    338	    foundry->getInstanceTransformsIAS(inst, ias_idx, emm );
    339	    assert( num_ias_inst == inst.size() ); 
    340	
    341	    createIAS(inst); 
    342	    LOG(LEVEL) << descIAS(inst); 
    343	}
    344	
    345	/** 
    (gdb) 


    (gdb) f 13
    #13 0x00007ffff7b2dda8 in SBT::createIAS_Standard (this=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:317
    317	    createIAS(ias_idx); 
    (gdb) list
    312	void SBT::createIAS_Standard()
    313	{
    314	    unsigned num_ias = foundry->getNumUniqueIAS() ; 
    315	    assert( num_ias == 1 );  
    316	    unsigned ias_idx = 0 ; 
    317	    createIAS(ias_idx); 
    318	}
    319	
    320	/**
    321	SBT::createIAS
    (gdb) 


    (gdb) f 14
    #14 0x00007ffff7b2dd3a in SBT::createIAS (this=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:304
    304	        createIAS_Standard(); 
    (gdb) list
    299	
    300	void SBT::createIAS()
    301	{
    302	    if(isStandardIAS())
    303	    {
    304	        createIAS_Standard(); 
    305	    }
    306	    else
    307	    {
    308	        createIAS_Selection();
    (gdb) 

    (gdb) f 15
    #15 0x00007ffff7b2c70f in SBT::createGeom (this=0x164a4d0) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:111
    111	    createIAS(); 
    (gdb) list
    106	void SBT::createGeom()
    107	{
    108	    LOG(LEVEL) << "[" ; 
    109	    createGAS();    
    110	    LOG(LEVEL) << "] createGAS " ; 
    111	    createIAS(); 
    112	    LOG(LEVEL) << "] createIAS " ; 
    113	    createHitgroup(); 
    114	    LOG(LEVEL) << "] createHitGroup " ; 
    115	    checkHitgroup(); 
    (gdb) 



    (gdb) f 16
    #16 0x00007ffff7b2c578 in SBT::setFoundry (this=0x164a4d0, foundry_=0x6bf830) at /data/blyth/junotop/opticks/CSGOptiX/SBT.cc:91
    91	    createGeom(); 
    (gdb) list
    86	**/
    87	
    88	void SBT::setFoundry(const CSGFoundry* foundry_)
    89	{
    90	    foundry = foundry_ ; 
    91	    createGeom(); 
    92	}
    93	
    94	/**
    95	SBT::createGeom




    (gdb) f 17 
    #17 0x00007ffff7ab4126 in CSGOptiX::initGeometry (this=0xd35be0) at /data/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:427
    427	    sbt->setFoundry(foundry); 
    (gdb) list
    422	
    423	#if OPTIX_VERSION < 70000
    424	    six->setFoundry(foundry);
    425	#else
    426	    LOG(LEVEL) << "[ sbt.setFoundry " ; 
    427	    sbt->setFoundry(foundry); 
    428	    LOG(LEVEL) << "] sbt.setFoundry " ; 
    429	#endif
    430	    const char* top = Top(); 
    431	    setTop(top); 
    (gdb) f 18
    #18 0x00007ffff7ab2f69 in CSGOptiX::init (this=0xd35be0) at /data/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:335
    335	    initGeometry();
    (gdb) list
    330	    initSBT();
    331	    initFrameBuffer(); 
    332	    initCheckSim(); 
    333	    initStack(); 
    334	    initParams(); 
    335	    initGeometry();
    336	    initRender(); 
    337	    initSimulate(); 
    338	
    339	    LOG(LEVEL) << "]" ; 
    (gdb) 



