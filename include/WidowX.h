#ifndef WIDOWX_H
#define WIDOWX_H

#include<array>

#include "RoboticArm.h"
#include "Vec2.h"
#include "WidowXServos.h"

#define L0 15.0
#define L1 14.14 
#define L2 14.75


class WidowX : public RoboticArm
{
    public:
        WidowX( );
        Vec3 headPosition();
        std::array<double,3> mLengths;

        bool canReachGoal();
        void setGoal( Vec3 goal , double goalAngle );
        void goToGoal();

    private:
        Vec2 head2DPosition();
        std::array<int,6> mServosGoalPositions; 
        Vec2 goal2D();
        Vec2 wristPosition();
        void compute3LastMotors( WidowXServos* servos , Vec2 elbowPosition , Vec2 wristPosition );
};
#endif