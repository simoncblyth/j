#!/bin/bash

usage(){ cat << EOU
peek.sh : THIS WAS USED TO DEVELOP SOME MACHINERY USED IN oj_deploy_to_cvmfs.sh
=================================================================================

0. get *tarpath* from argument, or if none provided from the last tarball in incoming folder


To find the last scheduled pipeline log click on the last pipeline at::

   https://code.ihep.ac.cn/JUNO/offline/junosw/-/pipeline_schedules
   https://code.ihep.ac.cn/JUNO/offline/junosw/-/pipelines/23065

Gitlab scheduled daily runner start time is 17:00 in Asia/shanghai, full log::

   https://code.ihep.ac.cn/JUNO/offline/junosw/-/jobs/86906/viewer

From the full log the opticks build+run started 17:03 (asia/shanghai)::

   export CI_JOB_STARTED_AT="2025-10-23T09:03:30Z"
   
So it just missed the Opticks v0.5.5 release that landed on cvmfs 4 mins later::

    A[blyth@localhost junosw]$ l  /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
    1 lrwxrwxrwx. 1 cvmfs cvmfs 14 Oct 23 17:07 /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest -> Opticks-v0.5.5


EOU
}


tarpath=$1
if [ -z "$tarpath" ]; then
    tarpath=$(ls -1t incoming/*.tar | head -1)
    if [ -z "$tarpath" ]; then
        printf "%s: No tarballs found in incoming/ folder\n" "$BASH_SOURCE"
        exit 1
    fi
fi 

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



if ! tarball_from_scheduled_build "$tarpath"; then
    printf "%s: tarball NOT from scheduled build, exiting\n" "$BASH_SOURCE"
    exit 1
fi

if ! is_first_scheduled_build_for_this_release "$tarpath"; then
   printf "%s - not first build of release - do day release\n" "$BASH_SOURCE"
else
   printf "%s - first build for release - do dated reference release\n" "$BASH_SOURCE"
fi


