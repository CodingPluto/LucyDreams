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
    this->priority = 0;
    if (game == nullptr)
    {
        throw "You haven't setup the game instance for the Game Objects.";
    }
    cout << "Game Object Created ("  << this << ")" << endl;
    game->addGameObj(this);
}

GameObject::~GameObject()
{
    game->removeGameObj(this);
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