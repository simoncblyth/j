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

NAM=$(basename $TAR)
NAM=${NAM/.tar}

DOM=opticks.ihep.ac.cn
REL=ok/releases
DIR=/cvmfs/$DOM/$REL
LNK=Opticks-vLatest

info(){ cat << EOI

TAR : $TAR
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


   cvmfs_server transaction $DOM   ## start transaction to make it writable
   tar xvf $TAR -C $DIR            ## -C cd to the DIR before extraction

   cd $DIR/$ARCH && ln -sfn $NAM $LNK && cd
   [ $? -ne 0 ] && echo $BASH_SOURCE FAILED TO PLANT LNK $LNK && exit 1

   cvmfs_server publish -m "$BASH_SOURCE $TAR " $DOM 

   ls -l $DIR
   info

else
   echo $BASH_SOURCE argument naming existing TAR file [$TAR] is required 
   info
   exit 2
fi 

exit 0

