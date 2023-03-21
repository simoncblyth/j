blyth-88-simulation-history-comparison-checks
===============================================

* prior :doc:`blyth-88-ModelTrigger_Debug`


NEXT : Fake skip checking 
-----------------------------

Before moving to two_pmt layout try to reduce the manual config 
for fake skipping which becomes more of a liability when testing 
with more PMTs.

* HMM: need to look at fakemask bits to see how many with only FAKE_MANUAL  


U4Recorder::

    614     unsigned fakemask = FAKES_SKIP ? ClassifyFake(step, flag, spec, PIDX_DUMP ) : 0 ;
    615     bool is_fake = fakemask > 0 && ( flag == BOUNDARY_TRANSMIT || flag == BOUNDARY_REFLECT ) ;
    616 
    617     int st = ( is_fake ? -1 : 1 )*SPECS.add(spec, false ) ;   // DO NOT SEE -ve AT PYTHON LEVEL AS THEY GET SKIPPED
    618 
    619     current_aux.q2.i.z = fakemask ;  // CAUTION: stomping on cdbg.pmtid setting above  
    620     current_aux.q2.i.w = st ;
    621 
    622     LOG_IF(info, PIDX_DUMP )
    623         << " l.id " << std::setw(3) << label->id
    624         << " step_mm " << std::fixed << std::setw(10) << std::setprecision(4) << step_mm
    625         << " abbrev " << OpticksPhoton::Abbrev(flag)
    626         << " spec " << std::setw(50) << spec
    627         << " st " << std::setw(3) << st
    628         << " is_fake " << ( is_fake ? "YES" : "NO " )
    629         << " fakemask " << fakemask
    630         << " U4Fake::Desc " << U4Fake::Desc(fakemask)
    631         ;



    In [3]: fm = a.aux[:,:,2,2].view(np.uint32)

    In [6]: w_fm = np.where( fm > 0 ) ; w_fm 
    Out[6]: 
    (array([  20,  579, 1112, 1540, 1661, 1787, 1867, 2060, 2210, 2597, 2697, 2816, 2895, 3357, 3382, 3964, 4075, 4298, 4307, 4525, 4686, 5220, 5222, 5405, 5437, 5466, 5528, 5815, 6303, 6341, 6376, 6620,
            7104, 7407, 7626, 7727, 7847, 8102, 8208, 8383, 8838, 8966, 9362, 9453, 9504, 9587]),
     array([1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]))


    In [2]: fm = t.aux[:,:,2,2].view(np.uint32)
    In [4]: fm[fm > 0]
    Out[4]: array([], dtype=uint32)   


DISABLE FAKE SKIPPING TO STUDY THE FAKES

FewPMT.sh::

    147     f0=Pyrex/Pyrex:AroundCircle0/hama_body_phys
    148     f1=Pyrex/Pyrex:hama_body_phys/AroundCircle0
    149     f2=Vacuum/Vacuum:hama_inner1_phys/hama_inner2_phys
    150     f3=Vacuum/Vacuum:hama_inner2_phys/hama_inner1_phys
    151     f4=Pyrex/Pyrex:AroundCircle1/nnvt_body_phys
    152     f5=Pyrex/Pyrex:nnvt_body_phys/AroundCircle1
    153     f6=Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys
    154     f7=Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys
    155 
    156     f8=Pyrex/Pyrex:nnvt_body_phys/nnvt_log_pv
    157     f9=Pyrex/Pyrex:nnvt_log_pv/nnvt_body_phys
    158 
    159     case $LAYOUT in
    160        two_pmt) fakes="$f0,$f1,$f2,$f3,$f4,$f5,$f6,$f7" ;;
    161        one_pmt) fakes="$f0,$f1,$f2,$f3,$f4,$f5,$f6,$f7,$f8,$f9" ;;
    162     esac
    163 
    164     export U4Recorder__FAKES="$fakes"
    165     ##export U4Recorder__FAKES_SKIP=1


That gives terrible chi2 as expected:: 

    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/hamaLogicalPMT/ModelTriggerSimple/one_pmt/rain_line 
    c2sum : 15067.0742 c2n :    22.0000 c2per:   684.8670  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                                                                       ' ' 0' '     0   3825' '3825.0000' '    -1    126']
     [' 1' 'TO BT BT SD                                                                                    ' ' 1' '  3819      0' '3819.0000' '   126     -1']
     [' 2' 'TO BT BT SA                                                                                    ' ' 2' '  3234   1231' '898.5463' '   131   1108']
     [' 3' 'TO BT SA                                                                                       ' ' 3' '     0   3223' '3223.0000' '    -1    125']
     [' 4' 'TO BT BT BT BT SA                                                                              ' ' 4' '  1219      4' '1207.0524' '  1371   1161']
     [' 5' 'TO BT BT SR SA                                                                                 ' ' 5' '     0    396' '396.0000' '    -1   1252']
     [' 6' 'TO BT BT BT BT SR SA                                                                           ' ' 6' '   356      0' '356.0000' '  1350     -1']
     [' 7' 'TO BT BT BR BT BT SA                                                                           ' ' 7' '   328      0' '328.0000' '   156     -1']


HUH still none::

    In [3]: fm = a.aux[:,:,2,2].view(np.uint32)
    In [4]: fm[fm>0]
    Out[4]: array([], dtype=uint32)
    In [5]: np.all( fm == 0 )
    Out[5]: True


