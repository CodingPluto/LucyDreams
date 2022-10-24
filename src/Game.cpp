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
    setSeed(time(0));
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
    gameRunning = true;
    gameLoop();
    
}


void Game::exitGame()
{
    gameRunning = false;
}

