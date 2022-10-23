#ifndef SRC_COLLIDERS_AABB_COLLIDER_H
#define SRC_COLLIDERS_AABB_COLLIDER_H
#include "Collider.h"

class AABBCollider : public Collider
{
private:
    float rawWidth;
    float rawHeight;
    Position2 rawOffset;
public:
    Position2 getAdjustedPosition();
    ~AABBCollider();
    float width;
    float height;
    Position2 offset;
    
    AABBCollider(float x, float y, float width, float height, class Sprite *owner = nullptr);
    AABBCollider(SDL_Rect rect, class Sprite *owner = nullptr);
    void setRawWidth(float newWidth);
    void setRawHeight(float newHeight);
    void setRawOffset(Position2 offset);
    void setAABBColliders(std::vector<class AABBCollider*> &newColliders);
    void debugCollision() final;
    void AABBCollision() final;
    void circularCollision() final;
    void updateDimensions() final;
    bool isOverlapping(const AABBCollider *collider);
};



#endif