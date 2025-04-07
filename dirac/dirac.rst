dirac production
====================

http://dirac-code.ihep.ac.cn/juno/ts/run-detsim-ts.sh

::

     01 #!/bin/bash
      2 
      3 cvmfsRepo=$1
      4 softwareVersion=$2
      5 jobid=$3

      6 evtmax=$4
      7 seed=$5

      8 extraArgs=$6
      9 userOutput=$7
     10 preScripts=$8
     11 proxy_urls=$9
     12 ncores=${10}
     13 
     14 export seed
     15 export evtmax
     16 export proxy_urls
     17    
     18 . ./env.sh "$cvmfsRepo" "$softwareVersion"
     19    
     20 if [ "$preScripts" = "" ]; then
     21   echo "no pre scripts are needed!\n"
     22 else
     23   echo "preScripts with $seed: $preScripts"
     24   echo ${preScripts}|awk '{run=$0;system(run)}'
     25   if [[ $? -ne 0 ]]; then
     26     echo "pre script failed. Aborting"
     27     exit 1
     28   fi
     29 fi
     30 
     31 if [ "${userOutput}" -ne 0 ]; then
     32    echo "(/usr/bin/time -v python $TUTORIALROOT/share/tut_detsim.py --no-gdml --evtmax $evtmax --seed $seed --output detsim-${seed}.root --user-output detsim_user-${seed}.root $extraArgs) 1 >>(tail     -c ${maxlogsize} > app.out) 2>>(tail -c ${maxlogsize} > app.err )"
     33   (/usr/bin/time -v python $TUTORIALROOT/share/tut_detsim.py --no-gdml --evtmax $evtmax --seed $seed --output detsim-${seed}.root --user-output detsim_user-${seed}.root $extraArgs) 1> >(tail -c ${maxlogsize} > app.out) 2> >(tail -c ${maxlogsize} > app.err )
     34 else
     35    echo "(/usr/bin/time -v python $TUTORIALROOT/share/tut_detsim.py --no-gdml --evtmax $evtmax --seed $seed --output detsim-${seed}.root $extraArgs) 1 >>(tail -c ${maxlogsize} > app.out) 2>>(tail -    c ${maxlogsize} > app.err )"
     36   (/usr/bin/time -v python $TUTORIALROOT/share/tut_detsim.py --no-gdml --evtmax $evtmax --seed $seed --output detsim-${seed}.root $extraArgs) 1> >(tail -c ${maxlogsize} > app.out) 2> >(tail -c ${ma    xlogsize} > app.err )
     37 fi
     38 
     39 
     40 ls -al
     41 
     42 file_pattern="detsim-*.*sub*"
     43 current_dir=$(pwd)
     44 
     45 for file in $current_dir/$file_pattern; do
     46   if [ -f "$file" ]; then
     47     rm "$file"
     48     echo "Deleted file: $file"
     49   fi
     50 done







http://dirac-code.ihep.ac.cn/juno/ts/env.sh::

     01 #!/bin/bash
      2 
      3 cvmfsRepo=$1
      4 softwareVersion=$2
      5 maxlogsize=$((32*1024*1024))
      6 if [ -z "$cvmfsRepo" ]; then
      7    cvmfsRepo="/cvmfs/juno.ihep.ac.cn"
      8 fi   
      9 
     10 version=`more /etc/redhat-release|tr -cd "[0-9][.]"`
     11 version1=${version%.*}
     12 version2=${version1%.*}
     13 export LD_LIBRARY_PATH=/usr/lib64/:$LD_LIBRARY_PATH
     14 export CMTCONFIG=amd64_linux26
     15 source "${cvmfsRepo}/${softwareVersion}/setup.sh"
     16 if [ "$cvmfsReo" = "/cvmfs/juno.ihep.ac.cn" ]; then
     17    source "${cvmfsRepo}/${softwareVersion}/../../contrib/gcc/*/bashrc"
     18    source "${cvmfsRepo}/${softwareVersion}/../../contrib/binutils/*/bashrc"
     19    source "${cvmfsRepo}/${softwareVersion}/../../contrib/compat/bashrc"
     20 fi
     21 echo $LD_LIBRARY_PATH




