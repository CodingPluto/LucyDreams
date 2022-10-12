#include "../PlatformerCollision.h"
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
                if (previousPosition.x + collisionChecker.width <= collider->position.x)
                {
                    position.x = (collider->position.x - collisionChecker.width);
                    touching[COLL_RIGHT_WALL] = true;
                }
                else if (previousPosition.x >= collider->position.x + collider->width)
                {
                    position.x = (collider->position.x + collider->width);
                    touching[COLL_LEFT_WALL] = true;
                }
                else if (previousPosition.y + collisionChecker.height <= collider->position.y)
                {
                    position.y = (collider->position.y - collisionChecker.height);
                    touching[COLL_FLOOR] = true;
                }
                else if (previousPosition.y >= collider->position.y + collider->height)
                {
                    position.y = (collider->position.y + collider->height);
                    touching[COLL_CEILING] = true;
                }
                else
                {
                    position = previousPosition;
                }
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