#pragma once

struct ZCanvas
{
    bool verbose ; 
    int width ; 
    int height ; 
    int xscale ; 
    int yscale ; 
    int nx ; 
    int ny ; 
    char* c ; 

    ZCanvas( int width, int height, int xscale, int yscale ); 
    void resize(int width, int height); 
    void clear(); 
    void drawtest(); 

    void draw(  int ix, int iy, int dx, int dy, int val);
    void draw(  int ix, int iy, int dx, int dy, float val);
    void draw(  int ix, int iy, int dx, int dy, double val);
    void drawch(int ix, int iy, int dx, int dy, char ch);
    void draw(  int ix, int iy, int dx, int dy, const char* txt);
    void _draw(  int x, int y,  int dx, int dy, const char* txt);      // 0,0 is at top left 

    void print(const char* msg=nullptr) const ; 
    const char* desc() const ; 

};


