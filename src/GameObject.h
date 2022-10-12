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
    std::string debugName;
protected:
public:
    void enable();
    void disable();
    void setDebugName(const std::string &debugName);
    const std::string &getDebugName();
    gs__GameObjectStatus getGameObjectStatus();
    static class Game *game;
    GameObject();
    GameObject(std::string debugName);
    virtual ~GameObject();
    void setUpdateOrder(int priority);
    int getUpdateOrder();
    static void setupGameObjs(class Game *gameInst);
    virtual void update() = 0;
};

#endif
