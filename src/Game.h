#ifndef SRC_GAME_H
#define SRC_GAME_H
#include <vector>
#include <map>
#include <chrono>
#include <string>
#include "GameObject.h"
#include "handlers/Handler.h"




class Game
{
protected:
    virtual ~Game();
    Game();
    virtual void loadHandlers() = 0;
    virtual void loadGameData() = 0;
    std::vector<class Handler*> organisedHandlers[4];
private:
    const unsigned int intended_framerate = 60;
    long long framesSinceInitalization = 0;
    std::chrono::_V2::system_clock::time_point previousIterDT;
    std::chrono::_V2::system_clock::time_point currentIterDT;
    std::chrono::_V2::system_clock::time_point previousFrameDT;
    std::chrono::_V2::system_clock::time_point currentFrameDT;

    std::vector<class GameObject*> *gameObjects;
    std::vector<class GameObject*> pendingGameObjects;
    std::vector<class GameObject*> pendingRemovalGameObjects;
    std::vector<class GameObject*> gameObjectsToBeDeleted;
    void gameLoop();
    void getInput();
    void updateGame();
    void renderOutput();
    void outputErrors();
    void calculateDeltaTimeForFrameTiming();
    void calculateDeltaTime();
    double frameTimingDeltaTime;
    bool gameRunning;
    std::vector<HandlerError*> errorsOnTick;
    void updateHandlers(hp__HandlerTickPoint tickPoint);
public:
    void setGameObjects(std::vector<GameObject*> *gameObjectsPtr);
    void debugLog(std::string text);
    const bool debugMode = false;
    class WindowHandler *windowHandler = nullptr;
    class EventsHandler *eventsHandler = nullptr; 
    class ImageHandler *imageHandler = nullptr;
    class CameraHandler *cameraHandler = nullptr;
    class InputHandler *inputHandler = nullptr;
    class SceneHandler *sceneHandler = nullptr;
    double deltaTime = 0.016;
    long long getFramesSinceInitalization();
    void initalize();
    void addHandler(Handler *handler, hp__HandlerTickPoint tickPoint);
    void exitGame();
    void deleteAtFrameEnd(GameObject *address);
    /*
    bool keyState(SDL_Scancode key);
    */
    void reloadGameObjProrities();
    void addGameObject(GameObject *address);
    void removeGameObject(GameObject *address);
};

#endif