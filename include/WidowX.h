#ifndef WIDOWX_H
#define WIDOWX_H

#include "RoboticArm.h"

class WidowX : public RoboticArm
{
    public:
        WidowX::WidowX( ServoGroup::ServoGroup *servoGroup );
        Point3 headPosition();
};
#endif