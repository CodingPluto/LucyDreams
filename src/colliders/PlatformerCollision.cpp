#include "PlatformerCollision.h"
using namespace std;


void PlatformerCollision::moveAndCollide()
{
    touching[COLL_LEFT_WALL] = false;
    touching[COLL_RIGHT_WALL] = false;
    touching[COLL_FLOOR] = false;
    touching[COLL_CEILING] = false;
    collisionChecker.position = position;
    collisionChecker.checkCollision(AABB_COLLISION);
    if (collisionChecker.isColliding())
    {
        for (AABBCollider* &collider : collisionChecker.getAABBCollidedObjects())
        {
            if (collisionChecker.isOverlapping(collider))
            {
                if (getAdjustedPreviousPosition().x + collisionChecker.width <= collider->getAdjustedPosition().x)
                {
                    if (collisionEnabled[COLL_RIGHT_WALL])
                    {
                        position.x = (collider->getAdjustedPosition().x - collisionChecker.width - collisionChecker.offset.x);
                    }
                    touching[COLL_RIGHT_WALL] = true;
                }
                else if (getAdjustedPreviousPosition().x >= collider->getAdjustedPosition().x + collider->width)
                {
                    if (collisionEnabled[COLL_LEFT_WALL])
                    {
                        position.x = (collider->getAdjustedPosition().x + collider->width - collisionChecker.offset.x);
                    }
                    touching[COLL_LEFT_WALL] = true;
                }
                if (getAdjustedPreviousPosition().y >= collider->getAdjustedPosition().y + collider->height)
                {
                    if (collisionEnabled[COLL_CEILING])
                    {
                        position.y = (collider->getAdjustedPosition().y + collider->height - collisionChecker.offset.y);
                    }
                    touching[COLL_CEILING] = true;
                }
                else if (getAdjustedPreviousPosition().y + collisionChecker.height <= collider->getAdjustedPosition().y)
                {
                    if (collisionEnabled[COLL_FLOOR])
                    {
                        position.y = (collider->getAdjustedPosition().y - collisionChecker.height - collisionChecker.offset.y);
                    }
                    touching[COLL_FLOOR] = true;
                }
                /*
                else
                {
                    position = previousPosition;
                }
                */
                collisionChecker.position = position;

            }
        }
    }
}

PlatformerCollision::PlatformerCollision(vector<AABBCollider*> &colliderGroup, float hitboxWidth, float hitboxHeight): collisionChecker(position.x,position.y,hitboxWidth,hitboxHeight,this)
{
    touching[COLL_LEFT_WALL] = false;
    touching[COLL_RIGHT_WALL] = false;
    touching[COLL_FLOOR] = false;
    touching[COLL_CEILING] = false;
    collisionEnabled[COLL_LEFT_WALL] = true;
    collisionEnabled[COLL_RIGHT_WALL] = true;
    collisionEnabled[COLL_FLOOR] = true;
    collisionEnabled[COLL_CEILING] = true;
    collisionChecker.setAABBColliders(colliderGroup);
    setUpdateOrder(50);
    colliderGroup.emplace_back(&collisionChecker);
    setDebugName("PlatformerCollision");
    /* If Seg Fault:
    You may have provided a malformed vector to the Platformer collision construction..
    Please check that the vector provided is not being constructed as this class is being created...
    your welcome, future me.
    */
}

Position2 PlatformerCollision::getAdjustedPreviousPosition()
{
    return previousPosition + collisionChecker.offset;
}

void PlatformerCollision::outputCollisions()
{
    cout << "LT WALL: " << touching[COLL_LEFT_WALL] << endl;
    cout << "RT WALL: " << touching[COLL_RIGHT_WALL] << endl;
    cout << "CEILING: " << touching[COLL_LEFT_WALL] << endl;
    cout << "FLOOR: " << touching[COLL_RIGHT_WALL] << endl;
}

bool PlatformerCollision::touchingWall()
{
    return (touching[COLL_LEFT_WALL] || touching[COLL_RIGHT_WALL]);
}

void PlatformerCollision::enableSpecificCollisions(Touching touching)
{
    collisionEnabled[touching] = true;
}

void PlatformerCollision::disableSpecificCollisions(Touching touching)
{
    collisionEnabled[touching] = false;
}