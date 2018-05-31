#ifndef VEC3_H
#define VEC3_H

# include <ostream>

class Vec3
{
    public:
        double mX;
        double mY;
        double mZ;

        Vec3();
        Vec3( double x , double y , double z );
        void set( double x , double y , double z );
        double distanceTo( Vec3 p );
        Vec3 operator+( Vec3 p );
        Vec3 operator-( Vec3 p );
    private:

};

std::ostream& operator<<(std::ostream &strm, const Vec3 &v);

#endif