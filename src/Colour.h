#ifndef SRC_COLOUR_RGB_H
#define SRC_COLOUR_RGB_H

typedef unsigned char byte;
class ColourRGBA
{
public:
    byte r;
    byte g;
    byte b;
    byte a;
    ColourRGBA():r(0),g(0),b(0),a(255){}
    ColourRGBA(byte r, byte g, byte b, byte a): r(r), g(g), b(b),a(a){}
};

#endif