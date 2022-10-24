#include "Lucy.h"
#include "../clouds/CloudPlatform.h"
#include "../clouds/CheckpointPlatform.h"
#include "../handlers/InputHandler.h"
#include "../handlers/WindowHandler.h"
#include "../handlers/CameraHandler.h"
#include "../handlers/ImageHandler.h"
#include "../handlers/SceneHandler.h"
#include "../utils/utils.h"
using namespace std;

const string Lucy::lucyImagesPath = "lucyAnimations/";


void Lucy::onStart()
{
    cout << "Lucy on Start" << endl;
}

Lucy::Lucy(std::vector<AABBCollider*> &platforms): lucyAnimation(this), playerCamera(this,&lucyAnimation),platforms(platforms)
{
    //PlatformerCollision(platforms,8,19)
    //collisionChecker.setRawOffset({2,4});
    setDebugName("Lucy");
    setUpdateOrder(10);
    lucyAnimation.setDrawOrder(0);
    scale = 4;
    jumping = false;
    auto getAnimation = [](string pathName, int size)
    {
        vector<string> paths;
        for (int i = 0; i < size; i++)
        {
            paths.emplace_back(lucyImagesPath + pathName + "/" + "sprite_" + to_string(i) + ".png");
        }
        return paths;
    };
    lucyAnimation.addAnimation(getAnimation("lucy_running",8), "run", 0.15, true);
    lucyAnimation.addAnimation(getAnimation("lucy_idle",9), "idle", 0.3, true);
    lucyAnimation.addAnimation(getAnimation("lucy_fall",4), "fall", 0.05, true);
    lucyAnimation.addAnimation(getAnimation("lucy_jump",8), "jump", 0.03, false);
    lucyAnimation.addAnimation(getAnimation("lucy_die",8), "die", 0.1, false);
    lucyAnimation.changeConfiguration("idle");
    position = Position2(game->windowHandler->getCentreScreenX(lucyAnimation.getWidth()), 200);
    game->cameraHandler->setActiveCamera(&playerCamera);
    playerCamera.setCameraScrollingType(st_VerticalOnly);
    playerCamera.setCameraOffset({0,-170});
    lucyAnimation.setImage(lucyImagesPath + "lucy_idle" + "/" + "sprite_0" + ".png");
}
bool Lucy::onGround()
{
    return touching[COLL_FLOOR] || previousTouching[COLL_FLOOR];
}
void Lucy::resetFrameVariables()
{
    for(int i = 0; i < 4; i++)
    {
        touching[i] = false;
    }
}


ls__LucyState Lucy::determineState()
{
    //cout << "Position: " << position << endl;
    if (velocity.y < 0)
    {
        return ls_Jumping;
    }
    if (!currentPlatform && velocity.y > 450)
    {
        return ls_Falling;
    }
    if (abs(velocity.x) > 15)// && //!touchingWall())
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
    previousState = currentState;
    if (touching[COLL_CEILING])
    {
        clampMin(velocity.y, 0);
    }
    previousState = currentState;
}


void Lucy::handleInput()
{
    if (!currentPlatform && hadCurrentPlatformLastFrame)
    {
        //coyoteTime = true;
    }
    if (coyoteTime)
    {
        coyoteCounter ++;
    }
    if (coyoteTime > coyoteFrames)
    {
        coyoteTime = false;
    }
    if (!touching[COLL_LEFT_WALL])
    {
        if (game->inputHandler->keyPressed(SDL_SCANCODE_D) || game->inputHandler->keyPressed(SDL_SCANCODE_RIGHT))
        {
            velocity.x += defaultRunSpeed;
            lucyAnimation.setImageFlip(SDL_FLIP_NONE);
        }
    }
    if (!touching[COLL_RIGHT_WALL])
    {
        if (game->inputHandler->keyPressed(SDL_SCANCODE_A) || game->inputHandler->keyPressed(SDL_SCANCODE_LEFT))
        {
            velocity.x -= defaultRunSpeed;
            lucyAnimation.setImageFlip(SDL_FLIP_HORIZONTAL);
        }
    }
    //cout << onGround() << endl;
    if (jumping)
    {
        if (!(game->inputHandler->keyPressed(SDL_SCANCODE_W) || game->inputHandler->keyPressed(SDL_SCANCODE_UP)))
        {
            extendedJump = false;
        }
        framesSinceJump++;
        if (extendedJump)
        {
            if (framesSinceJump < 10)
            {
                velocity.y -= jumpHeight / (4 + framesSinceJump * 2);
            }
        }
    }
    if (game->inputHandler->keyJustPressed(SDL_SCANCODE_W) || game->inputHandler->keyJustPressed(SDL_SCANCODE_UP))
    {
        if (onGround() || coyoteTime)
        {
            jumping = true;
            velocity.y -= jumpHeight;
            coyoteTime = false;
            framesSinceJump = 0;
            extendedJump = true;
        };
    }
    if (abs(velocity.x) > maxRunSpeed) velocity.x = sign(velocity.x) * (maxRunSpeed);

}


