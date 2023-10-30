ntds3-closer-look-at-chi2-remote-SD-deviation
===============================================

::
 
    ntds3_noxjsjfa            # workstation

    GEOM tmpget               # laptop
    MODE=0 ~/j/ntds/ntds3.sh  # laptop



::

    ab.qcf[:40]
    QCF qcf :  
    a.q 100000 b.q 100000 lim slice(None, None, None) 
    c2sum :   191.8697 c2n :   189.0000 c2per:     1.0152  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  191.87/189:1.015 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SD                                            ' ' 0' ' 33389  33516' ' 0.2411' '     1      1']
     [' 1' 'TO BT BT BT BT SA                                            ' ' 1' ' 28134  27994' ' 0.3492' '     8      0']
     [' 2' 'TO BT BT BT BT BT SR SA                                      ' ' 2' '  6268   6181' ' 0.6080' ' 10363  10454']
     [' 3' 'TO BT BT BT BT BT SA                                         ' ' 3' '  4627   4714' ' 0.8103' '  8398   8449']
     [' 4' 'TO BT BT BT BT BT SR BR SR SA                                ' ' 4' '  1154   1198' ' 0.8231' ' 21156  20987']
     [' 5' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                       ' ' 5' '   947    970' ' 0.2760' ' 10389   9811']
     [' 6' 'TO BT BT BT BT BT SR BR SA                                   ' ' 6' '   923    961' ' 0.7665' ' 20241  20276']
     [' 7' 'TO BT BT BT BT BT SR SR SA                                   ' ' 7' '   901    886' ' 0.1259' ' 10399  10419']
     [' 8' 'TO BT BT AB                                                  ' ' 8' '   879    900' ' 0.2479' '    26      8']
     [' 9' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                 ' ' 9' '   615    657' ' 1.3868' ' 20974  21894']
     ['10' 'TO BT BT BT BT BR BT BT BT BT AB                             ' '10' '   573    577' ' 0.0139' '   646   5420']
     ['11' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                 ' '11' '   538    560' ' 0.4408' '  7312   7300']
     ['12' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD     ' '12' '   504    389' '14.8096' ' 12018  11473']
     ['13' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                 ' '13' '   470    463' ' 0.0525' '  7974   7971']
     ['14' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SA     ' '14' '   406    411' ' 0.0306' ' 11467  11464']
     ['15' 'TO BT BT BT BT BT SR SR SR SA                                ' '15' '   383    391' ' 0.0827' ' 10362  10410']
     ['16' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD  ' '16' '   390    372' ' 0.4252' ' 16444  17073']


HMM NO DEVIATION IN THE SA ?::

     ['12' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD     ' '12' '   504    389' '14.8096' ' 12018  11473']
     ['14' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SA     ' '14' '   406    411' ' 0.0306' ' 11467  11464']
    

::

    In [7]: ab.qcf.abo.reshape(-1,6)[:40]
    Out[7]:
    array([[ 5500,  5346,     1,     1, 33389, 33516],
           [ 5499,  5345,     8,     0, 28134, 27994],
           [ 4760,  4599, 10363, 10454,  6268,  6181],
           [ 2986,  2889,  8398,  8449,  4627,  4714],
           [ 3394,  3277, 21156, 20987,  1154,  1198],
           [  821,   801, 10389,  9811,   947,   970],
           [ 3027,  2927, 20241, 20276,   923,   961],
           [ 5087,  4917, 10399, 10419,   901,   886],
           [  195,   181,    26,     8,   879,   900],
           [ 3721,  3575, 20974, 21894,   615,   657],
           [  691,   682,   646,  5420,   573,   577],
           [ 1498,  1467,  7312,  7300,   538,   560],
           [ 1434,  1410, 12018, 11473,   504,   389],
           [ 1511,  1479,  7974,  7971,   470,   463],
           [ 1433,  1409, 11467, 11464,   406,   411],
           [ 5283,  5108, 10362, 10410,   383,   391],
           [ 2158,  2086, 16444, 17073,   390,   372],


    In [6]: rabo = ab.qcf.abo.reshape(-1,6)

    In [10]: np.c_[rabo, rabo[:,4]-rabo[:,5] ][:100]
    Out[10]:
    array([[ 5500,  5346,     1,     1, 33389, 33516,  -127],
           [ 5499,  5345,     8,     0, 28134, 27994,   140],
           [ 4760,  4599, 10363, 10454,  6268,  6181,    87],
           [ 2986,  2889,  8398,  8449,  4627,  4714,   -87],
           [ 3394,  3277, 21156, 20987,  1154,  1198,   -44],
           [  821,   801, 10389,  9811,   947,   970,   -23],
           [ 3027,  2927, 20241, 20276,   923,   961,   -38],
           [ 5087,  4917, 10399, 10419,   901,   886,    15],
           [  195,   181,    26,     8,   879,   900,   -21],
           [ 3721,  3575, 20974, 21894,   615,   657,   -42],
           [  691,   682,   646,  5420,   573,   577,    -4],
           [ 1498,  1467,  7312,  7300,   538,   560,   -22],
           [ 1434,  1410, 12018, 11473,   504,   389,   115],    ###
           [ 1511,  1479,  7974,  7971,   470,   463,     7],
           [ 1433,  1409, 11467, 11464,   406,   411,    -5],
           [ 5283,  5108, 10362, 10410,   383,   391,    -8],
           [ 2158,  2086, 16444, 17073,   390,   372,    18],
           [ 2157,  2085, 16401, 16235,   356,   334,    22],
           [ 3639,  3481, 20996, 21008,   353,   337,    16],
           [ 2756,  2671,   665,   666,   308,   344,   -36],
           [ 1762,  1711, 16582, 16920,   313,   342,   -29],
           [  631,   619,   651,   107,   315,   316,    -1],
           [ 3985,  3834, 22370, 22414,   269,   253,    16],
           [ 4383,  4218, 22976, 23408,   223,   242,   -19],
           [ 4384,  4219, 22684, 22616,   232,   236,    -4],
           [ 3984,  3831, 22437, 22440,   234,   230,     4],
           [ 3679,  3523, 22314, 22347,   210,   218,    -8],
           [ 1761,  1710,   659,  3525,   212,   216,    -4],
           [ 4127,  3980, 23612, 22917,   205,   213,    -8],
           [ 2711,  2624,  5038,  5122,   177,   156,    21],
           [ 3150,  3050, 21027, 21036,   157,   162,    -5],
           [    0,     0,   336,   231,   131,   116,    15],
           [ 2483,  2394, 16177, 16459,   126,   126,     0],
           [ 2482,  2393, 18406, 16152,   108,   125,   -17],



Try to increase photon stats from 100k to 1M with RainXZ_Z230_1M_f8.npy
------------------------------------------------------------------------

::

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0)
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 0 LEVEL 5:DEBUG
    2023-10-30 11:35:53.795 FATAL [333831] [SEvt::setNumPhoton@1667]  num_photon 1000000 evt.max_photon 100000
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1668: void SEvt::setNumPhoton(unsigned int): Assertion `num_photon_allowed' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd17064ba in SEvt::setNumPhoton (this=0xb4af50, num_photon=1000000) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1668
    #5  0x00007fffd170628a in SEvt::addGenstep (this=0xb4af50, q_=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1635
    #6  0x00007fffd1701a6a in SEvt::addFrameGenstep (this=0xb4af50) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:560
    #7  0x00007fffd1704486 in SEvt::beginOfEvent (this=0xb4af50, eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1188
    #8  0x00007fffd2c836a1 in U4Recorder::BeginOfEventAction (this=0xb22080, event=0xeff22610)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:280
    #9  0x00007fffd09eb85c in U4RecorderAnaMgr::BeginOfEventAction (this=0xb4ada0, evt=0xeff22610)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:31



That will probably run out of GPU memory with full recording enabled::

    N[blyth@localhost ~]$ nvidia-smi
    Mon Oct 30 12:34:37 2023       
    +-----------------------------------------------------------------------------+
    | NVIDIA-SMI 435.21       Driver Version: 435.21       CUDA Version: 10.1     |
    |-------------------------------+----------------------+----------------------+
    | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
    |===============================+======================+======================|
    |   0  TITAN RTX           Off  | 00000000:73:00.0  On |                  N/A |
    | 40%   32C    P8    15W / 280W |    421MiB / 24219MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+
    |   1  TITAN V             Off  | 00000000:A6:00.0 Off |                  N/A |
    | 35%   51C    P8    29W / 250W |    545MiB / 12066MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+
                                                                                   
    +-----------------------------------------------------------------------------+
    | Processes:                                                       GPU Memory |
    |  GPU       PID   Type   Process name                             Usage      |
    |=============================================================================|
    |    0     20865      G   /usr/bin/X                                    24MiB |
    |    0     21503      G   /usr/bin/gnome-shell                         102MiB |
    |    0     22134      G   /usr/bin/X                                   122MiB |
    |    0     22918      G   /usr/bin/gnome-shell                         159MiB |
    |    1      9854      C   ...p/ExternalLibs/Python/3.8.12/bin/python   533MiB |
    +-----------------------------------------------------------------------------+
    N[blyth@localhost ~]$ 


Looks like currently using GPU 1 (TITAN V) with only 12G.  
How to switch to GPU 0 (TITAL RTX) with 24G ?

First access to GPU probably the uploads done in CSGOptiX::Create 

::

    epsilon:n001 blyth$ i
    Using matplotlib backend: MacOSX

    In [1]: a = np.load("pho0.npy")                                                                                                           
    ---------------------------------------------------------------------------
    ValueError                                Traceback (most recent call last)
    <ipython-input-1-fa21ec47d28f> in <module>
    ----> 1 a = np.load("pho0.npy")

    ~/miniconda3/lib/python3.7/site-packages/numpy/lib/npyio.py in load(file, mmap_mode, allow_pickle, fix_imports, encoding)
        438             else:
        439                 return format.read_array(fid, allow_pickle=allow_pickle,
    --> 440                                          pickle_kwargs=pickle_kwargs)
        441         else:
        442             # Try a pickle

    ~/miniconda3/lib/python3.7/site-packages/numpy/lib/format.py in read_array(fp, allow_pickle, pickle_kwargs)
        769             array = array.transpose()
        770         else:
    --> 771             array.shape = shape
        772 
        773     return array

    ValueError: cannot reshape array of size 0 into shape (1000000,4)
    > /Users/blyth/miniconda3/lib/python3.7/site-packages/numpy/lib/format.py(771)read_array()
        769             array = array.transpose()
        770         else:
    --> 771             array.shape = shape
        772 
        773     return array

    ipdb>                           


HUH: header only pho0.npy ?::

    epsilon:n001 blyth$ xxd pho0.npy 
    00000000: 934e 554d 5059 0100 7600 7b27 6465 7363  .NUMPY..v.{'desc
    00000010: 7227 3a20 273c 6934 272c 2027 666f 7274  r': '<i4', 'fort
    00000020: 7261 6e5f 6f72 6465 7227 3a20 4661 6c73  ran_order': Fals
    00000030: 652c 2027 7368 6170 6527 3a20 2831 3030  e, 'shape': (100
    00000040: 3030 3030 2c20 3429 2c20 7d20 2020 2020  0000, 4), }     
    00000050: 2020 2020 2020 2020 2020 2020 2020 2020                  
    00000060: 2020 2020 2020 2020 2020 2020 2020 2020                  
    00000070: 2020 2020 2020 2020 2020 2020 2020 200a                 .
    epsilon:n001 blyth$ 


::

    QCF qcf :  
    a.q 1000000 b.q 1000000 lim slice(None, None, None) 
    c2sum :  1123.4806 c2n :  1058.0000 c2per:     1.0619  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  1123.48/1058:1.062 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SD                                                                              ' ' 0' '332201 331654' ' 0.4507' '     1      2']
     [' 1' 'TO BT BT BT BT SA                                                                              ' ' 1' '281160 281823' ' 0.7808' '     8      1']
     [' 2' 'TO BT BT BT BT BT SR SA                                                                        ' ' 2' ' 62733  63122' ' 1.2023' '103696 103630']
     [' 3' 'TO BT BT BT BT BT SA                                                                           ' ' 3' ' 46858  46634' ' 0.5367' ' 84566  84561']
     [' 4' 'TO BT BT BT BT BT SR BR SR SA                                                                  ' ' 4' ' 11488  11859' ' 5.8954' '209819 209876']
     [' 5' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                         ' ' 5' '  9942   9949' ' 0.0025' ' 42525  36463']
     [' 6' 'TO BT BT BT BT BT SR BR SA                                                                     ' ' 6' '  9642   9769' ' 0.8309' '202004 202004']
     [' 7' 'TO BT BT BT BT BT SR SR SA                                                                     ' ' 7' '  9073   9044' ' 0.0464' '103626 103848']
     [' 8' 'TO BT BT AB                                                                                    ' ' 8' '  8452   8618' ' 1.6143' '    26    218']
     [' 9' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                   ' ' 9' '  6405   6377' ' 0.0613' '202051 202901']
     ['10' 'TO BT BT BT BT BR BT BT BT BT AB                                                               ' '10' '  5818   5792' ' 0.0582' '   646   5434']
     ['11' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                   ' '11' '  4965   4944' ' 0.0445' ' 72994  72990']
     ['12' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                                   ' '12' '  4882   4900' ' 0.0331' ' 79661  79660']
     ['13' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD                                       ' '13' '  4359   4169' ' 4.2331' '114637 114662']
     ['14' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SA                                       ' '14' '  3892   3961' ' 0.6063' '114632 114637']
     ['15' 'TO BT BT BT BT BT SR SR SR SA                                                                  ' '15' '  3836   3811' ' 0.0817' '103637 103565']
     ['16' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                    ' '16' '  3819   3795' ' 0.0757' '161576 163676']
     ['17' 'TO BT BT BT BT BT SR BR SR SR SA                                                               ' '17' '  3505   3622' ' 1.9207' '209809 209925']
     ['18' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                                    ' '18' '  3533   3505' ' 0.1114' '161976 161568']
     ['19' 'TO BT BT BT BT BR BT BT BT BT BT SA                                                            ' '19' '  3473   3414' ' 0.5054' '  6573   6656']
     ['20' 'TO BT BT BT BT AB                                                                              ' '20' '  3386   3343' ' 0.2748' '   651    467']
     ['21' 'TO BT BT BT BT BR BT BT BT BT BT BT SC AB                                                      ' '21' '  3179   3078' ' 1.6303' '163763 115348']
     ['22' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SD                                 ' '22' '  2624   2732' ' 2.1777' '223640 223694']
     ['23' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SA                                 ' '23' '  2543   2500' ' 0.3666' '224374 223672']
     ['24' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SD                              ' '24' '  2403   2392' ' 0.0252' '226813 226290']
     ['25' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SA                              ' '25' '  2313   2143' ' 6.4856' '226236 225964']
     ['26' 'TO BT BT BT BT BR BT BT BT BT BT BT SA                                                         ' '26' '  2033   2120' ' 1.8225' '  6588   6569']
     ['27' 'TO BT BT BT BT BT SR BT BT BT BT BT AB                                                         ' '27' '  2103   2008' ' 2.1953' '209194 206802']
     ['28' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC AB                                                ' '28' '  2067   2013' ' 0.7147' '226402 221825']
     ['29' 'TO BT BT BT BT BR BT BT BT BT BT BT SD                                                         ' '29' '  1940   1955' ' 0.0578' ' 50398  50375']
     ['30' 'TO BT BT BT BT BT SR BR SR BR SR SA                                                            ' '30' '  1615   1707' ' 2.5479' '210471 210578']
     ['31' 'TO AB                                                                                          ' '31' '  1365   1448' ' 2.4490' '   336     50']
     ['32' 'TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT BT BT SD                                 ' '32' '  1227   1291' ' 1.6267' '163064 163173']
     ['33' 'TO BT BT BT BT BR BT BT BT BT BT AB                                                            ' '33' '  1165   1227' ' 1.6070' ' 55628  85614']
     ['34' 'TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT BT BT SA                                 ' '34' '  1226   1115' ' 5.2631' '163793 164942']
     ['35' 'TO BT BT BT BR BT BT BT BT SA                                                                  ' '35' '  1157   1178' ' 0.1889' '     0     10']
     ['36' 'TO BT BT BT BT BT SR BR SR BR SA                                                               ' '36' '  1094   1144' ' 1.1171' '210099 211050']
     ['37' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SD                                             ' '37' '  1048   1137' ' 3.6252' ' 86052  86067']
     ['38' 'TO BT BT BT BT BT SR SR BR SA                                                                  ' '38' '  1136   1042' ' 4.0569' '170573 170551']
     ['39' 'TO BT BT BT BT BT SR SR SR BR SA                                                               ' '39' '  1059   1131' ' 2.3671' '121912 121890']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## in A but not B 
    [['727' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT SD                                                ' '727' '    28      0' ' 0.0000' '134671     -1']
     ['757' 'TO BT BT BT BT BT SC SA                                                                        ' '757' '    26      0' ' 0.0000' '132133     -1']
     ['1201' 'TO BT BT BT BT BT SR BR SR AB                                                                  ' '1201' '    15      0' ' 0.0000' '229107     -1']
     ['1208' 'TO BT BT BT BT BT SR AB                                                                        ' '1208' '    15      0' ' 0.0000' '427907     -1']
     ['1373' 'TO BT BT BT BT BR BT BT BT BT BT BR BT BT BR SA                                                ' '1373' '    13      0' ' 0.0000' '889146     -1']
     ['1475' 'TO BT BT BR BT BT BT BT BT BT BT BT BT SA                                                      ' '1475' '    12      0' ' 0.0000' ' 75721     -1']
     ['1614' 'TO BT BT BT BT BT SC SR SA                                                                     ' '1614' '    11      0' ' 0.0000' '246537     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## in B but not A 
    [['1544' 'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT SC RE AB                                       ' '1544' '     0     11' ' 0.0000' '    -1 139224']
     ['1671' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BR AB                                       ' '1671' '     0     11' ' 0.0000' '    -1 285641']]
    ]----- repr(ab) 
    PICK=A MODE=3 SEL= ~/j/ntds/ntds3.sh 
    STARTING PVPLT_PLOTTER ... THERE COULD BE A WINDOW WAITING FOR YOU TO CLOSE
    pvplt_viewpoint reset:0 PARA:0 
     eye  : [1. 1. 1.] 
     look : [0. 0. 0.] 
     up   : [0. 0. 1.] 
     zoom : 1.0 
    pvplt_viewpoint reset:0 PARA:0 
     eye  : [1. 1. 1.] 
     look : [0. 0. 0.] 
     up   : [0. 0. 1.] 
     zoom : 1.0 


MODE=0 C2CUT=200 ~/j/ntds/ntds3.sh::

    In [5]: ab.qcf[:20]                                                                                                                                                                     
    sli: slice(None, 20, None) 
    Out[5]: 
    QCF qcf :  
    a.q 1000000 b.q 1000000 lim slice(None, None, None) 
    c2sum :   310.4353 c2n :   273.0000 c2per:     1.1371  C2CUT:  200 
    c2sum/c2n:c2per(C2CUT)  310.44/273:1.137 (200)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:20]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SD                                                                              ' ' 0' '332201 331654' ' 0.4507' '     1      2']
     [' 1' 'TO BT BT BT BT SA                                                                              ' ' 1' '281160 281823' ' 0.7808' '     8      1']
     [' 2' 'TO BT BT BT BT BT SR SA                                                                        ' ' 2' ' 62733  63122' ' 1.2023' '103696 103630']
     [' 3' 'TO BT BT BT BT BT SA                                                                           ' ' 3' ' 46858  46634' ' 0.5367' ' 84566  84561']
     [' 4' 'TO BT BT BT BT BT SR BR SR SA                                                                  ' ' 4' ' 11488  11859' ' 5.8954' '209819 209876']
     [' 5' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                         ' ' 5' '  9942   9949' ' 0.0025' ' 42525  36463']
     [' 6' 'TO BT BT BT BT BT SR BR SA                                                                     ' ' 6' '  9642   9769' ' 0.8309' '202004 202004']
     [' 7' 'TO BT BT BT BT BT SR SR SA                                                                     ' ' 7' '  9073   9044' ' 0.0464' '103626 103848']
     [' 8' 'TO BT BT AB                                                                                    ' ' 8' '  8452   8618' ' 1.6143' '    26    218']
     [' 9' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                   ' ' 9' '  6405   6377' ' 0.0613' '202051 202901']
     ['10' 'TO BT BT BT BT BR BT BT BT BT AB                                                               ' '10' '  5818   5792' ' 0.0582' '   646   5434']
     ['11' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                   ' '11' '  4965   4944' ' 0.0445' ' 72994  72990']
     ['12' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                                   ' '12' '  4882   4900' ' 0.0331' ' 79661  79660']
     ['13' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD                                       ' '13' '  4359   4169' ' 4.2331' '114637 114662']
     ['14' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SA                                       ' '14' '  3892   3961' ' 0.6063' '114632 114637']
     ['15' 'TO BT BT BT BT BT SR SR SR SA                                                                  ' '15' '  3836   3811' ' 0.0817' '103637 103565']
     ['16' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                    ' '16' '  3819   3795' ' 0.0757' '161576 163676']
     ['17' 'TO BT BT BT BT BT SR BR SR SR SA                                                               ' '17' '  3505   3622' ' 1.9207' '209809 209925']
     ['18' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                                    ' '18' '  3533   3505' ' 0.1114' '161976 161568']
     ['19' 'TO BT BT BT BT BR BT BT BT BT BT SA                                                            ' '19' '  3473   3414' ' 0.5054' '  6573   6656']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## in A but not B 
    [['727' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT SD                                                ' '727' '    28      0' ' 0.0000' '134671     -1']
     ['757' 'TO BT BT BT BT BT SC SA                                                                        ' '757' '    26      0' ' 0.0000' '132133     -1']
     ['1201' 'TO BT BT BT BT BT SR BR SR AB                                                                  ' '1201' '    15      0' ' 0.0000' '229107     -1']
     ['1208' 'TO BT BT BT BT BT SR AB                                                                        ' '1208' '    15      0' ' 0.0000' '427907     -1']
     ['1373' 'TO BT BT BT BT BR BT BT BT BT BT BR BT BT BR SA                                                ' '1373' '    13      0' ' 0.0000' '889146     -1']
     ['1475' 'TO BT BT BR BT BT BT BT BT BT BT BT BT SA                                                      ' '1475' '    12      0' ' 0.0000' ' 75721     -1']
     ['1614' 'TO BT BT BT BT BT SC SR SA                                                                     ' '1614' '    11      0' ' 0.0000' '246537     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## in B but not A 
    [['1544' 'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT SC RE AB                                       ' '1544' '     0     11' ' 0.0000' '    -1 139224']
     ['1671' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BR AB                                       ' '1671' '     0     11' ' 0.0000' '    -1 285641']]

    In [6]:                                                           


28/1M LEVEL ISSUE::

    C2CUT=100 SEL="TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT SD" ~/j/ntds/ntds3.sh 
                      [---------]   [----------][------------??]

    ## LOOKS LIKE AN EXTRA "BT" AT REMOTE PMT  
    ## INVESTIGATIONS BELOW : THE FIRST FEW OF SUCH HISTORIES ARE LANDING ON THE CURVE OF THE VIRTUAL WRAPPER
    ## WITH A NEAR DEGENERATE FIRST TWO INTERSECTS ONTO THE CURVE OF THE VIRTUAL WRAPPER


::

    In [10]: i                                                                                                                                                                                               
    Out[10]: 138938

    In [7]: a.f.record[i,:20,0]                                                                                                                                                                              
    Out[7]: 
    array([[-3175.228, 10467.324, 15785.413,     0.1  ],
           [-3186.896, 10505.791, 15844.604,     0.43 ],
           [-3189.652, 10514.876, 15858.585,     0.508],
           [-3191.009, 10519.349, 15866.566,     0.555],
           [-3191.409, 10520.667, 15868.581,     0.567],
           [-3192.284, 10523.551, 15873.64 ,     0.597],
           [-3193.289, 10526.864, 15868.88 ,     0.627],
           [-3193.74 , 10528.353, 15867.001,     0.638],
           [-3195.302, 10533.501, 15859.491,     0.685],
           [-3198.497, 10544.034, 15846.102,     0.765],
           [-5113.261, 16856.256,  7821.857,    48.654],  ###
           [-5113.28 , 16856.318,  7821.778,    48.654],  ### DEGENERATE DOUBLE BT ? 
           [-5121.067, 16881.986,  7789.147,    48.849],
           [-5126.725, 16893.408,  7778.972,    48.933],
           [-5128.41 , 16900.22 ,  7769.561,    48.987],
           [-5132.529, 16908.547,  7762.118,    49.048],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)

::

    In [11]: i = 134671

    In [12]: a.f.record[i,:20,0]                                                                                                                                                                             
    Out[12]: 
    array([[-3175.74 , 10469.013, 15784.215,     0.1  ],
           [-3187.665, 10508.322, 15844.703,     0.437],
           [-3190.407, 10517.363, 15858.614,     0.515],
           [-3191.768, 10521.851, 15866.648,     0.563],
           [-3192.172, 10523.181, 15868.681,     0.574],
           [-3193.05 , 10526.077, 15873.776,     0.604],
           [-3194.093, 10529.515, 15869.064,     0.634],
           [-3194.561, 10531.059, 15867.207,     0.645],
           [-3196.18 , 10536.396, 15859.776,     0.693],
           [-3199.57 , 10547.568, 15846.239,     0.776],
           [-4998.604, 16478.25 ,  8661.134,    44.521],  ##
           [-4998.614, 16478.283,  8661.094,    44.521],  ## 
           [-5005.801, 16501.975,  8632.391,    44.696],
           [-5011.088, 16513.076,  8622.707,    44.776],
           [-5012.457, 16518.22 ,  8616.09 ,    44.816],
           [-5016.171, 16526.137,  8609.075,    44.873],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)


    In [14]: a.f.record[i,:20,1].view(np.int32)                                                                                                                                                              
    Out[14]: 
    array([[-1104740444,  1057595729,  1062455236,           0],
           [-1104740444,  1057595729,  1062455236,       26601],
           [-1105864668,  1056373798,  1063065574,       26601],
           [-1104687605,  1057639274,  1062424223,       26601],
           [-1105737075,  1056584107,  1063000873,       26601],
           [-1103873652,  1058310195, -1085565930,       26601],
           [-1102909264,  1059104982, -1086242160,       26601],
           [-1103990937,  1058213534, -1085489519,       26601],
           [-1102961174,  1059062202, -1086203463,       26601],
           [-1102961174,  1059062202, -1086203464,       26601],

           [-1102961176,  1059062202, -1086203464,       28998],
           [-1102961178,  1059062202, -1086203464,       28998],
           [-1095961578,  1060476344, -1088527953,       28998],
           [-1104871717,  1058740249, -1085836485,       28998],
           [-1096179120,  1060423434, -1088409285,       28998],
           [-1096179120,  1060423434, -1088409285,       28998],
           [          0,           0,           0,           0],
           [          0,           0,           0,           0],
           [          0,           0,           0,           0],
           [          0,           0,           0,           0]], dtype=int32)



Can I find the transform from 26601 ? YEP the inst index is saved with the record::

    In [59]: cf.inst[26601]                                                                                                                                                                                  
    Out[59]: 
    array([[    0.24 ,    -0.792,     0.562,     0.   ],
           [   -0.957,    -0.29 ,     0.   ,     0.   ],
           [    0.163,    -0.538,    -0.827,     0.   ],
           [-3169.384, 10448.06 , 16077.108,     0.   ]], dtype=float32)

    In [63]: cf.inst[28998]                                                                                                                                                                                  
    Out[63]: 
    array([[    0.133,    -0.425,     0.895,     0.   ],
           [   -0.954,    -0.299,     0.   ,     0.   ],
           [    0.268,    -0.854,    -0.446,     0.   ],
           [-5206.227, 16598.227,  8664.55 ,     0.   ]], dtype=float32)



    In [15]: a.f.sframe                                                                                                                                                                                      
    Out[15]: 
    sframe       : 
    path         : /tmp/blyth/opticks/GEOM/V1J011/ntds3/ALL1/p001/sframe.npy
    meta         : creator:sframe::getFrameArray
    frs:NNVT:0:1000
    ek:OPTICKS_INPUT_PHOTON_FRAME
    ev:NNVT:0:1000
    ekvid:sframe_OPTICKS_INPUT_PHOTON_FRAME_NNVT_0_1000
    ce           : array([-3156.737, 10406.367, 16012.954,   348.289], dtype=float32)
    grid         : ix0    0 ix1    0 iy0    0 iy1    0 iz0    0 iz1    0 num_photon    0 gridscale     0.0000
    bbox         : array([[0., 0., 0.],
           [0., 0., 0.]], dtype=float32)
    target       : midx    109 mord      0 iidx   1000       inst       0   
    qat4id       : ins_idx     -1 gas_idx   -1   -1 
    m2w          : 
    array([[    0.24 ,    -0.792,     0.562,     0.   ],
           [   -0.957,    -0.29 ,     0.   ,     0.   ],
           [    0.163,    -0.538,    -0.827,     0.   ],
           [-3169.384, 10448.06 , 16077.108,     1.   ]], dtype=float32)

    w2m          : 
    array([[    0.24 ,    -0.957,     0.163,     0.   ],
           [   -0.792,    -0.29 ,    -0.538,     0.   ],
           [    0.562,    -0.   ,    -0.827,     0.   ],
           [   -0.005,     0.001, 19434.   ,     1.   ]], dtype=float32)

    id           : 
    array([[ 1.   , -0.   , -0.   ,  0.   ],
           [ 0.   ,  1.   , -0.   ,  0.   ],
           [-0.   , -0.   ,  1.   ,  0.   ],
           [ 0.001,  0.   ,  0.   ,  1.   ]], dtype=float32)
    ins_gas_ias  :  ins      0 gas    0 ias    0 





28/1M LEVEL ISSUE::

    C2CUT=100 SEL="TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT SD" ~/j/ntds/ntds3.sh 
                      [---------]   [----------][------------??]



::

    In [2]: sel                                                                                                                                                                                              
    Out[2]: 
    array([134671, 138938, 140473, 142361, 142808, 143160, 144924, 145086, 145087, 147297, 149293, 149693, 152323, 152394, 153984, 154028, 156583, 156902, 158140, 158361, 158633, 160201, 160417, 864550,
           865650, 865707, 865796, 915625])


::

    APID=134671 PICK=A ~/j/ntds/ntds3.sh 
    APID=138938 PICK=A ~/j/ntds/ntds3.sh 

    APID=138938 PICK=A NOGRID=1 ~/j/ntds/ntds3.sh 
    APID=138938 PICK=A NOGRID=1 NOFRAME=1 ~/j/ntds/ntds3.sh 

    APID=134671 PICK=A NOGRID=1 INST_FRAME=28998 ~/j/ntds/ntds3.sh 
    APID=138938 PICK=A NOGRID=1 INST_FRAME=29285 ~/j/ntds/ntds3.sh 
    APID=140473 PICK=A NOGRID=1 INST_FRAME=29403 ~/j/ntds/ntds3.sh 
    APID=142808 PICK=A NOGRID=1 INST_FRAME=29586 ~/j/ntds/ntds3.sh 


HMM : tis awkward navigating to the remote PMT after the bounce, how to jump to a different frame ? 
Using INST_FRAME allows to override the default event frame W2M 
So can see the history from the remote PMT frame where the photon ends. 


Need to find the correct remote instance for the photon::

    In [5]: np.c_[np.unique( a.f.record[134671,:,1,3].view(np.int32), return_index=True, return_counts=True )]                                   
    Out[5]: 
    array([[    0,     0,    17],
           [26601,     1,     9],
           [28998,    10,     6]])


    In [4]: np.c_[np.unique( a.f.record[138938,:,1,3].view(np.int32), return_index=True, return_counts=True )]                                   
    Out[4]: 
    array([[    0,     0,    17],
           [26601,     1,     9],
           [29285,    10,     6]])

    In [6]: np.c_[np.unique( a.f.record[140473,:,1,3].view(np.int32), return_index=True, return_counts=True )]                                   
    Out[6]: 
    array([[    0,     0,    17],
           [26601,     1,     9],
           [29403,    10,     6]])

    In [7]: np.c_[np.unique( a.f.record[142808,:,1,3].view(np.int32), return_index=True, return_counts=True )]                                   
    Out[7]: 
    array([[    0,     0,    17],
           [26601,     1,     9],
           [29586,    10,     6]])


