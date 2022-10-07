offline-opticks-convertMaterials-warnings
============================================


Isolate the GPropertyMap
--------------------------

Looks like almost none of them are suitable for table grouping::

    CMDLINE:/Users/blyth/opticks/ggeo/tests/GPropertyMap_make_table_Test.py
    f.base:/tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/GGeo/GScintillatorLib/LS

      : f.OpticalCONSTANT                                  :               (1, 2) : 3:55:16.733011 
      : f.PPOTIMECONSTANT                                  :               (2, 2) : 3:55:16.551690 
      : f.bisMSBTIMECONSTANT                               :               (2, 2) : 3:55:16.544841 
      : f.NeutronCONSTANT                                  :               (4, 2) : 3:55:16.733407 
      : f.GammaCONSTANT                                    :               (4, 2) : 3:55:16.733748 
      : f.AlphaCONSTANT                                    :               (4, 2) : 3:55:16.735665 
      : f.RAYLEIGH                                         :              (11, 2) : 3:55:16.550867 
      : f.PPOREEMISSIONPROB                                :              (15, 2) : 3:55:16.552482 
      : f.RINDEX                                           :              (18, 2) : 3:55:16.548323 
      : f.GROUPVEL                                         :              (18, 2) : 3:55:16.734160 
      : f.bisMSBREEMISSIONPROB                             :              (23, 2) : 3:55:16.545193 
      : f.REEMISSIONPROB                                   :              (28, 2) : 3:55:16.549931 
      : f.PPOCOMPONENT                                     :             (200, 2) : 3:55:16.553065 

      : f.SLOWCOMPONENT                                    :             (275, 2) : 3:55:16.546837 
      : f.FASTCOMPONENT                                    :             (275, 2) : 3:55:16.734891 
      : f.bisMSBCOMPONENT                                  :             (275, 2) : 3:55:16.545712 
      ## these 3 are all the same

      : f.bisMSBABSLENGTH                                  :             (375, 2) : 3:55:16.546123 
      : f.ABSLENGTH                                        :             (497, 2) : 3:55:16.736174 

      : f.RESOLUTIONSCALE                                  :             (761, 2) : 3:55:16.549046 
      : f.SCINTILLATIONYIELD                               :             (761, 2) : 3:55:16.547890 
      ## these 2 have same domain

      : f.PPOABSLENGTH                                     :             (770, 2) : 3:55:16.553745 


Actually 2 of the props have the same domain, and 3 are all the same::

    In [3]: np.all( f.RESOLUTIONSCALE[:,0] == f.SCINTILLATIONYIELD[:,0] )
    Out[3]: True

    In [4]: np.all( f.bisMSBCOMPONENT == f.SLOWCOMPONENT )
    Out[4]: True





    In [2]: f.NeutronCONSTANT
    Out[2]: 
    array([[0.   , 0.064],
           [0.   , 0.09 ],
           [0.   , 0.232],
           [0.   , 0.614]])

    In [3]: f.NeutronCONSTANT[:,0]
    Out[3]: array([0., 0., 0., 0.])

    In [4]: f.NeutronCONSTANT[:,0]*1e9 
    Out[4]: array([  3378.316,  16270.891,  78970.82 , 275520.417])

    In [5]: f.NeutronCONSTANT[:,1]
    Out[5]: array([0.064, 0.09 , 0.232, 0.614])

    In [6]: f.NeutronCONSTANT[:,1].sum()
    Out[6]: 1.0




