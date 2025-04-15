#!/bin/bash

usage(){ cat << EOU
oj_reference_deploy_to_cvmfs.sh
=================================

Usage example::

    A> ssh O   ## stratum-zero 
    O> ./oj_reference_deploy_to_cvmfs.sh incoming/J25.2.3_Opticks-v0.3.3.tar

Once this has been verified can combine with oj_deploy_to_cvmfs.sh 

HMM : HOW TO AVOID POTENTIAL DANGER THAT THE TARBALL IS BEING COPIED IN WHEN THIS IS RUN ? 

EOU
}

REF=1

TAR=$1
NAM=$(basename $TAR)
NAM=${NAM/.tar}

DOM=opticks.ihep.ac.cn
REL=oj/releases


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

   if [ -n "$REF" ]; then
       ETIM=$(stat --format=%Y $TAR)       ## modification time in seconds since epoch
       DATE=$(date -d @$ETIM +%Y_%m_%d)    ## formatted date eg 2025_04_13
       RE=s,^$RELP,$RDIR/$DATE,            ## replacing full prefixing RELP is safer
       echo "   REF ENABLED USING EXTRACTION TRANSFORM $RE "
       #tar tf $TAR --show-transformed --transform="$RE"
       tar xf $TAR --show-transformed --transform="$RE" -C $DIR
       LNK=LastRef
       LEL=$DATE
   else
       tar xf $TAR -C $DIR
       LNK=Latest
       LEL=$RDAY
   fi
   echo "   ] extract TAR into DIR " 

   echo "   [ plant LNK to LEL " 
   cd $DIR/$RDIR && ln -sfn $LEL $LNK && cd
   [ $? -ne 0 ] && echo $BASH_SOURCE FAILED TO PLANT LNK $LNK TO LEL $LEL && exit 1
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

