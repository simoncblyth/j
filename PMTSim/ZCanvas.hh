#pragma once

struct ZCanvas
{
    unsigned width ; 
    unsigned height ; 
    unsigned xscale ; 
    unsigned yscale ; 
    unsigned nx ; 
    unsigned ny ; 
    char* c ; 

    ZCanvas( unsigned width, unsigned height ); 
    void resize(unsigned width, unsigned height); 
    void clear(); 
    void drawtest(); 

    void draw(  int ix, int iy, int dx, int dy, int val);
    void drawch(int ix, int iy, int dx, int dy, char ch);
    void draw(  int ix, int iy, int dx, int dy, const char* txt);
    void _draw(  int x, int y,  int dx, int dy, const char* txt);      // 0,0 is at top left 

    void print(const char* msg=nullptr) const ; 
};