::

    epsilon:tests blyth$ ./GPropertyMap_make_table_Test.sh
    2022-10-05 14:01:06.977 INFO  [22013264] [main@18] desc_table numProperties 21 [ 
                    ABSLENGTH    len:  497 range: 0.00296154 : 125372
              NeutronCONSTANT    len:    4 range: 0.064 : 0.614
                     GROUPVEL    len:   18 range: 53.4699 : 285.98
              PPOTIMECONSTANT C  len:    2 constant: 1.6
                       RINDEX    len:   18 range: 1.0483 : 1.793
           bisMSBTIMECONSTANT C  len:    2 constant: 1.4
                SLOWCOMPONENT    len:  275 range: 0 : 1
               REEMISSIONPROB    len:   28 range: 0 : 0.8022
              bisMSBCOMPONENT    len:  275 range: 0 : 1
              bisMSBABSLENGTH    len:  375 range: 27.42 : 1.5e+08
                     RAYLEIGH    len:   11 range: 546.429 : 321429
                FASTCOMPONENT    len:  275 range: 0 : 1
                GammaCONSTANT    len:    4 range: 0.028 : 0.707
         bisMSBREEMISSIONPROB    len:   23 range: 0 : 0.932
                 PPOABSLENGTH    len:  770 range: 0.02 : 1.3029e+07
                 PPOCOMPONENT    len:  200 range: 0 : 0.0187
              RESOLUTIONSCALE C  len:  761 constant: 1
            PPOREEMISSIONPROB    len:   15 range: 0 : 0.93
              OpticalCONSTANT C  len:    1 constant: 1
                AlphaCONSTANT    len:    4 range: 0.0812 : 0.4982
           SCINTILLATIONYIELD C  len:  761 constant: 9846

    epsilon:tests blyth$ 




Warnings are from scintillator properties
--------------------------------------------

commented make_table that is giving lots of warnings from GPropertyLib::descRaw
and add desc_table to see why 

The small length properties are a fractional "misuse" of Geant4 properties
where the domain is not energy/wavelength. This isnt handled in the table making
causing the mismatch domain warnings. 

HOW TO FIX : recognize atypical properties and exclude them 
instead of asserting that all domains match and emitting all the warnings. 


::

    2022-10-05 12:48:18.890 INFO  [21895712] [GPropertyLib::dumpRaw@976] X4PhysicalVolume::collectScintillatorMaterials
    [ nraw 1 component LS
     pmap.desc_table 
    desc_table numProperties 21 [ 
                       RINDEX    len:   18 range: 1.0483 : 1.793
                     GROUPVEL    len:   18 range: 53.4699 : 285.98
                     RAYLEIGH    len:   11 range: 546.429 : 321429
                    ABSLENGTH    len:  497 range: 0.00296154 : 125372
                FASTCOMPONENT    len:  275 range: 0 : 1
                SLOWCOMPONENT    len:  275 range: 0 : 1
               REEMISSIONPROB    len:   28 range: 0 : 0.8022
              OpticalCONSTANT C  len:    1 constant: 1
                GammaCONSTANT    len:    4 range: 0.028 : 0.707
                AlphaCONSTANT    len:    4 range: 0.0812 : 0.4982
              NeutronCONSTANT    len:    4 range: 0.064 : 0.614
                 PPOABSLENGTH    len:  520 range: 0.11 : 1.3029e+07
            PPOREEMISSIONPROB    len:   15 range: 0 : 0.93
                 PPOCOMPONENT    len:  200 range: 0 : 0.0187
              PPOTIMECONSTANT C  len:    2 constant: 1.6
              bisMSBABSLENGTH    len:  375 range: 27.42 : 1.5e+08
         bisMSBREEMISSIONPROB    len:   23 range: 0 : 0.932
              bisMSBCOMPONENT    len:  275 range: 0 : 1
           bisMSBTIMECONSTANT C  len:    2 constant: 1.4
           SCINTILLATIONYIELD C  len:    2 constant: 9846
              RESOLUTIONSCALE C  len:    2 constant: 1

    ] nraw 1






arrange for local conversion to investigate warnings
-------------------------------------------------------

* g4cx/tests/G4CXOpticks_setGeometry_Test.sh 

GProperty_SIGINT::


    (lldb) f 8
    frame #8: 0x0000000100466451 libExtG4.dylib`X4PhysicalVolume::convertScintillators(this=0x00007ffeefbfccc8) at X4PhysicalVolume.cc:439
       436 	void X4PhysicalVolume::convertScintillators()
       437 	{
       438 	    LOG(LEVEL) << "[" ; 
    -> 439 	    collectScintillatorMaterials(); 
       440 	    createScintillatorGeant4InterpolatedICDF(); 
       441 	    LOG(LEVEL) << "]" ; 
       442 	}
    (lldb) f 7
    frame #7: 0x0000000100468e2c libExtG4.dylib`X4PhysicalVolume::collectScintillatorMaterials(this=0x00007ffeefbfccc8) at X4PhysicalVolume.cc:391
       388 	        m_sclib->addRawOriginal(pmap);      
       389 	    }
       390 	
    -> 391 	    m_sclib->dump("X4PhysicalVolume::collectScintillatorMaterials"); 
       392 	    LOG(LEVEL) << "]" ; 
       393 	}
       394 	
    (lldb) f 6
    frame #6: 0x000000010679bbcf libGGeo.dylib`GScintillatorLib::dump(this=0x0000000111a4a6e0, msg="X4PhysicalVolume::collectScintillatorMaterials") at GScintillatorLib.cc:61
       58  	void GScintillatorLib::dump(const char* msg)
       59  	{
       60  	    Summary(msg); 
    -> 61  	    dumpRaw(msg); 
       62  	}
       63  	
       64  	void GScintillatorLib::save()
    (lldb) f 5
    frame #5: 0x0000000106762714 libGGeo.dylib`GPropertyLib::dumpRaw(this=0x0000000111a4a6e0, msg="X4PhysicalVolume::collectScintillatorMaterials") const at GPropertyLib.cc:964
       961 	    {
       962 	        GPropertyMap<double>* pmap = m_raw[i] ;
       963 	        LOG(info) << " component " << pmap->getName() ;
    -> 964 	        LOG(info) << " table " << pmap->make_table() ;
       965 	    }
       966 	    LOG(info) << "] nraw " << nraw << " " << msg ; 
       967 	}
    (lldb) 

    (lldb) f 4
    frame #4: 0x00000001067439d7 libGGeo.dylib`GPropertyMap<double>::make_table(this=0x0000000111a53ae0, fw=20, dscale=1, dreciprocal=false) at GPropertyMap.cc:1007
       1004	
       1005	   unsigned int cfw = 10 + fw ; 
       1006	
    -> 1007	   if(vprops.size() > 0) ss << GProperty<T>::make_table( fw, dscale, dreciprocal, false,vprops, vtitles ) ;
       1008	   if(cprops.size() > 0) ss << GProperty<T>::make_table( cfw, dscale, dreciprocal, true ,cprops, ctitles )  ;
       1009	   if(dprops.size() > 0) ss << GProperty<T>::make_table( cfw, dscale, dreciprocal, true ,dprops, dtitles )  ;
       1010	   if(eprops.size() > 0) ss << GProperty<T>::make_table( cfw, dscale, dreciprocal, true ,eprops, etitles )  ;
    (lldb) p vprops
    (std::__1::vector<GProperty<double> *, std::__1::allocator<GProperty<double> *> >) $0 = size=16 {
      [0] = 0x0000000111a53de0
      [1] = 0x0000000111a53dc0
      [2] = 0x0000000111a54810
      [3] = 0x0000000111a54b10
      [4] = 0x0000000111a54bb0
      [5] = 0x0000000111a548b0
      [6] = 0x0000000111a54f10
      [7] = 0x0000000111a55560
      [8] = 0x0000000111a54fa0
      [9] = 0x0000000111a55720
      [10] = 0x0000000111a55950
      [11] = 0x0000000111a55da0
      [12] = 0x0000000111a55b90
      [13] = 0x0000000111a55f60
      [14] = 0x0000000111a56660
      [15] = 0x0000000111a55480
    }
    (lldb) 

    (lldb) f 3
    frame #3: 0x00000001067080f1 libGGeo.dylib`GProperty<double>::make_table(fw=20, dscale=1, dreciprocal=false, constant=false, columns=size=16, titles=size=16) at GProperty.cc:507
       504 	                            << " " << b->brief(titles[c].c_str())
       505 	                            ; 
       506 	
    -> 507 	                 if(SSys::getenvvar("GProperty_SIGINT")) std::raise(SIGINT); 
       508 	
       509 	                 hasSameDomain(a,b, delta, true); // dump
       510 	            }
    (lldb) 


