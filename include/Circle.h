#ifndef CIRCLE_H
#define CIRCLE_H

#include <array>

#include "Vec2.h"


class Circle
{
    public:
        Vec2 mCenter;
        double mRadius;

        Circle();
        Circle( Vec2 center , double radius);
        Circle( double centerX , double centerY , double radius );
        void set( Vec2 center , double radius);
        void set( double centerX , double centerY , double radius );

        bool intersect( Circle c , std::array<Vec2,2>* intersections);
        
    private:
        bool roots( double a , double b , double c , std::array<double,2>*);
};

#endif