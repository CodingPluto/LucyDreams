#include <ctime>
#include "Game.h"
#include "Sprite.h"
#include "utils/utils.h"
#include "handlers/WindowHandler.h"
#include "handlers/DisplayHandler.h"
#include "handlers/EventsHandler.h"
#include "handlers/ImageHandler.h"
#include "handlers/CameraHandler.h"
#include "handlers/InputHandler.h"
#include "handlers/SceneHandler.h"
#include "components/AnimationComponent.h"
#include "handlers/Camera.h"
#include "colliders/AABBCollider.h"
#include "Lucy.h"
#include "CloudPlatform.h"
#include "PlatformPlacer.h"
//#include "Trigger.h"
using namespace std;


class LucyDreams : public Game
{
    vector<GameObject*> loadedSprites;
    vector<AABBCollider*> colliders;
    void loadHandlers()
    {
        windowHandler = new WindowHandler("Lucy Dreams!",0,0,1280,720);
        eventsHandler = new EventsHandler();
        inputHandler = new InputHandler();
        cameraHandler = new CameraHandler();
        imageHandler = new ImageHandler(windowHandler, cameraHandler, "/home/pluto/Documents/Programming/LucyDreams/assets/images/");
        sceneHandler = new SceneHandler();
    }
    void loadGameData()
    {
        debugLog("--- Starting Loading Game Data ---");
        setSeed(time(0));
        //loadedSprites.emplace_back(new PlatformPlacer(colliders));
        debugLog("Loaded Sprites: " + to_string(loadedSprites.size()));
        debugLog("--- Loaded Game Data! ---");
        sceneHandler->setScene("First");

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


/*


        AABBCollider *aabbCollider = new AABBCollider(0,0,100,100);
        colliders.emplace_back(aabbCollider);
        aabbCollider->setAABBColliders(colliders);
        AABBCollider *aabbCollider2 = new AABBCollider(50,50,100,100);
        colliders.emplace_back(aabbCollider2);
        aabbCollider2->setAABBColliders(colliders);
        loadedSprites.emplace_back(aabbCollider);
        loadedSprites.emplace_back(aabbCollider2);

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
*/