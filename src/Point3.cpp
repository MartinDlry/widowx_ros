#include "Point3.h"

Point3::Point3()
{
    _x = 0;
    _y = 0;
    _z = 0;
}

Point3::Point3( double x , double y , double z )
{
    _x = x;
    _y = y;
    _z = z;
}

void Point3::set( double x , double y , double z )
{
    _x = x;
    _y = y;
    _z = z;
}

