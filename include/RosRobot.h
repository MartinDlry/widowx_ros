#ifndef ROSROBOT_H
#define ROSROBOT_H

#include "RoboticArm.h"


class RosRobot
{
    public:
        RoboticArm *pRoboticArm;
        Vec3 mPosition;
        
        RosRobot( RoboticArm* roboticArm , Vec3 position );

        bool canReachGoal();
        void setGoal( Vec3 goal , double goalAngle );
        void goToGoal();

    private:
        Vec3 mGoal;
        double mGoalAngle;
};

#endif