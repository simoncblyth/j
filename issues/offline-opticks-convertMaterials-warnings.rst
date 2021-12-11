offline-opticks-convertMaterials-warnings
============================================


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




