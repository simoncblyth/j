// ./NPFoldTest.sh 

#include "NPFold.h"

int main()
{
    NPFold* fold = NPFold::Load("$PMTSimParamData_BASE/PMTSimParamData") ; 
    std::cout << " fold " << fold->desc() << std::endl ; 
    return 0 ; 
}  



