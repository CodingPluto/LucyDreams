#include "../handlers/ImageHandler.h"
#include "../handlers/DisplayHandler.h"
#include "../handlers/WindowHandler.h"
#include "../cameras/SpriteCamera.h"
#include "ImageComponent.h"
#include "../gameData/Sprite.h"
using namespace std;

SDL_Texture* ImageComponent::getLoadedImage(string path)
{
    SDL_Texture *imageTexture;
    try
    {
        imageTexture = game->imageHandler->getImageTexture(path);
    }
    catch (const exception &e)
    {
        game->imageHandler->loadImage(path);
        imageTexture = game->imageHandler->getImageTexture(path);
    }
    return imageTexture;
}
void ImageComponent::setImage(string imageName)
{
    SDL_Texture *imageTexture = getLoadedImage(imageName);
    SDL_QueryTexture(imageTexture,nullptr,nullptr,&textureWidth,&textureHeight);
    this->imageName = imageName;
    if (!imageComponentInitalized)
    {
        game->imageHandler->addImageDrawer(this);
        imageComponentInitalized = true;
        game->imageHandler->reloadImageDrawerProrities();
    }
    if (cameraInstance)
    {
        cameraInstance->onImageSet();
    }
}

void ImageComponent::setCameraInstance(SpriteCamera *camera)
{
    cameraInstance = camera;
}

void ImageComponent::update()
{}

void ImageComponent::updateImageRect()
{
    imgRect.x = owner->getX() + (imageOffset.x * getScale());
    imgRect.y = owner->getY() + (imageOffset.y * getScale());
    imgRect.w = textureWidth * getScale();
    imgRect.h = textureHeight * getScale();
}

void ImageComponent::displayDebug()
{
    game->imageHandler->drawRect(&imgRect,{25, 18, 100,50},false,false);
    SDL_Rect corner;
    corner.x = imgRect.x;
    corner.y = imgRect.y;
    corner.w = getScale() * 2;
    corner.h = getScale() * 2;
    game->imageHandler->drawRect(&corner,{237, 0, 0,50},false,true);
}

ImageComponent::ImageComponent(Sprite *sprite):Component(sprite)
{
    setDebugName("ImageComponent");
    drawPriority = 100;
    imageComponentInitalized = false;
    imageName = "";
    isImageFlipped = SDL_FLIP_NONE;
    shown = true;
}

ImageComponent::~ImageComponent()
{
    game->imageHandler->removeImageDrawer(this);
}
void ImageComponent::setImageFlip(SDL_RendererFlip status)
{
    isImageFlipped = status;
}
SDL_RendererFlip ImageComponent::getFlippedStatus()
{
    return isImageFlipped;
}

void ImageComponent::setImageOffset(Position2 offset)
{
    imageOffset = offset;
}
Position2 ImageComponent::getImageOffset()
{
    return imageOffset;
}

void ImageComponent::draw()
{
    if (shown)
    {
        updateImageRect();
        game->imageHandler->drawImage(&imgRect,imageName,owner->getIsPositionRelative(),isImageFlipped);
        if (game->debugMode)
        {
            displayDebug();
        }
    }
}

void ImageComponent::show()
{
    shown = true;
}
void ImageComponent::hide()
{
    shown = false;
}

int ImageComponent::getDrawOrder()
{
    return drawPriority;
}

void ImageComponent::setDrawOrder(int priority)
{
    drawPriority = priority;
    game->imageHandler->reloadImageDrawerProrities();
}

std::string ImageComponent::getImageName()
{
    return imageName;
}

float ImageComponent::getWidth()
{
    return textureWidth * getScale();
}

float ImageComponent::getHeight()
{
    return textureHeight * getScale();
}