#include "Circle.h"

#include <math.h>

#include "Vec2.h"

Circle::Circle()
{
    mRadius = 0;
}
Circle::Circle( Vec2 center , double radius)
{
    mCenter = center;
    mRadius = radius;
}
Circle::Circle( double centerX , double centerY , double radius ) : Circle::Circle( Vec2( centerX , centerY ) , radius )
{}

void Circle::set( Vec2 center , double radius)
{
    mCenter = center;
    mRadius = radius;
}

void Circle::set( double centerX , double centerY , double radius )
{
    Circle::set( Vec2( centerX , centerY ) , radius );
}

bool Circle::roots( double a , double b , double c , std::array<double,2>* rootsTable )
{
    double delta = b*b - 4*a*c;
    if ( delta < 0 )
    {
        return false;
    }
    (*rootsTable)[0] = (-b - sqrt(delta)) / ( 2*a );
    (*rootsTable)[1] = (-b + sqrt(delta)) / ( 2*a );
    return true;
}

bool Circle::intersect( Circle circle , std::array<Vec2,2>* intersections)
{
    double x1 = mCenter.mX , y1 = mCenter.mY , x2 = circle.mCenter.mX , y2 = circle.mCenter.mY , r1 = mRadius , r2 = circle.mRadius;

    double m = (x1-x2)/(y2-y1);
    double p = (r1*r1 - r2*r2 - x1*x1 - y1*y1 +x2*x2 +y2*y2 )/(2*(y2-y1));

    double a = m*m + 1;
    double b = 2*( m*p - x1 - m*y1);
    double c = x1*x1 + y1*y1 - 2*p*y1 + p*p - (r1*r1);

    std::array<double,2> roots;
    if( !(Circle::roots( a , b , c , &roots )) )
    {
        return false;
    }

    (*intersections)[0].mX = roots[0];
    (*intersections)[0].mY = m * roots[0] + p;

    (*intersections)[1].mX = roots[1];
    (*intersections)[1].mY = m * roots[1] + p;
    return true;
}