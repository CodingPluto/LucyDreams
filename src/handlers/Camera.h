#ifndef SRC_CAMERA_H
#define SRC_CAMERA_H
#include "../utils/Position.h"

enum st__ScrollingType
{
    st_All,
    st_VerticalOnly,
    st_HoriziontalOnly
};

class Camera
{
private:
    class Sprite *owner;
    class ImageComponent *image;
    Position2 camOffset;
    int textureWidth;
    int textureHeight;
    st__ScrollingType st;
    Position2 cameraOffset;

public:
    void onImageSet();
    void setCameraOffset(Position2 cameraOffset);
    void setCameraScrollingType(st__ScrollingType newSt);
    Camera(class Sprite *owner, class ImageComponent *image);
    Camera();
    Position2 cameraUpdate();

};

#endif