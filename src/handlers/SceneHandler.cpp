#include <iostream>
#include "CameraHandler.h"
#include "SceneHandler.h"
#include "GameObjectHandler.h"
#include "../gameData/GameObject.h"
#include "../allScenes.h"


using namespace std;
SceneHandler::SceneHandler():Handler(hp_OnInput)
{
    isModifyingScene = false;
    debugName = "Scene Handler";
    addScene(Awake1,"Awake1");
    addScene(Awake2,"Awake2");
    addScene(Awake3,"Awake3");
    addScene(Awake4,"Awake4");
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

const std::string &SceneHandler::getCurrentSceneName()
{
    return sceneName;
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
    cout << "---- NEW SCENE {" << sceneName << "} ----" << endl;
}