#include <math.h>
#include "CloudPlatform.h"
#include "handlers/WindowHandler.h"
#include "utils/utils.h"
using namespace std;

CloudPlatform::CloudPlatform(vector<AABBCollider*> &colliders, Position2 setPosition, unsigned int cloudLength, unsigned int cloudType, int movementRange):image(this),cloudLength(cloudLength), cloudType(cloudType),collider(0,0,0,0,this)
{
    if (!cloudLength)
    {
        this->cloudLength = generateRandomNumber(1,5);
    }
    if (!cloudType)
    {
        this->cloudType = generateRandomNumber(1,3);
    }
    if (generateRandomNumber(0,1))
    {
        movementDirection = 1;
    }
    else
    {
        movementDirection = -1;
    }
    setDebugName("Cloud Platform");
    scale = 3;
    collider.setRawHeight(12);
    collider.setAABBColliders(colliders);
    collider.setUpdateOrder(50);
    this->movementRange = movementRange;
    setUpdateOrder(100);
    setCloudLength(this->cloudLength);
    position = setPosition;
    sinPoint = generateRandomNumber(1,1);
}


CloudPlatform::~CloudPlatform()
{}


void CloudPlatform::update()
{
    //position.x += movementDirection;
    movementSpeed = sin(sinPoint) * movementRange;
    position.y += movementSpeed;
    sinPoint += 0.02;
}

const int CloudPlatform::getCloudLength()
{
    return cloudLength;
}
const int CloudPlatform::getCloudType()
{
    return cloudType;
}

void CloudPlatform::setCloudLength(unsigned int cloudLength)
{
    this->cloudLength = cloudLength;
    if (cloudLength >= 100)
    {
        image.setImage("bigCloud.png");
        collider.setRawWidth(12 * 5 * 6);
    }
    else
    {
        image.setImage("cloud" + to_string(this->cloudLength) + "/sprite_" + to_string(this->cloudType - 1) + ".png");
        collider.setRawWidth(12 * this->cloudLength);
    }
}

const float &CloudPlatform::getMovementSpeed()
{
    return movementSpeed;
}