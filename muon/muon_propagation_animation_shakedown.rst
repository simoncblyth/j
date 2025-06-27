~/j/muon/muon_propagation_animation_shakedown.rst
====================================================

FIXED kinked muon issue
-------------------------

* fix was to not treat time zero as valid
* too many zeros in record array to get away with that


Suspicious
------------

* SRecord range giving t0 of zero from the unfilled zeros ? 
* Could be related to high times ? 
* Probably are getting mixing with unfilled zeros to cause the sliding "future kink"

Issue
-------

* floating lines with "future kink"  the length of the artifact gets smaller
  as animation time progresses reaching no artifact at the end of the animation time


How to reproduce issue 
----------------------

1. use EVT bash function to set AFOLD OR BFOLD within the EVT.sh script, 
   somehow muon events show the issue 

2. run cxr_min.sh (OR SGLFW_SOPTIX_Scene_test.sh) 
   and adjust view to a wide one (eg "4" and move upwards)

::

     cxr_min.sh
     SGLFW_SOPTIX_Scene_test.sh


3. alt-A or alt-B to make AFOLD/record or BFOLD/record appear, 
   alt-T to start/restart animation time
 
4. alt-O to switch off geometry in cxr_min.sh


DONE
-----

* improve SRecord::desc and SGLM time dumping from::

    export SGLM__init_time_DUMP


sysrap/gl/rec_flying_point
---------------------------

::
     01 #version 410 core
      2 
      3 uniform mat4 ModelViewProjection ;
      4 uniform vec4 Param ;
      5 
      6 layout (lines) in;
      7 layout (points, max_vertices = 1) out;
      8 
      9 out vec4 fcolor ;
     10 
     11 #define PERSIST 1
     12 // * With PERSIST defined the old rings remain visible after time has gone by
     13 // * Without PERSIST get the traditional flying point visualization
     14 
     15 void main ()
     16 {
     17     vec4 p0 = gl_in[0].gl_Position ;
     18     vec4 p1 = gl_in[1].gl_Position ;
     19     // two consequtive record positions with propagation times in .w
     20     
     21     float tc = Param.w  ;
     22     
     23     uint valid  = (uint(p0.w >= 0.) << 0) + (uint(p1.w >= 0.) << 1) + (uint(p1.w > p0.w) << 2) ;
                                                           ^^^^^^^^^
 
     24     // valid : times >= 0. and ordered correctly (no consideration of tc, input time Param.w)
     25     
     26     uint select = (uint(tc > p0.w ) << 0) + (uint(tc < p1.w) << 1) + (0x1 << 2 )  ;
     27     // select : input time Param tc is between the two point times 
     28     
     29     uint valid_select = valid & select ;
     30     // bitwise combination
     31     
     32     fcolor = vec4(1.0,1.0,1.0,1.0) ; ;
     33     
     34     if(valid_select == 0x7) // both points valid and with tc inbetween the points, so can mix to get position
     35     {
     36         vec3 pt = mix( vec3(p0), vec3(p1), (tc - p0.w)/(p1.w - p0.w) );
     37         gl_Position = ModelViewProjection * vec4( pt, 1.0 ) ;
     38         gl_PointSize = 2. ;
     39         EmitVertex();
     40         EndPrimitive();
     41     }   
     42 #ifdef PERSIST
     43     else if( valid == 0x7 && select == 0x5 )  // both points valid, but time is beyond them both
     44     {
     45         vec3 pt = vec3(p1) ;
     46         gl_Position = ModelViewProjection * vec4( pt, 1.0 ) ;
     47         gl_PointSize = 2. ;
     48         EmitVertex();
     49         EndPrimitive();
     50     }   
     51 #endif  
     52 }









time dumping 
---------------

::

    SGLM::init_time [SGLM__init_time_DUMP]  YES
     t_noenv YES
     ar
     [SRecord.desc
     lpath [/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/python3.11/ALL0_no_opticks_event_name/A001/record.npy]
                     mn (-21626.807,-21646.861, 0.000, 0.000) 
                     mx (21646.838,24500.000,49228.219,386.943) 
                     ce (10.016,1426.569,24614.109,24614.109) 
            record.sstr (29823, 32, 4, 4, )
           record_first 0
           record_count 954336
    [NP::descMeta
    [NP::DescMetaKVS only_with_stamp : NO 
    [NP::DescMetaKVS_kvs  keys.size 15 vals.size 15 tt.size 15 num_keys 15
                              rpos :      4,GL_FLOAT,GL_FALSE,64,0,false                                                                  
         SRecord__LoadArray_METHOD :                       NP::LoadSlice                                                                  
          SRecord__LoadArray_SLICE :                 $AFOLD_RECORD_SLICE                                                                  
                                x0 :                            -21626.8                                                                  
                                y0 :                            -21646.9                                                                  
                                z0 :                                   0                                                                  
                                t0 :                                   0                                                                  
                                x1 :                             21646.8                                                                  
                                y1 :                               24500                                                                  
                                z1 :                             49228.2                                                                  
                                t1 :                             386.943                                                                  
                                cx :                             10.0156                                                                  
                                cy :                             1426.57                                                                  
                                cz :                             24614.1                                                                  
                                ce :                             24614.1                                                                  
    ]NP::DescMetaKVS_kvs
    ]NP::DescMetaKVS
    ]NP::descMeta

    ]SRecord.desc

     br
     -
    [SGLM::desc_time
     T0   0.000
     T1   0.000
     t    0.000
     t0   0.000
     t1 386.943
     ts   0.077
     tn   5000
    ]SGLM::desc_time








