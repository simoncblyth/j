// name=RadiusTest ; gcc $name.cc -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name  

#include "Radius.hh"

int main(int argc, char** argv)
{
    Radius::Dump(); 
    Radius::Save("/tmp/RadiusTest.npy"); 

    return 0 ; 
}
