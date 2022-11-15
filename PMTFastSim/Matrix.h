#ifndef Matrix_h
#define Matrix_h 1

#include <iostream>
#include "TComplex.h"

struct MATRIX
{
    TComplex M00;
    TComplex M01;
    TComplex M10;
    TComplex M11;
};

class Matrix{
    public:
        Matrix(TComplex m00, TComplex m01, TComplex m10, TComplex m11);
        ~Matrix(){};

        void dot(Matrix* m);

        void   SetM(TComplex M00, TComplex M01, TComplex M10, TComplex M11);
        MATRIX GetM() { return matrix; }

        void Reset();
        void Print();

    public:
        MATRIX matrix;
};

#endif
