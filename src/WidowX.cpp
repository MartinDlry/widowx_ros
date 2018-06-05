#include "WidowX.h"

#include <sstream>
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
    for( int i = 1 ; i < 4 ; i++ )
    {
        a += ((((WidowXServos*)pServoGroup)-> mServos)[i])->radian(); //add the next servo relative radian angle
        pos += Vec2::makeVec2( a , mLengths[i-1] ); // add the next servo relative position
    }
    return pos;
}

bool WidowX::canReachGoal()
{
    WidowXServos testServos;
    //std::cout << testServos << std::endl;
    testServos.mServos[0]->setAngle( atan2( mGoal.mZ , mGoal.mX ));
    //std::cout << "motor 0 pos :" << testServos.mServos[0]->position() << std::endl;
    std::array<Vec2,2> intersections;
    Vec2 wrist = wristPosition();
    //std::cout << "wrist position =" << wrist << std::endl; 
    if ( Circle( 0 , 0 , mLengths[0] ).intersect( Circle( wrist , mLengths[1] ) , &intersections) )
    {
        //std::cout << "intersection 0 = " << intersections[0] << std::endl;
        //std::cout << "intersection 1 = " << intersections[1] << std::endl;
        compute3LastMotors( &testServos , intersections[0] , wrist );
        //std::cout << "case 1" << testServos << std::endl;
        bool b =  testServos.validPositions();
        int variation1 = ( (WidowXServos*)pServoGroup)->variation( &testServos );
        //std::cout << "var = " << variation1 << std::endl;
        std::array<int,6> pos1 = testServos.getPositions();
        compute3LastMotors( &testServos , intersections[1] , wrist );
        //std::cout << "case 2" <<testServos << std::endl;     

        if ( testServos.validPositions() )
        {
            if( b && ( ( ( WidowXServos* )pServoGroup )->variation( &testServos ) ) > variation1 ) //if both are valid but first is better
                mServosGoalPositions = pos1;
            else
                mServosGoalPositions = (testServos.getPositions()); 
        }
        else if( b )
        {
            mServosGoalPositions = pos1;
        }
        else
        {
            return false;
        }
        return true;
    }
}

void WidowX::setGoal( Vec3 goal , double goalAngle )
{
    mGoal = goal;
    mGoalAngle = goalAngle;
}

void WidowX::goToGoal()
{
    if( canReachGoal())
    {
        ((WidowXServos*)pServoGroup)->setPositions( mServosGoalPositions );
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

void WidowX::compute3LastMotors( WidowXServos* servos , Vec2 elbowPosition , Vec2 wristPosition )
{
    double a = atan2( elbowPosition.mY , elbowPosition.mX ),
    a2 = atan2( (wristPosition.mY - elbowPosition.mY ) , (wristPosition.mX - elbowPosition.mX ));
    servos->mServos[1]->setAngle( a );
    servos->mServos[2]->setAngle( a2 - a );
    servos->mServos[3]->setAngle( mGoalAngle - a2 );
}
