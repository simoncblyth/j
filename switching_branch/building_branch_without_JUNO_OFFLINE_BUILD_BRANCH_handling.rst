building_branch_without_JUNO_OFFLINE_BUILD_BRANCH_handling
=============================================================

Branches based from main prior to the JUNO_OFFLINE_BUILD_BRANCH addition of January 7th 2026, need working copy tweaks::

    A[blyth@localhost junosw]$ git diff build.sh
    diff --git a/build.sh b/build.sh
    index efec5ebc..9545eb01 100755
    --- a/build.sh
    +++ b/build.sh
    @@ -204,6 +204,7 @@ function cmake-build-type() {
     }
     
     function run-build() {
    +    local sourcedir=$(dirname $(realpath $BASH_SOURCE))
         local installdir=$(install-dir)
         local blddir=$(build-dir)
         check-build-dir
    @@ -211,7 +212,8 @@ function run-build() {
     
         pushd $blddir
     
    -    cmake .. $(check-var-enabled graphviz) \
    +    cmake $sourcedir \
    +             $(check-var-enabled graphviz) \
                  $(check-var-enabled withoec) \
                  $(check-var-enabled online) \
                  $(check-var-enabled PerformanceCheck) \
    A[blyth@localhost junosw]$ git diff oj_initialize.sh
    diff --git a/oj_initialize.sh b/oj_initialize.sh
    index 738b6981..eb56ebeb 100755
    --- a/oj_initialize.sh
    +++ b/oj_initialize.sh
    @@ -28,9 +28,16 @@ EOU
     }
     
     
    -source InstallArea/envset.sh
    +if [ -n "$JUNO_OFFLINE_BUILD_BRANCH" ]; then
    +    branch=$(git branch --show-current)
    +    envset=InstallArea/$branch/envset.sh
    +else
    +    envset=InstallArea/envset.sh
    +fi
    +
    +source $envset
     
    -vv="BASH_SOURCE PWD OPTICKS_PREFIX JUNO_OFFLINE_OFF JUNO_OFFLINE_VERSION CMAKE_PREFIX_PATH TUTORIALROOT OJ_DEBUG"
    +vv="BASH_SOURCE PWD branch envset OPTICKS_PREFIX JUNO_OFFLINE_OFF JUNO_OFFLINE_VERSION CMAKE_PREFIX_PATH TUTORIALROOT OJ_DEBUG"
     for v in $vv ; do printf "%30s : %s\n " "$v" "${!v}" ; done 
     
     if [ -z "$OJ_DEBUG" ]; then






