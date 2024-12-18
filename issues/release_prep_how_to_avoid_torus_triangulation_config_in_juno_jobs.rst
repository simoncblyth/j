release_prep_how_to_avoid_torus_triangulation_config_in_juno_jobs
=====================================================================



Currently require user config::

    194    unset U4Mesh__NumberOfRotationSteps_DUMP
    195    export U4Mesh__NumberOfRotationSteps_DUMP=1
    196    export U4Mesh__NumberOfRotationSteps_entityType_G4Torus=480


* Could detect JUNO within Opticks from the names and switch ?



::

    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_svacSurftube_0V1_0] num_entityType 480 num_solidName 0 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_sSurftube_0V1_0] num_entityType 480 num_solidName 0 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_svacSurftube_1V1_0] num_entityType 480 num_solidName 0 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_sSurftube_1V1_0] num_entityType 480 num_solidName 0 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_svacSurftube_2V1_0] num_entityType 480 num_solidName 0 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_sSurftube_2V1_0] num_entityType 480 num_solidName 0 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_svacSurftube_3V1_0] num_entityType 480 num_solidName 0 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_sSurftube_3V1_0] num_entityType 480 num_solidName 0 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_svacSurftube_4V1_0] num_entityType 480 num_solidName 0 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4Torus] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_sSurftube_4V1_0] num_entityType 480 num_solidName 0 num 480

