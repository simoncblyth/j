PMTEfficiency_collection_review
================================

jgr PMTEfficiency::

    jcv PMTEfficency

    jcv PMTEfficencyTable

    jcv PMTEfficiencyCheck

    jcv junoSD_PMT_v2

    jcv LSExpDetectorConstruction_Opticks
        sensor efficiencies passed to Opticks



jcv PMTEfficiency
------------------

* angular efficiencies are "hidden" in junoSD_PMT_v2::get_ce with only an awkward API to access them::

    double junoSD_PMT_v2::get_ce(const std::string& volname, const G4ThreeVector& localpos, bool pmt_type, bool qe_type, int &ce_cat)  

Previously I avoided trying to use this horrible API by duplicating the static double theta and efficiency arrays 
in PMTEfficiency

* was hoping to get people to see the light and do things in this clearer way, 
  but now have learnt lesson : people do not see code ugliness like I do.   

* hence being pragmatic can workaround the problem by adding method::

    double junoSD_PMT_v2::get_ce(double theta, int pmtcat)   

And implement that using: 

* hardcoded mapping between category integer and volname string (simple static array)
* use G4ThreeVector::setTheta to mockup a localpos
* convert category integer into pmt_type and qe_type bools 

The above is ugly and awkward but it is entirely do-able and will be simpler to maintain 
as then PMTEfficiency can be deleted, avoiding duplicated arrays.


