#ifndef MultiFilmModel_h
#define MultiFilmModel_h 1

#include "TComplex.h"

class Matrix;
class OpticalSystem;

struct ART
{
    double R_s;
    double R_p;
    double T_s;
    double T_p;
    double A_s;
    double A_p;
    double R;
    double T;
    double A;
};

class MultiFilmModel
{
    public:
        MultiFilmModel(int n_layer);
        ~MultiFilmModel();

        void SetWL(double wl) { wavelength = wl; }
        void SetAOI(double angle) { theta = angle; }
        void SetLayerPar(int i, double n_val, double k_val = 0, double d = 0);

        void Calculate();

        ART GetART();
        ART GetNormalART();

        OpticalSystem* GetOpticalSystem() { return optical_system; }
        
    private:
        OpticalSystem* optical_system;
        
        double wavelength;
        double theta;

        ART art;

        Matrix* Ms;
        Matrix* Mp;
};

#endif
