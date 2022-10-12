#ifndef SRC_PLATFORM_PLACER_H
#define SRC_PLATFORM_PLACER_H
#include "GameObject.h"

class PlatformPlacer : public GameObject
{
private:
    std::vector<class CloudPlatform*> myPlatforms;
    std::vector<class AABBCollider*> &colliders;
    int framesSinceLastClick = 0;
public:
    PlatformPlacer(std::vector<class AABBCollider*> &colliders);
    ~PlatformPlacer();
    void update();

};


#endif