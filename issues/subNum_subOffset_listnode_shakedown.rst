subNum_subOffset_listnode_shakedown
=======================================



* observe many crazy subNum values in cg convertPrim following direct from G4 translation (tds3dbg)



* checking earlier at X4PhysicalVolume::ConvertSolid_FromRawNode see

  * subNum looks OK : same as numTreeNodes
  * subOffset are mostly zero, but with some crazies



::


    2022-03-03 00:45:25.530 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1141]  after NTreeProcess:::Process 
    2022-03-03 00:45:25.530 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1150] [ before NCSG::Adopt 
    2022-03-03 00:45:25.559 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1152] ] after NCSG::Adopt 
    2022-03-03 00:45:25.559 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1177] ] 8
    2022-03-03 00:45:25.559 INFO  [268612] [X4PhysicalVolume::ConvertSolid@1023]  lvIdx 8 root.brief nnode::brief subNum    1 subOffset 1104150528 numTreeNodes    1 numSerializationNodes    1 soname sBar
    2022-03-03 00:45:25.559 INFO  [268612] [X4PhysicalVolume::ConvertSolid@1036]  lvIdx 8 soIdx 8 unbalanced_height 0 NCSG::MAX_EXPORT_HEIGHT 16 can_export_unbalanced 1
    2022-03-03 00:45:25.559 INFO  [268612] [X4PhysicalVolume::convertSolid@951]  lvname lCoating soname sBar [--x4skipsolidname] n
    2022-03-03 00:45:25.559 INFO  [268612] [X4PhysicalVolume::ConvertSolid_@1093] [ 9 soname sBar lvname lCoating
    2022-03-03 00:45:25.559 ERROR [268612] [X4Solid::Convert@123]  xs.hasHint 0 xs.desc X4SolidBase identifier a entityType                    5 entityName                G4Box name                                     sBar root 0x2bb547c0
    2022-03-03 00:45:25.559 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1141]  after NTreeProcess:::Process 
    2022-03-03 00:45:25.559 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1150] [ before NCSG::Adopt 
    2022-03-03 00:45:25.587 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1152] ] after NCSG::Adopt 
    2022-03-03 00:45:25.587 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1177] ] 9
    2022-03-03 00:45:25.587 INFO  [268612] [X4PhysicalVolume::ConvertSolid@1023]  lvIdx 9 root.brief nnode::brief subNum    1 subOffset 1104307814 numTreeNodes    1 numSerializationNodes    1 soname sBar
    2022-03-03 00:45:25.587 INFO  [268612] [X4PhysicalVolume::ConvertSolid@1036]  lvIdx 9 soIdx 9 unbalanced_height 0 NCSG::MAX_EXPORT_HEIGHT 16 can_export_unbalanced 1
    2022-03-03 00:45:25.587 INFO  [268612] [X4PhysicalVolume::convertSolid@951]  lvname lPanelTape soname sPanelTape [--x4skipsolidname] n
    2022-03-03 00:45:25.588 INFO  [268612] [X4PhysicalVolume::ConvertSolid_@1093] [ 10 soname sPanelTape lvname lPanelTape
    2022-03-03 00:45:25.588 ERROR [268612] [X4Solid::Convert@123]  xs.hasHint 0 xs.desc X4SolidBase identifier a entityType                    5 entityName                G4Box name                               sPanelTape root 0x2bcf4fb0
    2022-03-03 00:45:25.588 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1141]  after NTreeProcess:::Process 
    2022-03-03 00:45:25.588 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1150] [ before NCSG::Adopt 
    2022-03-03 00:45:25.615 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1152] ] after NCSG::Adopt 



    2022-03-03 00:45:26.250 INFO  [268612] [X4Solid::convertPolycone@1753]  R_inner_min      0.0000 R_inner_max      0.0000 num_R_inner 1 has_inner 0
    2022-03-03 00:45:26.250 INFO  [268612] [X4Solid::convertPolycone@1759]  R_outer_min  24750.0000 R_outer_max  24750.0000 num_R_outer 1
    2022-03-03 00:45:26.250 ERROR [268612] [X4Solid::Convert@123]  xs.hasHint 0 xs.desc X4SolidBase identifier a entityType                   15 entityName           G4Polycone name                              sBottomRock root 0x2ce93db0
    2022-03-03 00:45:26.250 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1141]  after NTreeProcess:::Process 
    2022-03-03 00:45:26.250 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1150] [ before NCSG::Adopt 
    2022-03-03 00:45:26.250 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1152] ] after NCSG::Adopt 
    2022-03-03 00:45:26.250 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1177] ] 137
    2022-03-03 00:45:26.250 INFO  [268612] [X4PhysicalVolume::ConvertSolid@1023]  lvIdx 137 root.brief nnode::brief subNum    1 subOffset    0 numTreeNodes    1 numSerializationNodes    1 soname sBottomRock
    2022-03-03 00:45:26.250 INFO  [268612] [X4PhysicalVolume::ConvertSolid@1036]  lvIdx 137 soIdx 137 unbalanced_height 0 NCSG::MAX_EXPORT_HEIGHT 16 can_export_unbalanced 1
    2022-03-03 00:45:26.250 INFO  [268612] [X4PhysicalVolume::convertSolid@951]  lvname lWorld soname sWorld [--x4skipsolidname] n
    2022-03-03 00:45:26.250 INFO  [268612] [X4PhysicalVolume::ConvertSolid_@1093] [ 138 soname sWorld lvname lWorld
    2022-03-03 00:45:26.250 ERROR [268612] [X4Solid::Convert@123]  xs.hasHint 0 xs.desc X4SolidBase identifier a entityType                    5 entityName                G4Box name                                   sWorld root 0x2ce9dab0
    2022-03-03 00:45:26.250 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1141]  after NTreeProcess:::Process 
    2022-03-03 00:45:26.251 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1150] [ before NCSG::Adopt 
    2022-03-03 00:45:26.280 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1152] ] after NCSG::Adopt 
    2022-03-03 00:45:26.280 INFO  [268612] [X4PhysicalVolume::ConvertSolid_FromRawNode@1177] ] 138
    2022-03-03 00:45:26.280 INFO  [268612] [X4PhysicalVolume::ConvertSolid@1023]  lvIdx 138 root.brief nnode::brief subNum    1 subOffset 1206542336 numTreeNodes    1 numSerializationNodes    1 soname sWorld
    2022-03-03 00:45:26.280 INFO  [268612] [X4PhysicalVolume::ConvertSolid@1036]  lvIdx 138 soIdx 138 unbalanced_height 0 NCSG::MAX_EXPORT_HEIGHT 16 can_export_unbalanced 1
    2022-03-03 00:45:26.280 INFO  [268612] [X4PhysicalVolume::dumpLV@1215]  m_lvidx.size() 139 m_lvlist.size() 139 edgeitems 100
     i     0 idx     0 lvname                                           lDomeAir soname                                   sTopRock_domeAir
     i     1 idx     1 lvname                                          lDomeRock soname                                      sTopRock_dome
     i     2 idx     2 lvname                                       lDomeRockBox soname                                       sDomeRockBox
     i     3 idx     3 lvname                                         lPoolCover soname                                       PoolCoversub
     i     4 idx     4 lvname                                    lUpperChimneyLS soname                                      Upper_LS_tube
     i     5 idx     5 lvname                                 lUpperChimneySteel soname                                   Upper_Steel_tube
     i     6 idx     6 lvname                                 lUpperChimneyTyvek soname                                   Upper_Tyvek_tube






