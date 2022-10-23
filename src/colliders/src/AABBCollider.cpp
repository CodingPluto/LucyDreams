#include "../AABBCollider.h"
#include "../../handlers/ImageHandler.h"
#include "../../handlers/CameraHandler.h"
#include "../../Sprite.h"

using namespace std;

void AABBCollider::debugCollision()
{
    SDL_Rect rect;
    rect.x = position.x + offset.x;
    rect.y = position.y + offset.y;
    rect.w = width;
    rect.h = height;
    bool relativePosition;
    if (owner)
    {
        relativePosition = owner->getIsPositionRelative();
    }
    else
    {
        relativePosition = true;
    }
    if (collided)
    {
        game->imageHandler->drawRect(&rect,{200,50,50,255},relativePosition,false);
    }
    else
    {
        game->imageHandler->drawRect(&rect,{100,100,100,255},relativePosition,false);
    }
}

AABBCollider::AABBCollider(float x, float y, float rawWidth, float rawHeight, Sprite *owner): Collider(owner)
{
    position.x = x;
    position.y = y;
    this->rawWidth = rawWidth;
    this->rawHeight = rawHeight;
    setDebugName("AABBCollider");
}

AABBCollider::AABBCollider(SDL_Rect rect,Sprite *owner): Collider(owner)
{
    position.x = rect.x;
    position.y = rect.y;
    this->width = rect.w;
    this->height = rect.h;
    setDebugName("AABBCollider");
}

void AABBCollider::AABBCollision()
{
    for (auto const &collider : *AABBColliders)
    {
        if (collider != this)
        {
            if (isOverlapping(collider))
            {
                AABBCollidedObjects.emplace_back(collider);
                collided = true;
            }
        }
    }
}

bool AABBCollider::isOverlapping(const AABBCollider *collider)
{
    return (position.x + offset.x < collider->position.x + collider->offset.x + collider->width &&
            position.x + offset.x + width > collider->position.x + collider->offset.x &&
            position.y + offset.y < collider->position.y + collider->offset.y + collider->height &&
            position.y + offset.y + height > collider->position.y + collider->offset.y);
}


void AABBCollider::circularCollision()
{
}


void AABBCollider::updateDimensions()
{
    if (owner)
    {
        width = rawWidth * getScale();
        height = rawHeight * getScale();
        offset = rawOffset * getScale();
    }
    else
    {
        width = rawWidth;
        height = rawHeight;
        offset = rawOffset;
    }
}

void AABBCollider::setRawWidth(float newWidth)
{
    rawWidth = newWidth;
}
void AABBCollider::setRawHeight(float newHeight)
{
    rawHeight = newHeight;
}
void AABBCollider::setAABBColliders(std::vector<class AABBCollider*> &newColliders)
{
    AABBColliders = &newColliders;
    AABBColliders->emplace_back(this);
}
void AABBCollider::setRawOffset(Position2 offset)
{
    rawOffset = offset;
}

Position2 AABBCollider::getAdjustedPosition()
{
    return {position.x + offset.x, position.y + offset.y};
}

AABBCollider::~AABBCollider()
{
    for (auto it = AABBColliders->begin(); it != AABBColliders->end(); ++it)
    {
        if (*it == this)
        {
            AABBColliders->erase(it);
            break;
        }
    }
}