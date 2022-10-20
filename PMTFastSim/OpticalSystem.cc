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

void OpticalSystem::Calculate_rt(Layer* layeri, Layer* layerj)
{
    TComplex ni = layeri->GetMaterial()->GetRefractiveIndex();
    TComplex nj = layerj->GetMaterial()->GetRefractiveIndex();
    
    layeri->parameter.rs_ij = (ni*layeri->parameter.cos_theta - nj*layerj->parameter.cos_theta)/(ni*layeri->parameter.cos_theta + nj*layerj->parameter.cos_theta);
    layeri->parameter.rp_ij = (nj*layeri->parameter.cos_theta - ni*layerj->parameter.cos_theta)/(nj*layeri->parameter.cos_theta + ni*layerj->parameter.cos_theta);
    layeri->parameter.ts_ij = (2.*ni*layeri->parameter.cos_theta)/(ni*layeri->parameter.cos_theta + nj*layerj->parameter.cos_theta);
    layeri->parameter.tp_ij = (2.*ni*layeri->parameter.cos_theta)/(nj*layeri->parameter.cos_theta + ni*layerj->parameter.cos_theta);
}

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
        layers[i]->parameter.cos_theta = TComplex::Sqrt(one - layers[i]->parameter.sin_theta*layers[i]->parameter.sin_theta);
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
            
            Ms_00 = tmps * TComplex::Exp(-zi*delta);
            Ms_01 = tmps * layers[i-1]->parameter.rs_ij * TComplex::Exp(zi*delta);
            Ms_10 = tmps * layers[i-1]->parameter.rs_ij * TComplex::Exp(-zi*delta);
            Ms_11 = tmps * TComplex::Exp(zi*delta);

            Mp_00 = tmpp * TComplex::Exp(-zi*delta);
            Mp_01 = tmpp * layers[i-1]->parameter.rp_ij * TComplex::Exp(zi*delta);
            Mp_10 = tmpp * layers[i-1]->parameter.rp_ij * TComplex::Exp(-zi*delta);
            Mp_11 = tmpp * TComplex::Exp(zi*delta);
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
