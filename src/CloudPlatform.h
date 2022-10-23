#ifndef SRC_CLOUD_PLATFORM_H
#define SRC_CLOUD_PLATFORM_H
#include "Sprite.h"
#include "components/ImageComponent.h"
#include "colliders/AABBCollider.h"
class CloudPlatform : public Sprite
{
private:
    ImageComponent image;
    int cloudLength;
    int cloudType;
    char movementDirection;
    int movementRange;
    float movementSpeed;
    float sinPoint;
public:
    const float &getMovementSpeed();
    const int getCloudLength();
    const int getCloudType();
    void setCloudLength(unsigned int cloudLength);
    AABBCollider collider;
    CloudPlatform(std::vector<class AABBCollider*> &colliders, Position2 setPosition, unsigned int cloudLength, unsigned int cloudType, int movementRange = 0);
    CloudPlatform(std::vector<class AABBCOllider*> &colliders);
    ~CloudPlatform();
    void update();

};


#endif