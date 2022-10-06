#ifndef SRC_IMAGE_COMPONENT_H
#define SRC_IMAGE_COMPONENT_H
#define VISUAL_DEGUG_MODE 1
#include <vector>
#include <SDL2/SDL.h>
#include "Component.h"
#include "../Position.h"


class ImageComponent : public Component
{
private:
    void displayDebug();
    void updateImageRect();
    int drawPriority;
protected:
    SDL_Texture* getLoadedImage(std::string path);
    bool shown;
    int textureWidth;
    int textureHeight;
    SDL_Rect imgRect;
    bool imageComponentInitalized;
    std::string imageName;
    SDL_RendererFlip isImageFlipped;
    Position2 imageOffset;
public:
    int getDrawOrder();
    void setDrawOrder(int priority);
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