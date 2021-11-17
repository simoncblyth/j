#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "ZCanvas.hh"

ZCanvas::ZCanvas(int width_, int height_, int xscale_, int yscale_ )
    :
    verbose(getenv("VERBOSE")!=nullptr),
    xscale(xscale_), 
    yscale(yscale_),
    nx(0),
    ny(0),
    c(nullptr)
{
    resize(width_, height_); 
}

void ZCanvas::resize(int width_, int height_)
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
    for(int y=0 ; y < ny ; y++) for(int x=0 ; x < nx ; x++)  c[y*nx+x] = ' ' ;   
    for(int y=0 ; y < ny ; y++) c[y*nx+nx-1] = '\n' ;   
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
    char tmp[8] ;
    int rc = snprintf(tmp, 8,"%d", val );
    assert( rc == int(strlen(tmp)) );
    _draw(ix, iy, dx, dy, tmp); 
}

void ZCanvas::draw(int ix, int iy, int dx, int dy, float val )
{
    char tmp[8] ;
    int rc = snprintf(tmp, 8, "%-6.1f", val );
    assert( rc == int(strlen(tmp)) );
    _draw(ix, iy, dx, dy, tmp); 
}
void ZCanvas::draw(int ix, int iy, int dx, int dy, double val)
{
    char tmp[8] ;
    int rc = snprintf(tmp, 8, "%-6.1f", val );
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
    if( ix < 0 ) ix += width ; 
    if( iy < 0 ) iy += height ; 

    if( ix >= width )  printf("ZCanvas::_draw FATAL ix>=width  ix %d width %d \n", ix, width ); 
    if( iy >= height ) printf("ZCanvas::_draw FATAL iy>=height iy %d height %d \n", iy, height ); 

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

const char* ZCanvas::desc() const 
{
    char msg[200] ; 
    snprintf(msg, 200, "ZCanvas::desc width %d height %d xscale %d yscale %d nx %d ny %d", width, height, xscale, yscale, nx, ny ); 
    return strdup(msg); 
}

