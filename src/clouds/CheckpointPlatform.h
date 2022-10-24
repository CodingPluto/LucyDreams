#ifndef SRC_CLOUDS_CHECKPOINT_PLATFORM_H
#define SRC_CLOUDS_CHECKPOINT_PLATFORM_H
#include "CloudPlatform.h"

class CheckpointPlatform : public CloudPlatform
{

public:
    const std::string sceneName;
    CheckpointPlatform(std::vector<AABBCollider*> &colliders, float xPosition, std::string newSceneName);
    ~CheckpointPlatform();

};


#endif