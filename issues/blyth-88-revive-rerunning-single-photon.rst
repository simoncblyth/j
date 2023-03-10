blyth-88-revive-rerunning-single-photon
==========================================


Getting Rerunning to work
-----------------------------


u4t/U4SimulateTest.sh::

    118 if [ -n "$RERUN" ]; then 
    119    export OPTICKS_G4STATE_RERUN=$RERUN
    120    running_mode=SRM_G4STATE_RERUN
    121 else
    122    running_mode=SRM_G4STATE_SAVE
    123 fi
    124 
    125 case $running_mode in 
    126    SRM_G4STATE_SAVE)  reldir=ALL$VERSION ;;
    127    SRM_G4STATE_RERUN) reldir=SEL$VERSION ;;
    128 esac
    129 
    130 ## sysrap/SEventConfig 
    131 export OPTICKS_RUNNING_MODE=$running_mode   # see SEventConfig::RunningMode
    132 export OPTICKS_MAX_BOUNCE=31                # can go upto 31 now that extended sseq.h 
    133 export OPTICKS_EVENT_MODE=StandardFullDebug
    134 

SEventConfig.cc::

    061 int SEventConfig::_RunningMode = SRM::Type(SSys::getenvvar(kRunningMode, _RunningModeDefault));
     62 const char* SEventConfig::_G4StateSpec  = SSys::getenvvar(kG4StateSpec,  _G4StateSpecDefault );
     63 int         SEventConfig::_G4StateRerun = SSys::getenvint(kG4StateRerun, _G4StateRerunDefault) ;
     64 

     92 int         SEventConfig::RunningMode(){ return _RunningMode ; }
     93 const char* SEventConfig::RunningModeLabel(){ return SRM::Name(_RunningMode) ; }
     94 bool SEventConfig::IsRunningModeDefault(){      return RunningMode() == SRM_DEFAULT ; }
     95 bool SEventConfig::IsRunningModeG4StateSave(){  return RunningMode() == SRM_G4STATE_SAVE ; }
     96 bool SEventConfig::IsRunningModeG4StateRerun(){ return RunningMode() == SRM_G4STATE_RERUN ; }
     97 
     98 const char* SEventConfig::G4StateSpec(){  return _G4StateSpec ; }
     99 
    100 /**
    101 SEventConfig::G4StateRerun
    102 ----------------------------
    103 
    104 When rerun mode is not enabled returns -1 even when rerun id is set. 
    105 
    106 **/
    107 int SEventConfig::G4StateRerun()
    108 {
    109     bool rerun_enabled = IsRunningModeG4StateRerun() ;
    110     return rerun_enabled && _G4StateRerun > -1 ? _G4StateRerun : -1  ;
    111 }
    112 


After config to save all g4state (not just 1000) by changing OPTICKS_G4STATE_SPEC to "$num_ph:38"
can rerun the single photon::

    RERUN=4772 N=0 POM=1 ./U4SimulateTest.sh 

    RERUN=4772 BP=junoPMTOpticalModel::DoIt N=0 POM=1 ./U4SimulateTest.sh 



