#include <SDL2/SDL.h>
#include <iostream>
#include "../InputHandler.h"
#include "../../Position.h"
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

    mouseButtonsPressed = SDL_GetMouseState(&mousePosition.first, &mousePosition.second);
    leftClickLastFrame = leftClickThisFrame;
    rightClickLastFrame = rightClickThisFrame;
    leftClickThisFrame = false;
    rightClickThisFrame = false;
    if ((mouseButtonsPressed & SDL_BUTTON_LMASK) != 0)
    {
        leftClickThisFrame = true;
    }
    if ((mouseButtonsPressed & SDL_BUTTON_RMASK) != 0)
    {
        rightClickThisFrame = true;
    }
    return nullptr;
}


bool InputHandler::initalize()
{
    leftClickLastFrame = false;
    rightClickLastFrame = false;
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


const bool InputHandler::isLMBPress()
{
    return leftClickThisFrame;
}
const bool InputHandler::isRMBPress()
{
    return rightClickThisFrame;
}
const bool InputHandler::isLMBOneClick()
{
    return (!leftClickLastFrame && leftClickThisFrame);
}
const bool InputHandler::isRMBOneClick()
{
    return (!rightClickLastFrame && rightClickThisFrame);
}

const unsigned int InputHandler::getMouseX()
{
    return mousePosition.first;
}
const unsigned int InputHandler::getMouseY()
{
    return mousePosition.second;
}

InputHandler::InputHandler(): Handler(hp_OnInput)
{
    debugName = "Input Handler";
}


InputHandler::~InputHandler()
{}