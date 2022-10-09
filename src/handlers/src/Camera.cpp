#include <SDL2/SDL.h>
#include "../WindowHandler.h"
#include "../ImageHandler.h"
#include "../../components/ImageComponent.h"
#include "../Camera.h"
#include "../../Sprite.h"
using namespace std;

Camera::Camera(Sprite *owner, ImageComponent *image): owner(owner)
{
    cout << "Camera Created." << endl;
    this->image = image;
    textureWidth = 0;
    textureHeight = 0;
    image->setCameraInstance(this);
}

void Camera::onImageSet()
{
    SDL_Texture *imageTexture;
    std::string imageName = image->getImageName();
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
    cout << textureWidth << endl;
    cout << textureHeight << endl;
    if (owner != nullptr)
    {
        camOffset.x = owner->getX() - owner->game->windowHandler->getScreenWidth()/2 + (textureWidth * image->getScale())/2;
        camOffset.y = owner->getY() - owner->game->windowHandler->getScreenHeight()/2 + (textureHeight * image->getScale())/2;
    }
    return camOffset;
}