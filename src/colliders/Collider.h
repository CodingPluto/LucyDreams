#ifndef SRC_COLLIDER_H
#define SRC_COLLIDER_H
#include <SDL2/SDL.h>
#include "../components/Component.h"
#include "../utils/Position.h"

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
    Position2 position;
    virtual ~Collider();
    bool isColliding();
    void checkCollision(CollisionType collisionType);
    std::vector<class AABBCollider*> *AABBColliders;
    std::vector<class CircularCollider*> *circularColliders;
    void setCircularColliders(std::vector<class CircularCollider*> &newColliders);
    void setColliderID(unsigned short newID);
    unsigned short getColliderID();
    std::vector<AABBCollider*> getAABBCollidedObjects();
    std::vector<CircularCollider*> getCircularCollidedObjects();
};


#endif