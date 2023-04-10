blyth-88-swap-spho-with-C4Lab-in-U4
======================================

DONE : remove old WITH_G4OPTICKS FROM S+C Processes and everywhere else
------------------------------------------------------------------------

::

    epsilon:~ blyth$ jcv DsG4Scintillation
    2 files to edit
    ./Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
    epsilon:junosw blyth$ 

    epsilon:junosw blyth$ jcv G4Cerenkov_modified
    2 files to edit
    ./Simulation/DetSimV2/PhysiSim/include/G4Cerenkov_modified.hh
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc
    epsilon:junosw blyth$ 


DONE : general removal of old WITH_G4OPTICKS
-----------------------------------------------

::

    epsilon:junosw blyth$ jgl WITH_G4OPTICKS

    ./Simulation/DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc
    ./Simulation/DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    ./Simulation/DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc
          This lot are destined for deletion 

    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc

    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc

    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    epsilon:junosw blyth$ 


Getting less::

    epsilon:opticks blyth$ jgl WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc
    ./Simulation/DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    ./Simulation/DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc

    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    epsilon:junosw blyth$ 

Down to just the ones needing deletion::

    epsilon:junosw blyth$ jgl WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc
    ./Simulation/DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    ./Simulation/DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc
    epsilon:junosw blyth$ 




DONE : switch over to C4Pho from spho
-----------------------------------------

* actually the U4 methods hide the label type, so this change actually needed in opticks/U4


DONE : mostly hide the label type from junosw
----------------------------------------------------

* notice that spho is not visible in U4.hh its used in private statics within U4.cc
* HMM: hiding spho/C4Pho type from junosw is good ... where is C4Pho visible in junosw, can it be hidden ? 

  * adding C4Track to do this, C4 now at 0.1.0 

::

    epsilon:opticks blyth$ jgr C4Pho
    ./Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh:struct C4Pho ; 
    ./Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh:        C4Pho* m_track_label ; 
    ./Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc:#include "C4Pho.h"
    ./Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc:    m_track_label = C4TrackInfo<C4Pho>::GetRef(_track);

    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#include "C4Pho.h"
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    C4Pho* label = C4TrackInfo<C4Pho>::GetRef(step->GetTrack());

spho not visible in junosw::

    epsilon:junosw blyth$ jgr spho                                          
    ./Simulation/GenTools/src/GtOpticksTool.cc:#include "sphoton.h"
    ./Simulation/GenTools/src/GtOpticksTool.cc:        sphoton p ;   
    ./Simulation/GenTools/src/GtOpticksTool.cc:        sphoton::Get(p, m_input_photon, idx );  
    ./Simulation/GenTools/src/GtOpticksTool.cc:        sphotond p ;   
    ./Simulation/GenTools/src/GtOpticksTool.cc:        sphotond::Get(p, m_input_photon, idx );  
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:      U4::GenPhotonEnd(i, aSecondaryTrack);  // sets spho label into Geant4 user track info 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:    G4Element* P =  G4Element::GetElement("Phosphorus", any_warnings);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        P = new G4Element("Phosphorus", "P", 15, 30.9738*g/mole);
    epsilon:junosw blyth$ 


DONE : junoSD_PMT_v2
----------------------

Tidied up, moving some stuff into junoSD_PMT_v2_Debug


DONE : cleaned up junoPMTOpticalModel using higher level C4Track from C4 0.1.1
------------------------------------------------------------------------------------

In junoPMTOpticalModel the label used:

1. to see if debug should be provided for a track, and to pass fastsim status to the recorder::

    167 void junoPMTOpticalModel::GetLabel(const G4Track* _track)
    168 {
    169 #if defined(WITH_G4CXOPTICKS) || defined(PMTSIM_STANDALONE)
    170     m_track_label = C4TrackInfo<C4Pho>::GetRef(_track);
    171     assert( m_track_label && "all photon tracks must be labelled" );
    172     bool PIDX_DUMP = m_track_label->id == PIDX && PIDX_ENABLED ;
    173     LOG_IF(info, PIDX_DUMP) << " PIDX " << PIDX << " label.id " << m_track_label->id ;
    174 #endif
    175 }

    390 #if defined(WITH_G4CXOPTICKS) || defined(PMTSIM_STANDALONE)
    391     bool PIDX_DUMP = m_track_label->id == PIDX && PIDX_ENABLED ;
    392     LOG_IF(info, PIDX_DUMP) << " PIDX " << PIDX << " label.id " << m_track_label->id << " dist1 " << dist1 << " trig " << trig << " whereAmI " << whereAm    I ;
    393 #endif
    ...
    615         char status = '?' ;
    616         if(      u0 < A)    status = u1 < D ? 'D' : 'A' ;
    617         else if( u0 < A+R)  status = 'R' ;
    618         else                status = 'T' ;
    619 
    620         m_track_label->uc4.w = status ;



2. to associate track index into debug info::

    junoPMTOpticalModel::CollectDebugInfo
    ...
    dbg.index = m_track_label->ix ;


Can do both those without needing "m_track_label" or any storage with an additional U4 static funcs.


Added C4Track to C4 so can do the above after 0.0.9 with::

    C4Track::GetLabelId(_track) ; 

    C4Track::SetLabelFlag(track, status ); 



DONE : Opticks/U4 needs to use Custom4 when found, but not require Custom4 
------------------------------------------------------------------------------ 

Note that junosw must always find Custom4 : so when using Opticks with junosw Custom4 must also be found 
for Opticks too.  

::

    epsilon:opticks blyth$ opticks-f Custom4
    ./u4/CMakeLists.txt:set(Custom4_VERBOSE ON)
    ./u4/CMakeLists.txt:find_package(Custom4 CONFIG)   ## NB : NOT REQUIRED
    ./u4/CMakeLists.txt:message(STATUS "${CMAKE_CURRENT_LIST_FILE} : Custom4_FOUND     : ${Custom4_FOUND}")
    ./u4/CMakeLists.txt:if(Custom4_FOUND)
    ./u4/CMakeLists.txt:    target_link_libraries( ${name} PUBLIC Custom4::Custom4 )
    ./u4/tests/CMakeLists.txt:   U4Custom4Test.cc
    ./u4/tests/U4Custom4Test.sh:U4Custom4Test
    ./u4/tests/U4Custom4Test.cc:U4Custom4Test.cc
    epsilon:opticks blyth$ 




