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
using namespace std;

class Tim : public Sprite
{
private:
    AnimationComponent animation;
    ImageComponent image;

public:
    Tim(): animation(this), image(this)
    {
        image.setImage("stars.png");
        image.setRelativeScale(0.5);
        image.setDrawOrder(0);
        animation.setDrawOrder(1);
        animation.addAnimation(vector<string>{"stars.png","COOKIE.png","COOKIE.png","background.png"},"test",1,true);
        animation.changeConfiguration("test");
        cout << "Tim Created!" << endl;
        scale = 1;
        position.x = 0;
    }
    void update()
    {
        if (game->inputHandler->keyJustPressed(SDL_SCANCODE_W))
        {
            cout << "W pressed" << endl;
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