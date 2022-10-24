#include <iostream>
#include "../CameraHandler.h"
#include "../SceneHandler.h"
#include "../GameObjectHandler.h"
#include "../../GameObject.h"
#include "../../colliders/AABBCollider.h"
#include "../../PlatformPlacer.h"
#include "../../Lucy.h"

using namespace std;
vector<AABBCollider*> colliders;
void myFirstScene(vector<GameObject*> *dynamicGameObjects)
{
    dynamicGameObjects->emplace_back(new PlatformPlacer(colliders));
    dynamicGameObjects->emplace_back(new Lucy(colliders));
}

void mySecondScene(vector<GameObject*> *dynamicGameObjects)
{

}

SceneHandler::SceneHandler():Handler(hp_OnInput)
{
    isModifyingScene = false;
    debugName = "Scene Handler";
    addScene(myFirstScene,"First");
    addScene(mySecondScene,"Second");
}
SceneHandler::~SceneHandler()
{
    for (auto dynamicGameObject : dynamicGameObjects)
    {
        delete dynamicGameObject;
    }
    dynamicGameObjects.clear();
}

void SceneHandler::addScene(SceneFunction sceneFunction,string sceneName)
{
    scenesFunctions[sceneName] = sceneFunction;
}

bool SceneHandler::initalize()
{
    return true;
}

HandlerError* SceneHandler::tick()
{
    if (isModifyingScene)
    {
        try
        {
            scenesFunctions.at(sceneName);
        }
        catch(const exception &e)
        {
            return new HandlerError(et_GameError,"The scene \'" + sceneName + "\' doesn\'t exist!",this);
        }
        modifyScene();
        isModifyingScene = false;
    }
    return nullptr;
}

void SceneHandler::setScene(const string &sceneName)
{
    this->sceneName = sceneName;
    isModifyingScene = true;
}

void SceneHandler::modifyScene()
{
    game->cameraHandler->setActiveCamera(nullptr);

    game->gameObjectHandler->purge();
    for (auto dynamicGameObject : dynamicGameObjects)
    {
        delete dynamicGameObject;
    }
    dynamicGameObjects.clear();
    scenesFunctions.at(sceneName)(&dynamicGameObjects);

    for (auto persistentGameObject : persistentGameObjects)
    {
        game->gameObjectHandler->addGameObject(persistentGameObject);
    }
}