::

     29 class PMTEfficiency
     30 {
     31    public:
     32         static PMTEfficiency* Make();
     33    public:
     34         enum { NBIN = 9, N_PMTCAT = 5 } ;
     35    private:
     36         // static char    CATEGORY_TYPE ;  
     37         static PMTEfficiency* INSTANCE ;
     38         static int s_pmt_categories_parcat[N_PMTCAT] ;
     39 //         static int s_pmt_categories_simcat[N_PMTCAT] ; 
     40         static double MISSING_EFFICIENCY ;
     41 //    public:  
     42 //         // SimToPar and ParToSim methods do not depend on CATEGORY_TYPE
     43 //         static int SimToPar(int simcat); 
     44 //         static int ParToSim(int parcat); 
     45    public:
     46         static int* PMTCategories();
     47         static int  NumPMTCategories();
     48 
     49 
     50    private:
     51         static double s_theta_Unknown[NBIN] ;
     52         static double s_ce_Unknown[NBIN] ;
     53 
     54         static double s_theta_NNVT[NBIN] ;
     55         static double s_ce_NNVT[NBIN] ;
     56 
     57         static double s_theta_Hamamatsu[NBIN] ;
     58         static double s_ce_Hamamatsu[NBIN] ;



jcv PMTEfficencyTable
-----------------------

Uses PMTEfficiency as source of efficiencies for each sensor category across theta domain.

::

    013 PMTEfficiencyTable::PMTEfficiencyTable(const PMTEfficiency* eff )
     14     :
     15     m_eff(eff),
     16     m_theta_steps(90),
     17     m_phi_steps(1),
     18     m_theta_min(0.*deg),
     19     m_theta_max(90.*deg),
     20     m_phi_min(0.),
     21     m_phi_max(0.)
     22 {   
     23     init();
     24 }


    075 void PMTEfficiencyTable::initThetaValues()
     76 {
     77     m_values.clear();
     78 
     79     int* cats = m_eff->PMTCategories() ; // could be simcat or parcat enum values
     80 
     81     unsigned ni = m_eff->NumPMTCategories() ;
     82     unsigned nj = m_theta_domain.size() ;
     83     unsigned nk = 1 ; // no phi dependency  
     84     unsigned nl = 1 ; // multiplicity 
     85 
     86     unsigned size = ni*nj*nk*nl ;
     87     float fill = 0.f ;
     88     m_values.resize(size, fill );
     89 
     90     m_shape.push_back(ni);
     91     m_shape.push_back(nj);
     92     m_shape.push_back(nk);
     93     m_shape.push_back(nl);
     94 
     95     for(unsigned i=0 ; i < ni ; i++)
     96     {
     97         int cat = cats[i] ;
     98 
     99         // cats array defines the order of the items in the table 
    100         // hmm the cat used when querying the texture must be in same 
    101         // enum type as the one used here 
    102 
    103         for(unsigned j=0 ; j < nj ; j++)
    104         {
    105             double theta = m_theta_domain[j] ;
    106             for(unsigned k=0 ; k < nk ; k++)
    107             {
    108                 unsigned offset = i*nj*nk + j*nk + k  ;
    109 
    110                 double value = m_eff->getEfficiency(theta, cat) ;
    ...
    122                 m_values[offset] = float(value);
    123             }
    124         }
    125     }
    126 }



jcv LSExpDetectorConstruction_Opticks 
---------------------------------------

Sensor efficiencies and angular efficiencies are passed to Opticks via G4Opticks interface

* non-angular efficiency collection relies on G4PVPlacement::GetCopyNo providing the pmtid
  and then uses this to lookup values for all PMTs::

    junoSD_PMT_v2::getPMTCategory(pmtid)
    junoSD_PMT_v2::getQuantumEfficiency(pmtid)
    junoSD_PMT_v2::getEfficiencyScale()

* theta dependent efficiency uses::

    junoSD_PMT_v2::getPMTEfficiencyTable 


::

    110     // 2. use the placements to pass sensor data : efficiencies, categories, identifiers  
    111 
    112     const junoSD_PMT_v2* sd = dynamic_cast<const junoSD_PMT_v2*>(sd_) ;
    113     assert(sd) ;
    114 
    115     LOG(info) << "[ setSensorData num_sensor " << num_sensor ;
    116     for(unsigned i=0 ; i < num_sensor ; i++)
    117     {
    118         const G4PVPlacement* pv = sensor_placements[i] ; // i is 0-based unlike sensor_index
    119         unsigned sensor_index = 1 + i ; // 1-based 
    120         assert(pv);
    121         G4int copyNo = pv->GetCopyNo();
    122         int pmtid = copyNo ;
    123         int pmtcat = sd->getPMTCategory(pmtid);
    124         float efficiency_1 = sd->getQuantumEfficiency(pmtid);
    125         float efficiency_2 = sd->getEfficiencyScale() ;
    126 
    127         g4ok->setSensorData( sensor_index, efficiency_1, efficiency_2, pmtcat, pmtid );

    /// notice that the sensor category type associated with the sensor is used to lookup the
    /// appropriate line of angular efficiency from the theta texture : so the PMT category enum 
    /// used here must be the same as that used in PMTEfficiencyTable

    128     }
    129     LOG(info) << "] setSensorData num_sensor " << num_sensor ;
    130 
    131     // 3. pass theta dependent efficiency tables for all sensor categories 
    132 
    133     PMTEfficiencyTable* pt = sd->getPMTEfficiencyTable();
    134     assert(pt);
    135 
    136     const std::vector<int>& shape = pt->getShape();
    137     const std::vector<float>& data = pt->getData();
    138 
    139     int   theta_steps = pt->getThetaSteps();
    140     float theta_min = pt->getThetaMin();
    141     float theta_max = pt->getThetaMax();
    142     LOG(info)
    143          << "[ setSensorAngularEfficiency "
    144          << " theta_steps " << theta_steps
    145          << " theta_min " << theta_min
    146          << " theta_max " << theta_max
    147          ;
    148  
    149     g4ok->setSensorAngularEfficiency(shape, data, theta_steps, theta_min, theta_max);
    150     LOG(info) << "] setSensorAngularEfficiency " ;
    151 
    152     g4ok->saveSensorLib("$TMP/LSExpDetectorConstruction__SetupOpticks/SensorLib") ; // just for debug 



    

