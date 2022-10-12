#include <SDL2/SDL.h>
#include "Sprite.h"
#include "handlers/ImageHandler.h"
#include "handlers/CameraHandler.h"
// Public functions
Sprite::Sprite()
{
    scale = 1;
    isPositionRelative = true;
    setDebugName("Sprite");
}
bool Sprite::getIsPositionRelative()
{
    return isPositionRelative;
}

void Sprite::displayPosition()
{
    SDL_Rect rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.w = scale * 10;
    rect.h = scale * 10;
    game->imageHandler->drawRect(&rect,{0, 237, 0, 50},isPositionRelative,false);
}

Position2 Sprite::getPreviousPosition()
{
    return previousPosition;
}

Position2 Sprite::getAbsolutePosition()
{
    if (isPositionRelative)
    {
        return position - game->cameraHandler->getCameraOffset();
    }
    return position;
}

void Sprite::syncPositions()
{
    previousPosition.x = position.x;
    previousPosition.y = position.y;
}
// Position
Position2 Sprite::getPosition()
{
    return position;
}
float Sprite::getX()
{
    return position.x;
}
float Sprite::getY()
{
    return position.y;
}
void Sprite::setPosition(float x, float y)
{
    setX(x);
    setY(y);
}
void Sprite::setPosition(Position2 position)
{
    this->position = position;
}
void Sprite::setX(float x)
{
    position.x = x;
}
void Sprite::setY(float y)
{
    position.y = y;
}
void Sprite::changeX(float x)
{
    position.x += x;
}
void Sprite::changeY(float y)
{
    position.y += y;
}
void Sprite::changePosition(float x, float y)
{
    changeX(x);
    changeY(y);
}
void Sprite::changePosition(Position2 position)
{
    this->position += position;
}

// Scale
float Sprite::getScale()
{
    return scale;
}