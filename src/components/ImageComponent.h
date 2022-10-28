#ifndef SRC_IMAGE_COMPONENT_H
#define SRC_IMAGE_COMPONENT_H
#include <vector>
#include <SDL2/SDL.h>
#include <functional>
#include "Component.h"
#include "../utils/Position.h"


class ImageComponent : public Component
{
private:
    void displayDebug();
    void updateImageRect();
    int drawPriority;
protected:
    SDL_Texture* getLoadedImage(std::string path);
    class SpriteCamera *cameraInstance = nullptr;
    bool shown;
    int textureWidth;
    int textureHeight;
    SDL_Rect imgRect;
    bool imageComponentInitalized;
    std::string imageName;
    SDL_RendererFlip isImageFlipped;
    Position2 imageOffset;
public:
    std::string getImageName();
    int getDrawOrder();
    float getWidth();
    float getHeight();
    void setDrawOrder(int priority);
    void setCameraInstance(class SpriteCamera *camera);
    void show();
    void hide();
    void setImageOffset(Position2 offset);
    Position2 getImageOffset();
    void setImageFlip(SDL_RendererFlip status);
    SDL_RendererFlip getFlippedStatus();
    ImageComponent(Sprite *sprite);
    virtual ~ImageComponent();
    void setImage(std::string imageName);
    virtual void draw();
    virtual void update();


};

#endif