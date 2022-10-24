#include "Component.h"
#include "../gameData/Sprite.h"
using namespace std;

Component::Component(Sprite *sprite)
{
    setDebugName("Component");
    owner = sprite;
    if (owner)
    {
        setUpdateOrder(owner->getUpdateOrder() + 1);
    }
    else
    {
        setUpdateOrder(100);
    }
}
Component::Component()
{}

float Component::getScale()
{
    return owner->getScale() * relativeScale;
}

void Component::setRelativeScale(float scale)
{
    relativeScale = scale;
}

Sprite* Component::getOwner()
{
    return owner;
}