Grab GDML
--------------

::

    240 const bool G4CXOpticks::setGeometry_saveGeometry = SSys::getenvbool("G4CXOpticks__setGeometry_saveGeometry") ;    


::

    2022-10-05 18:21:47.757 INFO  [68203] [G4CXOpticks::setGeometry@260] ] CSGOptiX::Create 
    2022-10-05 18:21:47.757 INFO  [68203] [G4CXOpticks::setGeometry@262]  cx 0x165f39b40 qs 0x165e9fbe0 QSim::Get 0x165e9fbe0
    2022-10-05 18:21:47.757 INFO  [68203] [G4CXOpticks::setGeometry@267] [ G4CXOpticks__setGeometry_saveGeometry 
    2022-10-05 18:21:47.757 INFO  [68203] [G4CXOpticks::saveGeometry@427] dir [$DefaultOutputDir
    SOpticksResource::ExecutableName exe0 python3.8 is_python 1 script ntds3 exe ntds3 result ntds32022-10-05 18:21:47.758 INFO  [68203] [G4CXOpticks::saveGeometry_@438] [ /tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks
    2022-10-05 18:21:52.330 INFO  [68203] [BFile::preparePath@837] created directory /tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/GGeo/GItemList
    2022-10-05 18:21:52.423 INFO  [68203] [BFile::preparePath@837] created directory /tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/GGeo/GNodeLib
    2022-10-05 18:21:52.683 INFO  [68203] [BFile::preparePath@837] created directory /tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/GGeo/GScintillatorLib/LS
    2022-10-05 18:21:52.685 INFO  [68203] [BFile::preparePath@837] created directory /tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/GGeo/GScintillatorLib/LS_ori
    2022-10-05 18:21:54.801 INFO  [68203] [U4GDML::write@148]  ekey U4GDML_GDXML_FIX_DISABLE U4GDML_GDXML_FIX_DISABLE 0 U4GDML_GDXML_FIX 1
    G4GDML: Writing '/tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/origin_raw.gdml'...
    G4GDML: Writing definitions...
    G4GDML: Writing materials...
    G4GDML: Writing solids...
    G4GDML: Writing structure...
    G4GDML: Writing setup...
    G4GDML: Writing surfaces...
    G4GDML: Writing '/tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/origin_raw.gdml' done !
    2022-10-05 18:21:58.041 INFO  [68203] [U4GDML::write@159]  Apply GDXML::Fix  rawpath /tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/origin_raw.gdml dstpath /tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks/origin.gdml
    2022-10-05 18:21:58.041 INFO  [68203] [G4CXOpticks::saveGeometry_@444] ] /tmp/blyth/opticks/GEOM/ntds3/G4CXOpticks
    2022-10-05 18:21:58.041 INFO  [68203] [G4CXOpticks::setGeometry@269] ] G4CXOpticks__setGeometry_saveGeometry 
    2022-10-05 18:21:58.041 INFO  [68203] [G4CXOpticks::setGeometry@272] ] fd 0x162eb89b0
    2022-10-05 18:21:58.041 INFO  [68203] [LSExpDetectorConstruction_Opticks::Setup@31] ] WITH_G4CXOPTICKS 




local checking of new geometry conversion
--------------------------------------------

1. run tds3 on GPU workstation, examine log to find OPTICKS_KEY 






