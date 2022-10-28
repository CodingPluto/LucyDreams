#ifndef SRC_POSITION_H
#define SRC_POSITION_H
#include <iostream>

class Position2
{
public:
    float x, y;

    Position2(): x(0), y(0){}
    Position2(float x, float y): x(x), y(y){}
    Position2(const Position2& src) // Copy Constructor Overload
    {
        x = src.x;
        y = src.y;
    }
    Position2 operator+=(Position2 pos)
    {
        x += pos.x;
        y += pos.y;
        return *this;
    }
    Position2 operator-=(Position2 pos)
    {
        x -= pos.x;
        y -= pos.y;
        return *this;
    }
    Position2 operator+(const Position2& pos)
    {
        return Position2(x + pos.x, y + pos.y);
    }
    Position2 operator-(const Position2& pos)
    {
        return Position2(x - pos.x, y - pos.y);
    }
    Position2 operator*(float scalar)
    {
        return Position2(x * scalar, y * scalar);
    }
    Position2 operator/(float scalar)
    {
        return Position2(x / scalar, y / scalar);
    }
    Position2 operator/(const Position2& pos)
    {   
        return Position2(x / pos.x, y / pos.y);
    }
    friend bool operator==(const Position2& lhs, const Position2& rhs)
    {
        return (lhs.x == rhs.x && lhs.y == rhs.y);
    }
    friend std::ostream& operator<<(std::ostream& os, Position2 pos)
    {
        std::cout << "{" << pos.x << "," << pos.y << "}";
        return std::cout;
    }
};

class Vector2 : private Position2
{
public:
    Vector2(){}
    Vector2(float x, float y):Position2(x,y){}

    //crossProd(){}
    //dotProd(){}
    //getMagnitiude(){}
};
#endif