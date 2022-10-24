#ifndef SRC_ALL_SCENES_H
#define SRC_ALL_SCENES_H

#include <vector>

extern std::vector<class AABBCollider*> colliders;

void Awake1(std::vector<class GameObject*> *dynamicGameObjects);
void Awake2(std::vector<class GameObject*> *dynamicGameObjects);
void Awake3(std::vector<class GameObject*> *dynamicGameObjects);
void Awake4(std::vector<class GameObject*> *dynamicGameObjects);
#endif