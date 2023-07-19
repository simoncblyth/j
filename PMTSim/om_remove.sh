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
/usr/local/opticks/lib/libPMTSim.dylib
/usr/local/opticks/lib/pkgconfig/PMTSim.pc
/usr/local/opticks/lib/cmake/pmtsim/properties-pmtsim-targets.cmake
/usr/local/opticks/lib/cmake/pmtsim/pmtsim-targets.cmake
/usr/local/opticks/lib/cmake/pmtsim/pmtsim-targets-debug.cmake
/usr/local/opticks/lib/cmake/pmtsim/pmtsim-config.cmake
/usr/local/opticks/lib/cmake/pmtsim/pmtsim-config-version.cmake
/usr/local/opticks/include/PMTSim/PMTSIM_API_EXPORT.hh
/usr/local/opticks/include/PMTSim/ZSolid.h
/usr/local/opticks/include/PMTSim/MaterialSvc.hh
/usr/local/opticks/include/PMTSim/PMTSim.hh
/usr/local/opticks/include/PMTSim/J_PMTSIM_LOG.hh
/usr/local/opticks/include/PMTSim/DetectorConstruction.hh
/usr/local/opticks/include/PMTSim/Layr.h
/usr/local/opticks/include/PMTSim/JPMT.h
/usr/local/opticks/include/PMTSim/junoPMTOpticalModel.hh
/usr/local/opticks/include/PMTSim/ModelTrigger_Debug.h
/usr/local/opticks/include/PMTSim/PMTSimParamSvc/PMTAccessor.h
/usr/local/opticks/include/PMTSim/PMTSimParamSvc/PMTSimParamData.h
/usr/local/opticks/include/PMTSim/PMTSimParamSvc/_PMTSimParamData.h
/usr/local/opticks/include/PMTSim/PMTSimParamSvc/PmtSimData_LPMT.h
/usr/local/opticks/include/PMTSim/PMTSimParamSvc/PmtSimData_SPMT.h
/usr/local/opticks/include/PMTSim/Geometry/PMT.h
/usr/local/opticks/include/PMTSim/Geometry/PMTCategory.h
/usr/local/opticks/lib/PMTSimTest
/usr/local/opticks/lib/X4SolidTreeTest
/usr/local/opticks/lib/G4UnionSolidOffsetsTest
/usr/local/opticks/lib/HamamatsuR12860PMTManagerTest
/usr/local/opticks/lib/MaterialSvcTest
/usr/local/opticks/lib/DetectorConstructionTest
/usr/local/opticks/lib/PMTSolidTest
/usr/local/opticks/lib/GetSolidTest
/usr/local/opticks/lib/GetValuesTest
/usr/local/opticks/lib/GetSolid_Test
/usr/local/opticks/lib/GetPVTest
EOP
}

dirs(){ cat << EOD
/usr/local/opticks/include/PMTSim
/usr/local/opticks/lib/cmake/pmtsim
EOD
}


for path in $(paths) ; do 
    if [ -f "$path" ]; then 
       echo $BASH_SOURCE : remove path $path 
       rm $path
    else
       echo -n 
       #echo $BASH_SOURCE : path $path does not exist
    fi 
done

for dir in $(dirs) ; do 
   if [ -d "$dir" -a ${#dir} -gt 1 ]; then 
       echo $BASH_SOURCE : dir $dir exists : removing 
       rm -rf "$dir" 
   else
       echo -n 
       #echo $BASH_SOURCE : dir $dir DOES NOT EXIST 
   fi 
done







