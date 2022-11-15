#include "Matrix.h"

int main(int argc, char** argv)
{
    TComplex a(0,1) ; 
    TComplex b(1,0) ; 
    TComplex c(0,1) ; 
    TComplex d(1,1) ; 
    Matrix m(a, b, c, d) ; 

    m.Print();  

    return 0 ; 
}
