#include "TString.h"
#include "OpticalSystem.h"

OpticalSystem::OpticalSystem(int n_layer)
{
    new Material("TopMaterial");
    top_layer = new ThickLayer("TopMaterial");
    new Material("BotMaterial");
    bot_layer = new ThickLayer("BotMaterial");
    
    layers.push_back(top_layer);
    layers.push_back(bot_layer);

    for(int i=0;i<n_layer-2;i++){
        std::string materialName = Form("layerMaterial%d", i);
        new Material(materialName);
        AddLayer(new ThinLayer(materialName));
    }
}

OpticalSystem::~OpticalSystem()
{
}

void OpticalSystem::AddLayer(ThinLayer* aLayer)
{
    std::vector<Layer*>::iterator it;
    it = layers.end();
    layers.insert(it-1, aLayer);
}

void OpticalSystem::ResetLayers()
{
    for(std::size_t i=0;i<layers.size();i++){
        layers[i]->ResetMatrix();
    }
}

/**


https://en.wikipedia.org/wiki/Fresnel_equations
See section "Complex amplitude reflection and transmission coefficients"

For s polarization, the reflection coefficient r is defined as the ratio of the
reflected wave's complex electric field amplitude to that of the incident wave,
whereas for p polarization r is the ratio of the waves complex magnetic field
amplitudes (or equivalently, the negative of the ratio of their electric field
amplitudes). The transmission coefficient t is the ratio of the transmitted
wave's complex electric field amplitude to that of the incident wave, for
either polarization. The coefficients r and t are generally different between
the s and p polarizations, and even at normal incidence (where the designations
s and p do not even apply!) the sign of r is reversed depending on whether the
wave is considered to be s or p polarized, an artifact of the adopted sign
convention (see graph for an air-glass interface at 0° incidence). 

**/

void OpticalSystem::Calculate_rt(Layer* layeri, Layer* layerj)
{
    TComplex ni = layeri->GetMaterial()->GetRefractiveIndex();
    TComplex nj = layerj->GetMaterial()->GetRefractiveIndex();
    
    layeri->parameter.rs_ij = (ni*layeri->parameter.cos_theta - nj*layerj->parameter.cos_theta)/(ni*layeri->parameter.cos_theta + nj*layerj->parameter.cos_theta);
    layeri->parameter.rp_ij = (nj*layeri->parameter.cos_theta - ni*layerj->parameter.cos_theta)/(nj*layeri->parameter.cos_theta + ni*layerj->parameter.cos_theta);
    layeri->parameter.ts_ij = (2.*ni*layeri->parameter.cos_theta)/(ni*layeri->parameter.cos_theta + nj*layerj->parameter.cos_theta);
    layeri->parameter.tp_ij = (2.*ni*layeri->parameter.cos_theta)/(nj*layeri->parameter.cos_theta + ni*layerj->parameter.cos_theta);
}


/**
OpticalSystem::Initialize
----------------------------

https://en.wikipedia.org/wiki/Thin-film_interference

https://en.wikipedia.org/wiki/Transfer-matrix_method_(optics)

In theoretical physics, a wave number, defined as the number of radians per unit distance, 
sometimes called "angular wavenumber", is more often used:[3]

          2*pi
    k =  -------
          lambda          lambda is the wavelength   (so units are reciprocal length eg m^-1 )


**/

void OpticalSystem::Initialize(double wl, double theta)
{
    ResetLayers();
    
    TComplex top_n = top_layer->GetMaterial()->GetRefractiveIndex();
    top_layer->parameter.sin_theta = TMath::Sin(theta*TMath::Pi()/180.);
    top_layer->parameter.cos_theta = TMath::Cos(theta*TMath::Pi()/180.);

    TComplex one = TComplex(1., 0.);
    TComplex zi  = TComplex(0., 1.);
    for(std::size_t i=1;i<layers.size();i++){
        TComplex layer_n = layers[i]->GetMaterial()->GetRefractiveIndex();
        layers[i]->parameter.sin_theta = top_n*top_layer->parameter.sin_theta/layer_n;
        layers[i]->parameter.cos_theta = _TComplex::Sqrt(one - layers[i]->parameter.sin_theta*layers[i]->parameter.sin_theta);
    }
    
    for(std::size_t i=0;i<layers.size()-1;i++){
        Calculate_rt(layers[i], layers[i+1]);
    }

    for(std::size_t i=1;i<layers.size();i++){
        TComplex tmps = 1./layers[i-1]->parameter.ts_ij;
        TComplex tmpp = 1./layers[i-1]->parameter.tp_ij;
        
        TComplex Ms_00, Ms_01, Ms_10, Ms_11;
        TComplex Mp_00, Mp_01, Mp_10, Mp_11;

        if(layers[i]->GetType() == fThin){
            ThinLayer* thin_layeri = dynamic_cast<ThinLayer*>(layers[i]);
            TComplex ni = thin_layeri->GetMaterial()->GetRefractiveIndex();
            double di = thin_layeri->GetThickness();

            TComplex delta = 2. * TMath::Pi() * ni * di * layers[i]->parameter.cos_theta / wl;
            
            Ms_00 = tmps * _TComplex::Exp(-zi*delta);
            Ms_01 = tmps * layers[i-1]->parameter.rs_ij * _TComplex::Exp(zi*delta);
            Ms_10 = tmps * layers[i-1]->parameter.rs_ij * _TComplex::Exp(-zi*delta);
            Ms_11 = tmps * _TComplex::Exp(zi*delta);

            Mp_00 = tmpp * _TComplex::Exp(-zi*delta);
            Mp_01 = tmpp * layers[i-1]->parameter.rp_ij * _TComplex::Exp(zi*delta);
            Mp_10 = tmpp * layers[i-1]->parameter.rp_ij * _TComplex::Exp(-zi*delta);
            Mp_11 = tmpp * _TComplex::Exp(zi*delta);
        }else{
            Ms_00 = tmps;
            Ms_01 = tmps * layers[i-1]->parameter.rs_ij;
            Ms_10 = tmps * layers[i-1]->parameter.rs_ij;
            Ms_11 = tmps;

            Mp_00 = tmpp;
            Mp_01 = tmpp * layers[i-1]->parameter.rp_ij;
            Mp_10 = tmpp * layers[i-1]->parameter.rp_ij;
            Mp_11 = tmpp;
        }

        layers[i]->SetMs(Ms_00, Ms_01, Ms_10, Ms_11);
        layers[i]->SetMp(Mp_00, Mp_01, Mp_10, Mp_11);
    }
}

void OpticalSystem::PrintInfo()
{
    for(std::size_t i=0;i<layers.size();i++){
        if(layers[i]->GetType() == fThin){
            std::cout<<"ThinLayer: "<<layers[i]->GetMaterial()->GetName()<<" "
                     <<layers[i]->GetMaterial()->GetRefractiveIndex()<<" "
                     <<dynamic_cast<ThinLayer*> (layers[i])->GetThickness()<<std::endl;
        }else{
            std::cout<<"ThickLayer: "<<layers[i]->GetMaterial()->GetName()<<" "
                     <<layers[i]->GetMaterial()->GetRefractiveIndex()<<std::endl;
        }
    }
}
