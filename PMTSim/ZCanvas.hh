#pragma once

struct ZCanvas
{
    unsigned xscale ; 
    unsigned yscale ; 
    unsigned nx ; 
    unsigned ny ; 
    char* c ; 

    ZCanvas( unsigned width, unsigned height ); 
    void clear(); 
    void draw(int ix, int iy, int val, int dy); 
    void draw(int ix, int iy, const char* txt, int dy );
    void _draw(int x, int y, const char* txt);      // 0,0 is at top left 

    void print(const char* msg=nullptr) const ; 
};


