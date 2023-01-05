// name=read_rootfile_without_root ; gcc $name.cc -std=c++11 -lstdc++ -I$HOME/np  -o /tmp/$name && /tmp/$name

#include <iostream>
#include <cstdlib>
#include "NP.hh"

int main(int argc, char** argv)
{
    const char* path = "$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root" ; 
    std::vector<char> buf ; 
    NP::LoadVec<char>(buf, path) ; 

    std::cout << " buf.size " << buf.size() << std::endl ; 

    return 0 ; 
} 
