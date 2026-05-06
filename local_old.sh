local_ok_externals_pre_release()
{
   : ~/local.sh
   : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy versions matching JUNOSW
   : NB versions need to match those used by gitlab-ci build when using the gitlab cvmfs release

   local_unset

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Xercesc/3.2.4/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/CLHEP/2.4.7.1/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/custom4/0.1.8/bashrc

   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Python/3.9.19/bashrc
   source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/python-numpy/1.23.5/bashrc

   export VIP_MODE=ok_externals
   export VIP_DESC="Opticks JUNOSW externals in common manually setup from cvmfs : Xercesc + CLHEP + Geant4 + custom4 + Python + python-numpy"
}

old_oje()
{
   : ~/j/local.sh
   : moved OJ testing into OJ repo
   oj_envset
}



old_oj_test()
{
   : ~/j/local.sh
   : invoke oj_envset that sources the envset.sh picked via opticks ENVSET bash function
   : then runs a single event simulation under gdb debugger
   : 
   : TESTGROUP string used to encapsulate at a high level what is done eg "gun" "doublemuon"
   : TEST string used to encapsulate options used varying how tests are run eg "hitlitemerged"
   :
   : HMM - LACKS IDENTITY MACHINERY OF ~/j/blyth-OJ-pmt-hit-type-2-for-muon-hits/detsim.sh
   : HMM - NEEDS TO USE SProf.sh profile/logparse machinery


   local defarg=""
   local arg=${1-$defarg}

   source ~/.opticks/TEST/TEST.sh
   [ -z "$TESTGROUP" ] && echo $FUNCNAME - ERROR TESTGROUP NOT DEFINED && return 1
   [ -z "$TEST"      ] && echo $FUNCNAME - ERROR TEST NOT DEFINED      && return 2

   local IDENTITY=$FUNCNAME

   #local logbase=/tmp/$USER/opticks
   local logbase=/data2/blyth/local
   local LOGBASE=$logbase
   local LOGFOLD=$LOGBASE/$FUNCNAME
   local LOGSTAMP=$(date +%Y%m%d)
   local LOGDIR=$LOGFOLD/$LOGSTAMP/$TEST
   local LOGNAME=$IDENTITY.log

   local vv="BASH_SOURCE FUNCNAME test TEST TMP GEOM LOGBASE LOGFOLD LOGSTAMP LOGDIR LOGNAME PWD SProf__WRITE"
   vvp(){ for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done ; }

   if [ "${arg/info}" != "$arg" ]; then
      vvp
      return 0
   fi


   oj_envset
   [ $? -ne 0 ] && echo $FUNCNAME - ERROR WITH oj_envset && return 1

   source dbg__.sh


   mkdir -p $LOGDIR
   pushd $LOGDIR
   rm -f $LOGNAME
   vvp > $LOGNAME


   ## THIS NOT USING TEST IN THE MODERN SENSE
   if [ "$TEST" == "default" ]; then

       vvp
       dbg__ \
          $(which python) \
          $(which tut_detsim.py) \
          --evtmax 1 \
          gun


   elif [[ "$TEST" =~ ^hit(merged|lite|litemerged)?$ ]]; then

       export SProf__WRITE=1    # enable profile writing see SProf::Write

       if [ -n "$LOG" ]; then
           # general loglevel of the class/struct
           export junoSD_PMT_v2_Opticks=INFO
           export QSim=INFO
           export SEvt=INFO

           export SEvt__SAVE=1       # extra logging re what is saved
           export SEvt__DIRECTORY=1  # extra logging re where arrays are saved
       fi
       vv="$vv LOG"


       # configure SEvt arrays to save
       export OPTICKS_MAX_SLOT=M10
       export OPTICKS_EVENT_MODE=HitPhotonSeq  ## try some SEvt saving with OJ
       export OPTICKS_MODE_SAVE=1  # 0:absolute, 1:relative to invoking dir



       local evtmax=1
       local pmt_hit_type=1
       local pmtsd_merge_twindow=1
       local opticks_mode_merge_override=1

       : NB use of "--pmtsd-merge-twindow 1" means that hit merging is enabled
       : BUT to check performance of GPU vs CPU merging the OPTICKS_MODE_MERGE_OVERRIDE
       : envvar is used control whether CPU/GPU merging happens

       case $TEST in
          hit)           pmt_hit_type=1 ; opticks_mode_merge_override=0 ;;
          hitmerged)     pmt_hit_type=1 ; opticks_mode_merge_override=1 ;;
          hitlite)       pmt_hit_type=2 ; opticks_mode_merge_override=0 ;;
          hitlitemerged) pmt_hit_type=2 ; opticks_mode_merge_override=1 ;;
       esac

       #local topcmd=dbg__
       local topcmd=time
       vv="$vv TEST topcmd evtmax pmt_hit_type pmtsd_merge_twindow opticks_mode_merge_override"

       export OPTICKS_MODE_MERGE_OVERRIDE=$opticks_mode_merge_override

       vvp >> $LOGNAME

       if [ "$TESTGROUP" == "gun" ]; then

           $topcmd \
              $(which python) \
              $(which tut_detsim.py) \
              --evtmax ${evtmax} \
              --pmt-hit-type ${pmt_hit_type} \
              --pmtsd-merge-twindow ${pmtsd_merge_twindow} \
              gun \
              2>&1 | tee -a $LOGNAME


       elif [ "$TESTGROUP" == "doublemuon" ]; then

           $topcmd \
              $(which python) \
              $(which tut_detsim.py) \
              --evtmax ${evtmax} \
              --pmt-hit-type ${pmt_hit_type} \
              --pmtsd-merge-twindow ${pmtsd_merge_twindow} \
              gun \
              2>&1 | tee -a $LOGNAME

       fi


       unset SProf__WRITE

   else
       printf "$FUNCNAME - ERROR TEST[$TEST] UNHANDLED \n"
   fi

   vvp
   popd

   return 0
}




old_ojtt()
{
   : ~/j/local.sh
   : NB this uses brackets creating subshell foreach TEST invokation

   local defarg=""
   local arg=${1-$defarg}

   local tests="hit hitmerged hitlite hitlitemerged"
   local tt=${TESTS:-$tests}

   
   local vv="BASH_SOURCE FUNCNAME tests TESTS tt defarg arg"

   if [ "${arg/info}" != "$arg" ]; then
      for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
      return 0
   fi


   local t
   for t in $tt ; do
   (
      printf "$FUNCNAME t[$t]\n"
      TEST=$t ojt $*
      [ $? -ne 0 ] && printf "$FUNCNAME ERROR FROM [TEST=$t ojt]\n"
   )
   done
}





