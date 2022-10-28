#include "Scene.h"

using namespace std;

Scene::Scene(const string name, const SceneFunction sceneLoader): name(name), sceneLoader(sceneLoader)
{}


void Scene::load()
{
    sceneLoader(&gameObjects);}


void Scene::unload()
{
    for (const GameObject* gameObject : gameObjects)
    {
        delete gameObject;
    }
}