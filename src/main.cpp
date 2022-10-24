#include <ctime>
#include "gameData/Game.h"
#include "gameData/Sprite.h"
#include "utils/utils.h"
#include "handlers/WindowHandler.h"
#include "handlers/DisplayHandler.h"
#include "handlers/EventsHandler.h"
#include "handlers/ImageHandler.h"
#include "handlers/CameraHandler.h"
#include "handlers/InputHandler.h"
#include "handlers/SceneHandler.h"
#include "handlers/GameObjectHandler.h"
using namespace std;


class LucyDreams : public Game
{
    void loadHandlers()
    {
        gameObjectHandler = new GameObjectHandler();
        windowHandler = new WindowHandler("Lucy Dreams!",0,0,1280,720);
        eventsHandler = new EventsHandler();
        inputHandler = new InputHandler();
        cameraHandler = new CameraHandler();
        imageHandler = new ImageHandler(windowHandler, cameraHandler, "/home/pluto/Documents/Programming/LucyDreams/assets/images/");
        sceneHandler = new SceneHandler();
        sceneHandler->setScene("Awake1");
    }
public:
    ~LucyDreams()
    {
        for (int i = 0; i < 4; ++i)
        {
            for (auto handler : organisedHandlers[i])
            {
                delete handler;
            }
        }
    }
};


int main(int argc, char *argv[])
{
    LucyDreams game;
    game.initalize();
}
