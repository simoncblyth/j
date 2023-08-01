opticksMode3-comparison
==========================



::

    epsilon:ALL1 blyth$ ls -1 p001/         
    ## NPFold_meta.txt                          
    ## hit.npy

    NPFold_index.txt                        
    domain.npy                              
    domain_meta.txt                         
    flat.npy                                
    genstep.npy                             
    inphoton.npy
    junoSD_PMT_v2_Opticks.npy
    junoSD_PMT_v2_Opticks_meta.txt
    junoSD_PMT_v2_Opticks_names.txt
    photon.npy
    prd.npy
    record.npy
    record_meta.txt
    seq.npy
    sframe.npy
    sframe_meta.txt
    tag.npy


::

    epsilon:ALL1 blyth$ ls -1 n001/
    ## aux.npy
    ## sup.npy
    ## gs.npy
    ## pho.npy
    ## pho0.npy
    ## photon_meta.txt

    NPFold_index.txt
    domain.npy
    domain_meta.txt
    flat.npy
    genstep.npy
    inphoton.npy
    junoSD_PMT_v2_Opticks.npy
    junoSD_PMT_v2_Opticks_meta.txt
    junoSD_PMT_v2_Opticks_names.txt
    photon.npy
    prd.npy
    record.npy
    record_meta.txt
    seq.npy
    sframe.npy
    sframe_meta.txt
    tag.npy


::

    epsilon:tests blyth$ ./SEvt__LoadTest.sh 
             BASH_SOURCE : ./SEvt__LoadTest.sh 
                    GEOM : V1J009 
                    FOLD : /tmp/SEvt__LoadTest 
          OPTICKS_PREFIX : /usr/local/opticks 
             CUDA_PREFIX : /usr/local/cuda 
                   AFOLD : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 
                   BFOLD : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001 
    af.desc
    NPFold::desc_subfold
     tot_items 10
     folds 1
     paths 1
    0 [/]
    NPFold::desc(0) 
    NPFold::desc depth 0
     loaddir:/tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 subfold 0 ff 0 kk 10 aa 10
             genstep.npy : (1, 6, 4, )
              photon.npy : (100, 4, 4, )
              record.npy : (100, 32, 4, 4, )
                 seq.npy : (100, 2, 2, )
                 prd.npy : (100, 32, 2, 4, )
                 hit.npy : (32, 4, 4, )
              domain.npy : (2, 4, 4, )
            inphoton.npy : (100, 4, 4, )
                 tag.npy : (100, 4, )
                flat.npy : (100, 64, )


    bf.desc
    NPFold::desc_subfold
     tot_items 11
     folds 1
     paths 1
    0 [/]
    NPFold::desc(0) 
    NPFold::desc depth 0
     loaddir:/tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001 subfold 0 ff 0 kk 11 aa 11
             genstep.npy : (1, 6, 4, )
              photon.npy : (100, 4, 4, )
              record.npy : (100, 32, 4, 4, )
                 seq.npy : (100, 2, 2, )
                 prd.npy : (100, 32, 2, 4, )
              domain.npy : (2, 4, 4, )
            inphoton.npy : (100, 4, 4, )
                 tag.npy : (100, 4, )
                flat.npy : (100, 64, )
                 aux.npy : (100, 32, 4, 4, )
                 sup.npy : (100, 6, 4, )




