#ifndef SRC_DISPLAY_HANDLER_H
#define SRC_DISPLAY_HANDLER_H
#include "Handler.h"
#include "../Colour.h"
class DisplayHandler : public Handler
{
private:
    class WindowHandler *windowHandler;
    class SDL_Renderer *renderer;
    class SDL_Window *window;
public:
    DisplayHandler(class WindowHandler *windowHandler);
    void setWindowTarget(class SDL_Window* window);
    bool initalize();
    HandlerError* tick();
    void drawRect(class SDL_Rect *rect, ColourRGBA rgba);
    void drawFilledRect(class SDL_Rect *rect, ColourRGBA rgba);
    void setDrawColour(ColourRGBA rgba);
    void linkToImageHandler(class ImageHandler *imageHandler);

};
#endif