#include <cassert>
#include "MultiFilmModel.h"



struct MultiFilmModelTest
{
    /*
    double _photon_energy;
    double _wavelength;
    double _aoi;
    */
    double _n1;
    double _n2, _k2, _d2;
    double _n3, _k3, _d3;
    double _n4;
    /*
    double _qe;

    double n_glass;
    double n_vacuum;
    double n_coating;
    double k_coating;
    double d_coating;
    double n_photocathode;
    double k_photocathode;
    double d_photocathode;
    */

    double _sin_theta1;
    double _cos_theta1;
    std::complex<double> _sin_theta4;
    std::complex<double> _cos_theta4;

    double fR_s;
    double fT_s;
    double fR_p;
    double fT_p;
    double fR_n;

    MultiFilmModel* m_multi_film_model;
    MultiFilmModelTest() ; 
    void getART(); 
};



MultiFilmModelTest::MultiFilmModelTest()
    :
    _n1(1.),
    _n2(1.2),_k2(0.2),_d2(0.01),
    _n3(1.2),_k3(0.2),_d3(0.01),    // TODO: get some realistic values 
    _n4(1.5),
    _sin_theta1(0.),
    _cos_theta1(0.),
    _sin_theta4(0.,0.),
    _cos_theta4(0.,0.),
    fR_s(0.),
    fT_s(0.),
    fR_p(0.),
    fT_p(0.),
    fR_n(0.),
    m_multi_film_model(new MultiFilmModel(4))
{
    //m_multi_film_model->SetWL(_wavelength);   // remove /m  : HMM 
    //m_multi_film_model->SetAOI(_aoi);
    m_multi_film_model->SetLayerPar(0, _n1);
    m_multi_film_model->SetLayerPar(1, _n2, _k2, _d2);
    m_multi_film_model->SetLayerPar(2, _n3, _k3, _d3);
    m_multi_film_model->SetLayerPar(3, _n4);
}

void MultiFilmModelTest::getART()
{
    ART art1 = m_multi_film_model->GetART();
    fR_s = art1.R_s;
    fT_s = art1.T_s;
    fR_p = art1.R_p;
    fT_p = art1.T_p;
}

 

int main(int argc, char** argv)
{
    MultiFilmModelTest t ; 
    t.getART(); 

    return 0 ; 
}