Change to always ClassifyFake::

    614     unsigned fakemask = ClassifyFake(step, flag, spec, PIDX_DUMP ) ;                 
    615     bool is_fake = FAKES_SKIP && fakemask > 0 && ( flag == BOUNDARY_TRANSMIT || flag == BOUNDARY_REFLECT ) ;
    616     int st = ( is_fake ? -1 : 1 )*SPECS.add(spec, false ) ;   // DO NOT SEE -ve AT PYTHON LEVEL AS THEY GET SKIPPED
    617     
    618     current_aux.q2.i.z = fakemask ;  // CAUTION: stomping on cdbg.pmtid setting above  
    619     current_aux.q2.i.w = st ; 


::

    In [1]: fm = a.aux[:,:,2,2].view(np.uint32)
    In [5]: fm.shape
    Out[5]: (10000, 32)

    In [6]: w_fm = np.where( fm > 0 ) ; w_fm
    Out[6]: 
    (array([  99,  117,  117,  117,  117, ..., 9878, 9880, 9880, 9881, 9881]),
     array([3, 2, 4, 6, 8, ..., 2, 2, 4, 2, 4]))

    In [9]: aq[w_fm[0]]
    Out[9]: 
    array([[b'TO SC BT BT SD                                                                                  '],
           [b'TO BT BT SR BT BR BT SR BT BT SA                                                                '],
           [b'TO BT BT SR BT BR BT SR BT BT SA                                                                '],
           [b'TO BT BT SR BT BR BT SR BT BT SA                                                                '],
           [b'TO BT BT SR BT BR BT SR BT BT SA                                                                '],
           ...,
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            ']], dtype='|S96')


    In [14]: np.c_[np.unique(fm, return_counts=True)]
    Out[14]: 
    array([[     0, 306952],
           [     4,   9633],       FAKE_SURFACE
           [     6,    527],       FAKE_SURFACE | FAKE_FDIST
           [     8,   2888]])      FAKE_MANUAL


     06 struct U4Fake
      7 {
      8     enum {
      9         FAKE_STEP_MM = 0x1 << 0,    // 1 
     10         FAKE_FDIST   = 0x1 << 1,    // 2
     11         FAKE_SURFACE = 0x1 << 2,    // 4
     12         FAKE_MANUAL  = 0x1 << 3     // 8
     13         };
     14 


    In [7]: np.c_[np.unique(a.qq[w_fk], return_counts=True)]
    Out[7]: array([[   12, 13048]])

    In [8]: BOUNDARY_TRANSMIT = 0x1 << 11

    In [9]: BOUNDARY_TRANSMIT.bit_length()
    Out[9]: 12



single point (-300,0,-10) (1,0,0) shooting the reflector : chi2 matches
---------------------------------------------------------------------------

::

    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/nnvtLogicalPMT/ModelTriggerSimple/one_pmt/lhs_reflector_point 
    c2sum :     5.3059 c2n :     7.0000 c2per:     0.7580  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SR BT SA            ' ' 0' '  9043   9055' ' 0.0080' '     1      1']
     [' 1' 'TO BT SA                  ' ' 1' '   826    794' ' 0.6321' '     0      0']
     [' 2' 'TO BT AB                  ' ' 2' '    37     30' ' 0.7313' '   124    268']
     [' 3' 'TO BT SR AB               ' ' 3' '    33     30' ' 0.1429' '   246    529']
     [' 4' 'TO BR SA                  ' ' 4' '    20     25' ' 0.5556' '   398    161']
     [' 5' 'TO BT SR BR SR BT SA      ' ' 5' '    11     21' ' 3.1250' '   852    492']
     [' 6' 'TO BT SR BT AB            ' ' 6' '    17     19' ' 0.1111' '   118    617']
     [' 7' 'TO AB                     ' ' 7' '     5     17' ' 0.0000' '  2701   1539']
     [' 8' 'TO BT SR BR SA            ' ' 8' '     4      2' ' 0.0000' '   102    356']
     [' 9' 'TO BT SR BT SC SA         ' ' 9' '     3      3' ' 0.0000' '    14   3473']
     ['10' 'TO SC SA                  ' '10' '     0      2' ' 0.0000' '    -1   6309']
     ['11' 'TO BT SR BT SC BT SR BT SA' '11' '     1      1' ' 0.0000' '  2791   2600']
     ['12' 'TO BR AB                  ' '12' '     0      1' ' 0.0000' '    -1   3014']]



FewPMT/nnvtLogicalPMT/ModelTriggerSimple/one_pmt/lhs_reflector_line  and hama chi2 match
-------------------------------------------------------------------------------------------

::

    172     elif [ "$CHECK" == "lhs_reflector_line" ]; then
    173 
    174         ttype=line
    175         radius=95
    176         pos=-300,0,-95   ## line from (-300,0,0) to (-300,0,-190)
    177         mom=1,0,0
    178 


* note there are no "TO BT BT" : no photon gets into the PMT here 
* note some "optical fiber"-ing around the pyrex leading to truncation::

  TO BT SR BR SR BR SR BR SR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR SR BR  

* SR: surface reflection with the lower hemi, 
* BR: fresnel Pyrex/Water boundary reflection


::

    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/nnvtLogicalPMT/ModelTriggerSimple/one_pmt/lhs_reflector_line 
    c2sum :     6.4809 c2n :    10.0000 c2per:     0.6481  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SR BT SA                                                                                 ' ' 0' '  8011   7940' ' 0.3160' '     1      1']
     [' 1' 'TO SA                                                                                          ' ' 1' '   862    862' ' 0.0000' '  9118   9118']
     [' 2' 'TO BT SA                                                                                       ' ' 2' '   716    732' ' 0.1768' '    12      0']
     [' 3' 'TO BR SA                                                                                       ' ' 3' '   116    122' ' 0.1513' '   421    242']
     [' 4' 'TO BT SR BR SR BT SA                                                                           ' ' 4' '    56     73' ' 2.2403' '   875    748']
     [' 5' 'TO AB                                                                                          ' ' 5' '    33     39' ' 0.5000' '    19   2570']
     [' 6' 'TO BT AB                                                                                       ' ' 6' '    29     37' ' 0.9697' '     0    524']
     [' 7' 'TO BT SR BR SR BR SR BR SR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR' ' 7' '    25     36' ' 1.9836' '  9027   9026']
     [' 8' 'TO BT SR AB                                                                                    ' ' 8' '    27     28' ' 0.0182' '   269    126']
     [' 9' 'TO BT SR BT AB                                                                                 ' ' 9' '    15     17' ' 0.1250' '   141     87']
     ['10' 'TO BT SR BR SA                                                                                 ' '10' '    15     13' ' 0.0000' '   125    612']
     ['11' 'TO BT SR BR SR BR SA                                                                           ' '11' '     9     13' ' 0.0000' '  8981   8731']
     ['12' 'TO BT SR BR SR BR SR BR SA                                                                     ' '12' '     5      7' ' 0.0000' '  9008   9010']
     ['13' 'TO BT SR BR SR BR SR BR SR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR SR BR' '13' '     6      7' ' 0.0000' '  8991   8989']
     ['14' 'TO BT SR BR SR BR SR BR SR BR SR BR SR BT SA                                                   ' '14' '     6      4' ' 0.0000' '  8723   8707']
     ['15' 'TO BT SR BR SR BR SR BR SR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR SR BR SR' '15' '     6      3' ' 0.0000' '  8977   8976']
     ['16' 'TO BT SR BR SR BR SR BR SR BR BR BR BR BR BR BR BR BR BR BR BR AB                              ' '16' '     0      5' ' 0.0000' '    -1   8990']
     ['17' 'TO BT SR BR SR BR SR BR SR BR BR AB                                                            ' '17' '     1      5' ' 0.0000' '  9094   9017']
     ['18' 'TO BT SR BR SR BR SR BR SR BR BR BR BR BR BR BR BR AB                                          ' '18' '     2      5' ' 0.0000' '  8989   8985']
     ['19' 'TO SC SA                                                                                       ' '19' '     5      3' ' 0.0000' '  3691   9717']
     ['20' 'TO BT SR BT SC SA                                                                              ' '20' '     5      2' ' 0.0000' '  1753   3731']
     ['21' 'TO BT SR BR SR BR SR BR SR BR BR BR BR BR BR BR AB                                             ' '21' '     4      2' ' 0.0000' '  8985   9062']
     ['22' 'TO BT SR BR AB                                                                                 ' '22' '     1      4' ' 0.0000' '  9060   8785']
     ['23' 'TO BT SR BR SR BR SR BR AB                                                                     ' '23' '     4      1' ' 0.0000' '  8997   9033']
     ['24' 'TO BT SR BR SR BR SR BR SR BR AB                                                               ' '24' '     3      3' ' 0.0000' '  9014   8978']]



    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/hamaLogicalPMT/ModelTriggerSimple/one_pmt/lhs_reflector_line 
    c2sum :    13.4250 c2n :    12.0000 c2per:     1.1187  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SR BT SA            ' ' 0' '  7931   7853' ' 0.3855' '     1      1']
     [' 1' 'TO SA                     ' ' 1' '   863    863' ' 0.0000' '     0      0']
     [' 2' 'TO BT SA                  ' ' 2' '   703    756' ' 1.9253' '     2     19']
     [' 3' 'TO BT SR BR BT SA         ' ' 3' '   113    126' ' 0.7071' '  8863   8863']
     [' 4' 'TO BT SR BT BT BT SA      ' ' 4' '    89     87' ' 0.0227' '  8073   8073']
     [' 5' 'TO BT SR AB               ' ' 5' '    56     43' ' 1.7071' '   110     16']
     [' 6' 'TO BT SR SR BT SA         ' ' 6' '    55     51' ' 0.1509' '  8324   8324']
     [' 7' 'TO BR SA                  ' ' 7' '    40     49' ' 0.9101' '   307   1054']
     [' 8' 'TO BT AB                  ' ' 8' '    35     40' ' 0.3333' '   140    372']
     [' 9' 'TO BT SR BR SR BT SA      ' ' 9' '    21     38' ' 4.8983' '   190    951']
     ['10' 'TO AB                     ' '10' '    30     35' ' 0.3846' '  3150    894']
     ['11' 'TO BT SR BT BR SA         ' '11' '    12     20' ' 2.0000' '  8076   8077']
     ['12' 'TO BT SR BT AB            ' '12' '    13     12' ' 0.0000' '   824    327']
     ['13' 'TO SC SA                  ' '13' '     9      5' ' 0.0000' '  3185   3492']
     ['14' 'TO BT SR BR AB            ' '14' '     6      1' ' 0.0000' '  8867   8914']
     ['15' 'TO BR BT BT SA            ' '15' '     5      4' ' 0.0000' '  8393   8422']
     ['16' 'TO BT SR BR SA            ' '16' '     4      2' ' 0.0000' '  1356   3665']
     ['17' 'TO BT SR SA               ' '17' '     4      4' ' 0.0000' '  8333   8326']
     ['18' 'TO BT SR BT SC SA         ' '18' '     2      3' ' 0.0000' '  1068   2642']
     ['19' 'TO SC BT SR BT SA         ' '19' '     2      2' ' 0.0000' '  8351   5780']
     ['20' 'TO BT SR BR SR SR BT SA   ' '20' '     0      2' ' 0.0000' '    -1   8032']
     ['21' 'TO BT SR BT BT BR SR BT SA' '21' '     2      0' ' 0.0000' '  8111     -1']
     ['22' 'TO BT SR BT SC BT SR BT SA' '22' '     0      2' ' 0.0000' '    -1   1955']
     ['23' 'TO BT SR BR SR BT BT BT SA' '23' '     1      0' ' 0.0000' '  7829     -1']
     ['24' 'TO BT SR BR SR BR SR BT SA' '24' '     0      1' ' 0.0000' '    -1   8235']]





