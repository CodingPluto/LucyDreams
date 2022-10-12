#ifndef SRC_CLOUD_PLATFORM_H
#define SRC_CLOUD_PLATFORM_H
#include "Sprite.h"
#include "components/ImageComponent.h"
#include "colliders/AABBCollider.h"
class CloudPlatform : public Sprite
{
private:
    ImageComponent image;
    const int cloudLength;
    const int cloudType;
public:
    AABBCollider collider;
    CloudPlatform(std::vector<class AABBCollider*> &colliders, Position2 setPosition = {-1,-1});
    ~CloudPlatform();
    void update();

};


#endif