void Lucy::correctPosition()
{
    float borderWidth = 12 * scale;
    if (position.x + borderWidth > game->windowHandler->getScreenWidth())
    {
        position.x =  game->windowHandler->getScreenWidth() - borderWidth;
    }
    else if (position.x < 0)
    {
        position.x = 0;
    }
}

void Lucy::checkCollision()
{

    float width = 12 * scale;
    float yOffset = 21 * scale;
    float height = 2 * scale;
    if (!currentPlatform)
    {
        hadCurrentPlatformLastFrame = false;
        for (AABBCollider* platform : platforms)
        {
            if (position.x < platform->position.x + platform->width &&
            position.x + width > platform->position.x &&
            position.y + height + yOffset > platform->position.y &&
            position.y + yOffset < platform->position.y + platform->height)
            {
                if (position.y + yOffset < platform->position.y || (!onGround() && velocity.y > fallSpeed * 25))
                {
                    if (velocity.y > 0)
                    {
                        heightOfNewPlatforms.emplace_back(platform->position.y);
                        currentPlatformCollider = platform;
                        if (currentPlatformCollider->hasColliderTag("CloudPlatformCheckpoint"))
                        {
                            CheckpointPlatform *checkpointPlatform = dynamic_cast<CheckpointPlatform*>(currentPlatformCollider->getOwner());
                            if (checkpointPlatform->sceneName != game->sceneHandler->getCurrentSceneName())
                            {
                                game->sceneHandler->setScene(checkpointPlatform->sceneName);
                            }
                        }
                        /*
                        */
                    }
                }
            }
        }
        for (auto heightOfPlatform : heightOfNewPlatforms)
        {
            int succeededBattles = 0;
            for (auto heightChallenged : heightOfNewPlatforms)
            {
                if (heightOfPlatform <= heightChallenged)
                {
                    succeededBattles++;
                }
            }
            if (succeededBattles == heightOfNewPlatforms.size())
            {
                currentPlatform = dynamic_cast<CloudPlatform*>(currentPlatformCollider->getOwner());
                break;
            }
        }
        heightOfNewPlatforms.clear();
    }
    else
    {

        position.y += currentPlatform->getMovementSpeed();
        if (position.x < currentPlatformCollider->position.x + currentPlatformCollider->width &&
            position.x + width > currentPlatformCollider->position.x &&
            position.y + height + yOffset > currentPlatformCollider->position.y &&
            position.y + yOffset < currentPlatformCollider->position.y + currentPlatformCollider->height)
        {
            position.y = currentPlatformCollider->position.y - height - yOffset;
            velocity.y = 0;
            touching[COLL_FLOOR] = true;
            jumping = false;
            hadCurrentPlatformLastFrame = true;
        }
        else
        {
            currentPlatform = nullptr;
            currentPlatformCollider = nullptr;
        }
    }
    /*
    SDL_Rect rect;
    rect.x = position.x;
    rect.y = position.y + yOffset;
    rect.w = width;
    rect.h = height;
    game->imageHandler->drawRect(&rect,{0,0,0,255},true,false);
    */
}



void Lucy::update()
{
    resetFrameVariables();
    
    handleInput();
    velocity.y += fallSpeed;
    if (touching[COLL_FLOOR] && velocity.y > 0) velocity.y = 0;
    clampMax(velocity.y, (float) terminalVelocity);
    enforceState(determineState());
    //outputCollisions();

    position += velocity * game->deltaTime;
    velocity.x = velocity.x * 0.7;
    checkCollision();
    correctPosition();

    previousTouching[COLL_LEFT_WALL] = touching[COLL_LEFT_WALL];
    previousTouching[COLL_RIGHT_WALL] = touching[COLL_RIGHT_WALL];
    previousTouching[COLL_CEILING] = touching[COLL_CEILING];
    previousTouching[COLL_FLOOR] = touching[COLL_FLOOR];
    syncPositions();

}










    // if(velocity.x && velocity.y)
    // {
    //     //velocity = velocity * (TERMINAL_VELOCITY / sqrt(velocity.x * velocity.x + velocity.y * velocity.y));
    //     cout << (TERMINAL_VELOCITY / (float)sqrt(velocity.x * velocity.x + velocity.y * velocity.y)) << endl;
    // }