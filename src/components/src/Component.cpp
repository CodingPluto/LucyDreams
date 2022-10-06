#include "../Component.h"
#include "../../Sprite.h"
using namespace std;

Component::Component(Sprite *sprite)
{
    owner = sprite;
    setUpdateOrder(owner->getUpdateOrder() + 1);
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