#!/bin/bash
usage(){ cat << EOU
opticks_juno.sh
================

This script provides bash functions doing setup of more
general applicability than the setup placed in::

    .gitlab-ci.yml
    .gitlab-ci/oj_helper.sh

Usage::

    source InstallArea/bin/opticks_juno.sh
    oj_geomsetup


EOU
}


oj_geomsetup()
{
   : opticks_juno.sh
   : extra env settings needed by Opticks-JUNOSW geometry conversion
   : NB this is sourced from envset.sh so needs to be appropriate to every usage
   : not just the .gitlab-ci.yml one off first runs

   if [ -n "$OJ_VERBOSE" ]; then type $FUNCNAME ; fi

   export GEOM=$OJ_SLUG
   export OJ_PREFIX=$(dirname $(dirname $(realpath $BASH_SOURCE))) # one above bin dir
   export OJ_GEOMDIR=$OJ_PREFIX/.opticks/GEOM/${GEOM}

   export ${GEOM}_CFBaseFromGEOM=${OJ_GEOMDIR}  ## for viz, eg CSGOptiXRenderInteractiveTest
   export CSGOptiXRenderInteractiveTest__FRAME_HOP=1

   export stree__force_triangulate_solid="filepath:${OJ_GEOMDIR}/CSGFoundry/tessname.txt"
   export SScene__initFromTree_addFrames=${OJ_GEOMDIR}/CSGFoundry/framespec.txt

   local vv="FUNCNAME OJ_SLUG GEOM BASH_SOURCE OJ_PREFIX OJ_GEOMDIR ${GEOM}_CFBaseFromGEOM stree__force_triangulate_solid SScene__initFromTree_addFrames"
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done


   export WaterPoolConstruction__CONFIG=3
   export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10            # default 1.e-3
   export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10  # default 0.05
   export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10       # default 0.05

   unset U4Mesh__NumberOfRotationSteps_DUMP
   export U4Mesh__NumberOfRotationSteps_DUMP=1
   export U4Mesh__NumberOfRotationSteps_entityType_G4Torus=480

   : NumberOfRotationSteps operates at the level of the full torus
   : rather than the small segment of the torus, so quite a large number of rotation
   : steps is needed to prevent the tesselated guidetube from impinging into the acrylic

   return 0
}


oj_tessname_from_meshname_notes(){ cat << EON

Generates tessname file from full meshname by python line-by-line regexp that
commenting solid names to be analytic CSG.::

   cat ~/.opticks/GEOM/J_2025_mar24/CSGFoundry/meshname.txt | oj_tessname_from_meshname > /tmp/tessname.txt

EON
   : opticks_juno.sh
   return 0
}

oj_tessname_from_meshname()
{
   : opticks_juno.sh
   : can only create tessname after meshname exists so needs to be a second run
   local oneline="import sys,re;ptn=re.compile('^(sSurftube|svacSurftube|solidSJ|solidXJ).*');print('\n'.join([('%s' if ptn.match(line) else '#%s') % line.rstrip() for line in sys.stdin.readlines()]))"
   python -c "$oneline" -
   return 0
}

