#include "Game.h"
#include "Sprite.h"
#include "handlers/WindowHandler.h"
#include "handlers/DisplayHandler.h"
#include "handlers/EventsHandler.h"
#include "handlers/ImageHandler.h"
#include "handlers/CameraHandler.h"
#include "handlers/InputHandler.h"
#include "components/AnimationComponent.h"
#include "handlers/Camera.h"
#include "Trigger.h"
using namespace std;

class Tim : public Sprite
{
private:
    ImageComponent image;
    Trigger trigger;

public:
    Tim(): image(this), trigger(this, 100)
    {
        image.setImage("stars.png");
        image.setRelativeScale(0.5);
        image.setDrawOrder(0);
        cout << "Tim Created!" << endl;
        scale = 1;
        position.x = 0;
    }
    void update()
    {
        if (game->inputHandler->isLMBOneClick())
        {
            cout << "mouse press!" << endl;
        }
        changePosition(0,0);
        displayPosition();
    }
};
class LucyDreams : public Game
{
    vector<GameObject*> loadedSprites;
    void loadHandlers()
    {
        windowHandler = new WindowHandler("Lucy Dreams!",0,0,500,500);
        displayHandler = new DisplayHandler(windowHandler);
        eventsHandler = new EventsHandler();
        inputHandler = new InputHandler();
        cameraHandler = new CameraHandler();
        imageHandler = new ImageHandler(displayHandler,"/home/pluto/Documents/Programming/LucyDreams/assets/images/");
    }
    void loadGameData()
    {
        loadedSprites.emplace_back(new Tim());
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
        for (GameObject *loadedSprite : loadedSprites)
        {
            delete loadedSprite;
        }
    }
};



int main(int argc, char *argv[])
{
    LucyDreams game;
    game.initalize();
}