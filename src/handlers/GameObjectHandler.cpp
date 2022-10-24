#include <iostream>
#include "GameObjectHandler.h"
#include "../gameData/GameObject.h"
#include "../utils/utils.h"
using namespace std;

GameObjectHandler::GameObjectHandler():Handler(hp_OnUpdate)
{
    debugName = "GameObject Handler";
}
GameObjectHandler::~GameObjectHandler()
{}
HandlerError* GameObjectHandler::tick()
{

    game->debugLog("trying to remove " + to_string(pendingRemovalGameObjects.size()) + " GameObjects.");
    game->debugLog("There are currently " + to_string(gameObjects.size()) + " GameObjects.");
    if (pendingRemovalGameObjects.size() > 0)
    {
        for (int i = 0; i < gameObjects.size(); i++)
        {
            for (GameObject *pendingRemovalGameObject : pendingRemovalGameObjects)
            {
                if (gameObjects[i] == pendingRemovalGameObject)
                {
                    gameObjects.erase(gameObjects.begin() + i);
                    i--;
                }
            }
        }
    }
    game->debugLog("Pending GameObjects: " + to_string(pendingGameObjects.size()));
    for (GameObject *gameObject : pendingGameObjects)
    {
        game->debugLog("Pending GameObject: " + gameObject->getDebugName() + " : " + addressToString(gameObject));
        gameObjects.emplace_back(gameObject);
    }

    if (pendingGameObjects.size() > 0 || pendingRemovalGameObjects.size() > 0)
    {
        reloadGameObjectPriorities();
    }
    pendingGameObjects.clear();
    pendingRemovalGameObjects.clear();
    game->debugLog("There are now " + to_string(gameObjects.size()) + " GameObjects.");
    game->debugLog("--- UPDATING gameObjects ---");
    for (GameObject *gameObject : gameObjects)
    {
        if (gameObject->getGameObjectStatus())
        {
            game->debugLog(gameObject->getDebugName() + " : " + addressToString(gameObject));
            gameObject->update();
        }
    }
    game->debugLog("--- UPDATING gameObjects ---");

    game->debugLog("--- DELETING gameObjectsToBeDeleted ---");
    for (GameObject *gameObject : gameObjectsToBeDeleted)
    {
        delete gameObject;
    }
    game->debugLog("--- DELETED gameObjectsToBeDeleted ---");
    gameObjectsToBeDeleted.clear();
    return nullptr;
}
bool GameObjectHandler::initalize()
{
    game->debugLog("GameObjects: " + to_string(gameObjects.size()) + " - should be 0.");
    gameObjects.clear();
    game->debugLog("running on start code!");
    game->debugLog("Pending GameObjects: " + to_string(pendingGameObjects.size()));
    for (GameObject *gameObject : pendingGameObjects)
    {
        game->debugLog("Pending GameObject: " + gameObject->getDebugName() + " : " + addressToString(gameObject));
        gameObjects.emplace_back(gameObject);
    }
    for (GameObject *gameObject : gameObjects)
    {
        game->debugLog("GameObject: " + gameObject->getDebugName() + " : " + addressToString(gameObject));
    }
    pendingGameObjects.clear();
    game->debugLog("Currently " + to_string(gameObjects.size()) + " GameObjects");
    vector<GameObject*> onStartGameObjects; // Don't know why on earth this works.
    // my guess is the new platforms being assigned in Platform Placer are somehow getting into GameObjects, rather that PendingGameObjects
    // this screws up the loop and makes Gameobjects run twice.
    // it fixed for now.
    onStartGameObjects.assign(gameObjects.begin(),gameObjects.end());
    for (GameObject *onStartGameObject : onStartGameObjects)
    {
        game->debugLog(" --- " + onStartGameObject->getDebugName() + "(" + addressToString(onStartGameObject) + ")" + " --- ");
        onStartGameObject->onStart();
    }
    game->debugLog("----- FINISHED ON START LOOP! -----");
    reloadGameObjectPriorities();
    return true;
}


void GameObjectHandler::addGameObject(GameObject *address)
{
    pendingGameObjects.emplace_back(address);
}
void GameObjectHandler::removeGameObject(GameObject *address)
{
    pendingRemovalGameObjects.emplace_back(address);
}

void GameObjectHandler::purge()
{
    if (game->getTickPoint() != hp_OnUpdate)
    {
        gameObjects.clear();
        pendingGameObjects.clear();
        pendingRemovalGameObjects.clear();
    }
    else
    {
        throw runtime_error("Attempt to purge GameObjects when iterating over them! Game Crash.");
    }
    // Not clearing gameObjectsToBeDeleted as they still need to be deleted to avoid memory leaks.
}

void GameObjectHandler::deleteAtFrameEnd(GameObject *address)
{
    gameObjectsToBeDeleted.emplace_back(address);
}


void GameObjectHandler::reloadGameObjectPriorities()
{
    /*
    if (game->getTickPoint() == hp_OnUpdate)
    {
        throw runtime_error("Can't reload GameObjects as updating!");
    }*/
    int previousUpdateOrder = numeric_limits<int>::max();
    int updateOrder;
    for (vector<GameObject*>::size_type i = 0; i < gameObjects.size(); ++i)
    {
        updateOrder = gameObjects[i]->getUpdateOrder();
        if (i > 0)
        {
            previousUpdateOrder = gameObjects[i - 1]->getUpdateOrder();
        }
        else
        {
            previousUpdateOrder = numeric_limits<int>::max();
        }
        while (updateOrder > previousUpdateOrder)
        {
            GameObject *movingObject = gameObjects[i];
            i --;
            GameObject *displacedObject = gameObjects[i];
            gameObjects[i] = movingObject;
            gameObjects[i + 1] = displacedObject;
            if (i > 0)
            {
                previousUpdateOrder = gameObjects[i - 1]->getUpdateOrder();
            }
            else
            {
                previousUpdateOrder = numeric_limits<int>::max();
            }
            updateOrder = gameObjects[i]->getUpdateOrder();
        }
    }
}