#include <SDL2/SDL.h>
#include <iostream>
#include "../InputHandler.h"
using namespace std;

HandlerError *InputHandler::tick()
{
    if (keysPressed[SDL_SCANCODE_W] && !keysPressedLastFrame[SDL_SCANCODE_W])
    {
        cout << "Key Just Pressed!" << ": " << SDL_SCANCODE_W << ": " << keysPressed[SDL_SCANCODE_W] << endl;
    }
    for (int keyID = 0; keyID < SDL_NUM_SCANCODES; ++keyID)
    {
        keysJustPressed[keyID] = (keysPressed[keyID] && !keysPressedLastFrame[keyID]);
        keysPressedLastFrame[keyID] = keysPressed[keyID];
    }
    return nullptr;
}


bool InputHandler::initalize()
{
    keysPressed = (const bool *)SDL_GetKeyboardState(0);
    return true;
}


const bool InputHandler::keyPressed(SDL_Scancode keyID)
{
    return keysPressed[keyID];
}
const bool InputHandler::keyJustPressed(SDL_Scancode keyID)
{
    return keysJustPressed[keyID];
}

InputHandler::InputHandler(): Handler(hp_OnInput)
{
    debugName = "Input Handler";
}


InputHandler::~InputHandler()
{}