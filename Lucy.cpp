#include "Lucy.h"
#include "utils.h"
#define DEFAULT_RUN_SPEED 140
#define MAX_RUN_SPEED 400
#define TERMINAL_VELOCITY 5000
#define JUMP_HEIGHT 400
#define FALL_SPEED 25
#define LUCY_SCALE 2
using namespace std;

const string Lucy::lucyImagesPath = imagesPath + "lucyAnimations/";



Lucy::Lucy(std::vector<AABBCollider*> &platforms): PlatformerCollision(12 * LUCY_SCALE,24 * LUCY_SCALE,platforms), lucyAnimation(this), playerCamera(this)
{
    setScale(LUCY_SCALE);
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
    lucyAnimation.addAnimation(getAnimation("lucy_running",8), "run", 0.2);
    lucyAnimation.addAnimation(getAnimation("lucy_idle",9), "idle", 0.4);
    lucyAnimation.addAnimation(getAnimation("lucy_fall",4), "fall", 0.1);
    lucyAnimation.addAnimation(getAnimation("lucy_jump",8), "jump", 0.03);
    lucyAnimation.addAnimation(getAnimation("lucy_die",8), "die", 0.1, false);
    game->setActiveCamera(&playerCamera);
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
    if (touching[COLL_LEFT_WALL])
    {
        return ls_Die;
    }
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
        lucyAnimation.setImageOffset(-2,0);
    }
    else
    {
        lucyAnimation.setImageOffset(0,0);
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
        cout << velocity.y << endl;
        clampMin(velocity.y, 0);
    }
    previousState = currentState;
}


void Lucy::handleInput()
{
    if (game->keyState(SDL_SCANCODE_D) || game->keyState(SDL_SCANCODE_RIGHT))
    {
        velocity.x += DEFAULT_RUN_SPEED;
        lucyAnimation.setImageFlip(SDL_FLIP_NONE);
    }
    if (game->keyState(SDL_SCANCODE_A) || game->keyState(SDL_SCANCODE_LEFT))
    {
        velocity.x -= DEFAULT_RUN_SPEED;
        lucyAnimation.setImageFlip(SDL_FLIP_HORIZONTAL);
    }
    if (game->keyState(SDL_SCANCODE_W) || game->keyState(SDL_SCANCODE_UP))
    {
        if (onGround()) velocity.y -= JUMP_HEIGHT;
    }
    if (abs(velocity.x) > MAX_RUN_SPEED) velocity.x = sign(velocity.x) * (MAX_RUN_SPEED);

}


void Lucy::update()
{
    resetFrameVariables();
    handleInput();

    velocity.y += FALL_SPEED;
    if (touching[COLL_FLOOR]) velocity.y = 0;
    velocity.x = velocity.x * 0.8;
    clampMax(velocity.y, (float) TERMINAL_VELOCITY);

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