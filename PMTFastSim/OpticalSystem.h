#ifndef OpticalSystem_h
#define OpticalSystem_h 1

#include <iostream>
#include <vector>

#include "Layer.h"

class OpticalSystem
{
    public:
        OpticalSystem(int n_layer);
        ~OpticalSystem();

        void AddLayer(ThinLayer* aLayer);
        void Initialize(double wl, double theta);

        void Calculate_rt(Layer* layeri, Layer* layerj);
    
        void SetTop(ThickLayer* aLayer) { top_layer = aLayer; }
        void SetBot(ThickLayer* aLayer) { bot_layer = aLayer; }

        ThickLayer* GetTop() { return top_layer; }
        ThickLayer* GetBot() { return bot_layer; }
        
        Layer* GetLayer(int i) { return layers[i]; }
        std::vector<Layer*> GetLayers() { return layers; }

        void ResetLayers();
        void PrintInfo();

    public:
        ThickLayer* top_layer;
        ThickLayer* bot_layer;

        std::vector<Layer*> layers;
};

#endif
