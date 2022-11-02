#ifndef SRC_PLATFORMER_COLLISION
#define SRC_PLATFORMER_COLLISION
#include "../gameData/Sprite.h"
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
    Position2 getAdjustedPreviousPosition();

protected:
    AABBCollider collisionChecker;
    bool touching[4];
    bool collisionEnabled[4];



public:
    PlatformerCollision(std::vector<AABBCollider*> &colliderGroup, float hitboxWidth, float hitboxHeight);
    void moveAndCollide();
    void outputCollisions();
    bool touchingWall();
    void enableSpecificCollisions(Touching touching);
    void disableSpecificCollisions(Touching touching);
};


#endif