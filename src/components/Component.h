#ifndef SRC_COMPONENT_H
#define SRC_COMPONENT_H
#include "../GameObject.h"
class Component : public GameObject
{
private:
    float relativeScale = 1;
protected:
    class Sprite *owner = nullptr;
    Component();
public:
    float getScale();
    void setRelativeScale(float scale);
    
    Component(class Sprite *sprite);
};


#endif