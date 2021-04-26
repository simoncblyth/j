tds-mu-120s-launch-interval
==============================



Issue : unexpected ~120s between launches, when launch time if ~45s
----------------------------------------------------------------------

* this is without on GPU culling so are copying lots more photon hits than necessary 
* also the hits and hiys are pulled back separately 
* what is the overhead ?
* TODO: profiling to find out 



1st quick parse of the tds log : /tmp/blyth/opticks/tds/python2.7.log
--------------------------------------------------------------------------

::

    2021-04-26 23:50:49.246 FATAL [128777] [OPropagator::launch@272]  skipahead 0
    2021-04-26 23:50:49.246 FATAL [128777] [ORng::setSkipAhead@160]  skip as as WITH_SKIPAHEAD not enabled 

    2021-04-26 23:51:36.309 INFO  [128777] [OPropagator::launch@287] 0 : (0;52309265,1)  launch time 47.0626

    2021-04-26 23:51:37.171 INFO  [128777] [OEvent::downloadHits@485]  nhit 15607454 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-04-26 23:51:37.603 INFO  [128777] [OEvent::downloadHiys@519]  nhiy 15607454 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-04-26 23:51:38.812 FATAL [128777] [G4Opticks::propagateOpticalPhotons@1152]  m_way_enabled num_hiys 15607454

    // what is happening here ?

    2021-04-26 23:52:50.191 FATAL [128777] [G4Opticks::reset@526]  m_way_enabled reset m_hiys 
    2021-04-26 23:52:54.816 INFO  [128777] [OpticksRun::createEvent@115]  tagoffset 8 skipaheadstep 0 skipahead 0
    2021-04-26 23:52:54.919 FATAL [128777] [OPropagator::launch@272]  skipahead 0
    2021-04-26 23:52:54.919 FATAL [128777] [ORng::setSkipAhead@160]  skip as as WITH_SKIPAHEAD not enabled 

    2021-04-26 23:53:41.990 INFO  [128777] [OPropagator::launch@287] 0 : (0;57169882,1)  launch time 47.0712

    2021-04-26 23:53:42.898 INFO  [128777] [OEvent::downloadHits@485]  nhit 16864901 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-04-26 23:53:43.365 INFO  [128777] [OEvent::downloadHiys@519]  nhiy 16864901 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-04-26 23:53:44.687 FATAL [128777] [G4Opticks::propagateOpticalPhotons@1152]  m_way_enabled num_hiys 16864901
    2021-04-26 23:55:02.608 FATAL [128777] [G4Opticks::reset@526]  m_way_enabled reset m_hiys 
    2021-04-26 23:55:07.213 INFO  [128777] [OpticksRun::createEvent@115]  tagoffset 9 skipaheadstep 0 skipahead 0
    2021-04-26 23:55:07.300 FATAL [128777] [OPropagator::launch@272]  skipahead 0
    2021-04-26 23:55:07.300 FATAL [128777] [ORng::setSkipAhead@160]  skip as as WITH_SKIPAHEAD not enabled 

    2021-04-26 23:55:50.848 INFO  [128777] [OPropagator::launch@287] 0 : (0;54398379,1)  launch time 43.5482

    2021-04-26 23:55:51.919 INFO  [128777] [OEvent::downloadHits@485]  nhit 15774984 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-04-26 23:55:52.362 INFO  [128777] [OEvent::downloadHiys@519]  nhiy 15774984 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-04-26 23:55:53.613 FATAL [128777] [G4Opticks::propagateOpticalPhotons@1152]  m_way_enabled num_hiys 15774984
    2021-04-26 23:57:06.613 FATAL [128777] [G4Opticks::reset@526]  m_way_enabled reset m_hiys 
    2021-04-26 23:57:09.783 INFO  [128777] [G4Opticks::Finalize@284] G4Opticks.desc ok 0x5ed7fb0 opmgr 0x15b31dcb0







ana/tds.py parsing the log::

    tds-grab
    tds.py 

::

    Mon Apr 26 23:39:22 2021 069000 : n:53856062 fn: 53.86 lt:   48.6860  dt:  132.8910 
    Mon Apr 26 23:41:29 2021 049000 : n:46168072 fn: 46.17 lt:   41.4006  dt:  126.9800 
    Mon Apr 26 23:43:24 2021 207000 : n:49612456 fn: 49.61 lt:   41.0512  dt:  115.1580 
    Mon Apr 26 23:45:27 2021 520000 : n:58532966 fn: 58.53 lt:   48.1707  dt:  123.3130 
    Mon Apr 26 23:47:34 2021 790000 : n:54414212 fn: 54.41 lt:   42.7393  dt:  127.2700 
    Mon Apr 26 23:49:33 2021 732000 : n:50214628 fn: 50.21 lt:   41.9189  dt:  118.9420 
    Mon Apr 26 23:51:36 2021 309000 : n:52309265 fn: 52.31 lt:   47.0626  dt:  122.5770 
    Mon Apr 26 23:53:41 2021 990000 : n:57169882 fn: 57.17 lt:   47.0712  dt:  125.6810 
    Mon Apr 26 23:55:50 2021 848000 : n:54398379 fn: 54.40 lt:   43.5482  dt:  128.8580 

                                                     
* fn : millions of photons
* lt : launch time seconds
* dt : time interval between launches 



