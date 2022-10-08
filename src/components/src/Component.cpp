#include "../Component.h"
#include "../../Sprite.h"
using namespace std;

Component::Component(Sprite *sprite)
{
    owner = sprite;
    if (owner)
    {
        setUpdateOrder(owner->getUpdateOrder() + 1);
    }
    else
    {
        setUpdateOrder(100);
    }
    cout << "Created component!" << endl;
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