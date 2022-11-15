#ifndef Material_h
#define Material_h 1

#include <iostream>
#include <map>

#include "TComplex.h"

class Material
{
    public:
        Material(std::string name, double n_value=1., double k_value=0.);
        ~Material();

        void SetRefractiveIndex(double n_new, double k_new = 0) { n = TComplex(n_new, k_new); }
        TComplex GetRefractiveIndex() { return n; }

        std::string GetName() { return fName; }
        static Material* GetMaterial(std::string name);

    public:
        std::string fName;

        TComplex n;
        static std::map<std::string, Material*> materials;

};

#endif
