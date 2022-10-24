#include <math.h>
#include "CloudPlatform.h"
#include "../handlers/WindowHandler.h"
#include "../utils/utils.h"
using namespace std;

CloudPlatform::CloudPlatform(vector<AABBCollider*> &colliders, Position2 setPosition, unsigned int cloudLength, int movementRange):image(this),cloudLength(cloudLength), cloudType(cloudType),collider(0,0,0,0,this)
{
    collider.setAABBColliders(colliders);
    position = setPosition;
    construct();
    setCloudLength(cloudLength);

}
CloudPlatform::CloudPlatform(vector<AABBCollider*> &colliders): image(this), collider(0,0,0,0,this)
{
    collider.setAABBColliders(colliders);
    construct();
}

void CloudPlatform::construct()
{
    this->cloudType = generateRandomNumber(1,3);
    setDebugName("Cloud Platform");
    scale = 3;
    collider.setRawHeight(cloudHeight);
    collider.setUpdateOrder(cloudUpdatePosition - 1);
    this->movementRange = movementRange;
    setUpdateOrder(cloudUpdatePosition);
    sinPoint = generateRandomNumber(1,1);

}

CloudPlatform::~CloudPlatform()
{}


void CloudPlatform::update()
{
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
    image.setImage("cloud" + to_string(this->cloudLength) + "/sprite_" + to_string(this->cloudType - 1) + ".png");
    collider.setRawWidth(cloudTileWidth * this->cloudLength);
}


const float &CloudPlatform::getMovementSpeed()
{
    return movementSpeed;
}