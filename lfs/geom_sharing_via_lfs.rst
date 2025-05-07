geom_sharing_via_lfs
=======================


Geometry folder has three file types : .gdml .npy .txt
---------------------------------------------------------

::

    A[blyth@localhost J_2025_mar24]$ find . -type f | wc -l 
    25618
    A[blyth@localhost J_2025_mar24]$ find . -type f | grep .gdml 
    ./origin.gdml
    ./origin_raw.gdml
    A[blyth@localhost J_2025_mar24]$ find . -type f | grep .txt | wc -l 
    12600
    A[blyth@localhost J_2025_mar24]$ find . -type f | grep .npy | wc -l 
    13016
    A[blyth@localhost J_2025_mar24]$ echo $(( 12600 + 13016 + 2 ))
    25618
    A[blyth@localhost J_2025_mar24]$ 



Look for ways to slim the geometry folder
--------------------------------------------

::

    A[blyth@localhost J_2025_mar24]$ du -hs *
    488M    CSGFoundry
    20M origin.gdml
    4.0K    origin_gdxml_report.txt
    20M origin_raw.gdml


    A[blyth@localhost CSGFoundry]$ du -hs *
    3.0M    inst.npy
    520K    itra.npy
    8.0K    meshname.txt
    4.0K    meta.txt
    4.0K    mmlabel.txt
    1.5M    node.npy
    84K primname.txt
    216K    prim.npy
    4.0K    solid.npy
    482M    SSim
    520K    tran.npy
    A[blyth@localhost CSGFoundry]$ 



    A[blyth@localhost SSim]$ du -hs * 
    11M extra
    4.0K    NPFold_index.txt
    0   NPFold_names.txt
    130M    scene
    341M    stree



    A[blyth@localhost stree]$ du -hs *
    69M mesh
    67M standard
    47M m2w.npy
    47M w2m.npy
    47M gtd.npy
    22M nds.npy
    13M digs_names.txt
    13M subs_names.txt
    5.9M    inst.npy
    5.9M    iinst.npy
    3.0M    inst_f4.npy
    3.0M    iinst_f4.npy
    1.5M    surface
    188K    _csg
    4.0K    digs.npy
    4.0K    factor.npy
    4.0K    force_triangulate_lvid.npy
    8.0K    implicit_names.txt
    4.0K    implicit.npy
    4.0K    inst_info.npy
    188K    inst_nidx.npy
    352K    material
    4.0K    mtindex.npy
    4.0K    mtindex_to_mtline.npy
    4.0K    mtline.npy
    4.0K    mtname_names.txt
    4.0K    mtname_no_rindex_names.txt
    4.0K    mtname_no_rindex.npy
    4.0K    mtname.npy
    4.0K    NPFold_index.txt
    0   NPFold_names.txt
    172K    rem.npy
    180K    sensor_id.npy
    4.0K    sensor_name_names.txt
    4.0K    sensor_name.npy
    8.0K    soname_names.txt
    4.0K    soname.npy
    20K subs_freq
    4.0K    subs.npy
    12K suname_names.txt
    4.0K    suname.npy
    20K tri.npy
    A[blyth@localhost stree]$ 


    A[blyth@localhost mesh]$ du -hs *
    40K base_steel
    28K GLb1.bt02_FlangeI_Web_FlangeII
    28K GLb1.bt05_FlangeI_Web_FlangeII
    28K GLb1.bt06_FlangeI_Web_FlangeII
    28K GLb1.bt07_FlangeI_Web_FlangeII
    28K GLb1.bt08_FlangeI_Web_FlangeII
    28K GLb1.up01_FlangeI_Web_FlangeII
    28K GLb1.up02_FlangeI_Web_FlangeII
    ...


    A[blyth@localhost standard]$ du -hs *
    16K bd_names.txt
    8.0K    bd.npy
    4.0K    bnd_meta.txt
    16K bnd_names.txt
    56M bnd.npy
    8.0K    energy.npy
    4.0K    icdf_meta.txt
    4.0K    icdf_names.txt
    100K    icdf.npy
    4.0K    mat_meta.txt
    4.0K    mat_names.txt
    1.1M    mat.npy
    4.0K    NPFold_index.txt
    0   NPFold_names.txt
    20K optical.npy
    4.0K    rayleigh_meta.txt
    4.0K    rayleigh_names.txt
    28K rayleigh.npy
    12K sur_names.txt
    10M sur.npy
    8.0K    wavelength.npy
    A[blyth@localhost standard]$ 

