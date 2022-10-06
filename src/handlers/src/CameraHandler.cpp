#include <cmath>
#include "../CameraHandler.h"

using namespace std;
Camera* CameraHandler::getActiveCamera()
{
    return activeCamera;
}


void CameraHandler::setActiveCamera(Camera *newCamera)
{
    activeCamera = newCamera;
}

CameraHandler::CameraHandler(): Handler(hp_OnRender)
{
    debugName = "Camera Handler";
    activeCamera = &defaultCamera;
}


HandlerError* CameraHandler::tick()
{
    cameraOffset = activeCamera->cameraUpdate();

    return nullptr;
    
}

Position2 CameraHandler::getCameraOffset()
{
    return cameraOffset;
}