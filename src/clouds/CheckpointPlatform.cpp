#include "CheckpointPlatform.h"

using namespace std;

CheckpointPlatform::CheckpointPlatform(vector<AABBCollider*> &colliders, float yPosition):CloudPlatform(colliders)
{
    position.y = yPosition;
    position.x = cloudTileWidth - cloudTileWidth / (float)6; 
    image.setImage("bigCloud.png");
    collider.setRawWidth(cloudTileWidth * 35);
}

CheckpointPlatform::~CheckpointPlatform()
{}