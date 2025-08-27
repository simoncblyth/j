
#include <string>
#include <DataPathHelper/Path.hh>
#include <iostream>

int main(int argc, char** argv)
{
    std::string f = argc > 1 ? argv[1] : "dummy.txt" ;
    std::string p = JUNO::Path::resolve(f);
    std::cout << p << "\n" ;
    return 0 ; 
}



