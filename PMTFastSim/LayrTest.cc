#include "Layr.h"

int main(int argc, char** argv)
{
    Stack<4> stk ; 

    Layr& l0 = stk.ll[0]; 
    Layr& l1 = stk.ll[1]; 
    Layr& l2 = stk.ll[2]; 
    Layr& l3 = stk.ll[3]; 

    l0.n.real(1.0) ; l0.n.imag(0.0)  ; l0.d = 0. ; 
    l1.n.real(1.0) ; l1.n.imag(0.01) ; l1.d = 500. ; // nm (same length unit as wavelength)
    l2.n.real(1.0) ; l2.n.imag(0.01) ; l2.d = 500. ;          
    l3.n.real(1.5) ; l3.n.imag(0.0)  ; l3.d = 0. ; 

    double wl = 500. ;  // nm 
    double theta = 0. ;  // radians M_PI/2. ;  
    stk.computeART(wl, theta); 

    std::cout << stk << std::endl ; 

    return 0 ; 
}
