#ifndef SRC_HANDLERS_CAMERAS_SPRITE_CAMERA_H
#define SRC_HANDLERS_CAMERAS_SPRITE_CAMERA_H
#include "Camera.h"
enum st__ScrollingType
{
    st_All,
    st_VerticalOnly,
    st_HoriziontalOnly
};
class SpriteCamera : public Camera
{
private:
    Position2 cameraOffset;
    st__ScrollingType st;
    class Sprite *const owner;
    class ImageComponent *const image;
    int textureWidth;
    int textureHeight;
public:
    void onImageSet();
    SpriteCamera(class Sprite *const owner, class ImageComponent *const image);
    void setCameraScrollingType(const st__ScrollingType &newSt);
    Position2 cameraUpdate() override;
    const std::string* getSceneOwner() override;
    void setCameraOffset(const Position2 &cameraOffset);


};
#endif