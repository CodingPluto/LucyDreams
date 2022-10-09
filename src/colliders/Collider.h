#ifndef SRC_COLLIDER_H
#define SRC_COLLIDER_H
#include <SDL2/SDL.h>
#include "../components/Component.h"
#include "../Position.h"
#define DEBUG_COLLISION 1

enum CollisionType{CIRCULAR_COLLISION = 1, AABB_COLLISION = 2};


class Collider : public Component
{
private:
    void resetCollision();
    void update();
protected:
    Collider(class Sprite *owner);
    Collider();
    virtual void debugCollision() = 0;
    virtual void updateDimensions() = 0;
    virtual void AABBCollision() = 0;
    virtual void circularCollision() = 0;

    std::vector<class AABBCollider*> AABBCollidedObjects;
    std::vector<class CircularCollider*> circularCollidedObjects;

    unsigned short colliderID;
    bool collided;
public:
    bool isColliding();
    Position2 position;
    void checkCollision(CollisionType collisionType);
    std::vector<class AABBCollider*> *AABBColliders;
    std::vector<class CircularCollider*> *circularColliders;
    void setAABBColliders(std::vector<class AABBCollider*> &newColliders);
    void setCircularColliders(std::vector<class CircularCollider*> &newColliders);
    void setColliderID(unsigned short newID);
    unsigned short getColliderID();
    std::vector<AABBCollider*> getAABBCollidedObjects();
    std::vector<CircularCollider*> getCircularCollidedObjects();
};


#endif