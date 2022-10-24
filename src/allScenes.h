#ifndef SRC_ALL_SCENES_H
#define SRC_ALL_SCENES_H

#include <vector>

extern std::vector<class AABBCollider*> colliders;

void firstScene(std::vector<class GameObject*> *dynamicGameObjects);
void secondScene(std::vector<class GameObject*> *dynamicGameObjects);


#endif