#ifndef SRC_COLLIDERS_AABB_COLLIDER_H
#define SRC_COLLIDERS_AABB_COLLIDER_H
#include "Collider.h"

class AABBCollider : public Collider
{
private:
public:
    float width;
    float height;
    AABBCollider(float x, float y, float width, float height, class Sprite *owner = nullptr);
    AABBCollider(SDL_Rect rect, class Sprite *owner = nullptr);
    void debugCollision() final;
    void AABBCollision() final;
    void circularCollision() final;
    bool isOverlapping(const AABBCollider *collider);
};



#endif