junoPMTOpticalModel
======================


Tree of dependencies
------------------------

from gather.sh::


   Matrix.h  : TComplex.h              # MATRIX, Matrix
   Matrix.cc : Matrix.h  

   Material.h  : TComplex.h 
   Material.cc : Material.h            #  static material map 

   Layer.h   : Matrix.h Material.h      # Layer, ThickLayer, ThinLayer 
   Layer.cc  : Layer.h  



   OpticalSystem.h  :   Layer.h         # vector of layers with ThickLayer top_layer bot_layer    
   OpticalSystem.cc :   TString.h       # TMath::Sin TMath::Cos TMath::Sqrt TComplex::Sqrt TString?Form 



   MultiFilmModel.h  :  TComplex.h           #   ART
   MultiFilmModel.cc :  MultiFilmModel.h Matrix.h OpticalSystem.h    # contains optical_system and Matrix Ms Mp  TComplex::Conjugate
                 

   junoPMTOpticalModel.h  : many G4 headers, Sniper, Svcs and MultiFilmSimSvc/MultiFilmModel.h   m_multi_film_model
   junoPMTOpticalModel.cc : m_multi_film_model = new MultiFilmModel(4);



junoPMTOpticalModel.cc
------------------------


* UGLY : for every G4FastStep lots of lookups and model rejig because indices depend in wavelength
* it would be more efficient and cleaner for the model to hold arrays of properties for all wavelengths

::


    165 void junoPMTOpticalModel::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
    166 {
    167     const G4Track* track = fastTrack.GetPrimaryTrack();
    168 
    169     int pmtid  = get_pmtid(track);
    170     int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
    171    
    172     _photon_energy  = energy;
    173     _wavelength     = twopi*hbarc/energy;
    174     n_glass         = _rindex_glass->Value(_photon_energy);
    175    
    176     _qe             = m_PMTSimParSvc->get_pmtid_qe(pmtid, energy);
    177 
    178     n_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_RINDEX", _photon_energy);
    179     k_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_KINDEX", _photon_energy);
    180     d_coating       = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "ARC_THICKNESS")/m;
    181 
    182     n_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_RINDEX", _photon_energy);
    183     k_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_KINDEX", _photon_energy);
    184     d_photocathode  = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "PHC_THICKNESS")/m;
    185 
    186     if(whereAmI == kInGlass){
    187         _n1 = n_glass;
    188         _n2 = n_coating;
    189         _k2 = k_coating;
    190         _d2 = d_coating;
    191         _n3 = n_photocathode;
    192         _k3 = k_photocathode;
    193         _d3 = d_photocathode;
    194         _n4 = n_vacuum;
    195     }else{
    196         _n1 = n_vacuum;
    197         _n2 = n_photocathode;
    198         _k2 = k_photocathode;
    199         _d2 = d_photocathode;
    200         _n3 = n_coating;
    201         _k3 = k_coating;
    202         _d3 = d_coating;
    203         _n4 = n_glass;
    204 
    205         _qe = 0.;
    206     }
    207     pos  += dist1*dir;
    208     time += dist1*_n1/c_light;
    209 
    210     UpdateTrackInfo(fastStep);
    211 
    212     fastTrack.GetPrimaryTrack()->GetStep()
    213         ->GetPostStepPoint()->SetStepStatus(fGeomBoundary);
    214 
    215     norm = _inner1_solid->SurfaceNormal(pos);
    216     if(whereAmI == kInGlass){
    217         norm *= -1.0;
    218     }
    219 
    220     _cos_theta1 = dir*norm;
    221 
    222     if(_cos_theta1 < 0.){
    223         _cos_theta1 = -_cos_theta1;
    224         norm = -norm;
    225     }
    226     _aoi = acos(_cos_theta1)*360./twopi;
    227 
    228     CalculateCoefficients();
    229 
    230     G4double T  = 0.;
    231     G4double R  = 0.;
    232     G4double A  = 0.;
    233     G4double An = 0.;
    234     G4double escape_fac = 0.;
    235     G4double E_s2 = 0.;
    236 
    237     if(_sin_theta1 > 0.){
    238         E_s2 = (pol*dir.cross(norm))/_sin_theta1;
    239         E_s2 *= E_s2;
    240     }else{
    241         E_s2 = 0.;
    242     }
    243 
    244     T = fT_s*E_s2 + fT_p*(1.0-E_s2);
    245     R = fR_s*E_s2 + fR_p*(1.0-E_s2);
    246     A = 1.0 - (T+R);
    247 
    248     An = 1.0 - (fT_n+fR_n);
    249     escape_fac  = _qe/An;
    250 
    251     if(escape_fac > 1.){
    252         G4cout<<"junoPMTOpticalModel: QE is larger than absorption coeff."<<G4endl;
    253     }
    254 
    255     G4double rand_absorb = G4UniformRand();
    256     G4double rand_escape = G4UniformRand();
    257 
    258     if(rand_absorb < A){
    259         // absorbed
    260         fastStep.ProposeTrackStatus(fStopAndKill);
    261         if(rand_escape<escape_fac){
    262         // detected
    263             fastStep.ProposeTotalEnergyDeposited(_photon_energy);
    264         }


Because the indices depend on wavelength are rejiging the model at every step:: 

    285 void junoPMTOpticalModel::CalculateCoefficients()
    286 {
    287     G4complex one(1., 0.);
    288     _sin_theta1 = sqrt(1.-_cos_theta1*_cos_theta1);
    289     _sin_theta4 = _n1 * _sin_theta1/_n4;
    290     _cos_theta4 = sqrt(one-_sin_theta4*_sin_theta4);
    291 
    292     m_multi_film_model->SetWL(_wavelength/m);
    293     m_multi_film_model->SetAOI(_aoi);
    294 
    295     m_multi_film_model->SetLayerPar(0, _n1);
    296     m_multi_film_model->SetLayerPar(1, _n2, _k2, _d2);
    297     m_multi_film_model->SetLayerPar(2, _n3, _k3, _d3);
    298     m_multi_film_model->SetLayerPar(3, _n4);
    299     ART art1 = m_multi_film_model->GetART();
    300     fR_s = art1.R_s;
    301     fT_s = art1.T_s;
    302     fR_p = art1.R_p;
    303     fT_p = art1.T_p;
    304 
    305     m_multi_film_model->SetLayerPar(0, n_glass);
    306     m_multi_film_model->SetLayerPar(1, n_coating, k_coating, d_coating);
    307     m_multi_film_model->SetLayerPar(2, n_photocathode, k_photocathode, d_photocathode);
    308     m_multi_film_model->SetLayerPar(3, n_vacuum);
    309     ART art2 = m_multi_film_model->GetNormalART();
    310     fR_n = art2.R;
    311     fT_n = art2.T;
    312 }

