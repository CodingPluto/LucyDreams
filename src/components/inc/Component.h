#ifndef SRC_COMPONENT_H
#define SRC_COMPONENT_H
#include "GameObject.h"
class Component : public GameObject
{
private:
    float relativeScale = 1;
protected:
    class Sprite *owner = nullptr;
    Component();
    float getScale();
public:
    void setRelativeScale(float scale);
    
    Component(class Sprite *sprite);
};


#endif