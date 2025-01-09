FIXED jok-tds-missing-BR-BT-on-A-side
========================================

Fixed by qsim.h removal of stray "return 0 " in qsim::propagate_at_boundary::

    P[blyth@localhost jtds]$ jok-
    P[blyth@localhost jtds]$ jok-ana
             BASH_SOURCE : /home/blyth/j/jtds/jtds.sh 
                     TMP : /data/blyth/opticks 
                     arg : info_pdb 
                    name : jtds 
                    SDIR : /home/blyth/j/jtds 
                    GEOM : J_2025jan08 
                    BASE : /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_Debug_Philox 
                     EVT : 000 
                     evt :  
                   AFOLD : /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_Debug_Philox/A000 
                   BFOLD : /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_Debug_Philox/B000 
                  script : /home/blyth/j/jtds/jtds.py 
    Python 3.7.7 (default, May  7 2020, 21:25:33) 
    Type 'copyright', 'credits' or 'license' for more information
    IPython 7.18.1 -- An enhanced Interactive Python. Type '?' for help.
    [from opticks.ana.p import * 
    [ana/p.py:from opticks.CSG.CSGFoundry import CSGFoundry 
    ]ana/p.py:from opticks.CSG.CSGFoundry import CSGFoundry 
    [ana/p.py:cf = CSGFoundry.Load()
    CSGFoundry.CFBase returning [/home/blyth/.opticks/GEOM/J_2025jan08], note:[via GEOM] 
    ]ana/p.py:cf = CSGFoundry.Load()
    ]from opticks.ana.p import * 
    INST_FRAME -1 : using default sframe saved with the sevt
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ('$AFOLD',) quiet:1
    sevt.init W2M
     None
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol a pid -1 opt  off [0. 0. 0.] 
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ('$BFOLD',) quiet:1
    sevt.init W2M
     None
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol b pid -1 opt  off [0. 0. 0.] 
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_Debug_Philox/A000 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_Debug_Philox/B000 
    [--- ab = SAB(a,b) ----
    INFO:opticks.ana.pvplt:[
    INFO:opticks.ana.qcf:QCF.__init__ qcf.aqu 
    INFO:opticks.ana.qcf:QCF.__init__ qcf.bqu 
    INFO:opticks.ana.qcf:QCF.__init__ [ qu loop
    INFO:opticks.ana.qcf:QCF.__init__ . qu loop 0 
    INFO:opticks.ana.qcf:QCF.__init__ . qu loop 1000 
    INFO:opticks.ana.qcf:QCF.__init__ ] qu loop
    INFO:opticks.ana.pvplt:]
    ]--- ab = SAB(a,b) ----
    [----- repr(ab) 
    sli: slice(None, 40, None) 
    SAB
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_Debug_Philox/A000 
    a

    CMDLINE:/home/blyth/j/jtds/jtds.py
    a.base:/data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_Debug_Philox/A000

      : a.genstep                                          :            (1, 6, 4) : 0:12:50.624416 
      : a.photon                                           :        (10000, 4, 4) : 0:12:50.624416 
      : a.record                                           :    (10000, 32, 4, 4) : 0:12:50.623416 
      : a.record_meta                                      :                    1 : 0:12:50.614416 
      : a.seq                                              :        (10000, 2, 2) : 0:12:50.614416 
      : a.hit                                              :         (3702, 4, 4) : 0:12:50.614416 
      : a.domain                                           :            (2, 4, 4) : 0:12:50.614416 
      : a.inphoton                                         :        (10000, 4, 4) : 0:12:50.614416 
      : a.seqnib                                           :             (10000,) : 0:12:50.613416 
      : a.seqnib_table                                     :              (33, 1) : 0:12:50.613416 
      : a.NPFold_index                                     :                 (9,) : 0:12:50.613416 
      : a.NPFold_meta                                      :                   25 : 0:12:50.613416 
      : a.NPFold_names                                     :                 (0,) : 0:12:50.613416 
      : a.sframe                                           :            (4, 4, 4) : 0:12:50.613416 
      : a.sframe_meta                                      :                    5 : 0:12:50.613416 

     min_stamp : 2025-01-08 20:31:13.165393 
     max_stamp : 2025-01-08 20:31:13.176393 
     dif_stamp : 0:00:00.011000 
     age_stamp : 0:12:50.613416 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_Debug_Philox/B000 
    b

    CMDLINE:/home/blyth/j/jtds/jtds.py
    b.base:/data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_Debug_Philox/B000

      : b.genstep                                          :            (1, 6, 4) : 0:12:50.769815 
      : b.photon                                           :        (10000, 4, 4) : 0:12:50.768815 
      : b.record                                           :    (10000, 32, 4, 4) : 0:12:50.768815 
      : b.record_meta                                      :                    1 : 0:12:50.759815 
      : b.seq                                              :        (10000, 2, 2) : 0:12:50.759815 
      : b.domain                                           :            (2, 4, 4) : 0:12:50.758815 
      : b.inphoton                                         :        (10000, 4, 4) : 0:12:50.758815 
      : b.seqnib                                           :             (10000,) : 0:12:50.758815 
      : b.seqnib_table                                     :              (33, 1) : 0:12:50.757815 
      : b.NPFold_index                                     :                 (8,) : 0:12:50.757815 
      : b.NPFold_meta                                      :                   56 : 0:12:50.757815 
      : b.NPFold_names                                     :                 (0,) : 0:12:50.756815 
      : b.sframe                                           :            (4, 4, 4) : 0:12:50.755815 
      : b.sframe_meta                                      :                    5 : 0:12:50.755815 

     min_stamp : 2025-01-08 20:31:13.020392 
     max_stamp : 2025-01-08 20:31:13.034392 
     dif_stamp : 0:00:00.014000 
     age_stamp : 0:12:50.755815 
    ab.qcf.aqu
    qcf.aqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x
    [[b'3375' b'24' b'TO             SD                                                                               ']
     [b'2869' b'27' b'TO             SA                                                                               ']
     [b'903' b'39' b'TO                SR SA                                                                         ']
     [b'808' b'1' b'TO                SA                                                                            ']
     [b'172' b'1562' b'TO                SR                      AB                                                    ']
     [b'109' b'101' b'TO                SR SR SA                                                                      ']
     [b'101' b'34' b'TO       AB                                                                                     ']
     [b'91' b'1742' b'TO                SR                                        SD                                  ']
     [b'78' b'1748' b'TO                SR                                        SA                                  ']
     [b'76' b'1750' b'TO                SR                      SC                   SA                               ']]
    ab.qcf.bqu
    qcf.bqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x
    [[b'3341' b'2' b'TO BT BT BT BT SD                                                                               ']
     [b'2770' b'0' b'TO BT BT BT BT SA                                                                               ']
     [b'618' b'1135' b'TO BT BT BT BT BT SR SA                                                                         ']
     [b'484' b'912' b'TO BT BT BT BT BT SA                                                                            ']
     [b'135' b'2184' b'TO BT BT BT BT BT SR BR SR SA                                                                   ']
     [b'120' b'1616' b'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                          ']
     [b'107' b'2031' b'TO BT BT BT BT BT SR BR SA                                                                      ']
     [b'95' b'1037' b'TO BT BT BT BT BT SR SR SA                                                                      ']
     [b'79' b'78' b'TO BT BT AB                                                                                     ']
     [b'70' b'2216' b'TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                    ']]
    a.CHECK :  





    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO             SD                                                                              ' ' 0' '  3375      0' '3375.0000' '    24     -1']
     [' 1' 'TO BT BT BT BT SD                                                                              ' ' 1' '     0   3341' '3341.0000' '    -1      2']
     [' 2' 'TO             SA                                                                              ' ' 2' '  2869      0' '2869.0000' '    27     -1']
     [' 3' 'TO BT BT BT BT SA                                                                              ' ' 3' '     0   2770' '2770.0000' '    -1      0']
     [' 4' 'TO                SR SA                                                                        ' ' 4' '   903      0' '903.0000' '    39     -1']
     [' 5' 'TO                SA                                                                           ' ' 5' '   808      0' '808.0000' '     1     -1']
     [' 6' 'TO BT BT BT BT BT SR SA                                                                        ' ' 6' '     0    618' '618.0000' '    -1   1135']
     [' 7' 'TO BT BT BT BT BT SA                                                                           ' ' 7' '     0    484' '484.0000' '    -1    912']
     [' 8' 'TO                SR                      AB                                                   ' ' 8' '   172      0' '172.0000' '  1562     -1']



::

    In [6]: a.q[:100]
    Out[6]: 
    array([[b'TO                DR    SR    SA                                                                '],
           [b'TO                SA                                                                            '],
           [b'TO                DR    SR                SA                                                    '],
           [b'TO                SA                                                                            '],
           [b'TO                SA                                                                            '],
           [b'TO                DR    SR                SA                                                    '],
           [b'TO             AB                                                                               '],
           [b'TO                SA                                                                            '],
           [b'TO                DR    SR    SA                                                                '],
           [b'TO                SA                                                                            '],
           [b'TO                DR    SR                   SR                   SA                            '],
           [b'TO                SA                                                                            '],



Getting many zeros in seq where expect c::

    In [10]: a.f.seq[1,0,0]
    Out[10]: 134217741

    In [11]: hex(134217741)
    Out[11]: '0x800000d'

    In [13]: b.f.seq[0,0,0]
    Out[13]: 9227469

    In [14]: hex(9227469)
    Out[14]: '0x8ccccd'


cx/CSGOptiX7.cu::

    340 
    341 #ifndef PRODUCTION
    342         ctx.trace(bounce);
    343 #endif
    344         command = sim->propagate(bounce, rng, ctx);
    345         bounce++;
    346 #ifndef PRODUCTION
    347         ctx.point(bounce) ;
    348 #endif
    349         if(command == BREAK) break ;
    350     }
    351 #ifndef PRODUCTION
    352     ctx.end();  // write seq, tag, flat 
    353 #endif
    354     evt->photon[idx] = ctx.p ;
    355     // not photon_idx, needs to go from zero for photons from a slice of genstep array
    356 }
    357 
    358 #endif




::

    0998 inline QSIM_METHOD int qsim::propagate_at_boundary(unsigned& flag, RNG& rng, sctx& ctx, float theTransmittance ) const
    0999 {
    1000 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1001     if(ctx.idx == base->pidx)
    1002     printf("//propagate_at_boundary.DEBUG_PIDX ctx.idx %d base %p base.pidx %d \n", ctx.idx, base, base->pidx  );
    1003 #endif
    1004 
    1005 #if !defined(PRODUCTION) && defined(DEBUG_TAG)
    1006     if(ctx.idx == base->pidx)
    1007     printf("//propagate_at_boundary.DEBUG_TAG ctx.idx %d base %p base.pidx %d \n", ctx.idx, base, base->pidx  );
    1008 #endif
    1009     //return 0 ;  // stray debug accidentally left here caused : ~/j/issues/jok-tds-missing-BR-BT-on-A-side.rst 
    1010 


That stray returned 0 caused no harm (because not BREAK), but it meant that the flag was not 
set leading to the zeros in the seq history. 


After removing the stray jok-ana back to agreement::

    ab.qcf[:40]
    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum :    38.2620 c2n :    32.0000 c2per:     1.1957  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  38.26/32:1.196 (30) pv[1.000,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SD                                                                              ' ' 0' '  3227   3341' ' 1.9787' '     0      2']
     [' 1' 'TO BT BT BT BT SA                                                                              ' ' 1' '  2882   2770' ' 2.2194' '     2      0']
     [' 2' 'TO BT BT BT BT BT SR SA                                                                        ' ' 2' '   659    618' ' 1.3164' '  1063   1135']
     [' 3' 'TO BT BT BT BT BT SA                                                                           ' ' 3' '   451    484' ' 1.1647' '   898    912']
     [' 4' 'TO BT BT BT BT BT SR BR SR SA                                                                  ' ' 4' '   131    135' ' 0.0602' '  2182   2184']
     [' 5' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                         ' ' 5' '    86    120' ' 5.6117' '  1624   1616']
     [' 6' 'TO BT BT BT BT BT SR BR SA                                                                     ' ' 6' '   104    107' ' 0.0427' '  2022   2031']
     [' 7' 'TO BT BT BT BT BT SR SR SA                                                                     ' ' 7' '    87     95' ' 0.3516' '  1056   1037']
     [' 8' 'TO BT BT AB                                                                                    ' ' 8' '    74     79' ' 0.1634' '    51     78']
     [' 9' 'TO BT BT BT BT BR BT BT BT BT AB                                                               ' ' 9' '    70     50' ' 3.3333' '   939   1216']
     ['10' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                   ' '10' '    62     70' ' 0.4848' '  2198   2216']
     ['11' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SA                                       ' '11' '    33     53' ' 4.6512' '  1730   1656']
     ['12' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD                                       ' '12' '    46     34' ' 1.8000' '  1686   1722']
     ['13' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                                   ' '13' '    43     43' ' 0.0000' '   803    828']
     ['14' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                    ' '14' '    42     41' ' 0.0120' '  1697   1803']
     ['15' 'TO BT BT BT BT BR BT BT BT BT BT SA                                                            ' '15' '    32     42' ' 1.3514' '    70     76']
     ['16' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                   ' '16' '    29     41' ' 2.0571' '   919    928']
     ['17' 'TO BT BT BT BT AB                                                                              ' '17' '    30     40' ' 1.4286' '     9    300']
     ['18' 'TO BT BT BT BT BT SR BR SR SR SA                                                               ' '18' '    35     22' ' 2.9649' '  2322   2541']
     ['19' 'TO BT BT BT BT BT SR SR SR SA                                                                  ' '19' '    29     35' ' 0.5625' '  1266   1123']
     ['20' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                                    ' '20' '    33     34' ' 0.0149' '  1753   1885']
     ['21' 'TO BT BT BT BT BR BT BT BT BT BT BT SC AB                                                      ' '21' '    27     34' ' 0.8033' '  2279   1750']
     ['22' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SA                              ' '22' '    24     29' ' 0.4717' '  2280   3387']
     ['23' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SD                              ' '23' '    20     28' ' 1.3333' '  2879   2415']
     ['24' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SD                                 ' '24' '    24     21' ' 0.2000' '  2245   2331']
     ['25' 'TO BT BT BT BT BT SR BT BT BT BT BT AB                                                         ' '25' '    24     22' ' 0.0870' '  2399   2234']
     ['26' 'TO BT BT BT BT BT SR BR SR BR SR SA                                                            ' '26' '    18     21' ' 0.2308' '  2191   2126']
     ['27' 'TO BT BT BT BT BR BT BT BT BT BT BT SC SC AB                                                   ' '27' '    21     13' ' 1.8824' '  2390   1833']
     ['28' 'TO BT BT BT BT BR BT BT BT BT BT BT SD                                                         ' '28' '    14     21' ' 1.4000' '   507    504']
     ['29' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SA                                 ' '29' '    19     19' ' 0.0000' '  2256   2244']
     ['30' 'TO AB                                                                                          ' '30' '    19     16' ' 0.2571' '    63     20']
     ['31' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC AB                                                ' '31' '    19     18' ' 0.0270' '  2821   2509']
     ['32' 'TO BT BT BT BR BT BT BT BT SA                                                                  ' '32' '    13     17' ' 0.0000' '     1      9']
     ['33' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SA                                             ' '33' '    16      6' ' 0.0000' '   876    873']
     ['34' 'TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT BT BT SD                                 ' '34' '    11     15' ' 0.0000' '  2483   2493']
     ['35' 'TO BT BT BT BT BT SR BR SR BT BT BT BT BT BT BT AB                                             ' '35' '    14      4' ' 0.0000' '  2190   2895']
     ['36' 'TO BT BT BT BT BT SR BR SR BR SA                                                               ' '36' '    14     11' ' 0.0000' '  2404   4263']
     ['37' 'TO BT BT BT BT BT SR SR BR SA                                                                  ' '37' '    14     13' ' 0.0000' '  1708   1732']
     ['38' 'TO BT BT BT BT BT SR SR BR SR SR SA                                                            ' '38' '     7     13' ' 0.0000' '  1835   1832']
     ['39' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SD                                             ' '39' '    12     12' ' 0.0000' '   861    876']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## in A but not B 
    []

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## in B but not A 
    []



  