oj_framespec()
{
   : opticks_juno.sh
   : framespec triplets configure visualization viewpoint bookmarks accessed with number keys
   cat << EOF
Hama:0:0                                   #  0
NNVT:0:0                                   #  1
Hama:0:1000                                #  2
NNVT:0:1000                                #  3
sDeadWater:0:-1                            #  4
sChimneyLS:0:-1                            #  5
sChimneyAcrylic:0:-1                       #  6
sChimneySteel:0:-1                         #  7
Upper_Chimney:0:-1                         #  8
sBotChimneySSEnclosureLS_PartI_II_III:0:-1 #  9
sBotChimneySSEnclosure_PartI_II_III:0:-1   # 10
GZ1.A06_07_FlangeI_Web_FlangeII:15:-1      # 11
GZ1.B06_07_FlangeI_Web_FlangeII:15:-1      # 12
solidXJfixture:0:-1                        # 13
solidXJfixture:20:-1                       # 14
solidXJfixture:40:-1                       # 15
solidXJfixture:55:-1                       # 16
solidXJanchor:0:-1                         # 17
solidXJanchor:20:-1                        # 18
solidXJanchor:40:-1                        # 19
solidXJanchor:55:-1                        # 20
solidSJCLSanchor:0:-1                      # 21
solidSJFixture:0:-1                        # 22
solidSJReceiver:0:-1                       # 23
solidSJReceiverFastern:0:-1                # 24
sSurftube_0V1_0:0:-1                       # 25
sSurftube_38V1_0:0:-1                      # 26
sSurftube_38V1_1:0:-1                      # 27
solidXJfixture:27:-1                       # 28 near bottom of CD
Hama:0:1                                   # 29 NB duplicates cause asserts in NPFold::add for the bookmark frames
EOF
   return 0
}


oj_initialize_meshname_tessname()
{
   : opticks_juno.sh
   if [ -n "$OJ_VERBOSE" ]; then type $FUNCNAME ; fi
   echo [ $FUNCNAME

   export G4CXOpticks__SaveGeometry_DIR=${OJ_GEOMDIR}
   export CSGFoundry__SAVE_OPT=meshname
   tut_detsim.py --opticks-mode 1 --evtmax 0 gun
   unset CSGFoundry__SAVE_OPT

   local meshname=${OJ_GEOMDIR}/CSGFoundry/meshname.txt

   if [ -f "$meshname" ]; then
       echo $FUNCNAME - created meshname $meshname
       ls -alst $meshname
   else
       echo $FUNCNAME - FAILED TO CREATE meshname $meshname
   fi

   if [ -f "$meshname" -a -n "${stree__force_triangulate_solid}" ]; then
      local tessname=${stree__force_triangulate_solid/filepath:}
      cat $meshname | oj_tessname_from_meshname > $tessname
      wc -l $meshname $tessname
   else
      echo $FUNCNAME - MISSING meshname $meshname OR stree__force_triangulate_solid
   fi

   echo ] $FUNCNAME
   return 0
}

oj_initialize_framespec()
{
   : opticks_juno.sh
   if [ -n "$OJ_VERBOSE" ]; then type $FUNCNAME ; fi
   echo [ $FUNCNAME
   if [ -n "${SScene__initFromTree_addFrames}" ]; then
       oj_framespec > ${SScene__initFromTree_addFrames}

       echo $FUNCNAME - ls -alst ${SScene__initFromTree_addFrames}
       ls -alst ${SScene__initFromTree_addFrames}
   else
       echo $0 - $FUNCNAME - MISSING SScene__initFromTree_addFrames
   fi

   echo ] $FUNCNAME
   return 0
}

oj_initialize_geomdir()
{
   : opticks_juno.sh
   if [ -n "$OJ_VERBOSE" ]; then type $FUNCNAME ; fi
   echo [ $FUNCNAME

   export G4CXOpticks__SaveGeometry_DIR=${OJ_GEOMDIR}

   tut_detsim.py --opticks-mode 1 --evtmax 0 gun

   echo $FUNCNAME - ls -alst ${OJ_GEOMDIR}/CSGFoundry
   ls -alst ${OJ_GEOMDIR}/CSGFoundry

   echo ] $FUNCNAME
   return 0
}


oj_initialize()
{
   : opticks_juno.sh
   : once only setup
   : NB a bug in the framespec list such as a duplicated key
   : would cause tut_detsim.py to assert so it makes more sense
   : to make any changes to framespec before the two tut_detsim runs

   if [ -n "$OJ_VERBOSE" ]; then type $FUNCNAME ; fi
   echo [ $FUNCNAME

   oj_initialize_framespec

   oj_initialize_meshname_tessname

   oj_initialize_geomdir

   echo ] $FUNCNAME
   return 0
}