FewPMT/nnvtLogicalPMT/ModelTriggerSimple/one_pmt/rain_line and hama OK
-------------------------------------------------------------------------

::

    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/nnvtLogicalPMT/ModelTriggerSimple/one_pmt/rain_line 
    c2sum :    26.2282 c2n :    21.0000 c2per:     1.2490  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                                                                       ' ' 0' '  3845   3732' ' 1.6852' '   129    128']
     [' 1' 'TO BT SA                                                                                       ' ' 1' '  3243   3299' ' 0.4794' '   133    129']
     [' 2' 'TO BT BT SR SA                                                                                 ' ' 2' '   460    474' ' 0.2099' '  1211   1218']
     [' 3' 'TO BT BT SR BT BT SA                                                                           ' ' 3' '   438    463' ' 0.6937' '  2144   2152']
     [' 4' 'TO BT BT SA                                                                                    ' ' 4' '   422    446' ' 0.6636' '  1094   1057']
     [' 5' 'TO BT BR BT SA                                                                                 ' ' 5' '   335    325' ' 0.1515' '   156    132']
     [' 6' 'TO SA                                                                                          ' ' 6' '   229    230' ' 0.0022' '     0      0']
     [' 7' 'TO BT BT SR BR SR SA                                                                           ' ' 7' '   120    122' ' 0.0165' '  2268   2311']
     [' 8' 'TO BT BT SR BR SA                                                                              ' ' 8' '   108    119' ' 0.5330' '  2297   2181']
     [' 9' 'TO BR SA                                                                                       ' ' 9' '   101     94' ' 0.2513' '   116    116']
     ['10' 'TO BT BT SR SR SA                                                                              ' '10' '    62     86' ' 3.8919' '  1227   1228']
     ['11' 'TO BT BT SR BR SR BT BT SA                                                                     ' '11' '    61     71' ' 0.7576' '  2258   2223']
     ['12' 'TO BT BT SR BR SR SR SA                                                                        ' '12' '    24     39' ' 3.5714' '  2568   2420']
     ['13' 'TO BT BT SR SR BT BT SA                                                                        ' '13' '    37     25' ' 2.3226' '  1851   1836']
     ['14' 'TO BT BT SR BR SR SR BT BT SA                                                                  ' '14' '    30     36' ' 0.5455' '  2406   2539']
     ['15' 'TO BT AB                                                                                       ' '15' '    35     33' ' 0.0588' '   231    313']
     ['16' 'TO BT BT SR BR SR BR SR BT BT SA                                                               ' '16' '    28     26' ' 0.0741' '  2291   2975']
     ['17' 'TO BT BT SR SR SR SA                                                                           ' '17' '    27     17' ' 2.2727' '  1197   1413']
     ['18' 'TO BT BT SR SR SR BT BT SA                                                                     ' '18' '    25     24' ' 0.0204' '  1368   1371']
     ['19' 'TO BT BT SR BR SR BR SA                                                                        ' '19' '    24      8' ' 8.0000' '  2292   5632']
     ['20' 'TO BT BT SR BR SR BR SR SA                                                                     ' '20' '    18     19' ' 0.0270' '  3073   2252']
     ['21' 'TO BT BT SR SR BR SR SA                                                                        ' '21' '     8     12' ' 0.0000' '  1954   1952']
     ['22' 'TO BT BT SR BR SR SR BR SR BT BT SA                                                            ' '22' '     8     11' ' 0.0000' '  2864   2565']
     ['23' 'TO BT BT SR SR SR BR SA                                                                        ' '23' '    10      8' ' 0.0000' '  1391   1670']
     ['24' 'TO BT BT SR BR SR SR BR SR SA                                                                  ' '24' '     7     10' ' 0.0000' '  2385   2531']]


    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/hamaLogicalPMT/ModelTriggerSimple/one_pmt/rain_line 
    c2sum :    16.1087 c2n :    18.0000 c2per:     0.8949  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                                            ' ' 0' '  3819   3825' ' 0.0047' '   126    126']
     [' 1' 'TO BT SA                                                            ' ' 1' '  3234   3223' ' 0.0187' '   131    125']
     [' 2' 'TO BT BT SA                                                         ' ' 2' '  1225   1231' ' 0.0147' '  1163   1108']
     [' 3' 'TO BT BT SR SA                                                      ' ' 3' '   388    396' ' 0.0816' '  1350   1252']
     [' 4' 'TO BT BR BT SA                                                      ' ' 4' '   328    303' ' 0.9905' '   156    182']
     [' 5' 'TO SA                                                               ' ' 5' '   228    229' ' 0.0022' '     0      0']
     [' 6' 'TO BT BT SR SR SA                                                   ' ' 6' '   179    201' ' 1.2737' '  1254   1248']
     [' 7' 'TO BR SA                                                            ' ' 7' '   109     99' ' 0.4808' '   116    116']
     [' 8' 'TO BT BT SR SR SR BT BT SA                                          ' ' 8' '    48     69' ' 3.7692' '  1634   1620']
     [' 9' 'TO BT BT SR SR SR SA                                                ' ' 9' '    50     55' ' 0.2381' '  1637   1615']
     ['10' 'TO BT AB                                                            ' '10' '    38     41' ' 0.1139' '   295    269']
     ['11' 'TO BT BT SR BT BT SA                                                ' '11' '    39     38' ' 0.0130' '  3550   3542']
     ['12' 'TO BT BT SR BR SA                                                   ' '12' '    22     34' ' 2.5714' '  3561   3423']
     ['13' 'TO BT BT SR SR SR BR SA                                             ' '13' '    25     18' ' 1.1395' '  1874   1673']
     ['14' 'TO BT BT SR SR BT BT SA                                             ' '14' '    22     16' ' 0.9474' '  2751   2779']
     ['15' 'TO BT BT SR SR SR BR BT BT SA                                       ' '15' '    17     21' ' 0.4211' '  1696   1750']
     ['16' 'TO BT BT SR SR SR BR BR SR SA                                       ' '16' '    21     10' ' 3.9032' '  1896   2007']
     ['17' 'TO BT BT SR SR BR SA                                                ' '17' '    19      9' ' 0.0000' '  2754   2760']
     ['18' 'TO BT BT BR SR SA                                                   ' '18' '    17     12' ' 0.0000' '  1168   1128']
     ['19' 'TO BT BT SR SR SR BR SR SA                                          ' '19' '    15     17' ' 0.1250' '  1619   1649']
     ['20' 'TO AB                                                               ' '20' '    12     15' ' 0.0000' '   343     50']
     ['21' 'TO BT BT SR SR SR BR BR SA                                          ' '21' '     9     14' ' 0.0000' '  1718   1684']
     ['22' 'TO BT BT SR BR SR SA                                                ' '22' '     8     11' ' 0.0000' '  3695   3633']
     ['23' 'TO BT BT SR SR SR BR SR SR SR SA                                    ' '23' '     9      4' ' 0.0000' '  1664   2593']
     ['24' 'TO BT BT BR SR SR SA                                                ' '24' '     9      7' ' 0.0000' '  1107   1107']]





