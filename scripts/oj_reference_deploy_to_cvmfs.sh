#!/bin/bash

usage(){ cat << EOU
oj_reference_deploy_to_cvmfs.sh
=================================

Usage example::

    A> ssh O   ## stratum-zero 
    O> ./oj_reference_deploy_to_cvmfs.sh
    O>   ## enter "YES" if the LAST_TAR detected is the one that needs to be deployed

HMM : HOW TO AVOID POTENTIAL DANGER THAT THE TARBALL IS BEING COPIED IN WHEN THIS IS RUN ? 

Changes
----------

2025 Jun 25 : Added more relevant "commit" MESSAGE : UNTESTED
    


EOU
}

REF=1


LAST_TAR=$(ls -1t incoming/*.tar | head -1)


TAR=$LAST_TAR
LS_TAR=$(ls -alst $TAR)

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
args(){ vvd CVMFS BASE TAR LS_TAR NAM DOM REL DIR LNK ; }

echo [ $0 
args



if [ -f "$TAR" ]; then 

   tar tf $TAR > /dev/null
   [ $? -ne 0 ] && echo $BASH_SOURCE TAR $TAR invalid && exit 1

   RELP0=$(tar tf $TAR | grep ENV.bash)
   RELP=${RELP0/\/ENV.bash/}  # eg J25.2.3_Opticks-v0.3.3/el9_amd64_gcc11/Fri
   RDIR=$(dirname $RELP)      # eg J25.2.3_Opticks-v0.3.3/el9_amd64_gcc11
   RDAY=$(basename $RELP)     # eg Fri
   ETIM=$(stat --format=%Y $TAR)       ## modification time in seconds since epoch
   DATE=$(date -d @$ETIM +%Y_%m_%d)    ## formatted date eg 2025_04_13

   PRED=$DIR/$RDIR/$DATE/envset.sh ## predict the envset.sh path in cvmfs

   CAUTION="avoid deployment when tarball timestamp is too fresh to avoid danger of tarball still arriving via scp"

   vv="0 TAR RELP0 RELP RDIR RDAY CVMFS DIR ETIM DATE PRED CAUTION"
   vvd $vv

   ANS=NO
   printf "\n"
   read -p "$BASH_SOURCE : Enter [YES] to proceed to deploy TAR:$TAR into DIR $DIR : " ANS
   if [ "$ANS" != "YES" ]; then
      echo $BASH_SOURCE : SKIPPING AS ANS[$ANS] IS NOT YES
      exit 0 
   fi 


   if [ "$CVMFS" == "1" ]; then
       echo "   [ cvmfs_server transaction $DOM"
       cvmfs_server transaction $DOM   ## start transation to make it writable
       [ $? -ne 0 ] && echo $BASH_SOURCE ERROR - ABORT && exit 1
       echo "   ] cvmfs_server transaction $DOM"
   fi 

   echo "   [ extract TAR into DIR " 
   mkdir -p $DIR 

   MESSAGE="$BASH_SOURCE $TAR"
   if [ -n "$REF" ]; then
       RE=s,^$RELP,$RDIR/$DATE,            ## replacing full prefixing RELP is safer : change day eg "Fri" into date

       echo "   REF ENABLED USING EXTRACTION TRANSFORM $RE "
       tar xf $TAR --show-transformed --transform="$RE" -C $DIR
       LNK=LastRef
       LEL=$DATE

       MESSAGE="$MESSAGE REF=1 $RDIR/$DATE"
   else
       tar xf $TAR -C $DIR
       LNK=Latest
       LEL=$RDAY
       MESSAGE="$MESSAGE $RELP"
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
      echo "   [ cvmfs_server publish -m \"$MESSAGE\" $DOM  "
      cvmfs_server publish -m "$MESSAGE" $DOM 
      [ $? -ne 0 ] && echo $BASH_SOURCE ERROR - ABORT && exit 2
      echo "   ] cvmfs_server publish -m \"$MESSAGE\" $DOM  "

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

