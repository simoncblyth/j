# anaconda_test.bash

usage(){ cat << EOU
::

   source anaconda_test.bash


EOU
}

path(){ cat << EOP
/hpcfs/juno/junogpu/blyth/junotop/offline/InstallArea/python
/hpcfs/juno/junogpu/blyth/junotop/sniper/InstallArea/python
/hpcfs/juno/junogpu/blyth/junotop/offline/InstallArea/amd64_linux26/lib
/hpcfs/juno/junogpu/blyth/junotop/sniper/InstallArea/amd64_linux26/lib
/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/python-yaml/5.1.2/lib/python2.7/site-packages
/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/python-cython/0.29.16/lib/python2.7/site-packages
/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.22.06/lib
/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/xrootd/4.12.6/lib/python2.7/site-packages
/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Git/1.8.4.3/lib/python2.7/site-packages
/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Python/2.7.17/lib/./python2.7/lib-dynload
/hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Python/2.7.17/lib/python2.7/site-packages
EOP
}


joi-(){ echo "$*" ; } # cannot directly echo to force more than just the echo to use the IFS 
join(){ IFS=$1 joi- ${*:2} ; }


check()
{
   declare -a a
   local p 
   for p in $(path) ; do  
      echo p $p
      [ -n "$p" ] && a+=($p)
   done
   local n=${#a[@]}
   echo n $n 

   local i 
   local m
   for ((i=0;i<$n;i++)); do
       printf " %3d : %s \n" $i ${a[$i]} 
       ((m=i+1))

       PP=$(join : ${a[@]:0:$m} )
       echo $PP      
       env -i PYTHONPATH=$PP bash -c "source /cvmfs/juno.ihep.ac.cn/sw/anaconda/Anaconda3-2020.11-Linux-x86_64/bin/activate root622"   
   done


}


check

