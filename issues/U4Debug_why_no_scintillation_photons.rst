U4Debug_why_no_scintillation_photons
=======================================


::

    epsilon:tests blyth$ ./U4Debug.sh 
    Fold : symbol f00 base /tmp/u4debug/ntds0/000 
    Fold : symbol f01 base /tmp/u4debug/ntds0/001 
    Fold : symbol f30 base /tmp/u4debug/ntds3/000 
    Fold : symbol f31 base /tmp/u4debug/ntds3/001 
    f00c     (8, 8) f00s    (47, 8) 
    f01c     (7, 8) f01s    (51, 8) 
    f30c     (8, 8) f30s    (47, 8) 
    f31c     (7, 8) f31s    (51, 8) 

    In [1]: f00c
    Out[1]: 
    array([[  53.764,  -89.174, -212.824,    0.815,    1.283,    0.394,   37.924,   34.   ],
           [  53.854,  -89.508, -212.887,    0.817,    1.368,    0.31 ,   20.278,   23.   ],
           [  53.991,  -89.643, -213.075,    0.818,    1.504,    0.255,    6.834,    4.   ],
           [  42.551,  -71.68 , -206.441,    0.743,    1.218,    0.474,   59.591,   70.   ],
           [  42.491,  -71.6  , -206.856,    0.744,    1.27 ,    0.397,   40.393,   36.   ],
           [  42.203,  -71.571, -207.061,    0.746,    1.346,    0.33 ,   23.966,   26.   ],
           [  42.094,  -71.577, -207.329,    0.747,    1.479,    0.265,    9.393,    4.   ],
           [  42.012,  -71.536, -207.533,    0.748,    1.664,    0.144,    0.564,    1.   ]])

    In [2]: f00s
    Out[2]: 
    array([[   0.   ,    0.   ,    0.   ,    0.   , 9846.   ,    0.   ,    0.   ,    0.   ],
           [  42.551,  -71.68 , -206.441,    0.743, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  53.764,  -89.174, -212.824,    0.815, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  66.251,  -69.446, -217.664,    0.895, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  63.812,  -79.847, -230.84 ,    0.951, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  77.33 ,   -7.587, -288.96 ,    1.264, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  60.371,  113.585, -418.662,    1.859, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  54.318,  117.991, -420.922,    1.885, 9846.   ,    0.   ,    0.   ,    0.   ],
           [   5.766,  113.45 , -421.511,    2.047, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ -21.653,   92.162, -430.589,    2.167, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ -21.626,   92.568, -430.728,    2.168, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ -18.828,   94.101, -417.725,    2.213, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  39.827,   92.089, -335.339,    2.551, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  46.673,   97.155, -333.627,    2.58 , 9846.   ,    0.   ,    0.   ,    0.   ],
           [  57.432,  112.899, -305.613,    2.693, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  49.185,  145.006, -323.266,    2.818, 9846.   ,    0.   ,    0.   ,    0.   ],
           ...




Hmm, associate a hit with the original S or C photon ?

::

     09 NormalTrackInfo::NormalTrackInfo()
     10 {   
     11     originalTrackID = 0;

     20 NormalTrackInfo::NormalTrackInfo(const G4Track* aTrack)
     21 {
     22     originalTrackID = aTrack->GetTrackID();
     23         
     24     // phys

     35 NormalTrackInfo::NormalTrackInfo(const NormalTrackInfo* aTrackInfo)
     36 {       
     37     originalTrackID = aTrackInfo->originalTrackID;
     38     tracedAncestors = aTrackInfo->tracedAncestors;
     39         
     40     // phys
     41     phys_michael_electron = 0;
     42     phys_neutron_capture = 0;
     43     phys_decay_mode = 0;
     44         
     45     from_cerenkov = aTrackInfo->from_cerenkov; 
     46     is_reemission = aTrackInfo->is_reemission;


::

    346 void
    347 NormalAnaMgr::PreUserTrackingAction(const G4Track* aTrack) {
    348 
    349   if(aTrack->GetParentID()==0 && aTrack->GetUserInformation()==0)
    350     {
    351         NormalTrackInfo* anInfo = new NormalTrackInfo(aTrack);
    352         G4Track* theTrack = (G4Track*)aTrack;
    353         theTrack->SetUserInformation(anInfo);
    354     }
    355     NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    356 




BP=NormalTrackInfo::NormalTrackInfo ntds0


::

    junoSD_PMT_v2::SaveNormHit pmtID   13240 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID    7036 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID   13078 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID    7924 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID   17230 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID   11254 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID    6096 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID   14790 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID   16264 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID    5089 producerID      -1 is_from_cerenkov 0 is_reemission 0
     dir /tmp/u4debug/ntds0/000 num_record 8
     dir /tmp/u4debug/ntds0/000 num_record 47
    [ junoSD_PMT_v2::EndOfEvent m_opticksMode  0
    ] junoSD_PMT_v2::EndOfEvent m_opticksMode  0
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 14 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize
    Begin of Event --> 1
    junoSD_PMT_v2::SaveNormHit pmtID   12227 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID  303004 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID    9725 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID    8996 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID    5195 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID    7738 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID   16857 producerID      -1 is_from_cerenkov 0 is_reemission 0
    junoSD_PMT_v2::SaveNormHit pmtID    3271 producerID      -1 is_from_cerenkov 0 is_reemission 0
     dir /tmp/u4debug/ntds0/001 num_record 7





