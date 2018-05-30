#ifndef ROSROBOT_H
#define ROSROBOT_H

#include "RoboticArm.h"

class RosRobot
{
    public:
        RoboticArm *pRoboticArm;
        Point3 mPosition;
};

#endif