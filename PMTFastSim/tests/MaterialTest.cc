#include <cassert>
#include <iostream>
#include "Material.h"

int main(int argc, char** argv)
{
    Material* a = new Material("a"); 
    Material* b = new Material("b"); 

    Material* a2 = Material::GetMaterial("a") ; 
    assert( a2 == a ); 

    Material* b2 = Material::GetMaterial("b") ; 
    assert( b2 == b ); 

    std::cout << " a2.GetName " << a2->GetName() << std::endl ; 
    std::cout << " b2.GetName " << b2->GetName() << std::endl ; 
   
   return 0 ; 

}
