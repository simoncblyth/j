#include <iostream>
#include "TComplex.h"

int main(int argc, char** argv)
{
   TComplex a(0, 1) ; 
   std::cout << " a " << a << std::endl ; 

   TComplex b = a ;  
   std::cout << " b " << b << std::endl ; 

   TComplex c = a*b ;  
   std::cout << " c " << c << std::endl ; 


   TComplex z(1,2) ; 
   TComplex y = _TComplex::Conjugate(z) ;  

   TComplex z_y = z*y ; 
   TComplex norm_z = std::norm(z) ; 
   double norm_z2 = std::norm(z) ; 

   std::cout << " z_y " << z_y << std::endl ; 
   std::cout << " norm_z " << norm_z << std::endl ; 
   std::cout << " norm_z2 " << norm_z2 << std::endl ; 


   return 0 ;  
}
