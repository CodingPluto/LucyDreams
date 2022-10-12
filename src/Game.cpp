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
    cout << "Base Game Instance Destructing!" << endl;
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


void Game::gameLoop()
{
    gameRunning = true;
    previousIterDT = chrono::system_clock::now();
    previousFrameDT = chrono::system_clock::now();
    double accumulated_seconds = 0;
    while (gameRunning)
    {
        calculateDeltaTimeForFrameTiming();
        accumulated_seconds += frameTimingDeltaTime;
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
}

long long Game::getFramesSinceInitalization()
{
    return framesSinceInitalization;
}

void Game::getInput()
{
    updateHandlers(hp_OnInput);
}

void Game::updateGame()
{
    updateHandlers(hp_OnUpdate);
    cout << "trying to remove " << pendingRemovalGameObjects.size() << " GameObjects." << endl;
    cout << "There are currently " << gameObjects.size() << " GameObjects." << endl;
    if (pendingRemovalGameObjects.size() > 0)
    {
        for (int i = 0; i < gameObjects.size(); i++)
        {
            cout << "Looping through gameObjects" << endl;
            for (GameObject *pendingRemovalGameObject : pendingRemovalGameObjects)
            {
                if (gameObjects[i] == pendingRemovalGameObject)
                {
                    cout << "Found one!" << endl;
                    gameObjects.erase(gameObjects.begin() + i);
                    i--;
                }
            }
            cout << i << endl;
        }
    }
    pendingRemovalGameObjects.clear();
    cout << "Pending GameObjects: " << pendingGameObjects.size() << endl;
    for (GameObject *gameObject : pendingGameObjects)
    {
        gameObjects.emplace_back(gameObject);
    }
    pendingGameObjects.clear();
    cout << "There are now " << gameObjects.size() << " GameObjects." << endl;
    cout << "--- UPDATING gameObjects ---" << endl;
    for (GameObject *gameObject : gameObjects)
    {
        if (gameObject->getGameObjectStatus())
        {
            cout << gameObject->getDebugName() << " : " << gameObject << endl;
            gameObject->update();
        }
    }
    cout << "--- UPDATED gameObjects ---" << endl;

    cout << "--- DELETING gameObjectsToBeDeleted ---" << endl;
    for (GameObject *gameObject : gameObjectsToBeDeleted)
    {
        cout << gameObject->getDebugName() << " : " << gameObject << endl;
        delete gameObject;
    }
    cout << "--- DELETED gameObjectsToBeDeleted ---" << endl;
    gameObjectsToBeDeleted.clear();
}

void Game::renderOutput()
{
    cout << "Updating handlers!" << endl;
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

void Game::addGameObject(GameObject *address)
{
    pendingGameObjects.emplace_back(address);
}

void Game::reloadGameObjProrities()
{
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

void Game::removeGameObject(GameObject *address)
{
    pendingRemovalGameObjects.emplace_back(address);
    cout << "added to pending removal" << endl;
    /*
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
    {
        if (*it == address)
        {
            gameObjects.erase(it);
            break;
        }
    }
    */
}

void Game::deleteAtFrameEnd(GameObject *address)
{
    gameObjectsToBeDeleted.emplace_back(address);
}


void Game::exitGame()
{
    gameRunning = false;
}

