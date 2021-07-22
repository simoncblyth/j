material_properties_one_more_edge_than_value
==============================================

Check RINDEX props
--------------------

Most but not all end with a duplicated RINDEX value. Is that artificial duplication to handle the extra edge ?::

    O[blyth@localhost junotop]$ find $JUNOTOP/data/Simulation/DetSim/Material -name RINDEX -exec tail -v {} \;
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/LAB/RINDEX <==
    6.2                 eV   1.6185              
    6.526               eV   1.6176              
    6.889               eV   1.527               
    7.294               eV   1.5545              
    7.75                eV   1.793               
    8.267               eV   1.7826              
    8.857               eV   1.6642              
    9.538               eV   1.5545              
    10.33               eV   1.4536              
    15.5                eV   1.4536              
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/PA/RINDEX <==
    1                   eV   1.51                
    14                  eV   1.51                
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/Vacuum/RINDEX <==
    1.55                eV   1.000001            
    6.2                 eV   1.000001            
    10.33               eV   1.000001            
    15.5                eV   1.000001            
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/photocathode_Ham8inch/RINDEX <==
    1.55                eV   2.9                 
    6.2                 eV   2.9                 
    10.33               eV   2.9                 
    15.5                eV   2.9                 
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/AcrylicMask/RINDEX <==
    6.2                 eV   1.6279              
    6.526               eV   1.627               
    6.889               eV   1.5359              
    7.294               eV   1.5635              
    7.75                eV   1.793               
    8.267               eV   1.7199              
    8.857               eV   1.6739              
    9.538               eV   1.5635              
    10.33               eV   1.462               
    15.5                eV   1.462               
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/photocathode_3inch/RINDEX <==
    1.55                eV   2.9                 
    6.2                 eV   2.9                 
    10.33               eV   2.9                 
    15.5                eV   2.9                 
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/Pyrex/RINDEX <==
    1.55                eV   1.46891             
    1.88914             eV   1.47166             
    2.11015             eV   1.47377             
    2.27048             eV   1.47546             
    2.55059             eV   1.47874             
    2.84497             eV   1.48267             
    3.0996              eV   1.48646             
    4.13001             eV   1.5061              
    6.20001             eV   1.5061              
    15.5                eV   1.5061              
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/FEP/RINDEX <==
    2                   eV   1.344               
    4                   eV   1.344               
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/photocathode_Ham20inch/RINDEX <==
    3.26274             eV   1.92                
    4.13                eV   1.49                
    4.96                eV   0.564               
    15.5                eV   0.88                
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/photocathode_MCP8inch/RINDEX <==
    1.55                eV   2.9                 
    6.2                 eV   2.9                 
    10.33               eV   2.9                 
    15.5                eV   2.9                 
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/Air/RINDEX <==
    1.55                eV   1.000273            
    6.2                 eV   1.000273            
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/LS/RINDEX <==
    6.2                 eV   1.6185              
    6.526               eV   1.6176              
    6.889               eV   1.527               
    7.294               eV   1.5545              
    7.75                eV   1.793               
    8.267               eV   1.7826              
    8.857               eV   1.6642              
    9.538               eV   1.5545              
    10.33               eV   1.4536              
    15.5                eV   1.4536              
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/vetoWater/RINDEX <==
    3.446               eV   1.3572              
    3.545               eV   1.358               
    3.649               eV   1.3585              
    3.76                eV   1.359               
    3.877               eV   1.3595              
    4.002               eV   1.36                
    4.136               eV   1.3608              
    6.2                 eV   1.39                
    10.33               eV   1.33                
    15.5                eV   1.33                
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/photocathode_HZC9inch/RINDEX <==
    1.55                eV   2.9                 
    6.2                 eV   2.9                 
    10.33               eV   2.9                 
    15.5                eV   2.9                 
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/photocathode/RINDEX <==
    3.26274             eV   1.92                
    4.13                eV   1.49                
    4.96                eV   0.564               
    15.5                eV   0.88                
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/Water/RINDEX <==
    3.446               eV   1.3572              
    3.545               eV   1.358               
    3.649               eV   1.3585              
    3.76                eV   1.359               
    3.877               eV   1.3595              
    4.002               eV   1.36                
    4.136               eV   1.3608              
    6.2                 eV   1.39                
    10.33               eV   1.33                
    15.5                eV   1.33                
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/ETFE/RINDEX <==
    6.60353             eV   1.4835              
    6.76362             eV   1.4902              
    6.93166             eV   1.4941              
    7.10826             eV   1.5101              
    7.2941              eV   1.5141              
    7.48991             eV   1.5287              
    7.69653             eV   1.5407              
    8.02876             eV   1.5606              
    8.14596             eV   1.5965              
    8.26665             eV   1.6005              
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/photocathode_MCP20inch/RINDEX <==
    3.26274             eV   1.92                
    4.13                eV   1.49                
    4.96                eV   0.564               
    15.5                eV   0.88                
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/VacuumT/RINDEX <==
    1.55                eV   1.000001            
    6.2                 eV   1.000001            
    10.33               eV   1.000001            
    15.5                eV   1.000001            
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/Mylar/RINDEX <==
    6.2                 eV   1.64                
    6.526               eV   1.64                
    6.889               eV   1.64                
    7.294               eV   1.64                
    7.75                eV   1.64                
    8.267               eV   1.64                
    8.857               eV   1.64                
    9.538               eV   1.64                
    10.33               eV   1.64                
    15.5                eV   1.64                
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/PE_PA/RINDEX <==
    1                   eV   1.51                
    14                  eV   1.51                
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/Acrylic/RINDEX <==
    6.2                 eV   1.6279              
    6.526               eV   1.627               
    6.889               eV   1.5359              
    7.294               eV   1.5635              
    7.75                eV   1.793               
    8.267               eV   1.7199              
    8.857               eV   1.6739              
    9.538               eV   1.5635              
    10.33               eV   1.462               
    15.5                eV   1.462               
    ==> /data/blyth/junotop/data/Simulation/DetSim/Material/MineralOil/RINDEX <==
    6.2                 eV   1.5956              
    6.526               eV   1.596               
    6.889               eV   1.5067              
    7.294               eV   1.5337              
    7.75                eV   1.7589              
    8.267               eV   1.687               
    8.857               eV   1.642               
    9.538               eV   1.5337              
    10.33               eV   1.434               
    15.5                eV   1.434               
    O[blyth@localhost junotop]$ 



