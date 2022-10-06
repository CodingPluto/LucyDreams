#ifndef SRC_IMAGE_HANDLER_H
#define SRC_IMAGE_HANDLER_H
#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include "Handler.h"
class ImageHandler : public Handler
{
private:
    class SDL_Renderer *renderer;
    class DisplayHandler *displayHandler;
    std::map<std::string,class SDL_Texture*> textureBank;
    bool initalize();
    std::vector<class ImageComponent*> imageDrawers;
    HandlerError *tick();
public:
    void reloadImageDrawerProrities();
    void addImageDrawer(class ImageComponent *address);
    void removeImageDrawer(class ImageComponent *address);
    const std::string workspacePath;
    ImageHandler(class DisplayHandler *displayHandler, std::string workspacePath);
    void setRenderer(class SDL_Renderer *renderer);
    void loadImage(std::string imagePath);
    SDL_Texture* getImageTexture(std::string imageName);
    void drawImage(SDL_Rect *rect, std::string imageName);
    void drawImage(SDL_Rect *rect, std::string imageName, SDL_RendererFlip flipTags);
    void drawImage(int x, int y, int width, int height, std::string imageName);
};









#endif