FewPMT/nnvtLogicalPMT/ModelTriggerSimple/one_pmt/rain_dynode  and also hama OK
-------------------------------------------------------------------------------------

::

    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/nnvtLogicalPMT/ModelTriggerSimple/one_pmt/rain_dynode 
    c2sum :    16.8642 c2n :    23.0000 c2per:     0.7332  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO SA                                                            ' ' 0' '  2940   2973' ' 0.1842' '     9     17']
     [' 1' 'TO SR SA                                                         ' ' 1' '  2172   2147' ' 0.1447' '     1      4']
     [' 2' 'TO SR BT BT SA                                                   ' ' 2' '  2048   2080' ' 0.2481' '     4      1']
     [' 3' 'TO SR BR SR SA                                                   ' ' 3' '   626    579' ' 1.8332' '     0     15']
     [' 4' 'TO SR BR SA                                                      ' ' 4' '   618    617' ' 0.0008' '    67     21']
     [' 5' 'TO SR BR SR BT BT SA                                             ' ' 5' '   437    418' ' 0.4222' '   336    339']
     [' 6' 'TO SR BR SR BR SA                                                ' ' 6' '   152    170' ' 1.0062' '   549    376']
     [' 7' 'TO SR BR SR BR SR SA                                             ' ' 7' '   118    103' ' 1.0181' '   337    356']
     [' 8' 'TO SR BR SR SR BT BT SA                                          ' ' 8' '   118    104' ' 0.8829' '    31     84']
     [' 9' 'TO SR BR SR BR SR BT BT SA                                       ' ' 9' '   101    109' ' 0.3048' '   365    335']
     ['10' 'TO SR BR SR SR SA                                                ' '10' '    94    101' ' 0.2513' '     6     23']
     ['11' 'TO SR SR BT BT SA                                                ' '11' '    98     97' ' 0.0051' '  1193   1192']
     ['12' 'TO SR SR SA                                                      ' '12' '    77     83' ' 0.2250' '  1203   1193']
     ['13' 'TO SR SR BR SA                                                   ' '13' '    40     58' ' 3.3061' '  1198   1194']
     ['14' 'TO SR BR SR BR SR BR SR SA                                       ' '14' '    45     32' ' 2.1948' '   331    676']
     ['15' 'TO SR BR SR BR SR BR SR BT BT SA                                 ' '15' '    33     31' ' 0.0625' '   527    505']
     ['16' 'TO SR BR SR SR BR SR BT BT SA                                    ' '16' '    30     32' ' 0.0645' '   128    214']
     ['17' 'TO SR BR SR SR BR SR SA                                          ' '17' '    20     28' ' 1.3333' '    83     86']
     ['18' 'TO SR SR BR SR SA                                                ' '18' '    27     19' ' 1.3913' '  1207   1211']
     ['19' 'TO SR BR SR SR BR SA                                             ' '19' '    23     21' ' 0.0909' '    40    113']
     ['20' 'TO SR SR BR SR SR BT BT SA                                       ' '20' '    22     21' ' 0.0233' '  1220   1202']
     ['21' 'TO SR BR SR SR BR SR BR SA                                       ' '21' '    12     19' ' 1.5806' '    62    133']
     ['22' 'TO SR SR BR SR SR SA                                             ' '22' '    17     14' ' 0.2903' '  1202   1259']
     ['23' 'TO SR BR SR BR SR BR SR BR SR BT BT SA                           ' '23' '     8     15' ' 0.0000' '   546    906']
     ['24' 'TO SR BR SR BR SR BR SA                                          ' '24' '    13     12' ' 0.0000' '   360    358']]


    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/hamaLogicalPMT/ModelTriggerSimple/one_pmt/rain_dynode 
    c2sum :     6.7850 c2n :     6.0000 c2per:     1.1308  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO SA                  ' ' 0' '  8809   8771' ' 0.0821' '     0      0']
     [' 1' 'TO SR BT BT SA         ' ' 1' '   324    355' ' 1.4153' '   756    782']
     [' 2' 'TO SR SA               ' ' 2' '   294    338' ' 3.0633' '   755    754']
     [' 3' 'TO SR BR SA            ' ' 3' '   279    262' ' 0.5342' '   775    760']
     [' 4' 'TO AB                  ' ' 4' '   168    168' ' 0.0000' '   709    709']
     [' 5' 'TO SR BR SR SA         ' ' 5' '    94     77' ' 1.6901' '  1114   1234']
     [' 6' 'TO SR BR SR SR SA      ' ' 6' '    10     11' ' 0.0000' '  1871   1118']
     [' 7' 'TO SR BR SR SR BR SA   ' ' 7' '     8      6' ' 0.0000' '  7360   2197']
     [' 8' 'TO SR BR SR SR BT BT SA' ' 8' '     4      3' ' 0.0000' '  1989   2045']
     [' 9' 'TO SR BR SR BR SA      ' ' 9' '     3      4' ' 0.0000' '  1164   1241']
     ['10' 'TO SR BT AB            ' '10' '     2      1' ' 0.0000' '  1172   1093']
     ['11' 'TO SR BR SR SR BR SR SA' '11' '     2      2' ' 0.0000' '  1973   7458']
     ['12' 'TO SR BR SR BT BT SA   ' '12' '     2      1' ' 0.0000' '  1227   1253']
     ['13' 'TO SR BT BT AB         ' '13' '     1      0' ' 0.0000' '  2578     -1']
     ['14' 'TO SR BT BR SD         ' '14' '     0      1' ' 0.0000' '    -1   6673']]





