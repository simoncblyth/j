#include "Layer.h"

Layer::Layer(std::string name)
{
    material = Material::GetMaterial(name);

    Ms = new Matrix(TComplex(1.,0.), TComplex(0., 0.), TComplex(0., 0.), TComplex(1., 0.));
    Mp = new Matrix(TComplex(1.,0.), TComplex(0., 0.), TComplex(0., 0.), TComplex(1., 0.));
}

Layer::~Layer()
{
}

void Layer::ResetMatrix()
{
    Ms->Reset();
    Mp->Reset();
}

ThickLayer::ThickLayer(std::string name) : 
    Layer(name)
{
    SetType(fThick);
}

ThickLayer::~ThickLayer()
{
}

ThinLayer::ThinLayer(std::string name, double d) :
    Layer(name)
{
    SetType(fThin);
    thickness = d;
}

ThinLayer::~ThinLayer()
{
}
