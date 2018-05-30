#ifndef POINT3_H
#define POINT3_H

class Point3
{
    public:
        double _x;
        double _y;
        double _z;

        Point3();
        Point3( double x , double y , double z );
        void set( double x , double y , double z );
        double distanceTo( Point3 p );
    private:

};

#endif