rain_disc matching
---------------------------

* HMM: not easy to follow the 3D viz 
* would need more 2D simtrace slice planes to be confident the photon paths are correct 

  * OR could try 3D simtrace with pyvista point cloud visualization 
  * https://docs.pyvista.org/examples/01-filter/surface_reconstruction.html
  * OR something like x4/tests/X4MeshTest.py will need to create U4Mesh based on the old X4Mesh for this 


::

    APID=60 MODE=3 ./viz.sh 


::

    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/hamaLogicalPMT/ModelTriggerSimple/one_pmt/rain_disc 
    c2sum :     7.2416 c2n :    17.0000 c2per:     0.4260  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                             ' ' 0' '  3566   3620' ' 0.4058' '     2      1']
     [' 1' 'TO BT SA                                             ' ' 1' '  3115   3078' ' 0.2211' '     0      5']
     [' 2' 'TO BT BT SA                                          ' ' 2' '  1278   1249' ' 0.3328' '     5      2']
     [' 3' 'TO AB                                                ' ' 3' '   579    580' ' 0.0009' '    20     20']
     [' 4' 'TO BT BT SR SA                                       ' ' 4' '   429    386' ' 2.2687' '    14      4']
     [' 5' 'TO BT BR BT SA                                       ' ' 5' '   290    317' ' 1.2010' '    32      8']
     [' 6' 'TO BT BT SR SR SA                                    ' ' 6' '   199    201' ' 0.0100' '     4     55']
     [' 7' 'TO BT BT SR SR SR SA                                 ' ' 7' '    82     72' ' 0.6494' '   164     56']
     [' 8' 'TO BR SA                                             ' ' 8' '    58     63' ' 0.2066' '   140    564']
     [' 9' 'TO BT BT SR SR SR BT BT SA                           ' ' 9' '    60     58' ' 0.0339' '    60     90']
     ['10' 'TO BT BT SR BR SA                                    ' '10' '    29     34' ' 0.3968' '    47      0']
     ['11' 'TO BT AB                                             ' '11' '    26     32' ' 0.6207' '   894    162']
     ['12' 'TO BT BT SR SR SR BR SA                              ' '12' '    29     26' ' 0.1636' '   341    111']
     ['13' 'TO BT BT SR BT BT SA                                 ' '13' '    28     26' ' 0.0741' '   534    510']
     ['14' 'TO BT BT SR SR SR BR SR SA                           ' '14' '    17     21' ' 0.4211' '     9    622']
     ['15' 'TO BT BT SR SR BT BT SA                              ' '15' '    18     16' ' 0.1176' '   847    820']
     ['16' 'TO BT BT SR SR SR BR BT BT SA                        ' '16' '    16     18' ' 0.1176' '   115   1639']
     ['17' 'TO BT BT SR SR BR SA                                 ' '17' '     8     17' ' 0.0000' '  1865    128']
     ['18' 'TO BT BT SR SR SR BR BR SA                           ' '18' '    12     15' ' 0.0000' '    43    228']
     ['19' 'TO BT BT BR SR SA                                    ' '19' '    14     14' ' 0.0000' '  1818    848']
     ['20' 'TO BT BT SR SR SR BR BR SR SA                        ' '20' '    13     11' ' 0.0000' '   741    934']
     ['21' 'TO BT BT SR SR SR BR SR SR SR BT BT SA               ' '21' '    12      6' ' 0.0000' '    45   3234']
     ['22' 'TO BT BT SR BR SR SA                                 ' '22' '     8     10' ' 0.0000' '  1257   1274']
     ['23' 'TO BT BT SR SR SR BR BT MI                           ' '23' '     9      4' ' 0.0000' '  2189    337']
     ['24' 'TO BT BT SR SR SR BR SR SR SR SA                     ' '24' '     6      9' ' 0.0000' '  3343      3']]





