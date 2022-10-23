#include <iostream>
#include <unistd.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <thread>
#include <iomanip>
#include <limits.h>
#include <dirent.h>
#include "Game.h"
#include "handlers/Handler.h"
#include "utils/utils.h"

using namespace std;

// Protected Functions


Game::Game(): gameRunning(false)
{
    GameObject::setupGameObjs(this);
    Handler::linkHandlersToGame(this);
}
Game::~Game()
{
    cout << "Game Destructing!" << endl;
}
// Private Functions
void Game::updateHandlers(hp__HandlerTickPoint tickPoint)
{
    for (Handler *handler : organisedHandlers[tickPoint])
    {
        HandlerError* errorStatus = handler->tick();
        if (errorStatus != nullptr)
        {
            errorsOnTick.emplace_back(errorStatus);
        }
    }
}
void Game::debugLog(string text)
{
    if (debugMode)
    {
        cout << text << endl;
    }
}


void Game::gameLoop()
{
    gameRunning = true;
    previousIterDT = chrono::system_clock::now();
    previousFrameDT = chrono::system_clock::now();
    double accumulated_seconds = 0;
    debugLog("GameObjects: " + to_string(gameObjects->size()) + " - should be 0.");
    gameObjects->clear();
    debugLog("running on start code!");
    debugLog("Pending GameObjects: " + to_string(pendingGameObjects.size()));
    for (GameObject *gameObject : pendingGameObjects)
    {
        if (gameObject->getDebugName() == "Lucy")
        {
            cout << "Lucy Found In Pending GameObjects." << endl;
        }
        debugLog("Pending GameObject: " + gameObject->getDebugName() + " : " + addressToString(gameObject));
        gameObjects->emplace_back(gameObject);
    }
    for (GameObject *gameObject : *gameObjects)
    {
        debugLog("GameObject: " + gameObject->getDebugName() + " : " + addressToString(gameObject));
    }
    pendingGameObjects.clear();
    debugLog("Currently " + to_string(gameObjects->size()) + " GameObjects");
    vector<GameObject*> onStartGameObjects; // Don't know why on earth this works.
    // my guess is the new platforms being assigned in Platform Placer are somehow getting into GameObjects, rather that PendingGameObjects
    // this screws up the loop and makes Gameobjects run twice.
    // it fixed for now.
    onStartGameObjects.assign(gameObjects->begin(),gameObjects->end());
    for (GameObject *onStartGameObject : onStartGameObjects)
    {
        debugLog(" --- " + onStartGameObject->getDebugName() + "(" + addressToString(onStartGameObject) + ")" + " --- ");
        onStartGameObject->onStart();
    }
    debugLog("----- FINISHED ON START LOOP! -----");
    reloadGameObjProrities();
    while (gameRunning)
    {
        calculateDeltaTimeForFrameTiming();
        accumulated_seconds += frameTimingDeltaTime;
        sleep(0); // This is to reduce cpu usage. May create frame stutters.
        if (isgreater(accumulated_seconds,16666666))
        {
            getInput();
            updateGame();
            renderOutput();
            outputErrors();
            calculateDeltaTime();
            accumulated_seconds = 0;
            ++framesSinceInitalization;
        }
    }
    tickPoint = hp_NoTick;
}

hp__HandlerTickPoint Game::getTickPoint()
{
    return tickPoint;
}

long long Game::getFramesSinceInitalization()
{
    return framesSinceInitalization;
}

void Game::getInput()
{
    tickPoint = hp_OnInput;
    updateHandlers(hp_OnInput);
}

void Game::updateGame()
{
    tickPoint = hp_OnUpdate;
    updateHandlers(hp_OnUpdate);

    debugLog("trying to remove " + to_string(pendingRemovalGameObjects.size()) + " GameObjects.");
    debugLog("There are currently " + to_string(gameObjects->size()) + " GameObjects.");
    if (pendingRemovalGameObjects.size() > 0)
    {
        for (int i = 0; i < gameObjects->size(); i++)
        {
            for (GameObject *pendingRemovalGameObject : pendingRemovalGameObjects)
            {
                if ((*gameObjects)[i] == pendingRemovalGameObject)
                {
                    gameObjects->erase(gameObjects->begin() + i);
                    i--;
                }
            }
        }
    }
    debugLog("Pending GameObjects: " + to_string(pendingGameObjects.size()));
    for (GameObject *gameObject : pendingGameObjects)
    {
        debugLog("Pending GameObject: " + gameObject->getDebugName() + " : " + addressToString(gameObject));
        gameObjects->emplace_back(gameObject);
    }

    if (pendingGameObjects.size() > 0 || pendingRemovalGameObjects.size() > 0)
    {
        reloadGameObjProrities();
    }
    pendingGameObjects.clear();
    pendingRemovalGameObjects.clear();
    debugLog("There are now " + to_string(gameObjects->size()) + " GameObjects.");
    debugLog("--- UPDATING gameObjects ---");
    for (GameObject *gameObject : *gameObjects)
    {
        if (gameObject->getGameObjectStatus())
        {
            debugLog(gameObject->getDebugName() + " : " + addressToString(gameObject));
            gameObject->update();
        }
    }
    debugLog("--- UPDATING gameObjects ---");

    debugLog("--- DELETING gameObjectsToBeDeleted ---");
    for (GameObject *gameObject : gameObjectsToBeDeleted)
    {
        delete gameObject;
    }
    debugLog("--- DELETED gameObjectsToBeDeleted ---");
    gameObjectsToBeDeleted.clear();
}

