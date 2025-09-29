why_no_stree_desc_dir/index
==============================


::

    A[blyth@localhost junosw]$ t oj_initialize_meshname_tessname
    oj_initialize_meshname_tessname () 
    { 
        : opticks_juno.sh;
        if [ -n "$OJ_VERBOSE" ]; then
            type $FUNCNAME;
        fi;
        echo [ $FUNCNAME;
        export G4CXOpticks__SaveGeometry_DIR=${OJ_GEOMDIR};
        export CSGFoundry__SAVE_OPT=meshname;
        tut_detsim.py --opticks-mode 1 --evtmax 0 gun;
        unset CSGFoundry__SAVE_OPT;
        local meshname=${OJ_GEOMDIR}/CSGFoundry/meshname.txt;
        if [ -f "$meshname" ]; then
            echo $FUNCNAME - created meshname $meshname;
            ls --color=auto -alst $meshname;
        else
            echo $FUNCNAME - FAILED TO CREATE meshname $meshname;
        fi;
        if [ -f "$meshname" -a -n "${stree__force_triangulate_solid}" ]; then
            local tessname=${stree__force_triangulate_solid/filepath:};
            cat $meshname | oj_tessname_from_meshname > $tessname;
            wc -l $meshname $tessname;
        else
            echo $FUNCNAME - MISSING meshname $meshname OR stree__force_triangulate_solid;
        fi;
        echo ] $FUNCNAME;
        return 0
    }


::

    586 void G4CXOpticks::SaveGeometry() // static
    587 {
    588     LOG_IF(error, INSTANCE==nullptr) << " INSTANCE nullptr : NOTHING TO SAVE " ;
    589     if(INSTANCE == nullptr) return ;
    590 
    591     const char* dir = ssys::getenvvar(SaveGeometry_KEY) ;
    592     LOG_IF(LEVEL, dir == nullptr ) << " not saving as envvar not set " << SaveGeometry_KEY  ;
    593     if(dir == nullptr) return ;
    594     LOG(info) << " save to dir " << dir << " configured via envvar " << SaveGeometry_KEY ;
    595     INSTANCE->saveGeometry(dir);
    596 }


    538 void G4CXOpticks::saveGeometry() const
    539 {
    540     const char* dir = SEventConfig::OutFold() ;
    541     LOG(LEVEL)  << "dir [" << ( dir ? dir : "-" )  ;
    542     saveGeometry(dir) ;
    543 }
    544 
    545 
    546 
    547 void G4CXOpticks::saveGeometry(const char* dir_) const
    548 {
    549     LOG(LEVEL) << " dir_ " << dir_ ;
    550     const char* dir = spath::Resolve(dir_);
    551     LOG(LEVEL) << "[ " << ( dir ? dir : "-" ) ;
    552     LOG(info)  << "[ " << ( dir ? dir : "-" ) ;
    553     std::cout << "G4CXOpticks::saveGeometry [ " << ( dir ? dir : "-" ) << std::endl ;
    554 
    555     if(wd) U4GDML::Write(wd, dir, "origin.gdml" );  // world
    556     if(fd) fd->save(dir) ;
    557 
    558     LOG(LEVEL) << "] " << ( dir ? dir : "-" ) ;
    559 }
    560 



    2664 void CSGFoundry::save_(const char* dir_) const
    2665 {
    2666     const char* dir = SPath::Resolve(dir_, DIRPATH);
    2667     LOG(LEVEL) << dir ;
    2668 
    2669     if(meshname.size() > 0 && save__("meshname")) NP::WriteNames( dir, "meshname.txt", meshname );
    2670 
    2671     std::vector<std::string> primname ;
    2672     getPrimName(primname);
    2673     if(primname.size() > 0 && save__("primname")) NP::WriteNames( dir, "primname.txt", primname );
    2674 
    2675     if(mmlabel.size() > 0 && save__("mmlabel"))  NP::WriteNames( dir, "mmlabel.txt", mmlabel );
    2676     if(hasMeta() && save__("meta"))  U::WriteString( dir, "meta.txt", meta.c_str() );
    2677 
    2678     if(solid.size() > 0 && save__("solid")) NP::Write(dir, "solid.npy",  (int*)solid.data(),  solid.size(), 3, 4 );
    2679     if(prim.size() > 0 && save__("prim"))  NP::Write(dir, "prim.npy",   (float*)prim.data(), prim.size(),   4, 4 );
    2680     if(node.size() > 0 && save__("node"))  NP::Write(dir, "node.npy",   (float*)node.data(), node.size(),   4, 4 );
    2681     if(plan.size() > 0 && save__("plan")) NP::Write(dir, "plan.npy",   (float*)plan.data(), plan.size(),   1, 4 );
    2682     if(tran.size() > 0 && save__("tran")) NP::Write(dir, "tran.npy",   (float*)tran.data(), tran.size(),   4, 4 );
    2683     if(itra.size() > 0 && save__("itra")) NP::Write(dir, "itra.npy",   (float*)itra.data(), itra.size(),   4, 4 );
    2684     if(inst.size() > 0 && save__("inst")) NP::Write(dir, "inst.npy",   (float*)inst.data(), inst.size(),   4, 4 );
    2685 
    2686 
    2687     if(sim && save__("SSim"))
    2688     {
    2689         LOG(LEVEL) << " SSim::save " << dir ;
    2690         const_cast<SSim*>(sim)->save(dir, SSim::RELDIR );
    2691     }
    2692     else
    2693     {
    2694         LOG(LEVEL) << " CANNOT SSim::save AS sim null " ;
    2695     }
    2696 }
    2697 
    2698 
    2699 bool CSGFoundry::save__(const char* elem) const
    2700 {
    2701     return save_opt == nullptr ? true : ( strstr(save_opt, elem) != nullptr ) ;
    2702 }


    0429 void SSim::save(const char* base, const char* reldir)
     430 {
     431     if(top == nullptr) serialize() ;
     432     LOG_IF(fatal, top == nullptr) << " top null : MUST serialize before save, serialize failed ? " ;
     433     assert( top != nullptr ) ;
     434 
     435     const char* dir = spath::Resolve(base, reldir) ;
     436     top->save(dir);
     437 }


That explains it stree::save is not called, instead stree:serialize is called and
the NPFold added to top::

     498 void SSim::serialize()
     499 {
     500     bool has_top = hasTop();
     501 
     502     LOG(LEVEL) << "[" ;
     503     LOG_IF(fatal, has_top )  << " has_top : cannot serialize twice : DONT SERIALIZE AFTER LOADING SSim " ;
     504     assert( !has_top );
     505 
     506     top = new NPFold ;
     507     NPFold* f_tree = tree->serialize() ;
     508     top->add_subfold( stree::RELDIR, f_tree );
     509 
     510     NPFold* f_scene = scene->serialize() ;
     511     top->add_subfold( SScene::RELDIR, f_scene );
     512 
     513     if( extra )
     514     {
     515         top->add_subfold( EXTRA, extra );
     516     }
     517 
     518     LOG(LEVEL) << "]" ;
     519 }


Need to land desc fold inside SSim/stree::

    (ok) A[blyth@localhost stree]$ pwd
    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/stree




