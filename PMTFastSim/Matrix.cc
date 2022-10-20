#include "Matrix.h"

Matrix::Matrix(TComplex m00, TComplex m01, TComplex m10, TComplex m11)
{
    matrix.M00 = m00;
    matrix.M01 = m01;
    matrix.M10 = m10;
    matrix.M11 = m11;
}

void Matrix::dot(Matrix* m)
{
    MATRIX M = m->GetM();

    TComplex tmp00 = matrix.M00;
    TComplex tmp01 = matrix.M01;
    TComplex tmp10 = matrix.M10;
    TComplex tmp11 = matrix.M11;

    matrix.M00 = tmp00*M.M00 + tmp01*M.M10;
    matrix.M01 = tmp00*M.M01 + tmp01*M.M11;
    matrix.M10 = tmp10*M.M00 + tmp11*M.M10;
    matrix.M11 = tmp10*M.M01 + tmp11*M.M11;
}

void Matrix::SetM(TComplex M00, TComplex M01, TComplex M10, TComplex M11)
{
    matrix.M00 = M00;
    matrix.M01 = M01;
    matrix.M10 = M10;
    matrix.M11 = M11;
}

void Matrix::Reset()
{
    matrix.M00 = TComplex(1., 0.);
    matrix.M01 = TComplex(0., 0.);
    matrix.M10 = TComplex(0., 0.);
    matrix.M11 = TComplex(1., 0.);
}

void Matrix::Print()
{
    std::cout<<"{"<<matrix.M00<<" "<<matrix.M01<<std::endl;
    std::cout<<matrix.M10<<" "<<matrix.M11<<"}"<<std::endl;
}
