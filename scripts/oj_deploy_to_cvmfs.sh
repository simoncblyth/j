#!/bin/bash

usage(){ cat << EOU
oj_deploy_to_cvmfs.sh
=========================

CAUTION : THIS SCRIPT IS INVOKED OVER SSH FROM GITLAB-CI RUNNER 

Usage example::

    A> ssh O   ## stratum-zero 
    O> ./oj_deploy_to_cvmfs.sh incoming/J25.2.3_Opticks-v0.3.3.tar

    O> DRYRUN=1 ./oj_deploy_to_cvmfs.sh    ## DRYRUN check with last tarball


Note the link planting with "ln -sfn" the "-n:--no-dereference"
option does forcible updating of directory symbolic links.

Issue::

        WARNING! There are open read-only file descriptors in /cvmfs/opticks.ihep.ac.cn

	CernVM-FS transaction error: another transaction is already open


WIP : Automated dated reference deployment for the first OJ release for each Opticks release
----------------------------------------------------------------------------------------------

HMM : PROBLEM WITH THIS IS THAT THE RELEASE COULD BE FROM A BRANCH ?
NEED WAY TO DETECT THAT A RELEASE IS A BRANCH BUILD

Could delect the first OJ install following an Opticks release by
the emptyness of the directory, and switch to dated folder in that case::

    [optickspub@cvmfs-stratum-zero-b ~]$ l /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.4/el9_amd64_gcc11/
    total 3
    1 drwxrwxr-x 3 optickspub optickspub  43 Sep 30 12:18 .
    1 lrwxrwxrwx 1 optickspub optickspub   3 Sep 30 12:18 Latest -> Tue
    1 drwxr-xr-x 7 optickspub optickspub 181 Sep 30 12:11 Tue
    1 -rw-r--r-- 1 optickspub optickspub   0 Sep 30 10:12 .cvmfscatalog
    1 drwxrwxr-x 3 optickspub optickspub  37 Sep 30 10:12 ..
    [optickspub@cvmfs-stratum-zero-b ~]$ 



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



tarball_from_scheduled_build() 
{
    # rc 0: tarball is from a scheduled build
    # rc 1: tarpath does not exist
    # rc 2: ENV.bash not found in tarball
    # rc 3: merge_request_event detected
    #
    #
    # * get *envrelp* relative path of ENV.bash within the tarball
    # * by extracting the ENV.bash from tarball to stdout populate *ci_settings* variable
    # * determine if the tarball was created from a CI build that was due to a merge request
    #   OR was due to a scheduled build

    local tarpath=$1

    if [ ! -f "$tarpath" ]; then
        printf "%s: RC:1 NO SUCH FILE tarpath[%s]\n" "$FUNCNAME" "$tarpath"
        return 1
    fi  
    
    local envrelp=$(tar -tf "$tarpath" 2>/dev/null | grep ENV.bash)
    if [ $? -ne 0 ] || [ -z "$envrelp" ]; then
        printf "%s: RC:2 No ENV.bash file found in tarball [%s]\n" "$FUNCNAME" "$tarpath"
        return 2
    fi  
    
    # Extract CI settings from ENV.bash to a temporary variable
    local ci_settings=$(tar -xf "$tarpath" -O "$envrelp" 2>/dev/null | grep '^export CI_')

    printf "%s: ci_settings\n%s\n" "$FUNCNAME" "$ci_settings"

    if [ $? -ne 0 ]; then
        printf "%s: RC:2 Failed to extract ENV.bash from tarball [%s]\n" "$FUNCNAME" "$tarpath"
        return 2
    fi

    # Check if the tarball is from a merge request
    local merge_branch
    if echo "$ci_settings" | grep -q "CI_PIPELINE_SOURCE=merge_request_event"; then
        printf "%s: RC:3 Detected merge request tarball based on CI settings:\n%s\n" "$FUNCNAME" "$ci_settings"
        return 3
    fi  

    # Check for non-empty CI_MERGE_REQUEST_SOURCE_BRANCH_NAME
    merge_branch=$(echo "$ci_settings" | grep 'CI_MERGE_REQUEST_SOURCE_BRANCH_NAME' | cut -d'=' -f2- | tr -d '"' | tr -d "'")
    if [ -n "$merge_branch" ]; then
        printf "%s: RC:3 Detected merge request tarball with source branch [%s]:\n%s\n" "$FUNCNAME" "$merge_branch" "$ci_settings"
        return 3
    fi

    printf "%s: RC:0 Tarball is from a reference release\n" "$FUNCNAME"
    return 0
}


is_first_scheduled_build_for_this_release()
{
    # rc 0: detect that this tarball is the first of this OJ release
    # rc 1: detect that this tarball is not the first of this OJ release

    local tarpath=$1
    local tarname=$(basename $tarpath)
    local tarstem=${tarname/.tar}
    local ojreldir=/cvmfs/opticks.ihep.ac.cn/oj/releases/$tarstem/el9_amd64_gcc11

    if [ -d "$ojreldir" ]; then
         printf "%s: RC:1 ojreldir[%s] EXISTS - SO NOT first build for release\n" "$FUNCNAME" "$ojreldir"
         return 1  
    fi 
    printf "%s: RC:0 ojreldir[%s] DIR DOES NOT EXIST - SO first build for release\n" "$FUNCNAME" "$ojreldir"
    return 0
}




TAR=$1

if [ -z "$TAR" ]; then
    TAR=$(ls -1t incoming/*.tar | head -1)
    if [ -z "$TAR" ]; then
        printf "%s: No tarballs found in incoming/ folder\n" "$BASH_SOURCE"
        exit 1
    fi
fi 


if ! tarball_from_scheduled_build "$TAR"; then
    printf "%s: tarball NOT from scheduled build, exiting\n" "$BASH_SOURCE"
    exit 1
fi

if ! is_first_scheduled_build_for_this_release "$TAR"; then
   printf "%s - not first build of release - below should do day release\n" "$BASH_SOURCE"
else
   printf "%s - first build for release - below should do dated reference release\n" "$BASH_SOURCE"
fi




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

   ETIM=$(stat --format=%Y $TAR)       ## modification time in seconds since epoch
   DATE=$(date -d @$ETIM +%Y_%m_%d)    ## formatted date eg 2025_04_13

   REF=0
   if [ ! -d "$DIR/$RDIR" ]; then
        echo $BASH_SOURCE - FIRST OJ DEPLOY OF AN OPTICKS RELEASE DETECTED - REF $REF
        REF=1
   fi 


   vv="0 TAR RELP0 RELP RDIR RDAY CVMFS DIR ETIM DATE REF"
   vvd $vv

 
   if [ -z "$DRYRUN" ]; then 


       if [ "$CVMFS" == "1" ]; then
           echo "   [ cvmfs_server transaction $DOM"
           cvmfs_server transaction $DOM   ## start transation to make it writable
           [ $? -ne 0 ] && echo $BASH_SOURCE ERROR - ABORT && exit 1
           echo "   ] cvmfs_server transaction $DOM"
       fi 

       echo "   [ extract TAR into DIR " 
       mkdir -p $DIR 

       MESSAGE="$BASH_SOURCE $TAR"
       if [ "$REF" == "1" ]; then     ## SET TO "10" TO PREVENT THIS FROM HAPPENING  
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
       echo "   ] plant LNK to LEL " 

       echo "   [ ls -l $DIR/$RDIR"
       ls -l $DIR/$RDIR
       echo "   ] ls -l $DIR/$RDIR"


       if [ "$CVMFS" == "1" ]; then

          echo "   [ cvmfs_server publish -m \"$MESSAGE\" $DOM  "
          cvmfs_server publish -m "$MESSAGE" $DOM 

          [ $? -ne 0 ] && echo $BASH_SOURCE ERROR - ABORT && exit 2
          echo "   ] cvmfs_server publish -m \"$BASH_SOURCE $TAR $RELP \" $DOM  "

          echo "   [ cvmfs_server tag $DOM"
          cvmfs_server tag $DOM
          date
          echo "   ] cvmfs_server tag $DOM"
       fi

       vvd $vv

    else
        echo $BASH_SOURCE DRYRUN - NOT DOING ANYTHING MUCH  
    fi 

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

