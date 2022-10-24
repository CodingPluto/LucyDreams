#ifndef SRC_CLOUDS_PLATFORM_PLACER_H
#define SRC_CLOUDS_PLATFORM_PLACER_H
#include "../GameObject.h"

class PlatformPlacer : public GameObject
{
private:
    std::vector<class CloudPlatform*> myPlatforms;
    std::vector<class AABBCollider*> &colliders;
    CloudPlatform *activeCloudPlatform = nullptr;
    std::vector<CloudPlatform *>::iterator activeCloudPlatformIter;
    bool hasActiveCloudPlatform;
    int framesSinceLastClick = 0;
    void outputPlatformsToFile();
public:
    PlatformPlacer(std::vector<class AABBCollider*> &colliders);
    ~PlatformPlacer();
    void update();

};


#endif