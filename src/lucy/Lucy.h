#ifndef SRC_LUCY_H
#define SRC_LUCY_H
#include <string>
#include "../components/AnimationComponent.h"
#include "../colliders/PlatformerCollision.h"
#include "../cameras/SpriteCamera.h"
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




class Lucy : public Sprite
{
    AnimationComponent lucyAnimation;
private:
    SpriteCamera playerCamera;
    int coyoteCounter = 0;
    bool coyoteTime = false;
    bool extendedJump = false;
    unsigned int framesSinceJump;
    bool previousTouching[4];
    bool touching[4];
    bool jumping;
    bool hadCurrentPlatformLastFrame = false;
    ls__LucyState previousState;
    Position2 velocity;
    static const std::string lucyImagesPath;
    static const int defaultRunSpeed = 140;
    static const int maxRunSpeed = 400;
    static const int terminalVelocity = 2000;
    static const int jumpHeight = 400;
    static const int fallSpeed = 25;
    static const int lucyScale = 2;
    static const int coyoteFrames = 5;
    std::vector<AABBCollider*> &platforms;
    std::vector<int> heightOfNewPlatforms;
    class CloudPlatform* currentPlatform = nullptr;
    class AABBCollider* currentPlatformCollider = nullptr;

    const std::string *previouslyLoadedLevelName = nullptr;

    bool onGround();
    void resetFrameVariables();
    ls__LucyState determineState();
    void enforceState(ls__LucyState currentState);
    void handleInput();
    void correctPosition();
    void checkCollision();
public:
    void onStart() override;
    Lucy(std::vector<AABBCollider*> &platforms);
    void update();
};


#endif