subNum/subOffset stomping for leaf nodes that are also root nodes of a single element tree 
-----------------------------------------------------------------------------------------------

HMM the subNum/subOffset using param.u.x and param.u.y is fine for the root node of trees with numNodes 3,7,15,... etc 
which will always be one of CSG_UNION/CSG_INTERSECTION/CSG_DIFFERENCE but it is not OK for single node "trees"
as those slots are in use.

Add some asserts to enforce this. Making sure that all usage checks type before setting or getting subNum/subOffset 

::


     160 /**
     161 nnode::subNum
     162 ---------------
     163 
     164 Fields used for subNum and subOffset here need match those used in CSG/CSGNode.h 
     165 
     166 **/
     167 
     168 unsigned nnode::subNum() const
     169 {
     170     return param.u.x ;
     171 }
     172 void nnode::setSubNum(unsigned num)
     173 {
     174     param.u.x = num ;
     175 }
     176 
     177 unsigned nnode::subOffset() const
     178 {
     179     return param.u.y ;
     180 }
     181 void nnode::setSubOffset(unsigned num)
     182 {
     183     param.u.y = num ;
     184 }
     185 





Hmm it gets more involved : after avoiding mis-reads are always getting zero for subNum/subOffset
------------------------------------------------------------------------------------------------------


The GParts m_part_buffer if constructed in GGeo::deferredCreateGParts from GPts instances.


