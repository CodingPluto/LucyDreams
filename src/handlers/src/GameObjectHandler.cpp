#include "../GameObjectHandler.h"
#include "../../GameObject.h"
using namespace std;

GameObjectHandler::GameObjectHandler():Handler(hp_OnUpdate)
{
    debugName = "GameObject Handler";
}
GameObjectHandler::~GameObjectHandler()
{}
HandlerError* GameObjectHandler::tick()
{
    return nullptr;
}
bool GameObjectHandler::initalize()
{
    return true;
}