rain_dynode_diag giving crazy "TO TO" and lots of Geant4 dumping
--------------------------------------------------------------------

U4SimulateTest.sh::

    174     elif [ "$CHECK" == "rain_dynode_diag" ]; then
    175 
    176         ttype=line
    177         radius=120
    178         pos=0,0,-50
    179         mom=1,0,-1
    180 


See G4 noise::

      G4ParticleChange::CheckIt  : the Momentum Change is not unit vector !!  Difference:  3.42285e-08

      -----------------------------------------------
        G4ParticleChange Information  
      -----------------------------------------------
        # of 2ndaries       :                    0
      -----------------------------------------------
        Energy Deposit (MeV):                    0
        Non-ionizing Energy Deposit (MeV):                    0
        Track Status        :                Alive
        True Path Length (mm) :                 84.3
        Stepping Control      :                    0
        Mass (GeV)   :                    0
        Charge (eplus)   :                    0
        MagneticMoment   :                    0
       

Probably need to normalize in double precision ? 

* YEP adding ".unit()" double precision normalization to U4VPrimaryGenerator::GetPhotonParam avoids the noise


./cf.sh:: 

    ./U4SimulateTest.sh cf ## PMT Geometry : A(N=0) Unnatural+FastSim, B(N=1) Natural+CustomBoundary  
    GEOM/GEOMList/IMPL/LAYOUT/CHECK : FewPMT/hamaLogicalPMT/ModelTriggerSimple/one_pmt/rain_dynode_diag 
    c2sum :  3155.9487 c2n :    21.0000 c2per:   150.2833  C2CUT:   30 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO SA                                                   ' ' 0' '  3894   4057' ' 3.3416' '  2056      7']
     [' 1' 'TO SR SA                                                ' ' 1' '  3067   3646' '49.9391' '  2054      0']
     [' 2' 'TO SR BT BT SA                                          ' ' 2' '     4    557' '545.1141' '  3528      9']

     [' 3' 'TO TO SR SA                                             ' ' 3' '   535      0' '535.0000' '     0     -1']

     [' 4' 'TO TO SR BT BT SA                                       ' ' 4' '   522      0' '522.0000' '     1     -1']
     [' 5' 'TO SR SR SA                                             ' ' 5' '   451    437' ' 0.2207' '  2067   2001']
     [' 6' 'TO SR BR SA                                             ' ' 6' '     8    279' '255.8920' '  3530      5']
     [' 7' 'TO TO SR BR SA                                          ' ' 7' '   277      0' '277.0000' '     4     -1']
     [' 8' 'TO SR BR SR SA                                          ' ' 8' '     0    224' '224.0000' '    -1    542']
     [' 9' 'TO TO SR BR SR SA                                       ' ' 9' '   218      0' '218.0000' '   543     -1']
     ['10' 'TO SR SR SR SR SA                                       ' '10' '   209    214' ' 0.0591' '  2115   2024']
     ['11' 'TO TO SA                                                ' '11' '   213      0' '213.0000' '    18     -1']



