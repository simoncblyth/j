cxr_table_snap_times
=======================

* still with the PMTs in hatboxes as name changes need to be accomodated 
* TODO: examine the translation logging and update arguments 
* TODO: complete the checks of the cx scripts 

* below timings are not to be trusted until remove the hatboxes 

::

    epsilon:CSGOptiX blyth$ ./cxr_table.sh 
    idx         -e        time(s)           relative         enabled geometry description                                              
      0         5,         0.0004             0.0720         ONLY: 1:sStrutBallhead                                                    
      1         9,         0.0004             0.0744         ONLY: 130:sPanel                                                          
      2         7,         0.0004             0.0768         ONLY: 1:base_steel                                                        
      3         6,         0.0006             0.1127         ONLY: 1:uni1                                                              
      4         1,         0.0009             0.1595         ONLY: 5:PMT_3inch_pmt_solid                                               
      5         8,         0.0010             0.1768         ONLY: 1:uni_acrylic3                                                      
      6         4,         0.0014             0.2636         ONLY: 6:mask_PMT_20inch_vetosMask_virtual                                 
      7         3,         0.0036             0.6541         ONLY: 7:HamamatsuR12860sMask_virtual                                      
      8         0,         0.0040             0.7291         ONLY: 3084:sWorld                                                         
      9         2,         0.0040             0.7316         ONLY: 7:NNVTMCPPMTsMask_virtual                                           
     10        t2,         0.0052             0.9530         EXCL: 7:NNVTMCPPMTsMask_virtual                                           
     11        t4,         0.0053             0.9637         EXCL: 6:mask_PMT_20inch_vetosMask_virtual                                 
     12    1,2,3,4         0.0055             1.0000         ONLY PMT                                                                  
     13        t5,         0.0056             1.0155         EXCL: 1:sStrutBallhead                                                    
     14         t0         0.0057             1.0312         3084:sWorld                                                               
     15        t1,         0.0057             1.0315         EXCL: 5:PMT_3inch_pmt_solid                                               
     16        t9,         0.0057             1.0361         EXCL: 130:sPanel                                                          
     17        t6,         0.0057             1.0376         EXCL: 1:uni1                                                              
     18        t8,         0.0057             1.0408         EXCL: 1:uni_acrylic3                                                      
     19        t3,         0.0057             1.0447         EXCL: 7:HamamatsuR12860sMask_virtual                                      
     20        t7,         0.0058             1.0569         EXCL: 1:base_steel                                                        
     21        t0,         0.0059             1.0731         EXCL: 3084:sWorld                                                         
     22       t8,0         0.0059             1.0749         EXCL: 1:uni_acrylic3 3084:sWorld                                          
    idx         -e        time(s)           relative         enabled geometry description                                              




./cxr_view.sh 

* sWaterTube view very clearly shows the PMT hatboxes 




