#!/bin/bash

usage(){ cat << EOU
ok_deploy_to_cvmfs.sh
======================

Usage example::

    A> scp /data1/blyth/local/opticks_Debug/Opticks-v0.3.5.tar O: 
    A> ssh O   ## stratum-zero 
    O> ./ok_deploy_to_cvmfs.sh Opticks-v0.3.5.tar

Note ln -sfn 

-n:--no-dereference 
   allows updating directory links

EOU
}

TAR=$1
CVMFS=${CVMFS:-1}

NAM=$(basename $TAR)
NAM=${NAM/.tar}

DOM=opticks.ihep.ac.cn
REL=ok/releases
DIR=/cvmfs/$DOM/$REL
LNK=Opticks-vLatest

info(){ cat << EOI

TAR : $TAR
CVMFS : $CVMFS
NAM : $NAM
DOM : $DOM
REL : $REL
DIR : $DIR
LNK : $LNK


EOI
}

if [ -f "$TAR" ]; then 

   info

   tar tvf $TAR
   [ $? -ne 0 ] && echo $BASH_SOURCE TAR $TAR invalid && exit 1

   RELP0=$(tar tf $TAR | grep bashrc)  ## eg el9_amd64_gcc11/Opticks-v0.3.5/bashrc
   RELP=${RELP0/\/bashrc}              ## eg el9_amd64_gcc11/Opticks-v0.3.5
   ARCH=$(dirname $RELP)               ## eg el9_amd64_gcc11
   NAMD=$(basename $RELP)              ## eg Opticks-v0.3.5 

   if [ "$NAM" != "$NAMD" ]; then
       echo $BASH_SOURCE FATAL - INCONSISTENT TAR - NAM $NAM NAMD $NAMD 
       exit 1
   fi 


   if [ "$CVMFS" == "1" ]; then
       echo "   [ cvmfs_server transaction $DOM"
       cvmfs_server transaction $DOM   ## start transation to make it writable
       [ $? -ne 0 ] && echo $BASH_SOURCE ERROR - ABORT && exit 1
       echo "   ] cvmfs_server transaction $DOM"
   fi 


   tar xvf $TAR -C $DIR            ## -C cd to the DIR before extraction

   cd $DIR/$ARCH && ln -sfn $NAM $LNK && cd
   [ $? -ne 0 ] && echo $BASH_SOURCE FAILED TO PLANT LNK $LNK && exit 1


   if [ "$CVMFS" == "1" ]; then
      echo "   [ cvmfs_server publish -m \"$BASH_SOURCE $TAR $RELP \" $DOM  "
      cvmfs_server publish -m "$BASH_SOURCE $TAR $RELP " $DOM 
      [ $? -ne 0 ] && echo $BASH_SOURCE ERROR - ABORT && exit 2
      echo "   ] cvmfs_server publish -m \"$BASH_SOURCE $TAR $RELP \" $DOM  "

      echo "   [ cvmfs_server tag $DOM"
      cvmfs_server tag $DOM
      date
      echo "   ] cvmfs_server tag $DOM"
   fi

   ls -l $DIR/$ARCH
   info

else
   echo $BASH_SOURCE argument naming existing TAR file [$TAR] is required 
   info
   exit 2
fi 

exit 0

