#include "MultiFilmModel.h"

#include "Matrix.h"
#include "OpticalSystem.h"

#include <cassert>

MultiFilmModel::MultiFilmModel(int n_layer)
{
    optical_system = new OpticalSystem(n_layer);

    Ms = new Matrix(TComplex(1.,0.), TComplex(0.,0.), TComplex(0.,0.), TComplex(1.,0.));
    Mp = new Matrix(TComplex(1.,0.), TComplex(0.,0.), TComplex(0.,0.), TComplex(1.,0.));
}

MultiFilmModel::~MultiFilmModel()
{
}

void MultiFilmModel::Calculate()
{
    if(wavelength == 0){
        std::cout<<"MultiFilmModel: WAVELENGTH not set!!!"<<std::endl;
        assert(0);
    }

    optical_system->Initialize(wavelength, theta);
    std::vector<Layer*> layers  = optical_system->GetLayers();

    Ms->Reset();
    Mp->Reset();
    
    for(std::size_t i=0;i<layers.size();i++){
        Ms->dot(layers[i]->GetMs());
        Mp->dot(layers[i]->GetMp());
    }
    
    MATRIX ms = Ms->GetM();
    MATRIX mp = Mp->GetM();

    TComplex rs = ms.M10/ms.M00;
    TComplex rp = mp.M10/mp.M00;
    TComplex ts = 1./ms.M00;
    TComplex tp = 1./mp.M00;

    ThickLayer *top = optical_system->GetTop();
    ThickLayer *bot = optical_system->GetBot();
    
    TComplex n1 = top->GetMaterial()->GetRefractiveIndex();
    TComplex n2 = bot->GetMaterial()->GetRefractiveIndex();
    TComplex cos_theta_1 = top->parameter.cos_theta;
    TComplex cos_theta_2 = bot->parameter.cos_theta;

    art.R_s = rs*TComplex::Conjugate(rs);
    art.R_p = rp*TComplex::Conjugate(rp);
    art.T_s = (n2*cos_theta_2)/(n1*cos_theta_1)*ts*TComplex::Conjugate(ts);
    art.T_p = (TComplex::Conjugate(n2)*cos_theta_2)/(TComplex::Conjugate(n1)*cos_theta_1)*tp*TComplex::Conjugate(tp);
    art.A_s = 1.-art.R_s-art.T_s;
    art.A_p = 1.-art.R_p-art.T_p;
    art.R   = (art.R_s+art.R_p)/2.;
    art.T   = (art.T_s+art.T_p)/2.;
    art.A   = (art.A_s+art.A_p)/2.;
}

void MultiFilmModel::SetLayerPar(int i, double n_val, double k_val, double d)
{
    optical_system->GetLayer(i)
                  ->GetMaterial()
                  ->SetRefractiveIndex(n_val, k_val);

    if(optical_system->GetLayer(i)->GetType() == fThin){
        dynamic_cast<ThinLayer*>(optical_system->GetLayer(i))
                                               ->SetThickness(d);
    }
}

ART MultiFilmModel::GetART()
{
    this->Calculate();
    return art;
}

ART MultiFilmModel::GetNormalART()
{
    this->SetAOI(0.);
    this->Calculate();
    return art;
}
