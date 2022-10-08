#ifndef SRC_PLATFORMER_COLLSION
#define SRC_PLATFORMER_COLLISION
#include "../Sprite.h"
#include "AABBCollider.h"

enum Touching
{
    COLL_FLOOR = 0,
    COLL_RIGHT_WALL = 1,
    COLL_CEILING = 2,
    COLL_LEFT_WALL = 3
};

class PlatformerCollision : public Sprite
{
private:

protected:
    AABBCollider collisionChecker;
    bool touching[4];



public:
    PlatformerCollision(float w, float h, std::vector<AABBCollider*> &colliderGroup);
    void moveAndCollide();
    void outputCollisions();
    bool touchingWall();
};


#endif