#ifndef SRC_CAMERA_H
#define SRC_CAMERA_H
#include "../Position.h"
class Camera
{
private:
    class Sprite *owner;
    class ImageComponent *image;
    Position2 camOffset;
    int textureWidth;
    int textureHeight;
public:
    void onImageSet();
    Camera(class Sprite *owner, class ImageComponent *image);
    Camera();
    Position2 cameraUpdate();

};

#endif