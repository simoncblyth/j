blyth-88-insitu-chi2-history-comparison
========================================

Context
---------

* aside :doc:`blyth-88-revive-input-photons`


Compare Machinery
-------------------

Workstation::

    N=0 ntds2
    N=1 ntds2


Laptop::

    jxn                 ## cd ~/j/ntds
    ./ntds.sh grab 
    ./ntds.sh cf

insitu gun comparison between N=0,1 has different photon counts::

    In [1]: a.f.photon.shape
    Out[1]: (9915, 4, 4)

    In [2]: b.f.photon.shape
    Out[2]: (9810, 4, 4)


And very poor chi2 (kludged comparison by using first 8000)::

    ./ntds.sh VERSION:-1 load both AFOLD and BFOLD
    CSGFoundry.CFBase returning None, note:via NO envvars 
    ERROR CSGFoundry.CFBase returned None OR non-existing CSGFoundry dir so cannot CSGFoundry.Load
    Fold : symbol                              a base /tmp/blyth/opticks/GEOM/ntds2/ALL0/000 
    Fold : symbol                              b base /tmp/blyth/opticks/GEOM/ntds2/ALL1/000 
    qcf.aqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x

    [[b'1340' b'2' b'SI AB                                                                                           ']
     [b'1307' b'9' b'SI BT BT BT BT BT BT BT SD                                                                      ']
     [b'537' b'7' b'SI SC BT BT BT BT BT BT BT SD                                                                   ']
     [b'388' b'17' b'SI RE BT BT BT BT BT BT BT SD                                                                   ']
     [b'361' b'0' b'SI RE AB                                                                                        ']
     [b'291' b'36' b'SI SC AB                                                                                        ']
     [b'209' b'13' b'SI SC SC BT BT BT BT BT BT BT SD                                                                ']
     [b'158' b'38' b'SI RE SC BT BT BT BT BT BT BT SD                                                                ']
     [b'135' b'140' b'SI RE RE BT BT BT BT BT BT BT SD                                                                ']
     [b'104' b'47' b'SI RE RE AB                                                                                     ']]

    qcf.bqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x
    [[b'1229' b'11' b'SI AB                                                                                           ']
     [b'407' b'7' b'SI BT BT BT BT BT BT SD                                                                         ']
     [b'407' b'26' b'SI BT BT BT BT BT BT SA                                                                         ']
     [b'362' b'0' b'SI RE AB                                                                                        ']
     [b'265' b'5' b'SI SC AB                                                                                        ']
     [b'235' b'30' b'SI SC BT BT BT BT BT BT SD                                                                      ']
     [b'189' b'29' b'SI SC BT BT BT BT BT BT SA                                                                      ']
     [b'146' b'83' b'SI RE BT BT BT BT BT BT SA                                                                      ']
     [b'133' b'65' b'SI RE BT BT BT BT BT BT SD                                                                      ']
     [b'113' b'8' b'SI BT BT SA                                                                                     ']]

    QCF qcf 
    c2sum :  4965.0996 c2n :    54.0000 c2per:    91.9463  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  4965.10/54:91.946 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'SI AB                           ' ' 0' '  1340   1229' ' 4.7960' '     2     11']
     [' 1' 'SI BT BT BT BT BT BT BT SD      ' ' 1' '  1307     16' '1259.7740' '     9     36']
     [' 2' 'SI SC BT BT BT BT BT BT BT SD   ' ' 2' '   537     10' '507.7313' '     7    827']
     [' 3' 'SI BT BT BT BT BT BT SA         ' ' 3' '     0    407' '407.0000' '    -1     26']
     [' 4' 'SI BT BT BT BT BT BT SD         ' ' 4' '     0    407' '407.0000' '    -1      7']
     [' 5' 'SI RE BT BT BT BT BT BT BT SD   ' ' 5' '   388      2' '382.0410' '    17   4203']
     [' 6' 'SI RE AB                        ' ' 6' '   361    362' ' 0.0014' '     0      0']
     [' 7' 'SI SC AB                        ' ' 7' '   291    265' ' 1.2158' '    36      5']
     [' 8' 'SI SC BT BT BT BT BT BT SD      ' ' 8' '     2    235' '229.0675' '  7045     30']



Changing geometry with N=0/1 will change random consumption
and hence change the generated gensteps so will get event 
fluctuations that invalidate history chi2 comparison at reasonable stats. 

Hence need to use common input photons for chi2 comparisons
at reasonable statistical level (say up to 1M photons) to be valid. 

* :doc:`blyth-88-revive-input-photons`


