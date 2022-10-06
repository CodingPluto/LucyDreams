#ifndef SRC_CAMERA_H
#define SRC_CAMERA_H
#include "Position.h"
class Camera
{
private:
    class Sprite *owner;
    Position2 camOffset;
    int textureWidth;
    int textureHeight;
public:
    Camera(class Sprite *owner, std::string imageName);
    Camera();
    Position2 cameraUpdate();

};

#endif