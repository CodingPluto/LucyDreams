
#include <vector>
#include "GameObject.h"
#include "../utils/Position.h"

#ifndef SRC_SPRITE_H
#define SRC_SPRITE_H

class Sprite : public GameObject
{
private:

protected:
    bool isPositionRelative;
    Position2 position;
    Position2 previousPosition;
    float scale;
    void syncPositions();

    void displayPosition();

public:
    Sprite();

    // Position
    bool getIsPositionRelative();
    Position2 getPosition();
    Position2 getPreviousPosition();
    Position2 getAbsolutePosition();
    float getX();
    float getY();
    void setPosition(float x, float y);
    void setPosition(Position2 position);
    void setX(float x);
    void setY(float y);
    void changeX(float x);
    void changeY(float y);
    void changePosition(float x, float y);
    void changePosition(Position2 position);
    float getScale();
};


#endif