Probably the "TO TO" is a fail to skip fake issue ?::

    APID=0 ./viz.sh 


./fk.sh::  

    In [6]: np.c_[st[0,:5]]
    Out[6]: 
    array([['UNSET'],
           ['Vacuum/Vacuum:hama_inner2_phys/hama_inner1_phys'],
           ['Vacuum/Pyrex:hama_inner2_phys/hama_body_phys'],
           ['Vacuum/Vacuum:hama_inner1_phys/hama_inner1_phys'],
           ['UNSET']], dtype='<U50')


    In [3]: a.f.record[0,:4,0]
    Out[3]: 
    array([[  84.853,    0.   ,   34.853,    0.   ],
           [ 119.706,    0.   ,    0.   ,    0.164],
           [ 216.322,    0.   ,  -96.617,    0.62 ],
           [-176.783,    0.   ,  130.282,    2.134]], dtype=float32)

    In [4]: a.f.record[0,:4,1]
    Out[4]: 
    array([[ 0.707,  0.   , -0.707,    nan],
           [ 0.707,  0.   , -0.707,    nan],
           [-0.866,  0.   ,  0.5  ,    nan],
           [-0.866,  0.   ,  0.5  ,    nan]], dtype=float32)


::

    611     unsigned fakemask = ClassifyFake(step, flag, spec, PIDX_DUMP ) ;
    612     bool is_fake = FAKES_SKIP && fakemask > 0 && ( flag == BOUNDARY_TRANSMIT || flag == BOUNDARY_REFLECT ) ;
    613     int st = ( is_fake ? -1 : 1 )*SPECS.add(spec, false ) ;   // DO NOT SEE -ve AT PYTHON LEVEL AS THEY GET SKIPPED
    614 
    615     current_aux.q2.i.z = fakemask ;  // CAUTION: stomping on cdbg.pmtid setting above  
    616     current_aux.q2.i.w = st ;
    617 