::

    027 /**
     28 GPt
     29 =====
     30 
     31 GPt captures node placement of a solid within the 
     32 full geometry tree in a minimal way, holding only:
     33     
     34 placement
     35    global transform 
     36 lvIdx, csgIdx
     37    indices referencing the solid shape
     38 ndIdx
     39    index of the node in the full tree 
     40 spec
     41    string representing the boundary of this node in the tree
     42    (material and surface  omat/osur/isur/imat) 
     43     
     44 GPt are canonically instanciated in X4PhysicalVolume::convertNode
     45 where instances are associated with the GVolume of the 
     46 structural tree.
     47 
     48 vectors of GPt instances are collected into GPts m_pts within GMergedMesh.
     49 The GPts are persisted into the geocache which allows GParts creation 
     50 to be deferred postcache. 
     51 
     52 **/ 
     53 
     54 struct GGEO_API GPt 
     55 {
     56     static const char* DEFAULT_SPEC ;
     57 
     58     int         lvIdx ;
     59     int         ndIdx ;
     60     int         csgIdx ;
     61     std::string spec ;
     62     glm::mat4   placement ;
     63 
     64     GPt( int lvIdx_, int ndIdx_, int csgIdx_, const char* spec_, const glm::mat4& placement_ );
     65     GPt( int lvIdx_, int ndIdx_, int csgIdx_, const char* spec_ );
     66 
     67     const std::string& getSpec() const ;
     68     const glm::mat4&   getPlacement() const ;
     69     void setPlacement( const glm::mat4& placement_ );
     70     std::string desc() const ;
     71 
     72 };



     69 class GGEO_API GPts {
     70     public:
     71         static const plog::Severity LEVEL ;
     72         static GPts* Make();
     73         static GPts* Load(const char* path);
     74         static const char* GPTS_LIST ;
     75     private:
     76         template<typename T> static NPY<T>* LoadBuffer(const char* dir, const char* tag);
     77         static const char* BufferName(const char* tag) ;
     78     public:
     79         GPts(NPY<int>* pts, NPY<float>* plc, GItemList* specs);
     80         void export_();
     81         void import();
     82     public:
     83         unsigned     getNumPt() const ;
     84         const GPt*   getPt(unsigned i) const ;
     85         void         add(GPt* pt);
     86         void         dump(const char* msg="GPts::dump") const ;
     87         void         save(const char* path);
     88         std::string  brief() const ;
     89     private:
     90         std::vector<GPt*>  m_pts ;
     91     private:
     92         NPY<int>*          m_ipt_buffer ;
     93         NPY<float>*        m_plc_buffer ;  // placement transforms 
     94         GItemList*         m_specs ;       // boundary specs 
     95 
    096 };



    111 void GPts::export_() // to the buffer
    112 {   
    113     for(unsigned i=0 ; i < getNumPt() ; i++ )
    114     {   
    115         const GPt* pt = getPt(i); 
    116         glm::ivec4 ipt(pt->lvIdx, pt->ndIdx, pt->csgIdx, i);
    117         
    118         m_specs->add(pt->spec.c_str());
    119         m_ipt_buffer->add(ipt); 
    120         m_plc_buffer->add(pt->placement) ;
    121     }
    122 }



::

    1432 void GGeo::deferredCreateGParts()
    1433 {
    1434     LOG(LEVEL) << "[" ;
    1435 
    1436     const std::vector<const NCSG*>& solids = m_meshlib->getSolids();
    1437 
    1438     unsigned nmm = m_geolib->getNumMergedMesh();
    1439 
    1440     int gparts_debug = SSys::getenvint("GPARTS_DEBUG", ~0u );
    1441 
    1442     LOG(LEVEL)
    1443         << " geolib.nmm " << nmm
    1444         << " meshlib.solids " << solids.size()
    1445         << " gparts_debug " << gparts_debug
    1446         ;
    1447 
    1448     for(unsigned i=0 ; i < nmm ; i++)
    1449     {
    1450         GMergedMesh* mm = m_geolib->getMergedMesh(i);
    1451 
    1452         if( mm->getParts() != NULL )
    1453         {
    1454             LOG(LEVEL) << " skip as parts already present for mm " << i ;
    1455             // this happens for test geometry eg tboolean.sh 
    1456             continue ;
    1457         }
    1458 
    1459         assert( mm->getParts() == NULL );
    1460 
    1461         GPts* pts = mm->getPts();
    1462         if( pts == NULL )
    1463         {
    1464             LOG(fatal) << " pts NULL, cannot create GParts for mm " << i ;
    1465             //continue ; 
    1466             assert(0);
    1467         }
    1468 
    1469         LOG(LEVEL) << "[ GParts::Create i/nmm " << i << "/" << nmm ;
    1470         unsigned num_mismatch_pt = 0 ;
    1471         std::vector<glm::mat4> mismatch_placements ;
    1472 
    1473 
    1474         GParts::SetDEBUG( i == unsigned(gparts_debug) ? 1 : 0 );
    1475         GParts* parts = GParts::Create( m_ok, pts, solids, &num_mismatch_pt, &mismatch_placements ) ;
    1476         parts->setRepeatIndex(i);
    1477 
    1478         if(num_mismatch_pt > 0 )


::

     715 /**
     716 NCSG::import_tree_operator
     717 ---------------------------
     718 
     719 TODO: Notice that only the typecode is used, no parameters
     720 are loaded from the buffer... but they need to be 
     721 for subNum/subOffset 
     722 
     723 **/
     724 
     725 nnode* NCSG::import_tree_operator( unsigned idx, OpticksCSG_t typecode )
     726 {   
     727     if(m_verbosity > 2)
     728     {
     729     LOG(info) << "NCSG::import_operator "
     730               << " idx " << idx  
     731               << " typecode " << typecode 
     732               << " csgname " << CSG::Name(typecode)
     733               ;
     734     }
     735     
     736     nnode* node = NULL ;
     737     switch(typecode)
     738     {  
     739        case CSG_UNION:        node = nunion::make_union(NULL, NULL ) ; break ; 
     740        case CSG_INTERSECTION: node = nintersection::make_intersection(NULL, NULL ) ; break ;
     741        case CSG_DIFFERENCE:   node = ndifference::make_difference(NULL, NULL )   ; break ;
     742        default:               node = NULL                                 ; break ;
     743     }
     744     assert(node);
     745     return node ; 
     746 }

