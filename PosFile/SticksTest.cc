#include <iostream>
#include "Sticks.hh"

int main(int argc, char** argv)
{
    const char* member = argc > 1 ? argv[1] : nullptr ;

    if( member == nullptr )
    {
        std::cout << " expecting argument strings from the first member column " << std::endl ; 
        std::cout << std::endl << Sticks::TABLE << std::endl ; 
        return 0 ; 
    }

    const char* class_ = Sticks::GetClass(member) ;   
    const char* posfile = Sticks::GetPosFile(member) ;   
    const char* radius = Sticks::GetRadius(member) ;   
    const char* note = Sticks::GetNote(member) ;   

    std::cout 
        << " member " << member 
        << " radius " << ( radius ? radius : "-" ) 
        << " class_ " << ( class_ ? class_ : "-" ) 
        << " posfile " << ( posfile ? posfile : "-" ) 
        << " note " << ( note ? note : "-" ) 
        << std::endl
        ; 

    return 0 ; 
}
