#include "../AABBCollider.h"
#include "../../handlers/ImageHandler.h"
#include "../../handlers/CameraHandler.h"
#include "../../Sprite.h"

using namespace std;

void AABBCollider::debugCollision()
{
    SDL_Rect rect;
    rect.x = position.x + game->cameraHandler->getCameraOffset().x;
    rect.y = position.y + game->cameraHandler->getCameraOffset().y;
    rect.w = width;
    rect.h = height;
    cout << "debugged collision!" << endl;
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

AABBCollider::AABBCollider(float x, float y, float width, float height, Sprite *owner): Collider(owner)
{
    position.x = x;
    position.y = y;
    this->width = width;
    this->height = height;
    cout << "AABB Collider created!" << endl;
}

AABBCollider::AABBCollider(SDL_Rect rect,Sprite *owner): Collider(owner)
{
    position.x = rect.x;
    position.y = rect.y;
    this->width = rect.w;
    this->height = rect.h;
}

void AABBCollider::AABBCollision()
{
    for (auto const &collider : *AABBColliders)
    {
        cout << "checking for collisions" << endl;
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
