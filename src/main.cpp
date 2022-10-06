#include <iostream>
#include "Game.h"
#include "Component.h"
#include "Sprite.h"
#include "handlers/inc/WindowHandler.h"
#include "handlers/inc/DisplayHandler.h"
#include "handlers/inc/EventsHandler.h"
#include "handlers/inc/ImageHandler.h"
#include "handlers/inc/CameraHandler.h"
#include "AnimationComponent.h"
#include "Camera.h"
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