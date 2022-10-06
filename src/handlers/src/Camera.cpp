#include <SDL2/SDL.h>
#include "../WindowHandler.h"
#include "../ImageHandler.h"
#include "../Camera.h"
#include "../../Sprite.h"
using namespace std;

Camera::Camera(Sprite *owner, std::string imageName): owner(owner)
{
    cout << "Camera Created." << endl;
    SDL_Texture *imageTexture;
    try
    {
        imageTexture = owner->game->imageHandler->getImageTexture(imageName);
    }
    catch (const exception &e)
    {
        cout << "The image \'" << imageName << "\' was not loaded." << endl;
        cout << "Loading \'" << imageName << "\'" << endl;
        owner->game->imageHandler->loadImage(imageName);
        imageTexture = owner->game->imageHandler->getImageTexture(imageName);
    }
    SDL_QueryTexture(imageTexture,nullptr,nullptr,&textureWidth,&textureHeight);
}
Camera::Camera()
{
    owner = nullptr;
    cout << "Camera Created." << endl;
}


Position2 Camera::cameraUpdate()
{
    if (owner != nullptr)
    {
        camOffset.x = owner->getX() - owner->game->windowHandler->getScreenWidth()/2 + (textureWidth * owner->getScale())/2;
        camOffset.y = owner->getY() - owner->game->windowHandler->getScreenHeight()/2 + (textureHeight * owner->getScale())/2;
    }
    return camOffset;
}