EVT.sh
-------

::


     09 if [ "$GEOM" == "J25_4_0_opticks_Debug" ]; then
     10 
     11     #check=muon_cxs
     12     check=muon_om1
     13     #check=wp_pmt_ipc
     14     #check=wp_pmt_cxs
     15     #check=Hama
     16     #check=SPMT_ipc
     17     #check=SPMT_cxs
     18 
     19     if [ "$check" == "muon_cxs" ]; then
     20 
     21         afold=/data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL98_Debug_Philox_input_genstep_muon/A006
     22         export AFOLD=${AFOLD:-$afold}
     23 
     24         #afold_record_slice=[::1000]
     25         #afold_record_slice=[::100]
     26         afold_record_slice=[:1000000]
     27         export AFOLD_RECORD_SLICE=$afold_record_slice
     28 
     29 
     30     elif [ "$check" == "muon_om1" ]; then
     31 
     32         afold=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/python3.11/ALL0_no_opticks_event_name/A001
     33         export AFOLD=${AFOLD:-$afold}








::

    A[blyth@localhost ALL0_no_opticks_event_name]$ pwd
    /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/python3.11/ALL0_no_opticks_event_name
    A[blyth@localhost ALL0_no_opticks_event_name]$ du -h A???/record.npy
    59M	    A001/record.npy
    6.0M	A003/record.npy
    4.3M	A004/record.npy
    16M	    A005/record.npy
    66G	    A006/record.npy
    3.3M	A008/record.npy




Lots of very shortlived photons
--------------------------------

::

    ~/j/muon/muon.sh pdb

    In [16]: a.qtab
    Out[16]: 
    array([[b'16165', b'0', b'CK SA                                                                                           '],
           [b'9852', b'104', b'CK AB                                                                                           '],
           [b'1058', b'2307', b'CK BT SA                                                                                        '],
           [b'562', b'5562', b'CK BT BT SA                                                                                     '],
           [b'551', b'2320', b'CK DR BT SA                                                                                     '],
           [b'315', b'2315', b'CK DR AB                                                                                        '],
           [b'302', b'2328', b'CK BT BT AB                                                                                     '],
           [b'287', b'2322', b'CK BR AB                                                                                        '],
           [b'230', b'2313', b'CK BT AB                                                                                        '],
           [b'94', b'2310', b'CK DR BT AB                                                                                     ']], dtype='|S96')


    In [18]: w = a.q_startswith("CK SA")


    In [22]: a.f.record[w,:2,0]
    Out[22]: 
    array([[[-4022.399,  -902.223, 49228.22 ,    67.348],
            [-4620.618, 22287.566, 37300.87 ,   154.379]],

           [[-4023.11 ,  -876.913, 49215.938,    67.442],
            [-4845.418, 20874.9  , 39233.242,   147.343]],

           [[-4022.685,  -892.034, 49223.273,    67.386],
            [-4117.133, 21275.566, 38721.082,   149.23 ]],

           [[-4023.55 ,  -861.243, 49208.332,    67.5  ],
            [-4521.483, 22265.705, 37333.723,   154.257]],

           [[-4024.096,  -841.791, 49198.89 ,    67.572],
            [-4333.297, 20932.908, 39160.664,   147.58 ]],

           ...,

           [[ 8685.115, 24478.775, 30786.857,   169.283],
            [ 8684.409, 24500.   , 30775.959,   169.363]],

           [[ 8685.629, 24460.248, 30795.842,   169.215],
            [ 8683.502, 24500.   , 30776.678,   169.362]],

           [[ 8685.533, 24463.69 , 30794.174,   169.227],
            [ 8685.052, 24500.   , 30777.434,   169.361]],

           [[ 8684.587, 24497.873, 30777.598,   169.354],
            [ 8684.529, 24500.   , 30776.627,   169.362]],

           [[ 8684.96 , 24484.412, 30784.125,   169.304],
            [ 8684.822, 24500.   , 30776.256,   169.363]]], shape=(16165, 2, 4), dtype=float32)


::

    ANIM=1 T0=60 T1=100 SGLFW_SOPTIX_Scene_test.sh

     ANIM=1 T0=30 T1=200 SGLFW_SOPTIX_Scene_test.sh

