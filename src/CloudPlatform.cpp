#include "CloudPlatform.h"
#include "handlers/WindowHandler.h"
#include "utils/utils.h"
using namespace std;

CloudPlatform::CloudPlatform(vector<AABBCollider*> &colliders, Position2 setPosition):image(this),cloudLength(generateRandomNumber(1,4)), cloudType(generateRandomNumber(0,0)),collider(0,0,0,0,this)
{
    setDebugName("Cloud Platform");
    scale = 3;
    collider.setRawWidth(12 * cloudLength);
    collider.setRawHeight(12);
    collider.setAABBColliders(colliders);
    collider.setUpdateOrder(50);
    image.setImage("cloud" + to_string(cloudLength) + "/sprite_" + to_string(cloudType) + ".png");
    cout << "Settting position now" << endl;
    position = setPosition;
    cout << "Successfully created Cloud Platform!" << endl;
}


CloudPlatform::~CloudPlatform()
{
    cout << "Trying to delete!" << endl;
}


void CloudPlatform::update()
{}