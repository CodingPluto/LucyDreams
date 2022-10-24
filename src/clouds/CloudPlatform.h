#ifndef SRC_CLOUDS_CLOUD_PLATFORM_H
#define SRC_CLOUDS_CLOUD_PLATFORM_H
#include "../gameData/Sprite.h"
#include "../components/ImageComponent.h"
#include "../colliders/AABBCollider.h"
class CloudPlatform : public Sprite
{
private:
    void construct();
protected:
    static const unsigned int cloudUpdatePosition = 50U;
    static const unsigned int cloudHeight = 12U;
    static const unsigned int cloudTileWidth = 12U;
    ImageComponent image;
    int cloudLength = 0;
    int cloudType = 1;
    int movementRange = 0;
    float movementSpeed = 0;
    float sinPoint = 0;
public:
    void setCloudLength(unsigned int cloudLength);
    const float &getMovementSpeed();
    const int getCloudLength();
    const int getCloudType();
    AABBCollider collider;
    CloudPlatform(std::vector<class AABBCollider*> &colliders, Position2 setPosition, unsigned int cloudLength, int movementRange = 0);
    CloudPlatform(std::vector<class AABBCollider*> &colliders);
    virtual ~CloudPlatform();
    void update();

};


#endif