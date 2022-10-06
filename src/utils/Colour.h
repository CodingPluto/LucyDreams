#ifndef SRC_COLOUR_RGB_H
#define SRC_COLOUR_RGB_H
#include <iostream>
class ColourRGBA
{
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    ColourRGBA():r(0),g(0),b(0),a(255){}
    ColourRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a): r(r), g(g), b(b),a(a){}
    friend std::ostream& operator<<(std::ostream& os, ColourRGBA colour)
    {
        std::cout << "RGBA{" << (int)colour.r << "," << (int)colour.g << "," << (int)colour.b << "," << (int)colour.a << "}";
        return std::cout;
    }
};

#endif