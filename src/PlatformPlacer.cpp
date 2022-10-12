#include "PlatformPlacer.h"
#include "handlers/InputHandler.h"
#include "CloudPlatform.h"
#include <iostream>
using namespace std;

PlatformPlacer::PlatformPlacer(vector<AABBCollider*> &colliders):colliders(colliders)
{
    setDebugName("Platform Placer");
}


PlatformPlacer::~PlatformPlacer()
{
    for (const CloudPlatform *cloudPlatform : myPlatforms)
    {
        delete cloudPlatform;
    }
}

void PlatformPlacer::update()
{
    if (game->inputHandler->isRMBOneClick())
    {
        CloudPlatform *cloudPlatform = nullptr;
        for (auto it = myPlatforms.begin(); it != myPlatforms.end(); ++it)
        {
            cloudPlatform = *it;
            if (cloudPlatform->collider.position.x <= game->inputHandler->getMouseX() && cloudPlatform->collider.position.x + cloudPlatform->collider.width >= game->inputHandler->getMouseX())
            {
                if (cloudPlatform->collider.position.y <= game->inputHandler->getMouseY() && cloudPlatform->collider.position.y + cloudPlatform->collider.height >= game->inputHandler->getMouseY())
                {
                    cout << "Gonna delete it!" << endl;
                    game->deleteAtFrameEnd(cloudPlatform);
                    myPlatforms.erase(it);
                    break;
                }
            }
        }
    }
    else if (game->inputHandler->isLMBOneClick() && framesSinceLastClick > 5)
    {
        cout << "LEFT CLICK!" << endl;
        myPlatforms.emplace_back(new CloudPlatform(colliders,{(float)game->inputHandler->getMouseX(),(float)game->inputHandler->getMouseY()}));
        cout << "still updating!" << endl;
        framesSinceLastClick = 0;
    }
    cout << "finished updating!" << endl;
    framesSinceLastClick ++;
}