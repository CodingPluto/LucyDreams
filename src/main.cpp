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
    Camera camera;

public:
    Tim(): image(this), trigger(this, 100), camera(this, &image)
    {
        isPositionRelative = true;
        image.setImage("stars.png");
        image.setRelativeScale(0.1);
        image.setDrawOrder(0);
        cout << "Tim Created!" << endl;
        scale = 1;
        position.x = 0;
        game->cameraHandler->setActiveCamera(&camera);
    }
    void update()
    {
        cout << "starting update " << endl;
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 50;
        rect.h = 50;
        //game->displayHandler->drawRect(&rect,{0,0,0,255},true,false);
        if (game->inputHandler->isLMBOneClick())
        {
            cout << "mouse press!" << endl;
        }
        cout << getAbsolutePosition() << endl;
        changePosition(1,0);
        displayPosition();
        cout << "finished update" << endl;
    }
};
class LucyDreams : public Game
{
    vector<GameObject*> loadedSprites;
    void loadHandlers()
    {
        windowHandler = new WindowHandler("Lucy Dreams!",0,0,500,500);
        eventsHandler = new EventsHandler();
        inputHandler = new InputHandler();
        cameraHandler = new CameraHandler();
        imageHandler = new ImageHandler(windowHandler, cameraHandler, "/home/pluto/Documents/Programming/LucyDreams/assets/images/");
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