Curious:

* ./ph.sh shows red midline of failed to skip FAKE
* N=0 ./pr.sh also show thats (careful of overlapped windows with "pr.sh")

Note that the "TO TO" only happens when the Vac/Vac midline is the first boundary encountered by the photon 


PIDX=0 ./ph.sh run::

    junoPMTOpticalModel::ModelTrigger@141:  PIDX 0 label.id 0
    junoPMTOpticalModel::ModelTriggerSimple_@358:  PIDX 0 label.id 0 dist1 49.2893 trig 0 whereAmI 2
    U4Recorder::ClassifyFake@705:  fdist 136.638 fin kInside fakemask 16 desc FAKE_VV_INNER12|
    U4Recorder::UserSteppingAction_Optical@618:  l.id   0 step_mm    49.2893 abbrev BT spec    Vacuum/Vacuum:hama_inner1_phys/hama_inner2_phys st -16 is_fake YES fakemask 16 U4Fake::Desc FAKE_VV_INNER12|
    junoPMTOpticalModel::ModelTrigger@141:  PIDX 0 label.id 0
    junoPMTOpticalModel::ModelTriggerSimple_@358:  PIDX 0 label.id 0 dist1 -0 trig 0 whereAmI 2
    U4Recorder::ClassifyFake@705:  fdist 453.89 fin kInside fakemask 0 desc 
    U4Recorder::UserSteppingAction_Optical@618:  l.id   0 step_mm   136.6367 abbrev SR spec       Vacuum/Pyrex:hama_inner2_phys/hama_body_phys st   1 is_fake NO  fakemask 0 U4Fake::Desc 
    junoPMTOpticalModel::ModelTrigger@141:  PIDX 0 label.id 0
    junoPMTOpticalModel::ModelTriggerSimple_@358:  PIDX 0 label.id 0 dist1 193.272 trig 0 whereAmI 1
    U4Recorder::ClassifyFake@705:  fdist 453.89 fin kInside fakemask 1 desc FAKE_STEP_MM|
    U4Recorder::UserSteppingAction_Optical@618:  l.id   0 step_mm     0.0000 abbrev NA spec       Pyrex/Vacuum:hama_body_phys/hama_inner2_phys st   2 is_fake NO  fakemask 1 U4Fake::Desc FAKE_STEP_MM|
    junoPMTOpticalModel::ModelTrigger@141:  PIDX 0 label.id 0
    junoPMTOpticalModel::ModelTriggerSimple_@358:  PIDX 0 label.id 0 dist1 193.272 trig 0 whereAmI 1
    U4Recorder::ClassifyFake@705:  fdist 260.618 fin kInside fakemask 16 desc FAKE_VV_INNER12|
    U4Recorder::UserSteppingAction_Optical@618:  l.id   0 step_mm   193.2721 abbrev BT spec    Vacuum/Vacuum:hama_inner2_phys/hama_inner1_phys st -11 is_fake YES fakemask 16 U4Fake::Desc FAKE_VV_INNER12|
    junoPMTOpticalModel::ModelTrigger@141:  PIDX 0 label.id 0
    junoPMTOpticalModel::ModelTriggerSimple_@358:  PIDX 0 label.id 0 dist1 260.617 trig 1 whereAmI 2
    junoPMTOpticalModel::DoIt@574:  PIDX 0 track.GetMomentumDirection (-0.866083,0,0.4999)
    U4Recorder::ClassifyFake@705:  fdist 0.00107609 fin kInside fakemask 0 desc 
    U4Recorder::UserSteppingAction_Optical@618:  l.id   0 step_mm   260.6169 abbrev SA spec    Vacuum/Vacuum:hama_inner1_phys/hama_inner1_phys st  12 is_fake NO  fakemask 0 U4Fake::Desc 
    U4Recorder::PostUserTrackingAction_Optical@367:  l.id     0 seq TO TO SR SA

 


Change num_ph to 1 and disable skipping to investigate, FewPMT.sh::

    144     #export U4Recorder__FAKES_SKIP=1
     

Adding early exit to SEvt::pointPhoton when fake_first detected avoids the "TO TO" issue. 



