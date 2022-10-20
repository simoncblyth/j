#include <cassert>
#include <iostream>
#include "Layer.h"


int main(int argc, char** argv)
{
    Material* a = new Material("a"); 
    assert( a ); 

    Material* b = new Material("b"); 
    assert( b ); 

    // need materials to avoid eg : "a not found !!!" from below

    Layer* thick = new ThickLayer("a"); 
    Layer* thin  = new ThinLayer("b"); 
 
    assert( thick ); 
    assert( thin ); 

    return 0 ; 
}
