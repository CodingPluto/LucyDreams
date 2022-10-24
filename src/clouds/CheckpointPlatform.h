#ifndef SRC_CLOUDS_CHECKPOINT_PLATFORM_H
#define SRC_CLOUDS_CHECKPOINT_PLATFORM_H
#include "CloudPlatform.h"

class CheckpointPlatform : public CloudPlatform
{

public:
    CheckpointPlatform(std::vector<AABBCollider*> &colliders, float xPosition);
    ~CheckpointPlatform();

};


#endif