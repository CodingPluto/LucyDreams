#include <SDL2/SDL.h>
#include "../WindowHandler.h"
#include "../ImageHandler.h"
#include "../../components/ImageComponent.h"
#include "../Camera.h"
#include "../../Sprite.h"
using namespace std;

Camera::Camera(Sprite *owner, ImageComponent *image): owner(owner)
{
    this->image = image;
    textureWidth = 0;
    textureHeight = 0;
    image->setCameraInstance(this);
    st = st_All;
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

void Camera::setCameraScrollingType(st__ScrollingType newSt)
{
    st = newSt;
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
        //cout << textureWidth << endl;
        //cout << textureHeight << endl;
        camOffset = {0,0};
        switch(st)
        {
            case st_All:
                camOffset.x = owner->getX() - owner->game->windowHandler->getScreenWidth()/2 + (textureWidth * image->getScale())/2;
                camOffset.y = owner->getY() - owner->game->windowHandler->getScreenHeight()/2 + (textureHeight * image->getScale())/2;
                break;
            case st_HoriziontalOnly:
                camOffset.x = owner->getX() - owner->game->windowHandler->getScreenWidth()/2 + (textureWidth * image->getScale())/2;
                break;
            case st_VerticalOnly:
                camOffset.y = owner->getY() - owner->game->windowHandler->getScreenHeight()/2 + (textureHeight * image->getScale())/2;
                break;
            default:
                break;
        }
    }
    return camOffset;
}