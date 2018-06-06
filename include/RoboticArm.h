#ifndef ROBOTICARM_H
#define ROBOTICARM_H

#include "Vec3.h"

//interface
class RoboticArm
{
    
    public:
        virtual Vec3 headPosition() = 0;
        virtual bool canReachGoal() = 0;
        virtual void setGoal( Vec3 goal , double goalAngle ) = 0;
        virtual void goToGoal() = 0;

    protected:
        Vec3 mGoal;
        double mGoalAngle;
};

#endif