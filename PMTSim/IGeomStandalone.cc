#include <cstring>
#include "IGeomStandalone.h"

bool IGeomStandalone::StartsWithPrefix(const char* name, const char* prefix)  // static
{
    return strlen(name) >= strlen(prefix) && strncmp( name, prefix, strlen(prefix)) == 0 ;  
}

