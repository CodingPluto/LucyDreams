#ifndef SRC_ALL_SCENES_H
#define SRC_ALL_SCENES_H

#include <vector>

extern std::vector<class AABBCollider*> colliders;

void developer(std::vector<class GameObject*> *dynamicGameObjects);
void player(std::vector<class GameObject*> *dynamicGameObjects);

void awake1(std::vector<class GameObject*> *dynamicGameObjects);
void awake2(std::vector<class GameObject*> *dynamicGameObjects);
void awake3(std::vector<class GameObject*> *dynamicGameObjects);
void awake4(std::vector<class GameObject*> *dynamicGameObjects);
void testArea(std::vector<class GameObject*> *dynamicGameObjects);
#endif