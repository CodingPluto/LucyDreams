#include <iostream>
#include "../CameraHandler.h"
#include "../SceneHandler.h"
#include "../../GameObject.h"
#include "../../colliders/AABBCollider.h"
#include "../../PlatformPlacer.h"
#include "../../Lucy.h"

using namespace std;
vector<AABBCollider*> colliders;
void myFirstScene(vector<GameObject*> *dynamicGameObjects)
{
    cout << "RUNNING MY FIRST SCENE" << endl;
    dynamicGameObjects->emplace_back(new PlatformPlacer(colliders));
    dynamicGameObjects->emplace_back(new Lucy(colliders));

    cout << "Created new PlatformPlacer!" << endl;
}

void mySecondScene(vector<GameObject*> *dynamicGameObjects)
{

}

SceneHandler::SceneHandler():Handler(hp_OnInput)
{
    modifyGameObjects = false;
    debugName = "Scene Handler";
    cout << "Scene Handler Created!" << endl;
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
    game->setGameObjects(&loadedGameObjects);
    return true;
}

HandlerError* SceneHandler::tick()
{
    if (modifyGameObjects)
    {
        cout << "Modifiying game objeccts!" << endl;
        modifyLoadedGameObjects();
        modifyGameObjects = false;
    }
    return nullptr;
}

void SceneHandler::setScene(const string &sceneName)
{
    this->sceneName = sceneName;
    modifyGameObjects = true;
    cout << "Ticked boolean" << endl;
}

void SceneHandler::modifyLoadedGameObjects()
{
    game->cameraHandler->setActiveCamera(nullptr);
    loadedGameObjects.clear();
    for (auto dynamicGameObject : dynamicGameObjects)
    {
        delete dynamicGameObject;
    }
    dynamicGameObjects.clear();
    scenesFunctions.at(sceneName)(&dynamicGameObjects);

    for (auto persistentGameObject : persistentGameObjects)
    {
        loadedGameObjects.emplace_back(persistentGameObject);
    }
}