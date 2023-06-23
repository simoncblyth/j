#include <iostream>
#include "C4MultiLayrStack.h"

void test_StackSpec_serialize()
{
    StackSpec<double, 4> ss0 ;  
    ss0.ls[0] = {0.50, 0.51, 0.52, 0.0 } ; 
    ss0.ls[1] = {0.60, 0.61, 0.62, 0.0 } ; 
    ss0.ls[2] = {0.70, 0.71, 0.72, 0.0 } ; 
    ss0.ls[3] = {0.80, 0.81, 0.82, 0.0 } ; 
    std::cout << " ss0 " << ss0 << std::endl ; 

    std::array<double, 16> aa0 ; 
    ss0.serialize(aa0); 
    std::cout << " aa0 " << aa0 ; 

    StackSpec<double, 4> ss1 ; 
    ss1.import(aa0); 
    std::cout << " ss1 " << ss1 << std::endl ; 
}

void test_StackSpec_is_equal()
{
    StackSpec<double, 4> ss0 ;  
    ss0.ls[0] = {0.50, 0.51, 0.52, 0.0 } ; 
    ss0.ls[1] = {0.60, 0.61, 0.62, 0.0 } ; 
    ss0.ls[2] = {0.70, 0.71, 0.72, 0.0 } ; 
    ss0.ls[3] = {0.80, 0.81, 0.82, 0.0 } ; 
    std::cout << " ss0 " << ss0 << std::endl ; 

    StackSpec<double, 4> ss1(ss0); 
    std::cout << " ss1 " << ss1 << std::endl ; 

    ss1.ls[3].ni = 0.99 ;  // change smth to test is_equal finds it 

    bool eq = ss0.is_equal(ss1) ; 
    std::cout << " is_equal " << eq << std::endl ; 

    std::cout << ss0.desc_compare(ss1) << std::endl ; 
}

int main(int argc, char** argv)
{
    test_StackSpec_serialize(); 
    test_StackSpec_is_equal(); 
    return 0 ; 
}