::

    2021-12-10 23:05:27.282 INFO  [68176] [G4Opticks::translateGeometry@961] ( GGeo populate
    2021-12-10 23:05:27.359 INFO  [68176] [X4PhysicalVolume::convertMaterials@264]  num_mt 20
       0 :                             LS :  num_prop  19               RINDEX              GROUPVEL              RAYLEIGH             ABSLENGTH         FASTCOMPONENT         SLOWCOMPONENT        REEMISSIONPROB       OpticalCONSTANT         GammaCONSTANT         AlphaCONSTANT       NeutronCONSTANT          PPOABSLENGTH     PPOREEMISSIONPROB          PPOCOMPONENT       PPOTIMECONSTANT       bisMSBABSLENGTH  bisMSBREEMISSIONPROB       bisMSBCOMPONENT    bisMSBTIMECONSTANT 
       1 :                          Steel :  num_prop   1            ABSLENGTH 
       2 :                          Tyvek :  num_prop   1            ABSLENGTH 
       3 :                            Air :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
       4 :                   Scintillator : 
       5 :                    TiO2Coating : 
       6 :                       Adhesive : 
       7 :                      Aluminium : 
       8 :                           Rock :  num_prop   1            ABSLENGTH 
       9 :             LatticedShellSteel :  num_prop   1            ABSLENGTH 
      10 :                        Acrylic :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      11 :                          PE_PA :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      12 :                     StrutSteel :  num_prop   2         REFLECTIVITY             ABSLENGTH 
      13 :                    AcrylicMask :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      14 :               CDReflectorSteel :  num_prop   2         REFLECTIVITY             ABSLENGTH 
      15 :                         Vacuum :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      16 :                          Pyrex :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      17 :                          Water :  num_prop   4               RINDEX              GROUPVEL              RAYLEIGH             ABSLENGTH 
      18 :                      vetoWater :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      19 :                       Galactic : 

    2021-12-10 23:05:27.368 ERROR [68176] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt Scintillator
    2021-12-10 23:05:27.369 ERROR [68176] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt TiO2Coating
    2021-12-10 23:05:27.370 ERROR [68176] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt Adhesive
    2021-12-10 23:05:27.373 ERROR [68176] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt Aluminium
    2021-12-10 23:05:27.386 ERROR [68176] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt Galactic
    2021-12-10 23:05:27.395 INFO  [68176] [X4PhysicalVolume::convertMaterials@273]  used_materials.size 20 num_material_with_efficiency 0


    0255 void X4PhysicalVolume::convertMaterials()
     256 {
     257     OK_PROFILE("_X4PhysicalVolume::convertMaterials");
     258     LOG(LEVEL) << "[" ;
     259 
     260     const G4VPhysicalVolume* pv = m_top ;
     261     int depth = 0 ;
     262     convertMaterials_r(pv, depth);
     263 
     264     LOG(info) << X4Material::Desc(m_mtlist);
     265 
     266     const std::vector<G4Material*>& used_materials = m_mtlist ;
     267     X4MaterialTable::Convert(m_mlib, m_material_with_efficiency, used_materials );
     268     size_t num_material_with_efficiency = m_material_with_efficiency.size() ;
     269 
     270     m_mlib->close();   // may change order if prefs dictate
     271 
     272     LOG(verbose) << "]" ;
     273     LOG(info)
     274           << " used_materials.size " << used_materials.size()
     275           << " num_material_with_efficiency " << num_material_with_efficiency
     276           ;
     277 
     278     m_mlib->dumpSensitiveMaterials("X4PhysicalVolume::convertMaterials");
     279 
     280 
     281     LOG(LEVEL) << "]" ;
     282     OK_PROFILE("X4PhysicalVolume::convertMaterials");
     283 }




    2021-12-10 23:05:27.395 INFO  [68176] [GMaterialLib::dumpSensitiveMaterials@1258] X4PhysicalVolume::convertMaterials num_sensitive_materials 0
    2021-12-10 23:05:27.395 INFO  [68176] [X4PhysicalVolume::collectScintillatorMaterials@368]  found 1 scintillator materials  
    2021-12-10 23:05:27.396 INFO  [68176] [GScintillatorLib::Summary@51] X4PhysicalVolume::collectScintillatorMaterials GScintillatorLib.getNumRaw  1 GScintillatorLib.getNumRawOriginal  1


    0342 void X4PhysicalVolume::collectScintillatorMaterials()
     343 {
     344     LOG(LEVEL) << "[" ;
     345     assert( m_sclib );
     346     std::vector<GMaterial*>  scintillators_raw = m_mlib->getRawMaterialsWithProperties(SCINTILLATOR_PROPERTIES, ',' );
     347 
     348     typedef GPropertyMap<double> PMAP ;
     349     std::vector<PMAP*> raw_energy_pmaps ;
     350     m_mlib->findRawOriginalMapsWithProperties( raw_energy_pmaps, SCINTILLATOR_PROPERTIES, ',' );
     351 
     352     bool consistent = scintillators_raw.size() == raw_energy_pmaps.size()  ;
     353     if(!consistent)
     354         LOG(fatal)
     355             << " scintillators_raw.size " << scintillators_raw.size()
     356             << " raw_energy_pmaps.size " << raw_energy_pmaps.size()
     357             ;
     358 
     359     assert( consistent );
     360     unsigned num_scint = scintillators_raw.size() ;
     361 
     362     if(num_scint == 0)
     363     {
     364         LOG(LEVEL) << " found no scintillator materials  " ;
     365         return ;
     366     }
     367 
     368     LOG(info) << " found " << num_scint << " scintillator materials  " ;
     369 
     370     // wavelength domain 
     371     for(unsigned i=0 ; i < num_scint ; i++)
     372     {
     373         GMaterial* mat_ = scintillators_raw[i] ;
     374         PMAP* mat = dynamic_cast<PMAP*>(mat_);
     375         m_sclib->addRaw(mat);
     376     }
     377 
     378     // original energy domain 
     379     for(unsigned i=0 ; i < num_scint ; i++)
     380     {
     381         PMAP* pmap = raw_energy_pmaps[i] ;
     382         m_sclib->addRawOriginal(pmap);
     383     }
     384 
     385     m_sclib->dump("X4PhysicalVolume::collectScintillatorMaterials");
     386     LOG(LEVEL) << "]" ;
     387 }



    2021-12-10 23:05:27.396 INFO  [68176] [GPropertyLib::dumpRaw@937] X4PhysicalVolume::collectScintillatorMaterials
    2021-12-10 23:05:27.396 INFO  [68176] [GPropertyLib::dumpRaw@942]  component LS

    0935 void GPropertyLib::dumpRaw(const char* msg) const
     936 {
     937     LOG(info) << msg ;
     938     unsigned int nraw = m_raw.size();
     939     for(unsigned int i=0 ; i < nraw ; i++)
     940     {
     941         GPropertyMap<double>* pmap = m_raw[i] ;
     942         LOG(info) << " component " << pmap->getName() ;
     943         LOG(info) << " table " << pmap->make_table() ;
     944     }
     945 }


    2021-12-10 23:05:27.396 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 GROUPVEL range: 53.4699 : 206.241
    2021-12-10 23:05:27.397 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 18
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@227]  np_maxdiff  a    18 b    18
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    0 av    79.9898 bv    79.9898 ab          0
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    1 av    120.023 bv    124.808 ab     4.7845
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    2 av     129.99 bv    134.802 ab    4.81234
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    3 av    139.984 bv    144.808 ab     4.8231
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    4 av    149.975 bv    154.816 ab    4.84092
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    5 av     159.98 bv    164.829 ab    4.84916
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    6 av    169.981 bv    174.835 ab    4.85386
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    7 av    179.974 bv    184.844 ab    4.86997
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    8 av    189.985 bv    194.852 ab    4.86682
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i    9 av    199.974 bv    239.982 ab    40.0071
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i   10 av        300 bv    344.572 ab    44.5721
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i   11 av      404.7 bv    419.674 ab    14.9747
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i   12 av      435.8 bv    459.533 ab    23.7336
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i   13 av    486.001 bv    514.257 ab    28.2557
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i   14 av    546.001 bv    566.686 ab    20.6858
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i   15 av    589.001 bv     635.81 ab    46.8085
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i   16 av      690.7 bv    741.299 ab     50.599
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@242]  i   17 av    799.898 bv    799.898 ab          0
    2021-12-10 23:05:27.397 INFO  [68176] [np_maxdiff@251]  maxdiff 50.599
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 11
    2021-12-10 23:05:27.397 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 RAYLEIGH range: 546.429 : 321429
    2021-12-10 23:05:27.397 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 11
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 11
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 497
    2021-12-10 23:05:27.397 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 ABSLENGTH range: 0.00296154 : 125372
    2021-12-10 23:05:27.397 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 497
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 497
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-12-10 23:05:27.397 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 FASTCOMPONENT range: 0 : 1



    0470 template <typename T>
     471 std::string GProperty<T>::make_table(int fw, T dscale, bool dreciprocal, bool constant, std::vector< GProperty<T>* >& columns, std::vector<std::string>& titles)
     472 {
     473     assert(columns.size() == titles.size());
     474     unsigned int ncol = columns.size();
     475 
     476     T delta = 3e-6 ;   // get domain mismatch with default 1e-6 for GROUPVEL 
     477 
     478     std::stringstream ss ;
     479     if(ncol == 0)
     480     {   
     481         ss << "no columns" ;
     482     }
     483     else
     484     {   
     485         GProperty<T>* a = columns[0] ;
     486         for(unsigned int c=1 ; c < ncol ; c++)
     487         {   
     488             GProperty<T>* b = columns[c] ;  
     489             bool same_domain = hasSameDomain(a,b, delta) ;
     490             if(!same_domain)
     491             {    
     492                  LOG(fatal) << "GProperty<T>::make_table"
     493                             << " domain mismatch "
     494                             << " " << a->brief(titles[0].c_str())
     495                             << " " << b->brief(titles[c].c_str())
     496                             ; 
     497                  hasSameDomain(a,b, delta, true); // dump
     498             }
     499             
     500             //assert(same_domain);
     501         }
     502         GAry<T>* doms = a ? a->getDomain() : NULL ;
     503         assert(doms);
     504         
     505         ss << std::setw(fw) << "domain" ; 
     506         for(unsigned int c=0 ; c < ncol ; c++) ss << std::setw(fw) << titles[c] ;
     507         ss << std::endl ;
     508         
     509         T one(1); 
     510         std::vector< GAry<T>* > values ;  
     511         for(unsigned int c=0 ; c < ncol ; c++) values.push_back(columns[c]->getValues()) ;
     512         
     513         unsigned int nr = doms->getLength();
     514         
     515         for(unsigned int r=0 ; r < nr ; r++)
     516         {   
     517             if(constant && !(r == 0 || r == nr - 1)) continue ;
     518             
     519             T dval = doms->getValue(r) ; 





    2021-12-10 23:05:27.397 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 275
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-12-10 23:05:27.397 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 SLOWCOMPONENT range: 0 : 1
    2021-12-10 23:05:27.397 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 275
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 28
    2021-12-10 23:05:27.397 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 REEMISSIONPROB range: 0 : 0.8022
    2021-12-10 23:05:27.397 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 28
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 28
    2021-12-10 23:05:27.397 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-12-10 23:05:27.397 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 GammaCONSTANT range: 0.028 : 0.707
    2021-12-10 23:05:27.397 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 4
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-12-10 23:05:27.398 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 AlphaCONSTANT range: 0.0812 : 0.4982
    2021-12-10 23:05:27.398 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 4
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-12-10 23:05:27.398 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 NeutronCONSTANT range: 0.064 : 0.614
    2021-12-10 23:05:27.398 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 4
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 770
    2021-12-10 23:05:27.398 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 PPOABSLENGTH range: 0.02 : 1.3029e+07
    2021-12-10 23:05:27.398 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 770
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 770
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 15
    2021-12-10 23:05:27.398 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 PPOREEMISSIONPROB range: 0 : 0.93
    2021-12-10 23:05:27.398 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 15
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 15
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 200
    2021-12-10 23:05:27.398 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 PPOCOMPONENT range: 0 : 0.0187
    2021-12-10 23:05:27.398 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 200
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 200
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 375
    2021-12-10 23:05:27.398 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 bisMSBABSLENGTH range: 27.42 : 1.5e+08
    2021-12-10 23:05:27.398 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 375
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 375
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 23
    2021-12-10 23:05:27.398 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 bisMSBREEMISSIONPROB range: 0 : 0.932
    2021-12-10 23:05:27.398 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 23
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 23
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-12-10 23:05:27.398 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 bisMSBCOMPONENT range: 0 : 1
    2021-12-10 23:05:27.398 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 275
    2021-12-10 23:05:27.398 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-12-10 23:05:27.399 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 2
    2021-12-10 23:05:27.399 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  OpticalCONSTANT constant: 1 PPOTIMECONSTANT constant: 1.6
    2021-12-10 23:05:27.399 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 1 blen 2
    2021-12-10 23:05:27.399 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 2
    2021-12-10 23:05:27.399 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 2
    2021-12-10 23:05:27.399 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  OpticalCONSTANT constant: 1 bisMSBTIMECONSTANT constant: 1.4
    2021-12-10 23:05:27.399 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 1 blen 2
    2021-12-10 23:05:27.399 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 2
    2021-12-10 23:05:27.399 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 761
    2021-12-10 23:05:27.399 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  OpticalCONSTANT constant: 1 SCINTILLATIONYIELD constant: 11522
    2021-12-10 23:05:27.399 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 1 blen 761
    2021-12-10 23:05:27.399 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 761
    2021-12-10 23:05:27.399 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 761
    2021-12-10 23:05:27.399 FATAL [68176] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  OpticalCONSTANT constant: 1 RESOLUTIONSCALE constant: 1
    2021-12-10 23:05:27.399 INFO  [68176] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 1 blen 761
    2021-12-10 23:05:27.399 WARN  [68176] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 761
    2021-12-10 23:05:27.396 INFO  [68176] [GPropertyLib::dumpRaw@943]  table GPropertyMap<T>::make_table vprops 16 cprops 5 dprops 0 eprops 0 fprops 0 gprops 0
                  domain              RINDEX            GROUPVEL            RAYLEIGH           ABSLENGTH       FASTCOMPONENT       SLOWCOMPONENT      REEMISSIONPROB       GammaCONSTANT       AlphaCONSTANT     NeutronCONSTANT        PPOABSLENGTH   PPOREEMISSIONPROB        PPOCOMPONENT     bisMSBABSLENGTHbisMSBREEMISSIONPROB     bisMSBCOMPONENT
                 79.9898              1.4536             206.241             546.429          0.00296154                   0                   0                 0.4               0.028              0.0812               0.064                0.02               0.651                   0               42.26              0.6524                   0
                 120.023              1.4536             199.323             546.429          0.00296154                   0                   0                 0.4                0.06              0.1467                0.09                0.02               0.651                   0               42.26              0.6524                   0
                  129.99              1.5545             186.282             546.429          0.00296154                   0                   0                 0.4               0.205              0.2739               0.232                0.02               0.651                   0               41.13              0.6524                   0
                 139.984              1.6642             173.954             4885.71             1.42154            0.002269            0.002269                0.42               0.707              0.4982               0.614                0.02               0.651                   0               40.36              0.6524            0.002269
                 149.975              1.7826             167.688             19285.7             1.62885            0.002153            0.002153                0.45        3.52883e-315        3.52883e-315        3.52883e-315                0.02               0.651                   0               39.63              0.6524            0.002153
                  159.98               1.793             53.4699               27000             1.83615            0.001981            0.001981                 0.8        2.42092e-322        1.63042e-322        2.42092e-322                0.02                0.93                   0               38.37               0.932            0.001981
                 169.981              1.5545             148.255             39857.1             2.07308            0.001887            0.001887              0.8006        6.95332e-310        6.95332e-310        6.95332e-310                0.02                0.93                   0               37.71               0.932            0.001887
                 179.974               1.527             190.671             64285.7             2.28038            0.002218            0.002218              0.8004         1.62923e-05        3.52883e-315         1.62709e-05                0.02                0.93                   0               36.32               0.932            0.002218
                 189.985              1.6176              185.28              109286             2.60615            0.001909            0.001909              0.8022        3.52873e-315        1.97626e-323        3.52883e-315                0.02                0.93                   0               35.73               0.932            0.001909
                 199.974              1.6185             166.595              192857             2.81346            0.001965            0.001965              0.6353        3.52873e-315        1.63042e-322        3.52884e-315                0.02                0.93                   0               35.04               0.932            0.001965
                     300              1.5264              186.81              321429             3.02077             0.00169             0.00169              0.4165        2.37152e-322        6.95332e-310        9.88131e-323                0.02                0.93              0.0003               34.92               0.932             0.00169
                   404.7              1.4988             194.453        1.63042e-322             3.19846            0.001809            0.001809              0.3004        2.42092e-322        3.52873e-315        2.42092e-322                0.02                0.93              0.0003               34.69               0.932            0.001809
                   435.8              1.4955             195.919        6.95332e-310             3.40577            0.001994            0.001994              0.2354        6.95332e-310        1.97626e-323        6.95332e-310                0.02                   0              0.0002               34.59               0.932            0.001994
                 486.001              1.4915             195.281        3.52864e-315             3.58346            0.002311            0.002311              0.2203         7.38968e+97        1.63042e-322        6.95314e-310                0.02                   0              0.0002               34.69               0.932            0.002311
                 546.001              1.4861              198.51        1.44296e-312             3.73154             0.00205             0.00205              0.1969        3.52883e-315        6.95332e-310        3.52873e-315                0.02                   0              0.0002               34.92               0.932             0.00205
                 589.001              1.4842              198.74        2.42092e-322             3.90923            0.002102            0.002102              0.1936        3.52875e-315        3.52875e-315        3.52883e-315                0.02        6.37345e-322              0.0001               35.15               0.932            0.002102
                   690.7                1.48             200.934        6.95332e-310             4.08692            0.002259            0.002259              0.1712        3.52875e-315        4.94066e-324        3.52883e-315                0.02               0.651              0.0001               35.61               0.932            0.002259
                 799.898              1.4781             201.062         3.55114e+59               4.235            0.002578            0.002578              0.1417        1.63042e-322        1.63042e-322        2.42092e-322                0.02               0.651              0.0001                36.2               0.932            0.002578
                            domain               OpticalCONSTANT               PPOTIMECONSTANT            bisMSBTIMECONSTANT            SCINTILLATIONYIELD               RESOLUTIONSCALE
                       0.000826561                             1                           1.6                           1.4                         11522                             1

    2021-12-10 23:05:27.400 INFO  [68176] [NPY<T>::compare@2356]  a 275,2
    2021-12-10 23:05:27.400 INFO  [68176] [NPY<T>::compare@2357]  b 275,2
    2021-12-10 23:05:27.400 INFO  [68176] [NPY<T>::compare@2366]  ni 275 nv 2 dumplimit 100 epsilon 0 mode A
    2021-12-10 23:05:27.400 INFO  [68176] [NPY<T>::compare@2407]  mismatch_items 0
    2021-12-10 23:05:27.401 INFO  [68176] [X4PhysicalVolume::createScintillatorGeant4InterpolatedICDF@414]  num_scint 1 slow_en 275,2 fast_en 275,2 num_bins 4096 hd_factor 20 material_name LS g4icdf 3,4096,1
    2021-12-10 23:05:27.416 INFO  [68176] [X4PhysicalVolume::convertImplicitSurfaces_r@562]  parent_mtName Rock daughter_mtName Air
    2021-12-10 23:05:27.416 INFO  [68176] [X4PhysicalVolume::convertImplicitSurfaces_r@567]  RINDEX_NoRINDEX 1 NoRINDEX_RINDEX 0 pv1                       pExpHall pv2                       pTopRock bs 0 no-prior-border-surface-adding-implicit 
    2021-12-10 23:05:27.419 INFO  [68176] [X4PhysicalVolume::convertImplicitSurfaces_r@562]  parent_mtName Tyvek daughter_mtName vetoWater
    2021-12-10 23:05:27.419 INFO  [68176] [X4PhysicalVolume::convertImplicitSurfaces_r@567]  RINDEX_NoRINDEX 1 NoRINDEX_RINDEX 0 pv1                pOuterWaterPool pv2                    pPoolLining bs 0x2b1d7ab0 preexisting-border-surface-NOT-adding-implicit 
    2021-12-10 23:05:27.420 INFO  [68176] [X4PhysicalVolume::convertImplicitSurfaces_r@562]  parent_mtName Tyvek daughter_mtName Water
    2021-12-10 23:05:27.420 INFO  [68176] [X4PhysicalVolume::convertImplicitSurfaces_r@567]  RINDEX_NoRINDEX 1 NoRINDEX_RINDEX 0 pv1                    pInnerWater pv2               pCentralDetector bs 0x2b193610 preexisting-border-surface-NOT-adding-implicit 
    2021-12-10 23:05:27.437 INFO  [68176] [GSurfaceLib::dumpImplicitBorderSurfaces@765] X4PhysicalVolume::convertSurfaces




j/PMTSim/LSExpDetectorConstructionMaterial.icc::


     160             G4cout << "Setup LS Material Tables from MCParamsSvc" << G4endl;
     161             IMCParamsSvc::map_s2d LS_scales_map;
     162             bool st = mcgt->Get("Material.LS.scale", LS_scales_map);
     163             double scale_abslength = 1.0;
     164             if (st && LS_scales_map.count("AbsorptionLenBefore") && LS_scales_map.count("AbsorptionLenAfter")) {
     165                 scale_abslength = LS_scales_map["AbsorptionLenAfter"] / LS_scales_map["AbsorptionLenBefore"];
     166                 G4cout << "Scale ABSLENGTH from " << LS_scales_map["AbsorptionLenBefore"]
     167                        << " to " << LS_scales_map["AbsorptionLenAfter"]
     168                        << " factor: " << scale_abslength
     169                        << G4endl;
     170             }

     ...


     189            if(m_LS_optical_model == "new") // LAB AbsLength used for new LS optical model
     190                {
     191                  helper_mpt(LSMPT, "ABSLENGTH", mcgt.data(), "Material.LS.ABSLENGTH_v2");
     192                }
     193             else if (m_LS_optical_model == "old") // Old LS AbsLength used for old LS optical model
     194                {
     195                  helper_mpt(LSMPT, "ABSLENGTH", mcgt.data(), "Material.LS.ABSLENGTH_v1",scale_abslength);
     196                }
     197             else {
     198                     G4cout << "Warning: Can't find  LS abslength to register " << G4endl;
     199                  }


    epsilon:DetSim blyth$ find $JUNOTOP/data -name ABSLENGTH_v*
    /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/ABSLENGTH_v1
    /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/ABSLENGTH_v2

    epsilon:j blyth$ find $JUNOTOP/data -name scale
    /Users/blyth/junotop/data/Simulation/DetSim/Material/photocathode_Ham20inch/scale
    /Users/blyth/junotop/data/Simulation/DetSim/Material/Water/scale
    /Users/blyth/junotop/data/Simulation/DetSim/Material/LAB/scale
    /Users/blyth/junotop/data/Simulation/DetSim/Material/vetoWater/scale
    /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/scale
    /Users/blyth/junotop/data/Simulation/DetSim/Material/photocathode_3inch/scale
    /Users/blyth/junotop/data/Simulation/DetSim/Material/photocathode_MCP20inch/scale
    /Users/blyth/junotop/data/Simulation/DetSim/Material/photocathode/scale


    epsilon:j blyth$ cat /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/scale
    # This file is used for scale some variables quickly
    #   XXXBefore 1
    #   XXXAfter  1.5
    # so we could calculate the ratio is 1.5/1

    RayleighLenBefore 42.0
    RayleighLenAfter  27.0

    # used for old LS optical model
    AbsorptionLenBefore 26.0
    AbsorptionLenAfter  77.0

    # Following is Test only
    AbsorptionLenUnitBefore 26.0*m
    AbsorptionLenUnitAfter  77.0*m

    # concentration. It will affect absorption length.
    # Geant4 don't recognize mg/L
    bisMSBConcentrationBefore 15.0
    bisMSBConcentrationAfter 5.0

    # used for new LS optical model
    LSLY_NewLSModelScale   0.9684
    LSLY_NewPMTModelScale  0.8251
    epsilon:j blyth$ 




::

    epsilon:DetSim blyth$ head -10 /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/ABSLENGTH_v1
    1.3778 *eV 	0.2919 *m 
    1.3793 *eV 	0.3005 *m 
    1.3808 *eV 	0.3176 *m 
    1.3824 *eV 	0.3441 *m 
    1.3839 *eV 	0.3873 *m 
    1.3855 *eV 	0.3902 *m 
    1.3870 *eV 	0.3959 *m 
    1.3886 *eV 	0.4209 *m 
    1.3901 *eV 	0.4422 *m 
    1.3917 *eV 	0.4531 *m 
    epsilon:DetSim blyth$ tail -10 /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/ABSLENGTH_v1
    3.5530 *eV 	0.00095 *m 
    3.5581 *eV 	0.00088 *m 
    3.5632 *eV 	0.00077 *m 
    3.5683 *eV 	0.00070 *m 
    3.5735 *eV 	0.00062 *m 
    3.5786 *eV 	0.00055 *m 
    3.5838 *eV 	0.00048 *m 
    6.2000 *eV 	0.000001*m 
    10.3300*eV 	0.000001*m 
    15.500 *eV 	0.000001*m 
    epsilon:DetSim blyth$ 





::

    AlphaCONSTANT
    GammaCONSTANT
    NeutronCONSTANT
    OpticalCONSTANT

    epsilon:LS blyth$ cat AlphaCONSTANT
    4.345  *ns  0.4982 
    17.64  *ns  0.2739
    89.045   *ns  0.1467
    544.48    *ns  0.0812

    epsilon:LS blyth$ cat GammaCONSTANT
    4.6  *ns   0.707
    15.1  *ns   0.205
    76.1   *ns   0.06
    397   *ns   0.028

    epsilon:LS blyth$ cat NeutronCONSTANT
    4.5  *ns  0.614
    15.7     *ns  0.232
    76.2    *ns  0.09
    367   *ns   0.064

    epsilon:LS blyth$ cat OpticalCONSTANT
    1.50  *ns  1.0

    RAYLEIGH

    epsilon:LS blyth$ cat RAYLEIGH 
    1.55                *eV   500                 *m    
    1.7714              *eV   300                 *m    
    2.102               *eV   170                 *m    
    2.255               *eV   100                 *m    
    2.531               *eV   62                  *m    
    2.884               *eV   42                  *m    
    3.024               *eV   30                  *m    
    4.133               *eV   7.6                 *m    
    6.2                 *eV   0.85                *m    
    10.33               *eV   0.85                *m    
    15.5                *eV   0.85                *m    



    RINDEX

    epsilon:LS blyth$ cat RINDEX 
    1.55                *eV   1.4781              
    1.79505             *eV   1.48                
    2.10499             *eV   1.4842              
    2.27077             *eV   1.4861              
    2.55111             *eV   1.4915              
    2.84498             *eV   1.4955              
    3.06361             *eV   1.4988              
    4.13281             *eV   1.5264              
    6.2                 *eV   1.6185              
    6.526               *eV   1.6176              
    6.889               *eV   1.527               
    7.294               *eV   1.5545              
    7.75                *eV   1.793               
    8.267               *eV   1.7826              
    8.857               *eV   1.6642              
    9.538               *eV   1.5545              
    10.33               *eV   1.4536              
    15.5                *eV   1.4536              



    scale                    # kv
    ConstantProperty         # kv




    SLOWCOMPONENT
    FASTCOMPONENT
    PPOCOMPONENT
    bisMSBCOMPONENT

    REEMISSIONPROB
    PPOREEMISSIONPROB
    bisMSBREEMISSIONPROB

    PPOTIMECONSTANT
    bisMSBTIMECONSTANT

    ABSLENGTH_v1
    ABSLENGTH_v2
    PPOABSLENGTH
    bisMSBABSLENGTH



ABSLENGTH
-----------

::

    epsilon:j blyth$ ./qty.sh 
    https://github.com/simoncblyth/j/blob/main/qty.py
           (497, 2) : Material.LS.ABSLENGTH_v1 :     2.9615 : /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/ABSLENGTH_v1 
           (428, 2) : Material.LS.ABSLENGTH_v2 :     1.0000 : /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/ABSLENGTH_v2 
           (770, 2) : Material.LS.PPOABSLENGTH :     1.0000 : /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/PPOABSLENGTH 
           (375, 2) : Material.LS.bisMSBABSLENGTH :     1.0000 : /Users/blyth/junotop/data/Simulation/DetSim/Material/LS/bisMSBABSLENGTH 
    saving /tmp/blyth/j/qty/Material_LS_ABSLENGTH_mpplt.png 




