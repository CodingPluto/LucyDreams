#include "handlers/inc/ImageHandler.h"
#include "handlers/inc/DisplayHandler.h"
#include "handlers/inc/WindowHandler.h"
#include "handlers/inc/CameraHandler.h"
#include "ImageComponent.h"
#include "Sprite.h"
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
        cout << "The image \'" << path << "\' was not loaded." << endl;
        cout << "Loading \'" << path << "\'" << endl;
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
}

void ImageComponent::update()
{}

void ImageComponent::updateImageRect()
{
    imgRect.x = owner->getX() + (imageOffset.x * getScale()) - game->cameraHandler->getCameraOffset().x;
    imgRect.y = owner->getY() + (imageOffset.y * getScale()) - game->cameraHandler->getCameraOffset().y;
    imgRect.w = textureWidth * getScale();
    imgRect.h = textureHeight * getScale();
}

void ImageComponent::displayDebug()
{
    game->displayHandler->drawRect(&imgRect,{25, 18, 100,50});
    SDL_Rect corner;
    corner.x = imgRect.x;
    corner.y = imgRect.y;
    corner.w = getScale() * 2;
    corner.h = getScale() * 2;
    game->displayHandler->drawFilledRect(&corner,{237, 0, 0,50});
}

ImageComponent::ImageComponent(Sprite *sprite):Component(sprite)
{
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
        bool insideScreen =
        (imgRect.x < game->windowHandler->getScreenWidth())
        && (imgRect.x + imgRect.w > 0)
        && (imgRect.y < game->windowHandler->getScreenHeight())
        && (imgRect.y + imgRect.h > 0);
        if (insideScreen)
        {
            game->imageHandler->drawImage(&imgRect,imageName,isImageFlipped);
            if (VISUAL_DEGUG_MODE)
            {
                displayDebug();
            }
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
