#ifndef POSITION_HPP_
#define POSITION_HPP_

#include "stm32g4xx.h"


class Position{
public:
    float x;
    float y;
    float th;
public:
    Position(float _x=0.0f, float _y=0.0f, float _th=0.0f) : x(_x),y(_y),th(_th){}
    Position(const Position &pos) : x(pos.x), y(pos.y), th(pos.th){}

    inline Position operator+(const Position &pos) const { return Position(x+pos.x, y+pos.y, th+pos.th); }
    inline Position operator-(const Position &pos) const { return Position(x-pos.x, y-pos.y, th-pos.th); }
    
    inline const Position& operator=(const Position &pos) { x=pos.x; y=pos.y; th=pos.th; return *this; }

};


#endif