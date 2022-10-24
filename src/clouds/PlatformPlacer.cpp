#include <fstream>
#include <iostream>
#include "PlatformPlacer.h"
#include "../handlers/InputHandler.h"
#include "../handlers/CameraHandler.h"
#include "../handlers/GameObjectHandler.h"
#include "CloudPlatform.h"
#include "../utils/utils.h"
using namespace std;



PlatformPlacer::PlatformPlacer(vector<AABBCollider*> &colliders):colliders(colliders)
{
    setDebugName("Platform Placer");
}

void PlatformPlacer::outputPlatformsToFile()
{
    ofstream file("/home/pluto/Documents/Programming/LucyDreams/src/platformOutput/platforms.out");
    for (CloudPlatform *cloudPlatform : myPlatforms)
    {
        file << "myPlatforms.emplace_back(new CloudPlatform(" << "colliders," << "{" << to_string(cloudPlatform->getPosition().x) << ", " << to_string(cloudPlatform->getPosition().y) << "}," << to_string(cloudPlatform->getCloudLength()) << "," << to_string(cloudPlatform->getCloudType()) << "));\n";
    }
    file.close();
}


PlatformPlacer::~PlatformPlacer()
{
    try
    {
        outputPlatformsToFile();
    }
    catch(...)
    {
        cout << "The file wasn't opened properly." << endl;
    }
    for (const CloudPlatform *cloudPlatform : myPlatforms)
    {
        delete cloudPlatform;
    }
}

void PlatformPlacer::update()
{
    hasActiveCloudPlatform = false;
    for (auto it = myPlatforms.begin(); it != myPlatforms.end(); ++it)
    {
        Position2 cameraOffset = game->cameraHandler->getCameraOffset();
        activeCloudPlatformIter = it;
        activeCloudPlatform = *it;
        if (activeCloudPlatform->collider.position.x - cameraOffset.x <= game->inputHandler->getMouseX() && activeCloudPlatform->collider.position.x - cameraOffset.x + activeCloudPlatform->collider.width >= game->inputHandler->getMouseX())
        {
            if (activeCloudPlatform->collider.position.y - cameraOffset.y <= game->inputHandler->getMouseY() && activeCloudPlatform->collider.position.y - cameraOffset.y + activeCloudPlatform->collider.height >= game->inputHandler->getMouseY())
            {
                hasActiveCloudPlatform = true;
                break;
            }
        }
    }
    if (!hasActiveCloudPlatform)
    {
        activeCloudPlatformIter = myPlatforms.end();
        activeCloudPlatform = nullptr;
    }
    if (game->inputHandler->isRMBOneClick() && hasActiveCloudPlatform)
    {
        game->gameObjectHandler->deleteAtFrameEnd(activeCloudPlatform);
        myPlatforms.erase(activeCloudPlatformIter);
    }
    else if (game->inputHandler->isLMBOneClick() && framesSinceLastClick > 5)
    {
        Position2 mousePosition = {(float)game->inputHandler->getMouseX(),(float)game->inputHandler->getMouseY()};
        myPlatforms.emplace_back(new CloudPlatform(colliders,mousePosition + game->cameraHandler->getCameraOffset(),generateRandomNumber(1,5)));
        framesSinceLastClick = 0;
        activeCloudPlatform = myPlatforms[myPlatforms.size() - 1];
    }
    framesSinceLastClick ++;

    if (activeCloudPlatform)
    {
        for (int i = 1; i <= 5; i++)
        {
            if (game->inputHandler->keyJustPressed(game->inputHandler->numberScancodes[i]))
            {
                activeCloudPlatform->setCloudLength(i);
            }
        }
    }
}