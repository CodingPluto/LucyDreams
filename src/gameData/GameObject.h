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
    void setSceneName(const std::string *sceneNamePtr);
    const std::string *sceneNamePtr = nullptr;
    static class Game *game;
    virtual void update() = 0;
    virtual void onStart();
    void enable();
    void disable();
    GameObject();
    virtual ~GameObject();
    void setUpdateOrder(int priority);
    int getUpdateOrder();
    gs__GameObjectStatus getGameObjectStatus();

    void setDebugName(const std::string &debugName);
    const std::string &getDebugName();
    static void linkGameObjects(class Game *gameInst);
};

#endif
