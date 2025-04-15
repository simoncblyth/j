#!/bin/bash

usage(){ cat << EOU
oj_deploy_to_cvmfs.sh
=========================

CAUTION : THIS SCRIPT IS INVOKED OVER SSH FROM GITLAB-CI RUNNER 

Usage example::

    A> ssh O   ## stratum-zero 
    O> ./oj_deploy_to_cvmfs.sh incoming/J25.2.3_Opticks-v0.3.3.tar


Note the link planting with "ln -sfn" the "-n:--no-dereference"
option does forcible updating of directory symbolic links.

Issue::

        WARNING! There are open read-only file descriptors in /cvmfs/opticks.ihep.ac.cn

	CernVM-FS transaction error: another transaction is already open



Maybe use ingest ? but no way to plant the latest link that way ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* https://cvmfs-contrib.github.io/cvmfs-tutorial-2021/04_publishing/

Instead of manually starting a transaction, extracting the tarball and then
publishing it, the cvmfs_server command offers a more efficient method for
directly publishing the contents of a tarball::

    cvmfs_server ingest -t mytarball.tar -b some/path repo.organization.tld

The -b option expects the relative location (without leading slash!) in your repository 
where the contents of the tarball, specified with -t, should be extracted.
So in this case the tarball gets extracted to /cvmfs/repo.organization.tld/some/path



EOU
}

TAR=$1
NAM=$(basename $TAR)
NAM=${NAM/.tar}

DOM=opticks.ihep.ac.cn
REL=oj/releases
LNK=Latest

CVMFS=0
case $(uname -n) in
  cvmfs*) CVMFS=1 ; BASE=/cvmfs ;;
       *) BASE=/data1/blyth/local ;; 
esac

DIR=$BASE/$DOM/$REL


vvd(){ for v in $* ; do printf "%20s : %s\n" "$v" "${!v}" ; done ; }
args(){ vvd CVMFS BASE TAR NAM DOM REL DIR LNK ; }

echo [ $0 
args

if [ -f "$TAR" ]; then 

   tar tf $TAR > /dev/null
   [ $? -ne 0 ] && echo $BASH_SOURCE TAR $TAR invalid && exit 1

   RELP0=$(tar tf $TAR | grep ENV.bash)
   RELP=${RELP0/\/ENV.bash/}  # eg J25.2.3_Opticks-v0.3.3/el9_amd64_gcc11/Fri
   RDIR=$(dirname $RELP)      # eg J25.2.3_Opticks-v0.3.3/el9_amd64_gcc11
   RDAY=$(basename $RELP)     # eg Fri


   vv="0 TAR RELP0 RELP RDIR RDAY CVMFS DIR"
   vvd $vv

   if [ "$CVMFS" == "1" ]; then
       echo "   [ cvmfs_server transaction $DOM"
       cvmfs_server transaction $DOM   ## start transation to make it writable
       [ $? -ne 0 ] && echo $BASH_SOURCE ERROR - ABORT && exit 1
       echo "   ] cvmfs_server transaction $DOM"
   fi 


   echo "   [ extract TAR into DIR " 
   mkdir -p $DIR 
   tar xf $TAR -C $DIR
   echo "   ] extract TAR into DIR " 

   echo "   [ plant LNK  " 
   cd $DIR/$RDIR && ln -sfn $RDAY $LNK && cd
   [ $? -ne 0 ] && echo $BASH_SOURCE FAILED TO PLANT LNK $LNK && exit 1
   echo "   ] plant LNK  " 

   echo "   [ ls -l $DIR/$RDIR"
   ls -l $DIR/$RDIR
   echo "   ] ls -l $DIR/$RDIR"


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

   vvd $vv

else
   echo $BASH_SOURCE argument naming existing TAR file [$TAR] is required 
   args 
   exit 2
fi 

echo "   [ ls -l $DIR"
ls -l $DIR
echo "   ] ls -l $DIR"


args
echo ] $0 

exit 0

