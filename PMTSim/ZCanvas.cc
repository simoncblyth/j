#include <cassert>
#include <cstring>
#include <cstdio>

#include "ZCanvas.hh"

ZCanvas::ZCanvas(unsigned width_, unsigned height_ )
    :
    xscale(8), 
    yscale(4),
    nx(0),
    ny(0),
    c(nullptr)
{
    resize(width_, height_); 
}

void ZCanvas::resize(unsigned width_, unsigned height_)
{
    width = width_ ; 
    height = height_ ; 

    if( width == 0 || height == 0 ) return ; 
    nx = width*xscale+1 ;      // +1 for newlines 
    ny = height*yscale ; 
    delete [] c ; 
    c  = new char[nx*ny+1] ;   // +1 for string termination
    clear(); 
}

void ZCanvas::clear()
{
    for(unsigned y=0 ; y < ny ; y++) for(unsigned x=0 ; x < nx ; x++)  c[y*nx+x] = ' ' ;   
    for(unsigned y=0 ; y < ny ; y++) c[y*nx+nx-1] = '\n' ;   
    c[nx*ny] = '\0' ;  // string terminate 
}

void ZCanvas::drawtest()
{
    for(int ix=0 ; ix < width ;  ix++ )
    for(int iy=0 ; iy < height ; iy++ )
    {
        for(int dx=0 ; dx < xscale ; dx++)
        for(int dy=0 ; dy < yscale ; dy++)
        {
            draw(ix,iy,dx,dy, dx);
        }
    }
}

void ZCanvas::draw(int ix, int iy, int dx, int dy, int val)
{
    char tmp[10] ;
    int rc = sprintf(tmp, "%d", val );
    assert( rc == int(strlen(tmp)) );
    _draw(ix, iy, dx, dy, tmp); 
}

void ZCanvas::drawch(int ix, int iy, int dx, int dy, char ch)  
{
    char tmp[2]; 
    tmp[0] = ch ; 
    tmp[1] = '\0' ; 
    _draw(ix, iy, dx, dy, tmp); 
}
void ZCanvas::draw(int ix, int iy, int dx, int dy, const char* txt)   
{
    _draw(ix, iy, dx, dy, txt); 
}

void ZCanvas::_draw(int ix, int iy, int dx, int dy, const char* txt)  
{
    assert( ix < width  );  
    assert( iy < height  );  
    assert( dx < xscale );  
    assert( dy < yscale );  

    int x = ix*xscale + dx ; 
    int y = iy*yscale + dy ; 
    int l = strlen(txt) ; 

    if(!( x + l < nx && y < ny ))
    {   
        printf("ZCanvas::_draw error out of range x+l %d  nx %d  y %d ny %d \n", x+l, nx, y, ny );  
        return ; 
    }   

    int offset = y*nx + x ;   

    if(!(offset + l < nx*ny ))
    {   
        printf("ZCanvas::_draw error out of range offset+l %d  nx*ny %d \n", offset+l, nx*ny );  
        return ; 
    }   

    memcpy( c + offset , txt, l );
}


void ZCanvas::print(const char* msg) const 
{
    if(msg) printf("%s\n", msg); 
    if(verbose) 
        printf("\n[\n%s]\n",c);
    else 
        printf("\n%s",c);
}




