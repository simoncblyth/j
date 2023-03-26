blyth-88-insitu-ana
=====================

j/ntds/ntds.sh 
---------------


HMM is this a(N=0) or b(N=1)::

    epsilon:ntds blyth$ ./ntds.sh 
    CSGFoundry.CFBase returning None, note:via NO envvars 
    ERROR CSGFoundry.CFBase returned None OR non-existing CSGFoundry dir so cannot CSGFoundry.Load
    Fold : symbol                              a base /tmp/blyth/opticks/GEOM/ntds2/ALL/000 
    U4SimulateTest symbol a pid -1 opt  off [0. 0. 0.]

    In [1]: a
    Out[1]: U4SimulateTest symbol a pid -1 opt  off [0. 0. 0.]

    In [2]: a.qtab
    Out[2]: 
    array([[b'1507', b'11', b'SI AB                                                                                           '],
           [b'528', b'7', b'SI BT BT BT BT BT BT SD                                                                         '],
           [b'510', b'26', b'SI BT BT BT BT BT BT SA                                                                         '],
           [b'447', b'0', b'SI RE AB                                                                                        '],
           [b'320', b'5', b'SI SC AB                                                                                        '],
           [b'287', b'30', b'SI SC BT BT BT BT BT BT SD                                                                      '],
           [b'225', b'29', b'SI SC BT BT BT BT BT BT SA                                                                      '],
           [b'168', b'83', b'SI RE BT BT BT BT BT BT SA                                                                      '],
           [b'167', b'65', b'SI RE BT BT BT BT BT BT SD                                                                      '],
           [b'142', b'8', b'SI BT BT SA                                                                                     '],
           [b'133', b'162', b'SI RE RE AB                                                                                     '],
           [b'97', b'15', b'SI BT BT AB                                                                                     '],
           [b'97', b'9', b'SI SC SC AB                                                                                     '],
           [b'89', b'118', b'SI RE SC AB                                                                                     '],
           [b'89', b'122', b'SI SC SC BT BT BT BT BT BT SD                                                                   '],
           [b'78', b'23', b'SI BT BT BT BT BT BT BT SA                                                                      '],
           [b'74', b'39', b'SI SC SC BT BT BT BT BT BT SA                                                                   '],
           [b'71', b'79', b'SI BT BT BT BT BT BT BT SR SA                                                                   '],
           [b'69', b'28', b'SI RE SC BT BT BT BT BT BT SA                                                                   '],
           [b'64', b'190', b'SI RE SC BT BT BT BT BT BT SD                                                                   ']], dtype='|S96')

    In [3]:                                               


Plotting a few things shows no clangers yet
---------------------------------------------

::

    MODE=2 ./ntds.sh 
    MODE=3 ./ntds.sh 


TODO : need insitu metadata to identify the POM/PMT quadrant from the fold
-----------------------------------------------------------------------------

* try doing this at bash level in ntds3::

::

    568    export OPTICKS_EVENT_MODE=StandardFullDebug
    569    export OPTICKS_MAX_BOUNCE=31
    570 
    571    export POM=${POM:-1}
    572    export VERSION=${N:-1}
    573    export LAYOUT="POM $POM VERSION $VERSION"
    574 
    575    local opts=""
    576    opts="$opts --opticks-mode $mode"
    577    opts="$opts --no-guide_tube"
    578    opts="$opts --additionacrylic-simplify-csg"
    579 
    580    #case $LSM in   ## pass into UseLSOpticalModel : NOT YET EXPLORED
    581    #   0) opts="$opts --old-optical-model"  ;;
    582    #   1) opts="$opts --new-optical-model"  ;;
    583    #esac 
    584 
    585    case $POM in     ## pass into UsePMTOpticalModel
    586       0) opts="$opts --no-pmt-optical-model"  ;;
    587       1) opts="$opts --pmt-optical-model"     ;;
    588    esac
    589 
    590    case $VERSION in  ## pass into UsePMTNaturalGeometry
    591       0) opts="$opts --pmt-unnatural-geometry" ;;
    592       1) opts="$opts --pmt-natural-geometry"   ;;
    593    esac
    594 
    595    opts="$opts --evtmax $evtmax"
    596    opts="$opts $(anamgr) "



::

    In [3]: a.f.photon_meta
    Out[3]: 
    SCRIPT:ntds2
    ${GEOM}_GEOMList:GEOM_GEOMList


::

    1639 const char* SEvt::ENVMETA = R"LITERAL(
    1640 SCRIPT
    1641 CHECK
    1642 LAYOUT
    1643 TEST
    1644 VERSION
    1645 GEOM
    1646 EXECUTABLE
    1647 ${GEOM}_GEOMList
    1648 )LITERAL" ;
    1649 
    1650 // HIGHER ORDER KEYS WITH TOKENS ARE HANDLED IN ssys::_getenv
    1651 
    1652 void SEvt::AddEnvMeta( NP* a ) // static
    1653 {
    1654     if(a == nullptr) return ;
    1655     typedef std::pair<std::string, std::string> KV ;
    1656     std::vector<KV> kvs ;
    1657     ssys::getenv_(kvs, ENVMETA);
    1658     a->set_meta_kv(kvs) ;
    1659 }
    1660 
    1661 NP* SEvt::makePhoton() const
    1662 {
    1663     NP* p = NP::Make<float>( evt->num_photon, 4, 4 );
    1664     AddEnvMeta(p) ; 
    1665     return p ; 
    1666 }   



TODO : POM=1 PMT=0/1 INSITU COMPARISON
-----------------------------------------






