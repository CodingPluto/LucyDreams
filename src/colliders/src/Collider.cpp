#include "../Collider.h"
#include "../../Sprite.h"
#include "../AABBCollider.h"
using namespace std;

void Collider::resetCollision()
{
    collided = false;
}

bool Collider::isColliding()
{
    return collided;
}

void Collider::checkCollision(CollisionType collisionType)
{
    resetCollision();
    switch(collisionType)
    {
        case AABB_COLLISION:
            AABBCollidedObjects.clear();
            if (AABBColliders)
            {
                AABBCollision();
            }
            break;
        case CIRCULAR_COLLISION:
            circularCollidedObjects.clear();
            if (circularColliders)
            {
                circularCollision();
            }
            break;
        default:
            throw out_of_range("You entered an enum value that wasn't accounted for!!");
    }
}

void Collider::update()
{
    cout << "Updating!" << endl;
    if (DEBUG_COLLISION)
    {
        debugCollision();
    }
}


Collider::Collider(Sprite *owner):Component(owner),AABBColliders(nullptr),circularColliders(nullptr)
{
    cout << "Collider created!" << endl;
    collided = false;
}
Collider::Collider():AABBColliders(nullptr),circularColliders(nullptr)
{
    collided = false;
}

void Collider::setAABBColliders(std::vector<class AABBCollider*> &newColliders)
{
    AABBColliders = &newColliders;
}
void Collider::setCircularColliders(std::vector<class CircularCollider*> &newColliders)
{
    circularColliders = &newColliders;
}
void Collider::setColliderID(unsigned short newID)
{
    colliderID = newID;
}
unsigned short Collider::getColliderID()
{
    return colliderID;
}

vector<AABBCollider*> Collider::getAABBCollidedObjects()
{
    return AABBCollidedObjects;
}

vector<CircularCollider*> Collider::getCircularCollidedObjects()
{
    return circularCollidedObjects;
}
