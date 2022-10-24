#ifndef SRC_HANDLERS_SCENE_HANDLER_H
#define SRC_HANDLERS_SCENE_HANDLER_H
#include <vector>
#include <functional>
#include <map>
#include "Handler.h"
typedef std::function<void(std::vector<class GameObject*> *gameObjectsPtr)> SceneFunction;
class SceneHandler : public Handler
{
private:
    bool initalize();
    bool isModifyingScene;
    std::vector<class GameObject*> dynamicGameObjects;
    std::vector<class GameObject*> persistentGameObjects;
    std::map<std::string,SceneFunction> scenesFunctions;
    void addScene(SceneFunction sceneFunction,std::string sceneName);
    void modifyScene();
    HandlerError* tick();
    std::string sceneName;
public:
    const std::string &getCurrentSceneName();
    void setScene(const std::string &sceneName);
    SceneHandler();
    ~SceneHandler();
};



#endif