#include <iostream>
#include "SpriteCamera.h"
#include "../components/ImageComponent.h"
#include "../gameData/Sprite.h"
#include "../handlers/ImageHandler.h"
#include "../handlers/WindowHandler.h"

using namespace std;

SpriteCamera::SpriteCamera(Sprite *owner, ImageComponent *image): owner(owner), image(image)
{
    textureWidth = 0;
    textureHeight = 0;
    image->setCameraInstance(this);
    st = st_All;
}

void SpriteCamera::onImageSet()
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

void SpriteCamera::setCameraScrollingType(const st__ScrollingType &newSt)
{
    st = newSt;
}

void SpriteCamera::setCameraOffset(const Position2 &cameraOffset)
{
    this->cameraOffset = cameraOffset;
}

Position2 SpriteCamera::cameraUpdate()
{
    position = {0,0};
    switch(st)
    {
        case st_All:
            position.x = owner->getX() - owner->game->windowHandler->getScreenWidth()/2 + (textureWidth * image->getScale())/2;
            position.y = owner->getY() - owner->game->windowHandler->getScreenHeight()/2 + (textureHeight * image->getScale())/2;
            break;
        case st_HoriziontalOnly:
            position.x = owner->getX() - owner->game->windowHandler->getScreenWidth()/2 + (textureWidth * image->getScale())/2;
            break;
        case st_VerticalOnly:
            position.y = owner->getY() - owner->game->windowHandler->getScreenHeight()/2 + (textureHeight * image->getScale())/2;
            break;
        default:
            break;
    }
    position = position + cameraOffset;
    return position;
}
const string* SpriteCamera::getSceneOwner()
{
    return owner->sceneNamePtr;
}