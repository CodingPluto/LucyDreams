#ifndef SRC_HANDLERS_CAMERAS_CAMERA_H
#define SRC_HANDLERS_CAMERAS_CAMERA_H
#include "../utils/Position.h"


class Camera
{
protected:
    Position2 position;

public:
    virtual const std::string* getSceneOwner();
    Camera();
    virtual Position2 cameraUpdate();

};

#endif