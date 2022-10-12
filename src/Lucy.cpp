#include "Lucy.h"
#include "handlers/InputHandler.h"
#include "handlers/CameraHandler.h"

#include "utils/utils.h"
using namespace std;

const string Lucy::lucyImagesPath = "lucyAnimations/";



Lucy::Lucy(std::vector<AABBCollider*> &platforms): PlatformerCollision(platforms,12,23), lucyAnimation(this), playerCamera(this,&lucyAnimation)
{
    setDebugName("Lucy");
    setUpdateOrder(10);
    lucyAnimation.setUpdateOrder(9);
    scale = 4;
    position = Position2(100,100);
    auto getAnimation = [](string pathName, int size)
    {
        vector<string> paths;
        for (int i = 0; i < size; i++)
        {
            paths.emplace_back(lucyImagesPath + pathName + "/" + "sprite_" + to_string(i) + ".png");
        }
        return paths;
    };
    lucyAnimation.addAnimation(getAnimation("lucy_running",8), "run", 0.2, true);
    lucyAnimation.addAnimation(getAnimation("lucy_idle",9), "idle", 0.4, true);
    lucyAnimation.addAnimation(getAnimation("lucy_fall",4), "fall", 0.1, true);
    lucyAnimation.addAnimation(getAnimation("lucy_jump",8), "jump", 0.03, false);
    lucyAnimation.addAnimation(getAnimation("lucy_die",8), "die", 0.1, false);
    lucyAnimation.changeConfiguration("idle");
    //game->cameraHandler->setActiveCamera(&playerCamera);
}
bool Lucy::onGround()
{
    return previousTouching[COLL_FLOOR] || touching[COLL_FLOOR];
}
void Lucy::resetFrameVariables()
{
}


ls__LucyState Lucy::determineState()
{
    //cout << "Position: " << position << endl;
    if (velocity.y < 0)
    {
        return ls_Jumping;
    }
    if (!onGround())
    {
        return ls_Falling;
    }
    if (abs(velocity.x) > 15 && !touchingWall())
    {
        return ls_Running;
    }
    return ls_Idle;
}


void Lucy::enforceState(ls__LucyState currentState)
{
    if (currentState == ls_Running && lucyAnimation.getFlippedStatus() == SDL_FLIP_NONE)
    {
        lucyAnimation.setImageOffset({-2,0});
    }
    else
    {
        lucyAnimation.setImageOffset({0,0});
    }
    if (previousState != currentState)
    {
        switch (currentState)
        {
            case ls_Running:
                lucyAnimation.changeConfiguration("run");
                break;
            case ls_Idle:
                lucyAnimation.changeConfiguration("idle");
                break;
            case ls_Falling:
                lucyAnimation.changeConfiguration("fall");
                break;
            case ls_Jumping:
                lucyAnimation.changeConfiguration("jump");
                break;
            case ls_Die:
                lucyAnimation.changeConfiguration("die");
            default:
                break;
        }
    }
    if (touching[COLL_CEILING])
    {
        clampMin(velocity.y, 0);
    }
    previousState = currentState;
}


void Lucy::handleInput()
{
    if (game->inputHandler->keyPressed(SDL_SCANCODE_D) || game->inputHandler->keyPressed(SDL_SCANCODE_RIGHT))
    {
        velocity.x += defaultRunSpeed;
        lucyAnimation.setImageFlip(SDL_FLIP_NONE);
    }
    if (game->inputHandler->keyPressed(SDL_SCANCODE_A) || game->inputHandler->keyPressed(SDL_SCANCODE_LEFT))
    {
        velocity.x -= defaultRunSpeed;
        lucyAnimation.setImageFlip(SDL_FLIP_HORIZONTAL);
    }
    if (game->inputHandler->keyPressed(SDL_SCANCODE_W) || game->inputHandler->keyPressed(SDL_SCANCODE_UP))
    {
        if (onGround()) velocity.y -= jumpHeight;
    }
    if (abs(velocity.x) > maxRunSpeed) velocity.x = sign(velocity.x) * (maxRunSpeed);

}


void Lucy::update()
{
    resetFrameVariables();
    handleInput();

    velocity.y += fallSpeed;
    if (touching[COLL_FLOOR]) velocity.y = 0;
    velocity.x = velocity.x * 0.8;
    clampMax(velocity.y, (float) terminalVelocity);

    enforceState(determineState());
    //outputCollisions();

    position += velocity * game->deltaTime;


    previousTouching[COLL_LEFT_WALL] = touching[COLL_LEFT_WALL];
    previousTouching[COLL_RIGHT_WALL] = touching[COLL_RIGHT_WALL];
    previousTouching[COLL_CEILING] = touching[COLL_CEILING];
    previousTouching[COLL_FLOOR] = touching[COLL_FLOOR];
    moveAndCollide();
    syncPositions();

}










    // if(velocity.x && velocity.y)
    // {
    //     //velocity = velocity * (TERMINAL_VELOCITY / sqrt(velocity.x * velocity.x + velocity.y * velocity.y));
    //     cout << (TERMINAL_VELOCITY / (float)sqrt(velocity.x * velocity.x + velocity.y * velocity.y)) << endl;
    // }