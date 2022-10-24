#ifndef SRC_TRIGGER_H
#define SRC_TRIGGER_H
#include <functional>
#include "../gameData/GameObject.h"

class Trigger : public GameObject
{
public:
    Trigger(const class Sprite *target, const unsigned int detectionRange);
    Trigger(std::vector<const class Sprite*> targets, const unsigned int detectionRange);

    ~Trigger();
private:
    bool enabled;
    const unsigned int detectionRange;
    std::function<void()> onEntry;
    std::function<void()> onOverlapping;
    std::function<void()> onExit;
    void update() override;
    std::vector<const class Sprite*> targets;

};

#endif
