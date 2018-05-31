#include "Vec2.h"

#include <math.h>
#include <ostream>

Vec2::Vec2()
{
    mX = 0;
    mY = 0;
}

Vec2::Vec2( double x , double y )
{
    mX = x;
    mY = y;
}

void Vec2::set( double x , double y )
{
    mX = x;
    mY = y;
}

Vec2 Vec2::operator+( Vec2 v )
{
    return ( Vec2( (mX + v.mX) , (mY + v.mY) ) );
}

void Vec2::operator+=( Vec2 v )
{
    mX += v.mX;
    mY += v.mY;
}

Vec2 Vec2::operator-( Vec2 v )
{
    return ( Vec2( (mX - v.mX) , (mY - v.mY) ) );
}

Vec2 Vec2::operator*( double d )
{
    return ( Vec2( (mX * d) , (mY * d) ) );
}

Vec2 Vec2::makeVec2( double angle , double length )
{
    return( Vec2( cos(angle) , sin(angle) ) * length );
}

std::ostream& operator<<(std::ostream &strm, const Vec2 &v) {
    return strm << "Vec2[" << v.mX << "," << v.mY << "]" ;
}

