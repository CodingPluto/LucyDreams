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
    for (GameObject *gameObject : gameObjects)
    {
        gameObject->update();
    }
}

void Game::renderOutput()
{
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
        throw runtime_error("A handler added past game initalization. Undefined behaviour.");
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

void Game::addGameObj(GameObject *address)
{
    gameObjects.emplace_back(address);
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
    for (vector<GameObject*>::size_type i = 0; i < gameObjects.size(); ++i)
    {
        cout << gameObjects[i]->getUpdateOrder() << ",  ";
    }
    cout << endl;
}

void Game::removeGameObj(GameObject *address)
{
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
    {
        if (*it == address)
        {
            gameObjects.erase(it);
            break;
        }
    }
}

void Game::exitGame()
{
    gameRunning = false;
}

/*
keys = SDL_GetKeyboardState(NULL);
*/
/*
bool Game::keyState(SDL_Scancode key)
{
    return keys[key];
}*/