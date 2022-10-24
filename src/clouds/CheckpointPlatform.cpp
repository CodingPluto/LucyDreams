#include "CheckpointPlatform.h"
#include "../handlers/WindowHandler.h"
using namespace std;

CheckpointPlatform::CheckpointPlatform(vector<AABBCollider*> &colliders, float yPosition, string newSceneName):CloudPlatform(colliders),sceneName(newSceneName)
{
    position.y = yPosition;
    image.setImage("bigCloud.png");
    position.x = game->windowHandler->getCentreScreenX(image.getWidth());
    collider.setRawWidth(cloudTileWidth * 35);
    collider.addColliderTag("CloudPlatformCheckpoint");
}

CheckpointPlatform::~CheckpointPlatform()
{}