void Game::renderOutput()
{
    tickPoint = hp_OnRender;
    updateHandlers(hp_OnRender);
}

void Game::outputErrors()
{
    for (HandlerError *error : errorsOnTick)
    {
        auto errorType = error->getErrorType();
        if (errorType == et_GameError || errorType == et_SystemError)
        {
            throw runtime_error(error->returnError());
        }
        else
        {
            cout << error->returnError() << endl;
        }
        delete error;
        error = nullptr;
    }
    errorsOnTick.clear();
}

void Game::calculateDeltaTimeForFrameTiming()
{
    currentIterDT = chrono::system_clock::now();
    frameTimingDeltaTime = (currentIterDT-previousIterDT).count();
    previousIterDT = currentIterDT;
}

void Game::calculateDeltaTime()
{
    currentFrameDT = chrono::system_clock::now();
    deltaTime = chrono::duration<double>(currentFrameDT - previousFrameDT).count();
    previousFrameDT = currentFrameDT;
}

// Public Functions


void Game::addHandler(Handler *handler, hp__HandlerTickPoint tickPoint)
{
    if (gameRunning)
    {
        throw runtime_error("A handler added past game initalization. Not allowed.");
    }
    organisedHandlers[tickPoint].emplace_back(handler);
}

void Game::initalize()
{
    loadHandlers();
    cout << "Loaded Handlers" << endl;
    for (int i = 0; i < 4; ++i)
    {
        for (Handler *handler : organisedHandlers[i])
        {
            if (handler->initalize())
            {
                cout << handler->getDebugName() << " (" << handler << "): " << "Successfully Initalized!" << endl;
            }
            else
            {
                throw runtime_error("The handler \'" + handler->getDebugName() + "\' couldn't be Initalized!");
            }
        }
    }
    loadGameData();
    gameRunning = true;
    gameLoop();
    
}

void Game::setGameObjects(vector<GameObject*> *gameObjectsPtr)
{
    gameObjects = gameObjectsPtr;
}

void Game::addGameObject(GameObject *address)
{
    pendingGameObjects.emplace_back(address);
}

void Game::reloadGameObjProrities()
{
    /*
    int previousUpdateOrder = numeric_limits<int>::max();
    int updateOrder;
    for (vector<GameObject*>::size_type i = 0; i < gameObjects->size(); ++i)
    {
        updateOrder = (*gameObjects)[i]->getUpdateOrder();
        if (i > 0)
        {
            previousUpdateOrder = (*gameObjects)[i - 1]->getUpdateOrder();
        }
        else
        {
            previousUpdateOrder = numeric_limits<int>::max();
        }
        while (updateOrder > previousUpdateOrder)
        {
            GameObject *movingObject = (*gameObjects)[i];
            i --;
            GameObject *displacedObject = (*gameObjects)[i];
            (*gameObjects)[i] = movingObject;
            (*gameObjects)[i + 1] = displacedObject;
            if (i > 0)
            {
                previousUpdateOrder = (*gameObjects)[i - 1]->getUpdateOrder();
            }
            else
            {
                previousUpdateOrder = numeric_limits<int>::max();
            }
            updateOrder = (*gameObjects)[i]->getUpdateOrder();
        }
    }
    cout << "UPDATE ORDER: " << endl;
    for (auto gameObject : *gameObjects)
    {
        cout << gameObject->getUpdateOrder() << "  :  "  << gameObject->getDebugName() << endl;
    }
    */
}

void Game::removeGameObject(GameObject *address)
{
    pendingRemovalGameObjects.emplace_back(address);
}

void Game::deleteAtFrameEnd(GameObject *address)
{
    gameObjectsToBeDeleted.emplace_back(address);
}


void Game::exitGame()
{
    gameRunning = false;
}

