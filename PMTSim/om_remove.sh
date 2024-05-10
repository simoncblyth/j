#!/bin/bash -l 
usage(){ cat << EOU
om_remove.sh
=============

This script manually removes the files installed by 
using "om" to install PMTSim into OPTICKS_PREFIX. 

Use this manual PMTSim remover when want to test 
building opticks without Custom4 and PMTSim 

This approach is a kludge which is forced by PMTSim 
being installed in a dirty way into OPTICKS_PREFIX.

TODO: get a cleaner PMTSim build to work, for example
trying to follow c4/build.sh 
Currently jps/build.sh runs into problems finding plog.

EOU
}

paths(){ cat << EOP
lib64/libPMTSim_standalone.so
lib64/pkgconfig/PMTSim_standalone.pc
lib64/cmake/pmtsim_standalone/properties-pmtsim_standalone-targets.cmake
lib64/cmake/pmtsim_standalone/pmtsim_standalone-targets.cmake
lib64/cmake/pmtsim_standalone/pmtsim_standalone-targets-debug.cmake
lib64/cmake/pmtsim_standalone/pmtsim_standalone-config.cmake
lib64/cmake/pmtsim_standalone/pmtsim_standalone-config-version.cmake
include/PMTSim_standalone/PMTSIM_API_EXPORT.hh
include/PMTSim_standalone/ZSolid.h
include/PMTSim_standalone/MaterialSvc.hh
include/PMTSim_standalone/PMTSim.hh
include/PMTSim_standalone/J_PMTSIM_LOG.hh
include/PMTSim_standalone/DetectorConstruction.hh
include/PMTSim_standalone/Layr.h
include/PMTSim_standalone/JPMT.h
include/PMTSim_standalone/junoPMTOpticalModel.hh
include/PMTSim_standalone/ModelTrigger_Debug.h
include/PMTSim_standalone/PMTSimParamSvc/PMTAccessor.h
include/PMTSim_standalone/PMTSimParamSvc/PMTSimParamData.h
include/PMTSim_standalone/PMTSimParamSvc/_PMTSimParamData.h
include/PMTSim_standalone/PMTSimParamSvc/PmtSimData_LPMT.h
include/PMTSim_standalone/PMTSimParamSvc/PmtSimData_SPMT.h
include/PMTSim_standalone/Geometry/PMT.h
include/PMTSim_standalone/Geometry/PMTCategory.h
include/PMTSim_standalone/Identifier/CopyNumber.hh
lib/PMTSimTest
lib/X4SolidTreeTest
lib/G4UnionSolidOffsetsTest
lib/HamamatsuR12860PMTManagerTest
lib/MaterialSvcTest
lib/DetectorConstructionTest
lib/PMTSolidTest
lib/GetSolidTest
lib/GetValuesTest
lib/GetSolid_Test
lib/GetPVTest
lib/GetLVTest
lib64/cmake/pmtsim_standalone
include/PMTSim_standalone
EOP
}



cd $OPTICKS_PREFIX
[ $? -ne 0 ] && echo $BASH_SOURCE : FAILED TO cd to OPTICKS_PREFIX $OPTICKS_PREFIX && exit 1
pwd

for path in $(paths) ; do 
    if [ -f "$path" ]; then 
       echo $BASH_SOURCE : remove path $path 
       rm "$path"
    elif [ -d "$path" -a ${#path} -gt 1 ]; then 
       echo $BASH_SOURCE : remove directory $path 
       rm -rf "$path" 
    else
       echo -n 
       #echo $BASH_SOURCE : path $path does not exist
    fi 
done



