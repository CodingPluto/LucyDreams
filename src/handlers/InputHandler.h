#ifndef SRC_HANDLERS_INPUT_HANDLER_H
#define SRC_HANDLERS_INPUT_HANDLER_H
#include "Handler.h"
class InputHandler : Handler
{
private:
    HandlerError *tick();
    bool initalize();
    const bool *keysPressed;
    bool keysPressedLastFrame[SDL_NUM_SCANCODES];
    bool keysJustPressed[SDL_NUM_SCANCODES];
public:
    const bool keyPressed(SDL_Scancode keyID);
    const bool keyJustPressed(SDL_Scancode keyID);
    InputHandler();
    ~InputHandler();
};


#endif