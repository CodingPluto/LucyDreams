#include "allScenes.h"
#include "gameData/GameObject.h"
#include "lucy/Lucy.h"
#include "clouds/PlatformPlacer.h"
#include "clouds/CheckpointPlatform.h"
#include "colliders/AABBCollider.h"
using namespace std;

vector<AABBCollider*> colliders;

void firstScene(vector<GameObject*> *dynamicGameObjects)
{
    dynamicGameObjects->emplace_back(new Lucy(colliders));
    dynamicGameObjects->emplace_back(new PlatformPlacer(colliders));
    dynamicGameObjects->emplace_back(new CheckpointPlatform(colliders, 300));
}

void secondScene(vector<GameObject*> *dynamicGameObjects)
{
    //dynamicGameObjects->emplace_back(new Lucy());
    dynamicGameObjects->emplace_back(new PlatformPlacer(colliders));
}