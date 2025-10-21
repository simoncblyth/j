/**
~/j/hit_digest/md5_test.sh
**/

#include <string>
#include <cassert>

extern "C" { 
  #include "md5.cuh"
}

std::string DescDigest( unsigned char* digest16 )
{
    char buf[32+1] ;
    for (int n = 0; n < 16; ++n) std::snprintf( &buf[2*n], 32+1, "%02x", (unsigned int)digest16[n]) ;
    buf[32] = '\0' ;
    return std::string(buf, buf + 32);
}

int main()
{
    const char* m = "hello" ;

    int ni = 3 ;
    int nj = strlen(m);

    uint8_t* dat = new uint8_t[ni*nj] ;
    for(int i=0 ; i < ni; i++ ) 
    for(int j=0 ; j < nj; j++ ) 
    dat[i*nj + j] = m[j] ;

    BYTE* in = (BYTE*)dat ; 
    WORD inlen = nj ;   // size of each item
    WORD n_batch = ni ; // number of items

    uint8_t* digest = new uint8_t[16*ni] ; 
    BYTE* out = digest ; 

    mcm_cuda_md5_hash_batch(in, inlen, out, n_batch);

    for(int i=0 ; i < ni ; i++)
    { 
        std::string hexdigest = DescDigest( digest + 16*i );
        printf("// hexdigest [%d][%s]\n", i, hexdigest.c_str() );
    }

    return 0 ; 
}
