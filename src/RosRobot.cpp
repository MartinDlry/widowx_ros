# include "RosRobot.h"

#include "RoboticArm.h"
#include "Vec3.h"

RosRobot::RosRobot( RoboticArm::RoboticArm *roboticArm , Vec3::Vec3 position )
{

}

bool RosRobot::canReachGoal()
{
    pRoboticArm->canReachGoal();
}
void RosRobot::setGoal( Vec3 goal , double goalAngle )
{
    pRoboticArm->setGoal( goal - mPosition , goalAngle );
}

void RosRobot::goToGoal()
{
    pRoboticArm->goToGoal();
    // work to do here
}