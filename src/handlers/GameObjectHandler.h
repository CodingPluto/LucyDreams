#ifndef SRC_HANDLERS_GAME_OBJECT_HANDLER_H
#define SRC_HANDLERS_GAME_OBJECT_HANDLER_H
#include "Handler.h"
#include <vector>

class GameObjectHandler : public Handler
{
private:
    HandlerError* tick() override;
    bool initalize() override;
    std::vector<class GameObject*> *GameObjectsPtr = nullptr;
public:
    GameObjectHandler();
    ~GameObjectHandler();

};





#endif