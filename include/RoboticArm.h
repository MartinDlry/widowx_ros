#ifndef ROBOTICARM_H
#define ROBOTICARM_H

#include "Point3.h"
#include "ServoGroup.h"

//interface
class RoboticArm
{
    
    public:
        ServoGroup *pServoGroup;
        virtual Point3 headPosition() = 0;
        

};

#endif