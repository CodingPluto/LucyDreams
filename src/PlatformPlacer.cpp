#include <fstream>
#include <iostream>
#include "PlatformPlacer.h"
#include "handlers/InputHandler.h"
#include "handlers/CameraHandler.h"
#include "CloudPlatform.h"
using namespace std;


void PlatformPlacer::onStart()
{   /*
    myPlatforms.clear();
    myPlatforms.emplace_back(new CloudPlatform(colliders,{105.000000, 497.338074},4,2));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{447.000000, 648.363403},2,3));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{289.000000, 540.824524},4,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{652.000000, 921.833923},2,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{624.000000, 911.898926},2,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{480.000000, 547.007996},3,3));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{630.000000, 570.164917},1,3));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{702.000000, 489.903961},2,3));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{488.000000, 629.214905},2,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{568.000000, 710.662720},4,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{568.000000, 610.428284},3,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{293.000000, 472.388000},3,2));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{293.000000, 643.228699},3,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{327.000000, 460.642151},2,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{735.000000, 622.534424},5,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{735.000000, 500.963196},1,3));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{628.000000, 483.644409},1,3));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{572.000000, 478.666168},3,1));
    myPlatforms.emplace_back(new CloudPlatform(colliders,{797.000000, 229.672592},3,1));
    */

}

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
        game->deleteAtFrameEnd(activeCloudPlatform);
        myPlatforms.erase(activeCloudPlatformIter);
    }
    else if (game->inputHandler->isLMBOneClick() && framesSinceLastClick > 5)
    {
        Position2 mousePosition = {(float)game->inputHandler->getMouseX(),(float)game->inputHandler->getMouseY()};
        myPlatforms.emplace_back(new CloudPlatform(colliders,mousePosition + game->cameraHandler->getCameraOffset(),-1,-1));
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