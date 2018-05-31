#ifndef ROSSPACE_H
#define ROSSPACE_H

#include <vector>

#include "RosRobot.h"
#include "Polygon3.h"

class RosSpace
{
    
    public:
        RosSpace();
        
        std::vector<RosRobot*> mRosRobots;
        std::vector<Polygon3> mObstacles;
        
    private:

};

#endif