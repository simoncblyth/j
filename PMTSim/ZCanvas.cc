#include <cassert>
#include <cstring>
#include <cstdio>

#include "ZCanvas.hh"

ZCanvas::ZCanvas(unsigned width, unsigned height)
    :
    xscale(8), 
    yscale(4),  
    nx(width*(xscale+1)),
    ny(height*(yscale+1)),
    c(new char[nx*ny+1])  // +1 for string termination
{
    clear(); 
}

void ZCanvas::clear()
{
    for(unsigned y=0 ; y < ny ; y++) for(unsigned x=0 ; x < nx ; x++)  c[y*nx+x] = ' ' ;   
    for(unsigned y=0 ; y < ny ; y++) c[y*nx+nx-1] = '\n' ;   
    c[nx*ny] = '\0' ;  // string terminate 
}

void ZCanvas::draw(int ix, int iy, int val, int dy )
{
    int x = ix*xscale ; 
    int y = iy*yscale + dy ; 

    char tmp[10] ;
    int rc = sprintf(tmp, "%d", val );
    assert( rc == int(strlen(tmp)) );
    _draw(x, y, tmp); 
}

void ZCanvas::draw(int ix, int iy, const char* txt, int dy)   // 0,0 is at top left 
{
    int x = ix*xscale ; 
    int y = iy*yscale + dy ; 
    _draw(x, y, txt); 
}

void ZCanvas::_draw(int x, int y, const char* txt)   // 0,0 is at top left 
{
    memcpy( c + y*nx + x , txt, strlen(txt) );
    // memcpy to avoid string termination 
    // hmm: drawing near the righthand side may stomp on newlines
    // hmm: drawing near bottom right risks writing off the end of the canvas
}

void ZCanvas::print(const char* msg) const 
{
    if(msg) printf("%s\n", msg); 
    printf("\n%s",c);
}


