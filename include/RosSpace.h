#ifndef ROSSPACE_H
#define ROSSPACE_H

#include <vector>

#include "RosRobot.h"
class RosSpace
{
    
    public:
        RosSpace();
        
        std::vector<RosRobot*> mRosRobots;
    
    private:

};

#endif