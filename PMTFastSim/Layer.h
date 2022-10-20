#ifndef Layer_h
#define Layer_h 1

#include "Matrix.h"
#include "Material.h"

enum LayerType { fThin, fThick };

class Layer
{
    public:
        struct LayerParameter
        {
            TComplex sin_theta;
            TComplex cos_theta;
            TComplex rs_ij;
            TComplex rp_ij;
            TComplex ts_ij;
            TComplex tp_ij;
        };

        Layer(std::string name);
        virtual ~Layer();
        
        Matrix* GetMs() { return Ms; }
        Matrix* GetMp() { return Mp; }

        void SetMs(TComplex M00, TComplex M01, TComplex M10, TComplex M11)
        { Ms->SetM(M00, M01, M10, M11); }
        void SetMp(TComplex M00, TComplex M01, TComplex M10, TComplex M11)
        { Mp->SetM(M00, M01, M10, M11); }

        Material* GetMaterial() { return material; }

        void SetType(LayerType t) { type = t; }
        LayerType GetType() { return type; }

        LayerParameter parameter;

        void ResetMatrix();

    private:
        Material* material;

        LayerType type;

        Matrix* Ms;
        Matrix* Mp;
};

#endif

#ifndef ThickLayer_h
#define ThickLayer_h 1

class ThickLayer : public Layer
{
    public:
        ThickLayer(std::string name);
        ~ThickLayer();
};

#endif

#ifndef ThinLayer_h
#define ThinLayer_h 1

class ThinLayer : public Layer
{
    public:
        ThinLayer(std::string name, double d = 0.);
        ~ThinLayer();

        void SetThickness(double x) { thickness = x; }
        double GetThickness() { return thickness; }
    
    private:
        double thickness;
};

#endif
