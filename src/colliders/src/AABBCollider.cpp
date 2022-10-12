#include "../AABBCollider.h"
#include "../../handlers/ImageHandler.h"
#include "../../handlers/CameraHandler.h"
#include "../../Sprite.h"

using namespace std;

void AABBCollider::debugCollision()
{
    SDL_Rect rect;
    rect.x = position.x;
    rect.y = position.y;
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
    cout << "AABB Collider created!" << endl;
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
    return (position.x < collider->position.x + collider->width &&
            position.x + width > collider->position.x &&
            position.y < collider->position.y + collider->height &&
            position.y + height > collider->position.y);
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
    }
    else
    {
        width = rawWidth;
        height = rawHeight;
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