#ifndef VEC2_H
#define VEC2_H

#include <ostream>

class Vec2
{
    public:
        double mX;
        double mY;

        Vec2();
        Vec2( double x , double y );
        void set( double x , double y );
        Vec2 operator+( Vec2 v);
        void operator+=( Vec2 v );
        Vec2 operator-( Vec2 v);
        Vec2 operator*( double d );

        static Vec2 makeVec2( double angle , double length );
        
    private:

};

std::ostream& operator<<(std::ostream &strm, const Vec2 &v);

#endif