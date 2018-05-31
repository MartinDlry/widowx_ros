#include "Vec3.h"

#include <ostream>

Vec3::Vec3()
{
    mX = 0;
    mY = 0;
    mZ = 0;
}

Vec3::Vec3( double x , double y , double z )
{
    mX = x;
    mY = y;
    mZ = z;
}

void Vec3::set( double x , double y , double z )
{
    mX = x;
    mY = y;
    mZ = z;
}

Vec3 Vec3::operator+( Vec3 p )
{
    return Vec3( (mX + p.mX) , (mY + p.mY) , (mZ + p.mZ) );
}

Vec3 Vec3::operator-( Vec3 p )
{
    return Vec3( (mX - p.mX) , (mY - p.mY) , (mZ - p.mZ) );
}

std::ostream& operator<<(std::ostream &strm, const Vec3 &v) {
    return strm << "Vec3[" << v.mX << " , " << v.mY  << " , " << v.mZ << "]" ;
}

