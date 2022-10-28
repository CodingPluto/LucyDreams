#include <SDL2/SDL.h>
#include "../handlers/WindowHandler.h"
#include "../handlers/ImageHandler.h"
#include "../components/ImageComponent.h"
#include "Camera.h"
#include "../gameData/Sprite.h"
using namespace std;



Camera::Camera()
{
    cout << "Camera Created." << endl;
}


Position2 Camera::cameraUpdate()
{
    return position;
}

const std::string* Camera::getSceneOwner()
{
    return nullptr;
}