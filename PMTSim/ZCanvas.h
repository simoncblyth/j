#pragma once

/**
ZCanvas : ascii "painting"
==============================

Used for rendering CSG trees by ZSolid::Draw 

**/

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>

struct ZCanvas
{
    bool verbose ; 
    unsigned width ; 
    unsigned height ; 
    unsigned xscale ; 
    unsigned yscale ; 
    unsigned nx ; 
    unsigned ny ; 
    char* c ; 

    ZCanvas( unsigned width, unsigned height, unsigned xscale=8, unsigned yscale=4 );  
    void resize(unsigned width, unsigned height);
    void clear(); 
    void drawtest(); 

    void draw(   int ix, int iy, int dx, int dy, int val); 
    void drawch( int ix, int iy, int dx, int dy, char ch); 
    void draw(   int ix, int iy, int dx, int dy, const char* txt);
    void _draw(  int ix, int iy, int dx, int dy, const char* txt);      // 0,0 is at top left 

    void print(const char* msg=nullptr) const ; 
    const char* desc() const ; 
};


inline ZCanvas::ZCanvas(unsigned width_, unsigned height_, unsigned xscale_, unsigned yscale_)
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

inline void ZCanvas::resize(unsigned width_, unsigned height_)
{
    width = width_ ; 
    height = height_ ; 
    nx = width*xscale+1 ;   // +1 for the newline
    ny = height*yscale  ; 
    if(verbose)
    printf("ZCanvas::resize width %d height %d nx %d ny %d nx*ny %d xscale %d yscale %d \n", width, height, nx, ny, nx*ny, xscale, yscale ); 
    delete [] c ; 
    c  = new char[nx*ny+1] ;   // +1 for string termination
    clear(); 
}

inline void ZCanvas::clear()
{
    for(unsigned y=0 ; y < ny ; y++) for(unsigned x=0 ; x < nx ; x++)  c[y*nx+x] = ' ' ;   
    for(unsigned y=0 ; y < ny ; y++) c[y*nx+nx-1] = '\n' ;   
    c[nx*ny] = '\0' ;  // string terminate 
}

inline void ZCanvas::drawtest()
{
    for(int ix=0 ; ix < int(width) ;  ix++ )
    for(int iy=0 ; iy < int(height) ; iy++ )
    {
        for(int dx=0 ; dx < int(xscale) ; dx++)
        for(int dy=0 ; dy < int(yscale) ; dy++)
        {
            draw(ix,iy,dx,dy, dx);
        }
    } 
}

inline void ZCanvas::draw(int ix, int iy, int dx, int dy, int val)
{
    char tmp[10] ;
    int rc = sprintf(tmp, "%d", val );
    bool expect = rc == int(strlen(tmp)) ; 
    assert( expect );
    if(!expect) exit(EXIT_FAILURE) ; 

    _draw(ix, iy, dx, dy, tmp); 
}

inline void ZCanvas::drawch(int ix, int iy, int dx, int dy, char ch)  
{
    char tmp[2]; 
    tmp[0] = ch ; 
    tmp[1] = '\0' ; 
    _draw(ix, iy, dx, dy, tmp); 
}
inline void ZCanvas::draw(int ix, int iy, int dx, int dy, const char* txt)   
{
    _draw(ix, iy, dx, dy, txt); 
}

inline void ZCanvas::_draw(int ix, int iy, int dx, int dy, const char* txt)   // 0,0 is at top left 
{
    bool expect = ix < int(width) && iy < int(height) && dx < int(xscale) &&  dy < int(yscale) ; 
    assert(expect); 
    if(!expect) exit(EXIT_FAILURE); 

    int x = ix*xscale + dx ; 
    int y = iy*yscale + dy ; 
    int l = strlen(txt) ; 

    if(!( x + l < int(nx) && y < int(ny) ))
    {
        printf("ZCanvas::_draw error out of range x+l %d  nx %d  y %d ny %d \n", x+l, nx, y, ny ); 
        return ; 
    }

    int offset = y*nx + x ;  

    if(!(offset + l < int(nx*ny) ))
    {
        printf("ZCanvas::_draw error out of range offset+l %d  nx*ny %d \n", offset+l, nx*ny ); 
        return ; 
    }

    memcpy( c + offset , txt, l );
}

inline void ZCanvas::print(const char* msg) const 
{
    if(msg) printf("%s\n", msg); 
    if(verbose) 
        printf("\n[\n%s]\n",c);
    else 
        printf("\n%s",c);
}

inline const char* ZCanvas::desc() const 
{
    char msg[200] ; 
    snprintf(msg, 200, "ZCanvas::desc width %d height %d xscale %d yscale %d nx %d ny %d", width, height, xscale, yscale, nx, ny ); 
    return strdup(msg); 
}

