#ifndef SRC_BLOCKERS_BLOCKER_H
#define SRC_BLOCKERS_BLOCKER_H
#include "../gameData/Sprite.h"
class Platform : public Sprite
{
public:
    Platform(const unsigned int platformLength, const bool direction);
    void setPlatformImages(const std::string &imageL, const std::string &imageM, const std::string &imageR);
    float getWidth();
private:
    static const char left = 0;
    static const char right = 1;
    bool direction;
    ~Platform();
    void update();
    const unsigned int platformLength;
    class ImageComponent* *platformSections;


};

#endif