#ifndef SRC_GAMEOBJECT_H
#define SRC_GAMEOBJECT_H

#include "Game.h"
class GameObject
{
protected:
public:
    static class Game *game;
    int priority;
    GameObject();
    virtual ~GameObject();
    void setUpdateOrder(int priority);
    int getUpdateOrder();
    static void setupGameObjs(class Game *gameInst);
    virtual void update() = 0;
};

#endif
