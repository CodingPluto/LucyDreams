#ifndef SRC_GAME_H
#define SRC_GAME_H
#include <vector>
#include <map>
#include <chrono>
#include <string>
#include "../handlers/Handler.h"




class Game
{
protected:
    virtual ~Game();
    Game();
    virtual void loadHandlers() = 0;
    std::vector<class Handler*> organisedHandlers[4];
private:
    hp__HandlerTickPoint tickPoint = hp_NoTick;
    const unsigned int intended_framerate = 60;
    long long framesSinceInitalization = 0;
    std::chrono::_V2::system_clock::time_point previousIterDT;
    std::chrono::_V2::system_clock::time_point currentIterDT;
    std::chrono::_V2::system_clock::time_point previousFrameDT;
    std::chrono::_V2::system_clock::time_point currentFrameDT;

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
    hp__HandlerTickPoint getTickPoint();
    void debugLog(std::string text);
    const bool debugMode = false;
    class WindowHandler *windowHandler = nullptr;
    class EventsHandler *eventsHandler = nullptr; 
    class ImageHandler *imageHandler = nullptr;
    class CameraHandler *cameraHandler = nullptr;
    class InputHandler *inputHandler = nullptr;
    class SceneHandler *sceneHandler = nullptr;
    class GameObjectHandler *gameObjectHandler = nullptr;
    double deltaTime = 0.016;
    long long getFramesSinceInitalization();
    void initalize();
    void addHandler(Handler *handler, hp__HandlerTickPoint tickPoint);
    void exitGame();
};

#endif