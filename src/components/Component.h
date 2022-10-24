#ifndef SRC_COMPONENT_H
#define SRC_COMPONENT_H
#include "../gameData/GameObject.h"
class Component : public GameObject
{
private:
    float relativeScale = 1;
protected:
    class Sprite *owner = nullptr;
public:
    float getScale();
    void setRelativeScale(float scale);
    class Sprite* getOwner();
    Component();
    Component(class Sprite *sprite);
};


#endif