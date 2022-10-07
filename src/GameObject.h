#ifndef SRC_GAMEOBJECT_H
#define SRC_GAMEOBJECT_H

#include "Game.h"

enum gs__GameObjectStatus
{
    gs_Enabled = 1,
    gs_Disabled = 0,
    gs_Removed = 2
};

class GameObject
{
private:
    gs__GameObjectStatus gs;
    int priority = 0;
protected:
public:
    void enable();
    void disable();
    gs__GameObjectStatus getGameObjectStatus();
    static class Game *game;
    GameObject();
    virtual ~GameObject();
    void setUpdateOrder(int priority);
    int getUpdateOrder();
    static void setupGameObjs(class Game *gameInst);
    virtual void update() = 0;
};

#endif
