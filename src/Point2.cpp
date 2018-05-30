#include "Point2.h"

Point2::Point2()
{
    _x = 0;
    _y = 0;
}

Point2::Point2( double x , double y )
{
    _x = x;
    _y = y;
}

void Point2::set( double x , double y )
{
    _x = x;
    _y = y;
}

