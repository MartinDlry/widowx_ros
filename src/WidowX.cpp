#include "WidowX.h"

#include <iostream>

#include "ServoGroup.h"
#include "DynamixelServo.h"
#include "WidowXServos.h"
#include "Vec3.h"
#include "Vec2.h"
#include "Circle.h"


WidowX::WidowX()
{
    pServoGroup = (ServoGroup*)(new WidowXServos());
    mLengths = { L0 , L1 , L2 };
}

Vec3 WidowX::headPosition()
{
    Vec2 v2 = head2DPosition();
    v2.mX = - v2.mX;
    double a = ((((WidowXServos*)pServoGroup)-> mServos)[0])->radian();
    return Vec3( v2.mX * cos( a ) , v2.mY , v2.mX * sin( a ) );
}

Vec2 WidowX::head2DPosition()
{ 
    double a = 0;
    Vec2 pos( 0 , 0 );
    std::cout << pos;
    for( int i = 1 ; i < 4 ; i++ )
    {

        a += ((((WidowXServos*)pServoGroup)-> mServos)[i])->radian(); //add the next servo relative radian angle
        std::cout << "a=" << a << " length=" << mLengths[i-1] << std::endl;
        pos += Vec2::makeVec2( a , mLengths[i-1] ); // add the next servo relative position
        std::cout << pos;
    }
    return pos;
}

bool WidowX::canReachGoal()
{
    WidowXServos s;
    s.mServos[0]->setAngle( atan2( mGoal.mZ , mGoal.mX ));

}

void WidowX::setGoal( Vec3 goal , double goalAngle )
{
    mGoal = goal;
    mGoalAngle = goalAngle;
}

void WidowX::goToGoal()
{
    std::array<Vec2,2> intersections;
    Vec2 wrist = wristPosition();
    if ( Circle( 0 , 0 , mLengths[0] ).intersect( Circle( wrist , mLengths[1] ) , &intersections) )
    {

    }
}

Vec2 WidowX::goal2D()
{
    return Vec2( -sqrt( mGoal.mX*mGoal.mX + mGoal.mZ*mGoal.mZ ) , mGoal.mY );
}

Vec2 WidowX::wristPosition()
{
    return ( goal2D() - Vec2( cos(mGoalAngle) , sin(mGoalAngle) ) * mLengths[2] );
}

void compute3LastMotors( ServoGroup* sevroGroup , Vec2 elbowPosition , Vec2 wristPosition )
{
    
}
