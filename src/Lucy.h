#ifndef SRC_LUCY_H
#define SRC_LUCY_H
#include <string>
#include "components/AnimationComponent.h"
#include "colliders/PlatformerCollision.h"
#include "handlers/Camera.h"
enum ls__LucyState
{
    ls_Running,
    ls_Jumping,
    ls_Falling,
    ls_Charging,
    ls_Repulse,
    ls_Idle,
    ls_Die
};




class Lucy : public PlatformerCollision
{
    AnimationComponent lucyAnimation;
private:
    bool previousTouching[4];
    ls__LucyState previousState;
    Position2 velocity;
    static const std::string lucyImagesPath;
    Camera playerCamera;
    static const int defaultRunSpeed = 140;
    static const int maxRunSpeed = 400;
    static const int terminalVelocity = 5000;
    static const int jumpHeight = 400;
    static const int fallSpeed = 25;
    static const int lucyScale = 2;

    bool onGround();
    void resetFrameVariables();
    ls__LucyState determineState();
    void enforceState(ls__LucyState currentState);
    void handleInput();
public:
    Lucy(std::vector<AABBCollider*> &platforms);
    void update();
};


#endif