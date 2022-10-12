#include "Trigger.h"
#include "Sprite.h"
using namespace std;


Trigger::Trigger(const Sprite *target, const unsigned int detectionRange): detectionRange(detectionRange)
{
    targets.emplace_back(target);
    setDebugName("Trigger");
}

Trigger::Trigger(std::vector<const Sprite*> targets, const unsigned int detectionRange): detectionRange(detectionRange)
{
    this->targets.assign(targets.begin(),targets.end());
    setDebugName("Trigger");
}

Trigger::~Trigger()
{}

void Trigger::update()
{
    cout << "I'm a trigger and I'm updating." << endl;
}