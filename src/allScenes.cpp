#include "allScenes.h"
#include "gameData/GameObject.h"
#include "lucy/Lucy.h"
#include "clouds/PlatformPlacer.h"
#include "clouds/CheckpointPlatform.h"
#include "colliders/AABBCollider.h"
#include "platforms/Platform.h"
#include "handlers/WindowHandler.h"
using namespace std;

vector<AABBCollider*> colliders;


void awake1(vector<GameObject*> *dynamicGameObjects)
{
    dynamicGameObjects->emplace_back(new CheckpointPlatform(colliders, 300, ""));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{952.000000, 397.000000},5,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{623.000000, 425.000000},4,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{501.000000, 379.000000},5,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{342.000000, 392.000000},4,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{198.000000, 371.000000},3,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{201.000000, 419.000000},5,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{107.000000, 409.000000},3,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{807.000000, 361.000000},2,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{909.000000, 419.000000},4,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{32.000000, 380.000000},5,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{1064.000000, 328.000000},5,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{1177.000000, 388.000000},3,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{1126.000000, 241.000000},3,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{955.000000, 189.000000},3,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{805.000000, 62.000000},5,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{981.000000, 126.000000},4,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{875.000000, -44.000000},5,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{809.000000, -166.000000},3,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{961.000000, -230.243469},3,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{1103.000000, -323.243469},4,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{1023.000000, -412.243469},5,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{1045.000000, -557.243408},5,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{10.000000, 78.000000},2,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{124.000000, 142.000000},2,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{277.000000, 93.000000},1,2));

    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{138.000000, -461.243469},3,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{359.000000, -301.243469},2,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{653.000000, -465.243469},1,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{445.000000, -437.243469},3,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{190.000000, -20.000000},3,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{517.000000, -79.000000},2,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{202.000000, 208.000000},1,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{559.000000, 43.000000},3,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{414.000000, 33.000000},2,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{269.000000, -175.000000},1,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{541.000000, -187.000000},4,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{712.000000, -291.750488},5,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{801.000000, -417.750488},4,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{82.000000, -254.750488},3,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{359.000000, -552.750488},2,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{794.000000, -540.750488},4,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{627.000000, -549.750488},2,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{22.000000, -551.750488},5,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{110.000000, -105.000000},5,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{554.000000, 194.000000},5,1));
    dynamicGameObjects->emplace_back(new CheckpointPlatform(colliders, -620,"awake2"));

}

void awake2(vector<GameObject*> *dynamicGameObjects)
{
    dynamicGameObjects->emplace_back(new CheckpointPlatform(colliders, -620,""));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{824.000000, -719.000000},5,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{479.000000, -700.000000},1,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{395.000000, -779.000000},5,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{157.000000, -746.000000},1,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{152.000000, -848.000000},2,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{293.000000, -701.000000},3,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{793.000000, -877.000000},4,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{865.000000, -807.000000},2,1));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{617.000000, -867.000000},3,2));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{1099.000000, -676.000000},3,3));
    dynamicGameObjects->emplace_back(new CloudPlatform(colliders,{1143.000000, -835.000000},5,3));

}

void awake3(vector<GameObject*> *dynamicGameObjects)
{}

void awake4(vector<GameObject*> *dynamicGameObjects)
{}



void developer(vector<class GameObject*> *dynamicGameObjects)
{
    dynamicGameObjects->emplace_back(new PlatformPlacer(colliders));

}
void player(vector<class GameObject*> *dynamicGameObjects)
{
    dynamicGameObjects->emplace_back(new Lucy(colliders));
}

void testArea(vector<GameObject*> *dynamicGameObjects)
{
    Platform *platform = new Platform(13, false);
    platform->setPlatformImages("blocker/blocker_left.png","blocker/blocker_middle.png","blocker/blocker_right.png");
    platform->setPosition(platform->game->windowHandler->getCentreScreenX(platform->getWidth()),670);
    dynamicGameObjects->emplace_back(platform);

    Platform *platform2 = new Platform(13, true);
    platform2->setPlatformImages("blocker/blocker_left.png","blocker/blocker_middle.png","blocker/blocker_right.png");
    platform2->setPosition(platform->game->windowHandler->getCentreScreenX(platform2->getWidth()),0);
    dynamicGameObjects->emplace_back(platform2);
}