what reads these files ? jgr G4MaterialPropertiesTable 
-----------------------------------------------------------

::

    Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc


::

     195 
     196          helper_mpt(LSMPT, "RINDEX",                     mcgt.data(), "Material.LS.RINDEX");
     197          helper_mpt(LSMPT, "FASTCOMPONENT",              mcgt.data(), "Material.LS.FASTCOMPONENT");
     198          helper_mpt(LSMPT, "SLOWCOMPONENT",              mcgt.data(), "Material.LS.SLOWCOMPONENT");
     199          helper_mpt(LSMPT, "REEMISSIONPROB",             mcgt.data(), "Material.LS.REEMISSIONPROB");
     200          helper_mpt(LSMPT, "RAYLEIGH",                   mcgt.data(), "Material.LS.RAYLEIGH", scale_rayleigh);
     201


::

    epsilon:offline blyth$ jgr ::helper_mpt 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:LSExpDetectorConstruction::helper_mpt(G4MaterialPropertiesTable* MPT, const std::string& mname, IMCParamsSvc* params, const std::string& name, double scale) {


jcv LSExpDetectorConstruction::

   186   private:
   187      bool helper_mpt(G4MaterialPropertiesTable*, const std::string&, IMCParamsSvc*, const std::string&, double scale=1.0);
   188      // insert properties into material properties table


   01671 bool
    1672 LSExpDetectorConstruction::helper_mpt(G4MaterialPropertiesTable* MPT, const std::string& mname, IMCParamsSvc* params, const std::string& name, double scale) {
    1673     IMCParamsSvc::vec_d2d props;
    1674     bool st = params->Get(name, props);
    1675     if (!st) {
    1676         LogError << "can't find material property: " << name << std::endl;
    1677         return false;
    1678     }
    1679     G4MaterialPropertyVector* vec = new G4MaterialPropertyVector(0,0,0);
    1680 
    1681     int N = props.size();
    1682     if (!N) {
    1683         LogError << "empty material property: " << name << std::endl;
    1684         return false;
    1685     }
    1686     for (int i = 0; i < N; ++i) {
    1687         vec->InsertValues(props[i].get<0>(), props[i].get<1>()*scale);
    1688     }
    1689     MPT->AddProperty(mname.c_str(), vec);
    1690     return true;
    1691 }
    1692 

* notice no special handling for the duplicated last value 



* geant4 also glosses over the extra edge

g4-cls G4MaterialPropertyVector
g4-cls G4PhysicsOrderedFreeVector::

    080   G4PhysicsOrderedFreeVector(G4double* Energies,
     81                  G4double* Values,
     82                  size_t VectorLength);
     83   // the vector is filled in this constructor 

     93   void InsertValues(G4double energy, G4double value);


    101   inline G4double GetMaxLowEdgeEnergy();
    103   inline G4double GetMinLowEdgeEnergy();


These are not max and min they are values at first and last energy ordered bin::

    112 inline
    113 G4double G4PhysicsOrderedFreeVector::GetMaxValue()
    114 {
    115   return dataVector.back();
    116 }
    117 
    118 inline
    119 G4double G4PhysicsOrderedFreeVector::GetMinValue()
    120 {
    121   return dataVector.front();
    122 }
    123 

"LowEdgeEnergy" ? So whats the high edge ? Fudged interface ?::

    124 inline
    125 G4double G4PhysicsOrderedFreeVector::GetMaxLowEdgeEnergy()
    126 {
    127   return binVector.back();
    128 }
    129 
    130 inline
    131 G4double G4PhysicsOrderedFreeVector::GetMinLowEdgeEnergy()
    132 {
    133   return binVector.front();
    134 }


::

     60 G4PhysicsOrderedFreeVector::G4PhysicsOrderedFreeVector(G4double *Energies,
     61                                                        G4double *Values,
     62                                                        size_t VectorLength)
     63   : G4PhysicsVector()
     64 {
     65         type = T_G4PhysicsOrderedFreeVector;
     66 
     67         dataVector.reserve(VectorLength);
     68         binVector.reserve(VectorLength);
     69 
     70         for (size_t i = 0 ; i < VectorLength ; ++i)
     71         {
     72           InsertValues(Energies[i], Values[i]);
     73         }
     74 }

     79 void G4PhysicsOrderedFreeVector::InsertValues(G4double energy, G4double value)
     80 {
     81         std::vector<G4double>::iterator binLoc =
     82                  std::lower_bound(binVector.begin(), binVector.end(), energy);
     83 
     84         size_t binIdx = binLoc - binVector.begin(); // Iterator difference!
     85 
     86         std::vector<G4double>::iterator dataLoc = dataVector.begin() + binIdx;
     87 
     88         binVector.insert(binLoc, energy);
     89         dataVector.insert(dataLoc, value);
     90 
     91         ++numberOfNodes;
     92         edgeMin = binVector.front();
     93         edgeMax = binVector.back();
     94 }


g4-cls G4PhysicsVector::

    207     G4PhysicsVectorType type;   // The type of PhysicsVector (enumerator)
    208 
    209     G4double edgeMin;           // Energy of first point
    210     G4double edgeMax;           // Energy of the last point
    211 
    212     size_t numberOfNodes;
    213 
    214     G4PVDataVector  dataVector;    // Vector to keep the crossection/energyloss
    215     G4PVDataVector  binVector;     // Vector to keep energy
    216     G4PVDataVector  secDerivative; // Vector to keep second derivatives 
    217 



        epsilon:offline blyth$ jcv IMCParamsSvc
    ./Simulation/DetSimV2/MCParamsSvc/MCParamsSvc/IMCParamsSvc.hh


    031 class IMCParamsSvc {
     32     public:
     33         virtual ~IMCParamsSvc() {}
     34 
     35         typedef boost::tuple<double, double> elem_d2d; // double, double
     36         typedef boost::tuple<std::string, double> elem_s2d; // string, double
     37 
     38         typedef std::vector<elem_d2d> vec_d2d;
     39         typedef std::vector<elem_s2d> vec_s2d;
     40         // Instead of using (string: double) vector, we could also use map<string, double>.
     41         typedef std::map<std::string, double> map_s2d;
     42 
     43         virtual bool Get(const std::string& param, vec_d2d& props) = 0;
     44         virtual bool Get(const std::string& param, vec_s2d& props) = 0;
     45         virtual bool Get(const std::string& param, map_s2d& props) = 0;
     46 
     47 };


jgr IMCParamsSvc
jcv MCParamsFileSvc


    041 bool
     42 MCParamsFileSvc::Get(const std::string& param, vec_d2d& props)
     43 {  
     44      const std::string path = GetPath( param );
     45     return get_implv1(path, props); 
     46 }
     47 

    epsilon:offline blyth$ jcv utils
    2 files to edit
    ./Simulation/DetSimV2/MCParamsSvc/src/utils.hh
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/utils.py
    epsilon:offline blyth$ 


    065 // template function helper
     66 template<typename T1, typename T2>
     67 bool get_implv1(const std::string& path,
     68         std::vector< boost::tuple<T1, T2> >& props)
     69 {
     70     namespace fs = boost::filesystem;
     71   
     72     fs::path fullp(path);
     73    
     74     typename boost::tuple<T1, T2> elem;
     75 
     76     std::ifstream ifs(fullp.string().c_str());
     77     while (ifs.good()) {
     78             std::string temp_line;
     79             std::getline(ifs, temp_line);
     80 
     81             // skip comments, starts with '#'
     82             temp_line.erase( std::find( temp_line.begin(), temp_line.end(), '#' ), temp_line.end() );
     83 
     84             // std::cout << "TEMP LINE: " << temp_line << std::endl;
     85             std::stringstream ss;
     86             ss << temp_line;
     87             // ============================
     88             // First Element
     89             // ============================
     90             ss >> elem.template get<0>();
     91             // ss >> elem;
     92             if (ss.fail()) { continue; }
     93 
     94             char c = ss.get();
     95             while (isspace(c)) {
     96                 c = ss.get();
     97                 if (ss.fail()) { return false; }
     98             }
     99             ss.unget();
    100             if (!isdigit(c)) {
    101                 // could be unit
    102                 std::string unit_1st;
    103                 ss >> unit_1st;
    104                 if (!ss.fail()) {
    105                      with_units(elem.template get<0>(), unit_1st);
    106                 }
    107             }
    108 
    109             // ============================
    110             // Second Element
    111             // ============================
    112             ss >> elem.template get<1>();
    113             if (ss.fail()) { continue; }
    113             if (ss.fail()) { continue; }
    114             // try detect unit
    115             std::string unit_2nd;
    116             ss >> unit_2nd;
    117             if (!ss.fail()) {
    118                 with_units(elem.template get<1>(), unit_2nd);
    119             }
    120 
    121             // std::cout << "After parsed: " << elem << std::endl;
    122             props.push_back(elem);
    123         }
    124     return true;
    125 }


