#include <iostream>
#include "GameObject.h"
#include "handlers/DisplayHandler.h"
using namespace std;

Game *GameObject::game = nullptr;

void GameObject::setupGameObjs(Game *gameInst)
{
    game = gameInst;

}

GameObject::GameObject(){
    gs = gs_Enabled;
    if (game == nullptr)
    {
        throw "You haven't setup the game instance for the Game Objects.";
    }
    cout << "Game Object Created ("  << this << ")" << endl;
    game->addGameObject(this);
}

void GameObject::setDebugName(const std::string &debugName)
{
    this->debugName = debugName;
}
const std::string &GameObject::getDebugName()
{
    return debugName;
}

GameObject::~GameObject()
{
    gs = gs_Removed;
    game->removeGameObject(this);
    cout << "Game Object Destroyed ("  << this << ")" << endl;
}

int GameObject::getUpdateOrder()
{
    return priority;
}

void GameObject::setUpdateOrder(int priority)
{
    this->priority = priority;
    game->reloadGameObjProrities();
}

void GameObject::enable()
{
    gs = gs_Enabled;
}

void GameObject::disable()
{
    gs = gs_Disabled;
}

gs__GameObjectStatus GameObject::getGameObjectStatus()
{
    return gs;
}